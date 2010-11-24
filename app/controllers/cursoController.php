<?php

require_once 'helper/NingenCmsHtmlHelper.inc';
require_once 'helper/NingenDate.inc';
require_once 'NingenPaginator.inc';

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';

require_once NINGENCMS_MODELDIR . '/TblAula.inc';
require_once NINGENCMS_MODELDIR . '/TblCentro.inc';
require_once NINGENCMS_MODELDIR . '/TblCategoria.inc';
require_once NINGENCMS_MODELDIR . '/TblCategoria.inc';
require_once NINGENCMS_MODELDIR . '/TblCategoriaExtendida.inc';
require_once NINGENCMS_MODELDIR . '/TblColectivo.inc';
require_once NINGENCMS_MODELDIR . '/TblCurso.inc';
require_once NINGENCMS_MODELDIR . '/TblModalidad.inc';
require_once NINGENCMS_MODELDIR . '/TblSector.inc';
require_once NINGENCMS_MODELDIR . '/TblPlan.inc';
require_once NINGENCMS_MODELDIR . '/TrelCandidato.inc';
require_once NINGENCMS_MODELDIR . '/TrelPrecandidato.inc';
require_once NINGENCMS_MODELDIR . '/TrelProfesor.inc';


class cursoController extends PplController{
    
    /**
     * Colección de categorias
     * @var array
     */
    protected $categoriasCOL = null;
    
    /**
     * Init
     * @see extranet.planespime.es/ningencms/lib/NingenController::initController()
     */
    public function initController(){

    	parent::initController();
        
    }
    
