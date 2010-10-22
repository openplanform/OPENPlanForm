<?php
require_once 'helper/NingenNumeric.inc';
require_once 'NingenPaginator.inc';

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';

require_once NINGENCMS_MODULEDIR . 'menuPrincipalModule.php';
require_once NINGENCMS_MODULEDIR . 'logoutModule.php';
require_once NINGENCMS_MODULEDIR . 'barraHerramientasModule.php';

require_once NINGENCMS_MODELDIR . '/TblConvocatoria.inc';
require_once NINGENCMS_MODELDIR . '/TblRequisito.inc';
require_once NINGENCMS_MODELDIR . '/TrelRequisitoConvocatoria.inc';
require_once NINGENCMS_MODELDIR . '/TblTipoConvocatoria.inc';

class convocatoriaController extends PplController{
    
    
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
    		'nom' 	=> 'vNombre',
    		'desc'	=> 'vDescripcion',
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
        $paginador = new NingenPaginator($this->db, null, 'tblConvocatoria', $this->helper);
        $paginador->setItemsPorPagina(10);
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
        $this->view->arrConvocatoriasDO = $convocatoriasCOL;
        
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
        
    	$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$convocatoriaDO = TblConvocatoria::findByPrimaryKey($this->db, $paramsARR[0]);
        	
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
        	
        }
        
    }
    
    /**
     * Acción de edición
     * Edita una convocatoria
     */
    public function editarAction(){
        
    	// Obtengo la convocatoria que voy a editar
    	$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	// Convocatoria
        	$convocatoriaDO = TblConvocatoria::findByPrimaryKey($this->db, $paramsARR[0]);
        	$this->view->convocatoriaDO = $convocatoriaDO;
        	
	    	// Tipos de Convocatoria
	    	$this->view->tiposConvocatoriaIDX = $this->cacheBO->getTiposConvocatoria();
	    	
	    	// Requisitos
	    	$this->view->requisitosIDX = $this->cacheBO->getRequisitos();
	    	
	    	// Requisitos de la convocatoria
	    	$this->view->requisitosConvocatoriaDO = $convocatoriaDO->getTrelRequisitoConvocatorias();
	    	
        }
        
    	// Actualizo la convocatoria
    	if ( isset($convocatoriaDO) && $this->helper->get('send') ){
    		
    		if ( $this->actualizarInsertar(true,$convocatoriaDO->getIdConvocatoria() ) ){
    			
    			// Todo ha ido bien
    			$this->redirectTo('convocatoria', 'index');
				
    		} else {
    			
    			$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con la edición de la convocatoria. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
				
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
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$convocatoriaDO = TblConvocatoria::findByPrimaryKey($this->db, $paramsARR[0]);
        	$nombreConvocatoria = 'Copia de ' . $convocatoriaDO->getVNombre();
        	$convocatoriaDO->setVNombre($nombreConvocatoria);
        	$convocatoriaDO->insert();
        }
        
        $this->redirectTo('convocatoria','editar', $this->db->getLastInsertId());
        
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
	    		
		// Tipo
		$tipo = $this->helper->escapeInjection($this->helper->get('tipoConvocatoria'));
	    if ( is_null($tipo) || empty($tipo) ){
	    	$correcto = false;
	    	$this->view->errorTipo = 'El tipo no puede estar vacío';
	    }
	    		
		// Descripción
		$descripcion = $this->helper->escapeInjection($this->helper->get('descripcion'));
	    if ( is_null($descripcion) ){
	    	$descripcion = '';
	    }
	    		
		// Presupuesto
		$presupuesto = $this->helper->escapeInjection($this->helper->get('presupuesto'));
	    if ( is_null($presupuesto) || empty($presupuesto) ){
	    	$correcto = false;
	    	$this->view->errorPresupuesto = 'El presupuesto no puede estar vacío';
	    } else if ( !NingenNumeric::currencyEuro($presupuesto) ) {
	    	$correcto = false;
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
	    	$convocatoriaDO->setVDescripcion($descripcion);
	    	$convocatoriaDO->setFkTipoConvocatoria($tipo);
	    	$convocatoriaDO->setEPresupuesto(NingenNumeric::formatoEuropeoDecimal($presupuesto, 2));
	    	
	    	// Empieza la transacción
	    	$this->db->begin();
	    	
	    	if ( $editar ){
	    		$correcto = $convocatoriaDO->update();
	    	} else {
	    		$correcto = $convocatoriaDO->insert();
	    	} 
	    	
	    	if ( $correcto ){
	    		
	    		// Requisitos de la convocatoria
	    		if ( !empty($arrIdsRequisitos) ){
	    			
	    			if ( $editar ){
		    			// Borramos los requisitos antiguos
		    			$sql = "DELETE FROM trelRequisitoConvocatoria WHERE fkConvocatoria = ".$idConvocatoria;
		    			$this->db->executeQuery($sql);
	    			} else {
	    				$idConvocatoria = $this->db->getLastInsertId();
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