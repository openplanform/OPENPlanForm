<?php

require_once CLASSESDIR . 'PplController.inc';
require_once 'helper/OwlNumeric.inc';
require_once 'helper/OwlString.inc';
require_once 'OwlPaginator.inc';
require_once 'OwlGoogleMaps.inc';

require_once MODULEDIR . 'menuPrincipalModule.php';
require_once MODULEDIR . 'logoutModule.php';
require_once MODULEDIR . 'barraHerramientasModule.php';

require_once MODELDIR . '/TblUsuario.inc';
require_once MODELDIR . '/TblEmpresa.inc';
require_once MODELDIR . '/TblPais.inc';
require_once MODELDIR . '/TblProvincia.inc';
require_once MODELDIR . '/TrelRolUsuario.inc';


class academiaController extends PplController{
    
    
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
        $paginador = new OwlPaginator($this->db, 'e WHERE EXISTS ( SELECT NULL FROM trelRolUsuario ru WHERE e.fkUsuario = ru.fkUsuario AND ru.fkRol = ' . PplAclManager::ROL_ACADEMIA . ')', 'tblEmpresa', $this->helper);
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
        $this->view->academiasCOL = $academiasCOL;
        
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
        
        // Mapa para las coordenadas
        $this->view->cabeceraMapa = OwlGoogleMaps::echoCabeceraMapa();
        $mapaDO = new OwlGoogleMaps();
        $mapaDO->setLatitud('39.57420604477404');
		$mapaDO->setLongitud('2.655208557844162');
		$mapaDO->setMarcadorCoordenadas(true);
        $this->view->mapa = $mapaDO->echoMapa();
        
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
        	if (!$academiaDO = TblEmpresa::findByPrimaryKey($this->db, $paramsARR[0])){
                $this->redirectTo('academia', 'index');
                return;
            }
            
        	$this->view->academiaDO = $academiaDO;
        	$this->view->duplicar = $duplicar = false;
        	
