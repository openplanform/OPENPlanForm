<?php

require_once CLASSESDIR . 'PplController.inc';
require_once MODELDIR . 'TblDocumento.inc';
require_once 'helper/OwlHtmlHelper.inc';
require_once 'helper/OwlFile.inc';
require_once 'OwlPaginator.inc';


class documentoController extends PplController{
    
    
    /**
     * Init
     * @see extranet.planespime.es/owl/lib/OwlController::initController()
     */
    public function initController(){
        
        $this->rewriteControllerLabel('administrador');
       
        parent::initController();
        
        // En esta página no utilizaremos layout ni vista,
    	// necesitamos poder controlar los encabezados.
    	if ($this->actionName == 'ver'){
	    	$this->view->bypassView();
	    	$this->bypassLayout();
    	} 
        
    }
    
    /**
     * Acción inicial, por defecto, el listado
     * @see extranet.planespime.es/owl/lib/OwlController::indexAction()
     */
    public function indexAction(){
        
        $sent = $this->helper->getAndEscape('sent');
        $error = false;
        
        // Si el usuario es administrador, podrá subir documentos dinámicos.
        $this->view->isAdmin = $isAdmin = $this->aclManager->getRolMasRelevanteUsuario($this->usuario->getId()) == PplAclManager::ROL_ADMINISTRADOR;
        
        
        if (!empty($sent)){
        	
            $nombre = $this->helper->getAndEscape('nombre');
            $desc = $this->helper->getAndEscape('desc');
            $dinamico = $this->helper->getAndEscape('dinamico');
            $identificador = $this->helper->getAndEscape('identificador');
            
            if (!$archivo = $_FILES['archivo']){
                $error = true;
            }
            
            // Obtengo las variables del archivo
            foreach ($archivo as $key => $value){
                $$key = $value;
            }

            if (!$error){
                
                $this->db->begin();
                
                // Se prepara la tupla
                $documentoDO = new TblDocumento($this->db);
                $documentoDO->setVRealName($name);
                $documentoDO->setVNombre($nombre);
                $documentoDO->setVMime($type);
                $documentoDO->setVTamano($size);
                $documentoDO->setVDescription($desc);
                $documentoDO->setModUser($this->usuario->getNombre());
                $documentoDO->setLastModified(date('Y-m-d'));
                
                // Si el usuario es administrador se evalúa el flag de dinámico
                if ($isAdmin && $dinamico == 'on'){
                	
                	if (empty($identificador)){
                		
                		$this->errorIdentificador = "Si el documento es dinámico, se debe indicar un identificador.";
                		$this->db->rollback();
                		return;
                		
                	}
                	
                	$documentoDO->setBDinamico(true);
                	$documentoDO->setVIdentificador($identificador);
                	
                } else {
                	
					$documentoDO->setBDinamico(false);                	
                	
                }
                
                if (!$documentoDO->insert()){
                    
                    $this->db->rollback();
                    return;
                    
                }                
                
                // Se intenta mover el archivo a su ubicación final ( El nombre se contruirá en base al id de documento, doc_ID)
                if (!move_uploaded_file($tmp_name, PplCacheBO::getUploadDir() . 'doc_' . $this->db->getLastInsertId())){
                    
                    echo ('Error mover');
                    $this->db->rollback();
                    return;
                    
                }
                
                $this->db->commit();
                
                
            } else {
                
                echo ('Error archivo'); 
                return;
                
            }
            
            
        }   
        
        // Parámetros de ordenación para el paginador
        $aliasCampos = array(
            'id'  => 'idDocumento',
            'tipo'   => 'vMime',
            'nom'  => 'vNombre',
            'tif'  => 'vIdentificador',
            'din'  => 'bDinamico',
        );
        
        if ( !empty($_REQUEST) && array_key_exists('o', $_GET) && array_key_exists('ob', $_GET) ){
            $order = $this->helper->escapeInjection($_GET['o']);
            $orderBy = $aliasCampos[$_GET['ob']];
            $aliasOrderBy = $_GET['ob'];
        } else {
            $order   = 'asc';
            $orderBy = 'idDocumento';
            $aliasOrderBy = 'id';
        }
        
        // Envío el orden a la vista
        if ( $order == 'asc' ){
            $this->view->order = 'desc';
        } else {
            $this->view->order = 'asc';
        }
        $this->view->orderBy = $aliasOrderBy;   

        // Se instancia y configura el paginador
        $paginador = new OwlPaginator($this->db, null, 'tblDocumento', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        
        
        $this->view->documentosCOL = $paginador->getItemCollection();
        $this->view->paginador = $paginador->getPaginatorHtml();
        
        
    }
    
    
    /**
     * Elimina un documento
     */
    public function eliminarAction(){
    	
    	$id = $this->getParam(0);
    	
    	if (!is_null($id)){
    		
    		if ($documentoDO = TblDocumento::findByPrimaryKey($this->db, $id)){
    			
    			$this->db->begin();
    			
    			// Se borra el archivo de la base de datos
    			if (!$documentoDO->delete()){
    				
    				$this->db->rollback();
	                $this->view->popup = array(
	                    'estado' => 'ko',
	                    'titulo' => 'Error',
	                    'mensaje'=> 'Ha ocurrido un error al eliminar el documento de la base de datos. Por favor intente nuevamente.',
	                    'url'=> '',
	                );
	                
	                return;
    				
    			} else {
    				
    				// Se borra el archivo del sistema
    				$path = $this->cacheBO->getUploadDir() . 'doc_' . $id;
    				
    				$error = !file_exists($path);
					$error = !unlink($path);
					
					if ($error){
						
						// KO
	    				$this->db->rollback();
		                $this->view->popup = array(
		                    'estado' => 'ko',
		                    'titulo' => 'Error',
		                    'mensaje'=> 'Ha ocurrido un error al eliminar el documento del sistema. Por favor intente nuevamente.',
		                    'url'=> '',
		                );
	
		                return;						
						
					} else {
						
						// OK
						$this->db->commit();
						$this->redirectTo('documento');
						
					}
    				
    			}
    			
    			
    		} else {
    			
    			// El documento no existe
    			$this->redirectTo('documento');
    			
    		}
    		
    		
    	} else {
    		
    		// No hay clave
    		$this->redirectTo('documento');
    		
    	}
    	
    }
    
    
	/**
	 * Muestra un documento
	 *  
	 * np: En esta página si no nos llega una clave no mostraremos ningun error,
	 * pero tampoco redirigiremos, ya que puede ser llamada desde otros sitios
	 */
    public function verAction(){
    	
    	$id = $this->getParam(0);
    	
    	// Hay clave
    	if (!is_null($id)){
    		
    		// Existe el doc?
			if ($documentoDO = TblDocumento::findByPrimaryKey($this->db, $id)){

				// Datos del archivo
				$docPath = $this->cacheBO->getUploadDir() . 'doc_' . $id;
				$fileMan = new OwlFile();
				$ext = $fileMan->getExtension($documentoDO->getVMime()); 
				$fileSize = filesize($docPath);

				// Mostramos el documento
				$fileMan->outputFile($documentoDO->getVMime(), $fileSize, 'doc_' . $id . '.' . $ext, $docPath);
				
			}    		
    		
    	}
    	
    }
    
}

?>