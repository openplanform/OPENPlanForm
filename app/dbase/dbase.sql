-- MySQL dump 10.13  Distrib 5.1.49, for debian-linux-gnu (i686)
--
-- Host: ldes    Database: planespime
-- ------------------------------------------------------
-- Server version	5.0.51a-24+lenny4-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Not dumping tablespaces as no INFORMATION_SCHEMA.FILES table on this server
--

--
-- Table structure for table `tblAcceso`
--

DROP TABLE IF EXISTS `tblAcceso`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblAcceso` (
  `idAcceso` int(11) NOT NULL auto_increment,
  `fkPadre` int(11) NOT NULL default '0',
  `vNombre` varchar(45) NOT NULL,
  `bMenu` tinyint(1) NOT NULL default '1',
  `iOrden` int(3) NOT NULL,
  `vControlador` varchar(45) default NULL,
  `vAccion` varchar(45) default NULL,
  `vRoles` varchar(255) default NULL,
  PRIMARY KEY  (`idAcceso`,`fkPadre`),
  KEY `fk_tblAcceso_tblAcceso1` (`fkPadre`),
  CONSTRAINT `fk_tblAcceso_tblAcceso1` FOREIGN KEY (`fkPadre`) REFERENCES `tblAcceso` (`idAcceso`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=120 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblAcceso`
--

