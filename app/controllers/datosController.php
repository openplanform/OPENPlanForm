<?php
require_once 'OwlPaginator.inc';

require_once CLASSESDIR . 'PplController.inc';

require_once MODELDIR . 'TblCarnetConducir.inc';

class datosController extends PplController{
	
	
	public function indexAction(){
		
	}
	
	/**
     * Init
     * @see extranet.planespime.es/owl/lib/OwlController::initController()
     */
	public function initController(){
		parent::initController();
	}
	
	/**
	 * Gestiona los carnets de conducir
	 */
	public function carnetAction(){
		
		/**
		 * 1. Obtenemos el objeto en caso de ser una edición
		 * 2. Comprobamos si se ha enviado el formulario
		 * 	2.1. Alta
		 * 	2.2. Editar
		 * 3. Obtenemos los datos del paginador
		 * 4. Lo enviamos todo a la vista
		 */
		
		// 1. Obtenemos el objeto en caso de ser una edición
		$idCarnet = $this->getParam(0);
		if ( !is_null($idCarnet) ){
			$carnetDO = TblCarnetConducir::findByPrimaryKey($this->db, $idCarnet);
		}
		
		// 2. Comprobamos si se ha enviado el formulario
        if ( array_key_exists(md5('send'), $_POST) ){
        	
        	$correcto = true;
        	$nombre = $this->helper->getAndEscape('nombre');
        	$descripcion = $this->helper->getAndEscape('descripcion');
        	
        	if ( empty($nombre) ){
        		$correcto = false;
        		$this->view->errorNombre = "El nombre no puede estar vacío";
        	}
        	
        	if ( empty($descripcion) ){
        		$correcto = false;
        		$this->view->errorDescripcion = "La descripción no puede estar vacía";
        	}
        	
        	if ( $correcto ){
        	
        		$this->db->begin();
        		
	        	// 2.1. Alta
	        	if ( $correcto && $_POST[md5('send')] == md5('alta') ) {
	        		$carnetDO = new TblCarnetConducir($this->db);
	        		$carnetDO->setVNombre($nombre);
	        		$carnetDO->setVDescripcion($descripcion);
	        		if ( !$carnetDO->insert() ){
	        			$correcto = false;
	        		}
	        	}
	        	
	        	// 2.2. Editar
	        	if ( $correcto && $_POST[md5('send')] == md5('editar') ) {
	        		$carnetDO = TblCarnetConducir::findByPrimaryKey($this->db, $idCarnet);
	        		$carnetDO->setVNombre($nombre);
	        		$carnetDO->setVDescripcion($descripcion);
	        		if ( !$carnetDO->update() ){
	        			$correcto = false;
	        		}
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
    		'nom' 	=> 'vNombre',
	    	'desc'	=> 'vDescripcion'
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
        $paginador = new OwlPaginator($this->db, null, 'tblCarnetConducir', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo los carnets
        $carnetsCOL = $paginador->getItemCollection();
        
        // 4. Lo enviamos todo a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío los carnets
        $this->view->carnetsCOL = $carnetsCOL;
        
        // Envío el carnet para editar
        if ( !empty($carnetDO) ){
        	$this->view->carnetDO = $carnetDO;
        }
        
	}
	
	/**
	 * Elimina un elemento pasado por la url
	 */
	public function eliminarAction(){
		
		// Item a eliminar
		$item = $this->getParam(0);
		
		// Id del item a eliminar
		$id = $this->getParam(1);
		
		if ( !is_null($id) ){
			
			// Buscamos el item
			switch ( $item ){
				
				case 'carnet':
					$itemDO = TblCarnetConducir::findByPrimaryKey($this->db, $id);
					break;
				
			}
			
			// Eliminamos el item
			if ( !empty($itemDO) ){
				$itemDO->delete();
			}
		}
		
		$this->redirectTo('datos', $item);
		
	}
	
}

?>