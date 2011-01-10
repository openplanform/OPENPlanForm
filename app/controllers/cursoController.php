<?php

require_once 'helper/OwlHtmlHelper.inc';
require_once 'helper/OwlDate.inc';
require_once 'helper/OwlString.inc';
require_once 'helper/OwlLanguage.inc';
require_once 'OwlPaginator.inc';

require_once CLASSESDIR . 'PplController.inc';
require_once CLASSESDIR . 'PplDocumentacion.inc';

require_once MODELDIR . '/TblAlumno.inc';
require_once MODELDIR . '/TblCentro.inc';
require_once MODELDIR . '/TblCategoria.inc';
require_once MODELDIR . '/TblCategoria.inc';
require_once MODELDIR . '/TblCategoriaExtendida.inc';
require_once MODELDIR . '/TblColectivo.inc';
require_once MODELDIR . '/TblCurso.inc';
require_once MODELDIR . '/TblEstadoCivil.inc';
require_once MODELDIR . '/TblHorario.inc';
require_once MODELDIR . '/TblModalidad.inc';
require_once MODELDIR . '/TblSector.inc';
require_once MODELDIR . '/TblTutoria.inc';
require_once MODELDIR . '/TblPlan.inc';
require_once MODELDIR . '/TrelCandidato.inc';
require_once MODELDIR . '/TrelPrecandidato.inc';
require_once MODELDIR . '/TrelProfesor.inc';
require_once MODELDIR . '/TblTutoria.inc';


class cursoController extends PplController{
    
    /**
     * Colección de categorias
     * @var array
     */
    protected $categoriasCOL = null;
    
    
    /**
     * Init
     * @see extranet.planespime.es/owl/lib/OwlController::initController()
     */
    public function initController(){

    	parent::initController();
        
    }
    
    
    /**
     * Acción inicial, por defecto, el listado
     * @see extranet.planespime.es/owl/lib/OwlController::indexAction()
     */
    public function indexAction(){
    	
    	// Parámetros de ordenación para el paginador
    	$aliasCampos = array(
    		'cat'	=> 'fkCategoria',
    		'fin'	=> 'dFin',
    		'ini'	=> 'dInicio',
    		'nom' 	=> 'vNombre',
    		'plan'	=> 'fkPlan',
    	);
    	
        if ( !empty($_REQUEST) && array_key_exists('o', $_GET) & array_key_exists('ob', $_GET) ){
        	$order = $this->helper->escapeInjection($_GET['o']);
        	$orderBy = $aliasCampos[$_GET['ob']];
        	$aliasOrderBy = $_GET['ob'];
        } else {
    		$order	 = 'asc';
    		$orderBy = 'vNombre';
    		$aliasOrderBy = 'nom';
        }
        
        // Envío el orden a la vista
        if ( $order == 'asc' ){
        	$this->view->order = 'desc';
        } else {
        	$this->view->order = 'asc';
        }
        $this->view->orderBy = $aliasOrderBy;
        
    	// Se instancia y configura el paginador
        $paginador = new OwlPaginator($this->db, null, 'tblCurso', $this->helper);
        $paginador->setItemsPorPagina(20);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo los cursos
        $cursosCOL = $paginador->getItemCollection();
        
        // Envío el paginador a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío los cursos a la vista
        $this->view->cursosCOL = $cursosCOL;
        
         // Planes
        $this->view->planesIDX = $this->cacheBO->getPlanes();
        
        // Categorías
        $this->view->categoriasIDX = $this->cacheBO->getCategorias();
        
        // Permiso para editar
    	if ( $this->aclManager->hasPerms('curso', 'editar') ){
    		$this->view->editar = true;
    	}
        
    }
    
    
    /**
     * Acción de alta
     * Da de alta un curso
     */
    public function altaAction(){
        
        // Planes
        $this->view->planesIDX = $this->cacheBO->getPlanes();
        
        // Select Categorías
        $arbolDS = array();
        $arbolDS = $this->_IteraCategorias($arbolDS, 0);
        $this->view->htmlSelectCategorias = $this->_getSelectHtml($arbolDS, 0, 0);
        
        // Colectivos
        $this->view->colectivosIDX = $this->cacheBO->getColectivos();
        
        // Modalidades
        $this->view->modalidadesIDX = $this->cacheBO->getModalidades();
        
        // Centros
        $this->view->centrosIDX = $this->cacheBO->getCentros();
        
        // Profesores
        $this->view->profesoresIDX = $this->cacheBO->getProfesores();
        
        // Categorías
        $this->view->categoriasIDX = $this->cacheBO->getCategorias();
        
        // Categorías de profesores
        $this->view->categoriasProfesoresIDX = $this->cacheBO->getProfesoresCategorias();
        
   		// Doy de alta el curso
    	if ( $this->helper->get('send') ){
    		
   			if ( $this->actualizarInsertar() ){
   				
   				// Todo ha ido bien
    			$this->redirectTo('curso', 'index');
					
   			} else {

   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con el alta del curso. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
					
   			}
    	}
        
    }
    
    
	/**
     * Acción de edición
     * Edita un curso
     */
    public function editarAction(){
        
   	 	// Obtengo el curso que voy a editar
    	$idCurso = $this->getParam(0);
        if ( !is_null($idCurso) ){
        	
        	// Curso
            if (!$cursoDO = TblCurso::findByPrimaryKey($this->db, $idCurso)){
                $this->redirectTo('curso', 'index');
                return;
            }
            
        	$duplicar = false;
        	
        } else {
        	
        	if ( OwlSession::getValue('cursoDuplicado') instanceof TblCurso ){
        		
        		$cursoDO = OwlSession::getValue('cursoDuplicado');
        		$duplicar = true;
        		
        	}
        	
        }
    	
        // Actualizo el curso
        if ( isset($cursoDO) && $this->helper->get('send') ){
        	
        	if ( $duplicar ){
    			$correcto = $this->actualizarInsertar();
    		} else {
    			$correcto = $this->actualizarInsertar(true, $cursoDO->getIdCurso());
    		}
    		
            if ( $correcto ){
                    
            	// Curso
            	if ( $duplicar ){
                	$this->redirectTo('curso','editar', $this->db->getLastInsertId());
            	} else {
                	$cursoDO = TblCurso::findByPrimaryKey($this->db, $cursoDO->getIdCurso());
            	}
                $this->view->cursoDO = $cursoDO;
                    
			} else {
                    
            	$this->view->popup = array(
                	'estado' => 'ko',
                	'titulo' => 'Error',
                    'mensaje'=> 'Ha ocurrido un error con la edición del curso. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                    'url'=> '',
                );
                    
            }
       }
       
       // Datos para la vista
       if ( isset($cursoDO) ){
       	
       		$this->view->cursoDO = $cursoDO;
       	
        	// Planes
	        $this->view->planesIDX = $this->cacheBO->getPlanes();
	        
	        // Select Categorías
	        $arbolDS = array();
	        $arbolDS = $this->_IteraCategorias($arbolDS, 0);
	        $this->view->htmlSelectCategorias = $this->_getSelectHtml($arbolDS, 0, $cursoDO->getFkCategoria());
	        
	        // Colectivos
	        $this->view->colectivosIDX = $this->cacheBO->getColectivos();
	        
	        // Modalidades
	        $this->view->modalidadesIDX = $this->cacheBO->getModalidades();
	        
	        // Centros
	        $this->view->centrosIDX = $this->cacheBO->getCentros();
	    	
	        // Profesores curso
	        $this->view->profesoresCursoCOL = TrelProfesor::findByTblCurso($this->db, $cursoDO->getIdCurso());
	        
	        // Profesores
	        $this->view->profesoresIDX = $this->cacheBO->getProfesores();
	        
	        // Categorías
	        $this->view->categoriasIDX = $this->cacheBO->getCategorias();
	        
	        // Categorías de profesores
	        $this->view->categoriasProfesoresIDX = $this->cacheBO->getProfesoresCategorias();
	        
	        // Personas
	        $this->view->personasIDX = $this->cacheBO->getPersonas();
	        
	        // Tutoría
	        $this->view->tutoriaDO = $this->cacheBO->getTutoriaCurso($idCurso);
	        
        }

    }
    
    
	/**
     * Acción de ficha
     * Ficha de un curso
     */
    public function fichaAction(){
        
    	$idCurso = $this->getParam(0);
        if ( !is_null($idCurso) ){
        	
        	$cursoDO = TblCurso::findByPrimaryKey($this->db, $idCurso);
        	
        	if ( !empty($cursoDO) ){
	        	
        		$this->view->cursoDO = $cursoDO;
	        	
	        	// Categoría del curso
	        	$this->view->categoriaDO = TblCategoriaExtendida::findByPrimaryKeyId($this->db, $cursoDO->getFkCategoria());
	        	
	        	// Profesores curso
		        $this->view->profesoresCursoCOL = TrelProfesor::findByTblCurso($this->db, $cursoDO->getIdCurso());
		        
		        // Profesores
		        $this->view->profesoresIDX = $this->cacheBO->getProfesores();
		        
  		        // Personas
		        $this->view->personasIDX = $this->cacheBO->getPersonas();
		        
		        // Precandidatos
		        $this->view->precandidatosCursoCOL = TrelPrecandidato::findByTblCurso($this->db, $cursoDO->getIdCurso());
		        
		        // Candidatos
		    	$this->view->candidatosCursoCOL = TrelCandidato::findByTblCurso($this->db, $cursoDO->getIdCurso());
		    	
		    	// Alumnos
		    	$this->view->alumnosCursoCOL = TblAlumno::findByTblCurso($this->db, $cursoDO->getIdCurso());
		    	
		    	// Modalidades
		    	$this->view->modalidadesIDX = $this->cacheBO->getModalidades();

        	}
        	
        }
        
    }
    
    
	/**
     * Acción de eliminar
     * Elimina un curso
     */
    public function eliminarAction(){
        
    	$idCurso = $this->getParam(0);
        if ( !is_null($idCurso) ){
        	
        	$cursoDO = TblCurso::findByPrimaryKey($this->db, $idCurso);
        	$cursoDO->delete();
        	
        }
        
        $this->redirectTo('curso','index');
        
    }
    
    
	/**
     * Acción de duplicar
     * Duplica un curso
     */
    public function duplicarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$cursoDO = TblCurso::findByPrimaryKey($this->db, $paramsARR[0]);
        	$nombreCurso = 'Copia de ' . $cursoDO->getVNombre();
        	$cursoDO->setVNombre($nombreCurso);
//        	$cursoDO->insert();
        	OwlSession::setValue('cursoDuplicado', $cursoDO);
        }
        
