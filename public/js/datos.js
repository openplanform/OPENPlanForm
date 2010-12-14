var $j = jQuery;
var editar = false;

/**
 * Comprueba los campos de carnet de conducir
 * @returns {Boolean}
 */
function comprobarCarnets() {
	
	// Nombre
	if ( !comprobarVacio('nombre', 'El nombre no puede estar vacío') ){
		return false;
	}
	
	// Descripción
	if ( !comprobarVacio('descripcion', 'La descripción no puede estar vacía') ){
		return false;
	}
	
	return true;
	
}

$j(document).ready(function(){
	
	$j('#formCarnet').bind('submit', function() {
		
		return comprobarCarnets();
		
	});
	
});
