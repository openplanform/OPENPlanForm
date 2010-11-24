<?php

require_once 'helper/NingenCmsHtmlHelper.inc';
require_once 'NingenPaginator.inc';

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';

require_once NINGENCMS_MODELDIR . '/TblAula.inc';
require_once NINGENCMS_MODELDIR . '/TblCentro.inc';
require_once NINGENCMS_MODELDIR . '/TblPais.inc';
require_once NINGENCMS_MODELDIR . '/TblProvincia.inc';

class aulaController extends PplController{
    
    
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
    		'cap'	=> 'iCapacidad',
    		'cen'	=> 'fkCentro',
    		'nom' 	=> 'vNombre',
	    	'dir'	=> 'vDireccion'
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
     * Da de alta un aula
     */
    public function altaAction(){
        
    	// Paises
        $this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
        
        // Provincias
        $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
        
        // Centros
        $this->view->centrosIDX = $this->cacheBO->getCentros();
        
   		// Doy de alta el aula
    	if ( $this->helper->get('send') ){
    		
   			if ( $this->actualizarInsertar() ){
   				
   				// Todo ha ido bien
    			$this->redirectTo('aula', 'index');
					
   			} else {

   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con el alta del aula. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
					
   			}
    	}

    }
    
    /**
     * Acción de edición
     * Edita un aula
     */
    public function editarAction(){
        
//    	// Obtengo el centro que voy a editar
//    	$paramsARR = $this->getParams();
//        if ( !empty($paramsARR) ){
//        	
//        	// Aula
//            if (!$aulaDO = TblAula::findByPrimaryKey($this->db, $paramsARR[0])){
//                $this->redirectTo('aula', 'index');
//                return;
//            }
//            
//        	$this->view->aulaDO = $aulaDO;
//        	
//        	// Paises
//	        $this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
//	        
//	        // Provincias
//	        $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
//	        
//	        // Centros
//	        $this->view->centrosIDX = $this->cacheBO->getCentros();
//	    	
//        }
//        
//    	// Actualizo el centro
//    	if ( isset($aulaDO) && $this->helper->get('send') ){
//    		
//    		if ( $this->actualizarInsertar(true,$aulaDO->getIdAula() ) ){
//    			
//    			// aula
//        		$aulaDO = TblAula::findByPrimaryKey($this->db, $paramsARR[0]);
//        		$this->view->aulaDO = $aulaDO;
//				
//    		} else {
//    			
//    			$this->view->popup = array(
//				    'estado' => 'ko',
//				    'titulo' => 'Error',
//				    'mensaje'=> 'Ha ocurrido un error con la edición del aula. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
//				    'url'=> '',
//				);
//				
//    		}
//    	}

    	// Obtengo el aula que voy a editar
    	$idAula = $this->getParam(0);
        if ( !is_null($idAula) ){
        	
        	// Aula
            if (!$aulaDO = TblAula::findByPrimaryKey($this->db, $idAula)){
                $this->redirectTo('aula', 'index');
                return;
            }
            
        	$duplicar = false;
        	
        } else {
        	
        	if ( NingenCmsSession::getValue('aulaDuplicado') instanceof TblAula ){
        		
        		$aulaDO = NingenCmsSession::getValue('aulaDuplicado');
        		$duplicar = true;
        		
        	}
        	
        }
        
    	// Actualizo el aula
        if ( isset($aulaDO) && $this->helper->get('send') ){
        	
        	if ( $duplicar ){
    			$correcto = $this->actualizarInsertar();
    		} else {
    			$correcto = $this->actualizarInsertar(true, $aulaDO->getIdAula());
    		}
    		
            if ( $correcto ){
                    
            	if ( $duplicar ){
                	$this->redirectTo('aula','editar', $this->db->getLastInsertId());
            	} else {
                	$aulaDO = TblAula::findByPrimaryKey($this->db, $aulaDO->getIdAula());
            	}
                $this->view->aulaDO = $aulaDO;
                    
			} else {
                    
            	$this->view->popup = array(
                	'estado' => 'ko',
                	'titulo' => 'Error',
                    'mensaje'=> 'Ha ocurrido un error con la edición del aula. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                    'url'=> '',
                );
                    
            }
         }
       
		// Datos para la vista
       	if ( isset($aulaDO) ){
        	
       		$this->view->aulaDO = $aulaDO;
       		
	    	// Paises
	        $this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
	        
	        // Provincias
	        $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
	        
	        // Centros
	        $this->view->centrosIDX = $this->cacheBO->getCentros();
	    	
        }
        
    }
    
	/**
     * Acción de ficha
     * Ficha de un aula
     */
    public function fichaAction(){
        
    	$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$aulaDO = TblAula::findByPrimaryKey($this->db, $paramsARR[0]);
        	
        	$this->view->aulaDO = $aulaDO;
	    	
        }
        
    }
    
	/**
     * Acción de eliminar
     * Elimina un aula
     */
    public function eliminarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$aulaDO = TblAula::findByPrimaryKey($this->db, $paramsARR[0]);
        	$aulaDO->delete();
        	
        }
        
        $this->redirectTo('aula','index');
        
    }
    
	/**
     * Acción de duplicar
     * Duplica un plan
     */
    public function duplicarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$aulaDO = TblAula::findByPrimaryKey($this->db, $paramsARR[0]);
        	$nombreAula = 'Copia de ' . $aulaDO->getVNombre();
        	$aulaDO->setVNombre($nombreAula);
//        	$aulaDO->insert();
			NingenCmsSession::setValue('aulaDuplicado', $aulaDO);
        }
        
