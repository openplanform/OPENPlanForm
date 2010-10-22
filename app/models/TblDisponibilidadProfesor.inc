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
require_once( 'TblDisponibilidadProfesorSearch.inc' );
require_once( 'TblDisponibilidadProfesorPK.inc' );

/**
 * Objeto para acceder a la tabla tblDisponibilidadProfesor.
 *
 * @package dataAccess
 */
class TblDisponibilidadProfesor extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idDisponibilidadProfesor"
     * @var integer
     */
    public $idDisponibilidadProfesor;

    /**
     * Atributo que representa el campo "fkProfesor"
     * @var integer
     */
    public $fkProfesor;

    /**
     * Atributo que representa el campo "dInicio"
     * @var string
     */
    public $dInicio;

    /**
     * Atributo que representa el campo "dFin"
     * @var string
     */
    public $dFin;

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
        $this->idDisponibilidadProfesor = $data['idDisponibilidadProfesor'];
        $this->fkProfesor = $data['fkProfesor'];
        $this->dInicio = $data['dInicio'];
        $this->dFin = $data['dFin'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblDisponibilidadProfesor segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblDisponibilidadProfesorSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblDisponibilidadProfesor';
        $where = array();
        if( $tmp = $searchItem->idDisponibilidadProfesor ){
            $where[] = "idDisponibilidadProfesor='$tmp'";
        }
        if( $tmp = $searchItem->fkProfesor ){
            $where[] = "fkProfesor='$tmp'";
        }
        if( $tmp = $searchItem->dInicio ){
            $where[] = "dInicio='$tmp'";
        }
        if( $tmp = $searchItem->dFin ){
            $where[] = "dFin='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return NingenGenericDO::createCollection( $db, $sql, 'TblDisponibilidadProfesor' );
}

    /**
     * Obtiene todas las filas de la tabla tblDisponibilidadProfesor.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblDisponibilidadProfesor';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblDisponibilidadProfesor' );
    }

    /**
     * Obtiene el elemento de la tabla tblDisponibilidadProfesor que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idDisponibilidadProfesor valor del campo 'idDisponibilidadProfesor'.
     * @return TblDisponibilidadProfesor
     */
    public static function findByPrimaryKey( $db, $idDisponibilidadProfesor ){

       $db->executeQuery("SELECT * FROM tblDisponibilidadProfesor WHERE idDisponibilidadProfesor = '$idDisponibilidadProfesor'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TblDisponibilidadProfesor');

    }

    /**
     * Obtiene el elemento de la tabla tblDisponibilidadProfesor que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblDisponibilidadProfesorPK $pk Objeto de la clave primaria.
     * @return TblDisponibilidadProfesor
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idDisponibilidadProfesor='".$pk->idDisponibilidadProfesor."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblDisponibilidadProfesor WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TblDisponibilidadProfesor');

    }

    /**
     * Obtiene todas las filas de la tabla tblDisponibilidadProfesor que coinciden con el criterio fkProfesor='$fkProfesor'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkProfesor string Valor del campo fkProfesor.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTrelProfesor( $db, $fkProfesor, $orderBy='' ){
         $sql = "SELECT * FROM tblDisponibilidadProfesor WHERE fkProfesor='$fkProfesor'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblDisponibilidadProfesor' );
     }

    /**
     * Actualiza una fila de la tabla tblDisponibilidadProfesor.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkProfesor=' . ( ( ( $value = $this->fkProfesor ) === null || !isset($this->fkProfesor) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dInicio=' . ( ( ( $value = $this->dInicio ) === null || !isset($this->dInicio) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dFin=' . ( ( ( $value = $this->dFin ) === null || !isset($this->dFin) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblDisponibilidadProfesor SET $setStr WHERE idDisponibilidadProfesor='".addslashes($this->_data['idDisponibilidadProfesor'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblDisponibilidadProfesor.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkProfesor';
        $attributes[] = 'dInicio';
        $attributes[] = 'dFin';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkProfesor ) === null || !isset($this->fkProfesor) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dInicio ) === null || !isset($this->dInicio) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dFin ) === null || !isset($this->dFin) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblDisponibilidadProfesor($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblDisponibilidadProfesor.
     */
    public function delete(){
        $where = array();
        $where[] = "idDisponibilidadProfesor="."'".addslashes($this->idDisponibilidadProfesor)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblDisponibilidadProfesor WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idDisponibilidadProfesor'.
      *
      * @return integer
      */
    public function getIdDisponibilidadProfesor(){
        return $this->idDisponibilidadProfesor;
    }

    /**
      * Obtiene el valor del atributo 'fkProfesor'.
      *
      * @return integer
      */
    public function getFkProfesor(){
        return $this->fkProfesor;
    }

    /**
      * Establece el valor del atributo 'fkProfesor'.
      *
      * @param integer Valor.
      */
    public function setFkProfesor( $value ){

        $this->fkProfesor = $value;

    }

    /**
      * Obtiene el valor del atributo 'dInicio'.
      *
      * @return string
      */
    public function getDInicio(){
        return $this->dInicio;
    }

    /**
      * Establece el valor del atributo 'dInicio'.
      *
      * @param string Valor.
      */
    public function setDInicio( $value ){

        $this->dInicio = $value;

    }

    /**
      * Obtiene el valor del atributo 'dFin'.
      *
      * @return string
      */
    public function getDFin(){
        return $this->dFin;
    }

    /**
      * Establece el valor del atributo 'dFin'.
      *
      * @param string Valor.
      */
    public function setDFin( $value ){

        $this->dFin = $value;

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TrelProfesor' relacionado.
     *
     * @return TrelProfesor
     */
    public function getTrelProfesor(){
        require_once('TrelProfesor.inc');
        return TrelProfesor::findByPrimaryKey( $this->_db, $this->fkProfesor );
    }

    /**
     * Asigna el objeto 'TrelProfesor' relacionado.
     *
     * @param TrelProfesor $dataObject
     */
    public function setTrelProfesor( $dataObject ){
        require_once('TrelProfesor.inc');
        $this->setFkProfesor( $dataObject->getIdProfesor() );
    }
}
?>