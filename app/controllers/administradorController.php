<?php

require NINGENCMS_CLASSESDIR . 'PplController.inc';
require_once NINGENCMS_MODELDIR . 'TblRol.inc';
require_once NINGENCMS_MODELDIR . 'TblAcceso.inc';
require_once NINGENCMS_MODELDIR . 'TblAccesoExtendido.inc';

require_once 'NingenPaginator.inc';

class administradorController extends PplController{
           
    /**
     * Colección de accesos 
     * @var array
     */
    protected $accesosCOL;
       
    /**
     * Init
     * @see extranet.planespime.es/app/classes/PplController::initController()
     */
    public function initController(){
        
        parent::initController();
        
    }
    
    public function indexAction(){
        
        
        
    }
    

    /**
     * Administración de roles de usuario
     */
    public function rolesAction(){

        // AÑADIR ROL
        if (count($_POST) > 0 && array_key_exists('sent', $_POST)){
            
            $nombre = $this->helper->getAndEscape('nombre');
            $desc = $this->helper->getAndEscape('desc');
            $error = false;
            
            if (empty($nombre)){
                $this->view->errorNombre = 'El nombre no puede estar vacío.';
                $error = true;
            }

            if (empty($nombre)){
                $this->view->errorDesc = 'El campo descripción no puede estar vacío.';
                $error = true;
            }
            
            // Si no hay error, instertamos datos
            if (!$error){
                
                $rolDO = new TblRol($this->db);
                $rolDO->setVNombre($nombre);
                $rolDO->setVDescripcion($desc);
                
                if (!$rolDO->insert()){
                    
                    $this->view->popup = array(
                        'estado' => 'ko',
                        'titulo' => 'Error',
                        'mensaje'=> 'Ha ocurrido un error con el alta del rol. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                        'url'=> '',
                    );
                    
                }
                
            }
            
        }
        
        // ELIMINAR ROL
        if (array_key_exists('d', $_REQUEST) && $_REQUEST['d'] != ''){
            
            $claveRol = intval($_REQUEST['d']);
            
            if (!$rolDO = TblRol::findByPrimaryKey($this->db, $claveRol)){
                
                // Si el rol no existe no mostraremos mensaje
                $this->redirectTo('administrador', 'roles');   
                
            }
            
            // Se elimina el rol 
            if (!$rolDO->delete()){
                
                $this->view->popup = array(
                    'estado' => 'ko',
                    'titulo' => 'Error',
                    'mensaje'=> 'Ha ocurrido un error al eliminar el rol. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                    'url'=> '',
                );                
                
            }

        }
        
        
        // Parámetros de ordenación para el paginador
        $aliasCampos = array(
            'id'  => 'idRol',
            'nom'   => 'vNombre',
            'desc'  => 'vDescripcion',
        );
        
        if ( !empty($_REQUEST) && array_key_exists('o', $_GET) & array_key_exists('ob', $_GET) ){
            $order = $this->helper->escapeInjection($_GET['o']);
            $orderBy = $aliasCampos[$_GET['ob']];
            $aliasOrderBy = $_GET['ob'];
        } else {
            $order   = 'asc';
            $orderBy = 'idRol';
            $aliasOrderBy = 'id';
        }
        
        // Envío el orden a la vista
        if ( $order == 'asc' ){
            $this->view->order = 'desc';
        } else {
            $this->view->order = 'asc';
        }
        
        
        // Se inicia el paginador y se obtienen los datos
        $paginador = new NingenPaginator($this->db, '', 'tblRol', $this->helper);
        $paginador->setPaginaActual(1);
        $paginador->setItemsPorPagina(10);
        $paginador->setOrderBy($orderBy);
        $paginador->setOrder($order);
        
        
        // Datos enviados a la vista
        $this->view->rolesCOL = $paginador->getItemCollection();
        $this->view->cantidadUsuariosIDX = $this->aclManager->getCantidadUsuariosRoles(); 
        $this->view->orderBy = $aliasOrderBy;
        
        // Solo el administrador podrá eliminar roles
        $this->view->editar = $this->aclManager->getRolMasRelevanteUsuario($this->usuario->getId()) == PplAclManager::ROL_ADMINISTRADOR;

    }
       
