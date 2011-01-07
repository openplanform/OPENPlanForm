#!/usr/bin/php -q
<?php

// ------------------------- CONFIGURACIONES -----------------------------

error_reporting(E_ALL);

// Es necesario cambiar el directorio base para que las constantes de path
// se referencien correctamente.
chdir('../');

// Se incluyen las definiciones del sistema de archivos
include_once 'configs/OwlGlobals.php';

// Se agregan las librerías al include_path
set_include_path(get_include_path() . PATH_SEPARATOR . LIBDIR . PATH_SEPARATOR . EXTLIBDIR);

// Clases necesarias
require_once 'OwlConsole.inc';
require_once 'OwlLog.inc';
require_once 'OwlMailer.inc';
require_once 'OwlMailerTemplate.inc';
require_once 'OwlSession.inc';
require_once 'dbase/OwlGenericDO.inc';
require_once 'helper/OwlDate.inc';

require_once CLASSESDIR . 'PplCacheBO.inc';
require_once MODELDIR . 'TblAlumno.inc';

// Aplicación
try {

	$shell = new OwlConsole();
	$shell->getOwlEnvironment();
	$appConfig = $shell->getApplicationConfig();
	
	$cacheBO = new PplCacheBO($shell->db);
	$log = new OwlLog('cron');
	
	$token = $shell->getArg(1);
	$modo = $shell->getArg(2);
	
} catch (OwlException $e){
	
	$e->echoCmsMessage();
	
}


// ------------------------ FLUJO DE EJECUCIÓN  --------------------------

$modos = array('curso');

if ($token != '-m'){
	muestraAyuda();
}

if (!in_array($modo, $modos)){
	muestraAyuda();
}

switch ($modo){
	
	case 'curso':
		
		// Avisos sobre inicio de cursos
		checkInicioCursos();
		
		
		
	break;
	
}

// Recordar que en unix, un cierre exitoso retorna 0
return 0;


// --------------------- FUNCIONES INTERNAS DEL SCRIPT  -------------------


/**
 * ENVÍA LOS CORREOS DE AVISO DE INICIO DE CURSO
 */
function checkInicioCursos(){
	
	global $shell, $log, $cacheBO, $mailer, $appConfig;
	
	
	// Fechas
	$proximoInicio = date('Y-m-d', strtotime('+5 day'));
	$hoy = date('Y-m-d');
	
	// Se obtienen todos los cursos
	$sql = "SELECT * FROM tblCurso WHERE dInicio BETWEEN '$hoy' AND '$proximoInicio'";
	$cursosProximosCOL = OwlGenericDO::createCollection($shell->db, $sql, 'TblCurso');
	
	
	// Se avisará a todos los *alumnos* de cada curso
	// que el mismo está por comenzar 
	foreach ($cursosProximosCOL as $cursoDO){
	
		$alumnosCOL = $cacheBO->getAlumnosCurso($cursoDO->getIdCurso());
		
		$mt = new OwlMailerTemplate();
		$mt->setTemplate(LAYOUTDIR . 'inicioCurso.txt');
		$mt->addField('CURSO', $cursoDO->getVNombre());
		$mt->addField('FECHA', OwlDate::getDiaMesAno($cursoDO->getDInicio()));
		$mt->addField('ENLACE', 'http://www.in.planespime.es/cursos/ficha.html/' . $cursoDO->getIdCurso());		
		
		// Enviaré un correo a cada alumno
		foreach ($alumnosCOL as $alumnoDO){
			
			$mailer = new OwlMailer($appConfig->getMailerConfiguration());
			
			$mailer->setFrom('noreply@planespime.es', 'Recordatorios Planespime.es');
			$mailer->setBody($mt->getContent());
			$mailer->addTo($alumnoDO->getVEmail(), $alumnoDO->getVNombre() . ' ' . $alumnoDO->getVPrimerApellido() . ($alumnoDO->getVSegundoApellido() ? ' ' . $alumnoDO->getVSegundoApellido() : ''));
			$mailer->setSubject('Recordatorio de inicio de curso - ' . $cursoDO->getVNombre());
			
			try {
				
				$mailer->send();
				
			} catch (Zend_Mail_Protocol_Exception $e){
				
				$log->addLine('Error al enviar aviso a: ' . $alumnoDO->getVEmail() . '. Exept: ' . $e->getMessage());
				continue;
				
			}
			
		}
		
		$log->addLine('Enviados todos los avisos de inicio para el curso: ' . $cursoDO->getVNombre());
		
	}
	
}


/**
 * ENVÍA EL AVISO DE LOS PRECANDIDATOS QUE NO HAN SIDO SELECCIONADOS
 */
function avisoPrecandidatosOut(){
	
	/*global $shell, $log, $cacheBO, $mailer, $appConfig;
	
	// Fechas
	$proximoInicio = date('Y-m-d', strtotime('+5 day'));
	$hoy = date('Y-m-d');
	
	// Se obtienen todos los cursos
	$sql = "SELECT * FROM tblCurso WHERE dInicio BETWEEN '$hoy' AND '$proximoInicio'";
	$cursosProximosCOL = OwlGenericDO::createCollection($shell->db, $sql, 'TblCurso');
	
	foreach ($cursosProximosCOL as $cursoDO){
		
		$precandidatosARR = $cacheBO->getDatosUsuarioPrecandidatosCurso($cursoDO->getIdCurso());
		
		foreach ($precandidatosARR as $precandidato){
			
			
			
		}
		
	}
	
	VERIFICAR, IGUAL NO ES NECESARIO REALIZAR ESTA TAREA EN UN CRON, COMENTAR CON AARON
	
	*/
	
}


/**
 * Muestra la ayuda del script
 * @return void
 */
function muestraAyuda(){
	
	global $shell;
	
	$shell->println('');
	$shell->println('Modo de uso: PplCronJobs.php -m [modo]');
	$shell->println('');
	
	die();
	
}




?>