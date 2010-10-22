var $j = jQuery;
var editar = false;

function comprobarCampos() {
	
	// Nombre
	if ( !comprobarVacio('nombre', 'El nombre no puede estar vacío') ){
		return false;
	}
	
	// Centro
	if ( !comprobarVacio('centro', 'El centro no puede estar vacío') ){
		return false;
	}
	
	// Capacidad
	if ( !comprobarVacio('capacidad', 'La capacidad no puede estar vacía') ){
		return false;
	}
	
	return true;
	
}

$j(document).ready(function(){
	
	$j('#altaAula').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
	$j('#editarAula').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
});
