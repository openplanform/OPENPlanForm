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
require_once( 'TblTipoPlanSearch.inc' );
require_once( 'TblTipoPlanPK.inc' );

/**
 * Objeto para acceder a la tabla tblTipoPlan.
 *
 * @package dataAccess
 */
class TblTipoPlan extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idTipoPlan"
     * @var integer
     */
    public $idTipoPlan;

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
        $this->idTipoPlan = $data['idTipoPlan'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblTipoPlan segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblTipoPlanSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblTipoPlan';
        $where = array();
        if( $tmp = $searchItem->idTipoPlan ){
            $where[] = "idTipoPlan='$tmp'";
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
        return NingenGenericDO::createCollection( $db, $sql, 'TblTipoPlan' );
}

    /**
     * Obtiene todas las filas de la tabla tblTipoPlan.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblTipoPlan';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblTipoPlan' );
    }

    /**
     * Obtiene el elemento de la tabla tblTipoPlan que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idTipoPlan valor del campo 'idTipoPlan'.
     * @return TblTipoPlan
     */
    public static function findByPrimaryKey( $db, $idTipoPlan ){

       $db->executeQuery("SELECT * FROM tblTipoPlan WHERE idTipoPlan = '$idTipoPlan'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TblTipoPlan');

    }

    /**
     * Obtiene el elemento de la tabla tblTipoPlan que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblTipoPlanPK $pk Objeto de la clave primaria.
     * @return TblTipoPlan
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idTipoPlan='".$pk->idTipoPlan."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblTipoPlan WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TblTipoPlan');

    }

    /**
     * Actualiza una fila de la tabla tblTipoPlan.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblTipoPlan SET $setStr WHERE idTipoPlan='".addslashes($this->_data['idTipoPlan'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblTipoPlan.
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
        if( $this->_db->executeQuery("INSERT INTO tblTipoPlan($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblTipoPlan.
     */
    public function delete(){
        $where = array();
        $where[] = "idTipoPlan="."'".addslashes($this->idTipoPlan)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblTipoPlan WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idTipoPlan'.
      *
      * @return integer
      */
    public function getIdTipoPlan(){
        return $this->idTipoPlan;
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
        return TblPlan::findByTblTipoPlan( $this->_db, $this->idTipoPlan, $orderBy );

    }
}
?>