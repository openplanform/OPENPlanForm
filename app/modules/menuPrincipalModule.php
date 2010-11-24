<?php

require_once 'OwlModule.inc';
require_once 'OwlException.inc';


class menuPrincipalModule extends OwlModule{

    /**
     * Referencia a la base de datos
     * @var OwlConnection
     */
    protected $db;
    
    /**
     * Árbol jerarquico del menu
     * @var array
     */
    protected $menuDS;
    
    /**
     * Código html del menu
     * @var array
     */
    private $_menuCode = array();
    
    /**
     * Codigo html de los submenus
     * @var array
     */
    public $submenus;    
    
       
    /**
     * Set DB
     * @param $db
     */
    public function setDb(OwlConnection $db){
        
        $this->db = $db;
        
    }
    
    /**
     * Establece el árbol de menú
     * 
     * @param array $menuDS
     */
    public function setMenuArray($menuDS){
        
        if (!$this->menuDS = $menuDS){
            
            throw new OwlException('Error crítico, no se han obtenido los datos del menu', 500);
             
        }
        
    }
   
    /**
     * Procesa los datos del menú
     */
    private function _generaMenu(){

        // Se iterará la lista de acceso en busca de claves patriarca
        foreach ($this->menuDS as $accesoDO){
            
            // Solo incluiremos los items activados para el menu
            if (!$accesoDO->isBMenu()){
                continue;
            }
            
            if ( $accesoDO->getFkPadre() == 0 ){
                
                $controlador = $accesoDO->getVControlador();
                $clave = $accesoDO->getIdAcceso();
                $this->_menuCode[$clave]['DO'] = $accesoDO;
                $this->_menuCode[$clave]['hijos'] = array();
                
            }
            
        }
        
        // Búsqueda recursiva de hijos
        $clavesPatriarca = array_keys($this->_menuCode);
        foreach ($clavesPatriarca as $clavePatriarca) {
            
            $this->_menuCode[$clavePatriarca] = $this->_generaMenuRecursivo($clavePatriarca,  $this->_menuCode[$clavePatriarca]);
            
        }
        
    }
    
    /**
     * Obtiene los hijos recursivamente
     * @return array
     */
    private function _generaMenuRecursivo( $clavePadre, $arrMenu ){
        
        foreach ($this->menuDS as $accesoDO){
            
            // Solo incluiremos los items activados para el menu
            if (!$accesoDO->isBMenu()){
                continue;
            }
            
            if ($clavePadre == $accesoDO->getFkPadre()){               
                
                $claveHijo = $accesoDO->getIdAcceso();
                $arrMenu['hijos'][$claveHijo]['DO'] = $accesoDO;
                $arrMenu['hijos'][$claveHijo]['hijos'] = array();
                $arrMenu['hijos'][$claveHijo] = $this->_generaMenuRecursivo( $claveHijo, $arrMenu['hijos'][$claveHijo]);
                
            }
            
        }
        
        return $arrMenu;
        
    }
    
    /**
     * Genera el Html de los subapartados del menú.
     * @param string
     * @param array
     * @return string
     */
    private function subapartadoHtmlRecursivo( $controlador, $arrMenu, $nivel ) {
    	
        $nivel++;
        
    	$html = '<div id="' . $controlador . 'Menu" class="menu" onmouseover="menuMouseover(event)">' . "\n";
		foreach ($arrMenu as $apartado) {
			
			$accesoDO = $apartado['DO'];
    	    $nombreItem = $accesoDO->getVNombre();
    	    
    	    $nombreParseado = str_ireplace('_', '', $nombreItem);
            
            // Separador delante
            if (preg_match('/^_.+$/', $nombreItem)) {
                $html .= '<div class="menuItemSep"></div>' . "\n";
            }
    	    
			if ( !empty( $apartado['hijos'] ) ){
			    
				$html .= '<a class="menuItem" href="" onclick="return false;" onmouseover="menuItemMouseover(event, \'' . $accesoDO->getVControlador() . $nivel . 'Menu\');">' . "\n";
                $html .= 	'<span class="menuItemText">' . $nombreParseado . '</span><span class="menuItemArrow">&#9654;</span>' . "\n";
                $html .= '</a>' . "\n";
        		
                $this->submenus[] = $this->subapartadoHtmlRecursivo($accesoDO->getVControlador() . $nivel , $apartado['hijos'], $nivel);
                
        	} else {
        	    
        		$html .= '<a class="menuItem" href="/' . $accesoDO->getVControlador() . '/' . $accesoDO->getVAccion() . '.html">' . $nombreParseado . '</a>' . "\n";
        		
        	}
        	
            // Separador detrás
            if (preg_match('/^.+_$/', $nombreItem)) {
                $html .= '<div class="menuItemSep"></div>' . "\n";
            }        	
            
    	}
    	$html .= '</div>' . "\n";
    	
    	return $html;
    }
    
