<?php

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';
require_once NINGENCMS_MODELDIR . 'TblPais.inc';
require_once NINGENCMS_MODELDIR . 'TblProvincia.inc';
require_once NINGENCMS_MODELDIR . 'TblUsuario.inc';
require_once NINGENCMS_MODELDIR . 'TrelRolUsuario.inc';

require_once 'helper/NingenCmsHtmlHelper.inc';
require_once 'helper/NingenString.inc';
require_once 'NingenPaginator.inc';


class consultoraController extends PplController{
    
    
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
        
        // Se instancia y configura el paginador
        $paginador = new NingenPaginator($this->db, 'e WHERE EXISTS ( SELECT NULL FROM trelRolUsuario ru WHERE e.fkUsuario = ru.fkUsuario AND ru.fkRol = ' . PplAclManager::ROL_CONSULTORA . ')', 'tblEmpresa', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
         // Obtengo las academias
        $consultorasCOL = $paginador->getItemCollection();
        
        // Envío el paginador a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();
        
        // Academias
        $this->view->consultorasCOL = $consultorasCOL;
        
        if ( $this->aclManager->hasPerms('consultora', 'editar') ){
            $this->view->editar = true;
        }
        
    }
    
    /**
     * Acción de alta
     * Da de alta una consultora
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
                $this->redirectTo('consultora', 'index');
                    
            } else {

                $this->view->popup = array(
                    'estado' => 'ko',
                    'titulo' => 'Error',
                    'mensaje'=> 'Ha ocurrido un error con el alta de consultora. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                    'url'=> '',
                );
                    
            }
        }        
        
    }
    
    /**
     * Acción de ficha
     * Ficha de una consultora
     */
    public function fichaAction(){
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
            
            // consultora
            $consultoraDO = TblEmpresa::findByPrimaryKey($this->db, $paramsARR[0]);
            $this->view->consultoraDO = $consultoraDO;
            
            // Usuario de la consultora
            $this->view->usuarioDO = $consultoraDO->getTblUsuario();
            
        }        
        
    }
    
    /**
     * Acción de duplicar
     * Duplica una academia
     */
    public function duplicarAction(){
        
        $this->bypassLayout();
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
            
            $consultoraDO = TblEmpresa::findByPrimaryKey($this->db, $paramsARR[0]);
            $nombreconsultora = 'Copia de ' . $consultoraDO->getVNombre();
            $consultoraDO->setVNombre($nombreconsultora);
            NingenCmsSession::setValue('consultoraDuplicada', $consultoraDO);
            //$consultoraDO->insert();
        }
        
        $this->redirectTo('consultora','editar');
        
    }    
    
    /**
     * Acción de editar
     * Editar una consultora
     */
    public function editarAction(){
        
        // Obtengo la consultora que voy a editar
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
            
            // consultora
            $consultoraDO = TblEmpresa::findByPrimaryKey($this->db, $paramsARR[0]);
            $this->view->consultoraDO = $consultoraDO;
            $this->view->duplicar = $duplicar = false;
            
            // Usuario de la consultora
            $this->view->usuarioDO = $consultoraDO->getTblUsuario();
            
            // Paises
            $this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
            
            // Provincias
            $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
        
        } else {
            
            if ( NingenCmsSession::getValue('consultoraDuplicada') instanceof TblEmpresa ){
                
                $consultoraDO = NingenCmsSession::getValue('consultoraDuplicada');
                $this->view->consultoraDO = $consultoraDO;
                $this->view->duplicar = $duplicar = true;
                
                // Paises
                $this->view->paisesCOL = TblPais::findAll($this->db, 'vIso');
                
                // Provincias
                $this->view->provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
            }
            
        }
        
        // Actualizo la consultora
        if ( isset($consultoraDO) && $this->helper->get('send') ){
            
            if ( $duplicar ){
                $correcto = $this->actualizarInsertar();
            } else {
                $correcto = $this->actualizarInsertar(true, $consultoraDO->getIdEmpresa(), $consultoraDO->getTblUsuario()->getIdUsuario());
            }
            
            if ( $correcto ){
                    
                // Todo ha ido bien
                $this->redirectTo('consultora', 'index');
                
            } else {
                
                $this->view->popup = array(
                    'estado' => 'ko',
                    'titulo' => 'Error',
                    'mensaje'=> 'Ha ocurrido un error con la edición de la consultora. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                    'url'=> '',
                );
                
            }
        }
        
    }
    
	/**
     * Acción de eliminar
     * Elimina el usuario de la consultora, y en la bbdd
     * se elimina la consultora en cascada
     */
    public function eliminarAction(){
        
        /**
         * @TODO Comprobar permisos
         */
        
        $paramsARR = $this->getParams();
        if ( !empty($paramsARR) ){
            
        	if ($consultoraDO = TblEmpresa::findByPrimaryKey($this->db, $paramsARR[0])){

        	   $claveConsultora = $consultoraDO->getFkUsuario();
        	   if ($usuarioDO = TblUsuario::findByPrimaryKey($this->db, $claveConsultora))
        	   
                    if (!$usuarioDO->delete()){
                        
                        /**
                         * @TODO Mostrar error (No se pudo borrar el usuario) 
                         */
                        $this->redirectTo('consultora','index');
                        return;
                        
                    }
                    
                    /**
                     * @TODO BORRADO OK (REDIRIGIR A DONDE SEA NECESARIO) 
                     */
                    $this->redirectTo('consultora','index');
                    return;
        	   
        	   } else {
        	       
        	        /**
                     * @TODO Mostrar error (El usuario no existe) 
                     */
                    $this->redirectTo('consultora','index');
                    return;
        	       
        	       
        	   }
        	    
        	    
        	} else {
        	    
        	    /**
        	     * @TODO Mostrar error (La consultora no existe) 
        	     */
        	    $this->redirectTo('consultora','index');
        	    
        	}
        	
    }
    
    /**
     * Obtiene los datos de academia y realiza el alta o la actualización
     * @param boolean $editar
     * @param intenger $idConsultora
     * @return boolean $correcto
     */
    public function actualizarInsertar($editar = false, $idConsultora = '', $idUsuario = '') {
        
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
                
            // Cambia de usuario pero no de contraseña
	        } else if ( $username != $oldUsername ){
	        	
	        	$this->view->errorPassword = 'La contraseña no puede estar vacía.';
		        $correcto = false;
		            
	        // No cambia de usuario ni de contraseña
	        } else {
	        	$setPassword = false;
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
    	$oldCif = $this->helper->escapeInjection($this->helper->get('oldCif'));
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
         *    añadimos al usuario el rol de academia
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
                    $rolUsuarioDO->setFkRol(PplAclManager::ROL_CONSULTORA);
                }
                
                if ( $editar ){
                    $correcto = $rolUsuarioDO->update();
                } else {
                    $correcto = $rolUsuarioDO->insert();
                }
                
            }
            
            // 3. Insertamos o actualizamos una consultora
            if ( $correcto ){
            
                // Datos de la academia
                
                if ( $editar ){
                    $consultoraDO = TblEmpresa::findByPrimaryKey($this->db, $idConsultora);
                } else {
                    $consultoraDO = new TblEmpresa($this->db);
                }
                
                $consultoraDO->setFkUsuario($idUsuario);
                $consultoraDO->setVNombre($nombre);
                $consultoraDO->setVCif($cif);
                $consultoraDO->setFkPais($pais);
                $consultoraDO->setFkProvincia($provincia);
                $consultoraDO->setVPoblacion($poblacion);
                $consultoraDO->setVDireccion($direccion);
                $consultoraDO->setVCp($cp);
                $consultoraDO->setVTelefono($telefono1);
                $consultoraDO->setVTelefono2($telefono2);
                $consultoraDO->setVFax($fax);
                $consultoraDO->setDAlta(date('Y-m-d'));
                
                if ( $editar ){
                    $correcto = $consultoraDO->update();
                } else {
                    $correcto = $consultoraDO->insert();
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
     * Buscar consultoras
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
            $id = $this->helper->getAndEscape('idConsultora');
            $pais = $this->helper->getAndEscape('pais');
            $provincia = $this->helper->getAndEscape('provincia');
            $cif = $this->helper->getAndEscape('cif');
            $cp = $this->helper->getAndEscape('cp');
            $kw = $this->helper->getAndEscape('keyword');
            
            $where = array();
            
            // Solo consultoras
            $claveRolConsultora = PplAclManager::ROL_CONSULTORA;
            $where[] = "EXISTS (SELECT NULL FROM trelRolUsuario WHERE trelRolUsuario.fkUsuario = tblEmpresa.fkUsuario AND trelRolUsuario.fkRol = $claveRolConsultora )";
            
            $queryString = '&amp;sent=1';
            
            // ID
            if (!empty($id)){
                $where[] = " idConsultora = $id";
                $this->view->id = $id;
                $queryString .= "&amp;idConsultora=$id";
            }
            
            // PAIS
            if (!empty($pais)){
                $where[] = " fkPais = '$pais'";
                $this->view->pais = $pais;
                $queryString .= "&amp;pais=$pais";
            }

            // PROVINCIA
            if (!empty($provincia)){
                $where[] = " fkProvincia = $provincia";
                $this->view->provincia = $provincia;
                $queryString .= "&amp;provincia=$provincia";
            }

            // CIF
            if (!empty($cif)){
                $where[] = " vCif = $cif";
                $this->view->cif = $cif;
                $queryString .= "&amp;cif=$cif";
            }

            // CP
            if (!empty($cp)){
                $where[] = " vCp = $cp";
                $this->view->cp = $cp;
                $queryString .= "&amp;cp=$cp";
            }
            
            // KEYWORD
            if (!empty($kw)){
                //$where[] = "vNombre LIKE '%$kw%' OR vDescripcion LIKE '%$kw%'";
                $where[] = "vNombre LIKE '%$kw%'";
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
            $paginador = new NingenPaginator($this->db, $where, 'tblEmpresa', $this->helper);
            $paginador->setItemsPorPagina(10);
            $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
            $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
            $paginador->setPaginaActual($paginaActual);
            $paginador->setOrderBy($orderBy);
            $paginador->setOrder($order);
        
            // Obtengo las convocatorias
            $consultorasCOL = $paginador->getItemCollection();
            $this->view->consultorasCOL = $consultorasCOL;        
            
            // Envío el paginador a la vista
            $this->view->paginador = $paginador->getPaginatorHtml();
            
            // Se propagan las clausulas de búsqueda en el paginador
            $this->view->querystring = $queryString;
            
            
        }        
        
    }
    
}

?>