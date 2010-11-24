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
require_once( 'TblEstadoPlanSearch.inc' );
require_once( 'TblEstadoPlanPK.inc' );

/**
 * Objeto para acceder a la tabla tblEstadoPlan.
 *
 * @package dataAccess
 */
class TblEstadoPlan extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idEstadoPlan"
     * @var integer
     */
    public $idEstadoPlan;

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
        $this->idEstadoPlan = $data['idEstadoPlan'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblEstadoPlan segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblEstadoPlanSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblEstadoPlan';
        $where = array();
        if( $tmp = $searchItem->idEstadoPlan ){
            $where[] = "idEstadoPlan='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TblEstadoPlan' );
}

    /**
     * Obtiene todas las filas de la tabla tblEstadoPlan.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblEstadoPlan';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblEstadoPlan' );
    }

    /**
     * Obtiene el elemento de la tabla tblEstadoPlan que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idEstadoPlan valor del campo 'idEstadoPlan'.
     * @return TblEstadoPlan
     */
    public static function findByPrimaryKey( $db, $idEstadoPlan ){

       $db->executeQuery("SELECT * FROM tblEstadoPlan WHERE idEstadoPlan = '$idEstadoPlan'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblEstadoPlan');

    }

    /**
     * Obtiene el elemento de la tabla tblEstadoPlan que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblEstadoPlanPK $pk Objeto de la clave primaria.
     * @return TblEstadoPlan
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idEstadoPlan='".$pk->idEstadoPlan."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblEstadoPlan WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblEstadoPlan');

    }

    /**
     * Actualiza una fila de la tabla tblEstadoPlan.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblEstadoPlan SET $setStr WHERE idEstadoPlan='".addslashes($this->_data['idEstadoPlan'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblEstadoPlan.
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
        if( $this->_db->executeQuery("INSERT INTO tblEstadoPlan($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblEstadoPlan.
     */
    public function delete(){
        $where = array();
        $where[] = "idEstadoPlan="."'".addslashes($this->idEstadoPlan)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblEstadoPlan WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idEstadoPlan'.
      *
      * @return integer
      */
    public function getIdEstadoPlan(){
        return $this->idEstadoPlan;
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
     * Obtiene todos los elementos relacionados de la tabla 'tblPlan'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPlans( $orderBy='' ){

        include_once('TblPlan.inc');
        return TblPlan::findByTblEstadoPlan( $this->_db, $this->idEstadoPlan, $orderBy );

    }
}
?>