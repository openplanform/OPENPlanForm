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
require_once( 'TblAvatarSearch.inc' );
require_once( 'TblAvatarPK.inc' );

/**
 * Objeto para acceder a la tabla tblAvatar.
 *
 * @package dataAccess
 */
class TblAvatar extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idAvatar"
     * @var integer
     */
    public $idAvatar;

    /**
     * Atributo que representa el campo "fkUsuario"
     * @var integer
     */
    public $fkUsuario;

    /**
     * Atributo que representa el campo "vArchivo"
     * @var string
     */
    public $vArchivo;

    /**
     * Atributo que representa el campo "bActivo"
     * @var boolean
     */
    public $bActivo;

    /**
     * Atributo que representa el campo "iAncho"
     * @var integer
     */
    public $iAncho;

    /**
     * Atributo que representa el campo "iAlto"
     * @var integer
     */
    public $iAlto;

    /**
     * Atributo que representa el campo "vMime"
     * @var string
     */
    public $vMime;

    /**
     * Atributo que representa el campo "vTamano"
     * @var string
     */
    public $vTamano;

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
        $this->idAvatar = $data['idAvatar'];
        $this->fkUsuario = $data['fkUsuario'];
        $this->vArchivo = $data['vArchivo'];
        $this->bActivo = $data['bActivo'];
        $this->iAncho = $data['iAncho'];
        $this->iAlto = $data['iAlto'];
        $this->vMime = $data['vMime'];
        $this->vTamano = $data['vTamano'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblAvatar segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblAvatarSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblAvatar';
        $where = array();
        if( $tmp = $searchItem->idAvatar ){
            $where[] = "idAvatar='$tmp'";
        }
        if( $tmp = $searchItem->fkUsuario ){
            $where[] = "fkUsuario='$tmp'";
        }
        if( $tmp = $searchItem->vArchivo ){
            $where[] = "vArchivo='$tmp'";
        }
        if( $tmp = $searchItem->bActivo ){
            $where[] = "bActivo='$tmp'";
        }
        if( $tmp = $searchItem->iAncho ){
            $where[] = "iAncho='$tmp'";
        }
        if( $tmp = $searchItem->iAlto ){
            $where[] = "iAlto='$tmp'";
        }
        if( $tmp = $searchItem->vMime ){
            $where[] = "vMime='$tmp'";
        }
        if( $tmp = $searchItem->vTamano ){
            $where[] = "vTamano='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblAvatar' );
}

    /**
     * Obtiene todas las filas de la tabla tblAvatar.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblAvatar';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblAvatar' );
    }

    /**
     * Obtiene el elemento de la tabla tblAvatar que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idAvatar valor del campo 'idAvatar'.
     * @return TblAvatar
     */
    public static function findByPrimaryKey( $db, $idAvatar ){

       $db->executeQuery("SELECT * FROM tblAvatar WHERE idAvatar = '$idAvatar'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblAvatar');

    }

    /**
     * Obtiene el elemento de la tabla tblAvatar que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblAvatarPK $pk Objeto de la clave primaria.
     * @return TblAvatar
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idAvatar='".$pk->idAvatar."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblAvatar WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblAvatar');

    }

    /**
     * Obtiene todas las filas de la tabla tblAvatar que coinciden con el criterio fkUsuario='$fkUsuario'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkUsuario string Valor del campo fkUsuario.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblUsuario( $db, $fkUsuario, $orderBy='' ){
         $sql = "SELECT * FROM tblAvatar WHERE fkUsuario='$fkUsuario'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblAvatar' );
     }

    /**
     * Actualiza una fila de la tabla tblAvatar.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkUsuario=' . ( ( ( $value = $this->fkUsuario ) === null || !isset($this->fkUsuario) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vArchivo=' . ( ( ( $value = $this->vArchivo ) === null || !isset($this->vArchivo) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bActivo=' . ( ( ( $value = $this->bActivo ) === null || !isset($this->bActivo) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iAncho=' . ( ( ( $value = $this->iAncho ) === null || !isset($this->iAncho) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iAlto=' . ( ( ( $value = $this->iAlto ) === null || !isset($this->iAlto) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vMime=' . ( ( ( $value = $this->vMime ) === null || !isset($this->vMime) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vTamano=' . ( ( ( $value = $this->vTamano ) === null || !isset($this->vTamano) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblAvatar SET $setStr WHERE idAvatar='".addslashes($this->_data['idAvatar'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblAvatar.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkUsuario';
        $attributes[] = 'vArchivo';
        $attributes[] = 'bActivo';
        $attributes[] = 'iAncho';
        $attributes[] = 'iAlto';
        $attributes[] = 'vMime';
        $attributes[] = 'vTamano';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkUsuario ) === null || !isset($this->fkUsuario) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vArchivo ) === null || !isset($this->vArchivo) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bActivo ) === null || !isset($this->bActivo) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iAncho ) === null || !isset($this->iAncho) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iAlto ) === null || !isset($this->iAlto) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vMime ) === null || !isset($this->vMime) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vTamano ) === null || !isset($this->vTamano) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblAvatar($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblAvatar.
     */
    public function delete(){
        $where = array();
        $where[] = "idAvatar="."'".addslashes($this->idAvatar)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblAvatar WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idAvatar'.
      *
      * @return integer
      */
    public function getIdAvatar(){
        return $this->idAvatar;
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
      * Obtiene el valor del atributo 'vArchivo'.
      *
      * @return string
      */
    public function getVArchivo(){
        return $this->vArchivo;
    }

    /**
      * Establece el valor del atributo 'vArchivo'.
      *
      * @param string Valor.
      */
    public function setVArchivo( $value ){

        $this->vArchivo = $value;

    }

    /**
      * Obtiene el valor del atributo 'bActivo'.
      *
      * @return boolean
      */
    public function isBActivo(){
        return ($this->bActivo ? true : false);
    }

    /**
      * Establece el valor del atributo 'bActivo'.
      *
      * @param boolean Valor.
      */
    public function setBActivo( $value ){

        $this->bActivo = $value;

    }

    /**
      * Obtiene el valor del atributo 'iAncho'.
      *
      * @return integer
      */
    public function getIAncho(){
        return $this->iAncho;
    }

    /**
      * Establece el valor del atributo 'iAncho'.
      *
      * @param integer Valor.
      */
    public function setIAncho( $value ){

        $this->iAncho = $value;

    }

    /**
      * Obtiene el valor del atributo 'iAlto'.
      *
      * @return integer
      */
    public function getIAlto(){
        return $this->iAlto;
    }

    /**
      * Establece el valor del atributo 'iAlto'.
      *
      * @param integer Valor.
      */
    public function setIAlto( $value ){

        $this->iAlto = $value;

    }

    /**
      * Obtiene el valor del atributo 'vMime'.
      *
      * @return string
      */
    public function getVMime(){
        return $this->vMime;
    }

    /**
      * Establece el valor del atributo 'vMime'.
      *
      * @param string Valor.
      */
    public function setVMime( $value ){

        $this->vMime = $value;

    }

    /**
      * Obtiene el valor del atributo 'vTamano'.
      *
      * @return string
      */
    public function getVTamano(){
        return $this->vTamano;
    }

    /**
      * Establece el valor del atributo 'vTamano'.
      *
      * @param string Valor.
      */
    public function setVTamano( $value ){

        $this->vTamano = $value;

    }

    // Relaciones

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