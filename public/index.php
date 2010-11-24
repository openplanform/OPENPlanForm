<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Guión de bootstrap, inicia la ejecución de la aplicación
 * 
 * @category Owl
 * @package Owl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es>, Aaron Amengual Arranz <aaron@ningen.es>
 * @version 0.5
 * @since 0.5
 * 
 */

// Se incluyen las definiciones del sistema de archivos
include_once '../app/configs/OwlGlobals.php';


// Se agregan las librerías al include_path
set_include_path(get_include_path() . 
    PATH_SEPARATOR . LIBDIR . 
    PATH_SEPARATOR . EXTLIBDIR);

// Se inicia la sessión
require_once 'OwlSession.inc';
OwlCmsSession::create();

// Se instancia la aplicación
require_once 'OwlApplication.inc';
$application = new OwlApplication();

?>