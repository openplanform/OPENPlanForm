<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 29 de December de 2010 a las 08:23:55
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TblEstudioSearch.inc' );
require_once( 'TblEstudioPK.inc' );

/**
 * Objeto para acceder a la tabla tblEstudio.
 *
 * @package dataAccess
 */
class TblEstudio extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idEstudio"
     * @var integer
     */
    public $idEstudio;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

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
        $this->idEstudio = $data['idEstudio'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblEstudio segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblEstudioSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblEstudio';
        $where = array();
        if( $tmp = $searchItem->idEstudio ){
            $where[] = "idEstudio='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TblEstudio' );
}

    /**
     * Obtiene todas las filas de la tabla tblEstudio.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblEstudio';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblEstudio' );
    }

    /**
     * Obtiene el elemento de la tabla tblEstudio que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idEstudio valor del campo 'idEstudio'.
     * @return TblEstudio
     */
    public static function findByPrimaryKey( $db, $idEstudio ){

       $db->executeQuery("SELECT * FROM tblEstudio WHERE idEstudio = '$idEstudio'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblEstudio');

    }

    /**
     * Obtiene el elemento de la tabla tblEstudio que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblEstudioPK $pk Objeto de la clave primaria.
     * @return TblEstudio
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idEstudio='".$pk->idEstudio."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblEstudio WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblEstudio');

    }

    /**
     * Actualiza una fila de la tabla tblEstudio.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblEstudio SET $setStr WHERE idEstudio='".addslashes($this->_data['idEstudio'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblEstudio.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vNombre';
        $attributes[] = 'vDescripcion';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblEstudio($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblEstudio.
     */
    public function delete(){
        $where = array();
        $where[] = "idEstudio="."'".addslashes($this->idEstudio)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblEstudio WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idEstudio'.
      *
      * @return integer
      */
    public function getIdEstudio(){
        return $this->idEstudio;
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
}
?>