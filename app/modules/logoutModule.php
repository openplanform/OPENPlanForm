<?php

require_once 'OwlModule.inc';

class logoutModule extends OwlModule{
    
    /**
     * Referencia al objeto de usuario en la sesión
     * @var PplUsuarioSesion
     */
    protected $usuario;
    
    /**
     * ACL Manager
     * @var PplAclManager
     */
    protected $acl;
    
    /**
     * Indica si la ficha de usuario está completa o no
     * @var boolean
     */
    protected $fichaUsuario = true;
    
    /**
     * Establece el gestor de listas de acceso
     * @param PplAclManager $acls
     */
    public function setAcl(PplAclManager $acl){
        $this->acl = $acl;
    }
    
    /**
     * Establece el objeto de usuario actual
     * @param PplUsuarioSesion $usuario
     */
    public function setUsuario(PplUsuarioSesion $usuario){
        $this->usuario = $usuario;
    }

    /**
     * Establece si creamos un enlace a la ficha del usuario
     * @param boolean $ficha
     */
    public function setFichaUsuario($ficha){
    	$this->fichaUsuario = $ficha;
    }
    
    /**
     * Request
     * @see extranet.planespime.es/owl/lib/OwlModule::requestModule()
     */
    public function requestModule(){
        
        
        
    }
    
    /**
     * Run
     * @see extranet.planespime.es/owl/lib/OwlModule::runModule()
     */
    public function runModule(){
        
        if (is_null($this->usuario)){
            return;
        }

        $idRol = $this->acl->getRolMasRelevanteUsuario($this->usuario->getId());
        $rolesIDX = $this->acl->getRoles();
        
        ?><div id="logoutModule"><?php 
        
        if ( $this->fichaUsuario ){
        	?><a href="/usuario/ficha/<?= $this->usuario->getId() ?>"><?= $this->usuario->getNombre() ?></a><?
        } else {
        	echo $this->usuario->getNombre();
        }
        
       ?> <strong>(<?= $rolesIDX[$idRol] ?>)</strong> 
            <a href="/index/logout.html" class="cerrarSesion" title="cerrar sesión">
                <span>cerrar sesión</span>
            </a>
        </div><?
        
    }
    
}

?>
