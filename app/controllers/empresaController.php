<?php

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';

require_once NINGENCMS_MODULEDIR . 'menuPrincipalModule.php';
require_once NINGENCMS_MODULEDIR . 'logoutModule.php';
require_once NINGENCMS_MODULEDIR . 'barraHerramientasModule.php';


class empresaController extends PplController{
    
    
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
        
    	// Doy de alta la empresa
    	if ( $this->helper->get('send') ){
    		
   			if ( $this->actualizarInsertar() ){
   				
   				// Todo ha ido bien
   				$this->view->popup = array(
				    'estado' => 'ok',
				    'titulo' => 'Correcto',
				    'mensaje'=> 'El alta de Plan se ha realizado correctamente',
				    'url'=> '/plan/index.html',
				);
					
   			} else {

   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con el alta de Plan. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
					
   			}
    	}
    	
    }
    
    /**
     * Acción de alta
     * Da de alta una empresa
     */
    public function altaAction(){
        
        echo 'ALTA';
        
    }
    
    /**
     * Acción de ficha
     * Ficha de una empresa
     */
    public function fichaAction(){
        
        echo 'FICHA';
        
    }
    
/**
     * Obtiene los datos de empresa y realiza el alta o la actualización
     * @param boolean $editar
     * @param intenger $idPlan
     * @return boolean $correcto
     */
    public function actualizarInsertar($editar = false, $idEmpresa = '') {
    	
	    $correcto = true;
	    		
	    // Nombre
	    $nombre = $this->helper->escapeInjection($this->helper->get('nombre'));
	    if ( is_null($nombre) || empty($nombre) ){
	    	$correcto = false;
	    	$this->view->errorNombre = 'El nombre no puede estar vacío';
	    }
	    		
		// Descripción
		$descripcion = $this->helper->escapeInjection($this->helper->get('descripcion'));
	    if ( is_null($descripcion) ){
	    	$descripcion = '';
	    }
	    		
		// Realiza la actualización o el alta
	    if ( $correcto ){
	    	
	    	if ( $editar ){
	    		$empresaDO = TblEmpresa::findByPrimaryKey($this->db, $idEmpresa);
	    	} else {
	    		$empresaDO = new TblEmpresa($this->db);
	    	}
	    	
	    	$convocatoriaDO->setVNombre($nombre);
	    	$convocatoriaDO->setVDescripcion($descripcion);
	    	
	    	// Empieza la transacción
	    	$this->db->begin();
	    	
	    	if ( $editar ){
	    		$correcto = $empresaDO->update();
	    	} else {
	    		$correcto = $empresaDO->insert();
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