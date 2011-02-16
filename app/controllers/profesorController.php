<?php

require_once 'helper/OwlString.inc';
require_once 'helper/OwlDate.inc';
require_once CLASSESDIR . 'PplController.inc';

require_once MODELDIR . 'TblCategoria.inc';
require_once MODELDIR . 'TblCarnetConducir.inc';
require_once MODELDIR . 'TblCurso.inc';
require_once MODELDIR . 'TblEstadoCivil.inc';
require_once MODELDIR . 'TblEstadoLaboral.inc';
require_once MODELDIR . 'TblNivelEstudios.inc';
require_once MODELDIR . 'TblPais.inc';
require_once MODELDIR . 'TblPersona.inc';
require_once MODELDIR . 'TblProvincia.inc';
require_once MODELDIR . 'TblTipoIdentificacion.inc';
require_once MODELDIR . 'TrelPersonaCarnet.inc';
require_once MODELDIR . 'TrelPersonaCategoria.inc';
require_once MODELDIR . 'TrelProfesor.inc';
require_once MODELDIR . 'TrelRolUsuario.inc';

require_once 'helper/OwlHtmlHelper.inc';
require_once 'dbase/OwlDatabase.inc';
require_once 'OwlPaginator.inc';


class profesorController extends PplController{
    
    /**
     * Colección de categorias
     * @var array
     */
    protected $categoriasCOL = null;
    
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
        $rolProfesor = PplAclManager::ROL_PROFESOR;
        $paginador = new OwlPaginator($this->db, 'p WHERE EXISTS (SELECT null FROM trelRolUsuario ru WHERE ru.fkUsuario = p.fkUsuario AND ru.fkRol = ' . $rolProfesor . ')', 'tblPersona', $this->helper);
        $paginador->setItemsPorPagina(20);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        
        // Categorías para profesores
        $categoriasProfesoresCOL = TrelPersonaCategoria::findAll($this->db, 'fkPersona');
        $this->view->categoriasProfesoresIDX = OwlDatabase::groupBy('fkPersona', $categoriasProfesoresCOL);
        
        // Categorias
        $categoriasCOL = TblCategoria::findAll($this->db, 'idCategoria');
        $this->view->categoriasIDX = OwlDatabase::indexFor('idCategoria', $categoriasCOL);
        
        // Obtengo todos los usuarios del sistema
        $profesoresCOL = $paginador->getItemCollection();
        
        // Envio el paginador a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();

        // Verificamos que el usuario actual tenga permisos para editar y/o eliminar desde el listado
        $this->view->editar = $this->aclManager->hasPerms('profesor', 'editar');
        
        // Paso los datos a la vista
        $this->view->profesoresCOL = $profesoresCOL;

        
        
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
        
        // Carnets de conducir
	    $this->view->carnetsCOL = TblCarnetConducir::findAll($this->db,'vNombre');
        
         // Categorías
        $arbolDS = array();
        $arbolDS = $this->_IteraCategorias($arbolDS, 0);
        $this->view->htmlSelectCategorias = $this->_getSelectHtml($arbolDS, 0);
        
