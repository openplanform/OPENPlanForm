<?php

require_once 'OwlModule.inc';

class barraHerramientasModule extends OwlModule{
    
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
	 * Contiene los parámetros de la url
	 * @var string
	 */
	protected $param;
	
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
     * @see extranet.planespime.es/owl/lib/OwlModule::requestModule()
     */
    public function requestModule(){
        
    }
    
    /**
     * (non-PHPdoc)
     * @see extranet.planespime.es/owl/lib/OwlModule::runModule()
     */
    public function runModule(){

    	/**
    	 * index: editar y buscar
    	 * alta: limpiar, guardar y listado
    	 * ficha: eliminar, editar y duplicar
    	 * buscar: listado
    	 * 
    	 */
    	
        ?><div id="toolbarPrincipal">
        
            <ul>
            
            	<?php
            	
            	// El botón del panel de inicio siempre se mostrará
            	$this->echoBotonPanel();
            	
            	// Botones especiales para la sección de administración
            	$controladoresAdministracion = array(
                    'administrador',
                    'documento',
            	);
            	
            	if (in_array($this->controller, $controladoresAdministracion)){
            	    
            	    switch ($this->action){
            	        
            	        case 'roles':
            	            $this->echoBotonMenu(true);
                            $this->echoBotonConfig(true);
                            $this->echoBotonRoles(false);
                            $this->echoBotonDocumentos(true);
        	            break;
            	            
            	        case 'menu' :
            	            $this->echoBotonMenu(false);
                            $this->echoBotonConfig(true);
                            $this->echoBotonRoles(true);
                            $this->echoBotonDocumentos(true);
        	            break;
            	            
            	        case 'configuracion':
            	            $this->echoBotonMenu(true);
                            $this->echoBotonConfig(false);
                            $this->echoBotonRoles(true);
                            $this->echoBotonDocumentos(true);
        	            break;
            	            
            	        case 'index' && $this->controller == 'documento':
            	            $this->echoBotonMenu(true);
                            $this->echoBotonConfig(true);
                            $this->echoBotonRoles(true);
                            $this->echoBotonDocumentos(false);
        	            break;
            	            
            	        default:
            	            $this->echoBotonMenu(true);
                            $this->echoBotonConfig(true);
                            $this->echoBotonRoles(true);
                            $this->echoBotonDocumentos(true);
        	            break;
            	        
            	    }
            	    
        	    } else {
            	
        	        // Resto de secciones del sitio
                	switch ($this->action) {
                		
                		// PANEL
                		case 'panel':
    	            		$this->echoBotonBuscar(false);
    	            		$this->echoBotonAnadir(false);
    	            		$this->echoBotonListado(false);
    		            	$this->echoBotonEditar(false);
    		            	$this->echoBotonGuardar(false);
    		            	$this->echoBotonDuplicar(false);
    		            	$this->echoBotonLimpiar(false);
    	            		$this->echoBotonEliminar(false);
                			break;
                			
                		// INDEX
                		case 'index':
    	            		$this->echoBotonBuscar();
    	            		$this->echoBotonAnadir();
    	            		$this->echoBotonListado(false);
    		            	$this->echoBotonEditar(false);
    		            	$this->echoBotonGuardar(false);
    		            	$this->echoBotonDuplicar(false);
    		            	$this->echoBotonLimpiar(false);
    	            		$this->echoBotonEliminar(false);
                			break;
                		
                		// FICHA
                		case 'ficha':
                			$this->echoBotonBuscar(false);
    	            		$this->echoBotonAnadir(false);
    	            		$this->echoBotonListado();
    		            	$this->echoBotonEditar();
    		            	$this->echoBotonGuardar(false);
    		            	$this->echoBotonDuplicar(false);
    		            	$this->echoBotonLimpiar(false);
    	            		$this->echoBotonEliminar(false);
                			break;
                		
                		// BUSCAR
                		case 'buscar':
                			$this->echoBotonBuscar(false);
    	            		$this->echoBotonAnadir();
    	            		$this->echoBotonListado();
    		            	$this->echoBotonEditar(false);
    		            	$this->echoBotonGuardar(false);
    		            	$this->echoBotonDuplicar(false);
    		            	$this->echoBotonLimpiar(false);
    	            		$this->echoBotonEliminar(false);
                			break;
                		
                		// ALTA
                		case 'alta':
                			$this->echoBotonBuscar(false);
    	            		$this->echoBotonAnadir(false);
    	            		$this->echoBotonListado();
    		            	$this->echoBotonEditar(false);
    		            	$this->echoBotonGuardar();
    		            	$this->echoBotonDuplicar(false);
    		            	$this->echoBotonLimpiar();
    	            		$this->echoBotonEliminar(false);
                			break;
                			
                		// EDITAR
                		case 'editar':
                			$this->echoBotonBuscar(false);
    	            		$this->echoBotonAnadir(false);
    	            		$this->echoBotonListado();
    		            	$this->echoBotonEditar(false);
    		            	$this->echoBotonGuardar();
    		            	$this->echoBotonDuplicar();
    		            	$this->echoBotonLimpiar(false);
    	            		$this->echoBotonEliminar();
                			break;
                		
                		default:
                			break;
                	}
                	
        	    }
            	
            	?>
               
            </ul>
        
        </div><?
        
    }
    
