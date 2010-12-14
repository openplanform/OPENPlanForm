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
require_once( 'TblDisponibilidadProfesorSearch.inc' );
require_once( 'TblDisponibilidadProfesorPK.inc' );

/**
 * Objeto para acceder a la tabla tblDisponibilidadProfesor.
 *
 * @package dataAccess
 */
class TblDisponibilidadProfesor extends OwlGenericDO{

    /**
     * Atributo que representa el campo "fkPersona"
     * @var integer
     */
    public $fkPersona;

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

    /**
     * Atributo que representa el campo "idDisponibilidad"
     * @var integer
     */
    public $idDisponibilidad;

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
        $this->fkPersona = $data['fkPersona'];
        $this->dInicio = $data['dInicio'];
        $this->dFin = $data['dFin'];
        $this->idDisponibilidad = $data['idDisponibilidad'];

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
        if( $tmp = $searchItem->fkPersona ){
            $where[] = "fkPersona='$tmp'";
        }
        if( $tmp = $searchItem->dInicio ){
            $where[] = "dInicio='$tmp'";
        }
        if( $tmp = $searchItem->dFin ){
            $where[] = "dFin='$tmp'";
        }
        if( $tmp = $searchItem->idDisponibilidad ){
            $where[] = "idDisponibilidad='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblDisponibilidadProfesor' );
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
         return OwlGenericDO::createCollection( $db, $sql, 'TblDisponibilidadProfesor' );
    }

    /**
     * Obtiene el elemento de la tabla tblDisponibilidadProfesor que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idDisponibilidad valor del campo 'idDisponibilidad'.
     * @return TblDisponibilidadProfesor
     */
    public static function findByPrimaryKey( $db, $idDisponibilidad ){

       $db->executeQuery("SELECT * FROM tblDisponibilidadProfesor WHERE idDisponibilidad = '$idDisponibilidad'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblDisponibilidadProfesor');

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
        $where[]="idDisponibilidad='".$pk->idDisponibilidad."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblDisponibilidadProfesor WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblDisponibilidadProfesor');

    }

    /**
     * Obtiene todas las filas de la tabla tblDisponibilidadProfesor que coinciden con el criterio fkPersona='$fkPersona'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPersona string Valor del campo fkPersona.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPersona( $db, $fkPersona, $orderBy='' ){
         $sql = "SELECT * FROM tblDisponibilidadProfesor WHERE fkPersona='$fkPersona'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblDisponibilidadProfesor' );
     }

    /**
     * Actualiza una fila de la tabla tblDisponibilidadProfesor.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkPersona=' . ( ( ( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dInicio=' . ( ( ( $value = $this->dInicio ) === null || !isset($this->dInicio) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dFin=' . ( ( ( $value = $this->dFin ) === null || !isset($this->dFin) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'idDisponibilidad=' . ( ( ( $value = $this->idDisponibilidad ) === null || !isset($this->idDisponibilidad) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblDisponibilidadProfesor SET $setStr WHERE idDisponibilidad='".addslashes($this->_data['idDisponibilidad'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblDisponibilidadProfesor.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkPersona';
        $attributes[] = 'dInicio';
        $attributes[] = 'dFin';
        $attributes[] = 'idDisponibilidad';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dInicio ) === null || !isset($this->dInicio) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dFin ) === null || !isset($this->dFin) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->idDisponibilidad ) === null || !isset($this->idDisponibilidad) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblDisponibilidadProfesor($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->idDisponibilidad );
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
        $where[] = "idDisponibilidad="."'".addslashes($this->idDisponibilidad)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblDisponibilidadProfesor WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'fkPersona'.
      *
      * @return integer
      */
    public function getFkPersona(){
        return $this->fkPersona;
    }

    /**
      * Establece el valor del atributo 'fkPersona'.
      *
      * @param integer Valor.
      */
    public function setFkPersona( $value ){

        $this->fkPersona = $value;

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

    /**
      * Obtiene el valor del atributo 'idDisponibilidad'.
      *
      * @return integer
      */
    public function getIdDisponibilidad(){
        return $this->idDisponibilidad;
    }

    /**
      * Establece el valor del atributo 'idDisponibilidad'.
      *
      * @param integer Valor.
      */
    public function setIdDisponibilidad( $value ){

        $this->idDisponibilidad = $value;

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblPersona' relacionado.
     *
     * @return TblPersona
     */
    public function getTblPersona(){
        require_once('TblPersona.inc');
        return TblPersona::findByPrimaryKey( $this->_db, $this->fkPersona );
    }

    /**
     * Asigna el objeto 'TblPersona' relacionado.
     *
     * @param TblPersona $dataObject
     */
    public function setTblPersona( $dataObject ){
        require_once('TblPersona.inc');
        $this->setFkPersona( $dataObject->getIdPersona() );
    }
}
?>