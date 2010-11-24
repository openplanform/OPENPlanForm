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
require_once( 'TblEstadoCivilSearch.inc' );
require_once( 'TblEstadoCivilPK.inc' );

/**
 * Objeto para acceder a la tabla tblEstadoCivil.
 *
 * @package dataAccess
 */
class TblEstadoCivil extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idEstadoCivil"
     * @var integer
     */
    public $idEstadoCivil;

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
        $this->idEstadoCivil = $data['idEstadoCivil'];
        $this->vNombre = $data['vNombre'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblEstadoCivil segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblEstadoCivilSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblEstadoCivil';
        $where = array();
        if( $tmp = $searchItem->idEstadoCivil ){
            $where[] = "idEstadoCivil='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TblEstadoCivil' );
}

    /**
     * Obtiene todas las filas de la tabla tblEstadoCivil.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblEstadoCivil';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblEstadoCivil' );
    }

    /**
     * Obtiene el elemento de la tabla tblEstadoCivil que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idEstadoCivil valor del campo 'idEstadoCivil'.
     * @return TblEstadoCivil
     */
    public static function findByPrimaryKey( $db, $idEstadoCivil ){

       $db->executeQuery("SELECT * FROM tblEstadoCivil WHERE idEstadoCivil = '$idEstadoCivil'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblEstadoCivil');

    }

    /**
     * Obtiene el elemento de la tabla tblEstadoCivil que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblEstadoCivilPK $pk Objeto de la clave primaria.
     * @return TblEstadoCivil
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idEstadoCivil='".$pk->idEstadoCivil."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblEstadoCivil WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblEstadoCivil');

    }

    /**
     * Actualiza una fila de la tabla tblEstadoCivil.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblEstadoCivil SET $setStr WHERE idEstadoCivil='".addslashes($this->_data['idEstadoCivil'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblEstadoCivil.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vNombre';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblEstadoCivil($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblEstadoCivil.
     */
    public function delete(){
        $where = array();
        $where[] = "idEstadoCivil="."'".addslashes($this->idEstadoCivil)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblEstadoCivil WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idEstadoCivil'.
      *
      * @return integer
      */
    public function getIdEstadoCivil(){
        return $this->idEstadoCivil;
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
     * Obtiene todos los elementos relacionados de la tabla 'tblAlumno'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblAlumnos( $orderBy='' ){

        include_once('TblAlumno.inc');
        return TblAlumno::findByTblEstadoCivil( $this->_db, $this->idEstadoCivil, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblPersona'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPersonas( $orderBy='' ){

        include_once('TblPersona.inc');
        return TblPersona::findByTblEstadoCivil( $this->_db, $this->idEstadoCivil, $orderBy );

    }
}
?>