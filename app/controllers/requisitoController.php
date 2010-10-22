<?php

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';
require_once 'helper/NingenCmsHtmlHelper.inc';


class requisitoController extends PplController{
    
    
    /**
     * Init
     * @see extranet.planespime.es/ningencms/lib/NingenController::initController()
     */
    public function initController(){
       
        
    }
    
    /**
     * Acción inicial, por defecto, el listado
     * @see extranet.planespime.es/ningencms/lib/NingenController::indexAction()
     */
    public function indexAction(){
        
        echo 'LISTADO';
        
    }
    
    /**
     * Acción de alta
     * Da de alta un requisito
     */
    public function altaAction(){
        
        echo 'ALTA';
        
    }
    
    /**
     * Acción de ficha
     * Ficha de un requisito
     */
    public function fichaAction(){
        
        echo 'FICHA';
        
    }
    
    
    
    
}

?>