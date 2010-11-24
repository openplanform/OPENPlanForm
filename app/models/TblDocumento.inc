<?php
/**
 * Este archivo ha sido generado con Ningen DoGen v.0.6
 * el 04 de November de 2010 a las 14:57:40
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/NingenConnection.inc');
require_once( 'dbase/NingenGenericDO.inc');
require_once( 'TblDocumentoSearch.inc' );
require_once( 'TblDocumentoPK.inc' );

/**
 * Objeto para acceder a la tabla tblDocumento.
 *
 * @package dataAccess
 */
class TblDocumento extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idDocumento"
     * @var integer
     */
    public $idDocumento;

    /**
     * Atributo que representa el campo "vRealName"
     * @var string
     */
    public $vRealName;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

    /**
     * Atributo que representa el campo "vMime"
     * @var string
     */
    public $vMime;

    /**
     * Atributo que representa el campo "vTamano"
     * @var string
     */
    public $vTamano;

    /**
     * Atributo que representa el campo "vDescription"
     * @var string
     */
    public $vDescription;

    /**
     * Atributo que representa el campo "mod_user"
     * @var string
     */
    public $modUser;

    /**
     * Atributo que representa el campo "last_modified"
     * @var string
     */
    public $lastModified;

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
        $this->idDocumento = $data['idDocumento'];
        $this->vRealName = $data['vRealName'];
        $this->vNombre = $data['vNombre'];
        $this->vMime = $data['vMime'];
        $this->vTamano = $data['vTamano'];
        $this->vDescription = $data['vDescription'];
        $this->modUser = $data['mod_user'];
        $this->lastModified = $data['last_modified'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblDocumento segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblDocumentoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblDocumento';
        $where = array();
        if( $tmp = $searchItem->idDocumento ){
            $where[] = "idDocumento='$tmp'";
        }
        if( $tmp = $searchItem->vRealName ){
            $where[] = "vRealName='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->vMime ){
            $where[] = "vMime='$tmp'";
        }
        if( $tmp = $searchItem->vTamano ){
            $where[] = "vTamano='$tmp'";
        }
        if( $tmp = $searchItem->vDescription ){
            $where[] = "vDescription='$tmp'";
        }
        if( $tmp = $searchItem->modUser ){
            $where[] = "mod_user='$tmp'";
        }
        if( $tmp = $searchItem->lastModified ){
            $where[] = "last_modified='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return NingenGenericDO::createCollection( $db, $sql, 'TblDocumento' );
}

    /**
     * Obtiene todas las filas de la tabla tblDocumento.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblDocumento';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblDocumento' );
    }

    /**
     * Obtiene el elemento de la tabla tblDocumento que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idDocumento valor del campo 'idDocumento'.
     * @return TblDocumento
     */
    public static function findByPrimaryKey( $db, $idDocumento ){

       $db->executeQuery("SELECT * FROM tblDocumento WHERE idDocumento = '$idDocumento'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TblDocumento');

    }

    /**
     * Obtiene el elemento de la tabla tblDocumento que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblDocumentoPK $pk Objeto de la clave primaria.
     * @return TblDocumento
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idDocumento='".$pk->idDocumento."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblDocumento WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TblDocumento');

    }

    /**
     * Actualiza una fila de la tabla tblDocumento.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vRealName=' . ( ( ( $value = $this->vRealName ) === null || !isset($this->vRealName) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vMime=' . ( ( ( $value = $this->vMime ) === null || !isset($this->vMime) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vTamano=' . ( ( ( $value = $this->vTamano ) === null || !isset($this->vTamano) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescription=' . ( ( ( $value = $this->vDescription ) === null || !isset($this->vDescription) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'mod_user=' . ( ( ( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'last_modified=' . ( ( ( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblDocumento SET $setStr WHERE idDocumento='".addslashes($this->_data['idDocumento'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblDocumento.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vRealName';
        $attributes[] = 'vNombre';
        $attributes[] = 'vMime';
        $attributes[] = 'vTamano';
        $attributes[] = 'vDescription';
        $attributes[] = 'mod_user';
        $attributes[] = 'last_modified';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vRealName ) === null || !isset($this->vRealName) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vMime ) === null || !isset($this->vMime) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vTamano ) === null || !isset($this->vTamano) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDescription ) === null || !isset($this->vDescription) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblDocumento($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblDocumento.
     */
    public function delete(){
        $where = array();
        $where[] = "idDocumento="."'".addslashes($this->idDocumento)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblDocumento WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idDocumento'.
      *
      * @return integer
      */
    public function getIdDocumento(){
        return $this->idDocumento;
    }

    /**
      * Obtiene el valor del atributo 'vRealName'.
      *
      * @return string
      */
    public function getVRealName(){
        return $this->vRealName;
    }

    /**
      * Establece el valor del atributo 'vRealName'.
      *
      * @param string Valor.
      */
    public function setVRealName( $value ){

        $this->vRealName = $value;

    }

    /**
      * Obtiene el valor del atributo 'vNombre'.
      *
      * @return string
      */
    public function getVNombre(){
        return $this->vNombre;
    }

    /**
      * Establece el valor del atributo 'vNombre'.
      *
      * @param string Valor.
      */
    public function setVNombre( $value ){

        $this->vNombre = $value;

    }

    /**
      * Obtiene el valor del atributo 'vMime'.
      *
      * @return string
      */
    public function getVMime(){
        return $this->vMime;
    }

    /**
      * Establece el valor del atributo 'vMime'.
      *
      * @param string Valor.
      */
    public function setVMime( $value ){

        $this->vMime = $value;

    }

    /**
      * Obtiene el valor del atributo 'vTamano'.
      *
      * @return string
      */
    public function getVTamano(){
        return $this->vTamano;
    }

    /**
      * Establece el valor del atributo 'vTamano'.
      *
      * @param string Valor.
      */
    public function setVTamano( $value ){

        $this->vTamano = $value;

    }

    /**
      * Obtiene el valor del atributo 'vDescription'.
      *
      * @return string
      */
    public function getVDescription(){
        return $this->vDescription;
    }

    /**
      * Establece el valor del atributo 'vDescription'.
      *
      * @param string Valor.
      */
    public function setVDescription( $value ){

        $this->vDescription = $value;

    }

    /**
      * Obtiene el valor del atributo 'mod_user'.
      *
      * @return string
      */
    public function getModUser(){
        return $this->modUser;
    }

    /**
      * Establece el valor del atributo 'mod_user'.
      *
      * @param string Valor.
      */
    public function setModUser( $value ){

        $this->modUser = $value;

    }

    /**
      * Obtiene el valor del atributo 'last_modified'.
      *
      * @return string
      */
    public function getLastModified(){
        return $this->lastModified;
    }

    /**
      * Establece el valor del atributo 'last_modified'.
      *
      * @param string Valor.
      */
    public function setLastModified( $value ){

        $this->lastModified = $value;

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelDocumentoCurso'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelDocumentoCursos( $orderBy='' ){

        include_once('TrelDocumentoCurso.inc');
        return TrelDocumentoCurso::findByTblDocumento( $this->_db, $this->idDocumento, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelNotificacionDocumento'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelNotificacionDocumentos( $orderBy='' ){

        include_once('TrelNotificacionDocumento.inc');
        return TrelNotificacionDocumento::findByTblDocumento( $this->_db, $this->idDocumento, $orderBy );

    }
}
?>