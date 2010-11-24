<?php

require_once 'helper/OwlHtmlHelper.inc';
require_once CLASSESDIR . 'PplController.inc';


class materialController extends PplController{
    
    
    /**
     * Init
     * @see extranet.planespime.es/owl/lib/OwlController::initController()
     */
    public function initController(){
       
        
    }
    
    /**
     * Acción inicial, por defecto, el listado
     * @see extranet.planespime.es/owl/lib/OwlController::indexAction()
     */
    public function indexAction(){
        
        echo 'LISTADO';
        
    }
    
    /**
     * Acción de alta
     * Da de alta un material
     */
    public function altaAction(){
        
        echo 'ALTA';
        
    }
    
    /**
     * Acción de ficha
     * Ficha de un material
     */
    public function fichaAction(){
        
        echo 'FICHA';
        
    }
    
    
    
    
}

?>