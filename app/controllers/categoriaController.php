<?php

require_once CLASSESDIR . 'PplController.inc';
require_once 'helper/OwlHtmlHelper.inc';

require_once MODELDIR . 'TblCategoriaExtended.inc';


class categoriaController extends PplController{
    
	/**
	 * Colección de categorías
	 * @var array
	 */
	protected $categoriasCOL;
	
    
    /**
     * Init
     * @see extranet.planespime.es/owl/lib/OwlController::initController()
     */
    public function initController(){
       
    	$this->rewriteControllerLabel('administrador');
    	parent::initController();
        
    }
    
    
    /**
     * Función recursiva para tratar las categorías
     * @param array $arrayDS
     * @param integer $clavePadre
     * @param integer $nivel
     */
    private function _IteraAccesos($arrayDS, $clavePadre){
        
        foreach ($this->categoriasCOL as $catDO){
            
            if ($catDO->getFkPadre() == $clavePadre){
                $arrayDS[$catDO->getIdCategoria()]['nombre'] = $catDO->getVNombre();
                $arrayDS[$catDO->getIdCategoria()]['DO'] = $catDO;
                $arrayDS[$catDO->getIdCategoria()]['hijos'] = array();
                $arrayDS[$catDO->getIdCategoria()]['hijos'] = $this->_IteraAccesos($arrayDS[$catDO->getIdCategoria()]['hijos'], $catDO->getIdCategoria());
            }
            
        }
        
        return $arrayDS;

    }
    
    
    /**
     * 
     * prepara el código html para el árbol de categorías
     * @param array $arbolDS
     */
    private function _getTreeHtml($arbolDS, $nivel, $selected=''){
        
        $nivel++;
        $html = '';
        
        $html .= $nivel > 1 ? "<li class=\"noItem\"><ul>\n" : "<ul>\n";
        foreach ($arbolDS as $clave=>$arbol){

            $clase = '';
            if (count($arbol['hijos'])){
                $clase = 'class="hasChildren"';
            }
            
            if ($nivel == 1){
                $clase = 'class="root"';
            }
            
            if ($clave == $selected){
                $clase = 'class="seleccionado"';
            }
            
            $catDO = $arbol['DO'];
            $html .= "\t" . '<li '.$clase.'><a href="/categoria/index.html?e=' . $clave . '" ' . '>' . str_ireplace('_', '', $arbol['nombre']) . '</a> </li>' . "\n";
            
            if (count($arbol['hijos'])){
                $html .= $this->_getTreeHtml($arbol['hijos'], $nivel, $selected);
            }
            
        }
        $html .= $nivel > 1 ? "</ul></li>\n"  : "</ul>\n";
        
        return $html;
        
    } 

    
    /**
     * Acción inicial, por defecto, el listado
     * @see extranet.planespime.es/owl/lib/OwlController::indexAction()
     */
    public function indexAction(){
    	
    	// Parámetros
    	$clave = null;
    	$sent = $this->helper->getAndEscape('sent');
		
    	// Editar
    	if (array_key_exists('e', $_REQUEST) && $_REQUEST['e'] != ''){
			$clave = intval($_GET['e']);
			$this->view->claveItem = $clave;
		}
		
		// Eliminar
		if(array_key_exists('edel', $_REQUEST) && $_REQUEST['edel'] != ''){
			$clave = intval($_REQUEST['edel']);
			
			if ($catDO = TblCategoriaExtended::findByPrimaryKey($this->db, $clave)){
				
				if (!$catDO->delete()){
					
					$this->view->popup = array(
                        'estado' => 'ko',
                        'titulo' => 'Error',
                        'mensaje'=> 'Ha ocurrido un error al eliminar la categoría. Inténtelo de nuevo en unos instantes por favor. Muchas gracias.',
                        'url'=> '/categoria/index.html?e=' . $edel,
                    ); 					
					
				}
				
				$this->redirectTo('categoria');
				
			} else {
				
				// Se intenta eliminar una categoría inexistente, redirigimos a index
				$this->redirectTo('categoria');
				return;
				
			}
			
		}
		

    	// EDICION
    	if (!is_null($clave)){
    		
    		if ($catDO = TblCategoriaExtended::findByPrimaryKey($this->db, $clave)){
    			
    			// Inserción de datos
    			if (!empty($sent)){
    				
    				$catDO->setVNombre($this->helper->get('nombre'));
    				$catDO->setVDescripcion($this->helper->get('descripcion'));
    				$catDO->setFkPadre($this->helper->get('padre'));
    				
    				if (!$catDO->update()){
    					
	                    $this->view->popup = array(
	                        'estado' => 'ko',
	                        'titulo' => 'Error',
	                        'mensaje'=> 'Ha ocurrido un error al actualizar la categoría. Inténtelo de nuevo en unos instantes por favor. Muchas gracias.',
	                        'url'=> '/categoria/index.html?e=' . $edel,
	                    );      					
    					
    				}
    				
    			}
    			
    			// Se obtienen los datos
	    		$this->view->editar = true;
    			$this->view->nombre = $catDO->getVNombre();
    			$this->view->desc = $catDO->getVDescripcion();
    			$this->view->padre = $catDO->getFkPadre();
    			
    		}
    		
    		
    	} else {
    		
    		if (!empty($sent)){
    		
	    		// ALTA
	    		$catDO = new TblCategoria($this->db);
	    		$catDO->setVNombre($this->helper->get('nombre'));
	    		$catDO->setVDescripcion($this->helper->get('descripcion'));
	    		$catDO->setFkPadre($this->helper->get('padre'));
	    		
	    		
	    		if (!$catDO->insert()){
	    			
					$this->view->popup = array(
						'estado' => 'ko',
						'titulo' => 'Error',
						'mensaje'=> 'Ha ocurrido un error al insertar la categoría. Inténtelo de nuevo en unos instantes por favor. Muchas gracias.',
						'url'=> '/categoria/index.html'
					);      			
	    			
	    		} else {
	    		
	    			$this->redirectTo('categoria');
	    			
	    		}
	    		
    		}
    		
    		
    	}
    	
    	// Se obtienen las categorías
    	$this->categoriasCOL = $categoriasCOL = TblCategoria::findAll($this->db, 'vNombre ASC');
    	$arbolDS = array();
    	
    	// Se genera el DS correspondiente, con el html
    	$arbolDS = $this->_IteraAccesos($arbolDS, 0, 0);
    	$this->view->htmltree = $this->_getTreeHtml($arbolDS, 0, $clave);
    	$this->view->categoriasPatriarcaCOL = $this->cacheBO->getCategoriasPatriarca();    	
    	
      
    }
    
    
    /**
     * Acción de alta
     * Da de alta una categoria
     */
    public function altaAction(){
        
        echo 'ALTA';
        
    }
    
    /**
     * Acción de ficha
     * Ficha de una categoria
     */
    public function fichaAction(){
        
        echo 'FICHA';
        
    }
    
    
    
    
}

?>