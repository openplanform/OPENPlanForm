<?php

require_once 'NingenModule.inc';

class breadcrumbsModule extends NingenModule{
    
    /**
     * Nombre del controlador
     * @var string
     */
    protected $controllerName = null;

    /**
     * Nombre de la acción
     * @var string
     */
    protected $actionName = null;
    
    /**
     * Base de datos
     * @var NingenConnection
     */
    protected $db;
    
    /**
     * Establece el nombre del controlador y de la acción
     * @param string $controller
     * @param string $action
     */
    public function setControllerAction($controller, $action = 'index'){
        
        $this->actionName = $action;
        $this->controllerName = $controller;
        
    }
    
    /**
     * Establece la referencia a la base de datos
     * @param NingenConection $db
     */
    public function setDb(NingenConnection $db){
        
        $this->db = $db;
        
    }
    
    /**
     * Ejecuta el módulo
     * @see extranet.planespime.es/ningencms/lib/NingenModule::runModule()
     */
    public function runModule(){
        
        // Controlador
        $sql = "SELECT vNombre AS label FROM tblAcceso WHERE vControlador = '" . $this->controllerName . "' AND vAccion IS NULL;";
        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $controllerLabel = $row['label'];
        
        // Accion
        $sql = "SELECT vNombre AS label FROM tblAcceso WHERE vControlador = '" . $this->controllerName . "' AND vAccion = '" . $this->actionName . "';";
        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $actionLabel = str_ireplace('_', '', $row['label']);
        
        ?><p class="inner">
            
           <a href="/<?= $this->controllerName ?>"><?= $controllerLabel ?></a>
           <span><strong>-></strong></span>
           <a href="/<?= $this->controllerName . '/' . $this->actionName ?>.html"><?= $actionLabel ?></a>
            
        </p><?
        
    }
    
    
}

?>
