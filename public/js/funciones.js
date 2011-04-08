$j = jQuery;

function resaltaFila(){
	
	$j(".listado tbody tr").mouseover(function() {
	     $j(this).addClass("tr_hover");
	});

	$j(".listado tbody tr").mouseout(function() {
	     $j(this).removeClass("tr_hover");
	});

	
}

jQuery(document).ready(function(){
	
	// Controlo que los campos numéricos sólo permitan números
	// Dinero
	jQuery(".dinero").numeric();
	
	// Números. No se permiten decimales.
	jQuery(".numerico").numeric('none', 'none');
	
	var tooltipId;
	var w;
	var jQtooltip;
	
	// Enlaces externos
	loadExternalUrl();
	
	// Tooltips
	jQuery('.campoTexto').each( function(){
		
		jQuery(this).bind({
			
			focus: function(){
			
				tooltipId = '#' + jQuery(this).attr('id') + 'Tooltip';
				jQtooltip = jQuery(tooltipId);
				w = jQuery(this).css("width");
				jQuery(tooltipId).css('left', w);
				
				if (jQuery(tooltipId).length != 0){
					jQuery(tooltipId).fadeIn('normal');
				}
			},
			
			focusout: function(){
				jQuery(tooltipId).fadeOut('high');
			}
		
		});
		
	});
	
	// Resalta una fila de listado al pasar el ratón por encima
	resaltaFila();
	
});

/* Inicialización en español para la extensión 'UI date picker' para jQuery. */
/* Traducido por Vester (xvester@gmail.com). */
jQuery(function($){
	$.datepicker.regional['es'] = {
		closeText: 'Cerrar',
		prevText: '&#x3c;Ant',
		nextText: 'Sig&#x3e;',
		currentText: 'Hoy',
		monthNames: ['Enero','Febrero','Marzo','Abril','Mayo','Junio',
		'Julio','Agosto','Septiembre','Octubre','Noviembre','Diciembre'],
		monthNamesShort: ['Ene','Feb','Mar','Abr','May','Jun',
		'Jul','Ago','Sep','Oct','Nov','Dic'],
		dayNames: ['Domingo','Lunes','Martes','Mi&eacute;rcoles','Jueves','Viernes','S&aacute;bado'],
		dayNamesShort: ['Dom','Lun','Mar','Mi&eacute;','Juv','Vie','S&aacute;b'],
		dayNamesMin: ['Do','Lu','Ma','Mi','Ju','Vi','S&aacute;'],
		weekHeader: 'Sm',
		dateFormat: 'dd/mm/yy',
		firstDay: 1,
		isRTL: false,
		showMonthAfterYear: false,
		yearRange: 'c-70:c',
        changeMonth: true,
        changeYear: true,
		yearSuffix: ''};
	$.datepicker.setDefaults($.datepicker.regional['es']);
});

/**
 * Devuelve el str con la primera letra en mayúsculas
 * @param str
 * @returns str
 */
function ucfirst (str) {
    var f = str.charAt(0).toUpperCase();
    return f + str.substr(1);
}

/**
 * Comprueba si un input está vacío
 * @returns boolean
 */
function comprobarVacio( idCampo, mensaje ) {
	
	idCampo = typeof(idCampo) != 'undefined' ? idCampo : false;
	mensaje = typeof(mensaje) != 'undefined' ? mensaje : '';
	
	if ( idCampo ){
		
		var idError = '#error' + ucfirst(idCampo);
		if ( $j('#' + idCampo).val() == '' ){
			$j(idError).html(mensaje);
			$j('#' + idCampo).focus();
			$j('#' + idCampo).css("borderColor","#F00");
			return false;
		} else {
			$j('#' + idCampo).css("borderColor","#A6A6A6");
			$j(idError).html('');
			return true;
		}

	}
	
	return false;
	
}

/**
 * Comprueba si un input cumple con una expresión regular
 * @returns boolean
 */
function comprobarRegExp( idCampo, regExp, mensaje ) {
	
	idCampo = typeof(idCampo) != 'undefined' ? idCampo : false;
	mensaje = typeof(mensaje) != 'undefined' ? mensaje : '';
	regExp = typeof(regExp) != 'undefined' ? regExp : false;
	
	if ( idCampo && regExp ){
		
		var idError = '#error' + ucfirst(idCampo);
		if ( !$j('#' + idCampo).val().match(regExp) ){
			$j(idError).html(mensaje);
			$j('#' + idCampo).focus();
			$j('#' + idCampo).css("borderColor","#F00");
			return false;
		} else {
			$j('#' + idCampo).css("borderColor","#A6A6A6");
			$j(idError).html('');
			return true;
		}

	}
	
	return false;
	
}

