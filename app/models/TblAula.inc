<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 24 de November de 2010 a las 08:55:32
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TblAulaSearch.inc' );
require_once( 'TblAulaPK.inc' );

/**
 * Objeto para acceder a la tabla tblAula.
 *
 * @package dataAccess
 */
class TblAula extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idAula"
     * @var integer
     */
    public $idAula;

    /**
     * Atributo que representa el campo "fkCentro"
     * @var integer
     */
    public $fkCentro;

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
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

    /**
     * Atributo que representa el campo "iCapacidad"
     * @var integer
     */
    public $iCapacidad;

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
     * Atributo que representa el campo "vPoblacion"
     * @var string
     */
    public $vPoblacion;

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
        $this->idAula = $data['idAula'];
        $this->fkCentro = $data['fkCentro'];
        $this->fkProvincia = $data['fkProvincia'];
        $this->fkPais = $data['fkPais'];
        $this->vNombre = $data['vNombre'];
        $this->iCapacidad = $data['iCapacidad'];
        $this->vDireccion = $data['vDireccion'];
        $this->vDescripcion = $data['vDescripcion'];
        $this->vPoblacion = $data['vPoblacion'];
        $this->modUser = $data['mod_user'];
        $this->lastModified = $data['last_modified'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblAula segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblAulaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblAula';
        $where = array();
        if( $tmp = $searchItem->idAula ){
            $where[] = "idAula='$tmp'";
        }
        if( $tmp = $searchItem->fkCentro ){
            $where[] = "fkCentro='$tmp'";
        }
        if( $tmp = $searchItem->fkProvincia ){
            $where[] = "fkProvincia='$tmp'";
        }
        if( $tmp = $searchItem->fkPais ){
            $where[] = "fkPais='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->iCapacidad ){
            $where[] = "iCapacidad='$tmp'";
        }
        if( $tmp = $searchItem->vDireccion ){
            $where[] = "vDireccion='$tmp'";
        }
        if( $tmp = $searchItem->vDescripcion ){
            $where[] = "vDescripcion='$tmp'";
        }
        if( $tmp = $searchItem->vPoblacion ){
            $where[] = "vPoblacion='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TblAula' );
}

    /**
     * Obtiene todas las filas de la tabla tblAula.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblAula';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblAula' );
    }

    /**
     * Obtiene el elemento de la tabla tblAula que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idAula valor del campo 'idAula'.
     * @return TblAula
     */
    public static function findByPrimaryKey( $db, $idAula ){

       $db->executeQuery("SELECT * FROM tblAula WHERE idAula = '$idAula'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblAula');

    }

    /**
     * Obtiene el elemento de la tabla tblAula que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblAulaPK $pk Objeto de la clave primaria.
     * @return TblAula
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idAula='".$pk->idAula."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblAula WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblAula');

    }

    /**
     * Obtiene todas las filas de la tabla tblAula que coinciden con el criterio fkCentro='$fkCentro'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCentro string Valor del campo fkCentro.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCentro( $db, $fkCentro, $orderBy='' ){
         $sql = "SELECT * FROM tblAula WHERE fkCentro='$fkCentro'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblAula' );
     }

    /**
     * Obtiene todas las filas de la tabla tblAula que coinciden con el criterio fkPais='$fkPais'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string fkPais string Valor del campo fkPais.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPais( $db, $fkPais, $orderBy='' ){
         $sql = "SELECT * FROM tblAula WHERE fkPais='$fkPais'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblAula' );
     }

    /**
     * Obtiene todas las filas de la tabla tblAula que coinciden con el criterio fkProvincia='$fkProvincia'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkProvincia string Valor del campo fkProvincia.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblProvincia( $db, $fkProvincia, $orderBy='' ){
         $sql = "SELECT * FROM tblAula WHERE fkProvincia='$fkProvincia'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblAula' );
     }

    /**
     * Actualiza una fila de la tabla tblAula.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkCentro=' . ( ( ( $value = $this->fkCentro ) === null || !isset($this->fkCentro) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkProvincia=' . ( ( ( $value = $this->fkProvincia ) === null || !isset($this->fkProvincia) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkPais=' . ( ( ( $value = $this->fkPais ) === null || !isset($this->fkPais) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iCapacidad=' . ( ( ( $value = $this->iCapacidad ) === null || !isset($this->iCapacidad) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDireccion=' . ( ( ( $value = $this->vDireccion ) === null || !isset($this->vDireccion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vPoblacion=' . ( ( ( $value = $this->vPoblacion ) === null || !isset($this->vPoblacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'mod_user=' . ( ( ( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'last_modified=' . ( ( ( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblAula SET $setStr WHERE idAula='".addslashes($this->_data['idAula'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblAula.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkCentro';
        $attributes[] = 'fkProvincia';
        $attributes[] = 'fkPais';
        $attributes[] = 'vNombre';
        $attributes[] = 'iCapacidad';
        $attributes[] = 'vDireccion';
        $attributes[] = 'vDescripcion';
        $attributes[] = 'vPoblacion';
        $attributes[] = 'mod_user';
        $attributes[] = 'last_modified';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkCentro ) === null || !isset($this->fkCentro) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkProvincia ) === null || !isset($this->fkProvincia) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkPais ) === null || !isset($this->fkPais) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iCapacidad ) === null || !isset($this->iCapacidad) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDireccion ) === null || !isset($this->vDireccion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vPoblacion ) === null || !isset($this->vPoblacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblAula($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblAula.
     */
    public function delete(){
        $where = array();
        $where[] = "idAula="."'".addslashes($this->idAula)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblAula WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idAula'.
      *
      * @return integer
      */
    public function getIdAula(){
        return $this->idAula;
    }

    /**
      * Obtiene el valor del atributo 'fkCentro'.
      *
      * @return integer
      */
    public function getFkCentro(){
        return $this->fkCentro;
    }

    /**
      * Establece el valor del atributo 'fkCentro'.
      *
      * @param integer Valor.
      */
    public function setFkCentro( $value ){

        $this->fkCentro = $value;

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
      * Obtiene el valor del atributo 'iCapacidad'.
      *
      * @return integer
      */
    public function getICapacidad(){
        return $this->iCapacidad;
    }

    /**
      * Establece el valor del atributo 'iCapacidad'.
      *
      * @param integer Valor.
      */
    public function setICapacidad( $value ){

        $this->iCapacidad = $value;

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
     * Obtiene todos los elementos relacionados de la tabla 'tblCurso'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblCursos( $orderBy='' ){

        include_once('TblCurso.inc');
        return TblCurso::findByTblAula( $this->_db, $this->idAula, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblDisponibilidadAula'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblDisponibilidadAulas( $orderBy='' ){

        include_once('TblDisponibilidadAula.inc');
        return TblDisponibilidadAula::findByTblAula( $this->_db, $this->idAula, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelEquipamientoAula'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelEquipamientoAulas( $orderBy='' ){

        include_once('TrelEquipamientoAula.inc');
        return TrelEquipamientoAula::findByTblAula( $this->_db, $this->idAula, $orderBy );

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblCentro' relacionado.
     *
     * @return TblCentro
     */
    public function getTblCentro(){
        require_once('TblCentro.inc');
        return TblCentro::findByPrimaryKey( $this->_db, $this->fkCentro );
    }

    /**
     * Asigna el objeto 'TblCentro' relacionado.
     *
     * @param TblCentro $dataObject
     */
    public function setTblCentro( $dataObject ){
        require_once('TblCentro.inc');
        $this->setFkCentro( $dataObject->getIdCentro() );
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