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
require_once( 'TrelNotificacionEmpresaSearch.inc' );
require_once( 'TrelNotificacionEmpresaPK.inc' );

/**
 * Objeto para acceder a la tabla trelNotificacionEmpresa.
 *
 * @package dataAccess
 */
class TrelNotificacionEmpresa extends OwlGenericDO{

    /**
     * Atributo que representa el campo "fkEmpresa"
     * @var integer
     */
    public $fkEmpresa;

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
        $this->fkEmpresa = $data['fkEmpresa'];
        $this->fkNotificacion = $data['fkNotificacion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelNotificacionEmpresa segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelNotificacionEmpresaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelNotificacionEmpresa';
        $where = array();
        if( $tmp = $searchItem->fkEmpresa ){
            $where[] = "fkEmpresa='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TrelNotificacionEmpresa' );
}

    /**
     * Obtiene todas las filas de la tabla trelNotificacionEmpresa.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelNotificacionEmpresa';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelNotificacionEmpresa' );
    }

    /**
     * Obtiene el elemento de la tabla trelNotificacionEmpresa que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkEmpresa valor del campo 'fkEmpresa'.
     * @param integer $fkNotificacion valor del campo 'fkNotificacion'.
     * @return TrelNotificacionEmpresa
     */
    public static function findByPrimaryKey( $db, $fkEmpresa, $fkNotificacion ){

       $db->executeQuery("SELECT * FROM trelNotificacionEmpresa WHERE fkEmpresa = '$fkEmpresa' AND fkNotificacion = '$fkNotificacion'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TrelNotificacionEmpresa');

    }

    /**
     * Obtiene el elemento de la tabla trelNotificacionEmpresa que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelNotificacionEmpresaPK $pk Objeto de la clave primaria.
     * @return TrelNotificacionEmpresa
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkEmpresa='".$pk->fkEmpresa."'";
        $where[]="fkNotificacion='".$pk->fkNotificacion."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelNotificacionEmpresa WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TrelNotificacionEmpresa');

    }

    /**
     * Obtiene todas las filas de la tabla trelNotificacionEmpresa que coinciden con el criterio fkEmpresa='$fkEmpresa'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkEmpresa string Valor del campo fkEmpresa.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblEmpresa( $db, $fkEmpresa, $orderBy='' ){
         $sql = "SELECT * FROM trelNotificacionEmpresa WHERE fkEmpresa='$fkEmpresa'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelNotificacionEmpresa' );
     }

    /**
     * Obtiene todas las filas de la tabla trelNotificacionEmpresa que coinciden con el criterio fkNotificacion='$fkNotificacion'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkNotificacion string Valor del campo fkNotificacion.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblNotificacion( $db, $fkNotificacion, $orderBy='' ){
         $sql = "SELECT * FROM trelNotificacionEmpresa WHERE fkNotificacion='$fkNotificacion'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelNotificacionEmpresa' );
     }

    /**
     * Actualiza una fila de la tabla trelNotificacionEmpresa.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkEmpresa=' . ( ( ( $value = $this->fkEmpresa ) === null || !isset($this->fkEmpresa) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkNotificacion=' . ( ( ( $value = $this->fkNotificacion ) === null || !isset($this->fkNotificacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelNotificacionEmpresa SET $setStr WHERE fkEmpresa='".addslashes($this->_data['fkEmpresa'])."' AND fkNotificacion='".addslashes($this->_data['fkNotificacion'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelNotificacionEmpresa.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkEmpresa';
        $attributes[] = 'fkNotificacion';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkEmpresa ) === null || !isset($this->fkEmpresa) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkNotificacion ) === null || !isset($this->fkNotificacion) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelNotificacionEmpresa($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkEmpresa, $this->fkNotificacion );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelNotificacionEmpresa.
     */
    public function delete(){
        $where = array();
        $where[] = "fkEmpresa="."'".addslashes($this->fkEmpresa)."'";
        $where[] = "fkNotificacion="."'".addslashes($this->fkNotificacion)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelNotificacionEmpresa WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'fkEmpresa'.
      *
      * @return integer
      */
    public function getFkEmpresa(){
        return $this->fkEmpresa;
    }

    /**
      * Establece el valor del atributo 'fkEmpresa'.
      *
      * @param integer Valor.
      */
    public function setFkEmpresa( $value ){

        $this->fkEmpresa = $value;

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
     * Obtiene el objeto 'TblEmpresa' relacionado.
     *
     * @return TblEmpresa
     */
    public function getTblEmpresa(){
        require_once('TblEmpresa.inc');
        return TblEmpresa::findByPrimaryKey( $this->_db, $this->fkEmpresa );
    }

    /**
     * Asigna el objeto 'TblEmpresa' relacionado.
     *
     * @param TblEmpresa $dataObject
     */
    public function setTblEmpresa( $dataObject ){
        require_once('TblEmpresa.inc');
        $this->setFkEmpresa( $dataObject->getIdEmpresa() );
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