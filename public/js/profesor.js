var $j = jQuery;
var editar = false;

function comprobarCampos() {
	
	// Datos de usuario
	// Nombre de usuario
	if ( !comprobarVacio('nombreUsuario', 'El nombre no puede estar vacío') ){
		return false;
	}

	// Construccion de nombre de usuario
	var regExpUsuario = /^[a-zA-Z0-9]{5,16}$/; 
	if ( !comprobarRegExp('nombreUsuario', regExpUsuario, 'El nombre no es correcto') ){
		return false;
	}
	
	// Si editamos no comprobamos que el campo contraseña esté vacío
	if ( editar ){
		
		if ( $j('#password1').val() != '' || $j('#repassword1').val() != '' ){
			
			// Contraseña - iguales
			if ( !compararCon('password1', $j('#repassword1').val(), 'Las contraseñas no coinciden') ){
				return false;
			}
			
			// Contraseña - longitud y formato
			var regExpPassword = /^(?=.*\d)(?=.*[A-Za-z@#$%^&+=]).{6,15}$/;
			if ( !comprobarRegExp('password1', regExpPassword, 'La contraseña no es correcta') ){
				return false;
			}
			
		}
		
	} else {
		
		// Contraseña
		if ( !comprobarVacio('password1', 'Las contraseñas no pueden estar vacías') || !comprobarVacio('repassword1', 'Las contraseñas no pueden estar vacías') ){
			return false;
		}
		
		// Contraseña - iguales
		if ( !compararCon('password1', $j('#repassword1').val(), 'Las contraseñas no coinciden') ){
			return false;
		}
		
		// Contraseña - longitud y formato
		var regExpPassword = /^(?=.*\d)(?=.*[A-Za-z@#$%^&+=]).{6,15}$/;
		if ( !comprobarRegExp('password1', regExpPassword, 'La contraseña no es correcta') ){
			return false;
		}
	
	}
	
	// Email
	if ( !comprobarVacio('emailUsuario', 'El email no puede estar vacío') ){
		return false;
	}

	var regExpMail = /^[-a-z0-9~!$%^&*_=+}{\'?]+(\.[-a-z0-9~!$%^&*_=+}{\'?]+)*@([a-z0-9_][-a-z0-9_]*(\.[-a-z0-9_]+)*\.(aero|arpa|biz|com|coop|edu|gov|info|int|mil|museum|name|net|org|pro|travel|mobi|[a-z][a-z])|([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}))(:[0-9]{1,5})?$/i;
	if ( !comprobarRegExp('emailUsuario', regExpMail, 'El formato de correo no es correcto') ){
		return false;
	}
	
	// Datos de profesor
	
	if ( !comprobarVacio('nombre', 'El nombre no puede estar vacío.') ){
		return false;
	}
	
	if ( !comprobarVacio('apellido1', 'El apellido no puede estar vacío.') ){
		return false;
	}

	if ( !comprobarVacio('nacimiento', 'La fecha de nacimiento no puede estar vacía.') ){
		return false;
	}
	
	if ( !comprobarVacio('tipoIdentificacion', 'Debe seleccionar un tipo.') ){
		return false;
	}
	
	if ( !comprobarVacio('dni', 'El número de identificación es obligatorio.') ){
		return false;
	}
	
	if ( !comprobarVacio('pais', 'Seleccionar un país.') ){
		return false;
	}
	
	if ( !comprobarVacio('estadoCivil', 'Seleccionar un estado') ){
		return false;
	}
	
	if ( !comprobarVacio('estadoLaboral', 'Seleccionar un estado') ){
		return false;
	}

	if ( !comprobarVacio('nivelEstudios', 'Seleccionar un nivel') ){
		return false;
	}
	
	return true;
	
}

$j(document).ready(function(){
	
	$j('#altaProfesor').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
	$j('#editarProfesor').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
    $(function() {
        $("#nacimiento" ).datepicker();
    });	
	
});