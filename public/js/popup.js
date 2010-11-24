
// Muestra el layer de sombra
function showSombra(){
	
	jQuery('#layerTrans').fadeIn('normal');
	
}

// Muestra el popup
function showPopup(){
	
	jQuery('#layerPopup').fadeIn('normal');
	
}

// Prepara el popup
function preparePopup(estado, titulo, mensaje, url, confirmacion){
	
	// Popup de confirmación
	confirmacion = typeof(confirmacion) != 'undefined' ? confirmacion : false;
	
	jQuery('#layoutTitleBar').html(titulo);
	jQuery('#layoutTitle').html(titulo);
	
	jQuery('#layoutContent').removeClass('ok');
	jQuery('#layoutContent').removeClass('ko');
	jQuery('#layoutContent').removeClass('confirmacion');
	jQuery('#layoutContent').addClass(estado);
	
	jQuery('#layoutMessage').html(mensaje);
	
	jQuery('#layerButtons').removeClass('ok');
	jQuery('#layerButtons').removeClass('ko');
	jQuery('#layerButtons').removeClass('confirmacion');
	jQuery('#layerButtons').addClass(estado);
	jQuery('#layerButtons a').attr('href', url);
	
	jQuery('#cancelarButton').remove();

	if ( confirmacion ){
		jQuery('#layerButtons').append('<a id="cancelarButton" class="cancelarButton" href="javascript:hidePopups()">Cancelar</a>');
	}
	
}

// Muestra la ventana de ok
function ventanaOk(titulo, mensaje, url){
	
	if (url == null){
		url = "javascript:hidePopups()";
	}
	
	preparePopup('ok', titulo, mensaje, url);
	showSombra();
	showPopup();
	
}

// Muestra la ventana de ko
function ventanaKo(titulo, mensaje, url){
	
	if (url == null){
		url = "javascript:hidePopups()";
	}
	
	preparePopup('ko', titulo, mensaje, url);
	showSombra();
	showPopup();
	
}

//Muestra la ventana de confirmación
function ventanaConfirmacion(titulo, mensaje, url){
	
	if (url == null){
		url = "javascript:hidePopups()";
	}
	
	preparePopup('confirmacion', titulo, mensaje, url, true);
	showSombra();
	showPopup();
	
}

function hidePopups(){

	jQuery('#layerTrans').fadeOut('normal');
	jQuery('#layerPopup').fadeOut('normal');
	
}
	
