<?php

require_once 'helper/NingenCmsHtmlHelper.inc';
require_once 'NingenPaginator.inc';

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';

require_once NINGENCMS_MODELDIR . '/TblAula.inc';
require_once NINGENCMS_MODELDIR . '/TblPlan.inc';
require_once NINGENCMS_MODELDIR . '/TblCategoria.inc';
require_once NINGENCMS_MODELDIR . '/TblColectivo.inc';
require_once NINGENCMS_MODELDIR . '/TblModalidad.inc';
require_once NINGENCMS_MODELDIR . '/TblSector.inc';
require_once NINGENCMS_MODELDIR . '/TblCurso.inc';
require_once NINGENCMS_MODELDIR . '/TblCentro.inc';


class cursoController extends PplController{
    
    
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
    		'cat'		=> 'fkCategoria',
    		'col'		=> 'fkColectivo',
    		'nom' 		=> 'vNombre',
    		'plan'		=> 'fkPlan',
    		'sector'	=> 'fkSector'
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
        $paginador = new NingenPaginator($this->db, null, 'tblAula', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo las aulas
        $aulasCOL = $paginador->getItemCollection();
        
        // Envío el paginador a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío las aulas a la vista
        $this->view->aulasCOL = $aulasCOL;
        
        // Centros
        $this->view->centrosIDX = $this->cacheBO->getCentros();
        
        // Permiso para editar
    	if ( $this->aclManager->hasPerms('academia', 'editar') ){
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
        
        // Categorías
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
     * Acción de ficha
     * Ficha de un curso
     */
    public function fichaAction(){
        
        echo 'FICHA';
        
    }
    
    /**
     * Función recursiva para tratar las categorias
     * @param array $arrayDS
     * @param integer $clavePadre
     * @param integer $nivel
     */
    private function _IteraCategorias($arrayDS, $clavePadre){
        
    	$categoriasCOL = TblCategoria::findAll($this->db, 'idCategoria ASC');
    	
        foreach ($categoriasCOL as $categoriaDO){
            
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
    	$alumnos = $this->helper->escapeInjection($this->helper->get('alumnos'));
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
		    	$cursoDO->setDInicio(date('Y-m-d', strtotime($inicio)));
		    	$cursoDO->setDFin(date('Y-m-d', strtotime($fin)));
		    	$cursoDO->setINumeroAlumnos($alumnos);
		    	$cursoDO->setLastModified(date('Y-m-d'));
                $cursoDO->setModUser($this->usuario->getNombre());
		    	
		    	if ( $editar ){
		    		$correcto = $cursoDO->update();
		    	} else {
		    		$correcto = $cursoDO->insert();
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
    
    
}

?>