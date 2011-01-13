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
	
	// Datos de academia
	
	// Nombre
	if ( !comprobarVacio('nombre', 'El nombre no puede estar vacío') ){
		return false;
	}
	
	// CIF
	if ( !comprobarVacio('cif', 'El cif no puede estar vacío') ){
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
	
	// Persona contacto
	if ( !comprobarVacio('contacto', 'El contacto no puede estar vacío') ){
		return false;
	}
	
	return true;
	
}

$j(document).ready(function(){
	
	$j('#altaAcademia').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
	$j('#editarAcademia').bind('submit', function() {
		
		return comprobarCampos();
		
	});
	
});