/**
 * Compara un valor de input con otro valor. Devuelve true si son iguales.
 * @returns boolean
 */
function compararCon( idCampo, valorComprobacion, mensaje ) {
	
	idCampo = typeof(idCampo) != 'undefined' ? idCampo : false;
	mensaje = typeof(mensaje) != 'undefined' ? mensaje : '';
	
	if ( idCampo ){
		
		var idError = '#error' + ucfirst(idCampo);
		if ( $j('#' + idCampo).val() != valorComprobacion ){
			$j(idError).html(mensaje);
			$j('#' + idCampo).focus();
			$j('#' + idCampo).css("borderColor","#F00");
			return false;
		} else {
			$j('#' + idCampo).css("borderColor","#A6A6A6");
			$j(idError).html('');
			return true;
		}

	}
	
	return false;
	
}

/**
 * Comprueba si un usuario ya existe.
 * Editar indica si estamos en la ficha de edición,
 * y realiza la comprobación sólo si el usuario
 * ha cambiado el nombre
 * @param idCampo
 * @param editar
 */
function comprobarUsuario(idCampo, editar) {
	
	editar = typeof(editar) != 'undefined' ? editar : false;
	var usuario = $j('#' + idCampo).val();
	var idError = '#error' + ucfirst(idCampo);
	var comprobar = false;
	
	if ( editar ) {
		var usuarioOculto = $j('#' + idCampo + "Oculto").val();
		if ( usuarioOculto.toLowerCase() != usuario.toLowerCase() ){
			comprobar = true;
		} else {
			$j('#' + idCampo).css("borderColor","#A6A6A6");
			$j(idError).html('');
		}
	} else if ( usuario != '' ){
		comprobar = true;
	}
	
	if ( comprobar ){
		
		$j.ajax({
	        type: 'POST',
	        url: '/ajax/comprobarUsuario.html',
	        data: 'usuario=' + usuario.toLowerCase(),
	        //Mostramos un mensaje con la respuesta
	        success: function(data) {
				arrRespuesta = $j.parseJSON(data);
	        	if ( arrRespuesta.resultado == 'ko' ) {
	        		$j(idError).html(arrRespuesta.mensaje);
	    			$j('#' + idCampo).css("borderColor","#F00");
	            } else {
	            	$j('#' + idCampo).css("borderColor","#A6A6A6");
	    			$j(idError).html('');
	            }
	        }
		});
		
	} else if ( editar ){
		$j('#' + idCampo).css("borderColor","#A6A6A6");
		$j(idError).html('');
	}
}

/**
 * Comprueba si el dni/cif ya existe
 * Editar indica si estamos en la ficha de edición,
 * y realiza la comprobación sólo si el usuario
 * ha cambiado el dni
 * @param string idCampo
 */
function comprobarDni(idCampo, empresa, editar) {
	
	editar = typeof(editar) != 'undefined' ? editar : false;
	empresa = typeof(empresa) != 'undefined' ? empresa : false;
	var dni = $j('#' + idCampo).val();
	var idError = '#error' + ucfirst(idCampo);
	var comprobar = false;
	
	if ( editar ) {
		var dniOculto = $j('#' + idCampo + "Oculto").val();
		if ( dniOculto != dni ){
			comprobar = true;
		} else {
			$j('#' + idCampo).css("borderColor","#A6A6A6");
			$j(idError).html('');
		}
	} else if ( dni != '' ){
		comprobar = true;
	}
	
	if (comprobar) {
	
		$j.ajax({
	        type: 'POST',
	        url: '/ajax/comprobarDni.html',
	        data: 'dni=' + dni + '&empresa=' + empresa,
	        //Mostramos un mensaje con la respuesta
	        success: function(data) {
				arrRespuesta = $j.parseJSON(data);
	        	if ( arrRespuesta.resultado == 'ko' ) {
	        		$j(idError).html(arrRespuesta.mensaje);
	    			$j('#' + idCampo).css("borderColor","#F00");
	            } else {
	            	$j('#' + idCampo).css("borderColor","#A6A6A6");
	    			$j(idError).html('');
	            }
	        }
		});
	
	}
}

//Tratamiento de target_blank
function loadExternalUrl(){

    if( !document.getElementsByTagName ){
        return;
    }

    var links = document.getElementsByTagName( 'a' );
    for( var i=0; i<links.length; i++ ){
    	if( links[i].rel == "external" ){
			links[i].target = "_blank";
        }
    }

}
