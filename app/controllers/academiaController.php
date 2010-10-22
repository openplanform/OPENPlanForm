<?php

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';
require_once 'helper/NingenNumeric.inc';
require_once 'helper/NingenString.inc';
require_once 'NingenPaginator.inc';

require_once NINGENCMS_MODULEDIR . 'menuPrincipalModule.php';
require_once NINGENCMS_MODULEDIR . 'logoutModule.php';
require_once NINGENCMS_MODULEDIR . 'barraHerramientasModule.php';

require_once NINGENCMS_MODELDIR . '/TblUsuario.inc';
require_once NINGENCMS_MODELDIR . '/TblEmpresa.inc';
require_once NINGENCMS_MODELDIR . '/TblPais.inc';
require_once NINGENCMS_MODELDIR . '/TblProvincia.inc';
require_once NINGENCMS_MODELDIR . '/TrelRolUsuario.inc';


class academiaController extends PplController{
    
    
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
    		'dir'	=> 'vDireccion',
    		'pob'	=> 'vPoblacion',
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
        $paginador = new NingenPaginator($this->db, 'e WHERE EXISTS ( SELECT NULL FROM trelRolUsuario ru WHERE e.fkUsuario = ru.fkUsuario AND ru.fkRol = ' . PplAclManager::ROL_ACADEMIA . ')', 'tblEmpresa', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo las academias
        $academiasCOL = $paginador->getItemCollection();
        
        // Envío el paginador a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
    	
    	// Academias
        $this->view->arrAcademiasDO = $academiasCOL;
        
    	if ( $this->aclManager->hasPerms('academia', 'editar') ){
    		$this->view->editar = true;
    	}
        
    }
    
    /**
     * Acción de alta
     * Da de alta una academia
     */
    public function altaAction(){
        
    	// Paises
        $this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
        
        // Provincias
        $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
        
   		// Doy de alta la academia
    	if ( $this->helper->get('send') ){
    		
   			if ( $this->actualizarInsertar() ){
   				
   				// Todo ha ido bien
    			$this->redirectTo('academia', 'index');
					
   			} else {

   				$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con el alta de academia. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
					
   			}
    	}
    	
    }
    
	/**
     * Acción de edición
     * Al duplicar una academia, se duplican los datos de la academia, pero no los datos del
     * usuario de dicha academia. Es necesario el parámetro 'duplicar' para indicarle a la vista
     * si le llega una duplicada o no.
     * Edita una academia
     */
    public function editarAction(){
        
    	// Obtengo la academia que voy a editar
    	$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	// Academia
        	$academiaDO = TblEmpresa::findByPrimaryKey($this->db, $paramsARR[0]);
        	$this->view->academiaDO = $academiaDO;
        	$this->view->duplicar = $duplicar = false;
        	
        	// Usuario de la academia
        	$this->view->usuarioDO = $academiaDO->getTblUsuario();
        	
        	// Paises
	       	$this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
	        
		    // Provincias
		    $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
	    
        } else {
        	
        	if ( NingenCmsSession::getValue('academiaDuplicada') instanceof TblEmpresa ){
        		
        		$academiaDO = NingenCmsSession::getValue('academiaDuplicada');
        		$this->view->academiaDO = $academiaDO;
        		$this->view->duplicar = $duplicar = true;
        		
        		// Paises
		       	$this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
		        
			    // Provincias
			    $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
        	}
        	
        }
        
