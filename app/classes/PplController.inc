<?php

require_once 'OwlController.inc';

require_once CLASSESDIR . 'PplAclManager.inc';
require_once CLASSESDIR . 'PplCacheBO.inc';

require_once MODULEDIR . 'menuPrincipalModule.php';
require_once MODULEDIR . 'logoutModule.php';
require_once MODULEDIR . 'breadcrumbsModule.php';
require_once MODULEDIR . 'popupModule.php';
require_once MODULEDIR . 'barraHerramientasModule.php';

/**
 * Sobreescritura del controlador genérico
 */
class PplController extends OwlController{

    /**
     * Manejador de listas de acceso
     * @var PplAclManager
     */
    protected $aclManager;
    
    /**
     * Cacheador de la aplicación
     * @var PplCacheBO
     */
    protected $cacheBO;
    
    /**
     * Objeto de usuario de sessión, tener en cuenta
     * que este objeto se inicializará solo en el init,
     * para tener uno "más actualizado" en caso de cambios,
     * obtenerlo desde la sesión.
     * 
     * @var PplUsuarioSesion
     */
    protected $usuario; 
    
    /**
     * Reescritura de la etiqueta de controlador
     * @var string
     */
    protected $controllerRewrite = null;
    

    /**
     * Añado el soporte de AclManager
     */
    public function __construct(){
        
        parent::__construct();
        
        // Se instancia el AclManager
        $this->aclManager = new PplAclManager($this->db);
        $this->cacheBO = new PplCacheBO($this->db);
        
    }
    
    /**
     * Se instancian los módulos mas significativos de la aplicacion
     * @see extranet.planespime.es/owl/lib/OwlController::initController()
     */
    public function initController(){
        
        /**
         * El usuario deberá tener una cuenta para poder ejecutar 
         * cualquier acción del controlador
         */
        if ($this->controllerName != 'index' || ($this->controllerName == 'index' && $this->actionName == 'panel' )){
            $usuarioBO = OwlSession::getValue('usuario');
            if (!$usuarioBO instanceof PplUsuarioSesion){
                $this->redirectTo('index', 'login');
                return;
            }
        }  
        
        // Se globaliza el usuario actual
        $this->usuario = $usuarioBO;
        
    	// ROLES
	    /*if (!$this->aclManager->hasPerms($this->controllerName, $this->actionName)){
	    	
	    	$this->stopExecution();
	    	echo OwlHtmlHelper::getHtmlErrorPage('Forbidden', 403, 'Acceso no autorizado', '<p>No dispone de los privilegios necesarios para acceder a este área.</p>');
	    	
	    	return;
	    }*/
        
        // ------------ MÓDULO - MENÚ PRINCIPAL -----------
        $menuPrincipalModule = new menuPrincipalModule('contenedor_menu');
            
            $menuPrincipalModule->setDb($this->db);

            // Se configuran los permisos del menu
            $acl = $this->aclManager->getAclData($this->usuario);
            $menuPrincipalModule->setMenuArray($acl);
            
            $this->addModule($menuPrincipalModule);

        // ------------ MÓDULO - LOGOUT -------------------
        $logoutModule = new logoutModule('contenedor_logout');
            
            $logoutModule->setAcl($this->aclManager);
            $logoutModule->setUsuario($this->usuario);
            $logoutModule->setFichaUsuario($this->aclManager->datosCompletosUsuario($usuarioBO->getId()));
            $this->addModule($logoutModule);
        
        // ------------ MÓDULO - BARRA DE HERRAMIENTAS ----
        $barraHerramientasModule = new barraHerramientasModule('contenedor_toolbar');
            
            $barraHerramientasModule->setAction($this->actionName);
            $barraHerramientasModule->setController($this->controllerName);
            $barraHerramientasModule->setParam($this->getParam(0));
            $this->addModule($barraHerramientasModule);
        
        
        // ------------ MÓDULO - POPUP ----------------------
        $popupModule = new popupModule('contenedor_popup');

            $this->addModule($popupModule);
            
            
        // ------------ MÓDULO - BREADCRUMBS -------------------
        $pathModule = new breadcrumbsModule('contenedor_path');
        
            $pathModule->setControllerAction($this->controllerName, $this->actionName, $this->controllerRewrite);
            $pathModule->setDb($this->db);
            $this->addModule($pathModule);
            
            
        // Casos especiales en los que no es necesario un layout
    	if ($this->actionName == "duplicar" ){
    		$this->bypassLayout();
    	}
    	
    }
    
}

?>
