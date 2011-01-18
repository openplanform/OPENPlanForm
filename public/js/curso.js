var $j = jQuery;

/**
 * Compara dos fechas en formato dd/mm/aaaa. Devuelve verdadero si la primera es mayor que la segunda.
 * @param fecha
 * @param fecha2
 * @returns boolean
 */
function comparaFecha(fecha, fecha2){
	
	var fechaIni=fecha.split("/");
	var fechaFin=fecha2.split("/");

	// año
	if(parseInt(fechaIni[2],10)>parseInt(fechaFin[2],10)){
		return(true);
	}else{
		
		// año
		if(parseInt(fechaIni[2],10)==parseInt(fechaFin[2],10)){
			
			// mes
			if(parseInt(fechaIni[1],10)>parseInt(fechaFin[1],10)){
				return(true);
			}
			
			// mes
			if(parseInt(fechaIni[1],10)==parseInt(fechaFin[1],10)){
				
				// dia
				if(parseInt(fechaIni[0],10)>parseInt(fechaFin[0],10)){
					return(true);
				}else{
					return(false);
				}
				
			}else{
				return(false);
			}
			
		}else{
			return(false);
		}
	}

}

/**
 * Edita una fila del horario del curso
 * @param idHorario
 */
function editarHorario(idHorario){
	
	var horaInicio = $j("#inicio_" + idHorario).html();
	var horaFin = $j("#fin_" + idHorario).html();
	
	// Estilos de la celda
	$j("#inicio_" + idHorario).css('padding','0px 10px');
	$j("#fin_" + idHorario).css('padding','0px 10px');
	
	// Inputs para modificar el horario
	$j("#inicio_" + idHorario).html('<input type="text" style="width:40px;border:1px solid #A6A6A6" name="nuevoInicio_' + idHorario + '" id="nuevoInicio_' + idHorario + '" value="' + horaInicio + '"/>');
	$j("#fin_" + idHorario).html('<input type="text" style="width:40px;border:1px solid #A6A6A6" name="nuevoFin_' + idHorario + '" id="nuevoFin_' + idHorario + '" value="' + horaFin + '"/>');
	
	// Botón guardar
	$j("#editar_" + idHorario).html('<a href="javascript:enviarHorario(\'' + idHorario + '\')" class="btnGuardar" title="Guardar Horario"><span>guardar</span></a>');
	
}

/**
 * Compara dos horarios en formato HH:MM. Devuelve verdadero si el primero es menor que el segundo
 * @param idInicio
 * @param idFin
 * @return boolean
 */
function comparaHorario(idInicio, idFin){
	
	var inicio = $j("#" + idInicio).val();
	var fin = $j("#" + idFin).val();
	var arrInicio = inicio.split(':');
	var arrFin = fin.split(':');
	
	var horaInicio = parseInt(arrInicio[0], 10);
	var minutosInicio = parseInt(arrInicio[1], 10);
	var horaFin = parseInt(arrFin[0], 10);
	var minutosFin = parseInt(arrFin[1], 10);
	
	// Horas
	if ( horaInicio <= horaFin ){
		
		// Minutos
		if ( minutosInicio <= minutosFin ){
			return true;
		} else {
			return false;
		}
		
	} else {
		return false;
	}
	
}

/**
 * Realiza la modificación real
 * @param idHorario
 */
