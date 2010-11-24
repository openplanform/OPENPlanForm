<?php

require_once 'OwlModule.inc';

class breadcrumbsModule extends OwlModule{
    
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
     * @var OwlConnection
     */
    protected $db;
    
    /**
     * Reescritura del controlador
     * @var string
     */
    protected $controllerRewrite = null;
    
    
    /**
     * Establece el nombre del controlador y de la acción
     * @param string $controller
     * @param string $action
     */
    public function setControllerAction($controller, $action = 'index', $rewrite = null){
        
        $this->actionName = $action;
        $this->controllerName = $controller;
        $this->controllerRewrite = $rewrite;
        
    }
    
    /**
     * Establece la referencia a la base de datos
     * @param OwlConection $db
     */
    public function setDb(OwlConnection $db){
        
        $this->db = $db;
        
    }
    
    /**
     * Ejecuta el módulo
     * @see extranet.planespime.es/owl/lib/OwlModule::runModule()
     */
    public function runModule(){
        
        // Controlador
        $controllerName = !is_null($this->controllerRewrite) ? $this->controllerRewrite : $this->controllerName;
        $sql = "SELECT vNombre AS label FROM tblAcceso WHERE vControlador = '" . $controllerName . "' AND vAccion IS NULL";
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
