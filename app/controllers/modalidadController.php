<?php

require_once CLASSESDIR . 'PplController.inc';
require_once 'helper/OwlHtmlHelper.inc';


class modalidadController extends PplController{
    
    
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
     * Da de alta un modalidad
     */
    public function altaAction(){
        
        echo 'ALTA';
        
    }
    
    /**
     * Acción de ficha
     * Ficha de un modalidad
     */
    public function fichaAction(){
        
        echo 'FICHA';
        
    }
    
    
    
    
}

?>