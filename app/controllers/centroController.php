<?php

require_once 'helper/OwlHtmlHelper.inc';
require_once 'OwlPaginator.inc';
require_once 'OwlGoogleMaps.inc';

require_once CLASSESDIR . 'PplController.inc';
require_once CLASSESDIR . 'PplCacheBO.inc';

require_once MODELDIR . '/TblCentro.inc';
require_once MODELDIR . '/TblPais.inc';
require_once MODELDIR . '/TblProvincia.inc';

class centroController extends PplController{
    
    
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
        $paginador = new OwlPaginator($this->db, null, 'tblCentro', $this->helper);
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
        
        // Mapa para las coordenadas
        $this->view->cabeceraMapa = OwlGoogleMaps::echoCabeceraMapa();
        $mapaDO = new OwlGoogleMaps();
        $mapaDO->setLatitud('39.57420604477404');
		$mapaDO->setLongitud('2.655208557844162');
		$mapaDO->setMarcadorCoordenadas(true);
        $this->view->mapa = $mapaDO->echoMapa();
        
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
        
//    	// Obtengo el centro que voy a editar
//    	$paramsARR = $this->getParams();
//        if ( !empty($paramsARR) ){
//        	
//        	// Centro
//            if (!$centroDO = TblCentro::findByPrimaryKey($this->db, $paramsARR[0])){
//                $this->redirectTo('centro', 'index');
//                return;
//            }
//            
//        	$this->view->centroDO = $centroDO;
//        	
//        	// Paises
//	        $this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
//	        
//	        // Provincias
//	        $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
//	        
//	        // Empresas
//	        $this->view->academiasIDX = $this->cacheBO->getAcademias();
//	    	
//        }
//        
//    	// Actualizo el centro
//    	if ( isset($centroDO) && $this->helper->get('send') ){
//    		
//    		if ( $this->actualizarInsertar(true,$centroDO->getIdCentro() ) ){
//    			
//    			// centro
//        		$centroDO = TblCentro::findByPrimaryKey($this->db, $paramsARR[0]);
//        		$this->view->centroDO = $centroDO;
//				
//    		} else {
//    			
//    			$this->view->popup = array(
//				    'estado' => 'ko',
//				    'titulo' => 'Error',
//				    'mensaje'=> 'Ha ocurrido un error con la edición del Centro. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
//				    'url'=> '',
//				);
//				
//    		}
//    	}

    	// Obtengo el centro que voy a editar
    	$idCentro = $this->getParam(0);
        if ( !is_null($idCentro) ){
        	
        	// Centro
            if (!$centroDO = TblCentro::findByPrimaryKey($this->db, $idCentro)){
                $this->redirectTo('centro', 'index');
                return;
            }
            
        	$duplicar = false;
        	
        } else {
        	
        	if ( OwlSession::getValue('centroDuplicado') instanceof TblCentro ){
        		
        		$centroDO = OwlSession::getValue('centroDuplicado');
        		$duplicar = true;
        		
        	}
        	
        }
        
    	// Actualizo el centro
        if ( isset($centroDO) && $this->helper->get('send') ){
        	
        	if ( $duplicar ){
    			$correcto = $this->actualizarInsertar();
    		} else {
    			$correcto = $this->actualizarInsertar(true, $centroDO->getIdCentro());
    		}
    		
            if ( $correcto ){
                    
            	if ( $duplicar ){
                	$this->redirectTo('centro','editar', $this->db->getLastInsertId());
            	} else {
                	$centroDO = TblCentro::findByPrimaryKey($this->db, $centroDO->getIdCentro());
            	}
                $this->view->centroDO = $centroDO;
                    
			} else {
                    
            	$this->view->popup = array(
                	'estado' => 'ko',
                	'titulo' => 'Error',
                    'mensaje'=> 'Ha ocurrido un error con la edición del centro. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                    'url'=> '',
                );
                    
            }
         }
       
