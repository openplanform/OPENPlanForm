<?php

require_once 'NingenPaginator.inc';
require_once 'NingenMailer.inc';
require_once 'NingenMailerTemplate.inc';
require_once 'helper/NingenDate.inc';
require_once 'helper/NingenString.inc';

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';
require_once NINGENCMS_MODULEDIR . 'menuPrincipalModule.php';
require_once NINGENCMS_MODULEDIR . 'logoutModule.php';
require_once NINGENCMS_MODULEDIR . 'barraHerramientasModule.php';
require_once NINGENCMS_MODULEDIR . 'avisoModule.php';

require_once NINGENCMS_MODELDIR . 'TblUsuario.inc';
require_once NINGENCMS_MODELDIR . 'TblPersona.inc';
require_once NINGENCMS_MODELDIR . 'TblProvincia.inc';
require_once NINGENCMS_MODELDIR . 'TblPais.inc';
require_once NINGENCMS_MODELDIR . 'TrelRolUsuario.inc';
require_once NINGENCMS_MODELDIR . 'TblTipoIdentificacion.inc';
require_once NINGENCMS_MODELDIR . 'TblEstadoCivil.inc';
require_once NINGENCMS_MODELDIR . 'TblEstadoLaboral.inc';
require_once NINGENCMS_MODELDIR . 'TblNivelEstudios.inc';

class usuarioController extends PplController{
    
    
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
            'mail'  => 'vEmail',
            'id'  => 'idUsuario',
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

        // Guardaremos la clave del usuario actual, sólo para verificar si se intenta eliminar a si mismo
        $this->view->idUsuarioActual = $this->usuario->getId();
        
        // Se instancia y configura el paginador
        $paginador = new NingenPaginator($this->db, null, 'tblUsuario', $this->helper);
        $paginador->setItemsPorPagina(10);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
        $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
        $paginador->setPaginaActual($paginaActual);
        
        // Obtengo todos los usuarios del sistema
        $usuariosCOL = $paginador->getItemCollection();
        
        // Envio el paginador a la vista
        $this->view->paginador = $paginador->getPaginatorHtml();

        // Obtengo todos los roles 
        $rolesCOL = $this->aclManager->getRoles();
        
        // Obtengo todos los roles asignados a todos los usuarios
        $rolesUsuariosCOL = TrelRolUsuario::findAll($this->db, 'fkUsuario ASC');
        
        // Prepararé un array con todos los datos a mostrar en la vista 
        // indexados por la clave de usuario
        $resultIDX = array();
        
        foreach ($usuariosCOL as $usuarioDO){
            
            $idUsuario = $usuarioDO->getIdUsuario();
            $nombresRolesUsuario = array();
            
            // Roles del usuario
             foreach ($rolesUsuariosCOL as $rolUsuarioDO){
                 
                 if ($idUsuario == $rolUsuarioDO->getFkUsuario()){
                     $nombresRolesUsuario[] = $rolesCOL[$rolUsuarioDO->getFkRol()]; 
                 }
                 
             }
            
            // Datos generales
            $resultIDX[$idUsuario]['nombre'] = $usuarioDO->getVNombre();
            $resultIDX[$idUsuario]['roles'] = implode(', ', $nombresRolesUsuario);
            $resultIDX[$idUsuario]['email'] = $usuarioDO->getVEmail();
            $resultIDX[$idUsuario]['datos'] = $this->aclManager->datosCompletosUsuario($idUsuario);
            
        }
        
        // Verificamos que el usuario actual tenga permisos para editar y/o eliminar desde el listado
        $this->view->editar = $this->aclManager->hasPerms('usuario', 'editar');
        
