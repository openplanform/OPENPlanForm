<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 17 de December de 2010 a las 09:57:03
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TblEmpresaSearch.inc' );
require_once( 'TblEmpresaPK.inc' );

/**
 * Objeto para acceder a la tabla tblEmpresa.
 *
 * @package dataAccess
 */
class TblEmpresa extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idEmpresa"
     * @var integer
     */
    public $idEmpresa;

    /**
     * Atributo que representa el campo "fkPais"
     * @var string
     */
    public $fkPais;

    /**
     * Atributo que representa el campo "fkProvincia"
     * @var integer
     */
    public $fkProvincia;

    /**
     * Atributo que representa el campo "fkUsuario"
     * @var integer
     */
    public $fkUsuario;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

    /**
     * Atributo que representa el campo "vCif"
     * @var string
     */
    public $vCif;

    /**
     * Atributo que representa el campo "vPoblacion"
     * @var string
     */
    public $vPoblacion;

    /**
     * Atributo que representa el campo "vDireccion"
     * @var string
     */
    public $vDireccion;

    /**
     * Atributo que representa el campo "vCp"
     * @var string
     */
    public $vCp;

    /**
     * Atributo que representa el campo "vLatitud"
     * @var string
     */
    public $vLatitud;

    /**
     * Atributo que representa el campo "vLongitud"
     * @var string
     */
    public $vLongitud;

    /**
     * Atributo que representa el campo "vTelefono"
     * @var string
     */
    public $vTelefono;

    /**
     * Atributo que representa el campo "vTelefono2"
     * @var string
     */
    public $vTelefono2;

    /**
     * Atributo que representa el campo "vFax"
     * @var string
     */
    public $vFax;

    /**
     * Atributo que representa el campo "bActiva"
     * @var boolean
     */
    public $bActiva;

    /**
     * Atributo que representa el campo "dAlta"
     * @var string
     */
    public $dAlta;

    /**
     * Atributo que representa el campo "dBaja"
     * @var string
     */
    public $dBaja;

    /**
     * Atributo que representa el campo "mod_user"
     * @var string
     */
    public $modUser;

    /**
     * Atributo que representa el campo "last_modified"
     * @var string
     */
    public $lastModified;

    /**
     * Atributo que representa el campo "vPersonaContacto"
     * @var string
     */
    public $vPersonaContacto;

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
        $this->idEmpresa = $data['idEmpresa'];
        $this->fkPais = $data['fkPais'];
        $this->fkProvincia = $data['fkProvincia'];
        $this->fkUsuario = $data['fkUsuario'];
        $this->vNombre = $data['vNombre'];
        $this->vCif = $data['vCif'];
        $this->vPoblacion = $data['vPoblacion'];
        $this->vDireccion = $data['vDireccion'];
        $this->vCp = $data['vCp'];
        $this->vLatitud = $data['vLatitud'];
        $this->vLongitud = $data['vLongitud'];
        $this->vTelefono = $data['vTelefono'];
        $this->vTelefono2 = $data['vTelefono2'];
        $this->vFax = $data['vFax'];
        $this->bActiva = $data['bActiva'];
        $this->dAlta = $data['dAlta'];
        $this->dBaja = $data['dBaja'];
        $this->modUser = $data['mod_user'];
        $this->lastModified = $data['last_modified'];
        $this->vPersonaContacto = $data['vPersonaContacto'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblEmpresa segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblEmpresaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblEmpresa';
        $where = array();
        if( $tmp = $searchItem->idEmpresa ){
            $where[] = "idEmpresa='$tmp'";
        }
        if( $tmp = $searchItem->fkPais ){
            $where[] = "fkPais='$tmp'";
        }
        if( $tmp = $searchItem->fkProvincia ){
            $where[] = "fkProvincia='$tmp'";
        }
        if( $tmp = $searchItem->fkUsuario ){
            $where[] = "fkUsuario='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->vCif ){
            $where[] = "vCif='$tmp'";
        }
        if( $tmp = $searchItem->vPoblacion ){
            $where[] = "vPoblacion='$tmp'";
        }
        if( $tmp = $searchItem->vDireccion ){
            $where[] = "vDireccion='$tmp'";
        }
        if( $tmp = $searchItem->vCp ){
            $where[] = "vCp='$tmp'";
        }
        if( $tmp = $searchItem->vLatitud ){
            $where[] = "vLatitud='$tmp'";
        }
        if( $tmp = $searchItem->vLongitud ){
            $where[] = "vLongitud='$tmp'";
        }
        if( $tmp = $searchItem->vTelefono ){
            $where[] = "vTelefono='$tmp'";
        }
        if( $tmp = $searchItem->vTelefono2 ){
            $where[] = "vTelefono2='$tmp'";
        }
        if( $tmp = $searchItem->vFax ){
            $where[] = "vFax='$tmp'";
        }
        if( $tmp = $searchItem->bActiva ){
            $where[] = "bActiva='$tmp'";
        }
        if( $tmp = $searchItem->dAlta ){
            $where[] = "dAlta='$tmp'";
        }
        if( $tmp = $searchItem->dBaja ){
            $where[] = "dBaja='$tmp'";
        }
        if( $tmp = $searchItem->modUser ){
            $where[] = "mod_user='$tmp'";
        }
        if( $tmp = $searchItem->lastModified ){
            $where[] = "last_modified='$tmp'";
        }
        if( $tmp = $searchItem->vPersonaContacto ){
            $where[] = "vPersonaContacto='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblEmpresa' );
}

    /**
     * Obtiene todas las filas de la tabla tblEmpresa.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblEmpresa';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblEmpresa' );
    }

    /**
     * Obtiene el elemento de la tabla tblEmpresa que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idEmpresa valor del campo 'idEmpresa'.
     * @return TblEmpresa
     */
    public static function findByPrimaryKey( $db, $idEmpresa ){

       $db->executeQuery("SELECT * FROM tblEmpresa WHERE idEmpresa = '$idEmpresa'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblEmpresa');

    }

    /**
     * Obtiene el elemento de la tabla tblEmpresa que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblEmpresaPK $pk Objeto de la clave primaria.
     * @return TblEmpresa
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idEmpresa='".$pk->idEmpresa."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblEmpresa WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblEmpresa');

    }

    /**
     * Obtiene todas las filas de la tabla tblEmpresa que coinciden con el criterio fkPais='$fkPais'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string fkPais string Valor del campo fkPais.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPais( $db, $fkPais, $orderBy='' ){
         $sql = "SELECT * FROM tblEmpresa WHERE fkPais='$fkPais'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblEmpresa' );
     }

    /**
     * Obtiene todas las filas de la tabla tblEmpresa que coinciden con el criterio fkProvincia='$fkProvincia'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkProvincia string Valor del campo fkProvincia.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblProvincia( $db, $fkProvincia, $orderBy='' ){
         $sql = "SELECT * FROM tblEmpresa WHERE fkProvincia='$fkProvincia'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblEmpresa' );
     }

    /**
     * Obtiene todas las filas de la tabla tblEmpresa que coinciden con el criterio fkUsuario='$fkUsuario'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkUsuario string Valor del campo fkUsuario.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblUsuario( $db, $fkUsuario, $orderBy='' ){
         $sql = "SELECT * FROM tblEmpresa WHERE fkUsuario='$fkUsuario'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblEmpresa' );
     }

    /**
     * Actualiza una fila de la tabla tblEmpresa.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkPais=' . ( ( ( $value = $this->fkPais ) === null || !isset($this->fkPais) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkProvincia=' . ( ( ( $value = $this->fkProvincia ) === null || !isset($this->fkProvincia) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkUsuario=' . ( ( ( $value = $this->fkUsuario ) === null || !isset($this->fkUsuario) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vCif=' . ( ( ( $value = $this->vCif ) === null || !isset($this->vCif) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vPoblacion=' . ( ( ( $value = $this->vPoblacion ) === null || !isset($this->vPoblacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDireccion=' . ( ( ( $value = $this->vDireccion ) === null || !isset($this->vDireccion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vCp=' . ( ( ( $value = $this->vCp ) === null || !isset($this->vCp) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vLatitud=' . ( ( ( $value = $this->vLatitud ) === null || !isset($this->vLatitud) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vLongitud=' . ( ( ( $value = $this->vLongitud ) === null || !isset($this->vLongitud) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vTelefono=' . ( ( ( $value = $this->vTelefono ) === null || !isset($this->vTelefono) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vTelefono2=' . ( ( ( $value = $this->vTelefono2 ) === null || !isset($this->vTelefono2) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vFax=' . ( ( ( $value = $this->vFax ) === null || !isset($this->vFax) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bActiva=' . ( ( ( $value = $this->bActiva ) === null || !isset($this->bActiva) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dAlta=' . ( ( ( $value = $this->dAlta ) === null || !isset($this->dAlta) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dBaja=' . ( ( ( $value = $this->dBaja ) === null || !isset($this->dBaja) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'mod_user=' . ( ( ( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'last_modified=' . ( ( ( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vPersonaContacto=' . ( ( ( $value = $this->vPersonaContacto ) === null || !isset($this->vPersonaContacto) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblEmpresa SET $setStr WHERE idEmpresa='".addslashes($this->_data['idEmpresa'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblEmpresa.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkPais';
        $attributes[] = 'fkProvincia';
        $attributes[] = 'fkUsuario';
        $attributes[] = 'vNombre';
        $attributes[] = 'vCif';
        $attributes[] = 'vPoblacion';
        $attributes[] = 'vDireccion';
        $attributes[] = 'vCp';
        $attributes[] = 'vLatitud';
        $attributes[] = 'vLongitud';
        $attributes[] = 'vTelefono';
        $attributes[] = 'vTelefono2';
        $attributes[] = 'vFax';
        $attributes[] = 'bActiva';
        $attributes[] = 'dAlta';
        $attributes[] = 'dBaja';
        $attributes[] = 'mod_user';
        $attributes[] = 'last_modified';
        $attributes[] = 'vPersonaContacto';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkPais ) === null || !isset($this->fkPais) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkProvincia ) === null || !isset($this->fkProvincia) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkUsuario ) === null || !isset($this->fkUsuario) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vCif ) === null || !isset($this->vCif) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vPoblacion ) === null || !isset($this->vPoblacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDireccion ) === null || !isset($this->vDireccion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vCp ) === null || !isset($this->vCp) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vLatitud ) === null || !isset($this->vLatitud) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vLongitud ) === null || !isset($this->vLongitud) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vTelefono ) === null || !isset($this->vTelefono) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vTelefono2 ) === null || !isset($this->vTelefono2) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vFax ) === null || !isset($this->vFax) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bActiva ) === null || !isset($this->bActiva) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dAlta ) === null || !isset($this->dAlta) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dBaja ) === null || !isset($this->dBaja) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vPersonaContacto ) === null || !isset($this->vPersonaContacto) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblEmpresa($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblEmpresa.
     */
    public function delete(){
        $where = array();
        $where[] = "idEmpresa="."'".addslashes($this->idEmpresa)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblEmpresa WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idEmpresa'.
      *
      * @return integer
      */
    public function getIdEmpresa(){
        return $this->idEmpresa;
    }

    /**
      * Obtiene el valor del atributo 'fkPais'.
      *
      * @return string
      */
    public function getFkPais(){
        return $this->fkPais;
    }

    /**
      * Establece el valor del atributo 'fkPais'.
      *
      * @param string Valor.
      */
    public function setFkPais( $value ){

        $this->fkPais = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkProvincia'.
      *
      * @return integer
      */
    public function getFkProvincia(){
        return $this->fkProvincia;
    }

    /**
      * Establece el valor del atributo 'fkProvincia'.
      *
      * @param integer Valor.
      */
    public function setFkProvincia( $value ){

        $this->fkProvincia = $value;

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
      * Obtiene el valor del atributo 'vCif'.
      *
      * @return string
      */
    public function getVCif(){
        return $this->vCif;
    }

    /**
      * Establece el valor del atributo 'vCif'.
      *
      * @param string Valor.
      */
    public function setVCif( $value ){

        $this->vCif = $value;

    }

    /**
      * Obtiene el valor del atributo 'vPoblacion'.
      *
      * @return string
      */
    public function getVPoblacion(){
        return $this->vPoblacion;
    }

    /**
      * Establece el valor del atributo 'vPoblacion'.
      *
      * @param string Valor.
      */
    public function setVPoblacion( $value ){

        $this->vPoblacion = $value;

    }

    /**
      * Obtiene el valor del atributo 'vDireccion'.
      *
      * @return string
      */
    public function getVDireccion(){
        return $this->vDireccion;
    }

    /**
      * Establece el valor del atributo 'vDireccion'.
      *
      * @param string Valor.
      */
    public function setVDireccion( $value ){

        $this->vDireccion = $value;

    }

    /**
      * Obtiene el valor del atributo 'vCp'.
      *
      * @return string
      */
    public function getVCp(){
        return $this->vCp;
    }

    /**
      * Establece el valor del atributo 'vCp'.
      *
      * @param string Valor.
      */
    public function setVCp( $value ){

        $this->vCp = $value;

    }

    /**
      * Obtiene el valor del atributo 'vLatitud'.
      *
      * @return string
      */
    public function getVLatitud(){
        return $this->vLatitud;
    }

    /**
      * Establece el valor del atributo 'vLatitud'.
      *
      * @param string Valor.
      */
    public function setVLatitud( $value ){

        $this->vLatitud = $value;

    }

    /**
      * Obtiene el valor del atributo 'vLongitud'.
      *
      * @return string
      */
    public function getVLongitud(){
        return $this->vLongitud;
    }

    /**
      * Establece el valor del atributo 'vLongitud'.
      *
      * @param string Valor.
      */
    public function setVLongitud( $value ){

        $this->vLongitud = $value;

    }

    /**
      * Obtiene el valor del atributo 'vTelefono'.
      *
      * @return string
      */
    public function getVTelefono(){
        return $this->vTelefono;
    }

    /**
      * Establece el valor del atributo 'vTelefono'.
      *
      * @param string Valor.
      */
    public function setVTelefono( $value ){

        $this->vTelefono = $value;

    }

    /**
      * Obtiene el valor del atributo 'vTelefono2'.
      *
      * @return string
      */
    public function getVTelefono2(){
        return $this->vTelefono2;
    }

    /**
      * Establece el valor del atributo 'vTelefono2'.
      *
      * @param string Valor.
      */
    public function setVTelefono2( $value ){

        $this->vTelefono2 = $value;

    }

    /**
      * Obtiene el valor del atributo 'vFax'.
      *
      * @return string
      */
    public function getVFax(){
        return $this->vFax;
    }

    /**
      * Establece el valor del atributo 'vFax'.
      *
      * @param string Valor.
      */
    public function setVFax( $value ){

        $this->vFax = $value;

    }

    /**
      * Obtiene el valor del atributo 'bActiva'.
      *
      * @return boolean
      */
    public function isBActiva(){
        return ($this->bActiva ? true : false);
    }

    /**
      * Establece el valor del atributo 'bActiva'.
      *
      * @param boolean Valor.
      */
    public function setBActiva( $value ){

        $this->bActiva = $value;

    }

    /**
      * Obtiene el valor del atributo 'dAlta'.
      *
      * @return string
      */
    public function getDAlta(){
        return $this->dAlta;
    }

    /**
      * Establece el valor del atributo 'dAlta'.
      *
      * @param string Valor.
      */
    public function setDAlta( $value ){

        $this->dAlta = $value;

    }

    /**
      * Obtiene el valor del atributo 'dBaja'.
      *
      * @return string
      */
    public function getDBaja(){
        return $this->dBaja;
    }

    /**
      * Establece el valor del atributo 'dBaja'.
      *
      * @param string Valor.
      */
    public function setDBaja( $value ){

        $this->dBaja = $value;

    }

    /**
      * Obtiene el valor del atributo 'mod_user'.
      *
      * @return string
      */
    public function getModUser(){
        return $this->modUser;
    }

    /**
      * Establece el valor del atributo 'mod_user'.
      *
      * @param string Valor.
      */
    public function setModUser( $value ){

        $this->modUser = $value;

    }

    /**
      * Obtiene el valor del atributo 'last_modified'.
      *
      * @return string
      */
    public function getLastModified(){
        return $this->lastModified;
    }

    /**
      * Establece el valor del atributo 'last_modified'.
      *
      * @param string Valor.
      */
    public function setLastModified( $value ){

        $this->lastModified = $value;

    }

    /**
      * Obtiene el valor del atributo 'vPersonaContacto'.
      *
      * @return string
      */
    public function getVPersonaContacto(){
        return $this->vPersonaContacto;
    }

    /**
      * Establece el valor del atributo 'vPersonaContacto'.
      *
      * @param string Valor.
      */
    public function setVPersonaContacto( $value ){

        $this->vPersonaContacto = $value;

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblCentro'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblCentros( $orderBy='' ){

        include_once('TblCentro.inc');
        return TblCentro::findByTblEmpresa( $this->_db, $this->idEmpresa, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblPlan'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPlanConsultora( $orderBy='' ){

        include_once('TblPlan.inc');
        return TblPlan::findByTblEmpresaConsultora( $this->_db, $this->idEmpresa, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblPlan'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPlanPropietaria( $orderBy='' ){

        include_once('TblPlan.inc');
        return TblPlan::findByTblEmpresaPropietaria( $this->_db, $this->idEmpresa, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelNotificacionEmpresa'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelNotificacionEmpresas( $orderBy='' ){

        include_once('TrelNotificacionEmpresa.inc');
        return TrelNotificacionEmpresa::findByTblEmpresa( $this->_db, $this->idEmpresa, $orderBy );

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblPais' relacionado.
     *
     * @return TblPais
     */
    public function getTblPais(){
        require_once('TblPais.inc');
        return TblPais::findByPrimaryKey( $this->_db, $this->fkPais );
    }

    /**
     * Asigna el objeto 'TblPais' relacionado.
     *
     * @param TblPais $dataObject
     */
    public function setTblPais( $dataObject ){
        require_once('TblPais.inc');
        $this->setFkPais( $dataObject->getVIso() );
    }

    /**
     * Obtiene el objeto 'TblProvincia' relacionado.
     *
     * @return TblProvincia
     */
    public function getTblProvincia(){
        require_once('TblProvincia.inc');
        return TblProvincia::findByPrimaryKey( $this->_db, $this->fkProvincia );
    }

    /**
     * Asigna el objeto 'TblProvincia' relacionado.
     *
     * @param TblProvincia $dataObject
     */
    public function setTblProvincia( $dataObject ){
        require_once('TblProvincia.inc');
        $this->setFkProvincia( $dataObject->getIdProvincia() );
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