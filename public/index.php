<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Guión de bootstrap, inicia la ejecución de la aplicación
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

// Se incluyen las definiciones del sistema de archivos
include_once '../app/configs/NingenGlobals.php';


// Se agregan las librerías al include_path
set_include_path(get_include_path() . 
	PATH_SEPARATOR . NINGENCMS_LIBDIR . 
	PATH_SEPARATOR . NINGENCMS_EXTLIBDIR);

// Se inicia la sessión
require_once 'NingenCmsSession.inc';
NingenCmsSession::create();

// Se instancia la aplicación
require_once 'NingenApplication.inc';
$application = new NingenApplication();

?>