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
require_once( 'TblDisponibilidadAulaSearch.inc' );
require_once( 'TblDisponibilidadAulaPK.inc' );

/**
 * Objeto para acceder a la tabla tblDisponibilidadAula.
 *
 * @package dataAccess
 */
class TblDisponibilidadAula extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idDisponibilidadAula"
     * @var integer
     */
    public $idDisponibilidadAula;

    /**
     * Atributo que representa el campo "fkAula"
     * @var integer
     */
    public $fkAula;

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
        $this->idDisponibilidadAula = $data['idDisponibilidadAula'];
        $this->fkAula = $data['fkAula'];
        $this->dInicio = $data['dInicio'];
        $this->dFin = $data['dFin'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblDisponibilidadAula segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblDisponibilidadAulaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblDisponibilidadAula';
        $where = array();
        if( $tmp = $searchItem->idDisponibilidadAula ){
            $where[] = "idDisponibilidadAula='$tmp'";
        }
        if( $tmp = $searchItem->fkAula ){
            $where[] = "fkAula='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TblDisponibilidadAula' );
}

    /**
     * Obtiene todas las filas de la tabla tblDisponibilidadAula.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblDisponibilidadAula';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblDisponibilidadAula' );
    }

    /**
     * Obtiene el elemento de la tabla tblDisponibilidadAula que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idDisponibilidadAula valor del campo 'idDisponibilidadAula'.
     * @return TblDisponibilidadAula
     */
    public static function findByPrimaryKey( $db, $idDisponibilidadAula ){

       $db->executeQuery("SELECT * FROM tblDisponibilidadAula WHERE idDisponibilidadAula = '$idDisponibilidadAula'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblDisponibilidadAula');

    }

    /**
     * Obtiene el elemento de la tabla tblDisponibilidadAula que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblDisponibilidadAulaPK $pk Objeto de la clave primaria.
     * @return TblDisponibilidadAula
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idDisponibilidadAula='".$pk->idDisponibilidadAula."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblDisponibilidadAula WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblDisponibilidadAula');

    }

    /**
     * Obtiene todas las filas de la tabla tblDisponibilidadAula que coinciden con el criterio fkAula='$fkAula'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkAula string Valor del campo fkAula.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblAula( $db, $fkAula, $orderBy='' ){
         $sql = "SELECT * FROM tblDisponibilidadAula WHERE fkAula='$fkAula'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblDisponibilidadAula' );
     }

    /**
     * Actualiza una fila de la tabla tblDisponibilidadAula.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkAula=' . ( ( ( $value = $this->fkAula ) === null || !isset($this->fkAula) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dInicio=' . ( ( ( $value = $this->dInicio ) === null || !isset($this->dInicio) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dFin=' . ( ( ( $value = $this->dFin ) === null || !isset($this->dFin) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblDisponibilidadAula SET $setStr WHERE idDisponibilidadAula='".addslashes($this->_data['idDisponibilidadAula'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblDisponibilidadAula.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkAula';
        $attributes[] = 'dInicio';
        $attributes[] = 'dFin';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkAula ) === null || !isset($this->fkAula) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dInicio ) === null || !isset($this->dInicio) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dFin ) === null || !isset($this->dFin) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblDisponibilidadAula($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblDisponibilidadAula.
     */
    public function delete(){
        $where = array();
        $where[] = "idDisponibilidadAula="."'".addslashes($this->idDisponibilidadAula)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblDisponibilidadAula WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idDisponibilidadAula'.
      *
      * @return integer
      */
    public function getIdDisponibilidadAula(){
        return $this->idDisponibilidadAula;
    }

    /**
      * Obtiene el valor del atributo 'fkAula'.
      *
      * @return integer
      */
    public function getFkAula(){
        return $this->fkAula;
    }

    /**
      * Establece el valor del atributo 'fkAula'.
      *
      * @param integer Valor.
      */
    public function setFkAula( $value ){

        $this->fkAula = $value;

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
     * Obtiene el objeto 'TblAula' relacionado.
     *
     * @return TblAula
     */
    public function getTblAula(){
        require_once('TblAula.inc');
        return TblAula::findByPrimaryKey( $this->_db, $this->fkAula );
    }

    /**
     * Asigna el objeto 'TblAula' relacionado.
     *
     * @param TblAula $dataObject
     */
    public function setTblAula( $dataObject ){
        require_once('TblAula.inc');
        $this->setFkAula( $dataObject->getIdAula() );
    }
}
?>