<?php

require_once CLASSESDIR . 'PplController.inc';

require_once MODELDIR . '/TblHorario.inc';

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
    
    /**
     * Comprueba si ya existe un usuario
     * @return array
     */
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
            }
	    	
			$jsonArrRespuesta = json_encode($arrRespuesta);
			
			echo $jsonArrRespuesta;
			
			
    	}
    	
    }
    
    /**
     * Comprueba si ya existe el cif/dni
     * @return array
     */
 	public function comprobarDniAction(){
    	
    	if ( array_key_exists('dni', $_POST) && !empty($_POST['dni']) ) {
	    	
    		if ( array_key_exists('empresa', $_POST) && $_POST['empresa'] == 'false' ){
    			$sql = "SELECT COUNT(*) AS total FROM tblPersona WHERE vNumeroIdentificacion = '" . $_POST['dni'] . "'";
    		} else {
    			$sql = "SELECT COUNT(*) AS total FROM tblEmpresa WHERE vCif = '" . $_POST['dni'] . "'";
    		}
            $this->db->executeQuery($sql);
            $row = $this->db->fetchRow();
            if (is_array($row) && array_key_exists('total', $row) && $row['total'] != 0){
            	$arrRespuesta['resultado'] = 'ko';
                $arrRespuesta['mensaje'] = 'El número ya está registrado';
            } else {
            	$arrRespuesta['resultado'] = 'ok';
            }
	    	
			$jsonArrRespuesta = json_encode($arrRespuesta);
			echo $jsonArrRespuesta;
			
    	} else {
    		
    		$arrRespuesta['resultado'] = 'ko';
			$jsonArrRespuesta = json_encode($arrRespuesta);
			echo $jsonArrRespuesta;
			
    	}
    	
    }
    
    /**
     * Comprueba si un alumno es candidato de un curso
     * @return array
     */
    public function comprobarCandidatoCursoAction(){
    	if ( array_key_exists('curso', $_POST) && !empty($_POST['curso']) && array_key_exists('alumno', $_POST) && !empty($_POST['alumno']) ) {
	    	
    		$sql = "SELECT COUNT(*) AS total FROM trelCandidato WHERE fkCurso = " . $_POST['curso'] . " AND fkPersona = " . $_POST['alumno'];
            $this->db->executeQuery($sql);
            $row = $this->db->fetchRow();
            if (is_array($row) && array_key_exists('total', $row) && $row['total'] != 0){
            	$arrRespuesta['resultado'] = 'ko';
                $arrRespuesta['mensaje'] = 'El alumno ya es <strong>candidato</strong> de dicho curso';
            } else {
            	$arrRespuesta['resultado'] = 'ok';
            }
	    	
			$jsonArrRespuesta = json_encode($arrRespuesta);
			echo $jsonArrRespuesta;
			
    	} else {
    		$arrRespuesta['resultado'] = 'ko';
			$jsonArrRespuesta = json_encode($arrRespuesta);
			echo $jsonArrRespuesta;
    	}
    }
    
    /**
     * Edita el horario de un curso
     * @return array
     */
    public function editarHorarioAction(){
    	
    	$arrRespuesta = array();
    	if ( array_key_exists('idHorario', $_POST) && !empty($_POST['idHorario']) ) {
    		
    		if ( ( array_key_exists('nuevoInicio', $_POST) && !empty($_POST['nuevoInicio']) && preg_match('/^\d{1,2}:\d{1,2}$/', $_POST['nuevoInicio']) ) && ( array_key_exists('nuevoFin', $_POST) && !empty($_POST['nuevoFin']) && preg_match('/^\d{1,2}:\d{1,2}$/', $_POST['nuevoFin']) ) ){
    			
    			$horarioDO = TblHorario::findByPrimaryKey($this->db, $_POST['idHorario']);
    			$horarioDO->setIDesde($_POST['nuevoInicio']);
    			$horarioDO->setIHasta($_POST['nuevoFin']);
    			if ( !$horarioDO->update() ){
    				// Error al insertar
	    			$arrRespuesta['resultado'] = 'ko';
	    			$arrRespuesta['mensaje'] = 'Ha ocurrido un error al guardar el horario';
    			}
    			
    		} else {
    			
    			// Horario vacío
    			$arrRespuesta['resultado'] = 'ko';
    			$arrRespuesta['mensaje'] = 'El formato de horario es HH:MM';
    			
    		}
    		
    	} else {
    		
    		// No se encuentra la clave del horario
    		$arrRespuesta['resultado'] = 'ko';
    		$arrRespuesta['mensaje'] = 'No se ha encontrado el horario';
    		
    	}
    	
    	$jsonArrRespuesta = json_encode($arrRespuesta);
		echo $jsonArrRespuesta;
    	
    }
    
}

?>
