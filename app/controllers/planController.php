<?php

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';
require_once 'helper/NingenNumeric.inc';
require_once 'NingenPaginator.inc';

require_once NINGENCMS_MODULEDIR . 'menuPrincipalModule.php';
require_once NINGENCMS_MODULEDIR . 'logoutModule.php';
require_once NINGENCMS_MODULEDIR . 'barraHerramientasModule.php';

require_once NINGENCMS_MODELDIR . '/TblConvocatoria.inc';
require_once NINGENCMS_MODELDIR . '/TblPlan.inc';

class planController extends PplController{
    
    
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
    		'con'	=> 'fkConvocatoria',
    		'est'	=> 'fkEstadoPlan',
    		'tipo'	=> 'fkTipoPlan',
    		'prop'	=> 'fkEmpresaPropietaria',
    		'pres'	=> 'ePresupuestoAsignado'
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
        $paginador = new NingenPaginator($this->db, null, 'tblPlan', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo los planes
        $planesCOL = $paginador->getItemCollection();
        
        // Envío el paginador a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Planes
        $this->view->planesCOL = $planesCOL;
        
        // Tipos de Plan
    	$this->view->tiposPlanIDX = $this->cacheBO->getTiposPlan();
    	
    	// Estados de Plan
    	$this->view->estadosPlanIDX = $this->cacheBO->getEstadosPlan();
    	
    	// Convocatorias
    	$this->view->convocatoriasIDX = $this->cacheBO->getConvocatorias();
    	
    	// Empresas
    	$this->view->consultorasIDX = $this->cacheBO->getConsultoras();
        
    	if ( $this->aclManager->hasPerms('convocatoria', 'editar') ){
    		$this->view->editar = true;
    	}
    	
        
    }
    
    /**
     * Acción de alta
     * Da de alta un plan
     */
    public function altaAction(){
        
    	// Tipos de Plan
    	$this->view->tiposPlanIDX = $this->cacheBO->getTiposPlan();
    	
    	// Estados de Plan
    	$this->view->estadosPlanIDX = $this->cacheBO->getEstadosPlan();
    	
    	// Convocatorias
    	$this->view->convocatoriasIDX = $this->cacheBO->getConvocatorias();
    	
    	// Consultoras
    	$this->view->consultorasIDX = $this->cacheBO->getConsultoras();
    	
    	// Doy de alta el plan
    	if ( $this->helper->get('send') ){
    		
   			if ( $this->actualizarInsertar() ){
   				
   				// Todo ha ido bien
    			$this->redirectTo('plan', 'index');
					
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
     * Acción de ficha
     * Ficha de un plan
     */
    public function fichaAction(){
        
    	$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$planDO = TblPlan::findByPrimaryKey($this->db, $paramsARR[0]);
        	
        	$this->view->planDO = $planDO;
        	
        	// Tipos de Plan
	    	$this->view->tiposPlanIDX = $this->cacheBO->getTiposPlan();
	    	
	    	// Estados de Plan
	    	$this->view->estadosPlanIDX = $this->cacheBO->getEstadosPlan();
	    	
	    	// Convocatorias
	    	$this->view->convocatoriasIDX = $this->cacheBO->getConvocatorias();
	    	
	    	// Empresas
	    	$this->view->empresasIDX = $this->cacheBO->getEmpresas();
    		
        }
        
    }
    
	/**
     * Acción de edición
     * Edita un plan
     */
    public function editarAction(){
        
    	// Obtengo el plan que voy a editar
    	$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	// Plan
        	$planDO = TblPlan::findByPrimaryKey($this->db, $paramsARR[0]);
        	$this->view->planDO = $planDO;
        	
	    	// Tipos de Plan
	    	$this->view->tiposPlanIDX = $this->cacheBO->getTiposPlan();
	    	
	    	// Estados de Plan
	    	$this->view->estadosPlanIDX = $this->cacheBO->getEstadosPlan();
	    	
	    	// Convocatorias
	    	$this->view->convocatoriasIDX = $this->cacheBO->getConvocatorias();
	    	
	    	// Consultoras
    		$this->view->consultorasIDX = $this->cacheBO->getConsultoras();
	    	
        }
        
    	// Actualizo el Plan
    	if ( isset($planDO) && $this->helper->get('send') ){
    		
    		if ( $this->actualizarInsertar(true,$planDO->getIdPlan() ) ){
    			
    			// Plan
	        	$planDO = TblPlan::findByPrimaryKey($this->db, $paramsARR[0]);
	        	$this->view->planDO = $planDO;
				
    		} else {
    			
    			$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con la edición del Plan. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
				
    		}
    	}
        
    }
    
	/**
     * Acción de eliminar
     * Elimina un plan
     */
    public function eliminarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$planDO = TblPlan::findByPrimaryKey($this->db, $paramsARR[0]);
        	$planDO->delete();
        	
        }
        