   		// Doy de alta la persona
    	if ( $this->helper->get('send') ){
    		
   			if ( $this->actualizarInsertar() ){
   				
   				// Todo ha ido bien
    			$this->redirectTo('profesor', 'index');
					
   			} else {

   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con el alta de profesor. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
					
   			}
    	}
        
    }
    
	/**
     * Acción de edición
     * Al duplicar un profesor, se copian los datos del profesor, pero no los datos del
     * usuario del profesor. Es necesario el parámetro 'duplicar' para indicarle a la vista
     * si le llega una duplicada o no.
     * Edita un profesor
     */
    public function editarAction(){
        
    	// Obtengo el profesor que voy a editar
    	$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	// Profesor
        	if (!$profesorDO = TblPersona::findByPrimaryKey($this->db, $paramsARR[0])){
                $this->redirectTo('profesor', 'index');
                return;
            }
            
        	$this->view->profesorDO = $profesorDO;
        	$this->view->duplicar = $duplicar = false;
        	
        	// Usuario del profesor
        	$this->view->usuarioDO = $profesorDO->getTblUsuario();
        	
        } else {
        	
        	if ( OwlSession::getValue('profesorDuplicado') instanceof TblPersona ){
        		
        		$profesorDO = OwlSession::getValue('profesorDuplicado');
        		$this->view->profesorDO = $profesorDO;
        		$this->view->duplicar = $duplicar = true;
        		
        	}
        	
        }
        
        if ( isset($profesorDO) ){
        	
        	// Categorías. Obtengo los ids de las categorías del profesor, y los paso a la función recursiva que
	       	// recorre las categorías para que marque las seleccionadas
	       	$personaCategoriasARR = TrelPersonaCategoria::findByTblPersona($this->db, $profesorDO->getIdPersona());
	       	$idsCategorias = array();
	       	foreach ( $personaCategoriasARR as $personaCategoriaDO ){
	       		$idsCategorias[] = $personaCategoriaDO->getFkCategoria();
	       	}
	       	
	        $arbolDS = array();
	        $arbolDS = $this->_IteraCategorias($arbolDS, 0);
	        $this->view->htmlSelectCategorias = $this->_getSelectHtml($arbolDS, 0, $idsCategorias);
	        
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
	        
	         // Carnets de conducir
	    	$this->view->carnetsCOL = TblCarnetConducir::findAll($this->db,'vNombre');
	    	
	    	// Carnets del alumno
	    	$this->view->carnetsProfesorCOL = TrelPersonaCarnet::findByTblPersona($this->db, $profesorDO->getIdPersona());
        
        }
        
    	// Actualizo el profesor
    	if ( isset($profesorDO) && $this->helper->get('send') ){
    		
    		if ( $duplicar ){
    			$correcto = $this->actualizarInsertar();
    		} else {
    			$correcto = $this->actualizarInsertar(true, $profesorDO->getIdPersona(), $profesorDO->getTblUsuario()->getIdUsuario());
    		}
    		
    		if ( $correcto ){
    				
    			// Todo ha ido bien
    			$this->redirectTo('profesor', 'index');
        	
    		} else {
    			
    			$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con la edición del profesor. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
				
    		}
    	}
        
    }
    
	/**
     * Acción de ficha
     * Ficha de un profesor
     */
    public function fichaAction(){
        
   		$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	// Profesor
        	$profesorDO = TblPersona::findByPrimaryKey($this->db, $paramsARR[0]);
        	if ( !empty($profesorDO) ){

        		$this->view->profesorDO = $profesorDO;
        	
        		// Usuario del profesor
        		$this->view->usuarioDO = $profesorDO->getTblUsuario();
        		
        		// Categorías
        		$this->view->categoriasIDX = $this->cacheBO->getCategorias();
        		
        		// Categorías del profesor
        		$categoriasProfesoresIDX = $this->cacheBO->getProfesoresCategorias();
        		$this->view->categoriasProfesorARR = $categoriasProfesoresIDX[$profesorDO->getIdPersona()];
        		
        		// Cursos que imparte
        		$this->view->cursosImpartidosCOL = TrelProfesor::findByTblPersona($this->db, $profesorDO->getIdPersona());
        		
        		// Cursos
        		$this->view->cursosCOL = TblCurso::findAll($this->db);
        		
        		// Carnets
        		$this->view->carnetsIDX = $this->cacheBO->getCarnets();
        		
        		// Carnets del alumno
	    		$this->view->carnetsProfesorCOL = TrelPersonaCarnet::findByTblPersona($this->db, $profesorDO->getIdPersona());
	    		
        	}
        	
        }
        
    }
    
	/**
     * Acción de eliminar
     * Elimina el usuario del profesor, y en la bbdd
     * se elimina el profesor en cascada
     */
    public function eliminarAction(){
        
        /**
         * @TODO Comprobar permisos
         */
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
            
        	if ($profesorDO = TblPersona::findByPrimaryKey($this->db, $paramsARR[0])){

        	   $claveUsuario = $profesorDO->getFkUsuario();
        	   if ($usuarioDO = TblUsuario::findByPrimaryKey($this->db, $claveUsuario))
        	   
                    if (!$usuarioDO->delete()){
                        
                        /**
                         * @TODO Mostrar error (No se pudo borrar el usuario) 
                         */
                        $this->redirectTo('profesor','index');
                        return;
                        
                    }
                    
                    /**
                     * @TODO BORRADO OK (REDIRIGIR A DONDE SEA NECESARIO) 
                     */
                    $this->redirectTo('profesor','index');
                    return;
        	   
        	   } else {
        	       
        	        /**
                     * @TODO Mostrar error (El usuario no existe) 
                     */
                    $this->redirectTo('profesor','index');
                    return;
        	       
        	       
        	   }
        	    
        	    
        	} else {
        	    
        	    /**
        	     * @TODO Mostrar error (La persona no existe) 
        	     */
        	    $this->redirectTo('profesor','index');
        	    
        	}
        	
    }
    
    
	/**
     * Acción de duplicar
     * Duplica una profesor
     */
    public function duplicarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	$profesorDO = TblPersona::findByPrimaryKey($this->db, $paramsARR[0]);
        	$nombreProfesor = 'Copia de ' . $profesorDO->getVNombre();
        	$profesorDO->setVNombre($nombreProfesor);
        	$profesorDO->setVNumeroIdentificacion('');
        	OwlSession::setValue('profesorDuplicado', $profesorDO);
        }
        
        $this->redirectTo('profesor','editar');
        
    }
    
	/**
     * Función recursiva para tratar las categorias
     * @param array $arrayDS
     * @param integer $clavePadre
     * @param integer $nivel
     */
    private function _IteraCategorias($arrayDS, $clavePadre){
        
    	if (is_null($this->categoriasCOL)){
    	   $this->categoriasCOL = TblCategoria::findAll($this->db, 'idCategoria ASC');
        }
    	
        foreach ($this->categoriasCOL as $categoriaDO){
            
            if ($categoriaDO->getFkPadre() == $clavePadre){
                $arrayDS[$categoriaDO->getIdCategoria()]['nombre'] = $categoriaDO->getVNombre();
                $arrayDS[$categoriaDO->getIdCategoria()]['DO'] = $categoriaDO;
                $arrayDS[$categoriaDO->getIdCategoria()]['hijos'] = array();
                $arrayDS[$categoriaDO->getIdCategoria()]['hijos'] = $this->_IteraCategorias($arrayDS[$categoriaDO->getIdCategoria()]['hijos'], $categoriaDO->getIdCategoria());
            }
            
        }
        
        return $arrayDS;
        
    }
    
    /**
     * 
     * prepara el código html para el árbol de categoria
     * @param array $arbolDS
     */
    private function _getSelectHtml($arbolDS, $nivel, $selected = array()){
        
        $nivel++;
        $html = '';
        
        foreach ($arbolDS as $clave => $arbol){

            if (count($arbol['hijos'])){
            	$html .= '<optgroup label="' . $arbol['nombre'] . '">';
                $html .= $this->_getSelectHtml($arbol['hijos'], $nivel, $selected);
                $html .= '</optgroup>';
            } else {
            	$sel = ( in_array($clave, $selected) ) ? 'selected="selected"' : '';
            	$html .= '<option value="' . $clave .'" ' . $sel . '>' . str_ireplace('_', '', $arbol['nombre']) . '</option>';
            }
            
        }
        
        return $html;
        
    }
    
	/**
     * Obtiene los datos de profesor y realiza el alta o la actualización
     * @param boolean $editar
     * @param intenger $idProfesor
     * @return boolean $correcto
     */
    public function actualizarInsertar($editar = false, $idProfesor = '', $idUsuario = '') {
    	
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
	   	
        // Datos del profesor

    	$nombre = $this->helper->getAndEscape('nombre');
        $apellido = $this->helper->getAndEscape('apellido1'); 
        $apellido2 = $this->helper->getAndEscape('apellido2'); 
        $nacimiento = $this->helper->getAndEscape('nacimiento');
        $tipoIdentificacion = $this->helper->getAndEscape('tipoIdentificacion'); 
        $dni = $this->helper->getAndEscape('dni');
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
    	$categoriasARR = array();
        if ( array_key_exists('categorias', $_POST) ){
        	foreach ($_POST['categorias'] as $categoria) {
            	$categoriasARR[] = $this->helper->escapeInjection($categoria);
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

        // Provincia
        if (empty($provincia)){
            $provincia = '';
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
		 * 	  añadimos al usuario el rol de profesor
		 * 3. Insertamos o actualizamos un profesor
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
	    			$rolUsuarioDO->setFkRol(PplAclManager::ROL_PROFESOR);
	    		}
	    		
	    		if ( $editar ){
		    		$correcto = $rolUsuarioDO->update();
		    	} else {
		    		$correcto = $rolUsuarioDO->insert();
		    	}
	    		
	    	}
	    	
	    	// 3. Insertamos o actualizamos una profesor
	    	if ( $correcto ){
	    	
		    	// Datos de la profesor
		    	
		    	if ( $editar ){
		    		$profesorDO = TblPersona::findByPrimaryKey($this->db, $idProfesor);
		    	} else {
		    		$profesorDO = new TblPersona($this->db);
		    	}
		    	
		    	$profesorDO->setFkUsuario($idUsuario);
		    	$profesorDO->setVNombre($nombre);
		    	$profesorDO->setVPrimerApellido($apellido);
		    	$profesorDO->setVSegundoApellido($apellido2);
		    	$profesorDO->setDNacimiento(OwlDate::europeoAmericano($nacimiento));
		    	$profesorDO->setFkTipoIdentificacion($tipoIdentificacion);
		    	$profesorDO->setVNumeroIdentificacion($dni);
		    	$profesorDO->setFkPais($pais);
		    	$profesorDO->setVTelefono($telefono);
		    	$profesorDO->setVMovil($movil);
		    	$profesorDO->setVDireccion($direccion);
		    	$profesorDO->setVDireccion($direccion);
		    	$profesorDO->setVCp($cp);
		    	$profesorDO->setVPoblacion($poblacion);
		    	$profesorDO->setFkProvincia($provincia);
		    	$profesorDO->setFkPais($pais);
		    	$profesorDO->setFkEstadoCivil($estadoCivil);
		    	$profesorDO->setFkEstadoLaboral($estadoLaboral);
		    	$profesorDO->setFkNivelEstudios($nivelEstudios);
		    	$profesorDO->setVObservaciones($observaciones);	    	
		    	$profesorDO->setDAlta(date('Y-m-d'));
		    	$profesorDO->setLastModified(date('Y-m-d'));
                $profesorDO->setModUser($this->usuario->getNombre());
		    	
		    	if ( $editar ){
		    		$correcto = $profesorDO->update();
		    	} else {
		    		$correcto = $profesorDO->insert();
		    	}
		    	
	    	}
	    	
	    	// Categorías del profesor. Si estoy editando, borro todas las categorías para insertar las nuevas.
	    	if ( $correcto ){
	    		
	    		if ( $editar ){
	    			$sql = 'DELETE FROM trelPersonaCategoria WHERE fkPersona = ' . $idProfesor;
	    			$this->db->executeQuery($sql);
	    		} else {
	    			$idProfesor = $this->db->getLastInsertId();
	    		}
	    		
	    		foreach ( $categoriasARR as $idCategoria ){
	    			$sql = 'INSERT INTO trelPersonaCategoria VALUES (' . $idProfesor . ',' . $idCategoria . ')';
	    			if ( !$this->db->executeQuery($sql) ){
	    				$correcto = false;
	    			}
	    			
	    		}
	    	}
	    	
	    	// Carnets de conducir
	    	if ( $correcto ){
	    			
    			if ( $editar ){
	    			// Borramos los carnets antiguos
	    			$sql = "DELETE FROM trelPersonaCarnet WHERE fkPersona = ".$idProfesor;
	    			$this->db->executeQuery($sql);
    			} else {
    				$idAlumno = $this->db->getLastInsertId();
    			}
    			
    			if ( !empty($arrIdsCarnets) ){
	    				
	    			// Insertamos los carnets
		    		$carnetPersona = new TrelPersonaCarnet($this->db);
		    		$carnetPersona->setFkPersona($idProfesor);
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
    			$this->db->enableForeignChecks();
    			$this->db->commit();
    		} else {
    			$this->db->enableForeignChecks();
    			$this->db->rollback();
    		}
	    	
	    }
	    	
	    return $correcto;
    	
    }
    
    /**
     * Buscar Profesores
     */
    public function buscarAction(){
        
        // Paises
        $this->view->paisesIDX = $this->cacheBO->getPaises();
        
        // Provincias
        $this->view->provinciasIDX = $this->cacheBO->getProvincias();
        
         // Categorías
        $arbolDS = array();
        $arbolDS = $this->_IteraCategorias($arbolDS, 0);
        $this->view->htmlSelectCategorias = $this->_getSelectHtml($arbolDS, 0);
        
        // Búsqueda de profesores
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
            $poblacion = $this->helper->getAndEscape('poblacion');
            $categorias = $this->helper->getAndEscape('categorias');
            
            // ID
            if (!empty($id)){
                $where[] = "idPersona = $id";
                $this->view->id = $id;
//                $queryString .= '&amp;idPersona=' . $id;
                $queryARR['idPersona'] = $id;
            } else {
	            $queryARR['idPersona'] = '';
	        }
            
            // KW
            if (!empty($kw)){
                $where[] = "vNombre LIKE '%$kw%' OR vPrimerApellido LIKE '%$kw%' OR vSegundoApellido LIKE '%$kw%' OR vNumeroIdentificacion LIKE '%$kw%'";
                $this->view->kw = $kw;
//                $queryString .= '&amp;kw=' . $kw;
                $queryARR['kw'] = $kw;
            } else {
	            $queryARR['kw'] = '';
	        }
            
            // PAIS
            if (!empty($pais)){
                $where[] = "fkPais = '$pais'";
                $this->view->pais = $pais;
//                $queryString .= '&amp;pais=' . $pais;
                $queryARR['pais'] = $pais;
            } else {
	            $queryARR['pais'] = '';
	        }
            
            // PROVINCIA
            if (!empty($provincia)){
                $where[] = "fkProvincia= $provincia";
                $this->view->provincia = $provincia;
//                $queryString .= '&amp;provincia=' . $provincia;
                $queryARR['provincia'] = $provincia;
            } else {
	            $queryARR['provincia'] = '';
	        }
            
	         // POBLACIÓN
            if (!empty($poblacion)){
                $where[] = "vPoblacion LIKE '%$poblacion%'";
                $this->view->poblacion = $poblacion;
//                $queryString .= '&amp;poblacion=' . $poblacion;
                $queryARR['poblacion'] = $poblacion;
            } else {
	            $queryARR['poblacion'] = '';
	        }
            
            // CATEGORÍAS
            // Pueden venir como un array o como un string
            if (is_array($categorias) || !empty($categorias)){
                if ( is_array($categorias) ){
                	$catsStr = implode(',', $categorias);	
                } else {
                	$catsStr = $categorias;
                	// Si hay más de una categoría, no se marca en el selector si no se le pasa un array
                	$categorias = explode(',', $categorias);
                }
                $where[] = " EXISTS (SELECT null FROM trelPersonaCategoria WHERE p.idPersona = trelPersonaCategoria.fkPersona AND trelPersonaCategoria.fkCategoria IN($catsStr))";
                $this->view->htmlSelectCategorias = $this->_getSelectHtml($arbolDS, 0, $categorias);
                $queryARR['categorias'] = $catsStr;
//                $where[] = " EXISTS (SELECT null FROM trelPersonaCategoria WHERE tblPersona.idPersona = trelPersonaCategoria.fkPersona AND trelPersonaCategoria.fkCategoria IN($catsStr))";
//                $queryString .= '&amp;categorias=' . $catsStr;
            }
            
            // Se instancia y configura el paginador
            $rolProfesor = PplAclManager::ROL_PROFESOR;
            $where[] = ' EXISTS (SELECT null FROM trelRolUsuario ru WHERE ru.fkUsuario = p.fkUsuario AND ru.fkRol = ' . $rolProfesor . ') ';
            $whereStr = 'p WHERE ' . implode(' AND ', $where);
            
            // Se efectúa la búsqueda
            $paginador = new OwlPaginator($this->db, $whereStr , 'tblPersona', $this->helper);
            $paginador->setItemsPorPagina(10);
            $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
            $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
            $paginador->setPaginaActual($paginaActual);
            $paginador->setOrderBy($orderBy);
            $paginador->setOrder($order);
//            $paginador->setExtraParams($queryString);
            $paginador->setExtraParams($queryARR);
            
            // Obtengo los profesores
            $profesoresCOL = $paginador->getItemCollection();
            $this->view->profesoresCOL = $profesoresCOL;
            
            // Envío el paginador a la vista
            $this->view->paginador = $paginador->getPaginatorHtml();
            
            // Se propagan las clausulas de búsqueda en el paginador
            foreach ( $queryARR as $clave => $valor ){
            	$queryString .= '&amp;' . $clave . '=' . $valor;
            }
            $this->view->querystring = $queryString;
            
            // Categorías para profesores
            $categoriasProfesoresCOL = TrelPersonaCategoria::findAll($this->db, 'fkPersona');
            $this->view->categoriasProfesoresIDX = OwlDatabase::groupBy('fkPersona', $categoriasProfesoresCOL);
            
            // Categorias
            $categoriasCOL = TblCategoria::findAll($this->db, 'idCategoria');
            $this->view->categoriasIDX = OwlDatabase::indexFor('idCategoria', $categoriasCOL);
            
            // Verificamos que el usuario actual tenga permisos para editar y/o eliminar desde el listado
        	$this->view->editar = $this->aclManager->hasPerms('profesor', 'editar');
        
        }
        
    }
    
}