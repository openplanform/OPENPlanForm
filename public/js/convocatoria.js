var $j = jQuery;

function comprobarCampos() {
	
	if ( !comprobarVacio('nombre', 'El nombre no puede estar vacío') ){
		return false;
	}
	
	if ( !comprobarVacio('ano', 'El año no puede estar vacío') ){
		return false;
	}
	
	if ( !comprobarVacio('tipoConvocatoria', 'El tipo no puede estar vacío') ){
		return false;
	}
	
	if ( !comprobarVacio('presupuesto', 'El presupuesto no puede estar vacío') ){
		return false;
	}
	
	return true;
	
}

$j(document).ready(function(){
	
	$j('#altaConvocatoria').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
	$j('#editarConvocatoria').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
});
