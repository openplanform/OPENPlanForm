<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 21 de January de 2011 a las 10:11:21
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TblTrabajoParoSearch.inc' );
require_once( 'TblTrabajoParoPK.inc' );

/**
 * Objeto para acceder a la tabla tblTrabajoParo.
 *
 * @package dataAccess
 */
class TblTrabajoParo extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idTrabajoParo"
     * @var integer
     */
    public $idTrabajoParo;

    /**
     * Atributo que representa el campo "vDescripcion"
     * @var string
     */
    public $vDescripcion;

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
        $this->idTrabajoParo = $data['idTrabajoParo'];
        $this->vDescripcion = $data['vDescripcion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblTrabajoParo segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblTrabajoParoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblTrabajoParo';
        $where = array();
        if( $tmp = $searchItem->idTrabajoParo ){
            $where[] = "idTrabajoParo='$tmp'";
        }
        if( $tmp = $searchItem->vDescripcion ){
            $where[] = "vDescripcion='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblTrabajoParo' );
}

    /**
     * Obtiene todas las filas de la tabla tblTrabajoParo.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblTrabajoParo';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblTrabajoParo' );
    }

    /**
     * Obtiene el elemento de la tabla tblTrabajoParo que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idTrabajoParo valor del campo 'idTrabajoParo'.
     * @return TblTrabajoParo
     */
    public static function findByPrimaryKey( $db, $idTrabajoParo ){

       $db->executeQuery("SELECT * FROM tblTrabajoParo WHERE idTrabajoParo = '$idTrabajoParo'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblTrabajoParo');

    }

    /**
     * Obtiene el elemento de la tabla tblTrabajoParo que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblTrabajoParoPK $pk Objeto de la clave primaria.
     * @return TblTrabajoParo
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idTrabajoParo='".$pk->idTrabajoParo."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblTrabajoParo WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblTrabajoParo');

    }

    /**
     * Actualiza una fila de la tabla tblTrabajoParo.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblTrabajoParo SET $setStr WHERE idTrabajoParo='".addslashes($this->_data['idTrabajoParo'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblTrabajoParo.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vDescripcion';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblTrabajoParo($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblTrabajoParo.
     */
    public function delete(){
        $where = array();
        $where[] = "idTrabajoParo="."'".addslashes($this->idTrabajoParo)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblTrabajoParo WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idTrabajoParo'.
      *
      * @return integer
      */
    public function getIdTrabajoParo(){
        return $this->idTrabajoParo;
    }

    /**
      * Obtiene el valor del atributo 'vDescripcion'.
      *
      * @return string
      */
    public function getVDescripcion(){
        return $this->vDescripcion;
    }

    /**
      * Establece el valor del atributo 'vDescripcion'.
      *
      * @param string Valor.
      */
    public function setVDescripcion( $value ){

        $this->vDescripcion = $value;

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblPersona'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPersonas( $orderBy='' ){

        include_once('TblPersona.inc');
        return TblPersona::findByTblTrabajoParo( $this->_db, $this->idTrabajoParo, $orderBy );

    }
}
?>