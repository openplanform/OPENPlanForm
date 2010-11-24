<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 24 de November de 2010 a las 08:55:33
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TblCarnetConducirSearch.inc' );
require_once( 'TblCarnetConducirPK.inc' );

/**
 * Objeto para acceder a la tabla tblCarnetConducir.
 *
 * @package dataAccess
 */
class TblCarnetConducir extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idCarnetConducir"
     * @var integer
     */
    public $idCarnetConducir;

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
        $this->idCarnetConducir = $data['idCarnetConducir'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblCarnetConducir segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblCarnetConducirSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblCarnetConducir';
        $where = array();
        if( $tmp = $searchItem->idCarnetConducir ){
            $where[] = "idCarnetConducir='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TblCarnetConducir' );
}

    /**
     * Obtiene todas las filas de la tabla tblCarnetConducir.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblCarnetConducir';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblCarnetConducir' );
    }

    /**
     * Obtiene el elemento de la tabla tblCarnetConducir que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idCarnetConducir valor del campo 'idCarnetConducir'.
     * @return TblCarnetConducir
     */
    public static function findByPrimaryKey( $db, $idCarnetConducir ){

       $db->executeQuery("SELECT * FROM tblCarnetConducir WHERE idCarnetConducir = '$idCarnetConducir'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblCarnetConducir');

    }

    /**
     * Obtiene el elemento de la tabla tblCarnetConducir que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblCarnetConducirPK $pk Objeto de la clave primaria.
     * @return TblCarnetConducir
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idCarnetConducir='".$pk->idCarnetConducir."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblCarnetConducir WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblCarnetConducir');

    }

    /**
     * Actualiza una fila de la tabla tblCarnetConducir.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblCarnetConducir SET $setStr WHERE idCarnetConducir='".addslashes($this->_data['idCarnetConducir'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblCarnetConducir.
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
        if( $this->_db->executeQuery("INSERT INTO tblCarnetConducir($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblCarnetConducir.
     */
    public function delete(){
        $where = array();
        $where[] = "idCarnetConducir="."'".addslashes($this->idCarnetConducir)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblCarnetConducir WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idCarnetConducir'.
      *
      * @return integer
      */
    public function getIdCarnetConducir(){
        return $this->idCarnetConducir;
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

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelPersonaCarnet'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelPersonaCarnets( $orderBy='' ){

        include_once('TrelPersonaCarnet.inc');
        return TrelPersonaCarnet::findByTblCarnetConducir( $this->_db, $this->idCarnetConducir, $orderBy );

    }
}
?>