    /**
     * Obtiene los parámetros de la url
     * @param string $param
     */
    public function setParam($param) {
    	$this->param = $param;
    }
    
	/**
     * Imprime el botón de buscar
     * @param boolean $activo
     */
	public function echoBotonBuscar($activo = true){
		
		if ( $activo ){
			
			echo '<li class="buscar">
	          	<a href="/' . $this->controller . '/buscar.html" title="Buscar un elemento">Buscar</a>
             </li>';
			
		} else {
			
			echo '<li class="buscar inactivo">
	          	<a href="javascript:void(0)" title="Buscar un elemento">Buscar</a>
             </li>';
			
		}
		
	}
	
	/**
     * Imprime el botón de alta
     * @param boolean $activo
     */
	public function echoBotonAnadir($activo = true){

		if ( $activo ){
			
			echo '<li class="anadir">
	          	<a href="/' . $this->controller . '/alta.html" title="Añadir un elemento nuevo">Añadir</a>
             </li>';
			
		} else {
			
			echo '<li class="anadir inactivo">
	          	<a href="javascript:void(0)" title="Añadir un elemento nuevo">Añadir</a>
             </li>';
			
		}
		
	}
	
	/**
     * Imprime el botón de listado
     * @param boolean $activo
     */
	public function echoBotonListado($activo = true){
		
		if ( $activo ){

			echo '<li class="listado">
	          	<a href="/' . $this->controller . '/index.html" title="Listar todos los elementos">Listado</a>
             </li>';
			
		} else {
			
			echo '<li class="listado inactivo">
	          	<a href="javascript:void(0)" title="Listar todos los elementos">Listado</a>
             </li>';
			
		}
		
	}
	/**
     * Imprime el botón de editar
     * @param boolean $activo
     */
	public function echoBotonEditar($activo = true){
		
		if ( $activo ){
			
			$url = '';
			if ( !empty($this->param ) ){
				$url = '/' . $this->controller . '/editar.html/' . $this->param;	
			}
			
			echo '<li class="editar">
	          	<a href="' . $url . '" title="Edita un elemento">Editar</a>
             </li>';
			
		} else {
			
			echo '<li class="editar inactivo">
	          	<a href="javascript:void(0)" title="Edita un elemento">Editar</a>
             </li>';
			
		}
		
	}

	/**
     * Imprime el botón de guardar
     * @param boolean $activo
     */
	public function echoBotonGuardar($activo = true){
		
		if ( $activo ){
		
			echo '<li class="guardar">
	          	<a href="javascript:void(0)" onclick="guardar(\'' . $this->action . ucfirst($this->controller) . '\')" title="Guarda los datos">Guardar</a>
             </li>';
		
		} else {
			
			echo '<li class="guardar inactivo">
	          	<a href="javascript:void(0)" title="Guarda los datos">Guardar</a>
             </li>';
			
		}
	}
	
