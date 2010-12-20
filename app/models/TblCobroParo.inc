<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 15 de December de 2010 a las 08:27:58
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TblCobroParoSearch.inc' );
require_once( 'TblCobroParoPK.inc' );

/**
 * Objeto para acceder a la tabla tblCobroParo.
 *
 * @package dataAccess
 */
class TblCobroParo extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idCobroParo"
     * @var integer
     */
    public $idCobroParo;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

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
        $this->idCobroParo = $data['idCobroParo'];
        $this->vNombre = $data['vNombre'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblCobroParo segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblCobroParoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblCobroParo';
        $where = array();
        if( $tmp = $searchItem->idCobroParo ){
            $where[] = "idCobroParo='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblCobroParo' );
}

    /**
     * Obtiene todas las filas de la tabla tblCobroParo.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblCobroParo';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblCobroParo' );
    }

    /**
     * Obtiene el elemento de la tabla tblCobroParo que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idCobroParo valor del campo 'idCobroParo'.
     * @return TblCobroParo
     */
    public static function findByPrimaryKey( $db, $idCobroParo ){

       $db->executeQuery("SELECT * FROM tblCobroParo WHERE idCobroParo = '$idCobroParo'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblCobroParo');

    }

    /**
     * Obtiene el elemento de la tabla tblCobroParo que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblCobroParoPK $pk Objeto de la clave primaria.
     * @return TblCobroParo
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idCobroParo='".$pk->idCobroParo."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblCobroParo WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblCobroParo');

    }

    /**
     * Actualiza una fila de la tabla tblCobroParo.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblCobroParo SET $setStr WHERE idCobroParo='".addslashes($this->_data['idCobroParo'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblCobroParo.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vNombre';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblCobroParo($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblCobroParo.
     */
    public function delete(){
        $where = array();
        $where[] = "idCobroParo="."'".addslashes($this->idCobroParo)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblCobroParo WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idCobroParo'.
      *
      * @return integer
      */
    public function getIdCobroParo(){
        return $this->idCobroParo;
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
}
?>