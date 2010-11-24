<?php

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';
require_once NINGENCMS_MODELDIR . 'TblDocumento.inc';
require_once 'helper/NingenCmsHtmlHelper.inc';


class documentoController extends PplController{
    
    
    /**
     * Init
     * @see extranet.planespime.es/ningencms/lib/NingenController::initController()
     */
    public function initController(){
        
        $this->rewriteControllerLabel('administrador');
       
        parent::initController();
        
    }
    
    /**
     * Acción inicial, por defecto, el listado
     * @see extranet.planespime.es/ningencms/lib/NingenController::indexAction()
     */
    public function indexAction(){
        
        $sent = $this->helper->getAndEscape('sent');
        $error = false;
        
        if (!empty($sent)){
            
            $nombre = $this->helper->getAndEscape('nombre');
            $desc = $this->helper->getAndEscape('desc');
            if (!$archivo = $_FILES['archivo']){
                $error = true;
            }
            
            // Obtengo las variables del archivo
            foreach ($archivo as $key => $value){
                $$key = $value;
            }
            
             /*
                [name] => S-30.pdf
                [type] => application/pdf
                [tmp_name] => /tmp/phpFmxBxU
                [error] => 0
                [size] => 151224
             */
            
            if (!$error){
                
                $this->db->begin();
                
                // Se prepara la tupla
                $documentoDO = new TblDocumento($this->db);
                $documentoDO->setVRealName($name);
                $documentoDO->setVNombre($nombre);
                $documentoDO->setVMime($type);
                $documentoDO->setVTamano($size);
                $documentoDO->setVDescription($desc);
                $documentoDO->setModUser($this->usuario->getNombre());
                $documentoDO->setLastModified(date('Y-m-d'));
                
                if (!$documentoDO->insert()){
                    
                    echo 'Error Insert';
                    $this->db->rollback();
                    return;
                    
                }                
                
                // Se intenta mover el archivo a su ubicación final ( El nombre se contruirá en base al id de documento, doc_ID)
                if (!move_uploaded_file($tmp_name, PplCacheBO::getUploadDir() . 'doc_' . $this->db->getLastInsertId())){
                    
                    echo ('Error mover');
                    $this->db->rollback();
                    return;
                    
                }
                
                echo 'Todo Ok';
                $this->db->commit();
                
                
            } else {
                
                echo ('Error archivo'); 
                return;
                
            }
            
            
        }        
        
        $this->view->documentosCOL = TblDocumento::findAll($this->db, 'last_modified DESC');
        
    }
    
}

?>