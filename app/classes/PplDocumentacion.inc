<?php

require_once 'OwlPdf.inc';
require_once 'helper/OwlFile.inc';
require_once 'helper/OwlDate.inc';

require_once CLASSESDIR . 'PplCacheBO.inc';


/**
 * Clase que contiene la definición de estructura para 
 * informes pdf generados. 
 * @author nico
 *
 */
class PplDocumentacion{
	
	/**
	 * Objeto de tratamiento de archivos pdf
	 * @var OwlPdf
	 */
	protected $pdf;
	
	/**
	 * Referencia a la base de datos
	 * @var OwlConnection
	 */
	protected $db;
	
	/**
	 * Identificador del documento
	 * @var string
	 */
	protected $identificadorDocumento;

	/**
	 * Gestor de archivos
	 * @var OwlFile
	 */
	protected $fileMan;
	
	/**
	 * Identificador interno del documento
	 * @var integer
	 */
	protected $docId;
	
	/**
	 * Array donde se mapean los metodos indexados por
	 * el identificador de documento
	 * @var array
	 */
	protected $validDocs = array(
		'S-30', // docControlAsistencia
		'S-20', // docListadoInicialAsistentes
		'S-10', // docInicioAccionFormativa
	);
	
	
	/**
	 * Establece el documento a tratar y la conexión a la base de datos.
	 * Si los datos son correctos llama al método para cargar el archivos a tratar.
	 * 
	 * @param OwlConnection $db
	 * @param string $identificadorDocumento
	 */
	public function __construct(OwlConnection $db, $identificadorDocumento){
		
		// Datos y objetos necesarios
		$this->db = $db;
		$this->identificadorDocumento = $identificadorDocumento;
		$this->fileMan = new OwlFile();
		
		// Verificamos que exista un método para el documento a tratar
		if (!in_array($identificadorDocumento, $this->validDocs)){
			throw new OwlException('No se ha definido un método para tratar el documento: ' . $identificadorDocumento, 500);
		}
		
		// Se carga el documento
		$this->loadBaseDocument();
		
	}
	
	
	/**
	 * Carga el documento a tratar
	 * @throws OwlException
	 */
	protected function loadBaseDocument(){
		
		// Se verifica si el documento a tratar existe en la base de datos
		$sql = "SELECT * FROM tblDocumento WHERE vIdentificador = '" . $this->identificadorDocumento . "'";
		$this->db->executeQuery($sql);
		
		// Si hay dos documentos con el mismo identificador, solo se tomará el primero (no se muestra error)
		if (!$doc = $this->db->fetchRow()){
			throw new OwlException('El documento dinámico <strong>' . $this->identificadorDocumento . '</strong> no existe', 500);
		}
		
		$this->docId = $doc['idDocumento'];
		
	}

	
	/**
	 * Establece la estructura para el documento con identificador S-30
	 * @param tblCurso $cursoDO
	 * @param tblPlan $planDO
	 * @param array $profesorDO
	 * @param array $alumnosCOL
	 * @param array $horariosCOL
	 * @param boolean $dosPaginas
	 */
	public function docControlAsistencia(TblCurso $cursoDO, TblPlan $planDO, TblPersona $profesorDO, $alumnosCOL, $horariosCOL, $dosPaginas = false){
		
		// Datos iniciales
		$propietarioDO = $planDO->getTblEmpresaPropietaria();
		$fileList = array();
		
		// Dos páginas
		if ($dosPaginas){
			
			// Se recarga el documento
			$this->identificadorDocumento = 'S-30-2';
			$this->loadBaseDocument();
			
			
		}
		
		// Archivo zip que contendrá todos los S-30
		$filename = 'tmp/S30-' . $cursoDO->getIdCurso() . '.zip';
		$zipFile = new ZipArchive();
		if ( file_exists($filename) ){
	   		$zipFile->open( $filename, ZIPARCHIVE::OVERWRITE );
		} else {
	   		$zipFile->open( $filename, ZIPARCHIVE::CREATE );
		}
		
		// Se generará un S-30 por cada sesión
		foreach ($horariosCOL as $horarioDO){
			
			// Se carga el documento original
			$this->pdf = new OwlPdf(PUBDIR . 'docs/doc_' . $this->docId);
	
			// Paginas
		    $this->pdf->addFieldValue('pag1', 1, 'text');
		    $this->pdf->addFieldValue('de1', 1, 'text');
		    
		    // Campos a dos páginas
		    if ($dosPaginas){
		    	
			    $this->pdf->addFieldValue('numExpediente2', '2010R64', 'text');
			    $this->pdf->addFieldValue('entidadSolicitante2', $propietarioDO->getVNombre(), 'text');
			    $this->pdf->addFieldValue('cif2', $propietarioDO->getVCif(), 'text');		    	
		    	
		    }
	
		    // Datos generales
		    $this->pdf->addFieldValue('numExpediente', $cursoDO->getVExpediente(), 'text');
		    $this->pdf->addFieldValue('entidadSolicitante', $propietarioDO->getVNombre(), 'text');
		    $this->pdf->addFieldValue('cif', $propietarioDO->getVCif(), 'text');
		    $this->pdf->addFieldValue('accionFormativa', $cursoDO->getVNombre(), 'text');
		    $this->pdf->addFieldValue('numAf', $cursoDO->getIAccion(), 'text');
		    $this->pdf->addFieldValue('numGrupo', $cursoDO->getIGrupo(), 'text');
		    $this->pdf->addFieldValue('fechaInicio', OwlDate::getDiaMesAno($cursoDO->getDInicio()), 'text');
		    $this->pdf->addFieldValue('fechaFin', OwlDate::getDiaMesAno($cursoDO->getDFin()), 'text');
		    $this->pdf->addFieldValue('responsableFormacion', $profesorDO->getVNombre() . ' ' . $profesorDO->getVPrimerApellido() . ' ' . $profesorDO->getVSegundoApellido(), 'text');
		    $this->pdf->addFieldValue('numGrupo', $cursoDO->getIGrupo(), 'text');
		    $this->pdf->addFieldValue('numSesion', $horarioDO->getISesion(), 'text');
		    $this->pdf->addFieldValue('fechaSesion', OwlDate::getDiaMesAno($horarioDO->getDDia()), 'text');
		    $this->pdf->addFieldValue('diasManyana', '', 'text');
		    $this->pdf->addFieldValue('desdeManyana', date('H:i', strtotime($horarioDO->getIDesde())), 'text');
		    $this->pdf->addFieldValue('hastaManyana', date('H:i', strtotime($horarioDO->getIHasta())), 'text');
		    $this->pdf->addFieldValue('diasTarde', '', 'text');
		    $this->pdf->addFieldValue('desdeTarde', '', 'text');
		    $this->pdf->addFieldValue('hastaTarde', '', 'text');
		    $this->pdf->addFieldValue('otroResponsable', '', 'text');
		    $this->pdf->addFieldValue('observaciones1', $cursoDO->getVObservaciones(), 'text');
		    
		    // Checks ( El cargo firmante siempre será el formador )
		    $this->pdf->addFieldValue('cargo_formador', 1, 'checkbox');
		    $this->pdf->addFieldValue('cargo_responsable', 0, 'checkbox');
		    $this->pdf->addFieldValue('cargo_otro', 0, 'checkbox');
	
		    // Alumnos
		    $x=1;
		    foreach ($alumnosCOL as $alumnoDO){
		    	
				$this->pdf->addFieldValue('apellido' . $x, $alumnoDO->getVPrimerApellido(), 'text');
		        $this->pdf->addFieldValue('segundoApellido' . $x, $alumnoDO->getVSegundoApellido(), 'text');
		        $this->pdf->addFieldValue('nombre' . $x, $alumnoDO->getVNombre(), 'text');
		        $this->pdf->addFieldValue('nif' . $x, $alumnoDO->getVNumeroIdentificacion(), 'text');
	
		        $x++;
		        $tope = $dosPaginas ? 30 : 16;
		        
		        // Temp: el documento solo admite 15 alumnos
	        	if ($x == $tope){
		    		break;
		    	}	        
		    	
		    }
		    
		    // Se escribe el archivo
		    $this->pdf->fillPdfForm();
		    
		    // Metadata del archivo generado
		    $fileName = 'S30_c' . $cursoDO->getIdCurso() . 's' . $horarioDO->getISesion() . '.pdf';
		    $fileList[] = array(
		    	'label' => 'S-30 - Sesión ' . $horarioDO->getISesion() . ' - ' . OwlDate::getDiaMesAno($horarioDO->getDDia()),
		    	'file' => $fileName
		    );
	
		    // Se compone el nombre del archivo
		    $num = $this->pdf->writeFile(PUBDIR . 'tmp/' . $fileName);

		    // Se añade el documento al archivo comprimido
	   		$zipFile->addFile('tmp/' . $fileName,  $fileName);
		    
		}		    
   		
		$zipFile->close();
		    
		// Se devuelve el array de archivos para ser pasado a la vista
	    return $fileList;
	    	    
		
	}
	
	
	/**
	 * Establece la estructura para el documento con identificador S-30 (A dos páginas, para más de 15 alumnos)
	 * @param tblCurso $cursoDO
	 * @param tblPlan $planDO
	 * @param array $profesorDO
	 * @param array $alumnosCOL
	 * @param array $horariosCOL
	 * @param boolean $dosPaginas
	 */
	public function docControlAsistencia2p(TblCurso $cursoDO, TblPlan $planDO, TblPersona $profesorDO, $alumnosCOL, $horariosCOL){
		
		return $this->docControlAsistencia($cursoDO, $planDO, $profesorDO, $alumnosCOL, $horariosCOL, true);
		
	}