        // Paso los datos a la vista
        $this->view->result = $resultIDX;
        
    }
    
    
    /**
     * Acción de alta
     * Da de alta un usuario
     */
    public function altaAction(){
        
        // Obtengo los roles
        $this->view->roles = $this->aclManager->getRoles();        
        
        // Se comprueba el acceso
        if (!$this->aclManager->hasPerms($this->controllerName, $this->actionName)){
            $this->redirectTo('usuario', 'ficha');
        }
        
        if (count($_POST) > 0){
            
            // Modo inserción de datos
            $username = strtolower($this->helper->getAndEscape('nombreUsuario'));
            $password = strtolower($this->helper->getAndEscape('password1'));
            $repassword = strtolower($this->helper->getAndEscape('repassword1'));
            $email = $this->helper->getAndEscape('emailUsuario');
            $avisar = $this->helper->getAndEscape('avisar');
            
            // Comprobaciones pertinentes
            if (empty($username)){
                $this->view->errorNombre = 'El nombre no puede estar vacío.';  
                return;
            }
            
            if (!preg_match('/^[a-zA-Z0-9]{5,16}$/', $username)) {
                $this->view->errorNombre = 'El nombre de usuario no es correcto.';
                return;                
            }
            
            $sql = "SELECT COUNT(*) AS total FROM tblUsuario WHERE LOWER(vNombre) = '$username'";
            $this->db->executeQuery($sql);
            $row = $this->db->fetchRow();
            if (is_array($row) && array_key_exists('total', $row) && $row['total'] != 0){
                $this->view->errorNombre = 'El nombre de usuario ya existe';
                return;                
            }
            
            if (empty($password) || empty($repassword)){
                $this->view->errorPassword = 'Las contraseñas no pueden estar vacías.';
                return;
            }
            
            if ($password != $repassword){
                $this->view->errorPassword = 'Las contraseñas no coinciden.';
                return;
            }
            
            if (!preg_match('/^(?=.*\d)(?=.*[A-Za-z@#$%^&+=]).{6,15}$/', $password)) {
                $this->view->errorPassword = 'La contraseña no es correcta.';
                return;
            } 
            
            // Email
        	if (!NingenString::validaMail($email)){
                $this->view->errorEmail = 'La dirección de correo proporcionada no es correcta.';
                return;
            }
            
            // Roles
        	$rolesARR = array();
            if ( array_key_exists('roles', $_POST) ){
	            foreach ($_POST['roles'] as $rol) {
	                $rolesARR[] = $this->helper->escapeInjection($rol);
	            }
            }
            
            if (count($rolesARR) == 0){
                $this->view->errorRol = 'Debe seleccionar como mínimo un rol.';
                return;
            } 
            
            // Se insertan los datos referentes a la cuenta de usuario
            $this->db->begin();
            
            $usuarioDO = new TblUsuario($this->db);
            $usuarioDO->setVNombre($username);
            $usuarioDO->setVPassword($this->aclManager->codificaPassword($password));
            $usuarioDO->setVEmail($email);
            
            if (!$usuarioDO->insert()){
                
                $this->db->rollback();
                
                $this->view->popup = array(
                    'estado' => 'ko',
                    'titulo' => 'Error',
                    'mensaje'=> 'Ha ocurrido un error con el alta de usuario. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                    'url'=> '',
                );
                
                return;
            }
            
            foreach ($rolesARR as $rol){
                
                // Se asignan los roles al nuevo usuario
                $usuarioRolDO = new TrelRolUsuario($this->db);
                $usuarioRolDO->setFkUsuario($this->db->getLastInsertId());
                $usuarioRolDO->setFkRol($rol);
                
                if (!$usuarioRolDO->insert()){

                    $this->db->rollback();

                    $this->view->popup = array(
                        'estado' => 'ko',
                        'titulo' => 'Error',
                        'mensaje'=> 'Ha ocurrido un error con la asignación de rol. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                        'url'=> '',
                    );
                    
                    return;
                    
                }
                
            }
            
            // En este punto ya se puede realizar el commit
            $this->db->commit();
            
            //
            // MAIL DE AVISO (avisar es un checkbox en el formulario de alta)
            //
            if ($avisar == 'on'){
            
                // Se obtiene la configuración del mailer
                $appConfig = $GLOBALS['NINGEN_CMS']['app_config'];
                if (!$appConfig instanceof NingenApplicationConfig){
                    throw new NingenException('No se ha obtenido la configuración del mailer. Error crítico.', 500);
                }
    
                // Template del mail
                $mt = new NingenMailerTemplate();
                $mt->setTemplate(NINGENCMS_LAYOUTDIR . 'nuevoUsuario.txt');
                $mt->addField('ENLACE', 'http://' . $appConfig->getAppHostname());
                $mt->addField('USUARIO', $username);
                $mt->addField('CONTRASENA', $password);
               
                // Mailer
                $mailerConfig = $appConfig->getMailerConfiguration();
                $mailer = new NingenMailer($mailerConfig);
                $mailer->setSubject("Formación PIME - Datos de acceso");
                $mailer->setFrom('<noreply@planespime.es>', 'PlanesPIME');
                $mailer->setBody($mt->getContent());
                $mailer->addTo($email);
                
    
                // Se envía el correo
                if(!$mailer->send()){
                    $this->view->popup = array(
                        'estado' => 'ko',
                        'titulo' => 'Error',
                        'mensaje'=> 'El usuario ha sido creado correctamente, pero ha ocurrido un error al enviar el mail de aviso.',
                        'url'=> '',
                    );
                    return;
                }
            
            }
                
            $this->redirectTo('usuario', 'index');
            
        }
        
    }
    
    
    
    /**
     * Acción de ficha
     * Ficha de un usuario
     */
    public function fichaAction(){
        
        // Se obtienen los datos y se preparan para la vista
        $this->_getDatosUsuarioFicha();
        
    }
    
    
    /**
     * Obtiene todos los datos necesarios para mostrar en la ficha de usuario
     * como así también en la página de edición. Retorna la clave de usuario. 
     * @return integer
     */
    private function _getDatosUsuarioFicha(){
        
        // Se obtiene la clave desde el request
        $claveUsuario = $this->getParam(0);

        // Datos de acceso
        if (!is_null($claveUsuario)){
            
            $usuarioBO = $this->aclManager->createSessionObject($claveUsuario);
            
        } else {

            // Si no se pasa clave de usuario redirigimos a la ficha
            $usuarioBO = NingenCmsSession::getValue('usuario');
            $claveUsuario = $usuarioBO->getId();
            
        }
        
        // Se guardará el antiguo nombre de usuario en la sesión, ya que en el apartado de edición es necesario saberlo
        NingenCmsSession::setValue('oldUsername', $usuarioBO->getNombre());
        
        $this->view->usuarioBO = $usuarioBO;
        $this->view->datehelper = new NingenDate();
        
        $rolPrincipalUsuario = $this->aclManager->getRolMasRelevanteUsuario($claveUsuario);
        
        
        // Verificaremos el típo de entidad (de acuerdo a su rol más relevante)
        if ($this->aclManager->isRolEmpresa($rolPrincipalUsuario)){
            
            $this->view->tipo = 'empresa';
            $this->view->empresaDO = array_shift(TblEmpresa::findByTblUsuario($this->db, $claveUsuario));
            
            if (!$this->view->empresaDO instanceof TblEmpresa){
                throw new NingenException('No se puede determinar la empresa vinculada al usuario. Por favor contacte con el administrador.', 500);
            }
            
        } elseif($this->aclManager->isRolPersona($rolPrincipalUsuario)){
            
            $this->view->tipo = 'persona';
            $this->view->personaDO = array_shift(TblPersona::findByTblUsuario($this->db, $claveUsuario));
            
            if (!$this->view->personaDO instanceof TblPersona){
                throw new NingenException('No se puede determinar la persona vinculada al usuario. Por favor contacte con el administrador.', 500);
            }
            
        } else {
            
            throw new NingenException('No se puede determinar el tipo de entidad del usuario a mostrar. Por favor contacte con el administrador.', 500);
            
        }
        
        // Labels para los roles
        $this->view->rolesIDX = $this->aclManager->getRoles();
        
        return $claveUsuario;
        
    }
    
    
    
    /**
     * Elimina a un usuario del sistema
     */
    public function eliminarAction(){
       
       // Si no hay parámetros no se puede continuar
       if (!$claveUsuario = $this->getParam(0)){
           $this->redirectTo('usuario', 'ficha');
           return;
       }
       
       $sql = "DELETE FROM tblUsuario WHERE idUsuario = $claveUsuario";
       
       // Se elimina el usuario
       if ($this->db->executeQuery($sql)){
            
           // El usuario se ha eliminado a sí mismo, lo expulsamos del sistema
           if ($this->usuario->getId() == $claveUsuario){
                
                $this->redirectTo('index', 'logout');
                
           } else {
                
                $this->redirectTo('usuario', 'index');

           }
            
       } else {
            
           $this->view->popup = array(
               'estado' => 'ko',
               'titulo' => 'Error',
               'mensaje'=> 'Ha ocurrido un error al eliminar el usuario. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
               'url'=> '/usuario/index.html',
           );
            
       }
        

       
        
    }
    
    
    
    /**
     * Busca a un usuario del sistema
     */
    public function buscarAction(){
        
        // Roles
        $this->view->rolesIDX = $this->aclManager->getRoles();
        
        // Búsqueda de usuarios
        $sent = $this->helper->getAndEscape('sent');
        
        if (!empty($sent)){

            // Solo comprobaremos permisos de edición si hay resultados
            if ( $this->aclManager->hasPerms('usuario', 'editar') ){
                $this->view->editar = true;
            }
            
            // Parámetros de ordenación para el paginador
            $aliasCampos = array(
                'nom'   => 'vNombre',
                'mail'  => 'vEmail',
                'id'  => 'idUsuario',
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
        
            $id = $this->helper->getAndEscape('idUsuario');
            $username = strtolower($this->helper->getAndEscape('username'));
            $email = $this->helper->getAndEscape('email');
            $roles = $this->helper->getAndEscape('roles');
            
            
            $where = array();
            $queryString = '&amp;sent=1';
            
            // ID
            if (!empty($id)){
                $where[] = "idUsuario = $id";
                $this->view->id = id;
                $queryString .= '&amp;idUsuario=' . $id;
            }
            
            // NOMBRE DE USUARIO
            if (!empty($username)){
                $where[] = "LOWER(vNombre) LIKE '%$username%'";
                $this->view->username = $username;
                $queryString .= '&amp;username=' . $username;
            }
            
            // EMAIL
            if (!empty($email)){
                $where[] = "vEmail LIKE '%$email%'";
                $this->view->email = $email;
                $queryString .= '&amp;email=' . $email;
            }
            
            // ROLES
            if (is_array($roles)){
                $rolesStr = implode(',', $roles);
                $where[] = " EXISTS (SELECT null FROM trelRolUsuario WHERE tblUsuario.idUsuario = trelRolUsuario.fkUsuario AND trelRolUsuario.fkRol IN($rolesStr))";
                $this->view->roles = $roles;
                $queryString .= '&amp;roles=' . $rolesStr;
            }
            
            // Se constuye el where
            if (count($where)){
                $where = ' WHERE ' . implode(' AND ', $where);
            } else {
                $where = '';
            }
            
            // Se ejecuta la búsqueda
            $paginador = new NingenPaginator($this->db, $where, 'tblUsuario', $this->helper);
            $paginador->setItemsPorPagina(10);
            $paginaActual = $this->helper->escapeInjection($this->helper->get('p'));
            $paginaActual = empty($paginaActual) ? 1 : $paginaActual;
            $paginador->setPaginaActual($paginaActual);
            $paginador->setOrderBy($orderBy);
            $paginador->setOrder($order);
            $paginador->setExtraParams($queryString);
        
            // Obtengo las convocatorias
            $usuariosCOL = $paginador->getItemCollection();
            
            // Envío el paginador a la vista
            $this->view->paginador = $paginador->getPaginatorHtml();
            
            // Se propagan las clausulas de búsqueda en el paginador
            $this->view->querystring = $queryString;    

            // Obtengo todos los roles 
            $rolesCOL = $this->aclManager->getRoles();
            
            // Obtengo todos los roles asignados a todos los usuarios
            $rolesUsuariosCOL = TrelRolUsuario::findAll($this->db, 'fkUsuario ASC');
            
            // Prepararé un array con todos los datos a mostrar en la vista 
            // indexados por la clave de usuario
            $resultIDX = array();
            
            foreach ($usuariosCOL as $usuarioDO){
                
                $idUsuario = $usuarioDO->getIdUsuario();
                $nombresRolesUsuario = array();
                
                // Roles del usuario
                 foreach ($rolesUsuariosCOL as $rolUsuarioDO){
                     
                     if ($idUsuario == $rolUsuarioDO->getFkUsuario()){
                         $nombresRolesUsuario[] = $rolesCOL[$rolUsuarioDO->getFkRol()]; 
                     }
                     
                 }
                
                // Datos generales
                $resultIDX[$idUsuario]['nombre'] = $usuarioDO->getVNombre();
                $resultIDX[$idUsuario]['roles'] = implode(', ', $nombresRolesUsuario);
                $resultIDX[$idUsuario]['email'] = $usuarioDO->getVEmail();
                
            }
            
            $this->view->result = $resultIDX;

        }        
        
    }
    
    
    /**
     * Editar un usuario del sistema
     */
    public function editarAction(){
        
        // Se obtienen los datos actuales y se le pasan a la vista
        $claveUsuario = $this->_getDatosUsuarioFicha();
        
        if ($this->view->tipo == 'persona'){
            
            // Estado civil
            $this->view->estadosCivilesCOL = TblEstadoCivil::findAll($this->db);
            
            // Estado laboral
            $this->view->estadosLaboralesCOL = TblEstadoLaboral::findAll($this->db);
            
            // Nivel de estudios
            $this->view->nivelEstudiosCOL = TblNivelEstudios::findAll($this->db);            
            
        }
        
        // Provincias
        $this->view->provinciasCOL = TblProvincia::findAll($this->db);
        
        // Paises
        $this->view->paisesCOL = TblPais::findAll($this->db);
        
        
        // Flag de envío mediante formulario
        $send = intval($this->helper->get('send'));
        $tipo = $this->helper->getAndEscape(md5('tipo'));
        
        // Se verifica si hay datos para insertar 
        if (count($_POST) > 0 && $send == 1){
            
            $newNombreUsuario = null;
            $newPassword = null;

            // CAMPOS COMUNES PARA AMBAS ENTIDADES

            $nombreUsuario = strtolower($this->helper->getAndEscape('nombreUsuario'));
            $password = strtolower($this->helper->getAndEscape('password1'));
            $repassword = strtolower($this->helper->getAndEscape('repassword1'));
            $email = $this->helper->getAndEscape('emailUsuario');
            $rolesARR = array();
            if ( array_key_exists('roles', $_POST) ){
                foreach ($_POST['roles'] as $rol) {
                    $rolesARR[] = $this->helper->escapeInjection($rol);
                }
            }
            
            // Nombre de usuario
            if (empty($nombreUsuario)){
                $this->view->errorNombre = 'El nombre de usuario no puede estar vacío';
                return;
            }
            
            if (!preg_match('/^[a-zA-Z0-9]{5,16}$/', $nombreUsuario)) {
                $this->view->errorNombre = 'El nombre de usuario no es correcto.';
                return;                
            }
            
            // Se verificará la existencia del nombre de usuario, solo en el caso que el nombre haya cambiado
            $oldUsername = NingenCmsSession::getValue('oldUsername');
            
            if (strtolower($oldUsername) != strtolower($nombreUsuario)){

                $sql = "SELECT COUNT(*) AS total FROM tblUsuario WHERE LOWER(vNombre) = '$nombreUsuario'";
                $this->db->executeQuery($sql);
                $row = $this->db->fetchRow();
                
                if (is_array($row) && array_key_exists('total', $row) && $row['total'] != 0){
                    $this->view->errorNombre = 'El nombre de usuario ya existe';
                    return;                
                }
                
                // Se separa el nuevo nombre de usuario
                $newNombreUsuario = $nombreUsuario;
                
            }  

            // Si se está intentando cambiar la contraseña se comprueba, de lo contrario no
            if (!empty($password) || !empty($repassword)){
                
                if ($password != $repassword){
                    $this->view->errorPassword = 'Las contraseñas no coinciden.';
                    return;
                }
                
                if (!preg_match('/^(?=.*\d)(?=.*[A-Za-z@#$%^&+=]).{6,15}$/', $password)) {
                    $this->view->errorPassword = 'La contraseña no es correcta.';
                    return;
                } 
                
                // Se separa el nuevo password
                $newPassword = $password;
                
            }            

            // Email
            if (!NingenString::validaMail($email)){
                $this->view->errorEmail = 'La dirección de correo proporcionada no es correcta.';
                return;
            }
            
            // Roles
            if (count($rolesARR) == 0){
                $this->view->errorRol = 'Debe seleccionar como mínimo un rol.';
                return;
            }
            
            // Se insertan los datos
            $this->db->begin();
            
            //
            // DATOS DE ACCESO
            //
            
            $usuarioDO = TblUsuario::findByPrimaryKey($this->db, $claveUsuario);
            if (!is_null($newNombreUsuario)){
                $usuarioDO->setVNombre($newNombreUsuario);
            }
            if (!is_null($newPassword)){
                $usuarioDO->setVPassword($this->aclManager->codificaPassword($newPassword));
            }
            $usuarioDO->setVEmail($email);
            
            // Se actualizan los datos de acceso
            if (!$usuarioDO->update()){
                
                $this->db->rollback();
                
                $this->view->popup = array(
                    'estado' => 'ko',
                    'titulo' => 'Error',
                    'mensaje'=> 'Ha ocurrido un error al actualizar el usuario. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                    'url'=> '',
                );
            
                return;
                
            }
            
            //
            // ROLES DE USUARIO
            //
            
            $sql = 'DELETE FROM trelRolUsuario WHERE fkUsuario = ' . $claveUsuario;
            
            if (!$this->db->executeQuery($sql)){
                
                $this->db->rollback();

                $this->view->popup = array(
                    'estado' => 'ko',
                    'titulo' => 'Error',
                    'mensaje'=> 'Ha ocurrido un error al restablecer sus roles. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                    'url'=> '',
                );
                
                return;                    
                
            }
            
            foreach ($rolesARR as $rol){
                
                // Se asignan los roles al nuevo usuario
                $usuarioRolDO = new TrelRolUsuario($this->db);
                $usuarioRolDO->setFkUsuario($claveUsuario);
                $usuarioRolDO->setFkRol($rol);
                
                if (!$usuarioRolDO->insert()){

                    $this->db->rollback();

                    $this->view->popup = array(
                        'estado' => 'ko',
                        'titulo' => 'Error',
                        'mensaje'=> 'Ha ocurrido un error con la asignación de roles. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                        'url'=> '',
                    );
                    
                    return;
                    
                }
                
            }                
            
            if (md5('persona') == $tipo){
                
                // PERSONA

                $nombre = $this->helper->getAndEscape('nombrePersona');
                $apellido = $this->helper->getAndEscape('apellido1Persona'); 
                $apellido2 = $this->helper->getAndEscape('apellido2Persona'); 
                $nacimiento = $this->helper->getAndEscape('nacimientoPersona');
                $dni = $this->helper->getAndEscape('dniPersona'); 
                $movil = $this->helper->getAndEscape('movilPersona'); 
                $direccion = $this->helper->getAndEscape('direccionPersona'); 
                $poblacion = $this->helper->getAndEscape('poblacionPersona'); 
                $cp = $this->helper->getAndEscape('cpPersona'); 
                $provincia = $this->helper->getAndEscape('provinciasUsuario'); 
                $pais = $this->helper->getAndEscape('paisPersona'); 
                $estadoCivil = $this->helper->getAndEscape('estadoCivil'); 
                $estadoLaboral = $this->helper->getAndEscape('estadoLaboral'); 
                $nivelEstudios = $this->helper->getAndEscape('nivelEstudios');
                $telefono = $this->helper->getAndEscape('telPersona');
                $movil = $this->helper->getAndEscape('movilPersona');

                // Nombre 
                if (empty($nombre)){
                    $this->view->errorNombrePersona = 'El nombre no puede quedar vacío';
                    return;
                }

                // Apellido 
                if (empty($apellido)){
                    $this->view->errorApellidoPersona = 'El apellido no puede quedar vacío';
                    return;
                }
                
                // Fecha de naciemiento
                if (empty($nacimiento)){
                    $this->view->errorNacimientoPersona = 'Debe introducir una fecha de nacimiento';
                    return;
                }
                
                // DNI
                if (empty($dni)){
                    $this->view->errorDniPersona = 'Debe introducir un número de identificación';
                    return;
                }
                
                // País
                if (empty($pais)){
                    $this->view->errorPaisPersona = 'Debe seleccionar un país';
                    return;
                }
                
                // Estado civil
                if (empty($estadoCivil)){
                    $this->view->errorEstadoCivil = 'Debe seleccionar un estado civil';
                    return;
                }
                
                // Estado laboral
                if (empty($estadoLaboral)){
                    $this->view->errorEstadoLaboral = 'Debe seleccionar un estado laboral';
                    return;
                }
                
                // Nivel de estudios
                if (empty($nivelEstudios)){
                    $this->view->errorNivelEstudios = 'Debe seleccionar un nivel de estudios';
                    return;
                }
                
                //
                // DATOS DE PERSONA
                //
                
                $personaDO = array_shift(TblPersona::findByTblUsuario($this->db, $claveUsuario));
                $personaDO->setVNombre($nombre);
                $personaDO->setVPrimerApellido($apellido);
                $personaDO->setVSegundoApellido($apellido2);
                $personaDO->setDNacimiento(NingenDate::europeoAmericano($nacimiento));
                $personaDO->setVNumeroIdentificacion($dni);
                $personaDO->setVTelefono($telefono);
                $personaDO->setVMovil($movil);
                $personaDO->setVDireccion($direccion);
                $personaDO->setVPoblacion($poblacion);
                $personaDO->setVCp($cp);
                $personaDO->setFkProvincia($provincia);
                $personaDO->setFkPais($pais);
                $personaDO->setFkEstadoCivil($estadoCivil);
                $personaDO->setFkEstadoLaboral($estadoLaboral);
                $personaDO->setFkNivelEstudios($nivelEstudios);
                $personaDO->setLastModified(date('Y-m-d'));
                $personaDO->setModUser($this->view->usuarioBO->getNombre());
                
                if (!$personaDO->update()){
                    
                    $this->db->rollback();
                    
                    $this->view->popup = array(
                        'estado' => 'ko',
                        'titulo' => 'Error',
                        'mensaje'=> 'Ha ocurrido un error al actualizar sus datos personales. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                        'url'=> '',
                    );
                    
                    return;                    
                    
                }
                
                $this->db->commit();
                
                
            } elseif (md5('empresa') == $tipo){
                
                // EMPRESA
                $this->view->empresaDO = array_shift(TblPersona::findByTblUsuario($this->db, $claveUsuario));
                
                // Se obtienen los datos
                $nombreEmpresa = $this->helper->getAndEscape('nombre');
                $cif = $this->helper->getAndEscape('cif');
                $pais = $this->helper->getAndEscape('pais');
                $provincia = $this->helper->getAndEscape('provincia');
                $poblacion = $this->helper->getAndEscape('poblacion');
                $direccion = $this->helper->getAndEscape('direccion');
                $cp = $this->helper->getAndEscape('cp');
                $telefono = $this->helper->getAndEscape('telefono1');
                $telefono2 = $this->helper->getAndEscape('telefono2');
                $fax = $this->helper->getAndEscape('fax');
                
                // Comprobación de campos
                if (empty($nombreEmpresa)){
                    $this->view->errorNombre = 'El nombre no puede quedar vacío.';
                }
                
                if (empty($cif)){
                    $this->view->errorCif = 'El CIF no puede quedar vacío';
                }
                
                if (empty($pais)){
                    $this->view->errorPais = 'Debe seleccionar un país.';
                }

                if (empty($provincia)){
                    $this->view->errorProvincia = 'Debe seleccionar una provincia.';
                }
                
                // Se prepara el insert
                $empresaDO = array_shift(TblEmpresa::findByTblUsuario($this->db, $claveUsuario));
                $empresaDO->setVNombre($nombreEmpresa);
                $empresaDO->setVCif($cif);
                $empresaDO->setFkPais($pais);
                $empresaDO->setFkProvincia($provincia);
                $empresaDO->setVPoblacion($poblacion);
                $empresaDO->setVDireccion($direccion);
                $empresaDO->setVCp($cp);
                $empresaDO->setVTelefono($telefono);
                $empresaDO->setVTelefono2($telefono2);
                $empresaDO->setVFax($fax);
                
                // Se insteran los datos
                if (!$empresaDO->update()){
                    
                    $this->db->rollback();
                    
                    $this->view->popup = array(
                        'estado' => 'ko',
                        'titulo' => 'Error',
                        'mensaje'=> 'Ha ocurrido un error al actualizar los datos de empresa. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                        'url'=> '',
                    );
                    
                    return;
                    
                }
                
                $this->db->commit();
                
            }
            
            // Se vuelven a obtener los datos del usuario
            $claveUsuario = $this->_getDatosUsuarioFicha();
            
        }
        
    }

	/**
     * Obtiene todos los datos necesarios para mostrar un formulario vacío de empresa o de usuario.
     * Retorna la clave de usuario. 
     * @return integer
     */
    private function _getDatosNuevoUsuarioFicha(){
        
        // Se obtiene la clave desde el request
        $claveUsuario = $this->getParam(0);

        // Datos de acceso
        if (!is_null($claveUsuario)){
            
            $usuarioBO = $this->aclManager->createSessionObject($claveUsuario);
            
        } else {

            // Si no se pasa clave de usuario redirigimos a la ficha
            $usuarioBO = NingenCmsSession::getValue('usuario');
            $claveUsuario = $usuarioBO->getId();
            
        }
        
        // Se guardará el antiguo nombre de usuario en la sesión, ya que en el apartado de edición es necesario saberlo
        NingenCmsSession::setValue('oldUsername', $usuarioBO->getNombre());
        
        $this->view->usuarioBO = $usuarioBO;
        
        $rolPrincipalUsuario = $this->aclManager->getRolMasRelevanteUsuario($claveUsuario);
        
        
        // Verificaremos el típo de entidad (de acuerdo a su rol más relevante)
        if ($this->aclManager->isRolEmpresa($rolPrincipalUsuario)){
            
            $this->view->tipo = 'empresa';
            
        } elseif($this->aclManager->isRolPersona($rolPrincipalUsuario)){
            
            $this->view->tipo = 'persona';
            
        } else {
            
            throw new NingenException('No se puede determinar el tipo de entidad del usuario a mostrar. Por favor contacte con el administrador.', 500);
            
        }
        
        // Labels para los roles
        $this->view->rolesIDX = $this->aclManager->getRoles();
        
        return $claveUsuario;
        
    }
    
    /**
     * Nuevo usuario
     * @throws NingenException
     */
    public function nuevoAction(){
        
        $this->setAlternateLayout('libre');
        
        // Mensaje de aviso para completar la ficha
        $avisoModule = new avisoModule('aviso');
        $this->addModule($avisoModule);
        
        // Se obtienen los datos actuales y se le pasan a la vista
        $claveUsuario = $this->_getDatosNuevoUsuarioFicha();
        
        if ($this->view->tipo == 'persona'){
            
        	// Tipo identificación
        	$this->view->tipoIdentificacionCOL = TblTipoIdentificacion::findAll($this->db, 'vNombre');
        
            // Estado civil
            $this->view->estadosCivilesCOL = TblEstadoCivil::findAll($this->db);
            
            // Estado laboral
            $this->view->estadosLaboralesCOL = TblEstadoLaboral::findAll($this->db);
            
            // Nivel de estudios
            $this->view->nivelEstudiosCOL = TblNivelEstudios::findAll($this->db);            
            
        }
        
        // Provincias
        $this->view->provinciasCOL = TblProvincia::findAll($this->db);
        
        // Paises
        $this->view->paisesCOL = TblPais::findAll($this->db);
        
        
        // Flag de envío mediante formulario
        $send = intval($this->helper->get('send'));
        $tipo = $this->helper->getAndEscape(md5('tipo'));
        
        // Se verifica si hay datos para insertar 
        if (count($_POST) > 0 && $send == 1){
            
            $newNombreUsuario = null;
            $newPassword = null;

            // CAMPOS COMUNES PARA AMBAS ENTIDADES

            $nombreUsuario = $this->helper->getAndEscape('nombreUsuario');
            $password = $this->helper->getAndEscape('password1');
            $repassword = $this->helper->getAndEscape('repassword1');
            $email = $this->helper->getAndEscape('emailUsuario');
            
            // Nombre de usuario
            if (empty($nombreUsuario)){
                $this->view->errorNombre = 'El nombre de usuario no puede estar vacío';
                return;
            }
            
            if (!preg_match('/^[a-zA-Z0-9]{5,16}$/', $nombreUsuario)) {
                $this->view->errorNombre = 'El nombre de usuario no es correcto.';
                return;                
            }
            
            // Se verificará la existencia del nombre de usuario, solo en el caso que el nombre haya cambiado
            $oldUsername = NingenCmsSession::getValue('oldUsername');
            
            if ($oldUsername != $nombreUsuario){

                $sql = "SELECT COUNT(*) AS total FROM tblUsuario WHERE vNombre = '$nombreUsuario'";
                $this->db->executeQuery($sql);
                $row = $this->db->fetchRow();
                
                if (is_array($row) && array_key_exists('total', $row) && $row['total'] != 0){
                    $this->view->errorNombre = 'El nombre de usuario ya existe';
                    return;                
                }
                
                // Se separa el nuevo nombre de usuario
                $newNombreUsuario = $nombreUsuario;
                
            }  

            // Si se está intentando cambiar la contraseña se comprueba, de lo contrario no
            if (!empty($password) || !empty($repassword)){
                
                if ($password != $repassword){
                    $this->view->errorPassword = 'Las contraseñas no coinciden.';
                    return;
                }
                
                if (!preg_match('/^(?=.*\d)(?=.*[A-Za-z@#$%^&+=]).{6,15}$/', $password)) {
                    $this->view->errorPassword = 'La contraseña no es correcta.';
                    return;
                } 
                
                // Se separa el nuevo password
                $newPassword = $password;
                
            }            

            // Email
            if (!NingenString::validaMail($email)){
                $this->view->errorEmail = 'La dirección de correo proporcionada no es correcta.';
                return;
            }
            
            // Se insertan los datos
            $this->db->begin();
            
            //
            // DATOS DE ACCESO
            //
            
            $usuarioDO = TblUsuario::findByPrimaryKey($this->db, $claveUsuario);
            if (!is_null($newNombreUsuario)){
                $usuarioDO->setVNombre($newNombreUsuario);
            }
            if (!is_null($newPassword)){
                $usuarioDO->setVPassword($this->aclManager->codificaPassword($newPassword));
            }
            $usuarioDO->setVEmail($email);
            
            // Se actualizan los datos de acceso
            if (!$usuarioDO->update()){
                
                $this->db->rollback();
                
                $this->view->popup = array(
                    'estado' => 'ko',
                    'titulo' => 'Error',
                    'mensaje'=> 'Ha ocurrido un error al actualizar sus datos de acceso. Inténtelo de nuevo en unos instantes por favor.',
                    'url'=> '',
                );
            
                return;

            }
            
            if (md5('persona') == $tipo){
                
                // PERSONA

                $nombre = $this->helper->getAndEscape('nombrePersona');
                $apellido = $this->helper->getAndEscape('apellido1Persona'); 
                $apellido2 = $this->helper->getAndEscape('apellido2Persona');
                $nacimiento = $this->helper->getAndEscape('nacimientoPersona');
                $dni = $this->helper->getAndEscape('dniPersona');
                $tipoIdentificacion = $this->helper->getAndEscape('tipoIdentificacion');
                $movil = $this->helper->getAndEscape('movilPersona'); 
                $direccion = $this->helper->getAndEscape('direccionPersona'); 
                $poblacion = $this->helper->getAndEscape('poblacionPersona'); 
                $cp = $this->helper->getAndEscape('cpPersona'); 
                $provincia = $this->helper->getAndEscape('provincia'); 
                $pais = $this->helper->getAndEscape('paisPersona'); 
                $estadoCivil = $this->helper->getAndEscape('estadoCivil'); 
                $estadoLaboral = $this->helper->getAndEscape('estadoLaboral'); 
                $nivelEstudios = $this->helper->getAndEscape('nivelEstudios');
                $telefono = $this->helper->getAndEscape('telPersona');
                $movil = $this->helper->getAndEscape('movilPersona');

                // Nombre 
                if (empty($nombre)){
                    $this->view->errorNombrePersona = 'El nombre no puede quedar vacío';
                    return;
                }

                // Apellido 
                if (empty($apellido)){
                    $this->view->errorApellidoPersona = 'El apellido no puede quedar vacío';
                    return;
                }
                
                // Fecha de naciemiento
                if (empty($nacimiento)){
                    $this->view->errorNacimientoPersona = 'Debe introducir una fecha de nacimiento';
                    return;
                }
                
                // DNI
                if (empty($dni)){
                    $this->view->errorDniPersona = 'Debe introducir un número de identificación';
                    return;
                }
                
                // País
                if (empty($pais)){
                    $this->view->errorPaisPersona = 'Debe seleccionar un país';
                    return;
                }
                
                // Estado civil
                if (empty($estadoCivil)){
                    $this->view->errorEstadoCivil = 'Debe seleccionar un estado civil';
                    return;
                }
                
                // Estado laboral
                if (empty($estadoLaboral)){
                    $this->view->errorEstadoLaboral = 'Debe seleccionar un estado laboral';
                    return;
                }
                
                // Nivel de estudios
                if (empty($nivelEstudios)){
                    $this->view->errorNivelEstudios = 'Debe seleccionar un nivel de estudios';
                    return;
                }
                
	            // Tipo identificación
                if (empty($tipoIdentificacion)){
                    $tipoIdentificacion = 1; // DNI
                }
                
                //
                // DATOS DE PERSONA
                //
                
                $personaDO = new TblPersona($this->db);
                $personaDO->setFkUsuario($claveUsuario);
                $personaDO->setVNombre($nombre);
                $personaDO->setVPrimerApellido($apellido);
                $personaDO->setVSegundoApellido($apellido2);
                $personaDO->setDNacimiento(NingenDate::europeoAmericano($nacimiento));
                $personaDO->setVNumeroIdentificacion($dni);
                $personaDO->setVTelefono($telefono);
                $personaDO->setVMovil($movil);
                $personaDO->setVDireccion($direccion);
                $personaDO->setVPoblacion($poblacion);
                $personaDO->setVCp($cp);
                $personaDO->setFkTipoIdentificacion($tipoIdentificacion);
                $personaDO->setFkProvincia($provincia);
                $personaDO->setFkPais($pais);
                $personaDO->setFkEstadoCivil($estadoCivil);
                $personaDO->setFkEstadoLaboral($estadoLaboral);
                $personaDO->setFkNivelEstudios($nivelEstudios);
                $personaDO->setDAlta(date('Y-m-d'));
                $personaDO->setLastModified(date('Y-m-d'));
                $personaDO->setModUser($this->view->usuarioBO->getNombre());
                
                if (!$personaDO->insert()){
                    
                    $this->db->rollback();
                    
                    $this->view->popup = array(
                        'estado' => 'ko',
                        'titulo' => 'Error',
                        'mensaje'=> 'Ha ocurrido un error al insertar sus datos personales. Inténtelo de nuevo en unos instantes por favor.',
                        'url'=> '',
                    );
                    
                    return;                    
                    
                }
                
                $this->db->commit();
                
                
            } elseif (md5('empresa') == $tipo){
                
                // EMPRESA
                
                // Se obtienen los datos
                $nombreEmpresa = $this->helper->getAndEscape('nombre');
                $cif = $this->helper->getAndEscape('cif');
                $pais = $this->helper->getAndEscape('pais');
                $provincia = $this->helper->getAndEscape('provincia');
                $poblacion = $this->helper->getAndEscape('poblacion');
                $direccion = $this->helper->getAndEscape('direccion');
                $cp = $this->helper->getAndEscape('cp');
                $telefono = $this->helper->getAndEscape('telefono1');
                $telefono2 = $this->helper->getAndEscape('telefono2');
                $fax = $this->helper->getAndEscape('fax');
                
                // Comprobación de campos
                if (empty($nombreEmpresa)){
                    $this->view->errorNombre = 'El nombre no puede quedar vacío.';
                }
                
                if (empty($cif)){
                    $this->view->errorCif = 'El CIF no puede quedar vacío';
                }
                
                if (empty($pais)){
                    $this->view->errorPais = 'Debe seleccionar un país.';
                }

                if (empty($provincia)){
                    $this->view->errorProvincia = 'Debe seleccionar una provincia.';
                }
                
                // Se prepara el insert
                
                $empresaDO = new TblEmpresa($this->db);
                $empresaDO->setFkUsuario($claveUsuario);
                $empresaDO->setVNombre($nombreEmpresa);
                $empresaDO->setVCif($cif);
                $empresaDO->setFkPais($pais);
                $empresaDO->setFkProvincia($provincia);
                $empresaDO->setVPoblacion($poblacion);
                $empresaDO->setVDireccion($direccion);
                $empresaDO->setVCp($cp);
                $empresaDO->setVTelefono($telefono);
                $empresaDO->setVTelefono2($telefono2);
                $empresaDO->setVFax($fax);
                $empresaDO->setDAlta(date('Y-m-d'));
                
                // Se insteran los datos
                if (!$empresaDO->insert()){
                    
                    $this->db->rollback();
                    
                    $this->view->popup = array(
                        'estado' => 'ko',
                        'titulo' => 'Error',
                        'mensaje'=> 'Ha ocurrido un error al insertar los datos de empresa. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                        'url'=> '',
                    );
                    
                    return;
                    
                }
                
                $this->db->commit();
                
            }
            
            // Se vuelven a obtener los datos del usuario
            //$claveUsuario = $this->_getDatosUsuarioFicha();
            $this->redirectTo('usuario', 'ficha');
            
        }
        
        
                
        
    }
    
}

?>