        	// Usuario de la academia
        	$this->view->usuarioDO = $academiaDO->getTblUsuario();
        	
        } else {
        	
        	if ( OwlSession::getValue('academiaDuplicada') instanceof TblEmpresa ){
        		
        		$academiaDO = OwlSession::getValue('academiaDuplicada');
        		$this->view->academiaDO = $academiaDO;
        		$this->view->duplicar = $duplicar = true;
        		
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
        
    	// Datos para la vista
    	if ( isset($academiaDO) ){
    		
	    	// Mapa para las coordenadas
	        $this->view->cabeceraMapa = OwlGoogleMaps::echoCabeceraMapa();
	        $mapaDO = new OwlGoogleMaps();
	        $latitud = $academiaDO->getVLatitud();
	        $longitud = $academiaDO->getVLongitud();
	        
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
	        
	        // Paises
	       	$this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
	        
		    // Provincias
		    $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
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
        	
        	if ( !empty($academiaDO) ){
        		
        		$this->view->academiaDO = $academiaDO;
        	
	        	// Usuario de la academia
        		$this->view->usuarioDO = $academiaDO->getTblUsuario();
        		
        	}
        	
        }
        
    }
    
	/**
     * Acción de eliminar
     * Elimina el usuario de la academia, y en la bbdd
     * se elimina la academia en cascada
     */
    public function eliminarAction(){
        
        /**
         * @TODO Comprobar permisos
         */
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
            
        	if ($academiaDO = TblEmpresa::findByPrimaryKey($this->db, $paramsARR[0])){

        	   $claveUsuario = $academiaDO->getFkUsuario();
        	   if ($usuarioDO = TblUsuario::findByPrimaryKey($this->db, $claveUsuario))
        	   
                    if (!$usuarioDO->delete()){
                        
                        /**
                         * @TODO Mostrar error (No se pudo borrar el usuario) 
                         */
                        $this->redirectTo('academia','index');
                        return;
                        
                    }
                    
                    /**
                     * @TODO BORRADO OK (REDIRIGIR A DONDE SEA NECESARIO) 
                     */
                    $this->redirectTo('academia','index');
                    return;
        	   
        	   } else {
        	       
        	        /**
                     * @TODO Mostrar error (El usuario no existe) 
                     */
                    $this->redirectTo('academia','index');
                    return;
        	       
        	       
        	   }
        	    
        	    
        	} else {
        	    
        	    /**
        	     * @TODO Mostrar error (La academia no existe) 
        	     */
        	    $this->redirectTo('academia','index');
        	    
        	}
        	
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
        	$academiaDO->setVCif('');
        	OwlSession::setValue('academiaDuplicada', $academiaDO);
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
	   	
        // Datos de la academia

        // Nombre
    	$nombre = $this->helper->escapeInjection($this->helper->get('nombre'));
	    if ( is_null($nombre) || empty($nombre) ){
	    	$correcto = false;
	    	$this->view->errorNombre = 'El nombre no puede estar vacío';
	    }
        
	    // Cif
    	$cif = $this->helper->escapeInjection($this->helper->get('cif'));
    	$oldCif = $this->helper->escapeInjection($this->helper->get('cifOculto'));
	    if ( is_null($cif) || empty($cif) ){
	    	
	    	$correcto = false;
	    	$this->view->errorCif = 'El cif no puede estar vacío';
	    	
	    } else {
        	
        	// Comprobamos que el número no exista ya en la bbdd
        	if ( !$editar || ($editar && $cif != $oldCif) ){
		        $sql = "SELECT COUNT(*) AS total FROM tblEmpresa WHERE vCif = '" . $cif . "'";
		        $this->db->executeQuery($sql);
		        $row = $this->db->fetchRow();
		        if (is_array($row) && array_key_exists('total', $row) && $row['total'] != 0){
		            $this->view->errorCif = 'El CIF ya está registrado';
		            $correcto = false;     
		        }
        	}
        	
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
	    
    	// Persona contacto
    	$contacto = $this->helper->escapeInjection($this->helper->get('contacto'));
	    if ( is_null($contacto) || empty($contacto) ){
	    	$correcto = false;
	    	$this->view->errorContacto = 'El contacto no puede estar vacío';
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
	    	if ( $setPassword ){
	    		$usuarioDO->setVPassword($this->aclManager->codificaPassword($password));
	    	}
	    	
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
		    	$academiaDO->setVTelefono(str_ireplace(' ', '', $telefono1));
		    	$academiaDO->setVTelefono2(str_ireplace(' ', '', $telefono2));
		    	$academiaDO->setVFax(str_ireplace(' ', '', $fax));
		    	$academiaDO->setVLatitud($latitud);
		    	$academiaDO->setVLongitud($longitud);
		    	$academiaDO->setVPersonaContacto($contacto);
		    	$academiaDO->setDAlta(date('Y-m-d'));
		    	$academiaDO->setLastModified(date('Y-m-d'));
                $academiaDO->setModUser($this->usuario->getNombre());
		    	
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
    
    /**
     * Buscar
     */
    public function buscarAction(){
        
        // Paises 
        $this->view->paisesIDX = $this->cacheBO->getPaises();
        
        // Provincias
        $this->view->provinciasIDX = $this->cacheBO->getProvincias();
        
        $sent = $this->helper->getAndEscape('sent');
        if (!empty($sent)){

            // Solo comprobaremos permisos de edición si hay resultados
            if ( $this->aclManager->hasPerms('consultora', 'editar') ){
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
            $id = $this->helper->getAndEscape('idAcademia');
            $pais = $this->helper->getAndEscape('pais');
            $provincia = $this->helper->getAndEscape('provincia');
            $cif = $this->helper->getAndEscape('cif');
            $cp = $this->helper->getAndEscape('cp');
            $kw = $this->helper->getAndEscape('keyword');
            
            $where = array();
            
            // Sólo consultoras
            $claveRolAcademia = PplAclManager::ROL_ACADEMIA;
            $where[] = "EXISTS (SELECT NULL FROM trelRolUsuario WHERE trelRolUsuario.fkUsuario = tblEmpresa.fkUsuario AND trelRolUsuario.fkRol = $claveRolAcademia )";
            
            $queryString = '&amp;sent=1';
            $queryARR['sent'] = 1;
            
            // ID
            if (!empty($id)){
                $where[] = " idEmpresa = $id";
                $this->view->id = $id;
//                $queryString .= "&amp;idEmpresa=$id";
                $queryARR['idEmpresa'] = $id;
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

            // CIF
            if (!empty($cif)){
                $where[] = " vCif = '$cif'";
                $this->view->cif = $cif;
//                $queryString .= "&amp;cif=$cif";
                $queryARR['cif'] = $cif;
            }

            // CP
            if (!empty($cp)){
                $where[] = " vCp = $cp";
                $this->view->cp = $cp;
//                $queryString .= "&amp;cp=$cp";
                $queryARR['cp'] = $cp;
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
            $paginador = new OwlPaginator($this->db, $where, 'tblEmpresa', $this->helper);
            $paginador->setItemsPorPagina(10);
            $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
            $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
            $paginador->setPaginaActual($paginaActual);
            $paginador->setOrderBy($orderBy);
            $paginador->setOrder($order);
//            $paginador->setExtraParams($queryString);
            $paginador->setExtraParams($queryARR);
        
            // Obtengo las convocatorias
            $academiasCOL = $paginador->getItemCollection();
            $this->view->academiasCOL = $academiasCOL;        
            
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