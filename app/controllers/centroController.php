<?php

require_once 'helper/NingenCmsHtmlHelper.inc';
require_once 'NingenPaginator.inc';

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';
require_once NINGENCMS_CLASSESDIR . 'PplCacheBO.inc';

require_once NINGENCMS_MODELDIR . '/TblCentro.inc';
require_once NINGENCMS_MODELDIR . '/TblPais.inc';
require_once NINGENCMS_MODELDIR . '/TblProvincia.inc';

class centroController extends PplController{
    
    
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
    		'aca'	=> 'fkEmpresa',
    		'dir'	=> 'vDireccion',
    		'nom' 	=> 'vNombre',
    		'tel'	=> 'vTelefono'
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
        $paginador = new NingenPaginator($this->db, null, 'tblCentro', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo los centros
        $centrosCOL = $paginador->getItemCollection();
        
        // Envío el paginador a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío los centros a la vista
        $this->view->centrosCOL = $centrosCOL;
        
        // Academia del centro
        $this->view->academiasIDX = $this->cacheBO->getAcademias();
        
        // Permiso para editar
    	if ( $this->aclManager->hasPerms('academia', 'editar') ){
    		$this->view->editar = true;
    	}
        
    }
    
    /**
     * Acción de alta
     * Da de alta un centro
     */
    public function altaAction(){
        
    	// Paises
        $this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
        
        // Provincias
        $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
        
        // Empresas
        $this->view->academiasIDX = $this->cacheBO->getAcademias();
        
   		// Doy de alta el centro
    	if ( $this->helper->get('send') ){
    		
   			if ( $this->actualizarInsertar() ){
   				
   				// Todo ha ido bien
    			$this->redirectTo('centro', 'index');
					
   			} else {

   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con el alta del centro. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
					
   			}
    	}
    	
    }

	/**
     * Acción de edición
     * Edita un centro
     */
    public function editarAction(){
        
    	// Obtengo el centro que voy a editar
    	$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	// centro
        	$centroDO = TblCentro::findByPrimaryKey($this->db, $paramsARR[0]);
        	$this->view->centroDO = $centroDO;
        	
        	// Paises
	        $this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
	        
	        // Provincias
	        $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
	        
	        // Empresas
	        $this->view->academiasIDX = $this->cacheBO->getAcademias();
	    	
        }
        
    	// Actualizo el centro
    	if ( isset($centroDO) && $this->helper->get('send') ){
    		
    		if ( $this->actualizarInsertar(true,$centroDO->getIdCentro() ) ){
    			
    			// centro
        		$centroDO = TblCentro::findByPrimaryKey($this->db, $paramsARR[0]);
        		$this->view->centroDO = $centroDO;
				
    		} else {
    			
    			$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con la edición del Centro. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
				
    		}
    	}
        
    }
    
    /**
     * Acción de ficha
     * Ficha de un centro
     */
    public function fichaAction(){
        
    	$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$centroDO = TblCentro::findByPrimaryKey($this->db, $paramsARR[0]);
        	
        	$this->view->centroDO = $centroDO;
	    	
        }
        
    }
    
	/**
     * Acción de eliminar
     * Elimina un centro
     */
    public function eliminarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$centroDO = TblCentro::findByPrimaryKey($this->db, $paramsARR[0]);
        	$centroDO->delete();
        	
        }
        
        $this->redirectTo('centro','index');
        
    }
    
	/**
     * Acción de duplicar
     * Duplica un centro
     */
    public function duplicarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$centroDO = TblCentro::findByPrimaryKey($this->db, $paramsARR[0]);
        	$nombreCentro = 'Copia de ' . $centroDO->getVNombre();
        	$centroDO->setVNombre($nombreCentro);
        	$centroDO->insert();
        }
        
        $this->redirectTo('centro','editar', $this->db->getLastInsertId());
        
    }
    
	/**
     * Obtiene los datos de centro y realiza el alta o la actualización
     * @param boolean $editar
     * @param intenger $idCentro
     * @return boolean $correcto
     */
    public function actualizarInsertar($editar = false, $idCentro = '') {
    	
	    $correcto = true;
	    		
     	// Comprobaciones pertinentes
     	
        // Nombre
    	$nombre = $this->helper->escapeInjection($this->helper->get('nombre'));
	    if ( is_null($nombre) || empty($nombre) ){
	    	$correcto = false;
	    	$this->view->errorNombre = 'El nombre no puede estar vacío';
	    }
        
	    // Academia
    	$academia = $this->helper->escapeInjection($this->helper->get('academia'));
	    if ( is_null($academia) || empty($academia) ){
	    	$correcto = false;
	    	$this->view->errorAcademia = 'La academia no puede estar vacía';
	    }
	    
	    // País
    	$pais = $this->helper->escapeInjection($this->helper->get('pais'));
	    if ( is_null($pais) || empty($pais) ){
	    	$correcto = false;
	    	$this->view->errorPais = 'El pais no puede estar vacío';
	    }
	    
	    // Provincia
    	$provincia = $this->helper->escapeInjection($this->helper->get('provincia'));
	    if ( is_null($provincia) || empty($provincia) ){
	    	$correcto = false;
	    	$this->view->errorProvincia = 'La provincia no puede estar vacía';
	    }
	    
    	// Dirección
    	$direccion = $this->helper->escapeInjection($this->helper->get('direccion'));
	    if ( is_null($direccion) || empty($direccion) ){
	    	$direccion = '';
	    }
	    
	    // Teléfono
    	$telefono = $this->helper->escapeInjection($this->helper->get('telefono'));
	    if ( is_null($telefono) || empty($telefono) ){
	    	$telefono = '';
	    }
	    
    	// Descripción
    	$descripcion = $this->helper->escapeInjection($this->helper->get('descripcion'));
	    if ( is_null($descripcion) || empty($descripcion) ){
	    	$descripcion = '';
	    }
	    
		/**
		 * Insertamos o actualizamos un centro
		 */
	    if ( $correcto ){

	    	// Empieza la transacción
		    $this->db->begin();
	    	
	    	// Insertamos o actualizamos un centro
	    	if ( $correcto ){
	    	
		    	if ( $editar ){
		    		$centroDO = TblCentro::findByPrimaryKey($this->db, $idCentro);
		    	} else {
		    		$centroDO = new TblCentro($this->db);
		    	}
		    	
		    	$centroDO->setVNombre($nombre);
		    	$centroDO->setFkEmpresa($academia);
		    	$centroDO->setFkPais($pais);
		    	$centroDO->setFkProvincia($provincia);
		    	$centroDO->setVDireccion($direccion);
		    	$centroDO->setVDescripcion($descripcion);
		    	$centroDO->setVTelefono($telefono);
		    	$centroDO->setLastModified(date('Y-m-d'));
                $centroDO->setModUser($this->usuario->getNombre());
		    	
		    	if ( $editar ){
		    		$correcto = $centroDO->update();
		    	} else {
		    		$correcto = $centroDO->insert();
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