	/**
     * Imprime el botón de duplicar
     * @param boolean $activo
     */
	public function echoBotonDuplicar($activo = true){
		
		if ( $activo ){
			
			$url = '';
			if ( !empty($this->param ) ){
				$url = '/' . $this->controller . '/duplicar.html/' . $this->param;	
			}
			
			echo '<li class="duplicar">
	          	<a href="' . $url . '" title="Duplica un elemento">Duplicar</a>
             </li>';
			
		} else {
			
			echo '<li class="duplicar inactivo">
	          	<a href="javascript:void(0)" title="Duplica un elemento">Duplicar</a>
             </li>';
			
		}
		
	}
	
	/**
     * Imprime el botón de limpiar
     * @param boolean $activo
     */
	public function echoBotonLimpiar($activo = true){
		
		if ( $activo ){
		
			echo '<li class="limpiar">
	          	<a href="javascript:void(0)" onclick="limpiar(\'' . $this->action . ucfirst($this->controller) . '\')" title="Vacía los campos del formulario" >Limpiar</a>
             </li>';
		
		} else {
			
			echo '<li class="limpiar inactivo">
	          	<a href="javascript:void(0)" title="Vacía los campos del formulario" >Limpiar</a>
             </li>';
			
		}
		
	}
	
	/**
     * Imprime el botón de eliminar
     * @param boolean $activo
     */
	public function echoBotonEliminar($activo = true){
		
		if ( $activo ){
			
			$url = '';
			if ( !empty($this->param ) ){
				$url = "javascript:ventanaConfirmacion('Confirmar','¿Está seguro que desea <strong>eliminar</strong> este elemento?','/" . $this->controller . "/eliminar.html/" . $this->param  . "')";
				echo '<li class="eliminar">
	          		<a href="' . $url . '" title="Elimina un elemento">Eliminar</a>
             	</li>';	
			} else {
				echo '<li class="eliminar inactivo">
	          		<a href="javascript:void(0)" title="Elimina un elemento">Eliminar</a>
             	</li>';
			}
			
		} else {
			
			echo '<li class="eliminar inactivo">
	          	<a href="javascript:void(0)" title="Elimina un elemento">Eliminar</a>
             </li>';
			
		}
		
	}
	
    /**
     * Imprime el botón de menu
     */
    public function echoBotonMenu($activo = true){
        
        if ($activo) {
        
            echo '<li class="menu">
                <a href="/administrador/menu.html" title="Editar menú">Menú</a>
             </li>';
            
        } else {
            
             echo '<li class="menu inactivo">
                <a href="javascript:void(0)" title="Editar menú">Menú</a>
             </li>';
            
        }
            
            
    }	
	
	
    /**
     * Imprime el botón de configuración
     */
    public function echoBotonConfig($activo = true){
        
        if ($activo){
        
            echo '<li class="config">
                <a href="/administrador/configuracion.html" title="Configuración">Config.</a>
             </li>';
            
        } else {
            
            echo '<li class="config inactivo">
                <a href="javascript:void(0)" title="Configuración">Config.</a>
             </li>';
            
        }
            
    }	
	
    /**
     * Imprime el botón de roles
     */
    public function echoBotonRoles($activo = true){
        
        if ($activo) {
            
            echo '<li class="roles">
                <a href="/administrador/roles.html" title="Administrar Roles">Roles</a>
             </li>';
            
        } else {
            
            echo '<li class="roles inactivo">
                <a href="javascript:void(0)" title="Administrar Roles">Roles</a>
             </li>';
            
        }
            
    }
	
    /**
     * Imprime el botón de documentos
     */
    public function echoBotonDocumentos($activo = true){
        
        if ($activo) {
            
            echo '<li class="documentos">
                <a href="/documento/index.html" title="Administrar Documentos">Docs.</a>
             </li>';
            
        } else {
            
            echo '<li class="documentos inactivo">
                <a href="javascript:void(0)" title="Administrar Documentos">Docs.</a>
             </li>';
            
        }
            
    }

    
    /**
     * Imprime el botón del Panel
     */
    public function echoBotonPanel(){
        
        echo '<li class="panel">
                <a href="/index/panel.html" title="Panel de inicio">Panel</a>
             </li>';
            
    }    
	
	
}

?>
