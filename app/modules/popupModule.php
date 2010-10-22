<?php

require_once 'NingenModule.inc';

class popupModule extends NingenModule{
    
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
        
        ?><div id="layerTrans"></div>
        <div id="layerPopup">
        
            <div class="barraTitulo" id="layoutTitleBar">Ventana mensaje</div>
            
            <div id="layoutContent" class="ok">
            
                <p id="layoutTitle">Ventana mensaje</p>
                <p id="layoutMessage">Aqui un mensaje descriptivo del mensaje, valga la redundancia.</p>
                
            </div>
            
            <p id="layerButtons" class="ok">
                <a href="" id="btnPopupAceptar">Aceptar</a>
            </p>
        
        </div><?
        
    }
    
}

?>