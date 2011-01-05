<?php

require_once CLASSESDIR . 'PplController.inc';
require_once 'helper/OwlNumeric.inc';
require_once 'OwlPaginator.inc';

require_once MODULEDIR . 'menuPrincipalModule.php';
require_once MODULEDIR . 'logoutModule.php';
require_once MODULEDIR . 'barraHerramientasModule.php';

require_once MODELDIR . '/TblConvocatoria.inc';
require_once MODELDIR . '/TblPlan.inc';
require_once MODELDIR . '/TblSector.inc';

class planController extends PplController{
    
    
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
        $paginador = new OwlPaginator($this->db, null, 'tblPlan', $this->helper);
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
        
    	// Sector
    	$this->view->sectoresIDX = $this->cacheBO->getSectores();
    	
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
    	
    	// Sector
    	$this->view->sectoresIDX = $this->cacheBO->getSectores();
    	
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
    		
	    	// Sector
    		$this->view->sectoresIDX = $this->cacheBO->getSectores();
        }
        
    }
    
	/**
     * Acción de edición
     * Edita un plan
     */
    public function editarAction(){
        
    	// Obtengo el plan que voy a editar
    	$idPlan = $this->getParam(0);
        if ( !is_null($idPlan) ){
        	
        	// Plan
            if (!$planDO = TblPlan::findByPrimaryKey($this->db, $idPlan)){
                $this->redirectTo('plan', 'index');
                return;
            }
            
        	$duplicar = false;
        	
        } else {
        	
        	if ( OwlSession::getValue('planDuplicado') instanceof TblPlan ){
        		
        		$planDO = OwlSession::getValue('planDuplicado');
        		$duplicar = true;
        		
        	}
        	
        }
    	
    	// Actualizo el plan
        if ( isset($planDO) && $this->helper->get('send') ){
        	
        	if ( $duplicar ){
    			$correcto = $this->actualizarInsertar();
    		} else {
    			$correcto = $this->actualizarInsertar(true, $planDO->getIdPlan());
    		}
    		
            if ( $correcto ){
                    
            	if ( $duplicar ){
                	$this->redirectTo('plan','editar', $this->db->getLastInsertId());
            	} else {
                	$planDO = TblPlan::findByPrimaryKey($this->db, $planDO->getIdPlan());
            	}
                $this->view->planDO = $planDO;
                    
			} else {
                    
            	$this->view->popup = array(
                	'estado' => 'ko',
                	'titulo' => 'Error',
                    'mensaje'=> 'Ha ocurrido un error con la edición del plan. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                    'url'=> '',
                );
                    
            }
       }
    	
    	// Datos para la vista
       	if ( isset($planDO) ){
        	
       		$this->view->planDO = $planDO;
       		
	    	// Tipos de Plan
	    	$this->view->tiposPlanIDX = $this->cacheBO->getTiposPlan();
	    	
	    	// Estados de Plan
	    	$this->view->estadosPlanIDX = $this->cacheBO->getEstadosPlan();
	    	
	    	// Convocatorias
	    	$this->view->convocatoriasIDX = $this->cacheBO->getConvocatorias();
	    	
	    	// Consultoras
    		$this->view->consultorasIDX = $this->cacheBO->getConsultoras();
	    	
    		// Sector
    		$this->view->sectoresIDX = $this->cacheBO->getSectores();
    		
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
        
        $idPlan = $this->getParam(0);
        if ( !is_null($idPlan) ){
        	
        	$planDO = TblPlan::findByPrimaryKey($this->db, $idPlan);
        	$nombrePlan = 'Copia de ' . $planDO->getVNombre();
        	$planDO->setVNombre($nombrePlan);
//        	$planDO->insert();
        	OwlSession::setValue('planDuplicado', $planDO);
        }
        
//        $this->redirectTo('plan','editar', $this->db->getLastInsertId());
        $this->redirectTo('plan','editar');
        
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
	    if ( is_null($convocatoria) || empty($convocatoria) ){
	    	$correcto = false;
	    	$this->view->errorConvocatoria = 'La convocatoria no puede estar vacía';
	    }
	    
	    // Sector
		$sector = $this->helper->escapeInjection($this->helper->get('sector'));
	    if ( is_null($sector) || empty($sector) ){
	    	$correcto = false;
	    	$this->view->errorSector = 'El sector no puede estar vacío';
	    }
	    
	    // Número de expediente
		$expediente = $this->helper->escapeInjection($this->helper->get('expediente'));
	    if ( is_null($expediente) || empty($expediente) ){
	    	$correcto = false;
	    	$this->view->errorExpediente = 'El expediente no puede estar vacío';
	    }
	    
    	// Estado
		$estado = $this->helper->escapeInjection($this->helper->get('estado'));
	    if ( is_null($estado) || empty($estado) ){
	    	$correcto = false;
	    	$this->view->errorEstado = 'El estado no puede estar vacío';
	    }
	    
    	// Presupuesto
		$presupuesto = $this->helper->escapeInjection($this->helper->get('presupuesto'));
	    if ( is_null($presupuesto) || empty($presupuesto) ){
	    	$correcto = false;
	    	$this->view->errorPresupuesto = 'El presupuesto no puede estar vacío';
	    } else if ( !OwlNumeric::currencyEuro($presupuesto) ) {
	    	$correcto = false;
	    	$this->view->errorPresupuesto = 'El presupuesto no tiene el formato correcto';
	    }
	    
    	// Propietario
		$propietario = $this->helper->escapeInjection($this->helper->get('propietario'));
	    if ( is_null($propietario) || empty($propietario) ){
	    	$correcto = false;
	    	$this->view->errorPropietario = 'El propietario no puede estar vacío';
	    }
	    
	    // Consultora
		$consultora = $this->helper->escapeInjection($this->helper->get('consultora'));
	    if ( is_null($consultora) || empty($consultora) ){
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
	    	$planDO->setFkSector($sector);
	    	$planDO->setVNumeroExpediente($expediente);
	    	$planDO->setFkEstadoPlan($estado);
	    	$planDO->setFkEmpresaPropietaria($propietario);
	    	$planDO->setFkEmpresaConsultora($consultora);
	    	$planDO->setEPresupuestoAsignado(OwlNumeric::formatoEuropeoDecimal($presupuesto, 2));
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
            $queryARR['sent'] = 1;
            
            // ID
            if (!empty($id)){
                $where[] = " idPlan = $id";
                $this->view->id = $id;
//                $queryString .= "&amp;idPlan=$id";
                $queryARR['idPlan'] = $id;
            }
            
            // TIPO
            if (!empty($tipo)){
                $where[] = " fkTipoPlan = $tipo";
                $this->view->tipo = $tipo;
//                $queryString .= "&amp;tipoPlan=$tipo";
                $queryARR['tipoPlan'] = $tipo;
            }

            // CONVOCATORIA
            if (!empty($convocatoria)){
                $where[] = " fkConvocatoria = $convocatoria";
                $this->view->convocatoria = $convocatoria;
//                $queryString .= "&amp;convocatoriaPlan=$convocatoria";
                $queryARR['convocatoriaPlan'] = $convocatoria;
            }

            // CONSULTORA
            if (!empty($consultora)){
                $where[] = " fkEmpresaConsultora = $consultora";
                $this->view->consultora = $consultora;
//                $queryString .= "&amp;consultoraPlan=$consultora";
                $queryARR['consultoraPlan'] = $consultora;
            }

            // ESTADO
            if (!empty($estado)){
                $where[] = " fkConvocatoria = $estado";
                $this->view->estado = $estado;
//                $queryString .= "&amp;estadoPlan=$estado";
                $queryARR['estadoPlan'] = $estado;
            }
            
            // KEYWORD
            if (!empty($kw)){
                $where[] = "vNombre LIKE '%$kw%' OR vDescripcion LIKE '%$kw%'";
                $this->view->kw = $kw;
                $queryString .= "&amp;keyword=$kw";
                $queryARR['keyword'] = $kw;             
            }
            
            // Se construye el where
            if (count($where)){
                $where = ' WHERE ' . implode(' AND ', $where);
            } else {
                $where = '';
            }
            
            // Se ejecuta la búsqueda
            $paginador = new OwlPaginator($this->db, $where, 'tblPlan', $this->helper);
            $paginador->setItemsPorPagina(10);
            $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
            $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
            $paginador->setPaginaActual($paginaActual);
            $paginador->setOrderBy($orderBy);
            $paginador->setOrder($order);
//            $paginador->setExtraParams($queryString);
            $paginador->setExtraParams($queryARR);
        
            // Obtengo los Planes
            $planesCOL = $paginador->getItemCollection();
            $this->view->planesCOL = $planesCOL;
            
            // Envío el paginador a la vista
            $this->view->paginador = $paginador->getPaginatorHtml();
            
            // Se propagan las clausulas de búsqueda en el paginado
        	foreach ( $queryARR as $clave => $valor ){
            	$queryString .= '&amp;' . $clave . '=' . $valor;
            }
            $this->view->querystring = $queryString;
            
            
        }        
        
    }
    
}

?>