<?php
require_once 'helper/OwlNumeric.inc';
require_once 'helper/OwlString.inc';
require_once 'OwlPaginator.inc';

require_once CLASSESDIR . 'PplController.inc';

require_once MODULEDIR . 'menuPrincipalModule.php';
require_once MODULEDIR . 'logoutModule.php';
require_once MODULEDIR . 'barraHerramientasModule.php';

require_once MODELDIR . '/TblConvocatoria.inc';
require_once MODELDIR . '/TblRequisito.inc';
require_once MODELDIR . '/TrelRequisitoConvocatoria.inc';
require_once MODELDIR . '/TblTipoConvocatoria.inc';
require_once MODELDIR . '/TrelDocumentoConvocatoria.inc';

class convocatoriaController extends PplController{
    
    
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
    	    'anyo'  => 'iAno',
    		'nom' 	=> 'vNombre',
    		'pres'	=> 'ePresupuesto',
    		'tipo'	=> 'fkTipoConvocatoria'
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
        $paginador = new OwlPaginator($this->db, null, 'tblConvocatoria', $this->helper);
        $paginador->setItemsPorPagina(20);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
        // Obtengo las convocatorias
        $convocatoriasCOL = $paginador->getItemCollection();
        
        // Envío el paginador a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Convocatorias
        $this->view->convocatoriasCOL = $convocatoriasCOL;
        
        // Tipos de Convocatoria
    	$this->view->tiposConvocatoriaIDX = $this->cacheBO->getTiposConvocatoria();
        
