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
require_once( 'TblUsuarioSearch.inc' );
require_once( 'TblUsuarioPK.inc' );

/**
 * Objeto para acceder a la tabla tblUsuario.
 *
 * @package dataAccess
 */
class TblUsuario extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idUsuario"
     * @var integer
     */
    public $idUsuario;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

    /**
     * Atributo que representa el campo "vPassword"
     * @var string
     */
    public $vPassword;

    /**
     * Atributo que representa el campo "vEmail"
     * @var string
     */
    public $vEmail;

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
        $this->idUsuario = $data['idUsuario'];
        $this->vNombre = $data['vNombre'];
        $this->vPassword = $data['vPassword'];
        $this->vEmail = $data['vEmail'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblUsuario segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblUsuarioSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblUsuario';
        $where = array();
        if( $tmp = $searchItem->idUsuario ){
            $where[] = "idUsuario='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->vPassword ){
            $where[] = "vPassword='$tmp'";
        }
        if( $tmp = $searchItem->vEmail ){
            $where[] = "vEmail='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblUsuario' );
}

    /**
     * Obtiene todas las filas de la tabla tblUsuario.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblUsuario';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblUsuario' );
    }

    /**
     * Obtiene el elemento de la tabla tblUsuario que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idUsuario valor del campo 'idUsuario'.
     * @return TblUsuario
     */
    public static function findByPrimaryKey( $db, $idUsuario ){

       $db->executeQuery("SELECT * FROM tblUsuario WHERE idUsuario = '$idUsuario'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblUsuario');

    }

    /**
     * Obtiene el elemento de la tabla tblUsuario que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblUsuarioPK $pk Objeto de la clave primaria.
     * @return TblUsuario
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idUsuario='".$pk->idUsuario."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblUsuario WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblUsuario');

    }

    /**
     * Actualiza una fila de la tabla tblUsuario.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vPassword=' . ( ( ( $value = $this->vPassword ) === null || !isset($this->vPassword) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vEmail=' . ( ( ( $value = $this->vEmail ) === null || !isset($this->vEmail) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblUsuario SET $setStr WHERE idUsuario='".addslashes($this->_data['idUsuario'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblUsuario.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vNombre';
        $attributes[] = 'vPassword';
        $attributes[] = 'vEmail';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vPassword ) === null || !isset($this->vPassword) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vEmail ) === null || !isset($this->vEmail) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblUsuario($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblUsuario.
     */
    public function delete(){
        $where = array();
        $where[] = "idUsuario="."'".addslashes($this->idUsuario)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblUsuario WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idUsuario'.
      *
      * @return integer
      */
    public function getIdUsuario(){
        return $this->idUsuario;
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
      * Obtiene el valor del atributo 'vPassword'.
      *
      * @return string
      */
    public function getVPassword(){
        return $this->vPassword;
    }

    /**
      * Establece el valor del atributo 'vPassword'.
      *
      * @param string Valor.
      */
    public function setVPassword( $value ){

        $this->vPassword = $value;

    }

    /**
      * Obtiene el valor del atributo 'vEmail'.
      *
      * @return string
      */
    public function getVEmail(){
        return $this->vEmail;
    }

    /**
      * Establece el valor del atributo 'vEmail'.
      *
      * @param string Valor.
      */
    public function setVEmail( $value ){

        $this->vEmail = $value;

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblAvatar'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblAvatars( $orderBy='' ){

        include_once('TblAvatar.inc');
        return TblAvatar::findByTblUsuario( $this->_db, $this->idUsuario, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblEmpresa'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblEmpresas( $orderBy='' ){

        include_once('TblEmpresa.inc');
        return TblEmpresa::findByTblUsuario( $this->_db, $this->idUsuario, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblPersona'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPersonas( $orderBy='' ){

        include_once('TblPersona.inc');
        return TblPersona::findByTblUsuario( $this->_db, $this->idUsuario, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelRolUsuario'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelRolUsuarios( $orderBy='' ){

        include_once('TrelRolUsuario.inc');
        return TrelRolUsuario::findByTblUsuario( $this->_db, $this->idUsuario, $orderBy );

    }
}
?>