<?php

require_once 'NingenCmsSession.inc';
require_once 'NingenMailer.inc';
require_once 'NingenMailerTemplate.inc';
require_once 'helper/NingenString.inc';
require_once NINGENCMS_CLASSESDIR . 'PplController.inc';

require_once NINGENCMS_MODELDIR . '/TblUsuario.inc';
require_once NINGENCMS_MODELDIR . '/TblUsuarioSearch.inc';


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
                $this->redirectTo('usuario', 'nuevo', $this->usuario->getId());
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
                    $this->redirectTo('usuario', 'nuevo', $this->usuario->getId());
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
	
	/**
	 * El usuario olvidó su contraseña y se le envía una nueva
	 */
	public function recordatorioAction(){
		
	    $this->setAlternateLayout('libre');
	    
	    if (count($_POST) != 0){
	    	
	        // Se verifican y escapan los datos
    	    $usuario = $this->helper->escapeInjection($this->helper->get('username'));
    	    $email = $this->helper->escapeInjection($this->helper->get('email'));
    	    
            if (empty($usuario)){
    	        $this->view->mensaje = 'El nombre de usuario no puede estar vacío.';
    	        return;
    	    }
    	    
    	    if (empty($email)){
    	        $this->view->mensaje = 'El email no puede estar vacío.';
    	        return;
    	    }
    	    
    	    // Se comprueba si existe el usuario
    	    $usuarioSearch = new TblUsuarioSearch();
    	    $usuarioSearch->vNombre = $usuario;
    	    $usuarioSearch->vEmail = $email;
    	    $usuarioDO = array_shift(TblUsuario::find($this->db, $usuarioSearch));
    	    
	        if ( !empty($usuarioDO) ){
		        
	        	$password = NingenString::generaPassword(10,false);
	        	
		        // Se obtiene la configuración del mailer
	            $appConfig = $GLOBALS['NINGEN_CMS']['app_config'];
	            if (!$appConfig instanceof NingenApplicationConfig){
	                throw new NingenException('No se ha obtenido la configuración del mailer. Error crítico.', 500);
	            }
	            
	            // Template del mail
	            $mt = new NingenMailerTemplate();
	            $mt->setTemplate(NINGENCMS_LAYOUTDIR . 'recordatorioContrasena.txt');
	            $mt->addField('USUARIO', $usuario);
	            $mt->addField('CONTRASENA', $password);
	            
	            // Mailer
	            $mailerConfig = $appConfig->getMailerConfiguration();
	            $mailer = new NingenMailer($mailerConfig);
	            $mailer->addTo($email, $usuario);
	            $mailer->setSubject("Formación PIME - Cambio de contraseña");
	            $mailer->setFrom('<noreply@planespime.es>', 'PlanesPIME');
	            $mailer->setBody($mt->getContent());
	            
	            // Se envía el correo
	            if(!$mailer->send()){
	                $this->view->error = 'Error al enviar el mensaje, por favor intente nuevamente en un momento.';
	                return;
	            } else {
	            	$usuarioDO->setVPassword($this->aclManager->codificaPassword($password));
	            	$usuarioDO->update();
	            }
	        	
	        }
	        
	        $this->view->mensaje = 'Si sus datos son correctos, se le ha enviado un correo';
	        
	    }
		
	}
	
}

?>