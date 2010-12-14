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
require_once( 'TrelNotificacionDocumentoSearch.inc' );
require_once( 'TrelNotificacionDocumentoPK.inc' );

/**
 * Objeto para acceder a la tabla trelNotificacionDocumento.
 *
 * @package dataAccess
 */
class TrelNotificacionDocumento extends OwlGenericDO{

    /**
     * Atributo que representa el campo "fkNotificacion"
     * @var integer
     */
    public $fkNotificacion;

    /**
     * Atributo que representa el campo "fkDocumento"
     * @var integer
     */
    public $fkDocumento;

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
        $this->fkNotificacion = $data['fkNotificacion'];
        $this->fkDocumento = $data['fkDocumento'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelNotificacionDocumento segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelNotificacionDocumentoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelNotificacionDocumento';
        $where = array();
        if( $tmp = $searchItem->fkNotificacion ){
            $where[] = "fkNotificacion='$tmp'";
        }
        if( $tmp = $searchItem->fkDocumento ){
            $where[] = "fkDocumento='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TrelNotificacionDocumento' );
}

    /**
     * Obtiene todas las filas de la tabla trelNotificacionDocumento.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelNotificacionDocumento';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelNotificacionDocumento' );
    }

    /**
     * Obtiene el elemento de la tabla trelNotificacionDocumento que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkNotificacion valor del campo 'fkNotificacion'.
     * @param integer $fkDocumento valor del campo 'fkDocumento'.
     * @return TrelNotificacionDocumento
     */
    public static function findByPrimaryKey( $db, $fkNotificacion, $fkDocumento ){

       $db->executeQuery("SELECT * FROM trelNotificacionDocumento WHERE fkNotificacion = '$fkNotificacion' AND fkDocumento = '$fkDocumento'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TrelNotificacionDocumento');

    }

    /**
     * Obtiene el elemento de la tabla trelNotificacionDocumento que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelNotificacionDocumentoPK $pk Objeto de la clave primaria.
     * @return TrelNotificacionDocumento
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkNotificacion='".$pk->fkNotificacion."'";
        $where[]="fkDocumento='".$pk->fkDocumento."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelNotificacionDocumento WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TrelNotificacionDocumento');

    }

    /**
     * Obtiene todas las filas de la tabla trelNotificacionDocumento que coinciden con el criterio fkDocumento='$fkDocumento'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkDocumento string Valor del campo fkDocumento.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblDocumento( $db, $fkDocumento, $orderBy='' ){
         $sql = "SELECT * FROM trelNotificacionDocumento WHERE fkDocumento='$fkDocumento'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelNotificacionDocumento' );
     }

    /**
     * Obtiene todas las filas de la tabla trelNotificacionDocumento que coinciden con el criterio fkNotificacion='$fkNotificacion'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkNotificacion string Valor del campo fkNotificacion.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblNotificacion( $db, $fkNotificacion, $orderBy='' ){
         $sql = "SELECT * FROM trelNotificacionDocumento WHERE fkNotificacion='$fkNotificacion'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelNotificacionDocumento' );
     }

    /**
     * Actualiza una fila de la tabla trelNotificacionDocumento.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkNotificacion=' . ( ( ( $value = $this->fkNotificacion ) === null || !isset($this->fkNotificacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkDocumento=' . ( ( ( $value = $this->fkDocumento ) === null || !isset($this->fkDocumento) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelNotificacionDocumento SET $setStr WHERE fkNotificacion='".addslashes($this->_data['fkNotificacion'])."' AND fkDocumento='".addslashes($this->_data['fkDocumento'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelNotificacionDocumento.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkNotificacion';
        $attributes[] = 'fkDocumento';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkNotificacion ) === null || !isset($this->fkNotificacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkDocumento ) === null || !isset($this->fkDocumento) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelNotificacionDocumento($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkNotificacion, $this->fkDocumento );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelNotificacionDocumento.
     */
    public function delete(){
        $where = array();
        $where[] = "fkNotificacion="."'".addslashes($this->fkNotificacion)."'";
        $where[] = "fkDocumento="."'".addslashes($this->fkDocumento)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelNotificacionDocumento WHERE $where");
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

    /**
      * Obtiene el valor del atributo 'fkDocumento'.
      *
      * @return integer
      */
    public function getFkDocumento(){
        return $this->fkDocumento;
    }

    /**
      * Establece el valor del atributo 'fkDocumento'.
      *
      * @param integer Valor.
      */
    public function setFkDocumento( $value ){

        $this->fkDocumento = $value;

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblDocumento' relacionado.
     *
     * @return TblDocumento
     */
    public function getTblDocumento(){
        require_once('TblDocumento.inc');
        return TblDocumento::findByPrimaryKey( $this->_db, $this->fkDocumento );
    }

    /**
     * Asigna el objeto 'TblDocumento' relacionado.
     *
     * @param TblDocumento $dataObject
     */
    public function setTblDocumento( $dataObject ){
        require_once('TblDocumento.inc');
        $this->setFkDocumento( $dataObject->getIdDocumento() );
    }

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
}
?>