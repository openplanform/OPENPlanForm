var $j = jQuery;

/**
 * Quita los profesores seleccionados del curso
 */
function quitarProfCurso(){
	$j('#profesoresSeleccionados option:selected').remove();
}

/**
 * Añade un profesor al curso
 * @param integer idProfesor
 * @param string nombre
 */
function addProfCurso(idProfesor, nombre){
	
	idProfesor = typeof(idProfesor) != 'undefined' ? idProfesor : false;
	var anadir = true;
	
	$j('#profesoresSeleccionados option').each( function(){
		if ( $j(this).val() == idProfesor ) {
			anadir = false;
		} 
	});
	
	if ( anadir ){
		$j('#profesoresSeleccionados').append($('<option selected="selected" onclick="this.select"></option>').attr("value",idProfesor).text(nombre));
	}
	
}

/**
 * Función que selecciona todos los profesores para pasarlos por el form
 */
function selectAll(){
	$j('#profesoresSeleccionados option').each( function(){
		$j(this).attr("selected","selected");
	});
}

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
		
	    // Seleccionamos todos los profesores del curso para no perderlos al guardar
	    selectAll();
		return comprobarCampos();
		
	});
	
	$j('#editarCurso').bind('submit', function() {

		// Seleccionamos todos los profesores del curso para no perderlos al guardar
		selectAll();
		return comprobarCampos();
		
	});
	
	$j.datepicker.setDefaults({
		yearRange: 'c-1:c+2'
	});
	
    $j("#inicio" ).datepicker();
    $j("#fin" ).datepicker();
	
});
