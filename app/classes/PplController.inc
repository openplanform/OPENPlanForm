<?php

require_once 'NingenController.inc';

require_once NINGENCMS_CLASSESDIR . 'PplAclManager.inc';
require_once NINGENCMS_CLASSESDIR . 'PplCacheBO.inc';
require_once NINGENCMS_MODULEDIR . 'menuPrincipalModule.php';
require_once NINGENCMS_MODULEDIR . 'logoutModule.php';
require_once NINGENCMS_MODULEDIR . 'popupModule.php';
require_once NINGENCMS_MODULEDIR . 'barraHerramientasModule.php';

/**
 * Sobreescritura del controlador genérico
 */
class PplController extends NingenController{

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
     * @see extranet.planespime.es/ningencms/lib/NingenController::initController()
     */
    public function initController(){
        
        /**
         * El usuario deberá tener una cuenta para poder ejecutar 
         * cualquier acción del controlador
         */
        if ($this->controllerName != 'index'){
            $usuarioBO = NingenCmsSession::getValue('usuario');
            if (!$usuarioBO instanceof PplUsuarioSesion){
                $this->redirectTo('index', 'login');
                return;
            }
        }  
        
        // Se globaliza el usuario actual
        $this->usuario = $usuarioBO;
        
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
            $this->addModule($logoutModule);
        
        // ------------ MÓDULO - BARRA DE HERRAMIENTAS ----
        $barraHerramientasModule = new barraHerramientasModule('contenedor_toolbar');
            
            $barraHerramientasModule->setAction($this->actionName);
            $barraHerramientasModule->setController($this->controllerName);
            $this->addModule($barraHerramientasModule);
        
        
        // ------------ MÓDULO - POPUP ----------------------
        $popupModule = new popupModule('contenedor_popup');

            $this->addModule($popupModule);
            
            
        // Casos especiales en los que no es necesario un layout
    	if ( $this->actionName == "eliminar" || $this->actionName == "duplicar" ){
    		$this->bypassLayout();
    	}
    }
    
}

?>