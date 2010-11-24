var $j = jQuery;

/**
 * Pasa los alumnos de un estado a otro
 */
function mueveAlumno(origen, destino){
	
	var id;
	var nombre;
	var anadir;
	
	$j('#' + origen + ' option:selected').each( function(){

		id = $j(this).val();
		nombre = $j(this).attr('text');
		anadir = true;
		$j('#' + destino + ' option').each( function(){
			if ( $j(this).val() == id ) {
				anadir = false;
			}
		});
		
		if ( anadir ){
			$j('#' + origen + ' option:selected').remove();
			$j('#' + destino).prepend($('<option selected="selected" onclick="this.select"></option>').attr("value",id).text(nombre));
		}
		
	});
	
}

/**
 * Redirige a la ficha del alumno seleccionado
 */
function fichaAlumno(idMultiselect){
	
	var id = $j('#' + idMultiselect + ' option:selected').attr('value');
	if ( id ){
		window.open("/alumno/ficha.html/" + id);
	}

}

/**
 * Redirige a la ficha del profesor seleccionado
 */
function fichaProfesor(){
	
	var idProfesor = $j('#profesoresSeleccionados option:selected').attr('value');
	if ( idProfesor ){
		window.open("/profesor/ficha.html/" + idProfesor);
	}
	
}

/**
 * Quita las personas del curso
 */
function quitarPersonaCurso(idMultiselect){
	$j('#' + idMultiselect + ' option:selected').remove();
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
		$j('#profesoresSeleccionados').prepend($('<option selected="selected" onclick="this.select"></option>').attr("value",idProfesor).text(nombre));
	}
	
}

/**
 * Función que selecciona todos los profesores para pasarlos por el form
 */
function selectProfesores(){
	$j('#profesoresSeleccionados option').each( function(){
		$j(this).attr("selected","selected");
	});
}

/**
 * Función que selecciona todos los alumnos para pasarlos por el form
 */
function selectAlumnos(){
	$j('#precandidatos option').each( function(){
		$j(this).attr("selected","selected");
	});
	$j('#candidatos option').each( function(){
		$j(this).attr("selected","selected");
	});
	$j('#alumnos option').each( function(){
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
	    selectProfesores();
		return comprobarCampos();
		
	});
	
	$j('#editarCurso').bind('submit', function() {

		// Seleccionamos todos los profesores del curso para no perderlos al guardar
		selectProfesores();
		// Seleccionamos todos los alumnos del curso para no perderlos al guardar
		selectAlumnos();
		return comprobarCampos();
		
	});
	
	$j.datepicker.setDefaults({
		yearRange: 'c-1:c+2'
	});
	
    $j("#inicio" ).datepicker();
    $j("#fin" ).datepicker();
    
});
