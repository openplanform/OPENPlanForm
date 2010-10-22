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
        $this->vNombre = $data['vNombre'];
        $this->vMime = $data['vMime'];
        $this->vTamano = $data['vTamano'];

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
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->vMime ){
            $where[] = "vMime='$tmp'";
        }
        if( $tmp = $searchItem->vTamano ){
            $where[] = "vTamano='$tmp'";
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
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vMime=' . ( ( ( $value = $this->vMime ) === null || !isset($this->vMime) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vTamano=' . ( ( ( $value = $this->vTamano ) === null || !isset($this->vTamano) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblDocumento SET $setStr WHERE idDocumento='".addslashes($this->_data['idDocumento'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblDocumento.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vNombre';
        $attributes[] = 'vMime';
        $attributes[] = 'vTamano';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vMime ) === null || !isset($this->vMime) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vTamano ) === null || !isset($this->vTamano) ) ? 'null' : "'".addslashes($value)."'";
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