	/**
	 * Establece la estructura para el documento con identificador S-20 
	 * @param TblCurso $cursoDO
	 * @param unknown_type $alumnosCOL
	 * @param TblPersona $tutorDO
	 * @param TblPlan $planDO
	 * @param array $modalidadesIDX
	 * @param TblTutoria $tutoriaDO
	 */
	public function docListadoInicialAsistentes(TblCurso $cursoDO, $alumnosCOL, TblPersona $tutorDO, TblPlan $planDO, $modalidadesIDX, TblTutoria $tutoriaDO){
		
		// Datos iniciales
		$propietarioDO = $planDO->getTblEmpresaPropietaria();
		$fileList = array();

		// Modalidad de la tutoría a distancia
		$modalidadTutoria = '';
		$fkModalidadTutoria = $tutoriaDO->getFkModalidad();
		if (array_key_exists($fkModalidadTutoria, $modalidadesIDX)){
			$modalidadTutoria = $modalidadesIDX[$fkModalidadTutoria];
		}
		
		// Se carga el documento original
		$this->pdf = new OwlPdf(PUBDIR . 'docs/doc_' . $this->docId);
	
		// Paginas
	    $this->pdf->addFieldValue('pag', 1, 'text');
	    $this->pdf->addFieldValue('de', 1, 'text');

		/**
	     * @TODO Los números de expediente estan hardcoded!
	     */	    
		
	    // Datos generales

		$this->pdf->addFieldValue('numExpediente', $cursoDO->getVExpediente(), 'text');
		$this->pdf->addFieldValue('entidadSolicitante', $propietarioDO->getVNombre(), 'text');
		$this->pdf->addFieldValue('cifEntidad', $propietarioDO->getVCif(), 'text');
		$this->pdf->addFieldValue('accionFormativa', $cursoDO->getVNombre(), 'text');
		$this->pdf->addFieldValue('numAccionFormativa', $cursoDO->getIAccion(), 'text');
		$this->pdf->addFieldValue('numGrupo', $cursoDO->getIGrupo(), 'text');
		$this->pdf->addFieldValue('fechaInicio', OwlDate::getDiaMesAno($cursoDO->getDInicio()), 'text');
		$this->pdf->addFieldValue('fechaFin', OwlDate::getDiaMesAno($cursoDO->getDFin()), 'text');
		$this->pdf->addFieldValue('profesorDistancia', $tutorDO->getVNombre() . ' ' . $tutorDO->getVPrimerApellido() . ' ' . $tutorDO->getVSegundoApellido(), 'text');
		$this->pdf->addFieldValue('nifProfesoresDistancia', $tutorDO->getVNumeroIdentificacion(), 'text');
		$this->pdf->addFieldValue('numHorasDisponibles', $tutoriaDO->getIHoras(), 'text');
		$this->pdf->addFieldValue('tiposTutorias', $modalidadTutoria, 'text');

		// Alumnos
		$x=1;
		foreach ($alumnosCOL as $alumnoDO){
			
			if ($x == 32){
				break;
			}
			
			$this->pdf->addFieldValue('nombre' . $x, $alumnoDO->getVNombre(), 'text');
			$this->pdf->addFieldValue('apellido' . $x, $alumnoDO->getVPrimerApellido(), 'text');
			$this->pdf->addFieldValue('segApellido' . $x, $alumnoDO->getVSegundoApellido(), 'text');
			$this->pdf->addFieldValue('nif' . $x, $alumnoDO->getVNumeroIdentificacion(), 'text');
			$this->pdf->addFieldValue('niss' . $x, $alumnoDO->getVNumeroSS(), 'text');
			$this->pdf->addFieldValue('sitLaboral' . $x, $alumnoDO->getTblEstadoLaboral()->getVNombre(), 'text');
			
			$x++;
			
		}

		// Nombre de archivo
	    $fileName['file'] = 'S20_c' . $cursoDO->getIdCurso() . '.pdf';
	    $fileName['label'] = 'S-20 - Listado inicial de asistentes';
			    
	    // Se escribe el archivo
	    $this->pdf->fillPdfForm();
	    $num = $this->pdf->writeFile(PUBDIR . 'tmp/' . $fileName['file']);	    
	    
	    return $fileName;
	    
	}
	
	
	/**
	 * 
	 * Establece la estructura para el documento con identificador S-10
	 * @param TblPlan $planDO
	 * @param TblCurso $cursoDO
	 * @param array $modalidadesIDX
	 * @param TblEmpresa $academiaDO
	 * @param array $horariosCOL
	 * @param array $tutoriaDO
	 */
	public function docInicioAccionFormativa(TblPlan $planDO, TblCurso $cursoDO, $modalidadesIDX, TblEmpresa $academiaDO, $horariosCOL, $tutoriaDO){
		
		$propietarioDO = $planDO->getTblEmpresaPropietaria();
		$consultoraDO = $planDO->getTblEmpresaConsultora();
		$diasFormacionARR = $this->_getDiasFormacion($horariosCOL);
		$horariosGeneralesARR = $this->_getHorariosGenerales($horariosCOL);
		
		// Se carga el documento original
		$this->pdf = new OwlPdf(PUBDIR . 'docs/doc_' . $this->docId);
		
		// Paginas
	    $this->pdf->addFieldValue('pag', 1, 'text');
	    $this->pdf->addFieldValue('de', 1, 'text');		
		
		// Datos consultora
		$this->pdf->addFieldValue('numExpediente', $cursoDO->getVExpediente(), 'text');
		$this->pdf->addFieldValue('nomEntidad', $propietarioDO->getVNombre(), 'text');
		$this->pdf->addFieldValue('cifEntidad', $propietarioDO->getVCif(), 'text');
		
		// Datos Curso
		$this->pdf->addFieldValue('numAccion', $cursoDO->getIAccion(), 'text');
		$this->pdf->addFieldValue('numGrupo', $cursoDO->getIGrupo(), 'text');
		$this->pdf->addFieldValue('nombreCurso', $cursoDO->getVNombre(), 'text');
		$this->pdf->addFieldValue('modalidad', $modalidadesIDX[$cursoDO->getFkModalidad()], 'text');
		$this->pdf->addFieldValue('numParticipantes', $cursoDO->getINumeroAlumnos(), 'text');
		
		// Horas Totales
		$horasPresenciales = $cursoDO->getIHorasPresenciales();
		$horasDistancia = $cursoDO->getIHorasDistancia();
		$totalHoras = $horasPresenciales + $horasDistancia;
		
		$this->pdf->addFieldValue('horasTotales', $totalHoras);
		$this->pdf->addFieldValue('fechaInicio', OwlDate::getDiaMesAno($cursoDO->getDInicio()));
		$this->pdf->addFieldValue('fechaFin', OwlDate::getDiaMesAno($cursoDO->getDFin()));
		
		
		// FORMACIÓN PRESENCIAL	
		if ($horasPresenciales != 0){
			
			$this->pdf->addFieldValue('fp_nombreComercial', $academiaDO->getVNombre());
			$this->pdf->addFieldValue('fp_Cif', $academiaDO->getVCif());
			$this->pdf->addFieldValue('fp_Localidad', $academiaDO->getVPoblacion());
			$this->pdf->addFieldValue('fp_Cp', $academiaDO->getVCp());
			$this->pdf->addFieldValue('fp_Direccion', $academiaDO->getVDireccion());
			$this->pdf->addFieldValue('fp_NumHoras', $horasPresenciales);
			
			$this->pdf->addFieldValue('fd_lunes', in_array('Monday', $diasFormacionARR), 'checkbox');
			$this->pdf->addFieldValue('fd_martes', in_array('Tuesday', $diasFormacionARR), 'checkbox');
			$this->pdf->addFieldValue('fd_miercoles', in_array('Wednesday', $diasFormacionARR), 'checkbox');
			$this->pdf->addFieldValue('fd_jueves', in_array('Thursday', $diasFormacionARR), 'checkbox');
			$this->pdf->addFieldValue('fd_viernes', in_array('Friday', $diasFormacionARR), 'checkbox');
			$this->pdf->addFieldValue('fd_sabado', in_array('Saturday', $diasFormacionARR), 'checkbox');
			$this->pdf->addFieldValue('fd_domingo', in_array('Sunday', $diasFormacionARR), 'checkbox');


			// Horarios
			$deMan = $aMan = $deTar = $aTar = null;
			if (array_key_exists('man', $horariosGeneralesARR) && is_array($horariosGeneralesARR['man'])){
				$deMan = $horariosGeneralesARR['man']['de'];
				$aMan = $horariosGeneralesARR['man']['hasta'];
			}
			if (array_key_exists('tar', $horariosGeneralesARR) && is_array($horariosGeneralesARR['tar'])){
				$deTar = $horariosGeneralesARR['tar']['de'];
				$aTar = $horariosGeneralesARR['tar']['hasta'];
			}
			
			$this->pdf->addFieldValue('fp_horario_man_de', date('H:i', strtotime($deMan)));
			$this->pdf->addFieldValue('fp_horario_man_a', date('H:i', strtotime($aMan)));
			$this->pdf->addFieldValue('fp_horario_tar_de', date('H:i', strtotime($deTar)));
			$this->pdf->addFieldValue('fp_horario_tar_a', date('H:i', strtotime($aTar)));			
			
			$this->pdf->addFieldValue('fp_nombre_contacto', $academiaDO->getVPersonaContacto());
			$this->pdf->addFieldValue('fp_nif_contacto', $academiaDO->getVTelefono());
			
		}
		
		// FORMACIÓN DISTANCIA
		if ($horasDistancia != 0){
			
			$this->pdf->addFieldValue('fd_nombreComercial', $academiaDO->getVNombre());
			$this->pdf->addFieldValue('fd_Cif', $academiaDO->getVCif());
			$this->pdf->addFieldValue('fd_Localidad', $academiaDO->getVPoblacion());
			$this->pdf->addFieldValue('fd_Cp', $academiaDO->getVCp());
			$this->pdf->addFieldValue('fd_Direccion', $academiaDO->getVDireccion());
			$this->pdf->addFieldValue('fd_NumHoras', $horasPresenciales);
			$this->pdf->addFieldValue('fd_lunes', in_array('Monday', $diasFormacionARR), 'checkbox');
			$this->pdf->addFieldValue('fd_martes', in_array('Tuesday', $diasFormacionARR), 'checkbox');
			$this->pdf->addFieldValue('fd_miercoles', in_array('Wednesday', $diasFormacionARR), 'checkbox');
			$this->pdf->addFieldValue('fd_jueves', in_array('Thursday', $diasFormacionARR), 'checkbox');
			$this->pdf->addFieldValue('fd_viernes', in_array('Friday', $diasFormacionARR), 'checkbox');
			$this->pdf->addFieldValue('fd_sabado', in_array('Saturday', $diasFormacionARR), 'checkbox');
			$this->pdf->addFieldValue('fd_domingo', in_array('Sunday', $diasFormacionARR), 'checkbox');
			
			// Horarios
			$deMan = $aMan = $deTar = $aTar = null;
			if (array_key_exists('man', $horariosGeneralesARR) && is_array($horariosGeneralesARR['man'])){
				$deMan = $horariosGeneralesARR['man']['de'];
				$aMan = $horariosGeneralesARR['man']['hasta'];
			}
			if (array_key_exists('tar', $horariosGeneralesARR) && is_array($horariosGeneralesARR['tar'])){
				$deTar = $horariosGeneralesARR['tar']['de'];
				$aTar = $horariosGeneralesARR['tar']['hasta'];
			}
			
			$this->pdf->addFieldValue('fd_horario_man_de', date('H:i', strtotime($deMan)));
			$this->pdf->addFieldValue('fd_horario_man_a', date('H:i', strtotime($aMan)));
			$this->pdf->addFieldValue('fd_horario_tar_de', date('H:i', strtotime($deTar)));
			$this->pdf->addFieldValue('fd_horario_tar_a', date('H:i', strtotime($aTar)));
			
			$this->pdf->addFieldValue('fd_nombre_contacto', $academiaDO->getVPersonaContacto());
			$this->pdf->addFieldValue('fd_nif_contacto', $academiaDO->getVTelefono());			
			
		}
		
		// TUTORIA
		if ($tutoriaDO instanceof TblTutoria){
			
			$tutorDO = $tutoriaDO->getTblPersona();
			$pref = 'td_';
			
			// Modalidad de la tutoría
			if ($tutoriaDO->getFkModalidad() == PplCacheBO::CLAVE_MODALIDAD_PRESENCIAL){
				$pref = 'tp_';
			}
			
			$this->pdf->addFieldValue($pref . 'nombreComercial', $consultoraDO->getVNombre());
			$this->pdf->addFieldValue($pref . 'Cif', $consultoraDO->getVCif());
			$this->pdf->addFieldValue($pref . 'Localidad', $consultoraDO->getVPoblacion());
			$this->pdf->addFieldValue($pref . 'Cp', $consultoraDO->getVCp());
			$this->pdf->addFieldValue($pref . 'Direccion', $consultoraDO->getVDireccion());
			$this->pdf->addFieldValue($pref . 'NumHoras', $horasPresenciales);
			
			$this->pdf->addFieldValue($pref . 'lunes', $tutoriaDO->isBLunes(), 'checkbox');
			$this->pdf->addFieldValue($pref . 'martes', $tutoriaDO->isBMartes(), 'checkbox');
			$this->pdf->addFieldValue($pref . 'miercoles', $tutoriaDO->isBMiercoles(), 'checkbox');
			$this->pdf->addFieldValue($pref . 'jueves', $tutoriaDO->isBJueves(), 'checkbox');
			$this->pdf->addFieldValue($pref . 'viernes', $tutoriaDO->isBViernes(), 'checkbox');
			$this->pdf->addFieldValue($pref . 'sabado', $tutoriaDO->isBSabado(), 'checkbox');
			$this->pdf->addFieldValue($pref . 'domingo', $tutoriaDO->isBDomingo(), 'checkbox');
			
			// Horarios
			$deMan = $aMan = $deTar = $aTar = null;
			if (array_key_exists('man', $horariosGeneralesARR) && is_array($horariosGeneralesARR['man'])){
				$deMan = $horariosGeneralesARR['man']['de'];
				$aMan = $horariosGeneralesARR['man']['hasta'];
			}
			if (array_key_exists('tar', $horariosGeneralesARR) && is_array($horariosGeneralesARR['tar'])){
				$deTar = $horariosGeneralesARR['tar']['de'];
				$aTar = $horariosGeneralesARR['tar']['hasta'];
			}
			
			$this->pdf->addFieldValue($pref . 'horario_man_de', date('H:i', strtotime($tutoriaDO->getIDesdeManana())));
			$this->pdf->addFieldValue($pref . 'horario_man_a', date('H:i', strtotime($tutoriaDO->getIHastaManana())));
			$this->pdf->addFieldValue($pref . 'horario_tar_de', date('H:i', strtotime($tutoriaDO->getIDesdeTarde())));
			$this->pdf->addFieldValue($pref . 'horario_tar_a', date('H:i', strtotime($tutoriaDO->getIHastaTarde())));
			
			$this->pdf->addFieldValue($pref . 'nombre_contacto', $consultoraDO->getVPersonaContacto());
			$this->pdf->addFieldValue($pref . 'nif_contacto', $consultoraDO->getVTelefono());						
			
			
		}
		
		$this->pdf->addFieldValue('observaciones', $cursoDO->getVObservaciones());
		
		
		// Nombre de archivo
	    $fileName['file'] = 'S10_c' . $cursoDO->getIdCurso() . '.pdf';
	    $fileName['label'] = 'S-10 - Inicio de acción formativa';
			    
	    // Se escribe el archivo
	    $this->pdf->fillPdfForm();
	    $num = $this->pdf->writeFile(PUBDIR . 'tmp/' . $fileName['file']);	    
	    
	    return $fileName;		
		
	}
	
	
	/**
	 * Devuelve un array con los nombre de días de la semana en inglés, en los que 
	 * hay fechas existentes en $horariosCOL
	 * 
	 * @param array $horariosCOL
	 */
	private function _getDiasFormacion($horariosCOL){
		
		$diasARR = array();
		
		foreach ($horariosCOL as $horarioDO){
			
			$dia = date('l', strtotime($horarioDO->getDDia()));
			
			if (!in_array($dia, $diasARR)){
				array_push($diasARR, $dia);
			}
			
		}
		
		return $diasARR;
		
	}
	
	
	/**
	 * 
	 * Devuelve los horarios de mañana y tarde generales de una lista de horarios.
	 * Será tomado como horario general el que mas se repita en cada turno.
	 * Si un turno solo tiene un horario (día particular) éste será devuelto como horario general del turno.
	 * 
	 * @param array $horariosCOL
	 * @return array
	 */
	private function _getHorariosGenerales($horariosCOL){

		$mediodia = '14:59:59';
		$horMan = array();
		$horTarde = array(); 
		
		foreach ($horariosCOL as $horarioDO){
			
			$desde = $horarioDO->getIDesde();
			$hasta = $horarioDO->getIHasta();
			
			// Horarios de mañana
			if ($desde < $mediodia){
				array_push($horMan, $desde . '-' . $hasta);
			} else {
				array_push($horTarde, $desde . '-' . $hasta);
			}
			
		}

		$horarioMan = $this->_getHorarioMasRepetido($horMan);
		$horarioTar = $this->_getHorarioMasRepetido($horTarde);
		
		return array('man'=>$horarioMan, 'tar'=>$horarioTar);
		
	}
	
	
	/**
	 * Método que devuelve el horario mas repetido de un array
	 * @param array $horariosARR
	 * @return array
	 */
	private function _getHorarioMasRepetido($horariosARR){
		
		$stack = array();
		foreach ($horariosARR as $horario){
			if (array_key_exists($horario, $stack)){
				$stack[$horario]++;
			} else {
				$stack[$horario] = 1;
			}
		}
		
		$maxRep = 0;
		$theOne = null;
		foreach ($stack as $horario => $repeticiones){
			if ($repeticiones > $maxRep){
				$theOne = $horario;
			}
		}
		
		if (is_null($theOne)){
			return null;
		}
		
		list($de, $hasta) = explode('-', $theOne);
		
		return array('de'=>$de, 'hasta'=>$hasta );
		
	}
	
	
}

?>