    	// Actualizo la academia
    	if ( isset($academiaDO) && $this->helper->get('send') ){
    		
    		if ( $duplicar ){
    			$correcto = $this->actualizarInsertar();
    		} else {
    			$correcto = $this->actualizarInsertar(true, $academiaDO->getIdEmpresa(), $academiaDO->getTblUsuario()->getIdUsuario());
    		}
    		
    		if ( $correcto ){
    				
    			// Todo ha ido bien
    			$this->redirectTo('academia', 'index');
				
    		} else {
    			
    			$this->view->popup = array(
				    'estado' => 'ko',
				    'titulo' => 'Error',
				    'mensaje'=> 'Ha ocurrido un error con la edición de la academia. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
				    'url'=> '',
				);
				
    		}
    	}
        
    }
    
    /**
     * Acción de ficha
     * Ficha de una academia
     */
    public function fichaAction(){
        
   		$paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	// Academia
        	$academiaDO = TblEmpresa::findByPrimaryKey($this->db, $paramsARR[0]);
        	$this->view->academiaDO = $academiaDO;
        	
        	// Usuario de la academia
        	$this->view->usuarioDO = $academiaDO->getTblUsuario();
        	
        }
        
    }
    
	/**
     * Acción de eliminar
     * Elimina una academia
     */
    public function eliminarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$academiaDO = TblEmpresa::findByPrimaryKey($this->db, $paramsARR[0]);
        	$academiaDO->delete();
        	
        }
        
        $this->redirectTo('academia','index');
        
    }
    
	/**
     * Acción de duplicar
     * Duplica una academia
     */
    public function duplicarAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
        	
        	$academiaDO = TblEmpresa::findByPrimaryKey($this->db, $paramsARR[0]);
        	$nombreAcademia = 'Copia de ' . $academiaDO->getVNombre();
        	$academiaDO->setVNombre($nombreAcademia);
        	NingenCmsSession::setValue('academiaDuplicada', $academiaDO);
        	//$academiaDO->insert();
        }
        
        $this->redirectTo('academia','editar');
        
    }
    
	/**
     * Obtiene los datos de academia y realiza el alta o la actualización
     * @param boolean $editar
     * @param intenger $idAcademia
     * @return boolean $correcto
     */
    public function actualizarInsertar($editar = false, $idAcademia = '', $idUsuario = '') {
    	
	    $correcto = true;
	    		
     	// Comprobaciones pertinentes
     	
	    // Datos del usuario
	    
	    $username = $this->helper->escapeInjection($this->helper->get('nombreUsuario'));
	    $oldUsername = $this->helper->getAndEscape('nombreUsuarioOculto');
        $password = $this->helper->escapeInjection($this->helper->get('password1'));
        $repassword = $this->helper->escapeInjection($this->helper->get('repassword1'));
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
		        
	        }
        
        } else {
        	
        	// Contraseña
	        if (empty($password) || empty($repassword)){
	            $this->view->errorPassword = 'La contraseñas no puede estar vacía.';
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
        if (!NingenString::validaMail($email)){
            $this->view->errorEmail = 'La dirección de correo proporcionada no es correcta.';
            $correcto = false;
        }
	   	
        // Datos de la academia

        // Nombre
    	$nombre = $this->helper->escapeInjection($this->helper->get('nombre'));
	    if ( is_null($nombre) || empty($nombre) ){
	    	$correcto = false;
	    	$this->view->errorNombre = 'El nombre no puede estar vacío';
	    }
        
	    // Cif
    	$cif = $this->helper->escapeInjection($this->helper->get('cif'));
	    if ( is_null($cif) || empty($cif) ){
	    	$correcto = false;
	    	$this->view->errorCif = 'El cif no puede estar vacío';
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
	    
    	// CP
    	$cp = $this->helper->escapeInjection($this->helper->get('cp'));
	    if ( is_null($cp) || empty($cp) ){
	    	$cp = '';
	    }
	    
    	// Teléfono 1
    	$telefono1 = $this->helper->escapeInjection($this->helper->get('telefono1'));
	    if ( is_null($telefono1) || empty($telefono1) ){
	    	$telefono1 = '';
	    }
	    
	    // Teléfono 2
    	$telefono2 = $this->helper->escapeInjection($this->helper->get('telefono2'));
	    if ( is_null($telefono2) || empty($telefono2) ){
	    	$telefono2 = '';
	    }
	    
	    // Fax
    	$fax = $this->helper->escapeInjection($this->helper->get('fax'));
	    if ( is_null($fax) || empty($fax) ){
	    	$fax = '';
	    }
	    
		/**
		 * 1. Insertamos o actualizamos un usuario
		 * 2. Insertamos o actualizamos los roles del usuario. En este caso,
		 * 	  añadimos al usuario el rol de academia
		 * 3. Insertamos o actualizamos una academia
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
	    	$usuarioDO->setVPassword($this->aclManager->codificaPassword($password));
	    	
	    	// Empieza la transacción
		    $this->db->begin();
	    	
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
	    			$rolUsuarioDO->setFkRol(PplAclManager::ROL_ACADEMIA);
	    		}
	    		
	    		if ( $editar ){
		    		$correcto = $rolUsuarioDO->update();
		    	} else {
		    		$correcto = $rolUsuarioDO->insert();
		    	}
	    		
	    	}
	    	
	    	// 3. Insertamos o actualizamos una academia
	    	if ( $correcto ){
	    	
		    	// Datos de la academia
		    	
		    	if ( $editar ){
		    		$academiaDO = TblEmpresa::findByPrimaryKey($this->db, $idAcademia);
		    	} else {
		    		$academiaDO = new TblEmpresa($this->db);
		    	}
		    	
		    	$academiaDO->setFkUsuario($idUsuario);
		    	$academiaDO->setVNombre($nombre);
		    	$academiaDO->setVCif($cif);
		    	$academiaDO->setFkPais($pais);
		    	$academiaDO->setFkProvincia($provincia);
		    	$academiaDO->setVPoblacion($poblacion);
		    	$academiaDO->setVDireccion($direccion);
		    	$academiaDO->setVCp($cp);
		    	$academiaDO->setVTelefono($telefono1);
		    	$academiaDO->setVTelefono2($telefono2);
		    	$academiaDO->setVFax($fax);
		    	$academiaDO->setDAlta(date('Y-m-d'));
		    	
		    	if ( $editar ){
		    		$correcto = $academiaDO->update();
		    	} else {
		    		$correcto = $academiaDO->insert();
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