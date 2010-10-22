<?php

require_once 'NingenModule.inc';

class logoutModule extends NingenModule{
    
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
     * Request
     * @see extranet.planespime.es/ningencms/lib/NingenModule::requestModule()
     */
    public function requestModule(){
        
        
        
    }
    
    /**
     * Run
     * @see extranet.planespime.es/ningencms/lib/NingenModule::runModule()
     */
    public function runModule(){
        
        if (is_null($this->usuario)){
            return;
        }

        $idRol = $this->acl->getRolMasRelevanteUsuario($this->usuario->getId());
        $rolesIDX = $this->acl->getRoles();
        
        ?><div id="logoutModule">
            <a href="/usuario/ficha/<?= $this->usuario->getId() ?>"><?= $this->usuario->getNombre() ?></a> 
            <strong>(<?= $rolesIDX[$idRol] ?>)</strong> 
            <a href="/index/logout.html" class="cerrarSesion" title="cerrar sesión">
                <span>cerrar sesión</span>
            </a>
        </div><?
        
    }
    
}

?>