    /**
     * Run
     * @see extranet.planespime.es/owl/lib/OwlModule::runModule()
     */
    public function runModule(){
        
        $this->_generaMenu();
        
        ?>
        <!-- Barra de menu -->
        <div class="menuBar">
	        <?
	            // Se añade el contador "j" para evitar que se generen dos IDs idénticos a partir de un mismo controlador
	        	$j = 0;
	        	
	        	// Creo los apartados principales del menú
	        	foreach ( $this->_menuCode as $apartado ){
	        	    
	        	    $j++;
	        		
	        	    // Sólo imprimiremos el botón de un apartado que tenga hijos
	        	    $hijos = $apartado['hijos'];
	        	    if (count($hijos)){
	        	    
    	        		$accesoDO = $apartado['DO'];
    	        		
    	        		?><a class="menuButton" href="" onclick="return buttonClick(event, '<?= $accesoDO->getVControlador() . $j ?>Menu');" onmouseover="buttonMouseover(event, '<?= $accesoDO->getVControlador() . $j ?>Menu');"><?= $accesoDO->getVNombre() ?></a>
    	        		<?
    	        		
	        	    }
	        		
	        	}
	        	
	        	// Recorro de nuevo el array para crear los subapartados. Hay que recorrerlo de esta manera debido a la estructura de menú del brainJar.
	        	$htmlSubapartados = '';
	        	$j = 0;
	        	foreach ( $this->_menuCode as $apartado) {
	        	    
	        	    $j++;
	        		
	        		if ( !empty( $apartado['hijos'] ) ){
	        			$apartadoDO = $apartado['DO'];
	        			$htmlSubapartados .= $this->subapartadoHtmlRecursivo( $apartadoDO->getVControlador() . $j, $apartado['hijos'], 0);
	        		}
	        		
	        	}
	        	
	        	echo $htmlSubapartados;
	        	
	        	// Se imprimen los submenues
	        	if (is_array($this->submenus) && count($this->submenus) > 0 ){
	        	    echo implode(null, $this->submenus);
	        	} else  {
	        	    echo $this->submenus;
	        	}
	        	
	        ?>
	        
        </div>
        
	        <!--<a class="menuButton" href="" onclick="return buttonClick(event, 'usuariosMenu');" onmouseover="buttonMouseover(event, 'alumnosMenu');">Usuarios</a>
            
             Ejemplo submenu
            
            <div id="planesMenu" class="menu" onmouseover="menuMouseover(event)">
                <a class="menuItem" href="blank.html">Edit Menu Item 1</a>
                <div class="menuItemSep"></div>
                <a class="menuItem" href="blank.html">Edit Menu Item 2</a>
                <a class="menuItem" href="" onclick="return false;" onmouseover="menuItemMouseover(event, 'editMenu3');">
                    <span class="menuItemText">Edit Menu Item 3</span><span class="menuItemArrow">&#9654;</span>
                </a>
                <a class="menuItem" href="blank.html">Edit Menu Item 4</a>
                <div class="menuItemSep"></div>
                <a class="menuItem" href="blank.html">Edit Menu Item 5</a>
            </div>
            
             
            <div id="editMenu3_3" class="menu">
                <a class="menuItem" href="blank.html">Edit Menu 3-3 Item 1</a>
                <a class="menuItem" href="blank.html">Edit Menu 3-3 Item 2</a>
                <a class="menuItem" href="blank.html">Edit Menu 3-3 Item 3</a>
                <div class="menuItemSep"></div>
                <a class="menuItem" href="blank.html">Edit Menu 3-3 Item 4</a>
            </div> --><?
        
    }
    
}

?>
