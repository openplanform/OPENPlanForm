<?php

require_once CLASSESDIR . 'PplController.inc';
require_once 'OwlPaginator.inc';
require_once 'helper/OwlString.inc';

require_once MODELDIR . '/TblDesiderata.inc';

class sugerenciaController extends PplController{

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
        
    /**
		 * 1. Obtenemos el objeto en caso de ser una edición
		 * 2. Comprobamos si se ha enviado el formulario
		 * 	2.1. Alta
		 * 	2.2. Editar
		 * 3. Obtenemos los datos del paginador
		 * 4. Lo enviamos todo a la vista
		 */
		
		// 1. Obtenemos el objeto en caso de ser una edición
		$idSugerencia = $this->getParam(0);
		if ( !is_null($idSugerencia) ){
			$sugerenciaDO = TblDesiderata::findByPrimaryKey($this->db, $idSugerencia);
			$this->view->sugerenciaDO = $sugerenciaDO;
		}
		
		// 2. Comprobamos si se ha enviado el formulario
        if ( array_key_exists(md5('send'), $_POST) ){
        	
        	$correcto = true;
        	$descripcion = $this->helper->getAndEscape('descripcion');
        	if ( empty($descripcion) ){
        		$correcto = false;
        		$this->view->errorDescripcion = "La descripción no puede estar vacía";
        	}
        	
        	if ( $correcto ){
        	
        		$this->db->begin();
        		
	        	// 2.1. Alta
	        	if ( $correcto && $_POST[md5('send')] == md5('alta') ) {
	        		$sugerenciaDO = new TblDesiderata($this->db);
	        		$sugerenciaDO->setFkPersona($this->usuario->getId());
	        		$sugerenciaDO->setVDescripcion($descripcion);
	        		if ( !$sugerenciaDO->insert() ){
	        			$correcto = false;
	        		}
	        	}
	        	
	        	// 2.2. Editar
	        	if ( $correcto && $_POST[md5('send')] == md5('editar') ) {
	        		$sugerenciaDO = TblDesiderata::findByPrimaryKey($this->db, $idSugerencia);
	        		$sugerenciaDO->setVDescripcion($descripcion);
	        		if ( !$sugerenciaDO->update() ){
	        			$correcto = false;
	        		}
	        		// Pasamos a la vista el objeto editado
	        		$this->view->sugerenciaDO = $sugerenciaDO;
	        	}
	        	
	        	if ( $correcto ){
	        		$this->db->commit();
	        	} else {
	        		$this->db->rollback();
	        	}
	        	
        	}
        	
        }
        
    	// 3. Obtenemos los datos del paginador
    	$aliasCampos = array(
    		'id'	=> 'idDesiderata',
    		'desc' 	=> 'vDescripcion',
    		'per'	=> 'fkPersona'
    	);
    	
        if ( !empty($_REQUEST) && array_key_exists('o', $_GET) & array_key_exists('ob', $_GET) ){
        	$order = $this->helper->escapeInjection($_GET['o']);
        	$orderBy = $aliasCampos[$_GET['ob']];
        	$aliasOrderBy = $_GET['ob'];
        } else {
    		$order	 = 'asc';
    		$orderBy = 'idDesiderata';
    		$aliasOrderBy = 'desc';
        }
        
        // Envío el orden a la vista
        if ( $order == 'asc' ){
        	$this->view->order = 'desc';
        } else {
        	$this->view->order = 'asc';
        }
        $this->view->orderBy = $aliasOrderBy;
        
    	// Se instancia y configura el paginador
        $paginador = new OwlPaginator($this->db, null, 'tblDesiderata', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo las academias
        $sugerenciasCOL = $paginador->getItemCollection();
        
        // 4. Lo enviamos todo a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Sugerencias
        $this->view->sugerenciasCOL = $sugerenciasCOL;
        
        // Personas
        $this->view->personasIDX = $this->cacheBO->getPersonas();
        
    	if ( $this->aclManager->hasPerms('sugerencia', 'editar') ){
    		$this->view->editar = true;
    	}
        
    }
    
    /**
     * Acción de eliminar
     */
    public function eliminarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$centroDO = TblDesiderata::findByPrimaryKey($this->db, $paramsARR[0]);
        	$centroDO->delete();
        	
        }
        
        $this->redirectTo('sugerencia','index');
        
    }
    
    
}

?>