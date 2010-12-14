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
require_once( 'TrelRolUsuarioSearch.inc' );
require_once( 'TrelRolUsuarioPK.inc' );

/**
 * Objeto para acceder a la tabla trelRolUsuario.
 *
 * @package dataAccess
 */
class TrelRolUsuario extends OwlGenericDO{

    /**
     * Atributo que representa el campo "fkUsuario"
     * @var integer
     */
    public $fkUsuario;

    /**
     * Atributo que representa el campo "fkRol"
     * @var integer
     */
    public $fkRol;

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
        $this->fkUsuario = $data['fkUsuario'];
        $this->fkRol = $data['fkRol'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelRolUsuario segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelRolUsuarioSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelRolUsuario';
        $where = array();
        if( $tmp = $searchItem->fkUsuario ){
            $where[] = "fkUsuario='$tmp'";
        }
        if( $tmp = $searchItem->fkRol ){
            $where[] = "fkRol='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TrelRolUsuario' );
}

    /**
     * Obtiene todas las filas de la tabla trelRolUsuario.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelRolUsuario';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelRolUsuario' );
    }

    /**
     * Obtiene el elemento de la tabla trelRolUsuario que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkUsuario valor del campo 'fkUsuario'.
     * @param integer $fkRol valor del campo 'fkRol'.
     * @return TrelRolUsuario
     */
    public static function findByPrimaryKey( $db, $fkUsuario, $fkRol ){

       $db->executeQuery("SELECT * FROM trelRolUsuario WHERE fkUsuario = '$fkUsuario' AND fkRol = '$fkRol'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TrelRolUsuario');

    }

    /**
     * Obtiene el elemento de la tabla trelRolUsuario que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelRolUsuarioPK $pk Objeto de la clave primaria.
     * @return TrelRolUsuario
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkUsuario='".$pk->fkUsuario."'";
        $where[]="fkRol='".$pk->fkRol."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelRolUsuario WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TrelRolUsuario');

    }

    /**
     * Obtiene todas las filas de la tabla trelRolUsuario que coinciden con el criterio fkRol='$fkRol'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkRol string Valor del campo fkRol.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblRol( $db, $fkRol, $orderBy='' ){
         $sql = "SELECT * FROM trelRolUsuario WHERE fkRol='$fkRol'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelRolUsuario' );
     }

    /**
     * Obtiene todas las filas de la tabla trelRolUsuario que coinciden con el criterio fkUsuario='$fkUsuario'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkUsuario string Valor del campo fkUsuario.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblUsuario( $db, $fkUsuario, $orderBy='' ){
         $sql = "SELECT * FROM trelRolUsuario WHERE fkUsuario='$fkUsuario'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelRolUsuario' );
     }

    /**
     * Actualiza una fila de la tabla trelRolUsuario.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkUsuario=' . ( ( ( $value = $this->fkUsuario ) === null || !isset($this->fkUsuario) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkRol=' . ( ( ( $value = $this->fkRol ) === null || !isset($this->fkRol) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelRolUsuario SET $setStr WHERE fkUsuario='".addslashes($this->_data['fkUsuario'])."' AND fkRol='".addslashes($this->_data['fkRol'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelRolUsuario.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkUsuario';
        $attributes[] = 'fkRol';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkUsuario ) === null || !isset($this->fkUsuario) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkRol ) === null || !isset($this->fkRol) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelRolUsuario($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkUsuario, $this->fkRol );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelRolUsuario.
     */
    public function delete(){
        $where = array();
        $where[] = "fkUsuario="."'".addslashes($this->fkUsuario)."'";
        $where[] = "fkRol="."'".addslashes($this->fkRol)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelRolUsuario WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'fkUsuario'.
      *
      * @return integer
      */
    public function getFkUsuario(){
        return $this->fkUsuario;
    }

    /**
      * Establece el valor del atributo 'fkUsuario'.
      *
      * @param integer Valor.
      */
    public function setFkUsuario( $value ){

        $this->fkUsuario = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkRol'.
      *
      * @return integer
      */
    public function getFkRol(){
        return $this->fkRol;
    }

    /**
      * Establece el valor del atributo 'fkRol'.
      *
      * @param integer Valor.
      */
    public function setFkRol( $value ){

        $this->fkRol = $value;

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblRol' relacionado.
     *
     * @return TblRol
     */
    public function getTblRol(){
        require_once('TblRol.inc');
        return TblRol::findByPrimaryKey( $this->_db, $this->fkRol );
    }

    /**
     * Asigna el objeto 'TblRol' relacionado.
     *
     * @param TblRol $dataObject
     */
    public function setTblRol( $dataObject ){
        require_once('TblRol.inc');
        $this->setFkRol( $dataObject->getIdRol() );
    }

    /**
     * Obtiene el objeto 'TblUsuario' relacionado.
     *
     * @return TblUsuario
     */
    public function getTblUsuario(){
        require_once('TblUsuario.inc');
        return TblUsuario::findByPrimaryKey( $this->_db, $this->fkUsuario );
    }

    /**
     * Asigna el objeto 'TblUsuario' relacionado.
     *
     * @param TblUsuario $dataObject
     */
    public function setTblUsuario( $dataObject ){
        require_once('TblUsuario.inc');
        $this->setFkUsuario( $dataObject->getIdUsuario() );
    }
}
?>