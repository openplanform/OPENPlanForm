
/**
 * Reinicia un formulario
 */
function limpiar( idFormulario){
	document.getElementById(idFormulario).reset();
}

/**
 * Envia un formulario
 */
function guardar( idFormulario){
	jQuery("#"+idFormulario).submit();
}