LOCK TABLES `tblAcceso` WRITE;
/*!40000 ALTER TABLE `tblAcceso` DISABLE KEYS */;
INSERT INTO `tblAcceso` VALUES (1,0,'Convocatorias',1,0,'convocatoria',NULL,NULL),(2,1,'Alta',1,0,'convocatoria','alta','1,2'),(3,1,'Listado',1,1,'convocatoria','index','1,2'),(4,1,'_Buscar...',1,3,'convocatoria','buscar','1,2'),(5,1,'Editar',0,5,'convocatoria','editar','1,2'),(6,0,'Planes',1,1,'plan',NULL,NULL),(7,6,'Alta',1,0,'plan','alta','1,2'),(8,6,'Listado',1,1,'plan','index','1,2,3'),(9,6,'_Buscar...',1,4,'plan','buscar','1,2,3'),(10,6,'Editar',0,5,'plan','editar','1,2'),(11,0,'Cursos',1,3,'curso',NULL,NULL),(13,11,'Alta',1,0,'curso','alta','1,3'),(14,11,'Listado',1,1,'curso','index','1,2,3,4,5,6'),(15,11,'_Buscar...',1,6,'curso','buscar','1,2,3,4,5,6'),(16,11,'Editar',0,5,'curso','editar','1,3'),(22,0,'Gestoras',1,4,'consultora',NULL,NULL),(23,22,'Alta',1,0,'consultora','alta','1,2'),(24,22,'Listado',1,1,'consultora','index','1,2,3'),(25,22,'_Buscar...',1,2,'consultora','buscar','1,2,3'),(26,22,'Editar',0,3,'consultora','editar','1,2'),(27,0,'Profesores',1,5,'profesor',NULL,NULL),(28,27,'Alta',1,0,'profesor','alta','1,3,4'),(29,27,'Listado',1,1,'profesor','index','1,2,3,4,5'),(30,27,'_Buscar...',1,2,'profesor','buscar','1,2,3,4,5'),(31,27,'Editar',0,3,'profesor','editar','1,3,4'),(32,0,'Academias',1,6,'academia',NULL,NULL),(33,32,'Alta',1,0,'academia','alta','1,3'),(34,32,'Listado',1,1,'academia','index','1,2,3,4,5,6'),(35,32,'_Buscar...',1,3,'academia','buscar','1,2,3,4,5,6'),(36,32,'Editar',0,3,'academia','editar','1,3,4'),(37,32,'Centros',1,2,'centro',NULL,'1'),(38,37,'Alta',1,0,'centro','alta','1,3,4'),(39,37,'Listado',1,1,'centro','index','1'),(40,37,'_Buscar...',1,3,'centro','buscar','1'),(41,37,'Editar',0,3,'centro','editar','1'),(42,37,'Aulas',1,2,'aula',NULL,'1,3,4'),(43,42,'Alta',1,0,'aula','alta','1,3,4'),(44,42,'Listado',1,1,'aula','index','1,3,4'),(45,42,'_Buscar...',1,2,'aula','buscar','1,3,4'),(46,42,'Editar',0,3,'aula','editar','1,3,4'),(47,11,'Alumnos',1,2,'alumno','','1,2,3,4'),(48,47,'Listado',1,1,'alumno','index','1,3,4'),(49,47,'_Buscar...',1,2,'alumno','buscar','1,3,4'),(50,0,'Usuarios',1,10,'usuario',NULL,NULL),(51,50,'Alta',1,0,'usuario','alta','1'),(52,50,'_Buscar...',1,2,'usuario','buscar','1'),(53,50,'Listado',1,1,'usuario','index','1'),(54,50,'Editar',0,3,'usuario','editar','1'),(55,0,'Administración',1,13,'administrador',NULL,NULL),(56,55,'Roles',1,19,'administrador','roles','1'),(57,55,'Configuración',1,18,'administrador','configuracion','1'),(59,55,'Menú',1,17,'administrador','menu','1'),(71,112,'Países',1,0,'datos','pais','1'),(72,112,'Provincias',1,1,'datos','provincia','1'),(73,112,'Carnets de conducir',1,2,'datos','carnet','1,2,3'),(74,112,'Categorías',1,3,'categoria','index','1,2,3'),(75,112,'Colectivos',1,4,'datos','colectivo','1,2,3'),(76,112,'Equipamiento',1,5,'datos','equipamiento','1,2,3,4'),(77,112,'Estados civiles',1,6,'datos','estadoCivil','1,2,3'),(78,112,'Estados laborales',1,7,'datos','estadoLaboral','1,2,3'),(79,6,'Estados de plan',1,2,'datos','estadoplan','1,2,3'),(81,112,'Modalidades',1,10,'datos','modalidad','1,2,3'),(82,112,'Niveles de estudios',1,11,'datos','estudios','1,2,3'),(83,112,'Requisitos',1,12,'datos','requisito','1,2,3'),(84,112,'Sectores',1,13,'datos','sector','1,2,3'),(85,1,'Tipos de convocatoria',1,2,'datos','tiposConvocatoria','1,2,3'),(86,112,'Tipos de identificaciones',1,15,'datos','identificacion','1,2,3'),(87,6,'Tipos de plan',1,3,'datos','tipoplan','1,2,3'),(97,47,'Editar',0,5,'alumno','editar','1,3'),(98,50,'Ficha',0,4,'usuario','ficha','1,2,3,4,5,6'),(99,1,'Ficha',0,6,'convocatoria','ficha','1,2,3'),(100,11,'Ficha',0,6,'curso','ficha','1,2,3,4,5,6'),(101,47,'Ficha',0,4,'alumno','ficha','1,3,4'),(102,22,'Ficha',0,4,'consultora','ficha','1,2,3'),(103,27,'Ficha',0,4,'profesor','ficha','1,2,3,4,5'),(104,32,'Ficha',0,4,'academia','ficha','1,2,3,4,5,6'),(105,42,'Ficha',0,4,'aula','ficha','1,3,4'),(106,37,'Ficha',0,4,'centro','ficha','1,3,4'),(107,0,'Panel Principal',0,0,'index','panel','1,2,3,4,5,6,7'),(108,47,'Alta',1,0,'alumno','alta','1,2,3,4'),(109,112,'Documentos',1,4,'documento','index','1,2,3,4'),(110,6,'Ficha',0,6,'plan','ficha','1,2,3'),(111,11,'Horario',0,7,'curso','horario','1,2,3'),(112,0,'Datos Comunes',1,11,'datos',NULL,NULL),(113,11,'Documentación',0,3,'curso','documentacion','1,2,3,4'),(114,11,'Alumnos del curso',0,4,'curso','alumnos','1,2,3,4'),(115,0,'Sugerencias',1,12,'sugerencia',NULL,NULL),(117,115,'Listado',1,1,'sugerencia','index','1,2,3,4,5,6'),(118,0,'Editar',0,2,'sugerencia','editar',NULL),(119,115,'Editar',0,2,'sugerencia','editar','1,2,3,4,5');
/*!40000 ALTER TABLE `tblAcceso` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblAlumno`
--

DROP TABLE IF EXISTS `tblAlumno`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblAlumno` (
  `idAlumno` int(11) NOT NULL auto_increment,
  `fkCurso` int(11) NOT NULL,
  `iPersona` int(11) NOT NULL,
  `iUsuario` int(11) NOT NULL,
  `vPais` varchar(45) character set latin1 NOT NULL,
  `vProvincia` varchar(45) default NULL,
  `vTipoIdentificacion` varchar(45) NOT NULL,
  `vEstadoCivil` varchar(45) NOT NULL,
  `vEstadoLaboral` varchar(45) NOT NULL,
  `vNivelEstudios` varchar(45) NOT NULL,
  `vNombre` varchar(45) NOT NULL,
  `vPrimerApellido` varchar(45) NOT NULL,
  `vSegundoApellido` varchar(45) default NULL,
  `vPoblacion` varchar(100) default NULL,
  `vNumeroIdentificacion` varchar(20) NOT NULL,
  `vEmail` varchar(50) NOT NULL,
  `vDireccion` varchar(255) default NULL,
  `bActiva` tinyint(1) default '0',
  `dAlta` date NOT NULL,
  `dNacimiento` date NOT NULL,
  `dBaja` date default NULL,
  `vNumeroSS` varchar(45) default NULL,
  `bNotificacion` tinyint(1) NOT NULL default '0',
  PRIMARY KEY  (`idAlumno`),
  KEY `fk_tblAlumno_trelPlanCursoCentro1` (`fkCurso`),
  CONSTRAINT `fk_tblAlumno_trelPlanCursoCentro1` FOREIGN KEY (`fkCurso`) REFERENCES `tblCurso` (`idCurso`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=484 DEFAULT CHARSET=utf8 COMMENT='Copia datos desde persona, se mantiene el id de usuario';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblAlumno`
--

LOCK TABLES `tblAlumno` WRITE;
/*!40000 ALTER TABLE `tblAlumno` DISABLE KEYS */;
INSERT INTO `tblAlumno` VALUES (193,7,45,114,'es',NULL,'DNI','Soltero/a','Desocupado','Universidad','Aaron','Amengual','Arranz','Palma','435621A','aaron@ningen.es','Gremi Fusters 32',NULL,'2010-12-16','1980-09-27',NULL,NULL,0),(194,8,45,114,'es',NULL,'DNI','Soltero/a','Desocupado','Universidad','Aaron','Amengual','Arranz','Palma','435621A','aaron@ningen.es','Gremi Fusters 32',NULL,'2010-12-16','1980-09-27',NULL,NULL,0),(436,25,45,114,'es',NULL,'DNI','Soltero/a','Desocupado','Universidad','Aaron','Amengual','Arranz','Palma','435621A','aaron@ningen.es','Gremi Fusters 32',NULL,'2010-12-28','1980-09-27',NULL,'0123456789877',0),(441,30,23,82,'es','Araba','DNI','Casado/a','Desocupado','EGB','Diego','Palo','Alagua','Palma de Mallorca','43135621M','aaron@ningen.es','Gremi Fusters 32',NULL,'2011-01-03','1994-11-01',NULL,'',0),(442,30,24,83,'ar','Albacete','DNI','Casado/a','Ocupado','Universidad','Nicolás','Palumbo','','Palma de Mallorca','43135621L','nico@ningen.es','General Riera 27',NULL,'2011-01-03','1984-03-22',NULL,NULL,0),(443,30,25,84,'es','Araba','DNI','Casado/a','Ocupado','Universidad','Xisco','Serra','','Palma de Mallorca','43135621J','xavi@ningen.es','Gremi Fusters 32',NULL,'2011-01-03','1975-05-15',NULL,NULL,0),(444,30,26,85,'es','Araba','DNI','Soltero/a','Ocupado','Universidad','David','Rosselló','Fernandez','Palma de Mallorca','43135621B','david@ningen.es','Av. Alemania 2',NULL,'2011-01-03','1964-12-09',NULL,NULL,0),(445,30,27,86,'es','Araba','DNI','Soltero/a','Ocupado','Universidad','Juan','Fernández','Fernandez','Palma de Mallorca','74859212G','juan@ningen.es','Av. Alemania 2',NULL,'2011-01-03','1964-12-09',NULL,NULL,0),(446,30,28,87,'es','Araba','DNI','Soltero/a','Ocupado','Universidad','Diego','Amengual','Lopez','Palma de Mallorca','43135621F','diego@ningen.es','Av. Alemania 2',NULL,'2011-01-03','1964-12-09',NULL,NULL,0),(447,30,30,89,'es','Araba','DNI','Casado/a','Ocupado','Universidad','Juanjo','García','Méndez','Palma de Mallorca','43135621C','juanjo@ningen.es','Gremi Fusters 32',NULL,'2011-01-03','1975-05-15',NULL,NULL,0),(448,30,31,90,'es','Araba','DNI','Casado/a','Desocupado','EGB','Yeray','Amengual','','Palma de Mallorca','43135621R','yeray@ningen.es','Gremi Fusters 32',NULL,'2011-01-03','1994-11-01',NULL,NULL,0),(449,30,38,107,'es',NULL,'DNI','Casado/a','Desocupado','EGB','Nicolai','Nicolau','','Palma de Mallorca','123321123','nico@ningen.es','',NULL,'2011-01-03','2010-11-12',NULL,NULL,0),(450,30,41,110,'es',NULL,'DNI','Divorciado/a','Desocupado','ESO','Nicolas','Palumbo','Segundo','Palma de Mallorca','31195646','nico@ningen.es','',NULL,'2011-01-03','2010-12-18',NULL,'',0),(451,30,42,111,'es',NULL,'NIE','Divorciado/a','Ocupado','EGB','Nicolas','Palumbo','Tercero','Palma de Mallorca','Y678876678','nico@ningen.es','',NULL,'2011-01-03','2010-12-03',NULL,'',0),(452,30,43,112,'es','A Coruña','DNI','Casado/a','Ocupado','ESO','Torito','Bravo','segundoApellido','Palma de Mallorca','Y777888999','nico@ningen.es','La calle 123',NULL,'2011-01-03','2010-12-12',NULL,NULL,0),(453,30,44,113,'es',NULL,'DNI','Casado/a','Desocupado','ESO','Torito','Bravo','','Palma de Mallorca','Y888777','nico@ningen.es','',NULL,'2011-01-03','2010-12-24',NULL,NULL,0),(454,30,45,114,'es',NULL,'DNI','Soltero/a','Desocupado','Universidad','Aaron','Amengual','Arranz','Palma','435621A','aaron@ningen.es','Gremi Fusters 32',NULL,'2011-01-03','1980-09-27',NULL,'0123456789877',0),(455,30,56,133,'ad','A Coruña','DNI','Casado/a','Desocupado','EGB','Michael','Jackson','','Palma','435621G','aaron@ningen.es','direccion',NULL,'2011-01-03','2010-12-03',NULL,NULL,0),(456,30,57,134,'si','Albacete','DNI','Divorciado/a','Desocupado','Universidad','Mario','Barakus','Mr T','Palma de Mallorca','666777888','nico@ningen.com','La calle 123',NULL,'2011-01-03','1983-04-12',NULL,NULL,0),(457,30,58,136,'hk','Ourense','DNI','Casado/a','Desocupado','EGB','Juana','Llopis','Llopis','Palma','43135621JF','aaron@ningen.es','Gremi Fusters 32',NULL,'2011-01-03','2010-12-16',NULL,'0123456789877',0),(478,35,55,130,'es',NULL,'DNI','Divorciado/a','Desocupado','EGB','Nicolás','Palumbo','','Palma de Mallorca','Y0154689X','nico@ningen.es','',NULL,'2011-01-11','2010-12-16',NULL,NULL,0),(479,35,66,145,'es',NULL,'DNI','Casado/a','Desocupado','EGB','Jose','Perez','','Palma de Mallorca','98778978','nico@ningen.es','',NULL,'2011-01-11','2010-12-16',NULL,NULL,0),(482,28,60,139,'af',NULL,'DNI','Soltero/a','Situación de cuidador no profesional (CPN)','EGB','Conan','El','Bárbaro','Cimmeria','435621E','example@example.com','Gremi Fusters 32',NULL,'2011-01-11','1930-01-01',NULL,'',0),(483,28,66,145,'es',NULL,'DNI','Casado/a','Desocupado','EGB','Jose','Perez','','Palma de Mallorca','98778978','nico@ningen.es','',NULL,'2011-01-11','2010-12-16',NULL,NULL,0);
/*!40000 ALTER TABLE `tblAlumno` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblAula`
--

DROP TABLE IF EXISTS `tblAula`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblAula` (
  `idAula` int(11) NOT NULL auto_increment,
  `fkCentro` int(11) NOT NULL,
  `fkProvincia` int(11) default NULL,
  `fkPais` varchar(2) character set latin1 default NULL,
  `vNombre` varchar(255) default NULL,
  `iCapacidad` int(11) NOT NULL,
  `vDireccion` varchar(255) default NULL,
  `vDescripcion` varchar(1000) default NULL,
  `vPoblacion` varchar(255) default NULL,
  `mod_user` varchar(45) default NULL,
  `last_modified` date default NULL,
  PRIMARY KEY  (`idAula`),
  KEY `fk_tblAula_tblCentro1` (`fkCentro`),
  KEY `fk_tblAula_tblProvincia1` (`fkProvincia`),
  KEY `fk_tblAula_tblPais1` (`fkPais`),
  CONSTRAINT `fk_tblAula_tblCentro1` FOREIGN KEY (`fkCentro`) REFERENCES `tblCentro` (`idCentro`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblAula_tblPais1` FOREIGN KEY (`fkPais`) REFERENCES `tblPais` (`vIso`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblAula_tblProvincia1` FOREIGN KEY (`fkProvincia`) REFERENCES `tblProvincia` (`idProvincia`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblAvatar`
--

DROP TABLE IF EXISTS `tblAvatar`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblAvatar` (
  `idAvatar` int(11) NOT NULL auto_increment,
  `fkUsuario` int(11) NOT NULL,
  `vArchivo` varchar(45) NOT NULL,
  `bActivo` tinyint(1) default '1',
  `iAncho` int(5) NOT NULL,
  `iAlto` int(5) NOT NULL,
  `vMime` varchar(45) NOT NULL,
  `vTamano` varchar(45) default NULL,
  PRIMARY KEY  (`idAvatar`),
  KEY `fk_tblAvatar_tblUsuario` (`fkUsuario`),
  CONSTRAINT `fk_tblAvatar_tblUsuario` FOREIGN KEY (`fkUsuario`) REFERENCES `tblUsuario` (`idUsuario`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblCarnetConducir`
--

DROP TABLE IF EXISTS `tblCarnetConducir`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblCarnetConducir` (
  `idCarnetConducir` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idCarnetConducir`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblCarnetConducir`
--

LOCK TABLES `tblCarnetConducir` WRITE;
/*!40000 ALTER TABLE `tblCarnetConducir` DISABLE KEYS */;
INSERT INTO `tblCarnetConducir` VALUES (1,'B','Coche'),(5,'A','Ciclomotor');
/*!40000 ALTER TABLE `tblCarnetConducir` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblCategoria`
--

DROP TABLE IF EXISTS `tblCategoria`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblCategoria` (
  `idCategoria` int(11) NOT NULL auto_increment,
  `fkPadre` int(11) NOT NULL default '0',
  `vNombre` varchar(255) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idCategoria`,`fkPadre`),
  KEY `fk_tblCategoria_tblCategoria1` (`fkPadre`)
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8 COMMENT='Idiomas, Inglés, Alemán, Informática, PHP';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblCategoriaEmpleo`
--

DROP TABLE IF EXISTS `tblCategoriaEmpleo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblCategoriaEmpleo` (
  `idCategoriaEmpleo` int(11) NOT NULL auto_increment,
  `vNombre` varchar(45) default NULL,
  PRIMARY KEY  (`idCategoriaEmpleo`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblCategoriaEmpleo`
--

LOCK TABLES `tblCategoriaEmpleo` WRITE;
/*!40000 ALTER TABLE `tblCategoriaEmpleo` DISABLE KEYS */;
INSERT INTO `tblCategoriaEmpleo` VALUES (1,'Directivo'),(2,'Comando intermedio'),(3,'Técnico'),(4,'Trabajador cualificado'),(5,'Trabajador de baja cualificación');
/*!40000 ALTER TABLE `tblCategoriaEmpleo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblCentro`
--

DROP TABLE IF EXISTS `tblCentro`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblCentro` (
  `idCentro` int(11) NOT NULL auto_increment,
  `fkProvincia` int(11) default NULL,
  `fkPais` varchar(2) character set latin1 NOT NULL,
  `fkEmpresa` int(11) NOT NULL,
  `vNombre` varchar(255) NOT NULL,
  `vPoblacion` varchar(45) default NULL,
  `vTelefono` varchar(45) default NULL,
  `vLatitud` varchar(45) default NULL,
  `vLongitud` varchar(45) default NULL,
  `vDireccion` varchar(255) default NULL,
  `vDescripcion` varchar(1000) default NULL,
  `mod_user` varchar(45) default NULL,
  `last_modified` date default NULL,
  PRIMARY KEY  (`idCentro`),
  KEY `fk_tblCentro_tblProvincia1` (`fkProvincia`),
  KEY `fk_tblCentro_tblPais1` (`fkPais`),
  KEY `fk_tblCentro_tblEmpresa1` (`fkEmpresa`),
  CONSTRAINT `fk_tblCentro_tblEmpresa1` FOREIGN KEY (`fkEmpresa`) REFERENCES `tblEmpresa` (`idEmpresa`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblCentro_tblPais1` FOREIGN KEY (`fkPais`) REFERENCES `tblPais` (`vIso`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblCentro_tblProvincia1` FOREIGN KEY (`fkProvincia`) REFERENCES `tblProvincia` (`idProvincia`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblCobroParo`
--

DROP TABLE IF EXISTS `tblCobroParo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblCobroParo` (
  `idCobroParo` int(11) NOT NULL auto_increment,
  `vNombre` varchar(100) NOT NULL,
  PRIMARY KEY  (`idCobroParo`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblCobroParo`
--

LOCK TABLES `tblCobroParo` WRITE;
/*!40000 ALTER TABLE `tblCobroParo` DISABLE KEYS */;
INSERT INTO `tblCobroParo` VALUES (1,'Cobro prestación por desempleo'),(2,'Cobro subsidio de desempleo'),(3,'He solicitado prestación o subsidio'),(4,'No cobro ni prestación ni subsidio');
/*!40000 ALTER TABLE `tblCobroParo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblColectivo`
--

DROP TABLE IF EXISTS `tblColectivo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblColectivo` (
  `idColectivo` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idColectivo`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblColectivo`
--

LOCK TABLES `tblColectivo` WRITE;
/*!40000 ALTER TABLE `tblColectivo` DISABLE KEYS */;
INSERT INTO `tblColectivo` VALUES (1,'Preferentemente desocupados','Desc'),(2,'Preferentemente ocupados','Desc');
/*!40000 ALTER TABLE `tblColectivo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblConvocatoria`
--

DROP TABLE IF EXISTS `tblConvocatoria`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblConvocatoria` (
  `idConvocatoria` int(11) NOT NULL auto_increment,
  `fkTipoConvocatoria` int(11) NOT NULL,
  `vNombre` varchar(255) NOT NULL,
  `iAno` smallint(6) NOT NULL,
  `ePresupuesto` decimal(11,2) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  `mod_user` varchar(45) default NULL,
  `last_modified` date default NULL,
  PRIMARY KEY  (`idConvocatoria`),
  KEY `fk_tblConvocatoria_tblTipoConvocatoria1` (`fkTipoConvocatoria`),
  CONSTRAINT `fk_tblConvocatoria_tblTipoConvocatoria1` FOREIGN KEY (`fkTipoConvocatoria`) REFERENCES `tblTipoConvocatoria` (`idTipoConvocatoria`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblCurso`
--

DROP TABLE IF EXISTS `tblCurso`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblCurso` (
  `idCurso` int(11) NOT NULL auto_increment,
  `fkPlan` int(11) NOT NULL,
  `fkCategoria` int(11) NOT NULL,
  `fkColectivo` int(11) NOT NULL,
  `fkModalidad` int(11) NOT NULL,
  `fkCentro` int(11) NOT NULL,
  `vNombre` varchar(255) NOT NULL,
  `bNotificacionInicio` tinyint(1) NOT NULL default '0',
  `bNotificacionFin` tinyint(1) NOT NULL default '0',
  `vDescripcion` varchar(1000) default NULL,
  `iHorasPresenciales` int(4) default NULL,
  `iHorasDistancia` int(4) default NULL,
  `dInicio` date default NULL,
  `dFin` date default NULL,
  `iNumeroAlumnos` int(4) default NULL,
  `mod_user` varchar(45) default NULL,
  `last_modified` date default NULL,
  `iGrupo` int(4) default NULL,
  `iAccion` float default NULL,
  `vObservaciones` varchar(1000) default NULL,
  `vExpediente` varchar(45) default NULL,
  PRIMARY KEY  (`idCurso`),
  KEY `fk_trelPlanCursoCentro_tblPlan1` (`fkPlan`),
  KEY `fk_tblCurso_tblCategoria1` (`fkCategoria`),
  KEY `fk_tblCurso_tblColectivo1` (`fkColectivo`),
  KEY `fk_tblCurso_tblModalidad1` (`fkModalidad`),
  KEY `fk_tblCurso_tblCentro1` (`fkCentro`),
  CONSTRAINT `fk_tblCurso_tblCategoria1` FOREIGN KEY (`fkCategoria`) REFERENCES `tblCategoria` (`idCategoria`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblCurso_tblCentro1` FOREIGN KEY (`fkCentro`) REFERENCES `tblCentro` (`idCentro`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblCurso_tblColectivo1` FOREIGN KEY (`fkColectivo`) REFERENCES `tblColectivo` (`idColectivo`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblCurso_tblModalidad1` FOREIGN KEY (`fkModalidad`) REFERENCES `tblModalidad` (`idModalidad`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_trelPlanCursoCentro_tblPlan1` FOREIGN KEY (`fkPlan`) REFERENCES `tblPlan` (`idPlan`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=36 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblDesiderata`
--

DROP TABLE IF EXISTS `tblDesiderata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblDesiderata` (
  `idDesiderata` int(11) NOT NULL auto_increment,
  `fkPersona` int(11) NOT NULL,
  `vDescripcion` varchar(1000) NOT NULL,
  PRIMARY KEY  (`idDesiderata`),
  KEY `fk_tblDesiderata_tblPersona1` (`fkPersona`),
  CONSTRAINT `fk_tblDesiderata_tblPersona1` FOREIGN KEY (`fkPersona`) REFERENCES `tblPersona` (`idPersona`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblDisponibilidadAula`
--

DROP TABLE IF EXISTS `tblDisponibilidadAula`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblDisponibilidadAula` (
  `idDisponibilidadAula` int(11) NOT NULL auto_increment,
  `fkAula` int(11) NOT NULL,
  `dInicio` datetime NOT NULL,
  `dFin` datetime NOT NULL,
  PRIMARY KEY  (`idDisponibilidadAula`),
  KEY `fk_tblDisponibilidadAula_tblAula1` (`fkAula`),
  CONSTRAINT `fk_tblDisponibilidadAula_tblAula1` FOREIGN KEY (`fkAula`) REFERENCES `tblAula` (`idAula`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblDisponibilidadProfesor`
--

DROP TABLE IF EXISTS `tblDisponibilidadProfesor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblDisponibilidadProfesor` (
  `fkPersona` int(11) NOT NULL,
  `dInicio` date default NULL,
  `dFin` date default NULL,
  `idDisponibilidad` int(11) NOT NULL,
  PRIMARY KEY  (`idDisponibilidad`),
  KEY `fk_tblDisponibilidadProfesor_tblPersona1` (`fkPersona`),
  CONSTRAINT `fk_tblDisponibilidadProfesor_tblPersona1` FOREIGN KEY (`fkPersona`) REFERENCES `tblPersona` (`idPersona`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblDocumento`
--

DROP TABLE IF EXISTS `tblDocumento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblDocumento` (
  `idDocumento` int(11) NOT NULL auto_increment,
  `vRealName` varchar(45) NOT NULL,
  `vNombre` varchar(45) NOT NULL,
  `vMime` varchar(100) NOT NULL,
  `vTamano` varchar(10) default NULL,
  `vDescription` varchar(1000) default NULL,
  `bDinamico` varchar(45) NOT NULL default '0',
  `vIdentificador` varchar(45) default NULL,
  `mod_user` varchar(45) NOT NULL,
  `last_modified` date NOT NULL,
  PRIMARY KEY  (`idDocumento`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblEmpresa`
--

DROP TABLE IF EXISTS `tblEmpresa`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblEmpresa` (
  `idEmpresa` int(11) NOT NULL auto_increment,
  `fkPais` varchar(2) character set latin1 NOT NULL,
  `fkProvincia` int(11) default NULL,
  `fkUsuario` int(11) NOT NULL,
  `vNombre` varchar(100) character set latin1 NOT NULL,
  `vCif` varchar(9) character set latin1 NOT NULL,
  `vPoblacion` varchar(100) character set latin1 default NULL,
  `vDireccion` varchar(255) character set latin1 default NULL,
  `vCp` varchar(9) character set latin1 default NULL,
  `vLatitud` varchar(45) default NULL,
  `vLongitud` varchar(45) default NULL,
  `vTelefono` bigint(20) default NULL,
  `vTelefono2` bigint(20) default NULL,
  `vFax` bigint(20) default NULL,
  `bActiva` tinyint(1) default '0',
  `dAlta` date NOT NULL,
  `dBaja` date default NULL,
  `mod_user` varchar(45) default NULL,
  `last_modified` date default NULL,
  `vPersonaContacto` varchar(100) NOT NULL,
  PRIMARY KEY  (`idEmpresa`),
  KEY `fk_tblEmpresa_tblPais` (`fkPais`),
  KEY `fk_tblEmpresa_tblProvincia1` (`fkProvincia`),
  KEY `fk_tblEmpresa_tblUsuario1` (`fkUsuario`),
  CONSTRAINT `fk_tblEmpresa_tblPais0` FOREIGN KEY (`fkPais`) REFERENCES `tblPais` (`vIso`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblEmpresa_tblProvincia10` FOREIGN KEY (`fkProvincia`) REFERENCES `tblProvincia` (`idProvincia`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblEmpresa_tblUsuario10` FOREIGN KEY (`fkUsuario`) REFERENCES `tblUsuario` (`idUsuario`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblEmpresa`
--

LOCK TABLES `tblEmpresa` WRITE;
/*!40000 ALTER TABLE `tblEmpresa` DISABLE KEYS */;
INSERT INTO `tblEmpresa` VALUES (13,'es',1,57,'+Humana','43135621H','Palma de Mallorca','Gremi Fusters 32','07005',NULL,NULL,971758585,999666333,971,NULL,'2010-10-27',NULL,NULL,NULL,'Pepe Humano'),(14,'es',1,60,'Academia De Baile Manolo Castelló','123213499','Palma de Mallorca','Soller - Bajo - Sontilo Sonpax','07120','39.576380964948505','2.6518289744853973',971234456,999666333,971321456,NULL,'2010-12-03',NULL,'admin','2010-12-03','Jose Baile'),(15,'es',7,96,'Consultora S.A.','123213499','Palma de Mallorca','Calle Enrique Alzamora, 1 - 4º','07011',NULL,NULL,971234456,0,971321456,NULL,'2010-11-03',NULL,NULL,NULL,'Pedro Consultor'),(16,'es',29,98,'Cursos CCC','48756846H','Palma de Mallorca','C/ Calle nº0','07120','','',971234456,999666333,971321456,NULL,'2010-12-03',NULL,'admin','2010-12-03','Juan Gomez'),(17,'es',7,132,'Open English','43135621H','Palma','Gremi Fusters 32','07004','39.57433836125881','2.6462607085704803',971758585,999666333,971910008,NULL,'2010-12-03',NULL,'admin','2010-12-03','Michael Moore');
/*!40000 ALTER TABLE `tblEmpresa` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblEquipamiento`
--

DROP TABLE IF EXISTS `tblEquipamiento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblEquipamiento` (
  `idEquipamiento` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idEquipamiento`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblEquipamiento`
--

LOCK TABLES `tblEquipamiento` WRITE;
/*!40000 ALTER TABLE `tblEquipamiento` DISABLE KEYS */;
INSERT INTO `tblEquipamiento` VALUES (2,'Proyector','proyector');
/*!40000 ALTER TABLE `tblEquipamiento` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblEstadoCivil`
--

DROP TABLE IF EXISTS `tblEstadoCivil`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblEstadoCivil` (
  `idEstadoCivil` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) default NULL,
  PRIMARY KEY  (`idEstadoCivil`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblEstadoCivil`
--

LOCK TABLES `tblEstadoCivil` WRITE;
/*!40000 ALTER TABLE `tblEstadoCivil` DISABLE KEYS */;
INSERT INTO `tblEstadoCivil` VALUES (1,'Casado/a'),(2,'Soltero/a'),(3,'Divorciado/a');
/*!40000 ALTER TABLE `tblEstadoCivil` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblEstadoLaboral`
--

DROP TABLE IF EXISTS `tblEstadoLaboral`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblEstadoLaboral` (
  `idEstadoLaboral` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) NOT NULL,
  PRIMARY KEY  (`idEstadoLaboral`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8 COMMENT='Empleado, autónomo, parado, etc.';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblEstadoLaboral`
--

LOCK TABLES `tblEstadoLaboral` WRITE;
/*!40000 ALTER TABLE `tblEstadoLaboral` DISABLE KEYS */;
INSERT INTO `tblEstadoLaboral` VALUES (1,'Ocupado'),(2,'Desocupado'),(4,'Situación de cuidador no profesional (CPN)');
/*!40000 ALTER TABLE `tblEstadoLaboral` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblEstadoPlan`
--

DROP TABLE IF EXISTS `tblEstadoPlan`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblEstadoPlan` (
  `idEstadoPlan` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idEstadoPlan`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblEstadoPlan`
--

LOCK TABLES `tblEstadoPlan` WRITE;
/*!40000 ALTER TABLE `tblEstadoPlan` DISABLE KEYS */;
INSERT INTO `tblEstadoPlan` VALUES (1,'Pendiente','El plan aun no ha sido aprobado'),(2,'Aprobado','El plan ha sido aprobado'),(3,'Denegado','El plan ha sido denegado');
/*!40000 ALTER TABLE `tblEstadoPlan` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblEstudio`
--

DROP TABLE IF EXISTS `tblEstudio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblEstudio` (
  `idEstudio` int(11) NOT NULL auto_increment,
  `vNombre` varchar(100) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idEstudio`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblEstudio`
--

LOCK TABLES `tblEstudio` WRITE;
/*!40000 ALTER TABLE `tblEstudio` DISABLE KEYS */;
INSERT INTO `tblEstudio` VALUES (1,'Sin Estudios',NULL),(2,'ESO / Graduado Escolar',NULL),(3,'Bachiller',NULL),(5,'Técnico FP Grado Superior / FPII',NULL),(6,'Diplomado (Educación Univercitaria de primer ciclo)','Diplomado. 2'),(7,'Doctor',NULL);
/*!40000 ALTER TABLE `tblEstudio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblHorario`
--

DROP TABLE IF EXISTS `tblHorario`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblHorario` (
  `idHorario` int(11) NOT NULL auto_increment,
  `fkCurso` int(11) NOT NULL,
  `dDia` date NOT NULL,
  `iDesde` time NOT NULL,
  `iHasta` time NOT NULL,
  `iSesion` int(4) default '0',
  `iHoras` time NOT NULL default '00:00:00',
  PRIMARY KEY  (`idHorario`),
  KEY `fk_tblHorario_tblCurso1` (`fkCurso`),
  KEY `tbl_Horario_fkCurso` (`fkCurso`),
  CONSTRAINT `tbl_Horario_fkCurso` FOREIGN KEY (`fkCurso`) REFERENCES `tblCurso` (`idCurso`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=783 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblMaterialCurso`
--

DROP TABLE IF EXISTS `tblMaterialCurso`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblMaterialCurso` (
  `idMaterialCurso` int(11) NOT NULL,
  `fkCurso` int(11) NOT NULL,
  `vNombre` varchar(255) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  `iCantidad` int(11) default '1',
  `ePrecio` decimal(9,2) default NULL,
  PRIMARY KEY  (`idMaterialCurso`),
  KEY `fk_tblMaterialCurso_tblCurso1` (`fkCurso`),
  CONSTRAINT `fk_tblMaterialCurso_tblCurso1` FOREIGN KEY (`fkCurso`) REFERENCES `tblCurso` (`idCurso`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Material Docente	';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblMaterialCurso`
--

LOCK TABLES `tblMaterialCurso` WRITE;
/*!40000 ALTER TABLE `tblMaterialCurso` DISABLE KEYS */;
/*!40000 ALTER TABLE `tblMaterialCurso` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblModalidad`
--

DROP TABLE IF EXISTS `tblModalidad`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblModalidad` (
  `idModalidad` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  `ePrecioHora` decimal(9,2) default NULL,
  PRIMARY KEY  (`idModalidad`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblModalidad`
--

LOCK TABLES `tblModalidad` WRITE;
/*!40000 ALTER TABLE `tblModalidad` DISABLE KEYS */;
INSERT INTO `tblModalidad` VALUES (1,'Presencial',NULL,NULL),(2,'Teleformación',NULL,NULL),(3,'Mixta','Desc',NULL),(4,'On line',NULL,NULL);
/*!40000 ALTER TABLE `tblModalidad` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblNivelEstudios`
--

DROP TABLE IF EXISTS `tblNivelEstudios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblNivelEstudios` (
  `idNivelEstudios` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idNivelEstudios`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblNivelEstudios`
--

LOCK TABLES `tblNivelEstudios` WRITE;
/*!40000 ALTER TABLE `tblNivelEstudios` DISABLE KEYS */;
INSERT INTO `tblNivelEstudios` VALUES (1,'EGB',NULL),(2,'ESO',NULL),(3,'Universidad',NULL);
/*!40000 ALTER TABLE `tblNivelEstudios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblNotificacion`
--

DROP TABLE IF EXISTS `tblNotificacion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblNotificacion` (
  `idNotificacion` int(11) NOT NULL auto_increment,
  `vAsunto` varchar(100) NOT NULL,
  `vMensaje` text NOT NULL,
  PRIMARY KEY  (`idNotificacion`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblNotificacion`
--

LOCK TABLES `tblNotificacion` WRITE;
/*!40000 ALTER TABLE `tblNotificacion` DISABLE KEYS */;
/*!40000 ALTER TABLE `tblNotificacion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblPais`
--

DROP TABLE IF EXISTS `tblPais`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblPais` (
  `vIso` varchar(2) character set latin1 NOT NULL,
  `vNombre_es` varchar(100) character set latin1 NOT NULL,
  `vNombre_ca` varchar(100) character set latin1 default NULL,
  `vNombre_en` varchar(100) default NULL,
  PRIMARY KEY  (`vIso`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblPais`
--

LOCK TABLES `tblPais` WRITE;
/*!40000 ALTER TABLE `tblPais` DISABLE KEYS */;
INSERT INTO `tblPais` VALUES ('ad','Andorra',NULL,NULL),('ae','Emiratos Árabes Unidos',NULL,NULL),('af','Afganistán',NULL,NULL),('ag','Antigua y Barbuda',NULL,NULL),('ai','Anguila',NULL,NULL),('al','Albania',NULL,NULL),('am','Armenia',NULL,NULL),('an','Antillas Holandesas',NULL,NULL),('ao','Angola',NULL,NULL),('aq','Antártica',NULL,NULL),('ar','Argentina','Argentina','Argentina'),('as','Samoa Americana',NULL,NULL),('at','Austria',NULL,NULL),('au','Australia',NULL,NULL),('aw','Aruba',NULL,NULL),('az','Azerbaidjan',NULL,NULL),('ba','Bosnia-Herzegovina',NULL,NULL),('bb','Barbados',NULL,NULL),('bd','Bangladesh',NULL,NULL),('be','Bélgica',NULL,NULL),('bf','Burkina Faso',NULL,NULL),('bg','Bulgaria',NULL,NULL),('bh','Bahrain',NULL,NULL),('bi','Burundi',NULL,NULL),('bj','Benin',NULL,NULL),('bm','Bermuda',NULL,NULL),('bn','Brunei Darussalam',NULL,NULL),('bo','Bolivia',NULL,NULL),('br','Brasil',NULL,NULL),('bs','Bahamas',NULL,NULL),('bt','Bhutan',NULL,NULL),('bv','Isla Bouvet',NULL,NULL),('bw','Botswana',NULL,NULL),('by','Bielorusia',NULL,NULL),('bz','Belice',NULL,NULL),('ca','Canadá',NULL,NULL),('cc','Isla Cocos (Keeling Islands)',NULL,NULL),('cd','República Democratica del Congo',NULL,NULL),('cf','República Central Africana',NULL,NULL),('cg','Congo',NULL,NULL),('ch','Suiza',NULL,NULL),('ci','Costa Marfil',NULL,NULL),('ck','Islas Cook',NULL,NULL),('cl','Chile',NULL,NULL),('cm','Camerún',NULL,NULL),('cn','China',NULL,NULL),('co','Colombia',NULL,NULL),('cr','Costa Rica',NULL,NULL),('cs','República Checa y Eslovakia',NULL,NULL),('cu','Cuba',NULL,NULL),('cv','Cabe Verde',NULL,NULL),('cx','Islas Christmas',NULL,NULL),('cy','Chipre',NULL,NULL),('cz','República Checa',NULL,NULL),('de','Alemania',NULL,NULL),('dj','Djibouti',NULL,NULL),('dk','Dinamarca',NULL,NULL),('dm','Dominica',NULL,NULL),('do','República Dominicana',NULL,NULL),('dz','Argelia',NULL,NULL),('ec','Ecuador',NULL,NULL),('ee','Estonia',NULL,NULL),('eg','Egypto',NULL,NULL),('eh','Sáhara Occidental',NULL,NULL),('er','Eritrea',NULL,NULL),('es','España','Espanya','Spain'),('et','Etiopía',NULL,NULL),('fi','Finlandia',NULL,NULL),('fj','Fiji',NULL,NULL),('fk','Falkland Islands (Islas Malvinas)',NULL,NULL),('fm','Micronesia',NULL,NULL),('fo','Islas Faroe',NULL,NULL),('fr','Francia',NULL,NULL),('ga','Gabón',NULL,NULL),('gd','Granada',NULL,NULL),('ge','Georgia',NULL,NULL),('gf','Guyana Francesa',NULL,NULL),('gg','Guernsey',NULL,NULL),('gh','Ghana',NULL,NULL),('gl','Groenlandia',NULL,NULL),('gm','Gambia',NULL,NULL),('gn','Guinea',NULL,NULL),('gp','Guadelupe (Francesa)',NULL,NULL),('gq','Guinea Ecuatorial',NULL,NULL),('gr','Grecia',NULL,NULL),('gs','Islas S. Georgia y S. Sandwich',NULL,NULL),('gt','Guatemala',NULL,NULL),('gu','Guam (USA)',NULL,NULL),('gw','Guinea Bissau',NULL,NULL),('gy','Guyana',NULL,NULL),('hk','Hong Kong',NULL,NULL),('hm','Islas Heard y McDonald',NULL,NULL),('hn','Honduras',NULL,NULL),('hr','Croacia',NULL,NULL),('ht','Haití',NULL,NULL),('hu','Hungría',NULL,NULL),('id','Indonesia',NULL,NULL),('ie','Irlanda',NULL,NULL),('il','Israel',NULL,NULL),('im','Isla de Man',NULL,NULL),('in','India',NULL,NULL),('io','Territorio Británico del Oceano Índico',NULL,NULL),('iq','Iraq',NULL,NULL),('ir','Irán',NULL,NULL),('is','Islandia',NULL,NULL),('it','Italia',NULL,NULL),('je','Jersey',NULL,NULL),('jm','Jamaica',NULL,NULL),('jo','Jordania',NULL,NULL),('jp','Japón',NULL,NULL),('ke','Kenya',NULL,NULL),('kg','Kyrgyzstan',NULL,NULL),('kh','Camboya',NULL,NULL),('ki','Kiribati',NULL,NULL),('km','Comoras',NULL,NULL),('kn','San Cristóbal y Nieves',NULL,NULL),('kp','Corea del norte',NULL,NULL),('kr','Corea del sur',NULL,NULL),('kw','Kuwait',NULL,NULL),('ky','Cayman Islands',NULL,NULL),('kz','Kazakhstan',NULL,NULL),('la','Laos',NULL,NULL),('lb','Líbano',NULL,NULL),('lc','Santa Lucía',NULL,NULL),('li','Liechtenstein',NULL,NULL),('lk','Sri Lanka',NULL,NULL),('lr','Liberia',NULL,NULL),('ls','Lesotho',NULL,NULL),('lt','Lituania',NULL,NULL),('lu','Luxemburgo',NULL,NULL),('lv','Letonia',NULL,NULL),('ly','Libia',NULL,NULL),('ma','Marruecos',NULL,NULL),('mc','Mónaco',NULL,NULL),('md','Moldavia',NULL,NULL),('me','Montenegro',NULL,NULL),('mg','Madagascar',NULL,NULL),('mh','Islas Marshall',NULL,NULL),('mk','Macedonia',NULL,NULL),('ml','Mali',NULL,NULL),('mm','Myanmar',NULL,NULL),('mn','Mongolia',NULL,NULL),('mo','Macao',NULL,NULL),('mp','Northern Mariana Islands',NULL,NULL),('mq','Martinica (Francesa)',NULL,NULL),('mr','Mauritania',NULL,NULL),('ms','Montserrat',NULL,NULL),('mt','Malta',NULL,NULL),('mu','Mauricia',NULL,NULL),('mv','Maldivas',NULL,NULL),('mw','Malawi',NULL,NULL),('mx','México',NULL,NULL),('my','Malasia',NULL,NULL),('mz','Mozambique',NULL,NULL),('na','Namibia',NULL,NULL),('nc','Nueva Caledonia (Francesa)',NULL,NULL),('ne','Niger',NULL,NULL),('nf','Norfolk Island',NULL,NULL),('ng','Nigeria',NULL,NULL),('ni','Nicaragua',NULL,NULL),('nl','Holanda',NULL,NULL),('no','Noruega',NULL,NULL),('np','Nepal',NULL,NULL),('nr','Nauru',NULL,NULL),('nu','Niue',NULL,NULL),('nz','Nueva Zelanda',NULL,NULL),('om','Omán',NULL,NULL),('pa','Panamá',NULL,NULL),('pe','Perú',NULL,NULL),('pf','Polinesia (Francesa)',NULL,NULL),('pg','Papua Nueva Guinea',NULL,NULL),('ph','Filipinas',NULL,NULL),('pk','Pakistán',NULL,NULL),('pl','Polonia',NULL,NULL),('pm','Saint Pierre y Miquelon',NULL,NULL),('pn','Islas Pitcairn',NULL,NULL),('pr','Puerto Rico',NULL,NULL),('pt','Portugal',NULL,NULL),('pw','Palau',NULL,NULL),('py','Paraguay',NULL,NULL),('qa','Qatar',NULL,NULL),('re','Reunión (Francesa)',NULL,NULL),('ro','Rumanía',NULL,NULL),('rs','Serbia',NULL,NULL),('ru','Rusia',NULL,NULL),('rw','Rwanda',NULL,NULL),('sa','Arabia Saudita',NULL,NULL),('sb','Islas Salomón',NULL,NULL),('sc','Seychelles',NULL,NULL),('sd','Sudán',NULL,NULL),('se','Suecia',NULL,NULL),('sg','Singapore',NULL,NULL),('sh','Santa Helena',NULL,NULL),('si','Eslovenia',NULL,NULL),('sj','Islas Svalbard y Jan Mayen',NULL,NULL),('sk','República Eslovaca',NULL,NULL),('sl','Sierra Leona',NULL,NULL),('sm','San Marino',NULL,NULL),('sn','Senegal',NULL,NULL),('so','Somalia',NULL,NULL),('sr','Suriname',NULL,NULL),('st','Sao Tomé y Príncipe',NULL,NULL),('sv','El Salvador',NULL,NULL),('sy','Siria',NULL,NULL),('sz','Swaziland',NULL,NULL),('tc','Islas Turcos y Caicos',NULL,NULL),('td','Chad',NULL,NULL),('tf','Territorios Franceses de Sur',NULL,NULL),('tg','Togo',NULL,NULL),('th','Tailandia',NULL,NULL),('tj','Tadjikistán',NULL,NULL),('tk','Tokelau',NULL,NULL),('tm','Turkmenia',NULL,NULL),('tn','Túnez',NULL,NULL),('to','Tonga',NULL,NULL),('tp','Timor del Este',NULL,NULL),('tr','Turquía',NULL,NULL),('tt','Trinidad y Tobago',NULL,NULL),('tv','Tuvalu',NULL,NULL),('tw','Taiwán',NULL,NULL),('tz','Tanzania',NULL,NULL),('ua','Ucrania',NULL,NULL),('ug','Uganda',NULL,NULL),('uk','Reino Unido',NULL,NULL),('um','USA Isla Menores',NULL,NULL),('us','Estados Unidos',NULL,NULL),('uy','Uruguay',NULL,NULL),('uz','Uzbekistán',NULL,NULL),('va','Vaticano',NULL,NULL),('vc','San Vicente y Granadinas',NULL,NULL),('ve','Venezuela',NULL,NULL),('vg','Islas Vírgenes (Reino Unido)',NULL,NULL),('vi','Islas Vírgenes (USA)',NULL,NULL),('vn','Vietnam',NULL,NULL),('vu','Vanuatu',NULL,NULL),('wf','Islas Wallis y Futuna',NULL,NULL),('ws','Samoa',NULL,NULL),('xx','Nicolandia',NULL,NULL),('ye','Yemen',NULL,NULL),('yt','Mayotte',NULL,NULL),('za','África del Sur',NULL,NULL),('zm','Zambia',NULL,NULL),('zr','Zaire',NULL,NULL),('zw','Zimbabwe',NULL,NULL);
/*!40000 ALTER TABLE `tblPais` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblPersona`
--

DROP TABLE IF EXISTS `tblPersona`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblPersona` (
  `idPersona` int(11) NOT NULL auto_increment,
  `fkUsuario` int(11) NOT NULL,
  `fkPais` varchar(2) character set latin1 NOT NULL,
  `fkProvincia` int(11) default NULL,
  `fkTipoIdentificacion` int(11) NOT NULL,
  `fkEstadoCivil` int(11) NOT NULL,
  `fkEstadoLaboral` int(11) NOT NULL,
  `fkNivelEstudios` int(11) NOT NULL,
  `vNombre` varchar(45) NOT NULL,
  `vPrimerApellido` varchar(45) NOT NULL,
  `vSegundoApellido` varchar(45) default NULL,
  `vSexo` varchar(45) default NULL,
  `vPoblacion` varchar(100) default NULL,
  `vCp` varchar(45) default NULL,
  `vNumeroIdentificacion` varchar(20) NOT NULL,
  `vNumeroSS` varchar(45) default NULL,
  `vDireccion` varchar(255) default NULL,
  `vTelefono` varchar(45) default NULL,
  `vMovil` varchar(45) default NULL,
  `bActiva` tinyint(1) default '0',
  `dAlta` date NOT NULL,
  `dNacimiento` date NOT NULL,
  `bDiscapacidad` int(1) default '0',
  `vObservaciones` varchar(1000) default NULL,
  `dBaja` date default NULL,
  `fkCobros` int(11) default NULL COMMENT 'Campo para estado laboral "ocupado"',
  `dAntiguedadParo` date default NULL COMMENT 'Campo para estado laboral "desocupado"',
  `vTrabajoParo` varchar(45) default NULL COMMENT 'Campo para estado laboral "desocupado"',
  `vSectorEmpresaActual` varchar(100) default NULL COMMENT 'Campo para estado laboral "ocupado"',
  `fkCategoriaEmpleo` int(11) default NULL,
  `bMas250Trabajadores` int(1) default NULL COMMENT 'Campo para estado laboral "ocupado"',
  `vRazonSocialEmpresaActual` varchar(100) default NULL COMMENT 'Campo para estado laboral "ocupado"',
  `vCifEmpresaActual` varchar(20) default NULL COMMENT 'Campo para estado laboral "ocupado"',
  `vDomicilioCentroTrabajo` varchar(100) default NULL COMMENT 'Campo para estado laboral "ocupado"',
  `vLocalidadCentroTrabajo` varchar(100) default NULL COMMENT 'Campo para estado laboral "ocupado"',
  `vCpCentroTrabajo` varchar(10) default NULL COMMENT 'Campo para estado laboral "ocupado"',
  `mod_user` varchar(45) default NULL,
  `last_modified` date default NULL,
  PRIMARY KEY  (`idPersona`),
  KEY `fk_tblPersona_tblPais1` (`fkPais`),
  KEY `fk_tblPersona_tblUsuario1` (`fkUsuario`),
  KEY `fk_tblPersona_tblTipoDocumento1` (`fkTipoIdentificacion`),
  KEY `fk_tblPersona_tblEstadoCivil1` (`fkEstadoCivil`),
  KEY `fk_tblPersona_tblEstadoLaboral1` (`fkEstadoLaboral`),
  KEY `fk_tblPersona_tblNivelEstudios1` (`fkNivelEstudios`),
  KEY `fk_tblPersona_tblProvincia1` (`fkProvincia`),
  KEY `fk_tblPersona_tblCobros1` (`fkCobros`),
  KEY `fk_tblPersona_tblCategoriaEmpleo` (`fkCategoriaEmpleo`),
  CONSTRAINT `fk_tblPersona_tblCategoriaEmpleo` FOREIGN KEY (`fkCategoriaEmpleo`) REFERENCES `tblCategoriaEmpleo` (`idCategoriaEmpleo`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblCobros1` FOREIGN KEY (`fkCobros`) REFERENCES `tblCobroParo` (`idCobroParo`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblEstadoCivil1` FOREIGN KEY (`fkEstadoCivil`) REFERENCES `tblEstadoCivil` (`idEstadoCivil`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblEstadoLaboral1` FOREIGN KEY (`fkEstadoLaboral`) REFERENCES `tblEstadoLaboral` (`idEstadoLaboral`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblNivelEstudios1` FOREIGN KEY (`fkNivelEstudios`) REFERENCES `tblNivelEstudios` (`idNivelEstudios`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblPais1` FOREIGN KEY (`fkPais`) REFERENCES `tblPais` (`vIso`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblProvincia1` FOREIGN KEY (`fkProvincia`) REFERENCES `tblProvincia` (`idProvincia`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblTipoDocumento1` FOREIGN KEY (`fkTipoIdentificacion`) REFERENCES `tblTipoIdentificacion` (`idTipoIdentificacion`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblUsuario1` FOREIGN KEY (`fkUsuario`) REFERENCES `tblUsuario` (`idUsuario`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=67 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblPlan`
--

DROP TABLE IF EXISTS `tblPlan`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblPlan` (
  `idPlan` int(11) NOT NULL auto_increment,
  `fkTipoPlan` int(11) NOT NULL,
  `fkConvocatoria` int(11) NOT NULL,
  `fkEmpresaConsultora` int(11) NOT NULL,
  `fkEmpresaPropietaria` int(11) NOT NULL,
  `fkEstadoPlan` int(11) NOT NULL,
  `fkSector` int(11) NOT NULL,
  `vNumeroExpediente` varchar(45) NOT NULL,
  `vNombre` varchar(45) default NULL,
  `vDescripcion` varchar(1000) default NULL,
  `ePresupuestoAsignado` decimal(9,2) default NULL,
  `mod_user` varchar(45) default NULL,
  `last_modified` date default NULL,
  PRIMARY KEY  (`idPlan`),
  KEY `fk_tblPlan_tblTipoPlan1` (`fkTipoPlan`),
  KEY `fk_tblPlan_tblConvocatoria1` (`fkConvocatoria`),
  KEY `fk_tblPlan_tblEmpresa1` (`fkEmpresaConsultora`),
  KEY `fk_tblPlan_tblEstadoPlan1` (`fkEstadoPlan`),
  KEY `fk_tblPlan_tblEmpresa2` (`fkEmpresaPropietaria`),
  KEY `fk_tblPlan_tblSector1` (`fkSector`),
  CONSTRAINT `fk_tblPlan_tblConvocatoria1` FOREIGN KEY (`fkConvocatoria`) REFERENCES `tblConvocatoria` (`idConvocatoria`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPlan_tblEmpresa1` FOREIGN KEY (`fkEmpresaConsultora`) REFERENCES `tblEmpresa` (`idEmpresa`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPlan_tblEmpresa2` FOREIGN KEY (`fkEmpresaPropietaria`) REFERENCES `tblEmpresa` (`idEmpresa`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPlan_tblEstadoPlan1` FOREIGN KEY (`fkEstadoPlan`) REFERENCES `tblEstadoPlan` (`idEstadoPlan`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPlan_tblSector1` FOREIGN KEY (`fkSector`) REFERENCES `tblSector` (`idSector`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPlan_tblTipoPlan1` FOREIGN KEY (`fkTipoPlan`) REFERENCES `tblTipoPlan` (`idTipoPlan`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblProvincia`
--

DROP TABLE IF EXISTS `tblProvincia`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblProvincia` (
  `idProvincia` int(11) NOT NULL auto_increment,
  `vNombre_es` varchar(100) character set latin1 NOT NULL,
  `vNombre_ca` varchar(100) character set latin1 default NULL,
  `vNombre_en` varchar(100) character set latin1 default NULL,
  PRIMARY KEY  (`idProvincia`)
) ENGINE=InnoDB AUTO_INCREMENT=53 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblProvincia`
--

LOCK TABLES `tblProvincia` WRITE;
/*!40000 ALTER TABLE `tblProvincia` DISABLE KEYS */;
INSERT INTO `tblProvincia` VALUES (1,'Araba','Araba','Araba'),(2,'Albacete','Albacete','Albacete'),(3,'Alacant',NULL,NULL),(4,'Almería',NULL,NULL),(5,'Ávila',NULL,NULL),(6,'Badajoz',NULL,NULL),(7,'Balears',NULL,NULL),(8,'Barcelona',NULL,NULL),(9,'Burgos',NULL,NULL),(10,'Cáceres',NULL,NULL),(11,'Cádiz',NULL,NULL),(12,'Castellón de la Plana',NULL,NULL),(13,'Ciudad Real',NULL,NULL),(14,'Córdoba',NULL,NULL),(15,'A Coruña',NULL,NULL),(16,'Cuenca',NULL,NULL),(17,'Girona',NULL,NULL),(18,'Granada',NULL,NULL),(19,'Guadalajara',NULL,NULL),(20,'Gipuzkoa',NULL,NULL),(21,'Huelva',NULL,NULL),(22,'Huesca',NULL,NULL),(23,'Jaén',NULL,NULL),(24,'León',NULL,NULL),(25,'Lleida',NULL,NULL),(26,'La Rioja',NULL,NULL),(27,'Lugo',NULL,NULL),(28,'Madrid',NULL,NULL),(29,'Málaga',NULL,NULL),(30,'Murcia',NULL,NULL),(31,'Navarra',NULL,NULL),(32,'Ourense',NULL,NULL),(33,'Asturies',NULL,NULL),(34,'Palencia',NULL,NULL),(35,'Las Palmas',NULL,NULL),(36,'Pontevedra',NULL,NULL),(37,'Salamanca',NULL,NULL),(38,'S.C.Tenerife',NULL,NULL),(39,'Cantabria',NULL,NULL),(40,'Segovia',NULL,NULL),(41,'Sevilla',NULL,NULL),(42,'Soria',NULL,NULL),(43,'Tarragona',NULL,NULL),(44,'Teruel',NULL,NULL),(45,'Toledo',NULL,NULL),(46,'Valencia',NULL,NULL),(47,'Valladolid',NULL,NULL),(48,'Bizkaia',NULL,NULL),(49,'Zamora',NULL,NULL),(50,'Zaragoza',NULL,NULL),(51,'Ceuta',NULL,NULL),(52,'Melilla',NULL,NULL);
/*!40000 ALTER TABLE `tblProvincia` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblRequisito`
--

DROP TABLE IF EXISTS `tblRequisito`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblRequisito` (
  `idRequisito` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idRequisito`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblRequisito`
--

LOCK TABLES `tblRequisito` WRITE;
/*!40000 ALTER TABLE `tblRequisito` DISABLE KEYS */;
INSERT INTO `tblRequisito` VALUES (1,'Documentación obligatoria',NULL),(2,'Memoria pedagógica',NULL),(3,'Preferentemente parados','Parados'),(4,'Preferentemente ocupados',NULL),(5,'Un requisito','Un requisito en particular.');
/*!40000 ALTER TABLE `tblRequisito` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblRol`
--

DROP TABLE IF EXISTS `tblRol`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblRol` (
  `idRol` int(11) NOT NULL auto_increment,
  `vNombre` varchar(45) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idRol`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblRol`
--

LOCK TABLES `tblRol` WRITE;
/*!40000 ALTER TABLE `tblRol` DISABLE KEYS */;
INSERT INTO `tblRol` VALUES (1,'Administrador','Administrador del Sistema'),(2,'Propietario','Propietario de Plan'),(3,'Consultora','Consultora - Gestora'),(4,'Academia','Academia donde se imparten los cursos'),(5,'Profesor','Profesor que imparte los cursos'),(6,'Alumno','Alumno de los cursos'),(7,'Usuario','Usuario de la aplicación'),(8,'Invitado','Invitado');
/*!40000 ALTER TABLE `tblRol` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblSector`
--

DROP TABLE IF EXISTS `tblSector`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblSector` (
  `idSector` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idSector`)
) ENGINE=InnoDB AUTO_INCREMENT=20 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblTipoConvocatoria`
--

DROP TABLE IF EXISTS `tblTipoConvocatoria`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblTipoConvocatoria` (
  `idTipoConvocatoria` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) default NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idTipoConvocatoria`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblTipoIdentificacion`
--

DROP TABLE IF EXISTS `tblTipoIdentificacion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblTipoIdentificacion` (
  `idTipoIdentificacion` int(11) NOT NULL auto_increment,
  `vNombre` varchar(100) NOT NULL,
  PRIMARY KEY  (`idTipoIdentificacion`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblTipoIdentificacion`
--

LOCK TABLES `tblTipoIdentificacion` WRITE;
/*!40000 ALTER TABLE `tblTipoIdentificacion` DISABLE KEYS */;
INSERT INTO `tblTipoIdentificacion` VALUES (1,'DNI'),(2,'NIE'),(3,'Pasaporte');
/*!40000 ALTER TABLE `tblTipoIdentificacion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblTipoPlan`
--

DROP TABLE IF EXISTS `tblTipoPlan`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblTipoPlan` (
  `idTipoPlan` int(11) NOT NULL auto_increment,
  `vNombre` varchar(45) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idTipoPlan`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblTipoPlan`
--

LOCK TABLES `tblTipoPlan` WRITE;
/*!40000 ALTER TABLE `tblTipoPlan` DISABLE KEYS */;
INSERT INTO `tblTipoPlan` VALUES (1,'Sectorial',NULL),(2,'Intersectorial',NULL);
/*!40000 ALTER TABLE `tblTipoPlan` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tblTutoria`
--

DROP TABLE IF EXISTS `tblTutoria`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblTutoria` (
  `idTutoria` int(11) NOT NULL auto_increment,
  `fkCurso` int(11) NOT NULL,
  `fkModalidad` int(11) NOT NULL,
  `fkTutor` int(11) NOT NULL,
  `iHoras` int(3) NOT NULL,
  `bLunes` tinyint(1) default '0',
  `bMartes` tinyint(1) default '0',
  `bMiercoles` tinyint(1) default '0',
  `bJueves` tinyint(1) default '0',
  `bViernes` tinyint(1) default '0',
  `bSabado` tinyint(1) default '0',
  `bDomingo` tinyint(1) default '0',
  `iDesdeManana` time default NULL,
  `iHastaManana` time default NULL,
  `iDesdeTarde` time default NULL,
  `iHastaTarde` time default NULL,
  PRIMARY KEY  (`idTutoria`),
  KEY `fk_tblTutoria_tblCurso` (`fkCurso`),
  KEY `fk_tblTutoria_tblModalidad` (`fkModalidad`),
  KEY `fk_tblTutoria_tblPersona` (`fkTutor`),
  CONSTRAINT `fk_tblTutoria_tblCurso` FOREIGN KEY (`fkCurso`) REFERENCES `tblCurso` (`idCurso`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblTutoria_tblModalidad` FOREIGN KEY (`fkModalidad`) REFERENCES `tblModalidad` (`idModalidad`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblTutoria_tblPersona` FOREIGN KEY (`fkTutor`) REFERENCES `tblPersona` (`idPersona`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblUsuario`
--

DROP TABLE IF EXISTS `tblUsuario`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblUsuario` (
  `idUsuario` int(11) NOT NULL auto_increment,
  `vNombre` varchar(50) character set latin1 NOT NULL,
  `vPassword` varchar(32) character set latin1 NOT NULL,
  `vEmail` varchar(45) NOT NULL,
  PRIMARY KEY  (`idUsuario`),
  KEY `idUsuario` (`idUsuario`)
) ENGINE=InnoDB AUTO_INCREMENT=147 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tblUsuario`
--

LOCK TABLES `tblUsuario` WRITE;
/*!40000 ALTER TABLE `tblUsuario` DISABLE KEYS */;
INSERT INTO `tblUsuario` VALUES (1,'admin','5be85bb62f6a70ae4cb776734251a459','no-mail@mail.com');
/*!40000 ALTER TABLE `tblUsuario` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trelCandidato`
--

DROP TABLE IF EXISTS `trelCandidato`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelCandidato` (
  `fkPersona` int(11) NOT NULL,
  `fkCurso` int(11) NOT NULL,
  `dAlta` date NOT NULL,
  PRIMARY KEY  (`fkCurso`,`fkPersona`),
  KEY `fk_trelCandidato_tblPersona1` (`fkPersona`),
  KEY `fk_trelCandidato_trelPlanCursoAula1` (`fkCurso`),
  CONSTRAINT `fk_trelCandidato_tblPersona1` FOREIGN KEY (`fkPersona`) REFERENCES `tblPersona` (`idPersona`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelCandidato_trelPlanCursoAula1` FOREIGN KEY (`fkCurso`) REFERENCES `tblCurso` (`idCurso`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trelDocumentoConvocatoria`
--

DROP TABLE IF EXISTS `trelDocumentoConvocatoria`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelDocumentoConvocatoria` (
  `fkConvocatoria` int(11) NOT NULL,
  `fkDocumento` int(11) NOT NULL,
  PRIMARY KEY  (`fkConvocatoria`,`fkDocumento`),
  KEY `fk_trelDocumentoConvocatoria_1` (`fkConvocatoria`),
  KEY `fk_trelDocumentoConvocatoria_2` (`fkDocumento`),
  CONSTRAINT `fk_trelDocumentoConvocatoria_1` FOREIGN KEY (`fkConvocatoria`) REFERENCES `tblConvocatoria` (`idConvocatoria`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelDocumentoConvocatoria_2` FOREIGN KEY (`fkDocumento`) REFERENCES `tblDocumento` (`idDocumento`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trelDocumentoCurso`
--

DROP TABLE IF EXISTS `trelDocumentoCurso`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelDocumentoCurso` (
  `fkCurso` int(11) NOT NULL,
  `fkDocumento` int(11) NOT NULL,
  PRIMARY KEY  (`fkCurso`,`fkDocumento`),
  KEY `fk_trelDocumentoCurso_tblDocumento1` (`fkDocumento`),
  KEY `fk_trelDocumentoCurso_tblCurso1` (`fkCurso`),
  CONSTRAINT `fk_trelDocumentoCurso_tblCurso1` FOREIGN KEY (`fkCurso`) REFERENCES `tblCurso` (`idCurso`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `fk_trelDocumentoCurso_tblDocumento1` FOREIGN KEY (`fkDocumento`) REFERENCES `tblDocumento` (`idDocumento`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Documentación del curso';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trelDocumentoCurso`
--

LOCK TABLES `trelDocumentoCurso` WRITE;
/*!40000 ALTER TABLE `trelDocumentoCurso` DISABLE KEYS */;
/*!40000 ALTER TABLE `trelDocumentoCurso` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trelEquipamientoAula`
--

DROP TABLE IF EXISTS `trelEquipamientoAula`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelEquipamientoAula` (
  `fkAula` int(11) NOT NULL,
  `fkEquipamiento` int(11) NOT NULL,
  `iCantidad` int(11) NOT NULL default '1',
  PRIMARY KEY  (`fkAula`,`fkEquipamiento`),
  KEY `fk_tblMaterialAula_tblAula1` (`fkAula`),
  KEY `fk_tblMaterialAula_tblMaterial1` (`fkEquipamiento`),
  CONSTRAINT `fk_tblMaterialAula_tblAula1` FOREIGN KEY (`fkAula`) REFERENCES `tblAula` (`idAula`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_tblMaterialAula_tblMaterial1` FOREIGN KEY (`fkEquipamiento`) REFERENCES `tblEquipamiento` (`idEquipamiento`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trelEquipamientoPlanCursoAula`
--

DROP TABLE IF EXISTS `trelEquipamientoPlanCursoAula`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelEquipamientoPlanCursoAula` (
  `idEquipamientoPlanCursoAula` int(11) NOT NULL auto_increment,
  `fkEquipamiento` int(11) NOT NULL,
  `fkCurso` int(11) NOT NULL,
  `iCantidad` int(11) NOT NULL default '1',
  `ePrecio` decimal(9,2) default NULL,
  PRIMARY KEY  (`idEquipamientoPlanCursoAula`),
  KEY `fk_trelMaterialPlanCursoAula_tblMaterial1` (`fkEquipamiento`),
  KEY `fk_trelMaterialPlanCursoAula_trelPlanCursoAula1` (`fkCurso`),
  CONSTRAINT `fk_trelMaterialPlanCursoAula_tblMaterial1` FOREIGN KEY (`fkEquipamiento`) REFERENCES `tblEquipamiento` (`idEquipamiento`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelMaterialPlanCursoAula_trelPlanCursoAula1` FOREIGN KEY (`fkCurso`) REFERENCES `tblCurso` (`idCurso`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='MATERIALES REQUERIDOS POR EL CURSO';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trelEstudioPersona`
--

DROP TABLE IF EXISTS `trelEstudioPersona`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelEstudioPersona` (
  `idEstudioPersona` int(11) NOT NULL auto_increment,
  `fkTipoEstudio` int(11) NOT NULL,
  `fkPersona` int(11) NOT NULL,
  `iAnyo` varchar(45) NOT NULL,
  PRIMARY KEY  (`idEstudioPersona`,`fkTipoEstudio`,`fkPersona`),
  KEY `fk_trelEstudioPersona_1` (`fkTipoEstudio`),
  KEY `fk_trelEstudioPersona_2` (`fkPersona`),
  CONSTRAINT `fk_trelEstudioPersona_1` FOREIGN KEY (`fkTipoEstudio`) REFERENCES `tblEstudio` (`idEstudio`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_trelEstudioPersona_2` FOREIGN KEY (`fkPersona`) REFERENCES `tblPersona` (`idPersona`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=34 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trelNotificacionDocumento`
--

DROP TABLE IF EXISTS `trelNotificacionDocumento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelNotificacionDocumento` (
  `fkNotificacion` int(11) NOT NULL,
  `fkDocumento` int(11) NOT NULL,
  PRIMARY KEY  (`fkNotificacion`,`fkDocumento`),
  KEY `fk_trelNotificacionDocumento_tblNotificacion1` (`fkNotificacion`),
  KEY `fk_trelNotificacionDocumento_tblDocumento1` (`fkDocumento`),
  CONSTRAINT `fk_trelNotificacionDocumento_tblDocumento1` FOREIGN KEY (`fkDocumento`) REFERENCES `tblDocumento` (`idDocumento`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelNotificacionDocumento_tblNotificacion1` FOREIGN KEY (`fkNotificacion`) REFERENCES `tblNotificacion` (`idNotificacion`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trelNotificacionDocumento`
--

LOCK TABLES `trelNotificacionDocumento` WRITE;
/*!40000 ALTER TABLE `trelNotificacionDocumento` DISABLE KEYS */;
/*!40000 ALTER TABLE `trelNotificacionDocumento` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trelNotificacionEmpresa`
--

DROP TABLE IF EXISTS `trelNotificacionEmpresa`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelNotificacionEmpresa` (
  `fkEmpresa` int(11) NOT NULL,
  `fkNotificacion` int(11) NOT NULL,
  PRIMARY KEY  (`fkEmpresa`,`fkNotificacion`),
  KEY `fk_trelNotificacionEmpresa_tblNotificacion1` (`fkNotificacion`),
  CONSTRAINT `fk_trelNotificacionEmpresa_tblEmpresa1` FOREIGN KEY (`fkEmpresa`) REFERENCES `tblEmpresa` (`idEmpresa`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelNotificacionEmpresa_tblNotificacion1` FOREIGN KEY (`fkNotificacion`) REFERENCES `tblNotificacion` (`idNotificacion`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trelNotificacionPersona`
--

DROP TABLE IF EXISTS `trelNotificacionPersona`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelNotificacionPersona` (
  `fkPersona` int(11) NOT NULL,
  `fkNotificacion` int(11) NOT NULL,
  PRIMARY KEY  (`fkPersona`,`fkNotificacion`),
  KEY `fk_trelNotificacionPersona_tblPersona1` (`fkPersona`),
  KEY `fk_trelNotificacionPersona_tblNotificacion1` (`fkNotificacion`),
  CONSTRAINT `fk_trelNotificacionPersona_tblNotificacion1` FOREIGN KEY (`fkNotificacion`) REFERENCES `tblNotificacion` (`idNotificacion`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelNotificacionPersona_tblPersona1` FOREIGN KEY (`fkPersona`) REFERENCES `tblPersona` (`idPersona`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trelPersonaCarnet`
--

DROP TABLE IF EXISTS `trelPersonaCarnet`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelPersonaCarnet` (
  `fkPersona` int(11) NOT NULL,
  `fkCarnet` int(11) NOT NULL,
  PRIMARY KEY  (`fkPersona`,`fkCarnet`),
  KEY `fk_trelPersonaCarnet_tblPersona1` (`fkPersona`),
  KEY `fk_trelPersonaCarnet_tblCarnetConducir1` (`fkCarnet`),
  CONSTRAINT `fk_trelPersonaCarnet_tblCarnetConducir1` FOREIGN KEY (`fkCarnet`) REFERENCES `tblCarnetConducir` (`idCarnetConducir`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelPersonaCarnet_tblPersona1` FOREIGN KEY (`fkPersona`) REFERENCES `tblPersona` (`idPersona`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trelPersonaCategoria`
--

DROP TABLE IF EXISTS `trelPersonaCategoria`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelPersonaCategoria` (
  `fkPersona` int(11) NOT NULL,
  `fkCategoria` int(11) NOT NULL,
  PRIMARY KEY  (`fkPersona`,`fkCategoria`),
  KEY `fk_trelPersonaCategoria_tblPersona1` (`fkPersona`),
  KEY `fk_trelPersonaCategoria_tblCategoria1` (`fkCategoria`),
  CONSTRAINT `fk_trelPersonaCategoria_tblCategoria1` FOREIGN KEY (`fkCategoria`) REFERENCES `tblCategoria` (`idCategoria`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelPersonaCategoria_tblPersona1` FOREIGN KEY (`fkPersona`) REFERENCES `tblPersona` (`idPersona`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Profesores, categorias en la que ejerce';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trelPrecandidato`
--

DROP TABLE IF EXISTS `trelPrecandidato`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelPrecandidato` (
  `fkPersona` int(11) NOT NULL,
  `fkCurso` int(11) NOT NULL,
  `dAlta` date NOT NULL,
  PRIMARY KEY  (`fkPersona`,`fkCurso`),
  KEY `fk_trelCandidato_tblPersona1` (`fkPersona`),
  KEY `fk_trelCandidato_trelPlanCursoAula1` (`fkCurso`),
  CONSTRAINT `fk_trelCandidato_tblPersona10` FOREIGN KEY (`fkPersona`) REFERENCES `tblPersona` (`idPersona`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelCandidato_trelPlanCursoAula10` FOREIGN KEY (`fkCurso`) REFERENCES `tblCurso` (`idCurso`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;


--
-- Table structure for table `trelProfesor`
--

DROP TABLE IF EXISTS `trelProfesor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelProfesor` (
  `fkPersona` int(11) NOT NULL,
  `fkCurso` int(11) NOT NULL,
  PRIMARY KEY  (`fkPersona`,`fkCurso`),
  KEY `fk_trelProfesor_tblPersona1` (`fkPersona`),
  KEY `fk_trelProfesor_trelPlanCursoAula1` (`fkCurso`),
  CONSTRAINT `fk_trelProfesor_tblPersona1` FOREIGN KEY (`fkPersona`) REFERENCES `tblPersona` (`idPersona`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelProfesor_trelPlanCursoAula1` FOREIGN KEY (`fkCurso`) REFERENCES `tblCurso` (`idCurso`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trelRequisitoConvocatoria`
--

DROP TABLE IF EXISTS `trelRequisitoConvocatoria`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelRequisitoConvocatoria` (
  `fkConvocatoria` int(11) NOT NULL,
  `fkRequisito` int(11) NOT NULL,
  PRIMARY KEY  (`fkConvocatoria`,`fkRequisito`),
  KEY `fk_trelRequisitoConvocatoria_tblConvocatoria1` (`fkConvocatoria`),
  KEY `fk_trelRequisitoConvocatoria_tblRequisito1` (`fkRequisito`),
  CONSTRAINT `fk_trelRequisitoConvocatoria_tblConvocatoria1` FOREIGN KEY (`fkConvocatoria`) REFERENCES `tblConvocatoria` (`idConvocatoria`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelRequisitoConvocatoria_tblRequisito1` FOREIGN KEY (`fkRequisito`) REFERENCES `tblRequisito` (`idRequisito`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trelRolUsuario`
--

DROP TABLE IF EXISTS `trelRolUsuario`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trelRolUsuario` (
  `fkUsuario` int(11) NOT NULL,
  `fkRol` int(11) NOT NULL,
  PRIMARY KEY  (`fkUsuario`,`fkRol`),
  KEY `fk_trelRolUsuario_tblUsuario1` (`fkUsuario`),
  KEY `fk_trelRolUsuario_tblRol1` (`fkRol`),
  CONSTRAINT `fk_trelRolUsuario_tblRol1` FOREIGN KEY (`fkRol`) REFERENCES `tblRol` (`idRol`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelRolUsuario_tblUsuario1` FOREIGN KEY (`fkUsuario`) REFERENCES `tblUsuario` (`idUsuario`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;


/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2011-01-07  8:48:47
