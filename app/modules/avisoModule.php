<?php

require_once 'NingenModule.inc';

class avisoModule extends NingenModule{
    
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

        ?><div class="aviso">
			<h2>Su ficha está incompleta. Una vez haya completado todos los datos podrá acceder a la aplicación.</h2>
		</div><?
        
    }
    
    
    
}

?>
