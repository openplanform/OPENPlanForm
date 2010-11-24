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
require_once( 'TrelNotificacionPersonaSearch.inc' );
require_once( 'TrelNotificacionPersonaPK.inc' );

/**
 * Objeto para acceder a la tabla trelNotificacionPersona.
 *
 * @package dataAccess
 */
class TrelNotificacionPersona extends OwlGenericDO{

    /**
     * Atributo que representa el campo "fkPersona"
     * @var integer
     */
    public $fkPersona;

    /**
     * Atributo que representa el campo "fkNotificacion"
     * @var integer
     */
    public $fkNotificacion;

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
        $this->fkNotificacion = $data['fkNotificacion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelNotificacionPersona segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelNotificacionPersonaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelNotificacionPersona';
        $where = array();
        if( $tmp = $searchItem->fkPersona ){
            $where[] = "fkPersona='$tmp'";
        }
        if( $tmp = $searchItem->fkNotificacion ){
            $where[] = "fkNotificacion='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TrelNotificacionPersona' );
}

    /**
     * Obtiene todas las filas de la tabla trelNotificacionPersona.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelNotificacionPersona';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelNotificacionPersona' );
    }

    /**
     * Obtiene el elemento de la tabla trelNotificacionPersona que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkPersona valor del campo 'fkPersona'.
     * @param integer $fkNotificacion valor del campo 'fkNotificacion'.
     * @return TrelNotificacionPersona
     */
    public static function findByPrimaryKey( $db, $fkPersona, $fkNotificacion ){

       $db->executeQuery("SELECT * FROM trelNotificacionPersona WHERE fkPersona = '$fkPersona' AND fkNotificacion = '$fkNotificacion'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TrelNotificacionPersona');

    }

    /**
     * Obtiene el elemento de la tabla trelNotificacionPersona que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelNotificacionPersonaPK $pk Objeto de la clave primaria.
     * @return TrelNotificacionPersona
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkPersona='".$pk->fkPersona."'";
        $where[]="fkNotificacion='".$pk->fkNotificacion."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelNotificacionPersona WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TrelNotificacionPersona');

    }

    /**
     * Obtiene todas las filas de la tabla trelNotificacionPersona que coinciden con el criterio fkNotificacion='$fkNotificacion'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkNotificacion string Valor del campo fkNotificacion.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblNotificacion( $db, $fkNotificacion, $orderBy='' ){
         $sql = "SELECT * FROM trelNotificacionPersona WHERE fkNotificacion='$fkNotificacion'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelNotificacionPersona' );
     }

    /**
     * Obtiene todas las filas de la tabla trelNotificacionPersona que coinciden con el criterio fkPersona='$fkPersona'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPersona string Valor del campo fkPersona.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPersona( $db, $fkPersona, $orderBy='' ){
         $sql = "SELECT * FROM trelNotificacionPersona WHERE fkPersona='$fkPersona'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelNotificacionPersona' );
     }

    /**
     * Actualiza una fila de la tabla trelNotificacionPersona.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkPersona=' . ( ( ( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkNotificacion=' . ( ( ( $value = $this->fkNotificacion ) === null || !isset($this->fkNotificacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelNotificacionPersona SET $setStr WHERE fkPersona='".addslashes($this->_data['fkPersona'])."' AND fkNotificacion='".addslashes($this->_data['fkNotificacion'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelNotificacionPersona.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkPersona';
        $attributes[] = 'fkNotificacion';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkNotificacion ) === null || !isset($this->fkNotificacion) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelNotificacionPersona($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkPersona, $this->fkNotificacion );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelNotificacionPersona.
     */
    public function delete(){
        $where = array();
        $where[] = "fkPersona="."'".addslashes($this->fkPersona)."'";
        $where[] = "fkNotificacion="."'".addslashes($this->fkNotificacion)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelNotificacionPersona WHERE $where");
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
      * Obtiene el valor del atributo 'fkNotificacion'.
      *
      * @return integer
      */
    public function getFkNotificacion(){
        return $this->fkNotificacion;
    }

    /**
      * Establece el valor del atributo 'fkNotificacion'.
      *
      * @param integer Valor.
      */
    public function setFkNotificacion( $value ){

        $this->fkNotificacion = $value;

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblNotificacion' relacionado.
     *
     * @return TblNotificacion
     */
    public function getTblNotificacion(){
        require_once('TblNotificacion.inc');
        return TblNotificacion::findByPrimaryKey( $this->_db, $this->fkNotificacion );
    }

    /**
     * Asigna el objeto 'TblNotificacion' relacionado.
     *
     * @param TblNotificacion $dataObject
     */
    public function setTblNotificacion( $dataObject ){
        require_once('TblNotificacion.inc');
        $this->setFkNotificacion( $dataObject->getIdNotificacion() );
    }

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