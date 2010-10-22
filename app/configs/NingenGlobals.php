<?php

/**
 * NINGEN CMS
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Definición de directorios del sistema, en este archivo solo deben guardarse
 * datos del sitema. Para configuraciones utilizar application.ini
 * 
 * @category NingenCms
 * @package NingenCms
 * @version 0.5
 * @since 0.5
 * 
 */

// Versión del cms
define('NINGENCMS_VERSION', '0.5.0');

// Directorio base de la instalación
define('NINGENCMS_BASEDIR', realpath('../'));

// Core del cms
define('NINGENCMS_INCDIR', NINGENCMS_BASEDIR . '/ningencms/');

// Directorio publico
define('NINGENCMS_PUBDIR', NINGENCMS_BASEDIR . '/public/');

// Librería principal
define('NINGENCMS_LIBDIR', NINGENCMS_INCDIR . 'lib/');

// Librería externa
define('NINGENCMS_EXTLIBDIR', NINGENCMS_INCDIR . 'extlib/');

// Directorio de recursos	
define('NINGENCMS_SHAREDIR', NINGENCMS_INCDIR . 'share/');

// Directorio de aplicacion
define('NINGENCMS_APPDIR', NINGENCMS_BASEDIR . '/app/');

// Directorio de controladores
define('NINGENCMS_CONTROLLERDIR', NINGENCMS_APPDIR . 'controllers/');

// Directorio de configuracion
define('NINGENCMS_CONFIGDIR', NINGENCMS_APPDIR . 'configs/');

// Directorio de layouts
define('NINGENCMS_LAYOUTDIR', NINGENCMS_APPDIR . 'layouts/');

// Directorio de vistas
define('NINGENCMS_VIEWDIR', NINGENCMS_APPDIR . 'views/');

// Directorio de modelos
define('NINGENCMS_MODELDIR', NINGENCMS_APPDIR . 'models/');

// Directorio de modulos
define('NINGENCMS_MODULEDIR', NINGENCMS_APPDIR . 'modules/');

// Directorio de clases
define('NINGENCMS_CLASSESDIR', NINGENCMS_APPDIR . 'classes/');

// Desarrollo | Producción
define('NINGENCMS_DEV', preg_match('/\.in\./', $_SERVER['SERVER_NAME']));

// Codificación a utilizar
define('NINGENCMS_APPENCODING', 'UTF-8');

// Zend Framework
define('ZEND_FRAMEWORK', NINGENCMS_EXTLIBDIR . 'Zend/');

?>