function enviarHorario(idHorario){
	
	var correcto = true;
	var regExp = /^(([0-1]?[0-9])|([2][0-3])):([0-5]?[0-9])(:([0-5]?[0-9]))?$/;
	var nuevoInicio = $j("#nuevoInicio_" + idHorario).val();
	var nuevoFin = $j("#nuevoFin_" + idHorario).val();
	var horasTotales = $j("#horasTotales").html();
	var horasSesion = $j("#horas_" + idHorario).html();
	var horasAsignadas = $j("#horasAsignadas").html();
	var minutosAsignados = $j("#minutosAsignados").html();
	horasTotales = typeof(horasTotales) != 'undefined' ? horasTotales : '';
	horasSesion = typeof(horasSesion) != 'undefined' ? horasSesion : '';
	horasAsignadas = typeof(horasAsignadas) != 'undefined' ? horasAsignadas : '';
	minutosAsignados = typeof(minutosAsignados) != 'undefined' ? minutosAsignados : '';
	
	// Comprobaciones
	if ( !comprobarVacio('nuevoInicio_'+idHorario) ){
		correcto = false;
		ventanaKo("Error", 'El horario no puede estar vacío');
		return;
	}
	
	if ( !comprobarRegExp('nuevoInicio_'+idHorario, regExp) ){
		correcto = false;
		ventanaKo("Error", 'El formato correcto es HH:MM');
		return;
	}
	
	if ( !comprobarVacio('nuevoFin_'+idHorario) ){
		correcto = false;
		ventanaKo("Error", 'El horario no puede estar vacío');
		return;
	}
	
	if ( !comprobarRegExp('nuevoFin_'+idHorario, regExp) ){
		correcto = false;
		ventanaKo("Error", 'El formato correcto es HH:MM');
		return;
	}
	
	if ( !comparaHorario('nuevoInicio_'+idHorario, 'nuevoFin_'+idHorario) ){
		correcto = false;
		ventanaKo("Error", 'La hora de inicio no puede ser menor que la hora de fin');
		return;
	}
	
	if ( correcto ) {
		
		// loading
		$j("#editar_" + idHorario).html('<div class="cargando" title="guardando..."><span>guardando...</span></div>');
		
		$j.ajax({
	        type: 'POST',
	        url: '/ajax/editarHorario.html',
	        data: 'idHorario=' + idHorario + '&nuevoInicio=' + nuevoInicio + '&nuevoFin=' + nuevoFin + '&horasTotales=' + horasTotales + '&horasSesion=' + horasSesion + '&horasAsignadas=' + horasAsignadas + '&minutosAsignados=' + minutosAsignados,
	        //Mostramos un mensaje con la respuesta
	        success: function(data) {
	        	
				arrRespuesta = $j.parseJSON(data);
	        	if ( arrRespuesta.resultado == 'ko' ) {

	        		ventanaKo("Error", arrRespuesta.mensaje);
	        		// Botón guardar
	        		$j("#editar_" + idHorario).html('<a href="javascript:enviarHorario(\'' + idHorario + '\')" class="btnGuardar" title="Guardar Horario"><span>guardar</span></a>');
	        		
	            } else {
	            	// Estilos de la celda
	        		$j("#inicio_" + idHorario).css('padding','5px 10px');
	        		$j("#fin_" + idHorario).css('padding','5px 10px');
	        		
	        		// Quitamos los inputs para modificar el horario
	        		$j("#inicio_" + idHorario).html(nuevoInicio);
	        		$j("#fin_" + idHorario).html(nuevoFin);
	        		
	        		// Actualizamos la cantidad de horas
	        		var arrHoras = arrRespuesta.horasAsignadas.split(':');
	        		var nuevasHorasAsignadas = arrHoras[0];
	        		var nuevosMinutosAsignados = arrHoras[1];
	        		
	        		// Actualizamos el html
	        		var html = '';
	        		if ( nuevosMinutosAsignados != '00' ){
	        			html += 'en las que <strong id="horasAsignadas">' + nuevasHorasAsignadas + '</strong> horas y <strong id="minutosAsignados">' + nuevosMinutosAsignados + '</strong> minutos han sido asignados.';
	        		} else {
	        			html += 'en las que <strong id="horasAsignadas">' + nuevasHorasAsignadas + '</strong> han sido asignadas.';
	        		}
	        		$j("#horas_" + idHorario).html(arrRespuesta.horas);
	        		$j("#informacionHoras").html(html);
	        		
	        		// Barra de porcentaje
	        		var porcentaje = ( arrHoras[0]*100 ) / horasTotales;
	        		$j("#barraHoras > strong").html('( ' + porcentaje + ' %)');
	        		$j("#barraHoras > div").css('width', porcentaje + '%')
	        		
	        		// Botón editar
	        		$j("#editar_" + idHorario).html('<a href="javascript:editarHorario(\'' + idHorario + '\')" class="btnEditar" title="Editar Horario"><span>editar</span></a>');
	            }
	        }
		});
	}
}

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
 * Redirige a la ficha del documento seleccionado
 */
function verDocumento(){
	
	var idDocumento = $j('#documentosSeleccionados option:selected').attr('value');
	if ( idDocumento ){
		window.open("/documento/ver/" + idDocumento);
	}
	
}

/**
 * Quita las personas del curso
 */
function quitarPersonaCurso(idMultiselect){
	$j('#' + idMultiselect + ' option:selected').remove();
}

/**
 * Quita los documentos del curso
 */
