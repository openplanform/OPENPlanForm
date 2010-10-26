<?php

require_once 'NingenCmsSession.inc';
require_once NINGENCMS_CLASSESDIR . 'PplController.inc';


class indexController extends PplController{
	
    
    /**
     * Init
     * @see extranet.planespime.es/ningencms/lib/NingenController::initController()
     */
    public function initController(){
        
        // La página principal siempre será el login
        if ($this->actionName == 'index'){
            
            $this->redirectTo('index', 'login');
            
        }

    }
    
    /**
     * Acción inicial, redirige a login
     * @see extranet.planespime.es/ningencms/lib/NingenController::indexAction()
     */
	public function indexAction(){

	    
	}
	
	/**
	 * Identifica a un usuario en el sistema
	 */
	public function loginAction(){
	    
	    // Se verifica si el usuario se encuentra ya logueado
        $this->usuario = NingenCmsSession::getValue('usuario');
        
        // De ser así lo redireccionamos a la página principal
        if ($this->usuario instanceof PplUsuarioSesion){
            
            // Si el usuario no tiene una empresa o persona asignada, obligamos a que complete sus datos.
            $claveUsuario = $this->usuario->getId();
            if ($this->aclManager->datosCompletosUsuario($claveUsuario)){
                $this->redirectTo('usuario', 'ficha');
            } else {
                $this->redirectTo('usuario', 'nuevo');
            }
            
            return;
        }
	    
	    // El login implementa el layout alternativo
	    $this->setAlternateLayout('libre');
	    
	    if (count($_POST) != 0){
	     
	        // Se verifican y escapan los datos
    	    $usuario = $this->helper->escapeInjection($this->helper->get('username'));
    	    $password = $this->helper->escapeInjection($this->helper->get('password'));
    	    
            if (empty($usuario)){
    	        $this->view->mensaje = 'El nombre de usuario no puede estar vacío.';
    	        return;
    	    }
    	    
    	    if (empty($password)){
    	        $this->view->mensaje = 'La constraseña no puede estar vacía.';
    	        return;
    	    }
    	    
    	    // Se realiza el login
    	    if (!$this->aclManager->login($usuario, $password)){
    	        
    	        $this->view->mensaje = 'Datos Incorrectos.';
    	        return;
    	        
    	    } else {
    	        
                // Si el usuario no tiene una empresa o persona asignada, obligamos a que complete sus datos.
                $this->usuario = NingenCmsSession::getValue('usuario');
                $claveUsuario = $this->usuario->getId();
                if ($this->aclManager->datosCompletosUsuario($claveUsuario)){
                    $this->redirectTo('usuario', 'ficha');
                } else {
                    $this->redirectTo('usuario', 'nuevo');
                }
                
                return;
    	        
    	    }
    	    
	    }    	    
    	    
	}
	
	/**
	 * Elimina al usuario actual de la sesión
	 */
	public function logoutAction(){
	    
	    // Logout tampoco necesita layout
	    $this->setAlternateLayout('libre');
	    
	    // Tararí tararí...
	    NingenCmsSession::setValue('usuario', null);
	    session_destroy();
	    
	    // Redirigimos al login nuevamente
	    $this->redirectTo('index', 'login');
	    
	}
	
	
	
}

?>