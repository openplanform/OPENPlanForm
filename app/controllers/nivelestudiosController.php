<?php

require_once CLASSESDIR . 'PplController.inc';
require_once 'helper/OwlHtmlHelper.inc';


class nivelestudiosController extends PplController{
    
    
    /**
     * Init
     * @see extranet.planespime.es/owl/OwlController::initController()
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
     * Da de alta un nivelestudios
     */
    public function altaAction(){
        
        echo 'ALTA';
        
    }
    
    /**
     * Acción de ficha
     * Ficha de un nivelestudios
     */
    public function fichaAction(){
        
        echo 'FICHA';
        
    }
    
    
    
    
}

?>