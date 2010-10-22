jQuery(document).ready(function(){
	
	jQuery('#agregarRol').bind('submit', function() {
		
		if ( !comprobarVacio('nombre', 'El nombre no puede estar vacío.') ){
			return false;
		}
		
		if ( !comprobarVacio('desc', 'El campo descripción no puede estar vacío.') ){
			return false;
		}
		
		return true;
		
	});
	
	jQuery('#formMenu').submit(function(){
		
		if ( !comprobarVacio('nombre', 'El campo etiqueta no puede estar vacío.') ){
			return false;
		}

		if ( !comprobarVacio('orden', 'El campo orden no puede estar vacío.') ){
			return false;
		}

		if ( !comprobarVacio('controlador', 'Se debe especificar un controlador.') ){
			return false;
		}

		if ( $j('#selectorRol').val() == null ){
			$j('#errorSelectorRol').html('Debe seleccionar como mínimo un rol.');
			$j('#selectorRol').focus();
			$j('#selectorRol').css("borderColor","#F00");
			return false;
		} else {
			$j('#selectorRol').css("borderColor","#A6A6A6");
			$j('#errorSelectorRol').html('');
		}
		
		return true;
		
	});
	
});