    	if ( $this->aclManager->hasPerms('convocatoria', 'editar') ){
    		$this->view->editar = true;
    	}
    	
    }
    
    /**
     * Acción de alta
     * Da de alta una convocatoria
     */
    public function altaAction(){

    	// Tipos de Convocatoria
    	$this->view->tiposConvocatoriaIDX = $this->cacheBO->getTiposConvocatoria();
    	
    	// Requisitos
    	$this->view->requisitosIDX = $this->cacheBO->getRequisitos();
    	
		// Obtengo los documentos dinamicos disponibles
    	$this->view->docsDinamicosCOL = $docsDinamicosCOL = $this->cacheBO->getDocumentosDinamicos();    	

    	// Doy de alta la convocatoria
    	if ( $this->helper->get('send') ){
    		
   			if ( $this->actualizarInsertar() ){
   				
   				// Todo ha ido bien
    			$this->redirectTo('convocatoria', 'index');
					
   			} else {

   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con el alta de Convocatoria. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
					
   			}
    	}
    	
    }
    
    
    /**
     * Acción de ficha
     * Ficha de una convocatoria
     */
    public function fichaAction(){
        
    	$idConvocatoria = $this->getParam(0);
    	
        if ( !is_null($idConvocatoria) ){
        	
        	$convocatoriaDO = TblConvocatoria::findByPrimaryKey($this->db, $idConvocatoria);
        	
        	$this->view->convocatoriaDO = $convocatoriaDO;
        	
        	// Tipos de Convocatoria
    		$this->view->tiposConvocatoriaIDX = $this->cacheBO->getTiposConvocatoria();
    		
    		// Requisitos de la convocatoria
    		$arrRequisitosConvocatoriaDO = $convocatoriaDO->getTrelRequisitoConvocatorias();
    		if ( !empty($arrRequisitosConvocatoriaDO) ){
    			$this->view->arrRequisitosConvocatoriaDO = $convocatoriaDO->getTrelRequisitoConvocatorias();
    		}
    		
    		// Requisitos
    		$this->view->requisitosIDX = $this->cacheBO->getRequisitos();
    		
    		// Estados de plan
    		$this->view->estadosPlanIDX = $this->cacheBO->getEstadosPlan();
    		
    		// Documentos dinámicos seleccionados para esta convocatoria
    		$this->view->documentosCOL = $this->cacheBO->getDocumentacionConvocatoria($idConvocatoria);
        	
        }
        
    }
    
    
    /**
     * Acción de edición
     * Edita una convocatoria
     */
    public function editarAction(){
        
    	// Obtengo la convocatoria que voy a editar
    	$idConvocatoria = $this->getParam(0);
        if ( !is_null($idConvocatoria) ){
        	
        	// Convocatoria
            if (!$convocatoriaDO = TblConvocatoria::findByPrimaryKey($this->db, $idConvocatoria)){
                $this->redirectTo('convocatoria', 'index');
                return;
            }
            
        	$duplicar = false;
        	
        } else {
        	
        	if ( OwlSession::getValue('convocatoriaDuplicado') instanceof TblConvocatoria ){
        		
        		$convocatoriaDO = OwlSession::getValue('convocatoriaDuplicado');
        		$duplicar = true;
        		
        	}
        	
        }

        // Obtengo los documentos dinamicos disponibles
    	$this->view->docsDinamicosCOL = $docsDinamicosCOL = $this->cacheBO->getDocumentosDinamicos();
        
    	// Actualizo la convocatoria
        if ( isset($convocatoriaDO) && $this->helper->get('send') ){
        	
        	if ( $duplicar ){
    			$correcto = $this->actualizarInsertar();
    		} else {
    			$correcto = $this->actualizarInsertar(true, $convocatoriaDO->getIdConvocatoria());
    		}
    		
            if ( $correcto ){
                    
            	if ( $duplicar ){
                	$this->redirectTo('convocatoria','editar', $this->db->getLastInsertId());
            	} else {
                	$convocatoriaDO = TblConvocatoria::findByPrimaryKey($this->db, $convocatoriaDO->getIdConvocatoria());
            	}
                $this->view->convocatoriaDO = $convocatoriaDO;
                    
			} else {
                    
            	$this->view->popup = array(
                	'estado' => 'ko',
                	'titulo' => 'Error',
                    'mensaje'=> 'Ha ocurrido un error con la edición de la convocatoria. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                    'url'=> '',
                );
                    
            }
       }
       
		// Datos para la vista
       	if ( isset($convocatoriaDO) ){
        	
       		$this->view->convocatoriaDO = $convocatoriaDO;
       		
	    	// Tipos de Convocatoria
	    	$this->view->tiposConvocatoriaIDX = $this->cacheBO->getTiposConvocatoria();
	    	
	    	// Requisitos
	    	$this->view->requisitosIDX = $this->cacheBO->getRequisitos();
	    	
	    	// Requisitos de la convocatoria
	    	if ( !$duplicar ){
	    		$this->view->requisitosConvocatoriaDO = $convocatoriaDO->getTrelRequisitoConvocatorias();
	    	}
	    	
       	    // Obtengo los documentos dinámicos actualmente ASIGNADOS a la convocatoria
		    $documentosConvocatoriaCOL = TrelDocumentoConvocatoria::findByTblConvocatoria($this->db, $idConvocatoria);
		    if (count($documentosConvocatoriaCOL)){
				$this->view->documentosConvocatoriaIDX = OwlDatabase::indexFor('fkDocumento', $documentosConvocatoriaCOL);
	    	}	    	
	    	
        }
    	
    }
    
    
	/**
     * Acción de eliminar
     * Elimina una convocatoria
     */
    public function eliminarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$convocatoriaDO = TblConvocatoria::findByPrimaryKey($this->db, $paramsARR[0]);
        	$convocatoriaDO->delete();
        	
        }
        
        $this->redirectTo('convocatoria','index');
        
    }
    
    
	/**
     * Acción de duplicar
     * Duplica una convocatoria
     */
    public function duplicarAction(){
        
        $idConvocatoria = $this->getParam(0);
        if ( !is_null($idConvocatoria) ){
        	
        	$convocatoriaDO = TblConvocatoria::findByPrimaryKey($this->db, $idConvocatoria);
        	$nombreConvocatoria = 'Copia de ' . $convocatoriaDO->getVNombre();
        	$convocatoriaDO->setVNombre($nombreConvocatoria);
//        	$convocatoriaDO->insert();
			OwlSession::setValue('convocatoriaDuplicado', $convocatoriaDO);
        }
        
//        $this->redirectTo('convocatoria','editar', $this->db->getLastInsertId());
        $this->redirectTo('convocatoria','editar');
        
    }
    
    
    /**
     * Obtiene los datos de convocatoria y realiza el alta o la actualización
     * @param boolean $editar
     * @param intenger $idConvocatoria
     * @return boolean $correcto
     */
    public function actualizarInsertar($editar = false, $idConvocatoria = '') {
    	
	    $correcto = true;
	    		
	    // Nombre
	    $nombre = $this->helper->escapeInjection($this->helper->get('nombre'));
	    if ( is_null($nombre) || empty($nombre) ){
	    	$correcto = false;
	    	$this->view->errorNombre = 'El nombre no puede estar vacío';
	    }

	     // Año
	    $ano = $this->helper->escapeInjection($this->helper->get('ano'));
	    if ( is_null($ano) || empty($ano) ){
	    	$correcto = false;
	    	$this->view->errorAno = 'El año no puede estar vacío';
	    }
	    
		// Tipo
		$tipo = $this->helper->escapeInjection($this->helper->get('tipoConvocatoria'));
	    if ( is_null($tipo) || empty($tipo) ){
	    	$correcto = false;
	    	$this->view->errorTipo = 'El tipo no puede estar vacío';
	    }
	    		
		// Descripción
		$descripcion = OwlString::escapeFromMceditor($this->helper->get('descripcion'));
	    if ( is_null($descripcion) ){
	    	$descripcion = '';
	    }
	    
		// Presupuesto
		$presupuesto = $this->helper->escapeInjection($this->helper->get('presupuesto'));
	    if ( is_null($presupuesto) || empty($presupuesto) ){
	    	$presupuesto = '';
	    } else if ( !OwlNumeric::currencyEuro($presupuesto) ) {
	    	$this->view->errorPresupuesto = 'El presupuesto no tiene el formato correcto';
	    }
	    		
	    // Requisitos
	    // requisitos: 'requisito_1', 'requisito_5'
		$arrIdsRequisitos = array();
		foreach ( $_REQUEST as $key => $value ) {
			$clave = explode('_', $key);
			if ( $clave[0] == 'requisito' ) {
				array_push($arrIdsRequisitos,$clave[1]);
			}
		}
	    
		// Realiza la actualización o el alta
	    if ( $correcto ){
	    	
	    	if ( $editar ){
	    		$convocatoriaDO = TblConvocatoria::findByPrimaryKey($this->db, $idConvocatoria);
	    	} else {
	    		$convocatoriaDO = new TblConvocatoria($this->db);
	    	}
	    	
	    	$convocatoriaDO->setVNombre($nombre);
	    	$convocatoriaDO->setIAno($ano);
	    	$convocatoriaDO->setVDescripcion($descripcion);
	    	$convocatoriaDO->setFkTipoConvocatoria($tipo);
	    	$convocatoriaDO->setEPresupuesto(OwlNumeric::formatoEuropeoDecimal($presupuesto, 2));
	    	$convocatoriaDO->setLastModified(date('Y-m-d'));
            $convocatoriaDO->setModUser($this->usuario->getNombre());
	    	
	    	// Empieza la transacción
	    	$this->db->begin();
	    	
	    	if ( $editar ){
	    		$correcto = $convocatoriaDO->update();
	    	} else {
	    		$correcto = $convocatoriaDO->insert();
	    		$idConvocatoria = $this->db->getLastInsertId();
	    	}
	    	
	    	if ( $correcto ){
	    		
	    		// Requisitos de la convocatoria
	    		if ( !empty($arrIdsRequisitos) ){
	    			
	    			if ( $editar ){
	    				
		    			$sql = "DELETE FROM trelRequisitoConvocatoria WHERE fkConvocatoria = ".$idConvocatoria;
		    			$this->db->executeQuery($sql);
		    			
	    			} 
	    			
	    			// Insertamos los requisitos
		    		$requisitoConvocatoria = new TrelRequisitoConvocatoria($this->db);
		    		$requisitoConvocatoria->setFkConvocatoria($idConvocatoria);
		    		foreach ($arrIdsRequisitos as $idRequisito) {
		    			$requisitoConvocatoria->setFkRequisito($idRequisito);
		    			if ( !$requisitoConvocatoria->insert() ){
		    				$correcto = false;
				    		break;
		    			}
		    		}
	    		}
	    		
	    		////////////////////////////////////////////////
	    		//											  //
	    		//		    DOCUMENTACIÓN DINÁMICA		      //
	    		//											  //
	    		////////////////////////////////////////////////
	    		
	    		// Documentos seleccionados
	    		$selDocs = array();
	    		
	    		// 1- Recorremos el array de post en busqueda de algún doc dinámico
	    		foreach ($_POST as $key => $value){
	    			if (preg_match('/doc_([0-9]+)/', $key, $claveARR)) {
	    				if (array_key_exists(1, $claveARR)){
	    					if ($value == 'on'){
	    						$selDocs[] = intval($claveARR[1]);
	    					} else {
	    						$delDocs[] = intval($claveARR[1]);
	    					}
	    				}
	    			}
	    		}
	    		
	    		// 2- Eliminaremos la documentación existente
    			$sql = "DELETE FROM trelDocumentoConvocatoria WHERE fkConvocatoria = $idConvocatoria";
    			if (!$this->db->executeQuery($sql)){
    				$correcto = false;
    			}
    			
	    		// 3- Crearemos una tupla por cada documento asignado
	    		foreach ($selDocs as $idDoc){
	    			
	    			$documentoConvocatoriaDO = new TrelDocumentoConvocatoria($this->db);
	    			$documentoConvocatoriaDO->setFkConvocatoria($idConvocatoria);
	    			$documentoConvocatoriaDO->setFkDocumento($idDoc);
	    			
	    			if (!$documentoConvocatoriaDO->insert()){
	    				$correcto = false;
	    				break;
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
     * Buscador de convocatorias
     */
    public function buscarAction(){
        
        // Tipos para el formulario de búsqueda
        $this->view->tiposConvocatoriaIDX = $this->cacheBO->getTiposConvocatoria();
        
        $sent = $this->helper->getAndEscape('sent');
        if (!empty($sent)){

            // Solo comprobaremos permisos de edición si hay resultados
            if ( $this->aclManager->hasPerms('convocatoria', 'editar') ){
                $this->view->editar = true;
            }
            
            // Parámetros de ordenación para el paginador
            $aliasCampos = array(
	    	    'anyo'  => 'iAno',
	    		'nom' 	=> 'vNombre',
	    		'pres'	=> 'ePresupuesto',
	    		'tipo'	=> 'fkTipoConvocatoria'
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
            $id = $this->helper->getAndEscape('idConvocatoria');
            $tipo = $this->helper->getAndEscape('tipoConvocatoria');
            $anyo = $this->helper->getAndEscape('anoConvocatoria');
            $kw = $this->helper->getAndEscape('keyword');
            
            $where = array();
            $queryString = '&amp;sent=1';
            $queryARR['sent'] = 1;
            
            // ID
            if (!empty($id)){
                $where[] = " idConvocatoria = $id";
                $this->view->id = $id;
//                $queryString .= "&amp;idConvocatoria=$id";
                $queryARR['idConvocatoria'] = $id;
            }
            
            // TIPO
            if (!empty($tipo)){
                $where[] = " fkTipoConvocatoria = $tipo";
                $this->view->tipo = $tipo;
//                $queryString .= "&amp;tipoConvocatoria=$tipo";
                $queryARR['tipoConvocatoria'] = $tipo;
            }

            // AÑO
            if (!empty($anyo)){
                $where[] = " iAno = $anyo";
                $this->view->anyo = $anyo;
//                $queryString .= "&amp;anoConvocatoria=$anyo";
                $queryARR['anoConvocatoria'] = $anyo;
            }
            
            // KEYWORD
            if (!empty($kw)){
                $where[] = "vNombre LIKE '%$kw%' OR vDescripcion LIKE '%$kw%'";
                $this->view->kw = $kw;
                $queryString .= "&amp;keyword=$kw";
                $queryARR['keyword'] = $kw;             
            }
            
            // Se constuye el where
            if (count($where)){
                $where = ' WHERE ' . implode(' AND ', $where);
            } else {
                $where = '';
            }
            
            // Se ejecuta la búsqueda
            $paginador = new OwlPaginator($this->db, $where, 'tblConvocatoria', $this->helper);
            $paginador->setItemsPorPagina(10);
            $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
            $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
            $paginador->setPaginaActual($paginaActual);
            $paginador->setOrderBy($orderBy);
            $paginador->setOrder($order);
//            $paginador->setExtraParams($queryString);
            $paginador->setExtraParams($queryARR);
        
            // Obtengo las convocatorias
            $convocatoriasCOL = $paginador->getItemCollection();
            $this->view->convocatoriasCOL = $convocatoriasCOL;        
            
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