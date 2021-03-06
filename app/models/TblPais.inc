<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 09 de December de 2010 a las 08:48:53
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TblPaisSearch.inc' );
require_once( 'TblPaisPK.inc' );

/**
 * Objeto para acceder a la tabla tblPais.
 *
 * @package dataAccess
 */
class TblPais extends OwlGenericDO{

    /**
     * Atributo que representa el campo "vIso"
     * @var string
     */
    public $vIso;

    /**
     * Atributo que representa el campo "vNombre_es"
     * @var string
     */
    public $vNombreEs;

    /**
     * Atributo que representa el campo "vNombre_ca"
     * @var string
     */
    public $vNombreCa;

    /**
     * Atributo que representa el campo "vNombre_en"
     * @var string
     */
    public $vNombreEn;

    // Constructor

    /**
     * Constructor
     */
    public function __construct( $db, $data=null ){

        if( $data ){
            $this->_setData($data);
        }
        $this->_db = $db;

    }

    /**
     * Asigna los valores de los atributos del DO utilizando los valores de la variable $data.
     *
     * @param array $data
     */
    private function _setData( $data ){

        $this->_data = $data;
        $this->vIso = $data['vIso'];
        $this->vNombreEs = $data['vNombre_es'];
        $this->vNombreCa = $data['vNombre_ca'];
        $this->vNombreEn = $data['vNombre_en'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblPais segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblPaisSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblPais';
        $where = array();
        if( $tmp = $searchItem->vIso ){
            $where[] = "vIso='$tmp'";
        }
        if( $tmp = $searchItem->vNombreEs ){
            $where[] = "vNombre_es='$tmp'";
        }
        if( $tmp = $searchItem->vNombreCa ){
            $where[] = "vNombre_ca='$tmp'";
        }
        if( $tmp = $searchItem->vNombreEn ){
            $where[] = "vNombre_en='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblPais' );
}

    /**
     * Obtiene todas las filas de la tabla tblPais.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblPais';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblPais' );
    }

    /**
     * Obtiene el elemento de la tabla tblPais que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $vIso valor del campo 'vIso'.
     * @return TblPais
     */
    public static function findByPrimaryKey( $db, $vIso ){

       $db->executeQuery("SELECT * FROM tblPais WHERE vIso = '$vIso'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblPais');

    }

    /**
     * Obtiene el elemento de la tabla tblPais que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblPaisPK $pk Objeto de la clave primaria.
     * @return TblPais
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="vIso='".$pk->vIso."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblPais WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblPais');

    }

    /**
     * Actualiza una fila de la tabla tblPais.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vIso=' . ( ( ( $value = $this->vIso ) === null || !isset($this->vIso) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre_es=' . ( ( ( $value = $this->vNombreEs ) === null || !isset($this->vNombreEs) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre_ca=' . ( ( ( $value = $this->vNombreCa ) === null || !isset($this->vNombreCa) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre_en=' . ( ( ( $value = $this->vNombreEn ) === null || !isset($this->vNombreEn) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblPais SET $setStr WHERE vIso='".addslashes($this->_data['vIso'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblPais.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vIso';
        $attributes[] = 'vNombre_es';
        $attributes[] = 'vNombre_ca';
        $attributes[] = 'vNombre_en';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vIso ) === null || !isset($this->vIso) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombreEs ) === null || !isset($this->vNombreEs) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombreCa ) === null || !isset($this->vNombreCa) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombreEn ) === null || !isset($this->vNombreEn) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblPais($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->vIso );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblPais.
     */
    public function delete(){
        $where = array();
        $where[] = "vIso="."'".addslashes($this->vIso)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblPais WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'vIso'.
      *
      * @return string
      */
    public function getVIso(){
        return $this->vIso;
    }

    /**
      * Establece el valor del atributo 'vIso'.
      *
      * @param string Valor.
      */
    public function setVIso( $value ){

        $this->vIso = $value;

    }

    /**
      * Obtiene el valor del atributo 'vNombre_es'.
      *
      * @return string
      */
    public function getVNombreEs(){
        return $this->vNombreEs;
    }

    /**
      * Establece el valor del atributo 'vNombre_es'.
      *
      * @param string Valor.
      */
    public function setVNombreEs( $value ){

        $this->vNombreEs = $value;

    }

    /**
      * Obtiene el valor del atributo 'vNombre_ca'.
      *
      * @return string
      */
    public function getVNombreCa(){
        return $this->vNombreCa;
    }

    /**
      * Establece el valor del atributo 'vNombre_ca'.
      *
      * @param string Valor.
      */
    public function setVNombreCa( $value ){

        $this->vNombreCa = $value;

    }

    /**
      * Obtiene el valor del atributo 'vNombre_en'.
      *
      * @return string
      */
    public function getVNombreEn(){
        return $this->vNombreEn;
    }

    /**
      * Establece el valor del atributo 'vNombre_en'.
      *
      * @param string Valor.
      */
    public function setVNombreEn( $value ){

        $this->vNombreEn = $value;

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblAlumno'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblAlumnos( $orderBy='' ){

        include_once('TblAlumno.inc');
        return TblAlumno::findByTblPais( $this->_db, $this->vIso, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblAula'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblAulas( $orderBy='' ){

        include_once('TblAula.inc');
        return TblAula::findByTblPais( $this->_db, $this->vIso, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblCentro'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblCentros( $orderBy='' ){

        include_once('TblCentro.inc');
        return TblCentro::findByTblPais( $this->_db, $this->vIso, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblEmpresa'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblEmpresas( $orderBy='' ){

        include_once('TblEmpresa.inc');
        return TblEmpresa::findByTblPais( $this->_db, $this->vIso, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblPersona'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPersonas( $orderBy='' ){

        include_once('TblPersona.inc');
        return TblPersona::findByTblPais( $this->_db, $this->vIso, $orderBy );

    }

    // Métodos multi-idioma.

    /**
      * Obtiene el valor de la atributo 'vNombre' según el idioma activo.
      *
      * @return string
      * @see OwlGenericDO::setLang()
      */
    public function getVNombre(){

        $attribute = 'vNombre'.ucfirst($this->getLang());
        return $this->$attribute;

    }

    /**
      * Establece el valor del atributo 'vNombre' según el idioma activo.
      *
      * @param string $value Valor.
      * @see OwlGenericDO::setLang()
      */
    public function setVNombre( $value ){

        $attribute = 'vNombre'.ucfirst($this->getLang());
        $this->$attribute = $value;

    }
}
?>