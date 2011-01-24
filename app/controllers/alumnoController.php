<?php

require_once 'helper/OwlString.inc';
require_once 'helper/OwlDate.inc';
require_once CLASSESDIR . 'PplController.inc';

require_once MODELDIR . 'TblCategoria.inc';
require_once MODELDIR . 'TblCategoriaEmpleo.inc';
require_once MODELDIR . 'TblCarnetConducir.inc';
require_once MODELDIR . 'TblCobroParo.inc';
require_once MODELDIR . 'TblCurso.inc';
require_once MODELDIR . 'TblEstadoCivil.inc';
require_once MODELDIR . 'TblEstadoLaboral.inc';
require_once MODELDIR . 'TblNivelEstudios.inc';
require_once MODELDIR . 'TblPais.inc';
require_once MODELDIR . 'TblPersona.inc';
require_once MODELDIR . 'TblProvincia.inc';
require_once MODELDIR . 'TblSector.inc';
require_once MODELDIR . 'TblTrabajoParo.inc';
require_once MODELDIR . 'TblTipoIdentificacion.inc';
require_once MODELDIR . 'TrelCandidato.inc';
require_once MODELDIR . 'TrelPersonaCategoria.inc';
require_once MODELDIR . 'TrelPersonaCarnet.inc';
require_once MODELDIR . 'TrelPrecandidato.inc';
require_once MODELDIR . 'TrelRolUsuario.inc';

require_once 'helper/OwlHtmlHelper.inc';
require_once 'dbase/OwlDatabase.inc';
require_once 'OwlPaginator.inc';


class alumnoController extends PplController{
    
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
            'nom'   => 'vNombre',
            'pob'	=> 'vPoblacion',
            'id'	=> 'idPersona',
        	'mov'	=> 'vMovil'
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
        
        // Se instancia y configura el paginador
        $rolAlumno = PplAclManager::ROL_ALUMNO;
        $paginador = new OwlPaginator($this->db, 'p WHERE EXISTS (SELECT null FROM trelRolUsuario ru WHERE ru.fkUsuario = p.fkUsuario AND ru.fkRol = ' . $rolAlumno . ')', 'tblPersona', $this->helper);
        $paginador->setItemsPorPagina(20);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        
        // Obtengo todos los usuarios del sistema
        $alumnosCOL = $paginador->getItemCollection();
        
        // Envio el paginador a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();

        // Verificamos que el usuario actual tenga permisos para editar y/o eliminar desde el listado
        $this->view->editar = $this->aclManager->hasPerms('alumno', 'editar');
        
