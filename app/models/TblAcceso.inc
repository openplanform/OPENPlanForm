<?php
/**
 * Este archivo ha sido generado con Ningen DoGen v.0.6
 * el 22 de October de 2010 a las 13:48:57
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/NingenConnection.inc');
require_once( 'dbase/NingenGenericDO.inc');
require_once( 'TblAccesoSearch.inc' );
require_once( 'TblAccesoPK.inc' );

/**
 * Objeto para acceder a la tabla tblAcceso.
 *
 * @package dataAccess
 */
class TblAcceso extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idAcceso"
     * @var integer
     */
    public $idAcceso;

    /**
     * Atributo que representa el campo "fkPadre"
     * @var integer
     */
    public $fkPadre;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

    /**
     * Atributo que representa el campo "bMenu"
     * @var boolean
     */
    public $bMenu;

    /**
     * Atributo que representa el campo "iOrden"
     * @var integer
     */
    public $iOrden;

    /**
     * Atributo que representa el campo "vControlador"
     * @var string
     */
    public $vControlador;

    /**
     * Atributo que representa el campo "vAccion"
     * @var string
     */
    public $vAccion;

    /**
     * Atributo que representa el campo "vRoles"
     * @var string
     */
    public $vRoles;

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
        $this->idAcceso = $data['idAcceso'];
        $this->fkPadre = $data['fkPadre'];
        $this->vNombre = $data['vNombre'];
        $this->bMenu = $data['bMenu'];
        $this->iOrden = $data['iOrden'];
        $this->vControlador = $data['vControlador'];
        $this->vAccion = $data['vAccion'];
        $this->vRoles = $data['vRoles'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblAcceso segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblAccesoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblAcceso';
        $where = array();
        if( $tmp = $searchItem->idAcceso ){
            $where[] = "idAcceso='$tmp'";
        }
        if( $tmp = $searchItem->fkPadre ){
            $where[] = "fkPadre='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->bMenu ){
            $where[] = "bMenu='$tmp'";
        }
        if( $tmp = $searchItem->iOrden ){
            $where[] = "iOrden='$tmp'";
        }
        if( $tmp = $searchItem->vControlador ){
            $where[] = "vControlador='$tmp'";
        }
        if( $tmp = $searchItem->vAccion ){
            $where[] = "vAccion='$tmp'";
        }
        if( $tmp = $searchItem->vRoles ){
            $where[] = "vRoles='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return NingenGenericDO::createCollection( $db, $sql, 'TblAcceso' );
}

    /**
     * Obtiene todas las filas de la tabla tblAcceso.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblAcceso';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblAcceso' );
    }

    /**
     * Obtiene el elemento de la tabla tblAcceso que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idAcceso valor del campo 'idAcceso'.
     * @param integer $fkPadre valor del campo 'fkPadre'.
     * @return TblAcceso
     */
    public static function findByPrimaryKey( $db, $idAcceso, $fkPadre ){

       $db->executeQuery("SELECT * FROM tblAcceso WHERE idAcceso = '$idAcceso' AND fkPadre = '$fkPadre'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TblAcceso');

    }

    /**
     * Obtiene el elemento de la tabla tblAcceso que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblAccesoPK $pk Objeto de la clave primaria.
     * @return TblAcceso
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idAcceso='".$pk->idAcceso."'";
        $where[]="fkPadre='".$pk->fkPadre."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblAcceso WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TblAcceso');

    }

    /**
     * Actualiza una fila de la tabla tblAcceso.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkPadre=' . ( ( ( $value = $this->fkPadre ) === null || !isset($this->fkPadre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bMenu=' . ( ( ( $value = $this->bMenu ) === null || !isset($this->bMenu) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iOrden=' . ( ( ( $value = $this->iOrden ) === null || !isset($this->iOrden) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vControlador=' . ( ( ( $value = $this->vControlador ) === null || !isset($this->vControlador) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vAccion=' . ( ( ( $value = $this->vAccion ) === null || !isset($this->vAccion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vRoles=' . ( ( ( $value = $this->vRoles ) === null || !isset($this->vRoles) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblAcceso SET $setStr WHERE idAcceso='".addslashes($this->_data['idAcceso'])."' AND fkPadre='".addslashes($this->_data['fkPadre'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblAcceso.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkPadre';
        $attributes[] = 'vNombre';
        $attributes[] = 'bMenu';
        $attributes[] = 'iOrden';
        $attributes[] = 'vControlador';
        $attributes[] = 'vAccion';
        $attributes[] = 'vRoles';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkPadre ) === null || !isset($this->fkPadre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bMenu ) === null || !isset($this->bMenu) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iOrden ) === null || !isset($this->iOrden) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vControlador ) === null || !isset($this->vControlador) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vAccion ) === null || !isset($this->vAccion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vRoles ) === null || !isset($this->vRoles) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblAcceso($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId(), $this->fkPadre );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblAcceso.
     */
    public function delete(){
        $where = array();
        $where[] = "idAcceso="."'".addslashes($this->idAcceso)."'";
        $where[] = "fkPadre="."'".addslashes($this->fkPadre)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblAcceso WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idAcceso'.
      *
      * @return integer
      */
    public function getIdAcceso(){
        return $this->idAcceso;
    }

    /**
      * Obtiene el valor del atributo 'fkPadre'.
      *
      * @return integer
      */
    public function getFkPadre(){
        return $this->fkPadre;
    }

    /**
      * Establece el valor del atributo 'fkPadre'.
      *
      * @param integer Valor.
      */
    public function setFkPadre( $value ){

        $this->fkPadre = $value;

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
      * Obtiene el valor del atributo 'bMenu'.
      *
      * @return boolean
      */
    public function isBMenu(){
        return ($this->bMenu ? true : false);
    }

    /**
      * Establece el valor del atributo 'bMenu'.
      *
      * @param boolean Valor.
      */
    public function setBMenu( $value ){

        $this->bMenu = $value;

    }

    /**
      * Obtiene el valor del atributo 'iOrden'.
      *
      * @return integer
      */
    public function getIOrden(){
        return $this->iOrden;
    }

    /**
      * Establece el valor del atributo 'iOrden'.
      *
      * @param integer Valor.
      */
    public function setIOrden( $value ){

        $this->iOrden = $value;

    }

    /**
      * Obtiene el valor del atributo 'vControlador'.
      *
      * @return string
      */
    public function getVControlador(){
        return $this->vControlador;
    }

    /**
      * Establece el valor del atributo 'vControlador'.
      *
      * @param string Valor.
      */
    public function setVControlador( $value ){

        $this->vControlador = $value;

    }

    /**
      * Obtiene el valor del atributo 'vAccion'.
      *
      * @return string
      */
    public function getVAccion(){
        return $this->vAccion;
    }

    /**
      * Establece el valor del atributo 'vAccion'.
      *
      * @param string Valor.
      */
    public function setVAccion( $value ){

        $this->vAccion = $value;

    }

    /**
      * Obtiene el valor del atributo 'vRoles'.
      *
      * @return string
      */
    public function getVRoles(){
        return $this->vRoles;
    }

    /**
      * Establece el valor del atributo 'vRoles'.
      *
      * @param string Valor.
      */
    public function setVRoles( $value ){

        $this->vRoles = $value;

    }
}
?>