<?php

require_once NINGENCMS_CLASSESDIR . 'PplController.inc';

/**
 * Controlador encargado de responder las peticiones asíncronas
 * de la a aplicacióm
 */
class ajaxController extends PplController{

    
    public function initController(){
        
        parent::initController();
        
        $this->bypassLayout();
        
    }
    
    public function indexAction(){
        
    }
    
    public function comprobarUsuarioAction(){
    	
    	if ( array_key_exists('usuario', $_POST) ){
	    	
    		$sql = "SELECT COUNT(*) AS total FROM tblUsuario WHERE vNombre = '" . $_POST['usuario'] . "'";
            $this->db->executeQuery($sql);
            $row = $this->db->fetchRow();
            if (is_array($row) && array_key_exists('total', $row) && $row['total'] != 0){
            	$arrRespuesta['resultado'] = 'ko';
                $arrRespuesta['mensaje'] = 'El nombre de usuario ya existe';
            } else {
            	$arrRespuesta['resultado'] = 'ok';
            	$arrRespuesta['mensaje'] = 'El nombre de usuario no existe';
            }
	    	
			$jsonArrRespuesta = json_encode($arrRespuesta);
			echo $jsonArrRespuesta;
			
    	}
    	
    }
    
    
}

?>