        $this->redirectTo('plan','index');
        
    }
    
	/**
     * Acción de duplicar
     * Duplica un plan
     */
    public function duplicarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$planDO = TblPlan::findByPrimaryKey($this->db, $paramsARR[0]);
        	$nombrePlan = 'Copia de ' . $planDO->getVNombre();
        	$planDO->setVNombre($nombrePlan);
        	$planDO->insert();
        }
        
        $this->redirectTo('plan','editar', $this->db->getLastInsertId());
        
    }
    
    /**
     * Obtiene los datos de plan y realiza el alta o la actualización
     * @param boolean $editar
     * @param intenger $idPlan
     * @return boolean $correcto
     */
    public function actualizarInsertar($editar = false, $idPlan = '') {
    	
	    $correcto = true;
	    		
	    // Nombre
	    $nombre = $this->helper->escapeInjection($this->helper->get('nombre'));
	    if ( is_null($nombre) || empty($nombre) ){
	    	$correcto = false;
	    	$this->view->errorNombre = 'El nombre no puede estar vacío';
	    }

    	// Tipo
		$tipo = $this->helper->escapeInjection($this->helper->get('tipo'));
	    if ( is_null($tipo) || empty($tipo) ){
	    	$correcto = false;
	    	$this->view->errorTipo = 'El tipo no puede estar vacío';
	    }
	    
	    // Convocatoria
		$convocatoria = $this->helper->escapeInjection($this->helper->get('convocatoria'));
	    if ( is_null($tipo) || empty($tipo) ){
	    	$correcto = false;
	    	$this->view->errorConvocatoria = 'La convocatoria no puede estar vacía';
	    }
	    
    	// Estado
		$estado = $this->helper->escapeInjection($this->helper->get('estado'));
	    if ( is_null($tipo) || empty($tipo) ){
	    	$correcto = false;
	    	$this->view->errorEstado = 'El estado no puede estar vacío';
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
	    
    	// Propietario
		$propietario = $this->helper->escapeInjection($this->helper->get('propietario'));
	    if ( is_null($tipo) || empty($tipo) ){
	    	$correcto = false;
	    	$this->view->errorPropietario = 'El propietario no puede estar vacío';
	    }
	    
	    // Consultora
		$consultora = $this->helper->escapeInjection($this->helper->get('consultora'));
	    if ( is_null($tipo) || empty($tipo) ){
	    	$correcto = false;
	    	$this->view->errorConsultora = 'La consultora no puede estar vacía';
	    }
	    
		// Descripción
		$descripcion = $this->helper->escapeInjection($this->helper->get('descripcion'));
	    if ( is_null($descripcion) ){
	    	$descripcion = '';
	    }
	    		
		// Realizamos la actualización o el alta
	    if ( $correcto ){
	    	
	    	if ( $editar ){
	    		$planDO = TblPlan::findByPrimaryKey($this->db, $idPlan);
	    	} else {
	    		$planDO = new TblPlan($this->db);
	    	}
	    	
	    	$planDO->setVNombre($nombre);
	    	$planDO->setFkTipoPlan($tipo);
	    	$planDO->setFkConvocatoria($convocatoria);
	    	$planDO->setFkEstadoPlan($estado);
	    	$planDO->setFkEmpresaPropietaria($propietario);
	    	$planDO->setFkEmpresaConsultora($consultora);
	    	$planDO->setEPresupuestoAsignado(NingenNumeric::formatoEuropeoDecimal($presupuesto, 2));
	    	$planDO->setVDescripcion($descripcion);
	    	$planDO->setLastModified(date('Y-m-d'));
            $planDO->setModUser($this->usuario->getNombre());
            
	    	// Empieza la transacción
	    	$this->db->begin();
	    	
	    	if ( $editar ){
	    		$correcto = $planDO->update();
	    	} else {
	    		$correcto = $planDO->insert();
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
     * Busqueda de planes
     */
    public function buscarAction(){
        
        // Tipos de plan
        $this->view->tiposPlanIDX = $this->cacheBO->getTiposPlan();
        
        // Convocatorias
        $this->view->convocatoriasIDX = $this->cacheBO->getConvocatorias();
        
        // Consultoras
        $this->view->consultorasIDX = $this->cacheBO->getConsultoras();
        
        // Estados de plan
        $this->view->estadosPlanIDX = $this->cacheBO->getEstadosPlan();
        
        
        $sent = $this->helper->getAndEscape('sent');
        if (!empty($sent)){

            // Solo comprobaremos permisos de edición si hay resultados
            if ( $this->aclManager->hasPerms('plan', 'editar') ){
                $this->view->editar = true;
            }
            
            // Parámetros de ordenación para el paginador
            $aliasCampos = array(
                'nom'   => 'vNombre',
                'con'   => 'fkConvocatoria',
                'est'   => 'fkEstadoPlan',
                'tipo'  => 'fkTipoPlan',
                'prop'  => 'fkEmpresaPropietaria',
                'pres'  => 'ePresupuestoAsignado'
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
            $id = $this->helper->getAndEscape('idPlan');
            $tipo = $this->helper->getAndEscape('tipoPlan');
            $convocatoria = $this->helper->getAndEscape('convocatoriaPlan');
            $consultora = $this->helper->getAndEscape('consultoraPlan');
            $estado = $this->helper->getAndEscape('estadoPlan');
            $kw = $this->helper->getAndEscape('keyword');
            
            $where = array();
            $queryString = '&amp;sent=1';
            
            // ID
            if (!empty($id)){
                $where[] = " idConvocatoria = $id";
                $this->view->id = $id;
                $queryString .= "&amp;idConvocatoria=$id";
            }
            
            // TIPO
            if (!empty($tipo)){
                $where[] = " fkTipoPlan = $tipo";
                $this->view->tipo = $tipo;
                $queryString .= "&amp;tipoPlan=$tipo";
            }

            // CONVOCATORIA
            if (!empty($convocatoria)){
                $where[] = " fkConvocatoria = $convocatoria";
                $this->view->convocatoria = $convocatoria;
                $queryString .= "&amp;convocatoriaPlan=$convocatoria";
            }

            // CONSULTORA
            if (!empty($consultora)){
                $where[] = " fkConvocatoria = $consultora";
                $this->view->consultora = $consultora;
                $queryString .= "&amp;consultoraPlan=$consultora";
            }

            // ESTADO
            if (!empty($estado)){
                $where[] = " fkConvocatoria = $estado";
                $this->view->estado = $estado;
                $queryString .= "&amp;estadoPlan=$estado";
            }
            
            // KEYWORD
            if (!empty($kw)){
                $where[] = "vNombre LIKE '%$kw%' OR vDescripcion LIKE '%$kw%'";
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
            $paginador = new NingenPaginator($this->db, $where, 'tblPlan', $this->helper);
            $paginador->setItemsPorPagina(10);
            $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
            $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
            $paginador->setPaginaActual($paginaActual);
            $paginador->setOrderBy($orderBy);
            $paginador->setOrder($order);
        
            // Obtengo los Planes
            $planesCOL = $paginador->getItemCollection();
            $this->view->planesCOL = $planesCOL;
            
            // Envío el paginador a la vista
            $this->view->paginador = $paginador->getPaginatorHtml();
            
            // Se propagan las clausulas de búsqueda en el paginador
            $this->view->querystring = $queryString;
            
            
        }        
        
    }
    
}

?>