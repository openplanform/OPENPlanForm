<?php

require_once 'NingenModule.inc';

class barraHerramientasModule extends NingenModule{
    
	/**
	 * Contiene la acción del controlador actual
	 * @var string
	 */
	protected $action;
	
	/**
	 * Contiene el controlador actual
	 * @var string
	 */
	protected $controller;
	
	/**
	 * Setea la acción
	 * @param string $action
	 */
	public function setAction( $action ){
		$this->action = $action;
	}
	
	/**
	 * Setea el controlador
	 * @param string $controller
	 */
	public function setController( $controller ){
		$this->controller = $controller;
	}
	
    /**
     * (non-PHPdoc)
     * @see extranet.planespime.es/ningencms/lib/NingenModule::requestModule()
     */
    public function requestModule(){
        
        
        
    }
    
    /**
     * (non-PHPdoc)
     * @see extranet.planespime.es/ningencms/lib/NingenModule::runModule()
     */
    public function runModule(){

        ?><div id="toolbarPrincipal">
        
            <ul>
                <li class="limpiar">
                    <a href="javascript:void(0)" onclick="limpiar('<?=$this->action . ucfirst($this->controller)?>')" title="Vacía los campos del formulario" >Limpiar</a>
                </li>
                <li class="guardar">
                    <a href="javascript:void(0)" onclick="guardar('<?=$this->action . ucfirst($this->controller)?>')" title="Guarda los datos">Guardar</a>
                </li>
                <li class="eliminar">
                    <a href="">Eliminar</a>
                </li>
                <li class="anadir">
                    <a href="/<?=$this->controller?>/alta.html" title="Añadir un elemento nuevo">Añadir</a>
                </li>
                <li class="editar">
                    <a href="">Editar</a>
                </li>
                <li class="buscar">
                    <a href="">Buscar</a>
                </li>
                <li class="listado">
                    <a href="/<?=$this->controller?>/index.html" title="Listar todos los elementos">Listado</a>
                </li>
                <li class="duplicar">
                    <a href="">Duplicar</a>
                </li>
            </ul>
        
        </div><?
        
    }
    
    
    
}

?>
