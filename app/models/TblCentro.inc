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
require_once( 'TblCentroSearch.inc' );
require_once( 'TblCentroPK.inc' );

/**
 * Objeto para acceder a la tabla tblCentro.
 *
 * @package dataAccess
 */
class TblCentro extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idCentro"
     * @var integer
     */
    public $idCentro;

    /**
     * Atributo que representa el campo "fkProvincia"
     * @var integer
     */
    public $fkProvincia;

    /**
     * Atributo que representa el campo "fkPais"
     * @var string
     */
    public $fkPais;

    /**
     * Atributo que representa el campo "fkEmpresa"
     * @var integer
     */
    public $fkEmpresa;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

    /**
     * Atributo que representa el campo "vPoblacion"
     * @var string
     */
    public $vPoblacion;

    /**
     * Atributo que representa el campo "vTelefono"
     * @var string
     */
    public $vTelefono;

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
     * Atributo que representa el campo "vDireccion"
     * @var string
     */
    public $vDireccion;

    /**
     * Atributo que representa el campo "vDescripcion"
     * @var string
     */
    public $vDescripcion;

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
        $this->idCentro = $data['idCentro'];
        $this->fkProvincia = $data['fkProvincia'];
        $this->fkPais = $data['fkPais'];
        $this->fkEmpresa = $data['fkEmpresa'];
        $this->vNombre = $data['vNombre'];
        $this->vPoblacion = $data['vPoblacion'];
        $this->vTelefono = $data['vTelefono'];
        $this->vLatitud = $data['vLatitud'];
        $this->vLongitud = $data['vLongitud'];
        $this->vDireccion = $data['vDireccion'];
        $this->vDescripcion = $data['vDescripcion'];
        $this->modUser = $data['mod_user'];
        $this->lastModified = $data['last_modified'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblCentro segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblCentroSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblCentro';
        $where = array();
        if( $tmp = $searchItem->idCentro ){
            $where[] = "idCentro='$tmp'";
        }
        if( $tmp = $searchItem->fkProvincia ){
            $where[] = "fkProvincia='$tmp'";
        }
        if( $tmp = $searchItem->fkPais ){
            $where[] = "fkPais='$tmp'";
        }
        if( $tmp = $searchItem->fkEmpresa ){
            $where[] = "fkEmpresa='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->vPoblacion ){
            $where[] = "vPoblacion='$tmp'";
        }
        if( $tmp = $searchItem->vTelefono ){
            $where[] = "vTelefono='$tmp'";
        }
        if( $tmp = $searchItem->vLatitud ){
            $where[] = "vLatitud='$tmp'";
        }
        if( $tmp = $searchItem->vLongitud ){
            $where[] = "vLongitud='$tmp'";
        }
        if( $tmp = $searchItem->vDireccion ){
            $where[] = "vDireccion='$tmp'";
        }
        if( $tmp = $searchItem->vDescripcion ){
            $where[] = "vDescripcion='$tmp'";
        }
        if( $tmp = $searchItem->modUser ){
            $where[] = "mod_user='$tmp'";
        }
        if( $tmp = $searchItem->lastModified ){
            $where[] = "last_modified='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblCentro' );
}

    /**
     * Obtiene todas las filas de la tabla tblCentro.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblCentro';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblCentro' );
    }

    /**
     * Obtiene el elemento de la tabla tblCentro que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idCentro valor del campo 'idCentro'.
     * @return TblCentro
     */
    public static function findByPrimaryKey( $db, $idCentro ){

       $db->executeQuery("SELECT * FROM tblCentro WHERE idCentro = '$idCentro'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblCentro');

    }

    /**
     * Obtiene el elemento de la tabla tblCentro que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblCentroPK $pk Objeto de la clave primaria.
     * @return TblCentro
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idCentro='".$pk->idCentro."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblCentro WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblCentro');

    }

    /**
     * Obtiene todas las filas de la tabla tblCentro que coinciden con el criterio fkEmpresa='$fkEmpresa'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkEmpresa string Valor del campo fkEmpresa.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblEmpresa( $db, $fkEmpresa, $orderBy='' ){
         $sql = "SELECT * FROM tblCentro WHERE fkEmpresa='$fkEmpresa'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblCentro' );
     }

    /**
     * Obtiene todas las filas de la tabla tblCentro que coinciden con el criterio fkPais='$fkPais'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string fkPais string Valor del campo fkPais.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPais( $db, $fkPais, $orderBy='' ){
         $sql = "SELECT * FROM tblCentro WHERE fkPais='$fkPais'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblCentro' );
     }

    /**
     * Obtiene todas las filas de la tabla tblCentro que coinciden con el criterio fkProvincia='$fkProvincia'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkProvincia string Valor del campo fkProvincia.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblProvincia( $db, $fkProvincia, $orderBy='' ){
         $sql = "SELECT * FROM tblCentro WHERE fkProvincia='$fkProvincia'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblCentro' );
     }

    /**
     * Actualiza una fila de la tabla tblCentro.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkProvincia=' . ( ( ( $value = $this->fkProvincia ) === null || !isset($this->fkProvincia) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkPais=' . ( ( ( $value = $this->fkPais ) === null || !isset($this->fkPais) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkEmpresa=' . ( ( ( $value = $this->fkEmpresa ) === null || !isset($this->fkEmpresa) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vPoblacion=' . ( ( ( $value = $this->vPoblacion ) === null || !isset($this->vPoblacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vTelefono=' . ( ( ( $value = $this->vTelefono ) === null || !isset($this->vTelefono) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vLatitud=' . ( ( ( $value = $this->vLatitud ) === null || !isset($this->vLatitud) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vLongitud=' . ( ( ( $value = $this->vLongitud ) === null || !isset($this->vLongitud) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDireccion=' . ( ( ( $value = $this->vDireccion ) === null || !isset($this->vDireccion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'mod_user=' . ( ( ( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'last_modified=' . ( ( ( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblCentro SET $setStr WHERE idCentro='".addslashes($this->_data['idCentro'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblCentro.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkProvincia';
        $attributes[] = 'fkPais';
        $attributes[] = 'fkEmpresa';
        $attributes[] = 'vNombre';
        $attributes[] = 'vPoblacion';
        $attributes[] = 'vTelefono';
        $attributes[] = 'vLatitud';
        $attributes[] = 'vLongitud';
        $attributes[] = 'vDireccion';
        $attributes[] = 'vDescripcion';
        $attributes[] = 'mod_user';
        $attributes[] = 'last_modified';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkProvincia ) === null || !isset($this->fkProvincia) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkPais ) === null || !isset($this->fkPais) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkEmpresa ) === null || !isset($this->fkEmpresa) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vPoblacion ) === null || !isset($this->vPoblacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vTelefono ) === null || !isset($this->vTelefono) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vLatitud ) === null || !isset($this->vLatitud) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vLongitud ) === null || !isset($this->vLongitud) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDireccion ) === null || !isset($this->vDireccion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblCentro($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblCentro.
     */
    public function delete(){
        $where = array();
        $where[] = "idCentro="."'".addslashes($this->idCentro)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblCentro WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idCentro'.
      *
      * @return integer
      */
    public function getIdCentro(){
        return $this->idCentro;
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
      * Obtiene el valor del atributo 'vDescripcion'.
      *
      * @return string
      */
    public function getVDescripcion(){
        return $this->vDescripcion;
    }

    /**
      * Establece el valor del atributo 'vDescripcion'.
      *
      * @param string Valor.
      */
    public function setVDescripcion( $value ){

        $this->vDescripcion = $value;

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
     * Obtiene todos los elementos relacionados de la tabla 'tblAula'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblAulas( $orderBy='' ){

        include_once('TblAula.inc');
        return TblAula::findByTblCentro( $this->_db, $this->idCentro, $orderBy );

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
}
?>