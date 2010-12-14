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
require_once( 'TblModalidadSearch.inc' );
require_once( 'TblModalidadPK.inc' );

/**
 * Objeto para acceder a la tabla tblModalidad.
 *
 * @package dataAccess
 */
class TblModalidad extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idModalidad"
     * @var integer
     */
    public $idModalidad;

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

    /**
     * Atributo que representa el campo "ePrecioHora"
     * @var string
     */
    public $ePrecioHora;

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
        $this->idModalidad = $data['idModalidad'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];
        $this->ePrecioHora = $data['ePrecioHora'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblModalidad segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblModalidadSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblModalidad';
        $where = array();
        if( $tmp = $searchItem->idModalidad ){
            $where[] = "idModalidad='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->vDescripcion ){
            $where[] = "vDescripcion='$tmp'";
        }
        if( $tmp = $searchItem->ePrecioHora ){
            $where[] = "ePrecioHora='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblModalidad' );
}

    /**
     * Obtiene todas las filas de la tabla tblModalidad.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblModalidad';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblModalidad' );
    }

    /**
     * Obtiene el elemento de la tabla tblModalidad que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idModalidad valor del campo 'idModalidad'.
     * @return TblModalidad
     */
    public static function findByPrimaryKey( $db, $idModalidad ){

       $db->executeQuery("SELECT * FROM tblModalidad WHERE idModalidad = '$idModalidad'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblModalidad');

    }

    /**
     * Obtiene el elemento de la tabla tblModalidad que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblModalidadPK $pk Objeto de la clave primaria.
     * @return TblModalidad
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idModalidad='".$pk->idModalidad."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblModalidad WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblModalidad');

    }

    /**
     * Actualiza una fila de la tabla tblModalidad.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'ePrecioHora=' . ( ( ( $value = $this->ePrecioHora ) === null || !isset($this->ePrecioHora) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblModalidad SET $setStr WHERE idModalidad='".addslashes($this->_data['idModalidad'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblModalidad.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vNombre';
        $attributes[] = 'vDescripcion';
        $attributes[] = 'ePrecioHora';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->ePrecioHora ) === null || !isset($this->ePrecioHora) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblModalidad($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblModalidad.
     */
    public function delete(){
        $where = array();
        $where[] = "idModalidad="."'".addslashes($this->idModalidad)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblModalidad WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idModalidad'.
      *
      * @return integer
      */
    public function getIdModalidad(){
        return $this->idModalidad;
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
      * Obtiene el valor del atributo 'ePrecioHora'.
      *
      * @return string
      */
    public function getEPrecioHora(){
        return $this->ePrecioHora;
    }

    /**
      * Establece el valor del atributo 'ePrecioHora'.
      *
      * @param string Valor.
      */
    public function setEPrecioHora( $value ){

        $this->ePrecioHora = $value;

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblCurso'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblCursos( $orderBy='' ){

        include_once('TblCurso.inc');
        return TblCurso::findByTblModalidad( $this->_db, $this->idModalidad, $orderBy );

    }
}
?>