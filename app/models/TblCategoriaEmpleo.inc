<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 16 de December de 2010 a las 04:06:51
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TblCategoriaEmpleoSearch.inc' );
require_once( 'TblCategoriaEmpleoPK.inc' );

/**
 * Objeto para acceder a la tabla tblCategoriaEmpleo.
 *
 * @package dataAccess
 */
class TblCategoriaEmpleo extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idCategoriaEmpleo"
     * @var integer
     */
    public $idCategoriaEmpleo;

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
        $this->idCategoriaEmpleo = $data['idCategoriaEmpleo'];
        $this->vNombre = $data['vNombre'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblCategoriaEmpleo segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblCategoriaEmpleoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblCategoriaEmpleo';
        $where = array();
        if( $tmp = $searchItem->idCategoriaEmpleo ){
            $where[] = "idCategoriaEmpleo='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TblCategoriaEmpleo' );
}

    /**
     * Obtiene todas las filas de la tabla tblCategoriaEmpleo.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblCategoriaEmpleo';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblCategoriaEmpleo' );
    }

    /**
     * Obtiene el elemento de la tabla tblCategoriaEmpleo que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idCategoriaEmpleo valor del campo 'idCategoriaEmpleo'.
     * @return TblCategoriaEmpleo
     */
    public static function findByPrimaryKey( $db, $idCategoriaEmpleo ){

       $db->executeQuery("SELECT * FROM tblCategoriaEmpleo WHERE idCategoriaEmpleo = '$idCategoriaEmpleo'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblCategoriaEmpleo');

    }

    /**
     * Obtiene el elemento de la tabla tblCategoriaEmpleo que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblCategoriaEmpleoPK $pk Objeto de la clave primaria.
     * @return TblCategoriaEmpleo
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idCategoriaEmpleo='".$pk->idCategoriaEmpleo."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblCategoriaEmpleo WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblCategoriaEmpleo');

    }

    /**
     * Actualiza una fila de la tabla tblCategoriaEmpleo.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblCategoriaEmpleo SET $setStr WHERE idCategoriaEmpleo='".addslashes($this->_data['idCategoriaEmpleo'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblCategoriaEmpleo.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vNombre';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblCategoriaEmpleo($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblCategoriaEmpleo.
     */
    public function delete(){
        $where = array();
        $where[] = "idCategoriaEmpleo="."'".addslashes($this->idCategoriaEmpleo)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblCategoriaEmpleo WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idCategoriaEmpleo'.
      *
      * @return integer
      */
    public function getIdCategoriaEmpleo(){
        return $this->idCategoriaEmpleo;
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
     * Obtiene todos los elementos relacionados de la tabla 'tblPersona'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPersonas( $orderBy='' ){

        include_once('TblPersona.inc');
        return TblPersona::findByTblCategoriaEmpleo( $this->_db, $this->idCategoriaEmpleo, $orderBy );

    }
}
?>