    /**
     * Administración de menú
     */
    public function menuAction(){
        
       // Valores globales
       $padreSelected = '';
       $this->view->rolesAcceso = array();
       $modo = $this->helper->getAndEscape('modo');
       $clave = $this->helper->getAndEscape('e');
       $edel = $this->helper->getAndEscape('edel');
              
       // MODO AÑADIR MENU
       if (count($_POST) && array_key_exists('sent', $_POST)){
           
           $error = false;
           
           $padre = $this->helper->getAndEscape('padre');
           $nombre = $this->helper->getAndEscape('nombre');
           $orden = $this->helper->getAndEscape('orden');
           $activo = $this->helper->getAndEscape('activo') == 'on';
           $controlador = $this->helper->getAndEscape('controlador');
           $accion = $this->helper->getAndEscape('accion');
           $roles = implode(',', $this->helper->getAndEscape('roles'));
           
           if (empty($nombre)){
               $this->view->errorNombre = 'El campo nombre no puede estar vacío.';
               $error = true;               
           }
           
           if (empty($controlador)){
               $this->view->errorControlador = 'Se debe especificar un controlador.';
               $error = true;               
           }
           
           if (empty($roles)){
               $this->view->errorRol = 'Debe seleccionar como mínimo un rol.';
               $error = true;               
           }
           
           if ($orden == ''){
               $this->view->errorOrden = 'El campo orden no puede estar vacío.';
               $error = true;               
           }
           
           // Se insertan los datos
           if (!$error){
               
               switch ($modo){
                   
                   case 'Añadir':
                       
                       $accesoDO = new TblAcceso($this->db);
                       $accesoDO->setFkPadre($padre);
                       $accesoDO->setVNombre($nombre);
                       $accesoDO->setBMenu($activo);
                       $accesoDO->setVControlador($controlador);
                       $accesoDO->setVAccion($accion);
                       $accesoDO->setIOrden($orden);
                       $accesoDO->setVRoles($roles);
                       
                       // Evitamos la comprobación de FK para la clave 0
                       if ('0' == $padre){
                           $this->db->executeQuery('SET FOREIGN_KEY_CHECKS = 0');
                       }
                       
                       if (!$accesoDO->insert()){
                           
                            $this->view->popup = array(
                                'estado' => 'ko',
                                'titulo' => 'Error',
                                'mensaje'=> 'Ha ocurrido un error al insertar el acceso. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                                'url'=> '/administrador/menu.html',
                            );

                            // Evitamos la comprobación de FK para la clave 0
                            if ('0' == $padre){
                                $this->db->executeQuery('SET FOREIGN_KEY_CHECKS = 1');
                            }
                           
                       } else {
                           
                            // Evitamos la comprobación de FK para la clave 0
                            if ('0' == $padre){
                                $this->db->executeQuery('SET FOREIGN_KEY_CHECKS = 1');
                            }
                           
                           // Hay que redirigir para recargar el menu
                           $this->redirectTo('administrador', 'menu');                           
                           
                       }
                       
                   break;
                   
                   case 'Modificar':
                       
                       if (!$accesoDO = TblAccesoExtendido::findByPrimaryKeyId($this->db, $clave)){
                           
                           $this->view->popup = array(
                                'estado' => 'ko',
                                'titulo' => 'Error',
                                'mensaje'=> 'El acceso a actualizar no existe. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                                'url'=> '/administrador/menu.html?e=' . $clave,
                            );
                           
                       } else {
                           
                           // Hay que redirigir para recargar el menu
                           $this->redirectTo('administrador', 'menu');
                           
                       }         
                       
                       $accesoDO->setFkPadre($padre);
                       $accesoDO->setVNombre($nombre);
                       $accesoDO->setBMenu($activo);
                       $accesoDO->setVControlador($controlador);
                       $accesoDO->setVAccion($accion);
                       $accesoDO->setIOrden($orden);
                       $accesoDO->setVRoles($roles);
                       
                       if (!$accesoDO->update()){
                           
                            $this->view->popup = array(
                                'estado' => 'ko',
                                'titulo' => 'Error',
                                'mensaje'=> 'Ha ocurrido un error al actualizar el acceso. Inténtelo de nuevo en unos instantes por favor.<br/>Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                                'url'=> '/administrador/menu.html?e=' . $clave,
                            );  
                           
                       } else {
                           
                           // Hay que redirigir para recargar el menu
                           $this->redirectTo('administrador', 'menu');
                           
                       }
                       
                   break;
                   
               }
               
           }
           
       }

       
       // MODO ELIMINAR MENU
       if (!empty($edel)){
       
           $errorDel = false;
           if (!$accesoDO = TblAccesoExtendido::findByPrimaryKeyId($this->db, $edel)){
                               
               $this->view->popup = array(
                    'estado' => 'ko',
                    'titulo' => 'Error',
                    'mensaje'=> 'El acceso a eliminar no existe. Inténtelo de nuevo en unos instantes por favor. Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                    'url'=> '/administrador/menu.html?e=' . $edel,
                );
                
                $errorDel = true;
               
           } 
           
           if (!$errorDel){
           
               $padreSelected = $accesoDO->getFkPadre();
        
               if (!$accesoDO->delete()){
                   
                    $this->view->popup = array(
                        'estado' => 'ko',
                        'titulo' => 'Error',
                        'mensaje'=> 'Ha ocurrido un error al eliminar el acceso. Inténtelo de nuevo en unos instantes por favor. Si el problema persiste póngase en contacto con el administrador. Muchas gracias.',
                        'url'=> '/administrador/menu.html?e=' . $edel,
                    );  
                   
               } else {
                   
                   // Hay que redirigir para recargar el menu
                   $this->redirectTo('administrador', 'menu');
                   
               }
              
           }
       
       }
       
       // MODO EDITAR MENU
       if (!empty($clave)){
           
           $this->view->editMode = true;
           $this->view->claveitem = $clave;
           
           if (!$accesoDO = TblAccesoExtendido::findByPrimaryKeyId($this->db, $clave)){
               $this->redirectTo('administrador', 'menu');
               return;
           }
           
           $padreSelected = $accesoDO->getFkPadre();
           $this->view->nombre = $accesoDO->getVNombre();
           $this->view->activo = $accesoDO->isBMenu();
           $this->view->controlador = $accesoDO->getVControlador();
           $this->view->accion = $accesoDO->getVAccion();
           $this->view->orden = $accesoDO->getIOrden();
           
           $rolesAcceso = $accesoDO->getVRoles();
           if (count($rolesAcceso)){
               $this->view->rolesAcceso = explode(',', $rolesAcceso);
           }
           
       }
       
        
       $this->accesosCOL = TblAcceso::findAll($this->db, 'iOrden ASC');
       
       $arbolDS = array();
       $arbolDS = $this->_IteraAccesos($arbolDS, 0, 0);
       
       $claveSeleccionada = (!empty($clave)) ? $clave : $edel;
       
       
       $html = $this->_getTreeHtml($arbolDS, 0, $claveSeleccionada);
       
       $this->view->htmltree = $html;
       $this->view->htmlselect = $this->_getSelectHtml($arbolDS, 0, $padreSelected);
       $this->view->roles = $this->aclManager->getRoles();
        
    }
    
    
    /**
     * 
     * prepara el código html para el árbol de menú
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
            
            $accesoDO = $arbol['DO'];
            $html .= "\t" . '<li '.$clase.'><a href="/administrador/menu.html?e=' . $clave . '" ' . ($accesoDO->isBMenu() ? '' : 'class="inactivo"') . '>' . str_ireplace('_', '', $arbol['nombre']) . '</a></li>' . "\n";
            
            if (count($arbol['hijos'])){
                $html .= $this->_getTreeHtml($arbol['hijos'], $nivel, $selected);
            }
            
        }
        $html .= $nivel > 1 ? "</ul></li>\n"  : "</ul>\n";
        
        return $html;
        
    } 

    
    
    /**
     * 
     * prepara el código html para el árbol de menú
     * @param array $arbolDS
     */
    private function _getSelectHtml($arbolDS, $nivel, $selected = ''){
        
        $nivel++;
        $html = '';
        
        foreach ($arbolDS as $clave => $arbol){

            $sep = '';
            if ($nivel > 1){
                $sep = str_pad('', $nivel, "-") . ' ';
            }
            
            $sel = $clave == $selected ? 'selected="selected"' : '';
            
            $html .= '<option value="' . $clave .'" ' . $sel . '>' . $sep . str_ireplace('_', '', $arbol['nombre']) . '</option>';
            
            if (count($arbol['hijos'])){
                $html .= $this->_getSelectHtml($arbol['hijos'], $nivel, $selected);
            }
            
        }
        
        return $html;
        
    } 
    
    
    /**
     * Función recursiva para tratar el menú
     * @param array $arrayDS
     * @param integer $clavePadre
     * @param integer $nivel
     */
    private function _IteraAccesos($arrayDS, $clavePadre){
        
        foreach ($this->accesosCOL as $accesoDO){
            
            if ($accesoDO->getFkPadre() == $clavePadre){
                $arrayDS[$accesoDO->getIdAcceso()]['nombre'] = $accesoDO->getVNombre();
                $arrayDS[$accesoDO->getIdAcceso()]['DO'] = $accesoDO;
                $arrayDS[$accesoDO->getIdAcceso()]['hijos'] = array();
                $arrayDS[$accesoDO->getIdAcceso()]['hijos'] = $this->_IteraAccesos($arrayDS[$accesoDO->getIdAcceso()]['hijos'], $accesoDO->getIdAcceso());
            }
            
        }
        
        return $arrayDS;
        
    }
    
    
    /**
     * Recarga la caché de menú
     */
    public function reloadmenucacheAction(){
        
        // Se recarga la caché de la lista de acceso
        $this->aclManager->getAclData($this->usuario, true);
        $this->redirectTo('administrador', 'menu');
        
    }   

    /**
     * Administrar configuración
     */
    public function configuracionAction(){
        
        
        
    }
    
}

?>
