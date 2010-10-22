<?php
/**
 * Este archivo ha sido generado con Ningen DoGen v.0.6
 * el 21 de October de 2010 a las 10:48:39
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/NingenConnection.inc');
require_once( 'dbase/NingenGenericDO.inc');
require_once( 'TblProvinciaSearch.inc' );
require_once( 'TblProvinciaPK.inc' );

/**
 * Objeto para acceder a la tabla tblProvincia.
 *
 * @package dataAccess
 */
class TblProvincia extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idProvincia"
     * @var integer
     */
    public $idProvincia;

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
        $this->idProvincia = $data['idProvincia'];
        $this->vNombreEs = $data['vNombre_es'];
        $this->vNombreCa = $data['vNombre_ca'];
        $this->vNombreEn = $data['vNombre_en'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblProvincia segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblProvinciaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblProvincia';
        $where = array();
        if( $tmp = $searchItem->idProvincia ){
            $where[] = "idProvincia='$tmp'";
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
        return NingenGenericDO::createCollection( $db, $sql, 'TblProvincia' );
}

    /**
     * Obtiene todas las filas de la tabla tblProvincia.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblProvincia';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblProvincia' );
    }

    /**
     * Obtiene el elemento de la tabla tblProvincia que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idProvincia valor del campo 'idProvincia'.
     * @return TblProvincia
     */
    public static function findByPrimaryKey( $db, $idProvincia ){

       $db->executeQuery("SELECT * FROM tblProvincia WHERE idProvincia = '$idProvincia'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TblProvincia');

    }

    /**
     * Obtiene el elemento de la tabla tblProvincia que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblProvinciaPK $pk Objeto de la clave primaria.
     * @return TblProvincia
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idProvincia='".$pk->idProvincia."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblProvincia WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TblProvincia');

    }

    /**
     * Actualiza una fila de la tabla tblProvincia.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre_es=' . ( ( ( $value = $this->vNombreEs ) === null || !isset($this->vNombreEs) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre_ca=' . ( ( ( $value = $this->vNombreCa ) === null || !isset($this->vNombreCa) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre_en=' . ( ( ( $value = $this->vNombreEn ) === null || !isset($this->vNombreEn) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblProvincia SET $setStr WHERE idProvincia='".addslashes($this->_data['idProvincia'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblProvincia.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vNombre_es';
        $attributes[] = 'vNombre_ca';
        $attributes[] = 'vNombre_en';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vNombreEs ) === null || !isset($this->vNombreEs) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombreCa ) === null || !isset($this->vNombreCa) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombreEn ) === null || !isset($this->vNombreEn) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblProvincia($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblProvincia.
     */
    public function delete(){
        $where = array();
        $where[] = "idProvincia="."'".addslashes($this->idProvincia)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblProvincia WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idProvincia'.
      *
      * @return integer
      */
    public function getIdProvincia(){
        return $this->idProvincia;
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
     * Obtiene todos los elementos relacionados de la tabla 'tblAula'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblAulas( $orderBy='' ){

        include_once('TblAula.inc');
        return TblAula::findByTblProvincia( $this->_db, $this->idProvincia, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblCentro'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblCentros( $orderBy='' ){

        include_once('TblCentro.inc');
        return TblCentro::findByTblProvincia( $this->_db, $this->idProvincia, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblEmpresa'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblEmpresas( $orderBy='' ){

        include_once('TblEmpresa.inc');
        return TblEmpresa::findByTblProvincia( $this->_db, $this->idProvincia, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblPersona'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPersonas( $orderBy='' ){

        include_once('TblPersona.inc');
        return TblPersona::findByTblProvincia( $this->_db, $this->idProvincia, $orderBy );

    }

    // Métodos multi-idioma.

    /**
      * Obtiene el valor de la atributo 'vNombre' según el idioma activo.
      *
      * @return string
      * @see NingenGenericDO::setLang()
      */
    public function getVNombre(){

        $attribute = 'vNombre'.ucfirst($this->getLang());
        return $this->$attribute;

    }

    /**
      * Establece el valor del atributo 'vNombre' según el idioma activo.
      *
      * @param string $value Valor.
      * @see NingenGenericDO::setLang()
      */
    public function setVNombre( $value ){

        $attribute = 'vNombre'.ucfirst($this->getLang());
        $this->$attribute = $value;

    }
}
?>