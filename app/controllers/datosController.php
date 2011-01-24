<?php
require_once 'OwlPaginator.inc';
require_once 'helper/OwlString.inc';

require_once CLASSESDIR . 'PplController.inc';

require_once MODELDIR . 'TblCarnetConducir.inc';
require_once MODELDIR . 'TblColectivo.inc';
require_once MODELDIR . 'TblCategoriaEmpleo.inc';
require_once MODELDIR . 'TblEquipamiento.inc';
require_once MODELDIR . 'TblEstadoCivil.inc';
require_once MODELDIR . 'TblEstadoLaboral.inc';
require_once MODELDIR . 'TblModalidad.inc';
require_once MODELDIR . 'TblNivelEstudios.inc';
require_once MODELDIR . 'TblEstudio.inc';
require_once MODELDIR . 'TblRequisito.inc';
require_once MODELDIR . 'TblSector.inc';
require_once MODELDIR . 'TblTipoIdentificacion.inc';
require_once MODELDIR . 'TblTipoConvocatoria.inc';
require_once MODELDIR . 'TblEstadoPlan.inc';
require_once MODELDIR . 'TblTipoPlan.inc';


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
			$this->view->carnetDO = $carnetDO;
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
	        		// Pasamos a la vista el objeto editado
	        		$this->view->carnetDO = $carnetDO;
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
        
	}
	
	/**
	 * Gestiona los colectivos
	 */
	public function colectivoAction(){
		
		/**
		 * 1. Obtenemos el objeto en caso de ser una edición
		 * 2. Comprobamos si se ha enviado el formulario
		 * 	2.1. Alta
		 * 	2.2. Editar
		 * 3. Obtenemos los datos del paginador
		 * 4. Lo enviamos todo a la vista
		 */
		
		// 1. Obtenemos el objeto en caso de ser una edición
		$idColectivo = $this->getParam(0);
		if ( !is_null($idColectivo) ){
			$colectivoDO = TblColectivo::findByPrimaryKey($this->db, $idColectivo);
			$this->view->colectivoDO = $colectivoDO;
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
        	
        	if ( $correcto ){
        	
        		$this->db->begin();
        		
	        	// 2.1. Alta
	        	if ( $correcto && $_POST[md5('send')] == md5('alta') ) {
	        		$colectivoDO = new TblColectivo($this->db);
	        		$colectivoDO->setVNombre($nombre);
	        		$colectivoDO->setVDescripcion($descripcion);
	        		if ( !$colectivoDO->insert() ){
	        			$correcto = false;
	        		}
	        	}
	        	
	        	// 2.2. Editar
	        	if ( $correcto && $_POST[md5('send')] == md5('editar') ) {
	        		$colectivoDO = TblColectivo::findByPrimaryKey($this->db, $idColectivo);
	        		$colectivoDO->setVNombre($nombre);
	        		$colectivoDO->setVDescripcion($descripcion);
	        		if ( !$colectivoDO->update() ){
	        			$correcto = false;
	        		}
	        		// Pasamos a la vista el objeto editado
	        		$this->view->colectivoDO = $colectivoDO;
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
        $paginador = new OwlPaginator($this->db, null, 'tblColectivo', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo los colectivos
        $colectivosCOL = $paginador->getItemCollection();
        
        // 4. Lo enviamos todo a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío los colectivos
        $this->view->colectivosCOL = $colectivosCOL;
		
	}
	
	/**
	 * Gestiona los equipamientos
	 */
	public function equipamientoAction(){
		
		/**
		 * 1. Obtenemos el objeto en caso de ser una edición
		 * 2. Comprobamos si se ha enviado el formulario
		 * 	2.1. Alta
		 * 	2.2. Editar
		 * 3. Obtenemos los datos del paginador
		 * 4. Lo enviamos todo a la vista
		 */
		
		// 1. Obtenemos el objeto en caso de ser una edición
		$idEquipamiento = $this->getParam(0);
		if ( !is_null($idEquipamiento) ){
			$equipamientoDO = TblEquipamiento::findByPrimaryKey($this->db, $idEquipamiento);
			$this->view->equipamientoDO = $equipamientoDO;
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
        	
        	if ( $correcto ){
        	
        		$this->db->begin();
        		
	        	// 2.1. Alta
	        	if ( $correcto && $_POST[md5('send')] == md5('alta') ) {
	        		$equipamientoDO = new TblEquipamiento($this->db);
	        		$equipamientoDO->setVNombre($nombre);
	        		$equipamientoDO->setVDescripcion($descripcion);
	        		if ( !$equipamientoDO->insert() ){
	        			$correcto = false;
	        		}
	        	}
	        	
	        	// 2.2. Editar
	        	if ( $correcto && $_POST[md5('send')] == md5('editar') ) {
	        		$equipamientoDO = TblEquipamiento::findByPrimaryKey($this->db, $idEquipamiento);
	        		$equipamientoDO->setVNombre($nombre);
	        		$equipamientoDO->setVDescripcion($descripcion);
	        		if ( !$equipamientoDO->update() ){
	        			$correcto = false;
	        		}
	        		// Pasamos a la vista el objeto editado
	        		$this->view->equipamientoDO = $equipamientoDO;
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
        $paginador = new OwlPaginator($this->db, null, 'tblEquipamiento', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo los equipamientos
        $equipamientosCOL = $paginador->getItemCollection();
        
        // 4. Lo enviamos todo a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío los equipamientos
        $this->view->equipamientosCOL = $equipamientosCOL;
		
	}

	/**
	 * Gestiona los estados civiles
	 */
	public function estadoCivilAction(){
		
		/**
		 * 1. Obtenemos el objeto en caso de ser una edición
		 * 2. Comprobamos si se ha enviado el formulario
		 * 	2.1. Alta
		 * 	2.2. Editar
		 * 3. Obtenemos los datos del paginador
		 * 4. Lo enviamos todo a la vista
		 */
		
		// 1. Obtenemos el objeto en caso de ser una edición
		$idEstadoCivil = $this->getParam(0);
		if ( !is_null($idEstadoCivil) ){
			$estadoCivilDO = TblEstadoCivil::findByPrimaryKey($this->db, $idEstadoCivil);
			$this->view->estadoCivilDO = $estadoCivilDO;
		}
		
		// 2. Comprobamos si se ha enviado el formulario
        if ( array_key_exists(md5('send'), $_POST) ){
        	
        	$correcto = true;
        	$nombre = $this->helper->getAndEscape('nombre');
        	        	
        	if ( empty($nombre) ){
        		$correcto = false;
        		$this->view->errorNombre = "El nombre no puede estar vacío";
        	}
        	
        	if ( $correcto ){
        	
        		$this->db->begin();
        		
	        	// 2.1. Alta
	        	if ( $correcto && $_POST[md5('send')] == md5('alta') ) {
	        		$estadoCivilDO = new TblEstadoCivil($this->db);
	        		$estadoCivilDO->setVNombre($nombre);
	        		if ( !$estadoCivilDO->insert() ){
	        			$correcto = false;
	        		}
	        	}
	        	
	        	// 2.2. Editar
	        	if ( $correcto && $_POST[md5('send')] == md5('editar') ) {
	        		$estadoCivilDO = TblEstadoCivil::findByPrimaryKey($this->db, $idEstadoCivil);
	        		$estadoCivilDO->setVNombre($nombre);
	        		if ( !$estadoCivilDO->update() ){
	        			$correcto = false;
	        		}
	        		// Pasamos a la vista el objeto editado
	        		$this->view->estadoCivilDO = $estadoCivilDO;
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
    		'nom' 	=> 'vNombre'
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
        $paginador = new OwlPaginator($this->db, null, 'tblEstadoCivil', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo los estadosCiviles
        $estadosCivilesCOL = $paginador->getItemCollection();
        
        // 4. Lo enviamos todo a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío los estadosCiviles
        $this->view->estadosCivilesCOL = $estadosCivilesCOL;
		
	}
	
	/**
	 * Gestiona los estados laborales
	 */
	public function estadoLaboralAction(){
		
		/**
		 * 1. Obtenemos el objeto en caso de ser una edición
		 * 2. Comprobamos si se ha enviado el formulario
		 * 	2.1. Alta
		 * 	2.2. Editar
		 * 3. Obtenemos los datos del paginador
		 * 4. Lo enviamos todo a la vista
		 */
		
		// 1. Obtenemos el objeto en caso de ser una edición
		$idEstadoLaboral = $this->getParam(0);
		if ( !is_null($idEstadoLaboral) ){
			$estadoLaboralDO = TblEstadoLaboral::findByPrimaryKey($this->db, $idEstadoLaboral);
			$this->view->estadoLaboralDO = $estadoLaboralDO;
		}
		
		// 2. Comprobamos si se ha enviado el formulario
        if ( array_key_exists(md5('send'), $_POST) ){
        	
        	$correcto = true;
        	$nombre = $this->helper->getAndEscape('nombre');
        	        	
        	if ( empty($nombre) ){
        		$correcto = false;
        		$this->view->errorNombre = "El nombre no puede estar vacío";
        	}
        	
        	if ( $correcto ){
        	
        		$this->db->begin();
        		
	        	// 2.1. Alta
	        	if ( $correcto && $_POST[md5('send')] == md5('alta') ) {
	        		$estadoLaboralDO = new TblEstadoLaboral($this->db);
	        		$estadoLaboralDO->setVNombre($nombre);
	        		if ( !$estadoLaboralDO->insert() ){
	        			$correcto = false;
	        		}
	        	}
	        	
	        	// 2.2. Editar
	        	if ( $correcto && $_POST[md5('send')] == md5('editar') ) {
	        		$estadoLaboralDO = TblEstadoLaboral::findByPrimaryKey($this->db, $idEstadoLaboral);
	        		$estadoLaboralDO->setVNombre($nombre);
	        		if ( !$estadoLaboralDO->update() ){
	        			$correcto = false;
	        		}
	        		// Pasamos a la vista el objeto editado
	        		$this->view->estadoLaboralDO = $estadoLaboralDO;
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
    		'nom' 	=> 'vNombre'
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
        $paginador = new OwlPaginator($this->db, null, 'tblEstadoLaboral', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo los estadosLaborales
        $estadosLaboralesCOL = $paginador->getItemCollection();
        
        // 4. Lo enviamos todo a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío los estadosLaborales
        $this->view->estadosLaboralesCOL = $estadosLaboralesCOL;
		
	}
	

	/**
	 * Gestiona las modalidades
	 */
	public function modalidadAction(){
		
		/**
		 * 1. Obtenemos el objeto en caso de ser una edición
		 * 2. Comprobamos si se ha enviado el formulario
		 * 	2.1. Alta
		 * 	2.2. Editar
		 * 3. Obtenemos los datos del paginador
		 * 4. Lo enviamos todo a la vista
		 */
		
		// 1. Obtenemos el objeto en caso de ser una edición
		$idModalidad = $this->getParam(0);
		if ( !is_null($idModalidad) ){
			$modalidadDO = TblModalidad::findByPrimaryKey($this->db, $idModalidad);
			$this->view->modalidadDO = $modalidadDO;
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
        	
        	if ( $correcto ){
        	
        		$this->db->begin();
        		
	        	// 2.1. Alta
	        	if ( $correcto && $_POST[md5('send')] == md5('alta') ) {
	        		$modalidadDO = new TblModalidad($this->db);
	        		$modalidadDO->setVNombre($nombre);
	        		$modalidadDO->setVDescripcion($descripcion);
	        		if ( !$modalidadDO->insert() ){
	        			$correcto = false;
	        		}
	        	}
	        	
	        	// 2.2. Editar
	        	if ( $correcto && $_POST[md5('send')] == md5('editar') ) {
	        		$modalidadDO = TblModalidad::findByPrimaryKey($this->db, $idModalidad);
	        		$modalidadDO->setVNombre($nombre);
	        		$modalidadDO->setVDescripcion($descripcion);
	        		if ( !$modalidadDO->update() ){
	        			$correcto = false;
	        		}
	        		// Pasamos a la vista el objeto editado
	        		$this->view->modalidadDO = $modalidadDO;
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
        $paginador = new OwlPaginator($this->db, null, 'tblModalidad', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo las modalidades
        $modalidadesCOL = $paginador->getItemCollection();
        
        // 4. Lo enviamos todo a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío las modalidades
        $this->view->modalidadesCOL = $modalidadesCOL;
		
	}
	
	/**
	 * Control y edición de paises
	 */
	public function paisAction(){
		
		// 1. Obtenemos el objeto en caso de ser una edición
		$idPais = $this->getParam(0);
		if ( !is_null($idPais) ){
			$paisDO = TblPais::findByPrimaryKey($this->db, $idPais);
			$this->view->paisDO = $paisDO;
		}
		
		// 2. Comprobamos si se ha enviado el formulario
        if ( array_key_exists(md5('send'), $_POST) ){
        	
        	$correcto = true;
        	$nombre = $this->helper->getAndEscape('nombre');
        	$iso = $this->helper->getAndEscape('iso');
        	        	
        	if ( empty($nombre) ){
        		$correcto = false;
        		$this->view->errorNombre = "El nombre no puede estar vacío";
        	}
        	        	
        	if ( empty($iso) ){
        		$correcto = false;
        		$this->view->errorIso = "El iso no puede estar vacío";
        	}
        	
        	if ( $correcto ){
        	
        		$this->db->begin();
        		
	        	// 2.1. Alta
	        	if ( $correcto && $_POST[md5('send')] == md5('alta') ) {
	        		$paisDO = new TblPais($this->db);
	        		$paisDO->setVIso($iso);
	        		$paisDO->setVNombre($nombre);
	        		if ( !$paisDO->insert() ){
	        			$correcto = false;
	        		}
	        	}
	        	
	        	// 2.2. Editar
	        	if ( $correcto && $_POST[md5('send')] == md5('editar') ) {
	        		$paisDO = TblPais::findByPrimaryKey($this->db, $idPais);
	        		$paisDO->setVIso($iso);
	        		$paisDO->setVNombre($nombre);
	        		if ( !$paisDO->update() ){
	        			$correcto = false;
	        		}
	        		// Pasamos a la vista el objeto editado
	        		$this->view->paisDO = $paisDO;
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
    		'nom' 	=> 'vNombre_es',
    		'iso' 	=> 'vIso'
    	);
    	
    	if ( !empty($_REQUEST) && array_key_exists('o', $_GET) & array_key_exists('ob', $_GET) ){
        	$order = $this->helper->escapeInjection($_GET['o']);
        	$orderBy = $aliasCampos[$_GET['ob']];
        	$aliasOrderBy = $_GET['ob'];
        } else {
    		$order	 = 'asc';
    		$orderBy = 'vNombre_es';
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
        $paginador = new OwlPaginator($this->db, null, 'tblPais', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo los estadosLaborales
        $paisesCOL = $paginador->getItemCollection();
        
        // 4. Lo enviamos todo a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío los estadosLaborales
        $this->view->paisesCOL = $paisesCOL;		
		
	}
	
	
	
	/**
	 * Control y edición de provincias
	 */
	public function provinciaAction(){
		
		// 1. Obtenemos el objeto en caso de ser una edición
		$idProvincia = $this->getParam(0);
		if ( !is_null($idProvincia) ){
			$provinciaDO = TblProvincia::findByPrimaryKey($this->db, $idProvincia);
			$this->view->provinciaDO = $provinciaDO;
		}
		
		// 2. Comprobamos si se ha enviado el formulario
        if ( array_key_exists(md5('send'), $_POST) ){
        	
        	$correcto = true;
        	$nombre = $this->helper->getAndEscape('nombre');
        	        	
        	if ( empty($nombre) ){
        		$correcto = false;
        		$this->view->errorNombre = "El nombre no puede estar vacío";
        	}
        	
        	if ( $correcto ){
        	
        		$this->db->begin();
        		
	        	// 2.1. Alta
	        	if ( $correcto && $_POST[md5('send')] == md5('alta') ) {
	        		$provinciaDO = new TblPais($this->db);
	        		$provinciaDO->setVNombreEs($nombre);
	        		if ( !$provinciaDO->insert() ){
	        			$correcto = false;
	        		}
	        	}
	        	
	        	// 2.2. Editar
	        	if ( $correcto && $_POST[md5('send')] == md5('editar') ) {
	        		$provinciaDO = TblProvincia::findByPrimaryKey($this->db, $idProvincia);
	        		$provinciaDO->setVNombreEs($nombre);
	        		if ( !$provinciaDO->update() ){
	        			$correcto = false;
	        		}
	        		// Pasamos a la vista el objeto editado
	        		$this->view->provinciaDO = $provinciaDO;
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
    		'nom' 	=> 'vNombre_es',
    	);
    	
    	if ( !empty($_REQUEST) && array_key_exists('o', $_GET) & array_key_exists('ob', $_GET) ){
        	$order = $this->helper->escapeInjection($_GET['o']);
        	$orderBy = $aliasCampos[$_GET['ob']];
        	$aliasOrderBy = $_GET['ob'];
        } else {
    		$order	 = 'asc';
    		$orderBy = 'vNombre_es';
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
        $paginador = new OwlPaginator($this->db, null, 'tblProvincia', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo los estadosLaborales
        $provinciasCOL = $paginador->getItemCollection();
        
        // 4. Lo enviamos todo a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío los estadosLaborales
        $this->view->provinciasCOL = $provinciasCOL;		
		
	}
	
	
	/**
	 * Niveles de estudios
	 */
	public function estudiosAction(){
		
		// Edicion
		$clave = $this->getParam(0);
		$sent = intval($this->helper->getAndEscape('sent'));
		
		if ($estudioDO = TblEstudio::findByPrimaryKey($this->db, $clave)){
			
			$this->view->nombre = $estudioDO->getVNombre();
			$this->view->desc = $estudioDO->getVDescripcion();

			$this->view->editar = true;
			
			if ($sent == 1){
			
				$estudioDO->setVNombre($this->helper->get('nombre'));
				$estudioDO->setVDescripcion($this->helper->get('desc'));
				
				if (!$estudioDO->update()){
					
	   				$this->view->popup = array(
					    'estado' => 'ko',
					    'titulo' => 'Error',
					    'mensaje'=> 'Ha ocurrido un error al actualizar el estudio. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
					    'url'=> '',
					);	
	
					return;
					
				} else {
					
					$this->redirectTo('datos','estudios');
					return;
					
				}
				
			}
				
			
		}
		
		// Alta
		if ($sent == 1){
			
			$estudioDO = new TblEstudio($this->db);
			
			$estudioDO->setVNombre($this->helper->getAndEscape('nombre'));
			$estudioDO->setVDescripcion($this->helper->getAndEscape('desc'));
			
			if (!$estudioDO->insert()){
				
   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error al insertar el estudio. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);	

				return;
				
			} else {
				
				$this->redirectTo('datos','estudios');
				return;
				
			}			
			
		}
		
		$aliasCampos = array(
    		'nom' 	=> 'vNombre',
    		'desc' 	=> 'vDescripcion',
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
        $paginador = new OwlPaginator($this->db, null, 'tblEstudio', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);	

        $this->view->estudiosCOL = $paginador->getItemCollection();
        $this->view->paginador = $paginador->getPaginatorHtml();
        
	}
	
	
	/**
	 * Requisitos
	 */
	public function requisitoAction(){
		
		$clave = $this->getParam(0);
		$sent = intval($this->helper->getAndEscape('sent'));
		
		if ($requisitoDO = TblRequisito::findByPrimaryKey($this->db, $clave)){
			
			$this->view->nombre = $requisitoDO->getVNombre();
			$this->view->desc = $requisitoDO->getVDescripcion();

			$this->view->editar = true;
			
			if ($sent == 1){
			
				$requisitoDO->setVNombre($this->helper->get('nombre'));
				$requisitoDO->setVDescripcion($this->helper->get('desc'));
				
				if (!$requisitoDO->update()){
					
	   				$this->view->popup = array(
					    'estado' => 'ko',
					    'titulo' => 'Error',
					    'mensaje'=> 'Ha ocurrido un error al actualizar el requisito. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
					    'url'=> '',
					);	
	
					return;
					
				} else {
					
					$this->redirectTo('datos','requisito');
					return;
					
				}
				
			}
				
			
		}	

		// Alta
		if ($sent == 1){
			
			$requisitoDO = new TblRequisito($this->db);
			
			$requisitoDO->setVNombre($this->helper->getAndEscape('nombre'));
			$requisitoDO->setVDescripcion($this->helper->getAndEscape('desc'));
			
			if (!$requisitoDO->insert()){
				
   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error al insertar el requisito. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);	

				return;
				
			} else {
				
				$this->redirectTo('datos','requisito');
				return;
				
			}			
			
		}		
		
		$aliasCampos = array(
    		'nom' 	=> 'vNombre',
    		'desc' 	=> 'vDescripcion',
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
        $paginador = new OwlPaginator($this->db, null, 'tblRequisito', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);

        $this->view->requisitosCOL = $paginador->getItemCollection();
        $this->view->paginador = $paginador->getPaginatorHtml();
		
	}

	
	/**
	 * Sectores
	 */
	public function sectorAction(){
		
		$clave = $this->getParam(0);
		$sent = intval($this->helper->getAndEscape('sent'));
		
		if ($sectorDO = TblSector::findByPrimaryKey($this->db, $clave)){
			
			$this->view->nombre = $sectorDO->getVNombre();
			$this->view->desc = $sectorDO->getVDescripcion();

			$this->view->editar = true;
			
			if ($sent == 1){
			
				$sectorDO->setVNombre($this->helper->get('nombre'));
				$sectorDO->setVDescripcion($this->helper->get('desc'));
				
				if (!$sectorDO->update()){
					
	   				$this->view->popup = array(
					    'estado' => 'ko',
					    'titulo' => 'Error',
					    'mensaje'=> 'Ha ocurrido un error al actualizar el sector. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
					    'url'=> '',
					);	
	
					return;
					
				} else {
					
					$this->redirectTo('datos','sector');
					return;
					
				}
				
			}
				
			
		}	

		// Alta
		if ($sent == 1){
			
			$sectorDO = new TblSector($this->db);
			
			$sectorDO->setVNombre($this->helper->getAndEscape('nombre'));
			$sectorDO->setVDescripcion($this->helper->getAndEscape('desc'));
			
			if (!$sectorDO->insert()){
				
   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error al insertar el sector. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);	

				return;
				
			} else {
				
				$this->redirectTo('datos','sector');
				return;
				
			}			
			
		}		
		
		$aliasCampos = array(
    		'nom' 	=> 'vNombre',
    		'desc' 	=> 'vDescripcion',
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
        $paginador = new OwlPaginator($this->db, null, 'tblSector', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);

        $this->view->sectoresCOL = $paginador->getItemCollection();
        $this->view->paginador = $paginador->getPaginatorHtml();		
		
	}
	
	
	/**
	 * Tipos de identificaciones
	 */
	public function identificacionAction(){
		
		
		$clave = $this->getParam(0);
		$sent = intval($this->helper->getAndEscape('sent'));
		
		if ($identificacionDO = TblTipoIdentificacion::findByPrimaryKey($this->db, $clave)){
			
			$this->view->nombre = $identificacionDO->getVNombre();
			$this->view->editar = true;
			
			if ($sent == 1){
			
				$identificacionDO->setVNombre($this->helper->get('nombre'));
				
				if (!$identificacionDO->update()){
					
	   				$this->view->popup = array(
					    'estado' => 'ko',
					    'titulo' => 'Error',
					    'mensaje'=> 'Ha ocurrido un error al actualizar el tipo de identificacion. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
					    'url'=> '',
					);	
	
					return;
					
				} else {
					
					$this->redirectTo('datos','identificacion');
					return;
					
				}
				
			}
				
			
		}	

		// Alta
		if ($sent == 1){
			
			$identificacionDO = new TblTipoIdentificacion($this->db);
			
			$identificacionDO->setVNombre($this->helper->getAndEscape('nombre'));
			
			if (!$identificacionDO->insert()){
				
   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error al insertar el tipo de identificacion. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);	

				return;
				
			} else {
				
				$this->redirectTo('datos','identificacion');
				return;
				
			}			
			
		}		
		
		$aliasCampos = array(
    		'nom' 	=> 'vNombre',
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
        $paginador = new OwlPaginator($this->db, null, 'tblTipoIdentificacion', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);

        $this->view->identificacionesCOL = $paginador->getItemCollection();
        $this->view->paginador = $paginador->getPaginatorHtml();		
		
	}
	
	
	/**
	 * Tipos de convocatoria
	 */
	public function tiposConvocatoriaAction(){
		
		$clave = $this->getParam(0);
		$sent = intval($this->helper->getAndEscape('sent'));
		
		if ($tipoConvocatoriaDO = TblTipoConvocatoria::findByPrimaryKey($this->db, $clave)){
			
			$this->view->tipoConvocatoriaDO = $tipoConvocatoriaDO;
			$this->view->nombre = $tipoConvocatoriaDO->getVNombre();
			$this->view->editar = true;
			
			if ($sent == 1){
			
				$tipoConvocatoriaDO->setVNombre($this->helper->get('nombre'));
				$tipoConvocatoriaDO->setVDescripcion($this->helper->get('descripcion'));
				
				if (!$tipoConvocatoriaDO->update()){
					
	   				$this->view->popup = array(
					    'estado' => 'ko',
					    'titulo' => 'Error',
					    'mensaje'=> 'Ha ocurrido un error al actualizar el tipo de convocatoria. Inténtelo de nuevo en unos instantes por favor. Muchas gracias.',
					    'url'=> '',
					);
	
					return;
					
				} else {
					
					
					$this->redirectTo('datos','tiposConvocatoria');
					return;
					
				}
				
			}			
			
		}
		
		// Alta
		if ($sent == 1){
			
			$tipoConvocatoriaDO = new TblTipoConvocatoria($this->db);
			
			$tipoConvocatoriaDO->setVNombre($this->helper->getAndEscape('nombre'));
			
			if (!$tipoConvocatoriaDO->insert()){
				
   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error al insertar el tipo de convocatoria. Inténtelo de nuevo en unos instantes por favor.<br/> Muchas gracias.',
				    'url'=> '',
				);	

				return;
				
			} else {
				
				$this->redirectTo('datos','tiposConvocatoria');
				return;
				
			}			
			
		}

		$aliasCampos = array(
    		'nom' 	=> 'vNombre',
    		'desc' 	=> 'vDescripcion',
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
        $paginador = new OwlPaginator($this->db, null, 'tblTipoConvocatoria', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);

        $this->view->tiposConvocatoriaCOL = $paginador->getItemCollection();
        $this->view->paginador = $paginador->getPaginatorHtml();		
		
		
	}
	
	
	/**
	 * Estados de planes 
	 */
	public function estadoplanAction(){
		
		$clave = $this->getParam(0);
		$sent = intval($this->helper->getAndEscape('sent'));
		
		if ($estadoPlanDO = TblEstadoPlan::findByPrimaryKey($this->db, $clave)){
			
			$this->view->estadoPlanDO = $estadoPlanDO;
			$this->view->nombre = $estadoPlanDO->getVNombre();
			$this->view->editar = true;
			
			if ($sent == 1){
			
				$estadoPlanDO->setVNombre($this->helper->get('nombre'));
				$estadoPlanDO->setVDescripcion($this->helper->get('descripcion'));
				
				if (!$estadoPlanDO->update()){
					
	   				$this->view->popup = array(
					    'estado' => 'ko',
					    'titulo' => 'Error',
					    'mensaje'=> 'Ha ocurrido un error al actualizar el estado de plan. Inténtelo de nuevo en unos instantes por favor. Muchas gracias.',
					    'url'=> '',
					);
	
					return;
					
				} else {
					
					
					$this->redirectTo('datos','estadoplan');
					return;
					
				}
				
			}			
			
		}
		
		// Alta
		if ($sent == 1){
			
			$estadoPlanDO = new TblEstadoPlan($this->db);
			
			$estadoPlanDO->setVNombre($this->helper->getAndEscape('nombre'));
			$estadoPlanDO->setVDescripcion($this->helper->getAndEscape('descripcion'));
			
			if (!$estadoPlanDO->insert()){
				
   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error al insertar el estado de plan. Inténtelo de nuevo en unos instantes por favor.<br/> Muchas gracias.',
				    'url'=> '',
				);	

				return;
				
			} else {
				
				$this->redirectTo('datos','estadoplan');
				return;
				
			}			
			
		}

		$aliasCampos = array(
    		'nom' 	=> 'vNombre',
    		'desc' 	=> 'vDescripcion',
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
        $paginador = new OwlPaginator($this->db, null, 'tblEstadoPlan', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);

        $this->view->estadosPlanCOL = $paginador->getItemCollection();
        $this->view->paginador = $paginador->getPaginatorHtml();				
		
	}
	
	
	/**
	 * Tipos de plan
	 */
	public function tipoplanAction(){
		
		$clave = $this->getParam(0);
		$sent = intval($this->helper->getAndEscape('sent'));
		
		if ($tipoPlanDO = TblTipoPlan::findByPrimaryKey($this->db, $clave)){
			
			$this->view->tipoPlanDO = $tipoPlanDO;
			$this->view->nombre = $tipoPlanDO->getVNombre();
			$this->view->editar = true;
			
			if ($sent == 1){
			
				$tipoPlanDO->setVNombre($this->helper->get('nombre'));
				$tipoPlanDO->setVDescripcion($this->helper->get('descripcion'));
				
				if (!$tipoPlanDO->update()){
					
	   				$this->view->popup = array(
					    'estado' => 'ko',
					    'titulo' => 'Error',
					    'mensaje'=> 'Ha ocurrido un error al actualizar el tipo de plan. Inténtelo de nuevo en unos instantes por favor. Muchas gracias.',
					    'url'=> '',
					);
	
					return;
					
				} else {
					
					$this->redirectTo('datos','tipoplan');
					return;
					
				}
				
			}			
			
		}
		
		// Alta
		if ($sent == 1){
			
			$tipoPlanDO = new TblTipoPlan($this->db);
			
			$tipoPlanDO->setVNombre($this->helper->getAndEscape('nombre'));
			$tipoPlanDO->setVDescripcion($this->helper->getAndEscape('descripcion'));
			
			if (!$tipoPlanDO->insert()){
				
   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error al insertar el tipo de plan. Inténtelo de nuevo en unos instantes por favor.<br/> Muchas gracias.',
				    'url'=> '',
				);	

				return;
				
			} else {
				
				$this->redirectTo('datos','tipoplan');
				return;
				
			}			
			
		}

		$aliasCampos = array(
    		'nom' 	=> 'vNombre',
    		'desc' 	=> 'vDescripcion',
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
        $paginador = new OwlPaginator($this->db, null, 'tblTipoPlan', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);

        $this->view->tiposPlanCOL = $paginador->getItemCollection();
        $this->view->paginador = $paginador->getPaginatorHtml();			
		
	}
	
	/**
	 * Gestiona las categorías laborales
	 */
	public function categorialaboralAction(){
		
		/**
		 * 1. Obtenemos el objeto en caso de ser una edición
		 * 2. Comprobamos si se ha enviado el formulario
		 * 	2.1. Alta
		 * 	2.2. Editar
		 * 3. Obtenemos los datos del paginador
		 * 4. Lo enviamos todo a la vista
		 */
		
		// 1. Obtenemos el objeto en caso de ser una edición
		$idCategoriaLaboral = $this->getParam(0);
		if ( !is_null($idCategoriaLaboral) ){
			$categoriaLaboralDO = TblCategoriaEmpleo::findByPrimaryKey($this->db, $idCategoriaLaboral);
			$this->view->categoriaLaboralDO = $categoriaLaboralDO;
		}
		
		// 2. Comprobamos si se ha enviado el formulario
        if ( array_key_exists(md5('send'), $_POST) ){
        	
        	$correcto = true;
        	$nombre = $this->helper->getAndEscape('nombre');
        	
        	if ( empty($nombre) ){
        		$correcto = false;
        		$this->view->errorNombre = "El nombre no puede estar vacío";
        	}
        	
        	if ( $correcto ){
        	
        		$this->db->begin();
        		
	        	// 2.1. Alta
	        	if ( $correcto && $_POST[md5('send')] == md5('alta') ) {
	        		$categoriaLaboralDO = new TblCategoriaEmpleo($this->db);
	        		$categoriaLaboralDO->setVNombre($nombre);
	        		if ( !$categoriaLaboralDO->insert() ){
	        			$correcto = false;
	        		}
	        	}
	        	
	        	// 2.2. Editar
	        	if ( $correcto && $_POST[md5('send')] == md5('editar') ) {
	        		$categoriaLaboralDO = TblCategoriaEmpleo::findByPrimaryKey($this->db, $idCategoriaLaboral);
	        		$categoriaLaboralDO->setVNombre($nombre);
	        		if ( !$categoriaLaboralDO->update() ){
	        			$correcto = false;
	        		}
	        		// Pasamos a la vista el objeto editado
	        		$this->view->categoriaLaboralDO = $categoriaLaboralDO;
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
        $paginador = new OwlPaginator($this->db, null, 'tblCategoriaEmpleo', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo las categorías
        $categoriasLaboralesCOL = $paginador->getItemCollection();
        
        // 4. Lo enviamos todo a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Envío los carnets
        $this->view->categoriasLaboralesCOL = $categoriasLaboralesCOL;
        
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

				case 'colectivo':
					$itemDO = TblColectivo::findByPrimaryKey($this->db, $id);
					break;

				case 'equipamiento':
					$itemDO = TblEquipamiento::findByPrimaryKey($this->db, $id);
					break;

				case 'estadoCivil':
					$itemDO = TblEstadoCivil::findByPrimaryKey($this->db, $id);
					break;

				case 'estadoLaboral':
					$itemDO = TblEstadoLaboral::findByPrimaryKey($this->db, $id);
					break;

				case 'modalidad':
					$itemDO = TblModalidad::findByPrimaryKey($this->db, $id);
					break;

				case 'nivelEstudios':
					$itemDO = TblNivelEstudios::findByPrimaryKey($this->db, $id);
					break;

				case 'pais':
					$itemDO = TblPais::findByPrimaryKey($this->db, $id);
					break;

				case 'provincia':
					$itemDO = TblProvincia::findByPrimaryKey($this->db, $id);
					break;

				case 'estudios':
					$itemDO = TblEstudio::findByPrimaryKey($this->db, $id);
					break;

				case 'requisito':
					$itemDO = TblRequisito::findByPrimaryKey($this->db, $id);
					break;

				case 'identificacion':
					$itemDO = TblTipoIdentificacion::findByPrimaryKey($this->db, $id);
					break;

				case 'sector':
					$itemDO = TblSector::findByPrimaryKey($this->db, $id);
					break;

				case 'tiposConvocatoria':
					$itemDO = TblTipoConvocatoria::findByPrimaryKey($this->db, $id);
					break;

				case 'estadoplan':
					$itemDO = TblEstadoPlan::findByPrimaryKey($this->db, $id);
					break;

				case 'tipoplan':
					$itemDO = TblTipoPlan::findByPrimaryKey($this->db, $id);
					break;

				case 'categorialaboral':
					$itemDO = TblCategoriaEmpleo::findByPrimaryKey($this->db, $id);
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