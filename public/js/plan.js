var $j = jQuery;

function comprobarCampos() {
	
	if ( !comprobarVacio('nombre', 'El nombre no puede estar vacío') ){
		return false;
	}

	if ( !comprobarVacio('convocatoria', 'La convocatoria no puede estar vacío') ){
		return false;
	}
	
	if ( !comprobarVacio('estado', 'El estado no puede estar vacío') ){
		return false;
	}
	
	if ( !comprobarVacio('propietario', 'El propietario no puede estar vacío') ){
		return false;
	}
	
	if ( !comprobarVacio('consultora', 'La consultora no puede estar vacía') ){
		return false;
	}
	
	return true;
	
}

$j(document).ready(function(){
	
	$j('#altaPlan').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
	$j('#editarPlan').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
});
