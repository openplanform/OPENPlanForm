<?php

/**
 * OWL
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Definición de directorios del sistema, en este archivo solo deben guardarse
 * datos del sitema. Para configuraciones utilizar application.ini
 * 
 * @category Owl
 * @package Owl
 * @version 0.5
 * @since 0.5
 * 
 */

// Versión del cms
define('VERSION', '0.5.2-dev');

// Directorio base de la instalación
define('BASEDIR', realpath('../'));

// Core del cms
define('INCDIR', BASEDIR . '/owl/');

// Directorio publico
define('PUBDIR', BASEDIR . '/public/');

// Librería principal
define('LIBDIR', INCDIR . 'lib/');

// Librería externa
define('EXTLIBDIR', INCDIR . 'extlib/');

// Directorio de recursos	
define('SHAREDIR', INCDIR . 'share/');

// Directorio de aplicacion
define('APPDIR', BASEDIR . '/app/');

// Directorio de controladores
define('CONTROLLERDIR', APPDIR . 'controllers/');

// Directorio de configuracion
define('CONFIGDIR', APPDIR . 'configs/');

// Directorio de layouts
define('LAYOUTDIR', APPDIR . 'layouts/');

// Directorio de vistas
define('VIEWDIR', APPDIR . 'views/');

// Directorio de modelos
define('MODELDIR', APPDIR . 'models/');

// Directorio de modulos
define('MODULEDIR', APPDIR . 'modules/');

// Directorio de clases
define('CLASSESDIR', APPDIR . 'classes/');

// Desarrollo | Producción ( Si no estamos en CLI )
if (array_key_exists('SERVER_NAME', $_SERVER)){
	define('DEVELOPMENT', preg_match('/\.in\./', $_SERVER['SERVER_NAME']));
} else {
	define('DEVELOPMENT', true);
}

// Codificación a utilizar
define('APPENCODING', 'UTF-8');

// Zend Framework
define('ZEND_FRAMEWORK', EXTLIBDIR . 'Zend/');

// Directorio de loggin
define('LOGDIR', INCDIR . 'log/');

?>
