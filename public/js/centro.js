var $j = jQuery;
var editar = false;

/**
 * Marca en el mapa la localización del centro según la dirección introducida
 */
function obtenerCoordenadasDireccion(){
	
	var pais = $j("#pais").val();
	var provincia = $j("#provincia option:selected").text();
	var poblacion = $j("#poblacion").val();
	var direccion = $j("#direccion").val();
	
	if ( pais != '' || provincia != '' || poblacion != '' || direccion != '' ){
		
		var geocoder = new google.maps.Geocoder();
		geocoder.geocode( { "address": pais + ' ' + provincia + ' ' + poblacion + ' ' + direccion }, function(results, status) {
	        	if (status == google.maps.GeocoderStatus.OK) {
	        		map.setCenter(results[0].geometry.location);
					var marker = new google.maps.Marker({
						map: map, 
						position: results[0].geometry.location
					});
					$j("#latitud").val(results[0].geometry.location.wa);
					$j("#longitud").val(results[0].geometry.location.ya);
		        } else {
		          ventanaKo("Error", "Se produjo un error: " + status)
	        	}
	        }
	    );
		
	} else {
		ventanaKo("Aviso", "Debes completar alguno de estos campos: país, provincia, población, dirección o cp");
	}
	
}

function comprobarCampos() {
	
	// Nombre
	if ( !comprobarVacio('nombre', 'El nombre no puede estar vacío') ){
		return false;
	}
	
	// Academia
	if ( !comprobarVacio('academia', 'La academia no puede estar vacía') ){
		return false;
	}
	
	// País
	if ( !comprobarVacio('pais', 'El país no puede estar vacío') ){
		return false;
	}
	
	// Población
	if ( !comprobarVacio('provincia', 'La provincia no puede estar vacía') ){
		return false;
	}
	
	return true;
	
}

$j(document).ready(function(){
	
	$j('#altaCentro').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
	$j('#editarCentro').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
});
