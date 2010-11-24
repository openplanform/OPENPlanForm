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
require_once( 'TrelPersonaCarnetSearch.inc' );
require_once( 'TrelPersonaCarnetPK.inc' );

/**
 * Objeto para acceder a la tabla trelPersonaCarnet.
 *
 * @package dataAccess
 */
class TrelPersonaCarnet extends OwlGenericDO{

    /**
     * Atributo que representa el campo "fkPersona"
     * @var integer
     */
    public $fkPersona;

    /**
     * Atributo que representa el campo "fkCarnet"
     * @var integer
     */
    public $fkCarnet;

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
        $this->fkCarnet = $data['fkCarnet'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelPersonaCarnet segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelPersonaCarnetSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelPersonaCarnet';
        $where = array();
        if( $tmp = $searchItem->fkPersona ){
            $where[] = "fkPersona='$tmp'";
        }
        if( $tmp = $searchItem->fkCarnet ){
            $where[] = "fkCarnet='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TrelPersonaCarnet' );
}

    /**
     * Obtiene todas las filas de la tabla trelPersonaCarnet.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelPersonaCarnet';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelPersonaCarnet' );
    }

    /**
     * Obtiene el elemento de la tabla trelPersonaCarnet que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkPersona valor del campo 'fkPersona'.
     * @param integer $fkCarnet valor del campo 'fkCarnet'.
     * @return TrelPersonaCarnet
     */
    public static function findByPrimaryKey( $db, $fkPersona, $fkCarnet ){

       $db->executeQuery("SELECT * FROM trelPersonaCarnet WHERE fkPersona = '$fkPersona' AND fkCarnet = '$fkCarnet'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TrelPersonaCarnet');

    }

    /**
     * Obtiene el elemento de la tabla trelPersonaCarnet que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelPersonaCarnetPK $pk Objeto de la clave primaria.
     * @return TrelPersonaCarnet
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkPersona='".$pk->fkPersona."'";
        $where[]="fkCarnet='".$pk->fkCarnet."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelPersonaCarnet WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TrelPersonaCarnet');

    }

    /**
     * Obtiene todas las filas de la tabla trelPersonaCarnet que coinciden con el criterio fkCarnet='$fkCarnet'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCarnet string Valor del campo fkCarnet.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCarnetConducir( $db, $fkCarnet, $orderBy='' ){
         $sql = "SELECT * FROM trelPersonaCarnet WHERE fkCarnet='$fkCarnet'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelPersonaCarnet' );
     }

    /**
     * Obtiene todas las filas de la tabla trelPersonaCarnet que coinciden con el criterio fkPersona='$fkPersona'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPersona string Valor del campo fkPersona.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPersona( $db, $fkPersona, $orderBy='' ){
         $sql = "SELECT * FROM trelPersonaCarnet WHERE fkPersona='$fkPersona'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelPersonaCarnet' );
     }

    /**
     * Actualiza una fila de la tabla trelPersonaCarnet.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkPersona=' . ( ( ( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkCarnet=' . ( ( ( $value = $this->fkCarnet ) === null || !isset($this->fkCarnet) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelPersonaCarnet SET $setStr WHERE fkPersona='".addslashes($this->_data['fkPersona'])."' AND fkCarnet='".addslashes($this->_data['fkCarnet'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelPersonaCarnet.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkPersona';
        $attributes[] = 'fkCarnet';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkCarnet ) === null || !isset($this->fkCarnet) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelPersonaCarnet($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkPersona, $this->fkCarnet );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelPersonaCarnet.
     */
    public function delete(){
        $where = array();
        $where[] = "fkPersona="."'".addslashes($this->fkPersona)."'";
        $where[] = "fkCarnet="."'".addslashes($this->fkCarnet)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelPersonaCarnet WHERE $where");
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
      * Obtiene el valor del atributo 'fkCarnet'.
      *
      * @return integer
      */
    public function getFkCarnet(){
        return $this->fkCarnet;
    }

    /**
      * Establece el valor del atributo 'fkCarnet'.
      *
      * @param integer Valor.
      */
    public function setFkCarnet( $value ){

        $this->fkCarnet = $value;

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblCarnetConducir' relacionado.
     *
     * @return TblCarnetConducir
     */
    public function getTblCarnetConducir(){
        require_once('TblCarnetConducir.inc');
        return TblCarnetConducir::findByPrimaryKey( $this->_db, $this->fkCarnet );
    }

    /**
     * Asigna el objeto 'TblCarnetConducir' relacionado.
     *
     * @param TblCarnetConducir $dataObject
     */
    public function setTblCarnetConducir( $dataObject ){
        require_once('TblCarnetConducir.inc');
        $this->setFkCarnet( $dataObject->getIdCarnetConducir() );
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