        // Paso los datos a la vista
        $this->view->alumnosCOL = $alumnosCOL;

        
        
    }
    
    /**
     * Acción de alta
     * Da de alta una persona
     */
    public function altaAction(){
        
   		// Paises
        $this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
        
        // Provincias
        $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
        
        // Tipo identificación
        $this->view->tipoIdentificacionCOL = TblTipoIdentificacion::findAll($this->db, 'vNombre');
        
        // Estado civil
        $this->view->estadosCivilesCOL = TblEstadoCivil::findAll($this->db, 'vNombre');
        
        // Estado laboral
        $this->view->estadosLaboralesCOL = TblEstadoLaboral::findAll($this->db, 'vNombre');
        
        // Nivel estudios
        $this->view->nivelEstudiosCOL = TblNivelEstudios::findAll($this->db, 'vNombre');
        
        // Cursos
        $sql = "SELECT * FROM tblCurso WHERE dInicio >= now()";
        $this->view->cursosCOL = OwlGenericDO::createCollection($this->db, $sql, 'tblCurso');
        
         // Sectores
	    $this->view->sectoresIDX = $this->cacheBO->getSectores();
	    
	    // Categorías
	    $this->view->categoriasIDX = $this->cacheBO->getCategorias();
        
	    // Carnets de conducir
	    $this->view->carnetsCOL = TblCarnetConducir::findAll($this->db,'vNombre');
	    
	    // Cobro de paro
	    $this->view->cobrosParoIDX = $this->cacheBO->getCobrosParo();
	    
	    // Trabajos paro
	    $this->view->trabajosParoIDX = $this->cacheBO->getTrabajoParo();
	    
	    // Categorías de empleo
	    $this->view->categoriasEmpleoIDX = $this->cacheBO->getCategoriasEmpleo();
	    
	    // Claves para los campos de situación laboral
	    $this->view->claveOcupado = PplCacheBO::CLAVE_OCUPADO;
	    $this->view->claveDesocupado = PplCacheBO::CLAVE_DESOCUPADO;
	    
   		// Doy de alta la persona
    	if ( $this->helper->get('send') ){
    		
   			if ( $this->actualizarInsertar() ){
   				
   				// Todo ha ido bien
    			$this->redirectTo('alumno', 'index');
					
   			} else {

   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con el alta de alumno. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
					
   			}
    	}
        
    }
    
	/**
     * Acción de edición
     * Al duplicar un alumno, se copian los datos del alumno, pero no los datos del
     * usuario del alumno. Es necesario el parámetro 'duplicar' para indicarle a la vista
     * si le llega una duplicada o no.
     * Edita una academia
     */
    public function editarAction(){
        
    	// Obtengo el alumno que voy a editar
    	$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	// Alumno
        	if (!$alumnoDO = TblPersona::findByPrimaryKey($this->db, $paramsARR[0])){
                $this->redirectTo('alumno', 'index');
                return;
            }
            
        	$this->view->duplicar = $duplicar = false;
        	
        	// Usuario del alumno
        	$this->view->usuarioDO = $alumnoDO->getTblUsuario();
        	
        } else {
        	
        	if ( OwlSession::getValue('alumnoDuplicado') instanceof TblPersona ){
        		
        		$alumnoDO = OwlSession::getValue('alumnoDuplicado');
        		$this->view->duplicar = $duplicar = true;
        		
        	}
        	
        }
        
    	// Actualizo el alumno
    	if ( isset($alumnoDO) && $this->helper->get('send') ){
    		
    		if ( $duplicar ){
    			$correcto = $this->actualizarInsertar();
    		} else {
    			$correcto = $this->actualizarInsertar(true, $alumnoDO->getIdPersona(), $alumnoDO->getTblUsuario()->getIdUsuario());
    		}
    		
    		if ( $correcto ){
    				
    			// Todo ha ido bien
    			$this->redirectTo('alumno', 'index');
        	
    		} else {
    			
    			$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con la edición del alumno. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
				
    		}
    	}
    	
    	// Datos para la vista
    	if ( isset($alumnoDO) ){
        	
    		$this->view->alumnoDO = $alumnoDO;
    		
	        // Paises
	        $this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
		        
	        // Provincias
	        $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
		        
	        // Tipo identificación
	        $this->view->tipoIdentificacionCOL = TblTipoIdentificacion::findAll($this->db, 'vNombre');
	        
	        // Estado civil
	        $this->view->estadosCivilesCOL = TblEstadoCivil::findAll($this->db, 'vNombre');
	        
	        // Estado laboral
	        $this->view->estadosLaboralesCOL = TblEstadoLaboral::findAll($this->db, 'vNombre');
	        
	        // Nivel estudios
	        $this->view->nivelEstudiosCOL = TblNivelEstudios::findAll($this->db, 'vNombre');
	        
	        // Cursos
	        $this->view->cursosIDX = $this->cacheBO->getCursos();
	        
	        // Cursos precandidato alumno
	        $this->view->cursosAlumnoCOL = TrelPrecandidato::findByTblPersona($this->db, $alumnoDO->getIdPersona() , 'dAlta');
	        
	        // Cursos a los que se puede preinscribir el alumno
	        $this->view->cursosPreinscribiblesCOL = $this->cacheBO->getCursosPreinscribibles($alumnoDO->getIdPersona());
	        
	        // Sectores
		    $this->view->sectoresIDX = $this->cacheBO->getSectores();
		    
		    // Categorías
		    $this->view->categoriasIDX = $this->cacheBO->getCategorias();
		    
		    // Carnets de conducir
	    	$this->view->carnetsCOL = TblCarnetConducir::findAll($this->db,'vNombre');
	    	
	    	// Carnets del alumno
	    	$this->view->carnetsAlumnoCOL = TrelPersonaCarnet::findByTblPersona($this->db, $alumnoDO->getIdPersona());
		    
	    	// Cobro de paro
	    	$this->view->cobrosParoIDX = $this->cacheBO->getCobrosParo();
	    	
	    	// Trabajos paro
	    	$this->view->trabajosParoIDX = $this->cacheBO->getTrabajoParo();
	    	
	    	// Categorías de empleo
	    	$this->view->categoriasEmpleoIDX = $this->cacheBO->getCategoriasEmpleo();
	    	
	    	// Claves para los campos de situación laboral
	    	$this->view->claveOcupado = PplCacheBO::CLAVE_OCUPADO;
	    	$this->view->claveDesocupado = PplCacheBO::CLAVE_DESOCUPADO;
        }
        
    }
    
	/**
     * Acción de ficha
     * Ficha de un alumno
     */
    public function fichaAction(){
        
   		$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	// Alumno
        	$alumnoDO = TblPersona::findByPrimaryKey($this->db, $paramsARR[0]);
        	if ( !empty($alumnoDO) ){

        		$this->view->alumnoDO = $alumnoDO;
        	
        		// Usuario del alumno
        		$this->view->usuarioDO = $alumnoDO->getTblUsuario();
        		
        		// Cursos preinscritos
        		$this->view->cursosPreinscritosCOL = TrelPrecandidato::findByTblPersona($this->db, $alumnoDO->getIdPersona());
        		
        		// Cursos precandidato
        		$this->view->cursosCandidatoCOL = TrelCandidato::findByTblPersona($this->db, $alumnoDO->getIdPersona());
        		
        		// Cursos alumno
        		$this->view->alumnoCursosCOL = $this->cacheBO->getAlumnosPersona($alumnoDO->getIdPersona());
        		
        		// Cursos
        		$this->view->cursosCOL = TblCurso::findAll($this->db, 'vNombre');
        		
        		// Carnets
        		$this->view->carnetsIDX = $this->cacheBO->getCarnets();
        		
        		// Carnets del alumno
	    		$this->view->carnetsAlumnoCOL = TrelPersonaCarnet::findByTblPersona($this->db, $alumnoDO->getIdPersona());
        		
        	}
        	
        }
        
    }
    
	/**
     * Acción de eliminar
     * Elimina el usuario del alumno, y en la bbdd
     * se elimina el alumno en cascada
     */
    public function eliminarAction(){
        
        /**
         * @TODO Comprobar permisos
         */
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
            
        	if ($alumnoDO = TblPersona::findByPrimaryKey($this->db, $paramsARR[0])){

        	   $claveUsuario = $alumnoDO->getFkUsuario();
        	   if ($usuarioDO = TblUsuario::findByPrimaryKey($this->db, $claveUsuario))
        	   
                    if (!$usuarioDO->delete()){
                        
                        /**
                         * @TODO Mostrar error (No se pudo borrar el usuario) 
                         */
                        $this->redirectTo('alumno','index');
                        return;
                        
                    }
                    
                    /**
                     * @TODO BORRADO OK (REDIRIGIR A DONDE SEA NECESARIO) 
                     */
                    $this->redirectTo('alumno','index');
                    return;
        	   
        	   } else {
        	       
        	        /**
                     * @TODO Mostrar error (El usuario no existe) 
                     */
                    $this->redirectTo('alumno','index');
                    return;
        	       
        	       
        	   }
        	    
        	    
        	} else {
        	    
        	    /**
        	     * @TODO Mostrar error (La persona no existe) 
        	     */
        	    $this->redirectTo('alumno','index');
        	    
        	}
        	
    }
    
    
	/**
     * Acción de duplicar
     * Duplica una alumno
     */
    public function duplicarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	$alumnoDO = TblPersona::findByPrimaryKey($this->db, $paramsARR[0]);
        	$nombreAlumno = 'Copia de ' . $alumnoDO->getVNombre();
        	$alumnoDO->setVNombre($nombreAlumno);
        	$alumnoDO->setVNumeroIdentificacion('');
        	OwlSession::setValue('alumnoDuplicado', $alumnoDO);
        }
        
        $this->redirectTo('alumno','editar');
        
    }
    
	/**
     * Obtiene los datos de alumno y realiza el alta o la actualización
     * @param boolean $editar
     * @param intenger $idAlumno
     * @return boolean $correcto
     */
    public function actualizarInsertar($editar = false, $idAlumno = '', $idUsuario = '') {
    	
	    $correcto = true;
	    
     	// Comprobaciones pertinentes
     	
	    // Datos del usuario
	    
	    $username = $this->helper->escapeInjection($this->helper->get('nombreUsuario'));
	    $oldUsername = $this->helper->getAndEscape('nombreUsuarioOculto');
        $password = $this->helper->escapeInjection($this->helper->get('password1'));
        $repassword = $this->helper->escapeInjection($this->helper->get('repassword1'));
        $setPassword = true;
        $email = $this->helper->escapeInjection($this->helper->get('emailUsuario'));
	    
        // Usuario
        if (empty($username)){
            $this->view->errorNombreUsuario = 'El nombre no puede estar vacío.';  
            $correcto = false;
        }
            
        if (!preg_match('/^[a-zA-Z0-9]{5,16}$/', $username)) {
            $this->view->errorNombreUsuario = 'El nombre de usuario no es correcto.';
            $correcto = false;                
        }
        
        if ( !$editar || ($editar && $username != $oldUsername) ){
	        $sql = "SELECT COUNT(*) AS total FROM tblUsuario WHERE vNombre = '$username'";
	        $this->db->executeQuery($sql);
	        $row = $this->db->fetchRow();
	        if (is_array($row) && array_key_exists('total', $row) && $row['total'] != 0){
	            $this->view->errorNombreUsuario = 'El nombre de usuario ya existe';
	            $correcto = false;     
	        }
        }
        
        if ( $editar ){
        	
	        // Contraseña
	        if ( !empty($password) || !empty($repassword)){
	            
		        if ($password != $repassword){
		            $this->view->errorPassword = 'Las contraseñas no coinciden.';
		            $correcto = false;
		        }
		            
		        if (!preg_match('/^(?=.*\d)(?=.*[A-Za-z@#$%^&+=]).{6,15}$/', $password)) {
		            $this->view->errorPassword = 'La contraseña no es correcta.';
		            $correcto = false;
		        }

		    // No cambia el password
	        } else {
	        	$setPassword = false;
	        }
        
        } else {
        	
        	// Contraseña
	        if (empty($password) || empty($repassword)){
	            $this->view->errorPassword = 'La contraseña no puede estar vacía.';
	            $correcto = false;
	        }
	            
	        if ($password != $repassword){
	            $this->view->errorPassword = 'Las contraseñas no coinciden.';
	            $correcto = false;
	        }
	            
	        if (!preg_match('/^(?=.*\d)(?=.*[A-Za-z@#$%^&+=]).{6,15}$/', $password)) {
	            $this->view->errorPassword = 'La contraseña no es correcta.';
	            $correcto = false;
	        }
        	
        }
            
        // Email
        if (!OwlString::validaMail($email)){
            $this->view->errorEmail = 'La dirección de correo proporcionada no es correcta.';
            $correcto = false;
        }
	   	
        // Datos del alumno
    	$nombre = $this->helper->getAndEscape('nombre');
        $apellido = $this->helper->getAndEscape('apellido1'); 
        $apellido2 = $this->helper->getAndEscape('apellido2');
        $sexo = $this->helper->getAndEscape('sexo');
        $discapacidad = $this->helper->getAndEscape('discapacidad');
        $nacimiento = $this->helper->getAndEscape('nacimiento');
        $tipoIdentificacion = $this->helper->getAndEscape('tipoIdentificacion'); 
        $dni = $this->helper->getAndEscape('dni');
        $numeroSS = $this->helper->getAndEscape('numeroSS');
        $oldDni = $this->helper->getAndEscape('dniOculto');
        $direccion = $this->helper->getAndEscape('direccion');
        $poblacion = $this->helper->getAndEscape('poblacion'); 
        $cp = $this->helper->getAndEscape('cp'); 
        $provincia = $this->helper->getAndEscape('provinciasUsuario'); 
        $pais = $this->helper->getAndEscape('pais');
        $estadoCivil = $this->helper->getAndEscape('estadoCivil');
        $estadoLaboral = $this->helper->getAndEscape('estadoLaboral');
        $nivelEstudios = $this->helper->getAndEscape('nivelEstudios');
        $telefono = $this->helper->getAndEscape('tel');
        $movil = $this->helper->getAndEscape('movil');
        $observaciones = $this->helper->get('observaciones');
        
	    // Cursos
    	$cursosARR = array();
        if ( array_key_exists('cursos', $_POST) ){
        	foreach ($_POST['cursos'] as $curso) {
            	$cursosARR[] = $this->helper->escapeInjection($curso);
            }
        }
        
    	// Carnet: 'carnet_1', 'carnet_5'
		$arrIdsCarnets = array();
		foreach ( $_REQUEST as $key => $value ) {
			$clave = explode('_', $key);
			if ( $clave[0] == 'carnet' ) {
				array_push($arrIdsCarnets,$clave[1]);
			}
		}
		
		// Campos para el caso de estar en situación laboral "Desocupado"
		$fechaParo = $this->helper->getAndEscape('fechaParo');
		$trabajo = $this->helper->getAndEscape('trabajo');
		$cobro = $this->helper->getAndEscape('cobro');
		
		// Campos para el caso de estar en situación laboral "Ocupado"
		$categoriaEmpleo = $this->helper->getAndEscape('categoriaEmpleo');
		$trabajadores250 = $this->helper->getAndEscape('trabajadores250');
		$sectorEmpresaActual = $this->helper->getAndEscape('sectorEmpresaActual');
		$razonEmpresaActual = $this->helper->getAndEscape('razonEmpresaActual');
		$cif = $this->helper->getAndEscape('cif');
		$domicilioEmpresaActual = $this->helper->getAndEscape('domicilioEmpresaActual');
		$localidadEmpresaActual = $this->helper->getAndEscape('localidadEmpresaActual');
		$cpEmpresaActual = $this->helper->getAndEscape('cpEmpresaActual');
		
        // Nombre 
        if (empty($nombre)){
        	$this->view->errorNombre = 'El nombre no puede quedar vacío';
            $correcto = false;
        }

        // Apellido 
        if (empty($apellido)){
            $this->view->errorApellido = 'El apellido no puede quedar vacío';
        	$correcto = false;
        }
                
        // Fecha de naciemiento
        if (empty($nacimiento)){
			$this->view->errorNacimiento = 'Debe introducir una fecha de nacimiento';
            $correcto = false;
        }

   		// Tipo de identificación
        if (empty($tipoIdentificacion)){
			$this->view->errorTipoIdentificacion = 'Debe seleccionar un tipo de identificación';
            $correcto = false;
        }
        
        // DNI
        if (empty($dni)){
            $this->view->errorDni = 'Debe introducir un número de identificación';
        	$correcto = false;
        } else {
        	
        	// Comprobamos que el número no exista ya en la bbdd
        	if ( !$editar || ($editar && $dni != $oldDni) ){
		        $sql = "SELECT COUNT(*) AS total FROM tblPersona WHERE vNumeroIdentificacion = '" . $dni . "'";
		        $this->db->executeQuery($sql);
		        $row = $this->db->fetchRow();
		        if (is_array($row) && array_key_exists('total', $row) && $row['total'] != 0){
		            $this->view->errorDni = 'El número ya está registrado';
		            $correcto = false;     
		        }
        	}
        	
        }
                
        // País
        if (empty($pais)){
        	$this->view->errorPais = 'Debe seleccionar un país';
            $correcto = false;
        }
                
        // Estado civil
        if (empty($estadoCivil)){
        	$this->view->errorEstadoCivil = 'Debe seleccionar un estado civil';
            $correcto = false;
        }
                
        // Estado laboral
        if (empty($estadoLaboral)){
            $this->view->errorEstadoLaboral = 'Debe seleccionar un estado laboral';
            $correcto = false;
        }
                
        // Nivel de estudios
        if (empty($nivelEstudios)){
            $this->view->errorNivelEstudios = 'Debe seleccionar un nivel de estudios';
        	$correcto = false;
        }
                
		/**
		 * 1. Insertamos o actualizamos un usuario
		 * 2. Insertamos o actualizamos los roles del usuario. En este caso,
		 * 	  añadimos al usuario el rol de alumno
		 * 3. Insertamos o actualizamos un alumno
		 */
	    if ( $correcto ){

	    	// 1. Insertamos un usuario
	    	if ( $editar ){
	    		$usuarioDO = TblUsuario::findByPrimaryKey($this->db, $idUsuario);
	    	} else {
	    		$usuarioDO = new TblUsuario($this->db);
	    	}
	    	
	    	$usuarioDO->setVNombre($username);
	    	$usuarioDO->setVEmail($email);
	    	if ( $setPassword ){
	    		$usuarioDO->setVPassword($this->aclManager->codificaPassword($password));
	    	}
	    	
	    	// Empieza la transacción
		    $this->db->begin();
		    $this->db->disableForeignChecks();
	    	
	    	if ( $editar ){
	    		$correcto = $usuarioDO->update();
	    	} else {
	    		$correcto = $usuarioDO->insert();
	    	}
	    	
	    	// 2. Insertamos o actualizamos los roles del usuario
	    	if ( $correcto ){
	    		
	    		if ( $editar ){
	    			 $rolUsuarioDO = array_shift(TrelRolUsuario::findByTblUsuario($this->db, $idUsuario));
	    		} else {
	    			// Id del último usuario insertado
	    			$idUsuario = $this->db->getLastInsertId();
	    			$rolUsuarioDO = new TrelRolUsuario($this->db);
	    			$rolUsuarioDO->setFkUsuario($idUsuario);
	    			$rolUsuarioDO->setFkRol(PplAclManager::ROL_ALUMNO);
	    		}
	    		
	    		if ( $editar ){
		    		$correcto = $rolUsuarioDO->update();
		    	} else {
		    		$correcto = $rolUsuarioDO->insert();
		    	}
	    		
	    	}
	    	
	    	// 3. Insertamos o actualizamos un alumno
	    	if ( $correcto ){
	    	
		    	// Datos de la alumno
		    	
		    	if ( $editar ){
		    		$alumnoDO = TblPersona::findByPrimaryKey($this->db, $idAlumno);
		    	} else {
		    		$alumnoDO = new TblPersona($this->db);
		    	}
		    	
		    	$alumnoDO->setFkUsuario($idUsuario);
		    	$alumnoDO->setVNombre($nombre);
		    	$alumnoDO->setVPrimerApellido($apellido);
		    	$alumnoDO->setVSegundoApellido($apellido2);
		    	$alumnoDO->setVSexo($sexo);		    	
		    	$alumnoDO->setBDiscapacidad($discapacidad);		    	
		    	$alumnoDO->setDNacimiento(OwlDate::europeoAmericano($nacimiento));
		    	$alumnoDO->setFkTipoIdentificacion($tipoIdentificacion);
		    	$alumnoDO->setVNumeroIdentificacion($dni);
		    	$alumnoDO->setVNumeroSS($numeroSS);
		    	$alumnoDO->setFkPais($pais);
		    	$alumnoDO->setVTelefono($telefono);
		    	$alumnoDO->setVMovil($movil);
		    	$alumnoDO->setVDireccion($direccion);
		    	$alumnoDO->setVDireccion($direccion);
		    	$alumnoDO->setVCp($cp);
		    	$alumnoDO->setVPoblacion($poblacion);
		    	$alumnoDO->setFkProvincia($provincia);
		    	$alumnoDO->setFkPais($pais);
		    	$alumnoDO->setFkEstadoCivil($estadoCivil);
		    	$alumnoDO->setFkEstadoLaboral($estadoLaboral);
		    	$alumnoDO->setFkNivelEstudios($nivelEstudios);
		    	$alumnoDO->setVObservaciones($observaciones);
		    	$alumnoDO->setDAlta(date('Y-m-d'));
		    	$alumnoDO->setLastModified(date('Y-m-d'));
                $alumnoDO->setModUser($this->usuario->getNombre());
		    	
                // Situación laboral "Desocupado"
                $alumnoDO->setDAntiguedadParo(OwlDate::europeoAmericano($fechaParo));
                $alumnoDO->setFkTrabajoParo($trabajo);
                $alumnoDO->setFkCobros($cobro);
                
                // Situación laboral "Ocupado"
                $alumnoDO->setFkCategoriaEmpleo($categoriaEmpleo);
                $alumnoDO->setVSectorEmpresaActual($sectorEmpresaActual);
                $alumnoDO->setBMas250Trabajadores($trabajadores250);
                $alumnoDO->setVRazonSocialEmpresaActual($razonEmpresaActual);
                $alumnoDO->setVCifEmpresaActual($cif);
                $alumnoDO->setVDomicilioCentroTrabajo($domicilioEmpresaActual);
                $alumnoDO->setVLocalidadCentroTrabajo($localidadEmpresaActual);
                $alumnoDO->setVCpCentroTrabajo($cpEmpresaActual);
                
		    	if ( $editar ){
		    		$correcto = $alumnoDO->update();
		    	} else {
		    		$correcto = $alumnoDO->insert();
		    	}
		    	
	    	}
	    	
	    	// Cursos del alumno. Si estoy editando, borro todos los cursos para insertar los nuevos
	    	if ( $correcto ){
	    		
	    		if ( $editar ){
	    			$sql = 'DELETE FROM trelPrecandidato WHERE fkPersona = ' . $idAlumno;
	    			$this->db->executeQuery($sql);
	    		} else {
	    			$idAlumno = $this->db->getLastInsertId();
	    		}
	    		
	    		foreach ( $cursosARR as $idCurso ){
	    			
	    			// Antes de actualizar si es precandidato, compruebo que el alumno no sea candidato del curso
	    			$sql = 'SELECT COUNT(*) AS total FROM trelCandidato WHERE fkPersona = ' . $idAlumno . ' AND fkCurso = '. $idCurso;
	    			$this->db->executeQuery($sql);
		            $row = $this->db->fetchRow();
		            if (is_array($row) && array_key_exists('total', $row) && $row['total'] == 0){
		            	
		    			$sql = 'INSERT INTO trelPrecandidato VALUES (' . $idAlumno . ',' . $idCurso . ',\'' . date('Y-m-d') . '\')';
		    			if ( !$this->db->executeQuery($sql) ){
		    				$correcto = false;
		    			}
		    			
		            }
	    			
	    		}
	    		
	    	}
	    	
	    	// Carnets de conducir
	    	if ( $correcto ){
	    			
    			if ( $editar ){
	    			// Borramos los carnets antiguos
	    			$sql = "DELETE FROM trelPersonaCarnet WHERE fkPersona = ".$idAlumno;
	    			$this->db->executeQuery($sql);
    			} else {
    				$idAlumno = $this->db->getLastInsertId();
    			}
    			
    			if ( !empty($arrIdsCarnets) ){
	    				
	    			// Insertamos los carnets
		    		$carnetPersona = new TrelPersonaCarnet($this->db);
		    		$carnetPersona->setFkPersona($idAlumno);
		    		foreach ($arrIdsCarnets as $idCarnet) {
		    			$carnetPersona->setFkCarnet($idCarnet);
		    			if ( !$carnetPersona->insert() ){
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
    		$this->db->enableForeignChecks();
	    	
	    }
	    	
	    return $correcto;
    	
    }
    
    /**
     * Buscar Alumnos
     */
    public function buscarAction(){
        
        // Paises
        $this->view->paisesIDX = $this->cacheBO->getPaises();
        
        // Provincias
        $this->view->provinciasIDX = $this->cacheBO->getProvincias();
        
        // Búsqueda de alumnos
        $sent = $this->helper->getAndEscape('sent');
        
        if (!empty($sent)){
            
            // Parámetros de ordenación para el paginador
            $aliasCampos = array(
                'nom'   => 'vNombre',
                'pob'   => 'vPoblacion',
                'id'    => 'idPersona',
                'mov'   => 'vMovil'
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
            
            $where = array();
            $queryString = '&amp;sent=1';
            $queryARR['sent'] = 1;
            
            $id = $this->helper->getAndEscape('idPersona');
            $kw = $this->helper->getAndEscape('kw');
            $pais = $this->helper->getAndEscape('pais');
            $provincia = $this->helper->getAndEscape('provincia');
            
            // ID
            if (!empty($id)){
                $where[] = "idPersona = $id";
                $this->view->id = $id;
//                $queryString .= '&amp;idPersona=' . $id;
                $queryARR['idPersona'] = $id;
            }
            
            // KW
            if (!empty($kw)){
                $where[] = "vNombre LIKE '%$kw%' OR vPrimerApellido LIKE '%$kw%' OR vSegundoApellido LIKE '%$kw%' OR vNumeroIdentificacion LIKE '%$kw%'";
                $this->view->kw = $kw;
//                $queryString .= '&amp;kw=' . $kw;
                $queryARR['kw'] = $kw;
            }
            
            // PAIS
            if (!empty($pais)){
                $where[] = "fkPais = '$pais'";
                $this->view->pais = $pais;
//                $queryString .= '&amp;pais=' . $pais;
				$queryARR['pais'] = $pais;
            }
            
            // PROVINCIA
            if (!empty($provincia)){
                $where[] = "fkProvincia= $provincia";
                $this->view->provincia = $provincia;
//                $queryString .= '&amp;provincia=' . $provincia;
                $queryARR['provinci'] = $provincia;
            }
            
            // Se instancia y configura el paginador
            $rolAlumno = PplAclManager::ROL_ALUMNO;
            $where[] = ' EXISTS (SELECT null FROM trelRolUsuario ru WHERE ru.fkUsuario = p.fkUsuario AND ru.fkRol = ' . $rolAlumno . ') ';
            $whereStr = 'p WHERE ' . implode(' AND ', $where);
            
            // Se efectúa la búsqueda
            $paginador = new OwlPaginator($this->db, $whereStr , 'tblPersona', $this->helper);
            $paginador->setItemsPorPagina(10);
            $paginador->setOrderBy($orderBy);
            $paginador->setOrder($order);
            $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
            $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
            $paginador->setPaginaActual($paginaActual);
//            $paginador->setExtraParams($queryString);
            $paginador->setExtraParams($queryARR);
            
            // Obtengo los alumnos
            $alumnosCOL = $paginador->getItemCollection();
            $this->view->alumnosCOL = $alumnosCOL;
            
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