function quitarDocumentosCurso(idMultiselect){
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
 * Añade un documento al curso
 * @param integer idDocumento
 * @param string nombre
 */
function addDocumentoCurso(idDocumento, nombre){
	
	idDocumento = typeof(idDocumento) != 'undefined' ? idDocumento : false;
	var anadir = true;
	
	$j('#documentosSeleccionados option').each( function(){
		if ( $j(this).val() == idDocumento ) {
			anadir = false;
		} 
	});
	
	if ( anadir ){
		$j('#documentosSeleccionados').prepend($('<option selected="selected" onclick="this.select"></option>').attr("value",idDocumento).text(nombre));
	}
	
}

/**
 * Función que selecciona todos los documentos para pasarlos por el form
 */
function selectDocumentos(){
	$j('#documentosSeleccionados option').each( function(){
		$j(this).attr("selected","selected");
	});
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
	
	// Centro
	if ( !comprobarVacio('centro', 'El centro no puede estar vacío') ){
		return false;
	}
	
	// Fechas
	var inicio = $j("#inicio").val();
	var fin = $j("#fin").val();
	if ( inicio != '' && fin != '' && !comparaFecha(fin, inicio) ){
		$j('#errorFecha').html('Fecha incorrecta');
		$j('#fin').css("borderColor","#F00");
		return false;
	} else {
		$j('#fin').css("borderColor","#A6A6A6");
		$j('#errorFecha').html('');
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
		return comprobarCampos();
		
	});
	
	$j('#alumnosCurso').bind('submit', function(){

		// Seleccionamos todos los alumnos del curso para no perderlos al guardar
		selectAlumnos();
		
	});
	
	$j('#materialDidacticoCurso').bind('submit', function(){
		
		// Seleccionamos todos los documentos del curso para no perderlos al guardar
		selectDocumentos();
		
	});
	
	$j('#horarioCurso').bind('submit', function() {
		
		var regExp = /^(([0-1]?[0-9])|([2][0-3])):([0-5]?[0-9])(:([0-5]?[0-9]))?$/;
		
		if ( !$j("#lunes").attr("checked") && !$j("#martes").attr("checked") && !$j("#miercoles").attr("checked") && !$j("#jueves").attr("checked") && !$j("#viernes").attr("checked") && !$j("#sabado").attr("checked") && !$j("#domingo").attr("checked") ) {
			$j("#errorSemana").html("Debe seleccionar un día");
			return false;
		}
		
		if ( !comprobarVacio('inicioGrupo', 'Debe rellenar este campo') ){
			return false;
		}
		
		if ( !comprobarRegExp('inicioGrupo', regExp, 'El formato no es correcto') ){
			return false;
		}
		
		if ( !comprobarVacio('finGrupo', 'Debe rellenar este campo') ){
			return false;
		}
		
		if ( !comprobarRegExp('finGrupo', regExp, 'El formato no es correcto') ){
			return false;
		}
		
		if ( !comparaHorario( 'inicioGrupo', 'finGrupo' ) ){
			ventanaKo("Error", 'La hora de inicio no puede ser menor que la hora de fin');
			return false;
		}
		
	});
	
	$j('#diaCurso').bind('submit', function() {
		
		var regExp = /^(([0-1]?[0-9])|([2][0-3])):([0-5]?[0-9])(:([0-5]?[0-9]))?$/; 
		
		if ( !comprobarVacio('dia', 'Debe rellenar este campo') ){
			return false;
		}
		
		if ( !comprobarVacio('inicioDia', 'Debe rellenar este campo') ){
			return false;
		}
		
		if ( !comprobarRegExp('inicioDia', regExp, 'El formato no es correcto') ){
			return false;
		}
		
		if ( !comprobarVacio('finDia', 'Debe rellenar este campo') ){
			return false;
		}
		
		if ( !comprobarRegExp('finDia', regExp, 'El formato no es correcto') ){
			return false;
		}
		
		if ( !inicioMenorFin( 'inicioDia', 'finDia' ) ){
			ventanaKo("Error", 'La hora de inicio no puede ser menor que la hora de fin');
			return false;
		}
		
	});
	
	$j.datepicker.setDefaults({
		yearRange: 'c-1:c+2'
	});
	
	// Inicio y fin del curso
	$j("#fin" ).datepicker();
    $j("#inicio" ).datepicker({
    	onSelect: function(date){
    		// Hacemos que el selector de fecha de fin sea posterior a la fecha de inicio
    		$j("#fin").datepicker('destroy');
    		$j("#fin").val('');
    		var arrFecha = date.split("/");
    		$j("#fin" ).datepicker({
    			minDate: new Date(arrFecha[2], arrFecha[1]-1, arrFecha[0])
    		});
    	}
    });
    
    // Dia de clase en concreto
    if ( typeof(inicioCurso) != "undefined" && typeof(finCurso) != "undefined" ){
    	var arrInicio = inicioCurso.split("-"); // inicioCurso se setea en la carga de la página
    	var arrFin = finCurso.split("-"); // finCurso se setea en la carga de la página
	    $j("#dia" ).datepicker({
	    	minDate: new Date(arrInicio[0], arrInicio[1]-1, arrInicio[2]),
	    	maxDate: new Date(arrFin[0], arrFin[1]-1, arrFin[2]) 
	    });
    }
    
    // Se permite un decimal
	$j(".decimal").numeric('.', 'none');
    
});
