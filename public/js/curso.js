var $j = jQuery;

function comprobarCampos() {
	
	// Nombre
	if ( !comprobarVacio('nombre', 'El nombre no puede estar vacío') ){
		return false;
	}
	
	// Plan
	if ( !comprobarVacio('plan', 'El plan no puede estar vacío') ){
		return false;
	}
	
	// Categoría
	if ( !comprobarVacio('categoria', 'La categoría no puede estar vacía') ){
		return false;
	}
	
	// Sector
	if ( !comprobarVacio('sector', 'El sector no puede estar vacío') ){
		return false;
	}
	
	// Colectivo
	if ( !comprobarVacio('colectivo', 'El colectivo no puede estar vacío') ){
		return false;
	}
	
	// Modalidad
	if ( !comprobarVacio('modalidad', 'La modalidad no puede estar vacía') ){
		return false;
	}
	
	// Aula
	if ( !comprobarVacio('aula', 'El aula no puede estar vacía') ){
		return false;
	}
	
	return true;
	
}

$j(document).ready(function(){
	
	$j('#altaCurso').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
	$j('#editarCurso').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
	$j.datepicker.setDefaults({
		yearRange: 'c-1:c+2'
	});
	
    $j("#inicio" ).datepicker();
    $j("#fin" ).datepicker();
	
});
