<?php

require_once 'OwlSession.inc';
require_once 'OwlMailer.inc';
require_once 'OwlPdf.inc';
require_once 'OwlMailerTemplate.inc';
require_once 'helper/OwlString.inc';

require_once CLASSESDIR . 'PplController.inc';
require_once MODELDIR . '/TblUsuario.inc';
require_once MODELDIR . '/TblUsuarioSearch.inc';


class indexController extends PplController{
	
    
    /**
     * Init
     * @see extranet.planespime.es/owl/lib/OwlController::initController()
     */
    public function initController(){
        
        // Necesitaremos los módulos para el panel principal
        if ($this->actionName == 'panel'){
            $this->rewriteControllerLabel('administrador');
            parent::initController();            
        }
        
        // La página principal siempre será el login
        if ($this->actionName == 'index'){
            
            $this->redirectTo('index', 'login');
            
        }

    }
    
    /**
     * Acción inicial, redirige a login
     * @see extranet.planespime.es/owl/lib/OwlController::indexAction()
     */
	public function indexAction(){

	    
	}
	
	/**
	 * Identifica a un usuario en el sistema
	 */
	public function loginAction(){
	    
	    // Se verifica si el usuario se encuentra ya logueado
        $this->usuario = OwlSession::getValue('usuario');
        
        // De ser así lo redireccionamos a la página principal
        if ($this->usuario instanceof PplUsuarioSesion){
            
            // Si el usuario no tiene una empresa o persona asignada, obligamos a que complete sus datos.
            $claveUsuario = $this->usuario->getId();
            if ($this->aclManager->datosCompletosUsuario($claveUsuario)){
                $this->redirectTo('index', 'panel');
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
                $this->usuario = OwlSession::getValue('usuario');
                $claveUsuario = $this->usuario->getId();
                if ($this->aclManager->datosCompletosUsuario($claveUsuario)){
                    $this->redirectTo('index', 'panel');
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
	    OwlSession::setValue('usuario', null);
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
		        
	        	$password = OwlString::generaPassword(10,false);
	        	
		        // Se obtiene la configuración del mailer
	            $appConfig = $GLOBALS['OWL']['app_config'];
	            if (!$appConfig instanceof OwlApplicationConfig){
	                throw new OwlException('No se ha obtenido la configuración del mailer. Error crítico.', 500);
	            }
	            
	            // Template del mail
	            $mt = new OwlMailerTemplate();
	            $mt->setTemplate(LAYOUTDIR . 'recordatorioContrasena.txt');
	            $mt->addField('USUARIO', $usuario);
	            $mt->addField('CONTRASENA', $password);
	            
	            // Mailer
	            $mailerConfig = $appConfig->getMailerConfiguration();
	            $mailer = new OwlMailer($mailerConfig);
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
	
	/**
	 * Panel Principal
	 */
    public function panelAction(){
        
        // CONVOCATORIAS ------------------------------------
        
        $sql = "SELECT COUNT(*) AS total FROM tblConvocatoria;";
        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $this->view->totalConvocatorias = $row['total'];

        $sql = "SELECT idConvocatoria, vNombre, last_modified FROM tblConvocatoria ORDER BY last_modified DESC LIMIT 1;";
        $this->db->executeQuery($sql);
        $this->view->ultimaConvocatoria = $this->db->fetchRow();
        
        
        // PLANES DE FORMACIÓN -------------------------------
        
        $sql = "SELECT COUNT(*) AS total FROM tblPlan;";
        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $this->view->totalPlanes = $row['total'];
        
        $sql = "SELECT idPlan, vNombre, last_modified FROM tblPlan ORDER BY last_modified DESC LIMIT 1;";
        $this->db->executeQuery($sql);
        $this->view->ultimoPlan = $this->db->fetchRow();
                

        // CURSOS --------------------------------------------
        
        $sql = "SELECT COUNT(*) AS total FROM tblCurso;";
        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $this->view->totalCursos = $row['total'];
        
        $sql = "SELECT idCurso, vNombre, last_modified FROM tblCurso ORDER BY last_modified DESC LIMIT 1;";
        $this->db->executeQuery($sql);
        $this->view->ultimoCurso = $this->db->fetchRow();
                

        // ALUMNOS -------------------------------------------
        
        $rolAlumnos = PplAclManager::ROL_ALUMNO;
        
        $sql = "SELECT COUNT(*) AS total
                FROM   tblPersona p
                WHERE  EXISTS(SELECT NULL
                              FROM   trelRolUsuario ru
                              WHERE  p.fkusuario = ru.fkusuario
                                     AND ru.fkrol = $rolAlumnos)";
        
        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $this->view->totalAlumnos = $row['total'];
                                     
        $sql = "SELECT idPersona,
               vNombre,
               last_modified
        FROM   tblPersona p
        WHERE  EXISTS(SELECT NULL
                      FROM   trelRolUsuario ru
                      WHERE  p.fkusuario = ru.fkusuario
                             AND ru.fkrol = $rolAlumnos)
        ORDER  BY p.last_modified DESC
        LIMIT  1";
        
        $this->db->executeQuery($sql);
        $this->view->ultimoAlumno = $this->db->fetchRow();
        
        // GESTORAS --------------------------------------------
        
        $rolGestora = PplAclManager::ROL_CONSULTORA;
        
        $sql = "SELECT COUNT(*) AS total
                FROM   tblEmpresa e
                WHERE  EXISTS(SELECT NULL
                              FROM   trelRolUsuario ru
                              WHERE  e.fkUsuario = ru.fkUsuario
                                     AND ru.fkRol = $rolGestora)";

        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $this->view->totalGestoras = $row['total'];
        
        $sql = "SELECT idEmpresa,
                       vNombre,
                       last_modified
                FROM   tblEmpresa e
                WHERE  EXISTS(SELECT NULL
                              FROM   trelRolUsuario ru
                              WHERE  e.fkusuario = ru.fkusuario
                                     AND ru.fkrol = $rolGestora)
                ORDER  BY e.last_modified DESC
                LIMIT  1";
        
        $this->db->executeQuery($sql);
        $this->view->ultimaGestora = $this->db->fetchRow();        


        // PROFESORES ------------------------------------------
        
        $rolProfesores = PplAclManager::ROL_PROFESOR;
        
        $sql = "SELECT COUNT(*) AS total
                FROM   tblPersona p
                WHERE  EXISTS(SELECT NULL
                              FROM   trelRolUsuario ru
                              WHERE  p.fkUsuario = ru.fkUsuario
                                     AND ru.fkRol = $rolProfesores)";
        
        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $this->view->totalProfesores = $row['total'];
        
        $sql = "SELECT idPersona,
                       vNombre,
                       last_modified
                FROM   tblPersona p
                WHERE  EXISTS(SELECT NULL
                              FROM   trelRolUsuario ru
                              WHERE  p.fkusuario = ru.fkusuario
                                     AND ru.fkrol = $rolProfesores)
                ORDER  BY p.last_modified DESC
                LIMIT  1";
        
        $this->db->executeQuery($sql);
        $this->view->ultimoProfesor = $this->db->fetchRow();              


        // ACADEMIAS ---------------------------------------------
        
        $rolAcademia = PplAclManager::ROL_ACADEMIA;
        
        $sql = "SELECT COUNT(*) AS total
                FROM   tblEmpresa e
                WHERE  EXISTS(SELECT NULL
                              FROM   trelRolUsuario ru
                              WHERE  e.fkUsuario = ru.fkUsuario
                                     AND ru.fkRol = $rolAcademia)";

        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $this->view->totalAcademias = $row['total'];
        
        $sql = "SELECT idEmpresa,
                       vNombre,
                       last_modified
                FROM   tblEmpresa e
                WHERE  EXISTS(SELECT NULL
                              FROM   trelRolUsuario ru
                              WHERE  e.fkusuario = ru.fkusuario
                                     AND ru.fkrol = $rolAcademia)
                ORDER  BY e.last_modified DESC
                LIMIT  1";
        
        $this->db->executeQuery($sql);
        $this->view->ultimaAcademia = $this->db->fetchRow();

        
        // AULAS -----------------------------------------------
        
        $sql = "SELECT COUNT(*) AS total FROM tblAula;";
        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $this->view->totalAulas = $row['total'];
        
        $sql = "SELECT idAula, vNombre, last_modified FROM tblAula ORDER BY last_modified DESC LIMIT 1;";
        $this->db->executeQuery($sql);
        $this->view->ultimoAula = $this->db->fetchRow();

        
        // CENTROS ----------------------------------------------
        
        $sql = "SELECT COUNT(*) AS total FROM tblCentro;";
        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $this->view->totalCentros = $row['total'];
        
        $sql = "SELECT idCentro, vNombre, last_modified FROM tblCentro ORDER BY last_modified DESC LIMIT 1;";
        $this->db->executeQuery($sql);
        $this->view->ultimoCentro = $this->db->fetchRow();        
        

        // USUARIOS ----------------------------------------------
        
        $sql = "SELECT COUNT(*) AS total FROM tblUsuario;";
        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $this->view->totalUsuarios = $row['total'];
        
        $sql = "SELECT idUsuario, vNombre FROM tblUsuario ORDER BY idUsuario DESC LIMIT 1;";
        $this->db->executeQuery($sql);
        $this->view->ultimoUsuario = $this->db->fetchRow();

    }
	
	
}

?>