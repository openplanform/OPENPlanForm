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
require_once( 'TblNotificacionSearch.inc' );
require_once( 'TblNotificacionPK.inc' );

/**
 * Objeto para acceder a la tabla tblNotificacion.
 *
 * @package dataAccess
 */
class TblNotificacion extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idNotificacion"
     * @var integer
     */
    public $idNotificacion;

    /**
     * Atributo que representa el campo "vAsunto"
     * @var string
     */
    public $vAsunto;

    /**
     * Atributo que representa el campo "vMensaje"
     * @var string
     */
    public $vMensaje;

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
        $this->idNotificacion = $data['idNotificacion'];
        $this->vAsunto = $data['vAsunto'];
        $this->vMensaje = $data['vMensaje'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblNotificacion segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblNotificacionSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblNotificacion';
        $where = array();
        if( $tmp = $searchItem->idNotificacion ){
            $where[] = "idNotificacion='$tmp'";
        }
        if( $tmp = $searchItem->vAsunto ){
            $where[] = "vAsunto='$tmp'";
        }
        if( $tmp = $searchItem->vMensaje ){
            $where[] = "vMensaje='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblNotificacion' );
}

    /**
     * Obtiene todas las filas de la tabla tblNotificacion.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblNotificacion';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblNotificacion' );
    }

    /**
     * Obtiene el elemento de la tabla tblNotificacion que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idNotificacion valor del campo 'idNotificacion'.
     * @return TblNotificacion
     */
    public static function findByPrimaryKey( $db, $idNotificacion ){

       $db->executeQuery("SELECT * FROM tblNotificacion WHERE idNotificacion = '$idNotificacion'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblNotificacion');

    }

    /**
     * Obtiene el elemento de la tabla tblNotificacion que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblNotificacionPK $pk Objeto de la clave primaria.
     * @return TblNotificacion
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idNotificacion='".$pk->idNotificacion."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblNotificacion WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblNotificacion');

    }

    /**
     * Actualiza una fila de la tabla tblNotificacion.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vAsunto=' . ( ( ( $value = $this->vAsunto ) === null || !isset($this->vAsunto) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vMensaje=' . ( ( ( $value = $this->vMensaje ) === null || !isset($this->vMensaje) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblNotificacion SET $setStr WHERE idNotificacion='".addslashes($this->_data['idNotificacion'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblNotificacion.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vAsunto';
        $attributes[] = 'vMensaje';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vAsunto ) === null || !isset($this->vAsunto) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vMensaje ) === null || !isset($this->vMensaje) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblNotificacion($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblNotificacion.
     */
    public function delete(){
        $where = array();
        $where[] = "idNotificacion="."'".addslashes($this->idNotificacion)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblNotificacion WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idNotificacion'.
      *
      * @return integer
      */
    public function getIdNotificacion(){
        return $this->idNotificacion;
    }

    /**
      * Obtiene el valor del atributo 'vAsunto'.
      *
      * @return string
      */
    public function getVAsunto(){
        return $this->vAsunto;
    }

    /**
      * Establece el valor del atributo 'vAsunto'.
      *
      * @param string Valor.
      */
    public function setVAsunto( $value ){

        $this->vAsunto = $value;

    }

    /**
      * Obtiene el valor del atributo 'vMensaje'.
      *
      * @return string
      */
    public function getVMensaje(){
        return $this->vMensaje;
    }

    /**
      * Establece el valor del atributo 'vMensaje'.
      *
      * @param string Valor.
      */
    public function setVMensaje( $value ){

        $this->vMensaje = $value;

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelNotificacionDocumento'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelNotificacionDocumentos( $orderBy='' ){

        include_once('TrelNotificacionDocumento.inc');
        return TrelNotificacionDocumento::findByTblNotificacion( $this->_db, $this->idNotificacion, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelNotificacionEmpresa'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelNotificacionEmpresas( $orderBy='' ){

        include_once('TrelNotificacionEmpresa.inc');
        return TrelNotificacionEmpresa::findByTblNotificacion( $this->_db, $this->idNotificacion, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelNotificacionPersona'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelNotificacionPersonas( $orderBy='' ){

        include_once('TrelNotificacionPersona.inc');
        return TrelNotificacionPersona::findByTblNotificacion( $this->_db, $this->idNotificacion, $orderBy );

    }
}
?>