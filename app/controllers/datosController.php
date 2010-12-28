<?php
require_once 'OwlPaginator.inc';

require_once CLASSESDIR . 'PplController.inc';

require_once MODELDIR . 'TblCarnetConducir.inc';
require_once MODELDIR . 'TblColectivo.inc';
require_once MODELDIR . 'TblEquipamiento.inc';
require_once MODELDIR . 'TblEstadoCivil.inc';
require_once MODELDIR . 'TblEstadoLaboral.inc';
require_once MODELDIR . 'TblModalidad.inc';
require_once MODELDIR . 'TblNivelEstudios.inc';

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
				
			}
			
			// Eliminamos el item
			if ( !empty($itemDO) ){
				$itemDO->delete();
			}
		}
		
		$this->redirectTo('datos', $item);
		
	}
	
	
	/**
	 * Control y edición de paises
	 */
	public function paisAction(){
		
		// 1. Obtenemos el objeto en caso de ser una edición
		$idPais = $this->getParam(0);
		if ( !is_null($idPais) ){
			$paisDO = TblEstadoLaboral::findByPrimaryKey($this->db, $idPais);
			$this->view->paisDO = $paisDO;
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
	        		$paisDO = new TblPais($this->db);
	        		$paisDO->setVNombre($nombre);
	        		if ( !$paisDO->insert() ){
	        			$correcto = false;
	        		}
	        	}
	        	
	        	// 2.2. Editar
	        	if ( $correcto && $_POST[md5('send')] == md5('editar') ) {
	        		$paisDO = TblPais::findByPrimaryKey($this->db, $idPais);
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
	
	
}

?>