//        $this->redirectTo('aula','editar', $this->db->getLastInsertId());
        $this->redirectTo('aula','editar');
        
    }
    
	/**
     * Obtiene los datos de aula y realiza el alta o la actualización
     * @param boolean $editar
     * @param intenger $idAula
     * @return boolean $correcto
     */
    public function actualizarInsertar($editar = false, $idAula = '') {
    	
	    $correcto = true;
	    		
     	// Comprobaciones pertinentes
     	
        // Nombre
    	$nombre = $this->helper->escapeInjection($this->helper->get('nombre'));
	    if ( is_null($nombre) || empty($nombre) ){
	    	$correcto = false;
	    	$this->view->errorNombre = 'El nombre no puede estar vacío';
	    }
        
	    // Centro
    	$centro = $this->helper->escapeInjection($this->helper->get('centro'));
	    if ( is_null($centro) || empty($centro) ){
	    	$correcto = false;
	    	$this->view->errorCentro = 'El centro no puede estar vacío';
	    }
	    
	    // Capacidad
    	$capacidad = $this->helper->escapeInjection($this->helper->get('capacidad'));
	    if ( is_null($capacidad) || empty($capacidad) ){
	    	$correcto = false;
	    	$this->view->errorCapacidad = 'La capacidad no puede estar vacía';
	    }
	    
	    // País
    	$pais = $this->helper->escapeInjection($this->helper->get('pais'));
	    if ( is_null($pais) || empty($pais) ){
	    	$pais = null;
	    }
	    
	    // Provincia
    	$provincia = $this->helper->escapeInjection($this->helper->get('provincia'));
	    if ( is_null($provincia) || empty($provincia) ){
	    	$provincia = null;
	    }
	    
	    // Población
    	$poblacion = $this->helper->escapeInjection($this->helper->get('poblacion'));
	    if ( is_null($poblacion) || empty($poblacion) ){
	    	$poblacion = '';
	    }
	    
    	// Dirección
    	$direccion = $this->helper->escapeInjection($this->helper->get('direccion'));
	    if ( is_null($direccion) || empty($direccion) ){
	    	$direccion = '';
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
	    	
	    	// Insertamos o actualizamos un aula
	    	if ( $correcto ){
	    	
		    	if ( $editar ){
		    		$aulaDO = TblAula::findByPrimaryKey($this->db, $idAula);
		    	} else {
		    		$aulaDO = new TblAula($this->db);
		    	}
		    	
		    	$aulaDO->setVNombre($nombre);
		    	$aulaDO->setICapacidad($capacidad);
		    	$aulaDO->setFkCentro($centro);
		    	$aulaDO->setFkPais($pais);
		    	$aulaDO->setFkProvincia($provincia);
		    	$aulaDO->setVPoblacion($poblacion);
		    	$aulaDO->setVDireccion($direccion);
		    	$aulaDO->setVDescripcion($descripcion);
		    	$aulaDO->setLastModified(date('Y-m-d'));
                $aulaDO->setModUser($this->usuario->getNombre());
		    	
		    	if ( $editar ){
		    		$correcto = $aulaDO->update();
		    	} else {
		    		$correcto = $aulaDO->insert();
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
     * Buscar aulas
     */
    public function buscarAction(){
        
        // Paises 
        $this->view->paisesIDX = $this->cacheBO->getPaises();
        
        // Provincias
        $this->view->provinciasIDX = $this->cacheBO->getProvincias();
        
        $sent = $this->helper->getAndEscape('sent');
        if (!empty($sent)){

            // Solo comprobaremos permisos de edición si hay resultados
            if ( $this->aclManager->hasPerms('centro', 'editar') ){
                $this->view->editar = true;
            }
            
            // Parámetros de ordenación para el paginador
	    	$aliasCampos = array(
	    		'cap'	=> 'iCapacidad',
	    		'cen'	=> 'fkCentro',
	    		'nom' 	=> 'vNombre',
	    		'dir'	=> 'vDireccion'
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
            $id = $this->helper->getAndEscape('idCentro');
            $pais = $this->helper->getAndEscape('pais');
            $provincia = $this->helper->getAndEscape('provincia');
            $capacidad = $this->helper->getAndEscape('capacidad');
            $kw = $this->helper->getAndEscape('keyword');
            
            $where = array();
            $queryString = '&amp;sent=1';
            
            // ID
            if (!empty($id)){
                $where[] = " idAula = $id";
                $this->view->id = $id;
                $queryString .= "&amp;idAula=$id";
            }
            
            // PAIS
            if (!empty($pais)){
                $where[] = " fkPais = '$pais'";
                $this->view->pais = $pais;
                $queryString .= "&amp;pais=$pais";
            }

            // PROVINCIA
            if (!empty($provincia)){
                $where[] = " fkProvincia = $provincia";
                $this->view->provincia = $provincia;
                $queryString .= "&amp;provincia=$provincia";
            }

            // CAPACIDAD
            if (!empty($capacidad)){
                $where[] = " iCapacidad = $capacidad";
                $this->view->capacidad = $capacidad;
                $queryString .= "&amp;capacidad=$capacidad";
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
            $paginador = new NingenPaginator($this->db, $where, 'tblAula', $this->helper);
            $paginador->setItemsPorPagina(10);
            $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
            $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
            $paginador->setPaginaActual($paginaActual);
            $paginador->setOrderBy($orderBy);
            $paginador->setOrder($order);
        
            // Obtengo las aulas
            $aulasCOL = $paginador->getItemCollection();
            $this->view->aulasCOL = $aulasCOL;        
            
            // Envío el paginador a la vista
            $this->view->paginador = $paginador->getPaginatorHtml();
            
            // Se propagan las clausulas de búsqueda en el paginador
            $this->view->querystring = $queryString;   

            // Centros
            $this->view->centrosIDX = $this->cacheBO->getCentros();
        
        }        
        
    }
    
    
}

?>