var $j = jQuery;
var editar = false;

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