//        $this->redirectTo('curso','editar', $this->db->getLastInsertId());
        $this->redirectTo('curso','editar');
        
    }
    
    
    /**
     * Función recursiva para tratar las categorias
     * @param array $arrayDS
     * @param integer $clavePadre
     * @param integer $nivel
     */
    private function _IteraCategorias($arrayDS, $clavePadre){
        
        if (is_null($this->categoriasCOL)){
    	   $this->categoriasCOL = TblCategoria::findAll($this->db, 'idCategoria ASC');
        }
    	
        foreach ($this->categoriasCOL as $categoriaDO){
            
            if ($categoriaDO->getFkPadre() == $clavePadre){
                $arrayDS[$categoriaDO->getIdCategoria()]['nombre'] = $categoriaDO->getVNombre();
                $arrayDS[$categoriaDO->getIdCategoria()]['DO'] = $categoriaDO;
                $arrayDS[$categoriaDO->getIdCategoria()]['hijos'] = array();
                $arrayDS[$categoriaDO->getIdCategoria()]['hijos'] = $this->_IteraCategorias($arrayDS[$categoriaDO->getIdCategoria()]['hijos'], $categoriaDO->getIdCategoria());
            }
            
        }
        
        return $arrayDS;
        
    }
    
    
    /**
     * 
     * prepara el código html para el árbol de categoria
     * @param array $arbolDS
     */
    private function _getSelectHtml($arbolDS, $nivel, $selected = ''){
        
        $nivel++;
        $html = '';
        
        foreach ($arbolDS as $clave => $arbol){

            if (count($arbol['hijos'])){
            	$html .= '<optgroup label="' . $arbol['nombre'] . '">';
                $html .= $this->_getSelectHtml($arbol['hijos'], $nivel, $selected);
                $html .= '</optgroup>';
            } else {
            	$sel = ($clave == $selected) ? 'selected="selected"' : '';
            	$html .= '<option value="' . $clave .'" ' . $sel . '>' . str_ireplace('_', '', $arbol['nombre']) . '</option>';
            }
            
        }
        
        return $html;
        
    }
    
    
    /**
     * Obtiene los datos de curso y realiza el alta o la actualización
     * @param boolean $editar
     * @param intenger $idCurso
     * @return boolean $correcto
     */
    public function actualizarInsertar($editar = false, $idCurso = '') {
    	
	    $correcto = true;
	    		
     	// Comprobaciones pertinentes
     	
        // Nombre
    	$nombre = $this->helper->escapeInjection($this->helper->get('nombre'));
	    if ( is_null($nombre) || empty($nombre) ){
	    	$correcto = false;
	    	$this->view->errorNombre = 'El nombre no puede estar vacío';
	    }
        
	    // Plan
    	$plan = $this->helper->escapeInjection($this->helper->get('plan'));
	    if ( is_null($plan) || empty($plan) ){
	    	$correcto = false;
	    	$this->view->errorPlan = 'El plan no puede estar vacío';
	    }
	    
	    // Expediente
	    $expediente = $this->helper->getAndEscape('expediente');
	    
	    // Categoría
    	$categoria = $this->helper->escapeInjection($this->helper->get('categoria'));
	    if ( is_null($categoria) || empty($categoria) ){
	    	$correcto = false;
	    	$this->view->errorCategoria = 'La categoria no puede estar vacía';
	    }
	    
	    // Colectivo
    	$colectivo = $this->helper->escapeInjection($this->helper->get('colectivo'));
	    if ( is_null($colectivo) || empty($colectivo) ){
	    	$correcto = false;
	    	$this->view->errorColectivo = 'El colectivo no puede estar vacío';
	    }
    	// Modalidad
    	$modalidad = $this->helper->escapeInjection($this->helper->get('modalidad'));
	    if ( is_null($modalidad) || empty($modalidad) ){
	    	$correcto = false;
	    	$this->view->errorModalidad = 'La modalidad no puede estar vacía';
	    }
	    
	    // Centro
    	$centro = $this->helper->escapeInjection($this->helper->get('centro'));
	    if ( is_null($centro) || empty($centro) ){
	    	$correcto = false;
	    	$this->view->errorCentro = 'El centro no puede estar vacío';
	    }
	    
	     // Horas presenciales
    	$horasP = $this->helper->escapeInjection($this->helper->get('horasP'));
	    if ( is_null($horasP) || empty($horasP) ){
	    	$horasP = "";
	    }
	    
	     // Horas a distacia
    	$horasD = $this->helper->escapeInjection($this->helper->get('horasD'));
	    if ( is_null($horasD) || empty($horasD) ){
	    	$horasD = "";
	    }
	    
    	// alumnos
    	$alumnos = $this->helper->escapeInjection($this->helper->get('numAlumnos'));
	    if ( is_null($alumnos) || empty($alumnos) ){
	    	$alumnos = "";
	    }
	    
	    // Acción
    	$accion = $this->helper->escapeInjection($this->helper->get('accion'));
	    if ( is_null($accion) || empty($accion) ){
	    	$accion = "";
	    }
	    
	    // Inicio
    	$inicio = $this->helper->escapeInjection($this->helper->get('inicio'));
	    if ( is_null($inicio) || empty($inicio) ){
	    	$inicio = "";
	    }
	    
	    // Fin
    	$fin = $this->helper->escapeInjection($this->helper->get('fin'));
	    if ( is_null($fin) || empty($fin) ){
	    	$fin = "";
	    }
	    
	    // Comparar fechas
	    if ( !empty($inicio) && !empty($fin) ){
	    	
	    	$strInicio = strtotime(OwlDate::europeoAmericano($inicio));
	    	$strFin = strtotime(OwlDate::europeoAmericano($fin));
	    	if ( $strInicio > $strFin ){
	    		$this->view->errorFecha = "Fecha incorrecta";
	    		$correcto = false;
	    	}
	    	
	    }
	    
    	// Descripción
    	$descripcion = $this->helper->escapeInjection($this->helper->get('descripcion'));
	    if ( is_null($descripcion) || empty($descripcion) ){
	    	$descripcion = "";
	    }
	    
    	// Observaciones
    	$observaciones = $this->helper->escapeInjection($this->helper->get('observaciones'));
	    if ( is_null($observaciones) || empty($observaciones) ){
	    	$observaciones = "";
	    }
	    
	    // Profesores
    	$profesoresARR = array();
        if ( array_key_exists('profesores', $_POST) ){
        	foreach ($_POST['profesores'] as $profesor) {
            	$profesoresARR[] = $this->helper->escapeInjection($profesor);
            }
        }
        
        // Datos de tutoría
        $idTutoria = $this->helper->getAndEscape('tutoria');
        $fkTutor = $this->helper->getAndEscape('tutor');
        $horasTutoria = $this->helper->getAndEscape('horasT');
        $fkModalidadTutoria = $this->helper->getAndEscape('modalidadTutoria');
        $lunes = $this->helper->getAndEscape('lunes') == 'on';
        $martes = $this->helper->getAndEscape('martes') == 'on';
        $miercoles = $this->helper->getAndEscape('miercoles') == 'on';
        $jueves = $this->helper->getAndEscape('jueves') == 'on';
        $viernes = $this->helper->getAndEscape('viernes') == 'on';
        $sabado = $this->helper->getAndEscape('sabado') == 'on';
        $domingo = $this->helper->getAndEscape('domingo') == 'on';
        $deMan = $this->helper->getAndEscape('de_man');
        $aMan = $this->helper->getAndEscape('a_man');
        $deTar = $this->helper->getAndEscape('de_tar');
        $aTar = $this->helper->getAndEscape('a_tar');
       
		/**
		 * Insertamos o actualizamos un curso
		 */
	    if ( $correcto ){
	    	
	    	// Empieza la transacción
		    $this->db->begin();
		    
		    // Desactivaremos la comprobación de claves foráneas
		    $this->db->disableForeignChecks();
	    	
	    	// Insertamos o actualizamos un curso
	    	if ( $correcto ){
	    	
		    	if ( $editar ){
		    		$cursoDO = TblCurso::findByPrimaryKey($this->db, $idCurso);
		    	} else {
		    		$cursoDO = new TblCurso($this->db);
		    	}
		    	
		    	$cursoDO->setVNombre($nombre);
		    	$cursoDO->setFkPlan($plan);
		    	$cursoDO->setFkCategoria($categoria);
		    	$cursoDO->setFkColectivo($colectivo);
		    	$cursoDO->setFkModalidad($modalidad);
		    	$cursoDO->setFkCentro($centro);
		    	$cursoDO->setIHorasPresenciales($horasP);
		    	$cursoDO->setIHorasDistancia($horasD);
		    	$cursoDO->setDInicio(OwlDate::europeoAmericano($inicio));
		    	$cursoDO->setDFin(OwlDate::europeoAmericano($fin));
		    	$cursoDO->setVDescripcion($descripcion);
		    	$cursoDO->setVObservaciones($observaciones);
		    	$cursoDO->setINumeroAlumnos($alumnos);
		    	$cursoDO->setIAccion($accion);
		    	$cursoDO->setLastModified(date('Y-m-d'));
		    	$cursoDO->setVExpediente($expediente);
                $cursoDO->setModUser($this->usuario->getNombre());
		    	
		    	if ( $editar ){
		    		$correcto = $cursoDO->update();
		    	} else {
		    		$correcto = $cursoDO->insert();
		    		$idCurso = $this->db->getLastInsertId();
		    	}
		    	
	    	}
	    	
	    	// Se vuelve a activar la comprobación de claves foráneas
	    	$this->db->enableForeignChecks();
	    	
	    	// Tutorías
	    	if ( $correcto ){
	    		
	    	    if (!empty($fkTutor) && !empty($horasTutoria) && !empty($fkModalidadTutoria)){
        	
	    	    	if (!empty($idTutoria)){
	    	    		// El curso ya tiene asignada una turoría
	    	    		$tutoriaDO = TblTutoria::findByPrimaryKey($this->db, $idTutoria);
	    	    	} else {
	    	    		$tutoriaDO = new TblTutoria($this->db);
	    	    	}
        			
        			$tutoriaDO->setFkCurso($cursoDO->getIdCurso());
        			$tutoriaDO->setFkModalidad($fkModalidadTutoria);
        			$tutoriaDO->setFkTutor($fkTutor);
        			$tutoriaDO->setIHoras($horasTutoria);
        			$tutoriaDO->setBLunes($lunes);
        			$tutoriaDO->setBMartes($martes);
        			$tutoriaDO->setBMiercoles($miercoles);
        			$tutoriaDO->setBJueves($jueves);
        			$tutoriaDO->setBViernes($viernes);
        			$tutoriaDO->setBSabado($sabado);
        			$tutoriaDO->setBDomingo($domingo);
        			$tutoriaDO->setIDesdeManana($deMan);
        			$tutoriaDO->setIDesdeTarde($deTar);
        			$tutoriaDO->setIHastaManana($aMan);
        			$tutoriaDO->setIHastaTarde($aTar);
        			
        			if ( !empty($idTutoria) ){
        				$correcto = $tutoriaDO->update();
        			} else {
        				$correcto = $tutoriaDO->insert();
        			}
        			
	    	    }
	    	    
	    	}
	    	
	    	// Profesores del curso. Si estoy editando, borro todos los profesores para insertar los nuevos
	    	if ( $correcto ){
	    		
	    		if ( $editar ){
	    			$sql = 'DELETE FROM trelProfesor WHERE fkCurso = ' . $idCurso;
	    			if ( !$this->db->executeQuery($sql) ){
	    				$correcto = false;
	    			}
	    		}
	    		
	    		if ( $correcto ){
		    		foreach ( $profesoresARR as $idProfesor ){
		    			$sql = 'INSERT INTO trelProfesor VALUES (' . $idProfesor . ',' . $idCurso . ')';
		    			if ( !$this->db->executeQuery($sql) ){
		    				$correcto = false;
		    			}
		    		}
	    		}
	    		
	    	}
	    	
    		if ( $correcto ){
    			// Todo ha ido bien
    			$this->db->commit();
    		} else {
    			$this->db->rollback();
    		}
	    	
	    }
	    	
	    return $correcto;
    	
    }
    
    
    /**
     * Buscar cursos
     */
    public function buscarAction(){
        
        // Se obtiene los planes
        $this->view->planesIDX = $this->cacheBO->getPlanes();
        
        // Categorías
        $arbolDS = array();
        $arbolDS = $this->_IteraCategorias($arbolDS, 0);
        $this->view->htmlSelectCategorias = $this->_getSelectHtml($arbolDS, 0, 0);
        $this->view->categoriasIDX = $this->cacheBO->getCategorias();
        
        // Colectivos
        $this->view->colectivosIDX = $this->cacheBO->getColectivos();
        
        // Modalidades
        $this->view->modalidadesIDX = $this->cacheBO->getModalidades();
        
        
        $sent = $this->helper->getAndEscape('sent');
        if (!empty($sent)){

            // Solo comprobaremos permisos de edición si hay resultados
            if ( $this->aclManager->hasPerms('curso', 'editar') ){
                $this->view->editar = true;
            }
            
            // Parámetros de ordenación para el paginador
            $aliasCampos = array(
                'cat'   => 'fkCategoria',
                'fin'   => 'dFin',
                'ini'   => 'dInicio',
                'nom'   => 'vNombre',
                'plan'  => 'fkPlan',
            );
            

            if ( !empty($_REQUEST) && array_key_exists('o', $_GET) && array_key_exists('ob', $_GET) ){
                $order = $this->helper->escapeInjection($_GET['o']);
                $orderBy = $aliasCampos[$_GET['ob']];
                $aliasOrderBy = $_GET['ob'];
            } else {
                $order   = 'asc';
                $orderBy = 'vNombre';
                $aliasOrderBy = 'nom';
            }            

            // Envío el orden a la vista
            if ( $order == 'asc' ){
                $this->view->order = 'desc';
            } else {
                $this->view->order = 'asc';
            }
            $this->view->orderBy = $aliasOrderBy;            
            
            // Se prepara el query
            $id = $this->helper->getAndEscape('idCurso');
            $plan = $this->helper->getAndEscape('idPlan');
            $cat = $this->helper->getAndEscape('cat');
            $colectivo = $this->helper->getAndEscape('colectivoCurso');
            $modalidad = $this->helper->getAndEscape('mod');
            $kw = $this->helper->getAndEscape('keyword');
            
            $where = array();
            $queryString = '&amp;sent=1';
            $queryARR['sent'] = 1;
            
            // ID
            if (!empty($id)){
                $where[] = " idCurso = $id";
                $this->view->id = $id;
//                $queryString .= "&amp;idCurso=$id";
                $queryARR['idCurso'] = $id;
            }
            
            // PLAN
            if (!empty($plan)){
                $where[] = " fkPlan = $plan";
                $this->view->plan = $plan;
//                $queryString .= "&amp;idPlan=$plan";
                $queryARR['idPlan'] = $plan;
            }

            // CATEGORÍA
            if (!empty($cat)){
                $where[] = " fkCategoria = $cat";
                $this->view->cat = $cat;
//                $queryString .= "&amp;cat=$cat";
                $queryARR['cat'] = $cat;
                $this->view->htmlSelectCategorias = $this->_getSelectHtml($arbolDS, 0, $cat);
            }

            // COLECTIVO
            if (!empty($colectivo)){
                $where[] = " fkColectivo = $colectivo";
                $this->view->colectivo = $colectivo;
//                $queryString .= "&amp;colectivoCurso=$colectivo";
                $queryARR['colectivoCurso'] = $colectivo;
            }

            // MODALIDAD
            if (!empty($modalidad)){
                $where[] = " fkModalidad = $modalidad";
                $this->view->modalidad = $modalidad;
//                $queryString .= "&amp;mod=$modalidad";
                $queryARR['mod'] = $modalidad;
            }
            
            
            // KEYWORD
            if (!empty($kw)){
                //$where[] = "vNombre LIKE '%$kw%' OR vDescripcion LIKE '%$kw%'";
                $where[] = "vNombre LIKE '%$kw%'";
                $this->view->kw = $kw;
//                $queryString .= "&amp;keyword=$kw";
                $queryARR['keyword'] = $kw;             
            }
            
            // Se constuye el where
            if (count($where)){
                $where = ' WHERE ' . implode(' AND ', $where);
            } else {
                $where = '';
            }
            
            // Se ejecuta la búsqueda
            $paginador = new OwlPaginator($this->db, $where, 'tblCurso', $this->helper);
            $paginador->setItemsPorPagina(10);
            $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
            $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
            $paginador->setPaginaActual($paginaActual);
            $paginador->setOrderBy($orderBy);
            $paginador->setOrder($order);
//            $paginador->setExtraParams($queryString);
            $paginador->setExtraParams($queryARR);
        
            // Obtengo las convocatorias
            $cursosCOL = $paginador->getItemCollection();
            $this->view->cursosCOL = $cursosCOL;        
            
            // Envío el paginador a la vista
            $this->view->paginador = $paginador->getPaginatorHtml();
            
            // Se propagan las clausulas de búsqueda en el paginador
        	foreach ( $queryARR as $clave => $valor ){
            	$queryString .= '&amp;' . $clave . '=' . $valor;
            }
            $this->view->querystring = $queryString;
            
            
        }        
        
    }
    
    
    /**
     * Horario del curso
     */
    public function horarioAction(){
    	
    	$idCurso = $this->getParam(0);
        if ( !is_null($idCurso) ){
        	
        	$cursoDO = TblCurso::findByPrimaryKey($this->db, $idCurso);
        	
        	if ( !empty($cursoDO) ){
	        	
        		$this->view->cursoDO = $cursoDO;
	        	
        		// Comprobamos que el curso tenga fecha inicio y fecha fin para poder crear horarios
        		$fechaInicioCurso = $cursoDO->getDInicio();
        		$fechaFinCurso = $cursoDO->getDFin();
        		if ( $fechaInicioCurso == '0000-00-00' && $fechaFinCurso == '0000-00-00' ){
        			$this->view->sinFechas = true;
        		}
        		
        		// El usuario ha enviado horarios
        		if ( $this->helper->getAndEscape(md5('sendHorario')) || $this->helper->getAndEscape(md5('sendDia')) ){
        		
        			$correcto = true;
        			$fechasARR = array();
        			
	        		// Comprobamos si se ha enviado un grupo
	        		if ( $this->helper->getAndEscape(md5('sendHorario')) ) {
	        			
	        			$lunes = $this->helper->escapeInjection($this->helper->get('lunes'));
	        			$martes = $this->helper->escapeInjection($this->helper->get('martes'));
	        			$miercoles = $this->helper->escapeInjection($this->helper->get('miercoles'));
	        			$jueves = $this->helper->escapeInjection($this->helper->get('jueves'));
	        			$viernes = $this->helper->escapeInjection($this->helper->get('viernes'));
	        			$sabado = $this->helper->escapeInjection($this->helper->get('sabado'));
	        			$domingo = $this->helper->escapeInjection($this->helper->get('domingo'));
	        			$inicio = $this->helper->escapeInjection($this->helper->get('inicioGrupo'));
	        			$fin = $this->helper->escapeInjection($this->helper->get('finGrupo'));
	
	        			if ( empty($lunes) && empty($martes) && empty($miercoles) && empty($jueves) && empty($viernes) && empty($sabado) && empty($domingo) ){
	        				$correcto = false;
	        				$this->view->errorSemana = "Debe seleccionar un día";
	        			}
	        			
	        			if ( empty($inicio) ){
	        				
	        				$correcto = false;
	        				$this->view->errorInicioGrupo = "Debe rellenar este campo";
	        				
	        			} elseif (!preg_match('/^\d{1,2}:\d{1,2}$/', $inicio)) {
	        				
	        				$correcto = false;
	        				$this->view->errorInicioGrupo = "El formato no es correcto";
	        				
	        			}
	        			
	        			if ( empty($fin) ){
	        				
	        				$correcto = false;
	        				$this->view->errorFinGrupo = "Debe rellenar este campo";
	        				
	        			} elseif (!preg_match('/^\d{1,2}:\d{1,2}$/', $fin)) {
	        				
	        				$correcto = false;
	        				$this->view->errorFinGrupo = "El formato no es correcto";
	        				
	        			}
	        			
	        			// Cálculo de los días que habrá clase
	        			if ( $correcto ){
	        				
	        				$diasARR = array();
	        				if ( !empty($lunes) ) array_push($diasARR, '1');
	        				if ( !empty($martes) ) array_push($diasARR, '2');
	        				if ( !empty($miercoles) ) array_push($diasARR, '3');
	        				if ( !empty($jueves) ) array_push($diasARR, '4');
	        				if ( !empty($viernes) ) array_push($diasARR, '5');
	        				if ( !empty($sabado) ) array_push($diasARR, '6');
	        				if ( !empty($domingo) ) array_push($diasARR, '0');
	        				
	        				$fechaIniTime = strtotime($fechaInicioCurso);
	        				$fechaFinTime = strtotime($fechaFinCurso);
	        				$duracionCursoTime = $fechaFinTime - $fechaIniTime;
	        				$duracionCurso = $duracionCursoTime/86400; // Número de días
	        				
	        				$duracionCurso++;
	        				
	        				// Compruebo qué días ha seleccionado el usuario, y creo las tuplas
	        				for ( $i=0; $i<=$duracionCurso; $i++ ){
	        					
	        					$diaSemana = date('w', $fechaIniTime);
	        					if ( in_array($diaSemana, $diasARR) ){
	        						$fechasARR[date('Y-m-d', $fechaIniTime)]['inicio'] = $inicio;
	        						$fechasARR[date('Y-m-d', $fechaIniTime)]['fin'] = $fin;
	        						$fechasARR[date('Y-m-d', $fechaIniTime)]['dia'] = date('Y-m-d', $fechaIniTime);
	        					}
	        					$fechaIniTime += 86400;
	        					
	        				}
	        				
	        				// Obtenemos las sesiones
	        				$fechasARR = $this->actualizarSesiones($fechasARR, $cursoDO->getIdCurso(), $fechaInicioCurso, $fechaFinCurso);
	        				
	        			}	
	        			
	        		}
	
	        		// Comprobamos si se ha enviado un día
	        		if ( $this->helper->getAndEscape(md5('sendDia')) ) {
	        			
	        			$dia = $this->helper->escapeInjection($this->helper->get('dia'));
	        			$inicio = $this->helper->escapeInjection($this->helper->get('inicioDia'));
	        			$fin = $this->helper->escapeInjection($this->helper->get('finDia'));
	        			
	        			if ( empty($dia) ){
	        				$correcto = false;
	        				$this->view->errorDia = "Debe rellenar este campo";
	        			}
	        			
	        			if ( empty($inicio) ){
	        				
	        				$correcto = false;
	        				$this->view->errorInicioDia = "Debe rellenar este campo";
	        				
	        			} elseif (!preg_match('/^\d{1,2}:\d{1,2}$/', $inicio)) {
	        				
	        				$correcto = false;
	        				$this->view->errorInicioDia = "El formato no es correcto";
	        				
	        			}
	        			
	        			if ( empty($fin) ){
	        				
	        				$correcto = false;
	        				$this->view->errorFinDia = "Debe rellenar este campo";
	        				
	        			} elseif (!preg_match('/^\d{1,2}:\d{1,2}$/', $fin)) {
	        				$correcto = false;
	        				$this->view->errorFinDia = "El formato no es correcto";
	        			}
	        			
	        			// Convierto el dia al formato de mysql
	        			$dia = OwlDate::europeoAmericano($dia);
	        			
	        			$fechasARR[$dia]['inicio'] = $inicio;
	        			$fechasARR[$dia]['fin'] = $fin;
	        			$fechasARR[$dia]['dia'] = $dia;
	        			
	        			// Obtenemos las sesiones
        				$fechasARR = $this->actualizarSesiones($fechasARR, $cursoDO->getIdCurso(), $fechaInicioCurso, $fechaFinCurso);
	        			
	        		}
	        		
	        		// Guardamos el horario
	        		if ( $correcto ){
	        			
	        			// Empieza la transacción
		    			$this->db->begin();
		    			
		    			// SE ELIMINAN TODAS LAS TUPLAS CORRESPONDIENTES A HORARIOS DE ESTE CURSO
		    			$sql = 'DELETE FROM tblHorario WHERE fkCurso = ' . $cursoDO->getIdCurso();
		    			
		    			if (!$this->db->executeQuery($sql)){
		    				
		    				// ERROR ELIMINAR
		    				echo '<h1>ERROR ELIMINAR</h1>';
		    				$correcto = false;
		    				
		    			} 
	        			
	        			foreach ( $fechasARR as $clave=>$horario ){
	        				
	        				$horarioDO = new TblHorario($this->db);
	        				$horarioDO->setFkCurso($cursoDO->getIdCurso());
	        				$horarioDO->setDDia($horario['dia']);
	        				$horarioDO->setIDesde($horario['inicio']);
	        				$horarioDO->setIHasta($horario['fin']);
	        				$horarioDO->setISesion(++$clave);
	        				
	        				if ( !$horarioDO->insert() ){
	        					$correcto = false;
	        					break;
	        				}
	        				
	        			}
	        			
	        			if ( $correcto ){
	        				$this->db->commit(); // np
	        			} else {
	        				$this->db->rollback();
	        			}
	        			
	        		}
	        		
        		} // if ( $this->helper->getAndEscape(md5('sendHorario')) || $this->helper->getAndEscape(md5('sendDia')) )
        		
        		// Se instancia y configura el paginador
        		$sql = "WHERE fkCurso = " . $cursoDO->getIdCurso();
		        $paginador = new OwlPaginator($this->db, $sql, 'tblHorario', $this->helper);
		        $paginador->setItemsPorPagina(10);
		        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
		        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
		        $paginador->setPaginaActual($paginaActual);
		        $paginador->setOrderBy('iSesion ASC');
		        
		        // Datos para la vista
		    	// Envío el horario
		        $this->view->horariosCOL = $paginador->getItemCollection();
		        
		        // Envío el paginador
		        $this->view->paginador = $paginador->getPaginatorHtml();
		    	
        		
        	} // if ( !empty($cursoDO) )
        	
        } // if ( !is_null($idCurso) )
        
    }
    
    
    /**
     * Elimina un horario de un curso
     */
    public function eliminarHorarioAction(){
    	
    	$idHorario = $this->getParam(0);
        if ( !is_null($idHorario) ){
        	
        	$horarioDO = TblHorario::findByPrimaryKey($this->db, $idHorario);
        	$horarioDO->delete();
        	$this->redirectTo('curso','horario', $horarioDO->getFkCurso());
        }
        
         $this->redirectTo('curso','index');
    	
    }
    
    
    /**
     * Elimina todo el horario de un curso
     */
    public function eliminarTodoHorarioAction(){
    	
    	$idCurso = $this->getParam(0);
        if ( !is_null($idCurso) ){
        	
        	$sql = "DELETE FROM tblHorario WHERE fkCurso = " . $idCurso;
        	$this->db->executeQuery($sql);
        	$this->redirectTo('curso','horario', $idCurso);
        }
        
         $this->redirectTo('curso','index');
    	
    }
    
    
    /**
     * Devuelve un array con los días, horas y sesiones del curso. Indexado por fecha
     * 
     * @param array $fechasUsuarioARR
     * @param integer $idCurso
     * @param date $fechaInicio
     * @param date $fechaFin
     */
    public function actualizarSesiones( $fechasUsuarioARR, $idCurso, $fechaInicio, $fechaFin ){
    	
		$fechasSesionARR = $fechasExistentesARR = array();
    	
    	// Obtenemos el horario del curso de la bbdd
    	$sql = "SELECT * FROM tblHorario WHERE fkCurso = " . $idCurso . " ORDER BY dDia ASC";
		$this->db->executeQuery($sql);

		while ($row = $this->db->fetchRow()){
			
			$dia = $row['dDia'];
			
			$diaCurso = array(
				'inicio' => $row['iDesde'],
				'fin' => $row['iHasta'],
				'dia' => $dia,			
			);

			// En la base de datos puede haber dos sesiones en un mismo día
			if (array_key_exists($dia, $fechasExistentesARR)){
				
				$diaCursoExistenteARR = $fechasExistentesARR[$dia];
				$fechasExistentesARR[$dia] = array();
				
				array_push($fechasExistentesARR[$dia], $diaCursoExistenteARR);
				array_push($fechasExistentesARR[$dia], $diaCurso);
				
			} else {
				
				$fechasExistentesARR[$dia] = $diaCurso;
				
			}
			
		}
		
		$periodoARR = OwlDate::createDateRangeArray($fechaInicio, $fechaFin);
		
		// Se contruye el array de retorno
		foreach ($periodoARR as $clave => $diaCurso){
			
			// Dos sesiones en el mismo día
			if (array_key_exists($diaCurso, $fechasExistentesARR) && array_key_exists($diaCurso, $fechasUsuarioARR)){
				
				$horaInicioExistente = strtotime($fechasExistentesARR[$diaCurso]['inicio']);
				$horaInicioUsuario = strtotime($fechasUsuarioARR[$diaCurso]['inicio']);
				
				if ($horaInicioExistente > $horaInicioUsuario){

					array_push($fechasSesionARR, $fechasUsuarioARR[$diaCurso]);
					array_push($fechasSesionARR, $fechasExistentesARR[$diaCurso]);
					
				} else {
					
					array_push($fechasSesionARR, $fechasExistentesARR[$diaCurso]);
					array_push($fechasSesionARR, $fechasUsuarioARR[$diaCurso]);
					
				}
				
			} elseif (array_key_exists($diaCurso, $fechasExistentesARR)){
				
				// Si es un array, hay mas de una sesión
				if (array_key_exists(0, $fechasExistentesARR[$diaCurso])){
					
					foreach ($fechasExistentesARR[$diaCurso] as $sesionCurso){
						array_push($fechasSesionARR, $sesionCurso);
					}
					
				} else {
					array_push($fechasSesionARR, $fechasExistentesARR[$diaCurso]);
				}
				
			} elseif (array_key_exists($diaCurso, $fechasUsuarioARR)){
				
				array_push($fechasSesionARR, $fechasUsuarioARR[$diaCurso]);	
				
			}
			
		}
		
	   	return $fechasSesionARR; 
    	
    }
    
    
    /**
     * Página donde se genera toda la documentación dinámica disponible 
     * para un curso en particular.
     */
    public function documentacionAction(){

    	// Sin clave no hay nada que hacer
    	if (!$idCurso = $this->getParam(0)){
    		$this->redirectTo('curso');
    		return;
    	}
    	
    	// El curso no existe
    	if (!$cursoDO = TblCurso::findByPrimaryKey($this->db, $idCurso)){
			$this->redirectTo('curso');
    		return;    		
    	}
    	
    	$idPlan = $cursoDO->getFkPlan();
    	$this->view->cursoDO = $cursoDO;
    	$mensajesDocumentacionARR = array();
    	$modalidadesIDX = $this->cacheBO->getModalidades();
    	
    	// Se obtienen los documentos seleccionados para convocatoria del curso
    	$documentosCOL = $this->cacheBO->getDocumentacionCurso($idPlan);
    	$planDO = TblPlan::findByPrimaryKey($this->db, $idPlan);
    	
    	// Profesores del curso
    	$profesoresCOL = $this->cacheBO->getProfesoresCurso($idCurso);
    	$profesorDO = array_shift($profesoresCOL);
    	
    	// Alumnos del curso
    	$alumnosCOL = TblAlumno::findByTblCurso($this->db, $idCurso);

    	// Horarios de formación del curso
    	$horariosCOL = TblHorario::findByTblCurso($this->db, $idCurso);
    	
    	
    	/////////////////////////////////////////////////////////////
    	//														   //
    	// 					SE GENERA LA DOCUMENTACIÓN             //
    	//														   //
    	/////////////////////////////////////////////////////////////
    	
  		// Se iteran todos los documentos asocidadsos a la convocatoria
    	foreach ($documentosCOL as $documentoDO){
    		
    		$docMan = new PplDocumentacion($this->db, $documentoDO->getVIdentificador());
    		$error = false;
    		
    		switch ($documentoDO->getVIdentificador()){
    			
    			//
    			// S-30 Control de asistencia
    			//
    			case 'S-30':
    				
    				//break;
    				
    				// Verificaremos que contamos con los datos necesarios para el curso
    				if (!$profesorDO instanceof TblPersona){
    					$mensajesDocumentacionARR[] = 'S-30: El curso actual aún no tiene un profesor asignado.';
    					$error = true;
    				}
    				
    				if (count($horariosCOL) == 0){
    					$mensajesDocumentacionARR[] = 'S-30: No se ha definido ningún horario.';
    					$error = true;
    				}
    				
    				if ($error){
    					break;
    				}
    				
    				// De acuerdo a la cantidad de alumnos, tendremos que generar un pdf con 1 o 2 páginas
    				if (count($alumnosCOL) > 15) {
    					$this->view->controlAsistenciaARR = $docMan->docControlAsistencia2p($cursoDO, $planDO, $profesorDO, $alumnosCOL, $horariosCOL);
    				} else {
    					$this->view->controlAsistenciaARR = $docMan->docControlAsistencia($cursoDO, $planDO, $profesorDO, $alumnosCOL, $horariosCOL);
    				}
    				
    			break;
    			
    			
    			//
    			// S-20 Listado inicial de asistentes
    			//
    			case 'S-20':
    				
    				$tutoriaDO = $this->cacheBO->getTutoriaCurso($idCurso);
    				if ($tutoriaDO instanceof TblTutoria && $tutorDO = $tutoriaDO->getTblPersona()){
	    				$this->view->listadoInicial = $docMan->docListadoInicialAsistentes($cursoDO, $alumnosCOL, $tutorDO, $planDO, $modalidadesIDX, $tutoriaDO);
    				} else {
    					$mensajesDocumentacionARR[] = 'S-20: El curso actual aún no tiene un tutor a distancia asignado.';
    				}
    				
    			break;
    			
    			
    			//
    			// S-10 Inicio grupo/acción formativa
    			//
    			case 'S-10':
    				
    				$academiaDO = $this->cacheBO->getAcademiaCurso($idCurso);
    				$tutoriaDO = $this->cacheBO->getTutoriaCurso($idCurso);
    				
    				$this->view->inicioAccion = $docMan->docInicioAccionFormativa($planDO, $cursoDO, $modalidadesIDX, $academiaDO, $horariosCOL, $tutoriaDO);
    				
    			break;
    			
    		}
    		
    	}
    	
    	// Se envian los mensajes a la vista
    	$this->view->mensajes = $mensajesDocumentacionARR;
    	
    }
    
    
    /**
     * Alumnos del curso a editar
     */
    public function alumnosAction(){
    	
    	
    	// Obtengo el curso que voy a editar
    	$idCurso = $this->getParam(0);
    	
    	$sent = $this->helper->getAndEscape('sent');
    	
    	if ( !is_null($idCurso) ){
        	
        	// Curso
            if (!$cursoDO = TblCurso::findByPrimaryKey($this->db, $idCurso)){
                $this->redirectTo('curso', 'index');
                return;
            }
            
		    // Actualización de datos
		    if (!empty($sent)){
		    	
	    	    // Precandidatos
		    	$precandidatosARR = array();
		        if ( array_key_exists('precandidatos', $_POST) ){
		        	foreach ($_POST['precandidatos'] as $precandidato) {
		            	$precandidatosARR[] = $this->helper->escapeInjection($precandidato);
		            }
		        }
		        
			    // Candidatos
		    	$candidatosARR = array();
		        if ( array_key_exists('candidatos', $_POST) ){
		        	foreach ($_POST['candidatos'] as $candidato) {
		            	$candidatosARR[] = $this->helper->escapeInjection($candidato);
		            }
		        }
		
		        // Alumnos
		    	$alumnosARR = array();
		        if ( array_key_exists('alumnos', $_POST) ){
		        	foreach ($_POST['alumnos'] as $alumno) {
		            	$alumnosARR[] = $this->helper->escapeInjection($alumno);
		            }
		        }
		        
		        $correcto = count($precandidatosARR) || count($candidatosARR) || count($alumnosARR);
		        
	    		// Se inicia la transacción
	    		$this->db->begin();
	    		
			    // Precandidatos
		    	if ( $correcto ){

	    			$sql = 'DELETE FROM trelPrecandidato WHERE fkCurso = ' . $idCurso;
	    			if ( !$this->db->executeQuery($sql) ){
	    				$correcto = false;
	    			}
		    		
		    		if ( $correcto && !empty($precandidatosARR) ){
		    			$sql = "INSERT INTO trelPrecandidato VALUES ";
		    			$valuesARR = array();
		    			foreach ( $precandidatosARR as $idPrecandidato ){
			    			$valuesARR[] = '(' . $idPrecandidato . ',' . $idCurso . ',\'' . date('Y-m-d') . '\')';
				    	}
				    	$sql .= implode(',', $valuesARR);
		    			if ( !$this->db->executeQuery($sql) ){
		    				$correcto = false;
		    			}
		    		}
		    		
		    	}
	
		    	// Candidatos
		    	if ( $correcto ){
		    		
	    			$sql = 'DELETE FROM trelCandidato WHERE fkCurso = ' . $idCurso;
	    			if ( !$this->db->executeQuery($sql) ){
	    				$correcto = false;
	    			}
		    		
		    		if ( $correcto && !empty($candidatosARR) ){
		    			$sql = "INSERT INTO trelCandidato VALUES ";
		    			$valuesARR = array();
		    			foreach ( $candidatosARR as $idCandidato ){
			    			$valuesARR[] = '(' . $idCandidato . ',' . $idCurso . ',\'' . date('Y-m-d') . '\')';
				    	}
				    	$sql .= implode(',', $valuesARR);
		    			if ( !$this->db->executeQuery($sql) ){
		    				$correcto = false;
		    			}
		    		}
		    		
		    	}
		    	
		    	// Alumnos
		    	if ( $correcto ){
		    		
	    			$sql = 'DELETE FROM tblAlumno WHERE fkCurso = ' . $idCurso;
	    			if ( !$this->db->executeQuery($sql) ){
	    				$correcto = false;
	    			}
		    		
		    		if ( $correcto ){
		    			
		    			if ( !empty($alumnosARR) ){
		    				
				    		// Obtenemos las personas para copiar como alumnos
				    		$sql = "SELECT * FROM tblPersona WHERE idPersona IN (" . implode(', ', $alumnosARR) . ")";
				    		
				    		$personasCOL = OwlGenericDO::createCollection($this->db, $sql, 'tblPersona');
				    		$estadosCivilesIDX = $this->cacheBO->getEstadosCiviles();
				    		$estadosLaboralesIDX = $this->cacheBO->getEstadosLaborales();
				    		$nivelesEstudioIDX = $this->cacheBO->getNivelesEstudio();
				    		$paisesIDX = $this->cacheBO->getPaises();
				    		$provinciasIDX = $this->cacheBO->getProvincias();
				    		$tiposIdentificacionIDX = $this->cacheBO->getTiposIdentificacion();
				    		
				    		foreach ( $personasCOL as $personaDO ){
				    			
				    			$alumnoDO = new TblAlumno($this->db);
				    			$alumnoDO->setDAlta(date('Y-m-d'));
				    			$alumnoDO->setDNacimiento($personaDO->getDNacimiento());
				    			$alumnoDO->setFkCurso($cursoDO->getIdCurso());
				    			$alumnoDO->setIPersona($personaDO->getIdPersona());
				    			$alumnoDO->setIUsuario($personaDO->getFkUsuario());
				    			$alumnoDO->setVDireccion($personaDO->getVDireccion());
				    			$alumnoDO->setVEmail($personaDO->getTblUsuario()->getVEmail());
				    			$alumnoDO->setVEstadoCivil($estadosCivilesIDX[$personaDO->getFkEstadoCivil()]->getVNombre());
				    			$alumnoDO->setVEstadoLaboral($estadosLaboralesIDX[$personaDO->getFkEstadoLaboral()]->getVNombre());
								$alumnoDO->setVNivelEstudios($nivelesEstudioIDX[$personaDO->getFkNivelEstudios()]->getVNombre());
								$alumnoDO->setVNombre($personaDO->getVNombre());
								$alumnoDO->setVNumeroIdentificacion($personaDO->getVNumeroIdentificacion());
								$alumnoDO->setVPais($paisesIDX[$personaDO->getFkPais()]->getVIso());
								$alumnoDO->setVPoblacion($personaDO->getVPoblacion());
								$alumnoDO->setVPrimerApellido($personaDO->getVPrimerApellido());
								$alumnoDO->setVProvincia( ( is_null($personaDO->getFkProvincia()) || $personaDO->getFkProvincia() == 0 ) ? null : $provinciasIDX[$personaDO->getFkProvincia()]->getVNombre());
								$alumnoDO->setVSegundoApellido($personaDO->getVSegundoApellido());
								$alumnoDO->setVNumeroSS($personaDO->getVNumeroSS());
								$alumnoDO->setVTipoIdentificacion($tiposIdentificacionIDX[$personaDO->getFkTipoIdentificacion()]->getVNombre());
								
								if ( !$alumnoDO->insert() ){
									$correcto = false;
								}
								
				    		}
		    			}
		    		}
		    		
		    		if ($correcto){
		    			
		    			$this->db->commit();
		    			
		    		} else {
		    			
		    			$this->db->rollback();
    			        $this->view->popup = array(
		                	'estado' => 'ko',
		                	'titulo' => 'Error',
		                    'mensaje'=> 'Ha ocurrido un error con la edición de los alumnos del curso. Inténtelo de nuevo en unos instantes por favor.<br/>Muchas gracias.',
		                    'url'=> '',
		                );
		    		}
		    		
		    	}		        
		    	
		    }
		    
			// Curso
            $this->view->cursoDO = $cursoDO;
            
	    	// Precandidatos
        	$this->view->precandidatosCursoCOL = TrelPrecandidato::findByTblCurso($this->db, $cursoDO->getIdCurso());
        
    	    // Alumnos
		    $this->view->alumnosCursoCOL = $alumnosCOL = TblAlumno::findByTblCurso($this->db, $cursoDO->getIdCurso());

	        // Candidatos
		    $this->view->candidatosCursoCOL = TrelCandidato::findByTblCurso($this->db, $cursoDO->getIdCurso());
		    
		    // Personas
	        $this->view->personasIDX = $this->cacheBO->getPersonas();			    
    
            
        } else {
        	
        	$this->redirectTo('curso', 'index');
        	return;
        	
        }
    	
    	
    }
    
}

?>