		// Datos para la vista
       	if ( isset($centroDO) ){
        	
       		$this->view->centroDO = $centroDO;
       		
        	// Paises
	        $this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
	        
	        // Provincias
	        $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
	        
	        // Empresas
	        $this->view->academiasIDX = $this->cacheBO->getAcademias();
	    	
	        // Mapa para las coordenadas
	        $this->view->cabeceraMapa = OwlGoogleMaps::echoCabeceraMapa();
	        $mapaDO = new OwlGoogleMaps();
	        $latitud = $centroDO->getVLatitud();
	        $longitud = $centroDO->getVLongitud();
	        
	        // El marcador sólo lo ponemos si el usuario introdujo previamente las coordenadas
    		if ( !empty($latitud) && !empty($longitud) ){
				$mapaDO->addMarcador('marcador', $latitud, $longitud);
			}
			
			// Ponemos la latitud y longitud por defecto
	        $latitud = empty($latitud) ? OwlGoogleMaps::LATITUD : $latitud;
	        $longitud = empty($longitud) ? OwlGoogleMaps::LONGITUD : $longitud;
	        
	        $mapaDO->setLatitud( $latitud );
			$mapaDO->setLongitud( $longitud );
			$mapaDO->setMarcadorCoordenadas(true);
	        $this->view->mapa = $mapaDO->echoMapa();
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
//        	$centroDO->insert();
        	OwlSession::setValue('centroDuplicado', $centroDO);
        }
        
//        $this->redirectTo('centro','editar', $this->db->getLastInsertId());
        $this->redirectTo('centro','editar');
        
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

	    // Población
    	$poblacion = $this->helper->escapeInjection($this->helper->get('poblacion'));
	    if ( is_null($poblacion) || empty($poblacion) ){
	    	$poblacion = '';
	    }
	    
    	// Latitud
    	$latitud = $this->helper->escapeInjection($this->helper->get('latitud'));
	    if ( is_null($latitud) || empty($latitud) ){
	    	$latitud = '';
	    }
	    
	    // Longitud
    	$longitud = $this->helper->escapeInjection($this->helper->get('longitud'));
	    if ( is_null($longitud) || empty($longitud) ){
	    	$longitud = '';
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
		    	$centroDO->setVPoblacion($poblacion);
		    	$centroDO->setVLatitud($latitud);
		    	$centroDO->setVLongitud($longitud);
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
    
    /**
     * Buscar centros
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
                'nom'   => 'vNombre',
                'dir'   => 'vDireccion',
                'pob'   => 'vPoblacion',
                'tel'   => 'vTelefono'
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
            $cif = $this->helper->getAndEscape('cif');
            $cp = $this->helper->getAndEscape('cp');
            $kw = $this->helper->getAndEscape('keyword');
            
            $where = array();
            $queryString = '&amp;sent=1';
            $queryARR['sent'] = 1;
            
            // ID
            if (!empty($id)){
                $where[] = " idCentro = $id";
                $this->view->id = $id;
//                $queryString .= "&amp;idCentro=$id";
                $queryARR['idCentro'] = $id;
            }
            
            // PAIS
            if (!empty($pais)){
                $where[] = " fkPais = '$pais'";
                $this->view->pais = $pais;
//                $queryString .= "&amp;pais=$pais";
                $queryARR['pais'] = $pais;
            }

            // PROVINCIA
            if (!empty($provincia)){
                $where[] = " fkProvincia = $provincia";
                $this->view->provincia = $provincia;
//                $queryString .= "&amp;provincia=$provincia";
                $queryARR['provincia'] = $provincia;
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
            $paginador = new OwlPaginator($this->db, $where, 'tblCentro', $this->helper);
            $paginador->setItemsPorPagina(10);
            $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
            $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
            $paginador->setPaginaActual($paginaActual);
            $paginador->setOrderBy($orderBy);
            $paginador->setOrder($order);
//            $paginador->setExtraParams($queryString);
            $paginador->setExtraParams($queryARR);
        
            // Obtengo los centros
            $centrosCOL = $paginador->getItemCollection();
            $this->view->centrosCOL = $centrosCOL;        
            
            // Envío el paginador a la vista
            $this->view->paginador = $paginador->getPaginatorHtml();
            
            // Se propagan las clausulas de búsqueda en el paginador
        	foreach ( $queryARR as $clave => $valor ){
            	$queryString .= '&amp;' . $clave . '=' . $valor;
            }
            $this->view->querystring = $queryString;        
        
        }
    
    }

}
?>