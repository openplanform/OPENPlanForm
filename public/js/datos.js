var $j = jQuery;
var editar = false;

/**
 * Comprueba el campo nombre
 * @returns {Boolean}
 */
function comprobarNombre() {
	
	if ( !comprobarVacio('nombre', 'El nombre no puede estar vacío') ){
		return false;
	}
	return true;
	
}

/**
 * Comprueba el campo descripción
 * @returns {Boolean}
 */
function comprobarDescripcion() {
	
	if ( !comprobarVacio('descripcion', 'La descripción no puede estar vacía') ){
		return false;
	}
	return true;
	
}

$j(document).ready(function(){
	
	$j('#formCarnet').bind('submit', function() {
		return ( comprobarNombre() && comprobarDescripcion() );
	});
	$j('#formColectivo').bind('submit', function() {
		return comprobarNombre();
	});
	$j('#formEquipamiento').bind('submit', function() {
		return comprobarNombre();
	});
	$j('#formEstadoCivil').bind('submit', function() {
		return comprobarNombre();
	});
	$j('#formEstadoLaboral').bind('submit', function() {
		return comprobarNombre();
	});
	$j('#formModalidad').bind('submit', function() {
		return comprobarNombre();
	});
	$j('#formNivelEstudio').bind('submit', function() {
		return comprobarNombre();
	});
	$j('#formCategorialaboral').bind('submit', function() {
		return comprobarNombre();
	});
	
});