    /**
     * Acción inicial, por defecto, el listado
     * @see extranet.planespime.es/ningencms/lib/NingenController::indexAction()
     */
    public function indexAction(){
        
    	// Parámetros de ordenación para el paginador
    	$aliasCampos = array(
    		'cat'	=> 'fkCategoria',
    		'fin'	=> 'dFin',
    		'ini'	=> 'dInicio',
    		'nom' 	=> 'vNombre',
    		'plan'	=> 'fkPlan',
    		'sec'	=> 'fkSector'
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
        $paginador = new NingenPaginator($this->db, null, 'tblCurso', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo las aulas
        $cursosCOL = $paginador->getItemCollection();
        
        // Envío el paginador a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío los cursos a la vista
        $this->view->cursosCOL = $cursosCOL;
        
         // Planes
        $this->view->planesIDX = $this->cacheBO->getPlanes();
        
        // Sectores
        $this->view->sectoresIDX = $this->cacheBO->getSectores();
        
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
        
        // Sectores
        $this->view->sectoresIDX = $this->cacheBO->getSectores();
        
        // Modalidades
        $this->view->modalidadesIDX = $this->cacheBO->getModalidades();
        
        // Aulas
        $this->view->aulasIDX = $this->cacheBO->getAulas();
        
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
        	
        	if ( NingenCmsSession::getValue('cursoDuplicado') instanceof TblCurso ){
        		
        		$cursoDO = NingenCmsSession::getValue('cursoDuplicado');
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
	        
	        // Sectores
	        $this->view->sectoresIDX = $this->cacheBO->getSectores();
	        
	        // Modalidades
	        $this->view->modalidadesIDX = $this->cacheBO->getModalidades();
	        
	        // Aulas
	        $this->view->aulasIDX = $this->cacheBO->getAulas();
	    	
	        // Profesores curso
	        $this->view->profesoresCursoCOL = TrelProfesor::findByTblCurso($this->db, $cursoDO->getIdCurso());
	        
	        // Profesores
	        $this->view->profesoresIDX = $this->cacheBO->getProfesores();
	        
	        // Categorías
	        $this->view->categoriasIDX = $this->cacheBO->getCategorias();
	        
	        // Categorías de profesores
	        $this->view->categoriasProfesoresIDX = $this->cacheBO->getProfesoresCategorias();
	        
	        // Precandidatos
	        $this->view->precandidatosCursoCOL = TrelPrecandidato::findByTblCurso($this->db, $cursoDO->getIdCurso());
	        
	        // Candidatos
		    $this->view->candidatosCursoCOL = TrelCandidato::findByTblCurso($this->db, $cursoDO->getIdCurso());
	        
	        // Personas
	        $this->view->personasIDX = $this->cacheBO->getPersonas();
	        
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

        	}
        	
        }
        
    }
    
	/**
     * Acción de eliminar
     * Elimina un aula
     */
    public function eliminarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$cursoDO = TblCurso::findByPrimaryKey($this->db, $paramsARR[0]);
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
        	NingenCmsSession::setValue('cursoDuplicado', $cursoDO);
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
	    
	    // Categoría
    	$categoria = $this->helper->escapeInjection($this->helper->get('categoria'));
	    if ( is_null($categoria) || empty($categoria) ){
	    	$correcto = false;
	    	$this->view->errorCategoria = 'La categoria no puede estar vacía';
	    }
	    
	    // Sector
    	$sector = $this->helper->escapeInjection($this->helper->get('sector'));
	    if ( is_null($sector) || empty($sector) ){
	    	$correcto = false;
	    	$this->view->errorSector = 'El sector no puede estar vacío';
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
	    
	    // Aula
    	$aula = $this->helper->escapeInjection($this->helper->get('aula'));
	    if ( is_null($aula) || empty($aula) ){
	    	$correcto = false;
	    	$this->view->errorAula = 'El aula no puede estar vacía';
	    }
	    
	     // horas presenciales
    	$horasP = $this->helper->escapeInjection($this->helper->get('horasP'));
	    if ( is_null($horasP) || empty($horasP) ){
	    	$horasP = "";
	    }
	    
	     // horas a distacia
    	$horasD = $this->helper->escapeInjection($this->helper->get('horasD'));
	    if ( is_null($horasD) || empty($horasD) ){
	    	$horasD = "";
	    }
	    
	     // horas de tutoría
    	$horasT = $this->helper->escapeInjection($this->helper->get('horasT'));
	    if ( is_null($horasT) || empty($horasT) ){
	    	$horasT = "";
	    }
	    
    	// alumnos
    	$alumnos = $this->helper->escapeInjection($this->helper->get('numAlumnos'));
	    if ( is_null($alumnos) || empty($alumnos) ){
	    	$alumnos = "";
	    }
	    
	    // inicio
    	$inicio = $this->helper->escapeInjection($this->helper->get('inicio'));
	    if ( is_null($inicio) || empty($inicio) ){
	    	$inicio = "";
	    }
	    
	    // fin
    	$fin = $this->helper->escapeInjection($this->helper->get('fin'));
	    if ( is_null($fin) || empty($fin) ){
	    	$fin = "";
	    }
	    
	    // Profesores
    	$profesoresARR = array();
        if ( array_key_exists('profesores', $_POST) ){
        	foreach ($_POST['profesores'] as $profesor) {
            	$profesoresARR[] = $this->helper->escapeInjection($profesor);
            }
        }
        
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
        
		/**
		 * Insertamos o actualizamos un centro
		 */
	    if ( $correcto ){

	    	// Empieza la transacción
		    $this->db->begin();
	    	
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
		    	$cursoDO->setFkSector($sector);
		    	$cursoDO->setFkModalidad($modalidad);
		    	$cursoDO->setFkAula($aula);
		    	$cursoDO->setIHorasPresenciales($horasP);
		    	$cursoDO->setIHorasDistancia($horasD);
		    	$cursoDO->setIHorasTutoria($horasT);
		    	$cursoDO->setDInicio(NingenDate::europeoAmericano($inicio));
		    	$cursoDO->setDFin(NingenDate::europeoAmericano($fin));
		    	$cursoDO->setINumeroAlumnos($alumnos);
		    	$cursoDO->setLastModified(date('Y-m-d'));
                $cursoDO->setModUser($this->usuario->getNombre());
		    	
		    	if ( $editar ){
		    		$correcto = $cursoDO->update();
		    	} else {
		    		$correcto = $cursoDO->insert();
		    	}
		    	
	    	}
	    	
	    	// Profesores del curso. Si estoy editando, borro todos los profesores para insertar los nuevos
	    	if ( $correcto ){
	    		
	    		if ( $editar ){
	    			$sql = 'DELETE FROM trelProfesor WHERE fkCurso = ' . $idCurso;
	    			if ( !$this->db->executeQuery($sql) ){
	    				$correcto = false;
	    			}
	    		} else {
	    			$idCurso = $this->db->getLastInsertId();
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
	    	
		    // Precandidatos
	    	if ( $correcto ){
	    		
	    		if ( $editar ){
	    			$sql = 'DELETE FROM trelPrecandidato WHERE fkCurso = ' . $idCurso;
	    			if ( !$this->db->executeQuery($sql) ){
	    				$correcto = false;
	    			}
	    		}
	    		
	    		if ( $correcto ){
	    			foreach ( $precandidatosARR as $idPrecandidato ){
		    			$sql = 'INSERT INTO trelPrecandidato VALUES (' . $idPrecandidato . ',' . $idCurso . ',\'' . date('Y-m-d') . '\')';
		    			if ( !$this->db->executeQuery($sql) ){
		    				$correcto = false;
		    			}
			    	}
	    		}
	    		
	    	}

	    	// Candidatos
	    	if ( $correcto ){
	    		
	    		if ( $editar ){
	    			$sql = 'DELETE FROM trelCandidato WHERE fkCurso = ' . $idCurso;
	    			if ( !$this->db->executeQuery($sql) ){
	    				$correcto = false;
	    			}
	    		}
	    		
	    		if ( $correcto ){
	    			foreach ( $candidatosARR as $idCandidato ){
		    			$sql = 'INSERT INTO trelCandidato VALUES (' . $idCandidato . ',' . $idCurso . ',\'' . date('Y-m-d') . '\')';
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
        
        // Sectores
        $this->view->sectoresIDX = $this->cacheBO->getSectores();
        
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
                'sec'   => 'fkSector'
            );
            

            if ( !empty($_REQUEST) && array_key_exists('o', $_GET) & array_key_exists('ob', $_GET) ){
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
            $sector = $this->helper->getAndEscape('sector');
            $modalidad = $this->helper->getAndEscape('mod');
            $kw = $this->helper->getAndEscape('keyword');
            
            $where = array();
            $queryString = '&amp;sent=1';
            
            // ID
            if (!empty($id)){
                $where[] = " idCurso = $id";
                $this->view->id = $id;
                $queryString .= "&amp;idCurso=$id";
            }
            
            // PLAN
            if (!empty($plan)){
                $where[] = " fkPlan = $plan";
                $this->view->plan = $plan;
                $queryString .= "&amp;idPlan=$plan";
            }

            // CATEGORÍA
            if (!empty($cat)){
                $where[] = " fkCategoria = $cat";
                $this->view->cat = $cat;
                $queryString .= "&amp;cat=$cat";
            }

            // COLECTIVO
            if (!empty($colectivo)){
                $where[] = " fkColectivo = $colectivo";
                $this->view->colectivo = $colectivo;
                $queryString .= "&amp;colectivoCurso=$colectivo";
            }

            // SECTOR
            if (!empty($sector)){
                $where[] = " fkSector = $sector";
                $this->view->sector = $sector;
                $queryString .= "&amp;sector=$sector";
            }

            // MODALIDAD
            if (!empty($modalidad)){
                $where[] = " fkModalidad = $modalidad";
                $this->view->modalidad = $modalidad;
                $queryString .= "&amp;mod=$modalidad";
            }
            
            
            // KEYWORD
            if (!empty($kw)){
                //$where[] = "vNombre LIKE '%$kw%' OR vDescripcion LIKE '%$kw%'";
                $where[] = "vNombre LIKE '%$kw%'";
                $this->view->kw = $kw;
                $queryString .= "&amp;keyword=$kw";             
            }
            
            // Se constuye el where
            if (count($where)){
                $where = ' WHERE ' . implode(' AND ', $where);
            } else {
                $where = '';
            }
            
            // Se ejecuta la búsqueda
            $paginador = new NingenPaginator($this->db, $where, 'tblCurso', $this->helper);
            $paginador->setItemsPorPagina(10);
            $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
            $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
            $paginador->setPaginaActual($paginaActual);
            $paginador->setOrderBy($orderBy);
            $paginador->setOrder($order);
        
            // Obtengo las convocatorias
            $cursosCOL = $paginador->getItemCollection();
            $this->view->cursosCOL = $cursosCOL;        
            
            // Envío el paginador a la vista
            $this->view->paginador = $paginador->getPaginatorHtml();
            
            // Se propagan las clausulas de búsqueda en el paginador
            $this->view->querystring = $queryString;
            
            
        }        
        
    }
    
    
}

?>