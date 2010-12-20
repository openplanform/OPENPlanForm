<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 16 de December de 2010 a las 10:23:35
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TblAlumnoSearch.inc' );
require_once( 'TblAlumnoPK.inc' );

/**
 * Objeto para acceder a la tabla tblAlumno.
 *
 * @package dataAccess
 */
class TblAlumno extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idAlumno"
     * @var integer
     */
    public $idAlumno;

    /**
     * Atributo que representa el campo "fkCurso"
     * @var integer
     */
    public $fkCurso;

    /**
     * Atributo que representa el campo "iPersona"
     * @var integer
     */
    public $iPersona;

    /**
     * Atributo que representa el campo "iUsuario"
     * @var integer
     */
    public $iUsuario;

    /**
     * Atributo que representa el campo "vPais"
     * @var string
     */
    public $vPais;

    /**
     * Atributo que representa el campo "vProvincia"
     * @var string
     */
    public $vProvincia;

    /**
     * Atributo que representa el campo "vTipoIdentificacion"
     * @var string
     */
    public $vTipoIdentificacion;

    /**
     * Atributo que representa el campo "vEstadoCivil"
     * @var string
     */
    public $vEstadoCivil;

    /**
     * Atributo que representa el campo "vEstadoLaboral"
     * @var string
     */
    public $vEstadoLaboral;

    /**
     * Atributo que representa el campo "vNivelEstudios"
     * @var string
     */
    public $vNivelEstudios;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

    /**
     * Atributo que representa el campo "vPrimerApellido"
     * @var string
     */
    public $vPrimerApellido;

    /**
     * Atributo que representa el campo "vSegundoApellido"
     * @var string
     */
    public $vSegundoApellido;

    /**
     * Atributo que representa el campo "vPoblacion"
     * @var string
     */
    public $vPoblacion;

    /**
     * Atributo que representa el campo "vNumeroIdentificacion"
     * @var string
     */
    public $vNumeroIdentificacion;

    /**
     * Atributo que representa el campo "vEmail"
     * @var string
     */
    public $vEmail;

    /**
     * Atributo que representa el campo "vDireccion"
     * @var string
     */
    public $vDireccion;

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
     * Atributo que representa el campo "dNacimiento"
     * @var string
     */
    public $dNacimiento;

    /**
     * Atributo que representa el campo "dBaja"
     * @var string
     */
    public $dBaja;

    /**
     * Atributo que representa el campo "vNumeroSS"
     * @var string
     */
    public $vNumeroSS;

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
        $this->idAlumno = $data['idAlumno'];
        $this->fkCurso = $data['fkCurso'];
        $this->iPersona = $data['iPersona'];
        $this->iUsuario = $data['iUsuario'];
        $this->vPais = $data['vPais'];
        $this->vProvincia = $data['vProvincia'];
        $this->vTipoIdentificacion = $data['vTipoIdentificacion'];
        $this->vEstadoCivil = $data['vEstadoCivil'];
        $this->vEstadoLaboral = $data['vEstadoLaboral'];
        $this->vNivelEstudios = $data['vNivelEstudios'];
        $this->vNombre = $data['vNombre'];
        $this->vPrimerApellido = $data['vPrimerApellido'];
        $this->vSegundoApellido = $data['vSegundoApellido'];
        $this->vPoblacion = $data['vPoblacion'];
        $this->vNumeroIdentificacion = $data['vNumeroIdentificacion'];
        $this->vEmail = $data['vEmail'];
        $this->vDireccion = $data['vDireccion'];
        $this->bActiva = $data['bActiva'];
        $this->dAlta = $data['dAlta'];
        $this->dNacimiento = $data['dNacimiento'];
        $this->dBaja = $data['dBaja'];
        $this->vNumeroSS = $data['vNumeroSS'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblAlumno segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblAlumnoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblAlumno';
        $where = array();
        if( $tmp = $searchItem->idAlumno ){
            $where[] = "idAlumno='$tmp'";
        }
        if( $tmp = $searchItem->fkCurso ){
            $where[] = "fkCurso='$tmp'";
        }
        if( $tmp = $searchItem->iPersona ){
            $where[] = "iPersona='$tmp'";
        }
        if( $tmp = $searchItem->iUsuario ){
            $where[] = "iUsuario='$tmp'";
        }
        if( $tmp = $searchItem->vPais ){
            $where[] = "vPais='$tmp'";
        }
        if( $tmp = $searchItem->vProvincia ){
            $where[] = "vProvincia='$tmp'";
        }
        if( $tmp = $searchItem->vTipoIdentificacion ){
            $where[] = "vTipoIdentificacion='$tmp'";
        }
        if( $tmp = $searchItem->vEstadoCivil ){
            $where[] = "vEstadoCivil='$tmp'";
        }
        if( $tmp = $searchItem->vEstadoLaboral ){
            $where[] = "vEstadoLaboral='$tmp'";
        }
        if( $tmp = $searchItem->vNivelEstudios ){
            $where[] = "vNivelEstudios='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->vPrimerApellido ){
            $where[] = "vPrimerApellido='$tmp'";
        }
        if( $tmp = $searchItem->vSegundoApellido ){
            $where[] = "vSegundoApellido='$tmp'";
        }
        if( $tmp = $searchItem->vPoblacion ){
            $where[] = "vPoblacion='$tmp'";
        }
        if( $tmp = $searchItem->vNumeroIdentificacion ){
            $where[] = "vNumeroIdentificacion='$tmp'";
        }
        if( $tmp = $searchItem->vEmail ){
            $where[] = "vEmail='$tmp'";
        }
        if( $tmp = $searchItem->vDireccion ){
            $where[] = "vDireccion='$tmp'";
        }
        if( $tmp = $searchItem->bActiva ){
            $where[] = "bActiva='$tmp'";
        }
        if( $tmp = $searchItem->dAlta ){
            $where[] = "dAlta='$tmp'";
        }
        if( $tmp = $searchItem->dNacimiento ){
            $where[] = "dNacimiento='$tmp'";
        }
        if( $tmp = $searchItem->dBaja ){
            $where[] = "dBaja='$tmp'";
        }
        if( $tmp = $searchItem->vNumeroSS ){
            $where[] = "vNumeroSS='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblAlumno' );
}

    /**
     * Obtiene todas las filas de la tabla tblAlumno.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblAlumno';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblAlumno' );
    }

    /**
     * Obtiene el elemento de la tabla tblAlumno que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idAlumno valor del campo 'idAlumno'.
     * @return TblAlumno
     */
    public static function findByPrimaryKey( $db, $idAlumno ){

       $db->executeQuery("SELECT * FROM tblAlumno WHERE idAlumno = '$idAlumno'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblAlumno');

    }

    /**
     * Obtiene el elemento de la tabla tblAlumno que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblAlumnoPK $pk Objeto de la clave primaria.
     * @return TblAlumno
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idAlumno='".$pk->idAlumno."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblAlumno WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblAlumno');

    }

    /**
     * Obtiene todas las filas de la tabla tblAlumno que coinciden con el criterio fkCurso='$fkCurso'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCurso string Valor del campo fkCurso.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCurso( $db, $fkCurso, $orderBy='' ){
         $sql = "SELECT * FROM tblAlumno WHERE fkCurso='$fkCurso'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblAlumno' );
     }

    /**
     * Actualiza una fila de la tabla tblAlumno.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkCurso=' . ( ( ( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iPersona=' . ( ( ( $value = $this->iPersona ) === null || !isset($this->iPersona) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iUsuario=' . ( ( ( $value = $this->iUsuario ) === null || !isset($this->iUsuario) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vPais=' . ( ( ( $value = $this->vPais ) === null || !isset($this->vPais) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vProvincia=' . ( ( ( $value = $this->vProvincia ) === null || !isset($this->vProvincia) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vTipoIdentificacion=' . ( ( ( $value = $this->vTipoIdentificacion ) === null || !isset($this->vTipoIdentificacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vEstadoCivil=' . ( ( ( $value = $this->vEstadoCivil ) === null || !isset($this->vEstadoCivil) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vEstadoLaboral=' . ( ( ( $value = $this->vEstadoLaboral ) === null || !isset($this->vEstadoLaboral) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNivelEstudios=' . ( ( ( $value = $this->vNivelEstudios ) === null || !isset($this->vNivelEstudios) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vPrimerApellido=' . ( ( ( $value = $this->vPrimerApellido ) === null || !isset($this->vPrimerApellido) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vSegundoApellido=' . ( ( ( $value = $this->vSegundoApellido ) === null || !isset($this->vSegundoApellido) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vPoblacion=' . ( ( ( $value = $this->vPoblacion ) === null || !isset($this->vPoblacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNumeroIdentificacion=' . ( ( ( $value = $this->vNumeroIdentificacion ) === null || !isset($this->vNumeroIdentificacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vEmail=' . ( ( ( $value = $this->vEmail ) === null || !isset($this->vEmail) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDireccion=' . ( ( ( $value = $this->vDireccion ) === null || !isset($this->vDireccion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bActiva=' . ( ( ( $value = $this->bActiva ) === null || !isset($this->bActiva) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dAlta=' . ( ( ( $value = $this->dAlta ) === null || !isset($this->dAlta) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dNacimiento=' . ( ( ( $value = $this->dNacimiento ) === null || !isset($this->dNacimiento) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dBaja=' . ( ( ( $value = $this->dBaja ) === null || !isset($this->dBaja) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNumeroSS=' . ( ( ( $value = $this->vNumeroSS ) === null || !isset($this->vNumeroSS) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblAlumno SET $setStr WHERE idAlumno='".addslashes($this->_data['idAlumno'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblAlumno.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkCurso';
        $attributes[] = 'iPersona';
        $attributes[] = 'iUsuario';
        $attributes[] = 'vPais';
        $attributes[] = 'vProvincia';
        $attributes[] = 'vTipoIdentificacion';
        $attributes[] = 'vEstadoCivil';
        $attributes[] = 'vEstadoLaboral';
        $attributes[] = 'vNivelEstudios';
        $attributes[] = 'vNombre';
        $attributes[] = 'vPrimerApellido';
        $attributes[] = 'vSegundoApellido';
        $attributes[] = 'vPoblacion';
        $attributes[] = 'vNumeroIdentificacion';
        $attributes[] = 'vEmail';
        $attributes[] = 'vDireccion';
        $attributes[] = 'bActiva';
        $attributes[] = 'dAlta';
        $attributes[] = 'dNacimiento';
        $attributes[] = 'dBaja';
        $attributes[] = 'vNumeroSS';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iPersona ) === null || !isset($this->iPersona) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iUsuario ) === null || !isset($this->iUsuario) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vPais ) === null || !isset($this->vPais) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vProvincia ) === null || !isset($this->vProvincia) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vTipoIdentificacion ) === null || !isset($this->vTipoIdentificacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vEstadoCivil ) === null || !isset($this->vEstadoCivil) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vEstadoLaboral ) === null || !isset($this->vEstadoLaboral) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNivelEstudios ) === null || !isset($this->vNivelEstudios) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vPrimerApellido ) === null || !isset($this->vPrimerApellido) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vSegundoApellido ) === null || !isset($this->vSegundoApellido) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vPoblacion ) === null || !isset($this->vPoblacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNumeroIdentificacion ) === null || !isset($this->vNumeroIdentificacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vEmail ) === null || !isset($this->vEmail) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDireccion ) === null || !isset($this->vDireccion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bActiva ) === null || !isset($this->bActiva) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dAlta ) === null || !isset($this->dAlta) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dNacimiento ) === null || !isset($this->dNacimiento) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dBaja ) === null || !isset($this->dBaja) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNumeroSS ) === null || !isset($this->vNumeroSS) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblAlumno($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblAlumno.
     */
    public function delete(){
        $where = array();
        $where[] = "idAlumno="."'".addslashes($this->idAlumno)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblAlumno WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idAlumno'.
      *
      * @return integer
      */
    public function getIdAlumno(){
        return $this->idAlumno;
    }

    /**
      * Obtiene el valor del atributo 'fkCurso'.
      *
      * @return integer
      */
    public function getFkCurso(){
        return $this->fkCurso;
    }

    /**
      * Establece el valor del atributo 'fkCurso'.
      *
      * @param integer Valor.
      */
    public function setFkCurso( $value ){

        $this->fkCurso = $value;

    }

    /**
      * Obtiene el valor del atributo 'iPersona'.
      *
      * @return integer
      */
    public function getIPersona(){
        return $this->iPersona;
    }

    /**
      * Establece el valor del atributo 'iPersona'.
      *
      * @param integer Valor.
      */
    public function setIPersona( $value ){

        $this->iPersona = $value;

    }

    /**
      * Obtiene el valor del atributo 'iUsuario'.
      *
      * @return integer
      */
    public function getIUsuario(){
        return $this->iUsuario;
    }

    /**
      * Establece el valor del atributo 'iUsuario'.
      *
      * @param integer Valor.
      */
    public function setIUsuario( $value ){

        $this->iUsuario = $value;

    }

    /**
      * Obtiene el valor del atributo 'vPais'.
      *
      * @return string
      */
    public function getVPais(){
        return $this->vPais;
    }

    /**
      * Establece el valor del atributo 'vPais'.
      *
      * @param string Valor.
      */
    public function setVPais( $value ){

        $this->vPais = $value;

    }

    /**
      * Obtiene el valor del atributo 'vProvincia'.
      *
      * @return string
      */
    public function getVProvincia(){
        return $this->vProvincia;
    }

    /**
      * Establece el valor del atributo 'vProvincia'.
      *
      * @param string Valor.
      */
    public function setVProvincia( $value ){

        $this->vProvincia = $value;

    }

    /**
      * Obtiene el valor del atributo 'vTipoIdentificacion'.
      *
      * @return string
      */
    public function getVTipoIdentificacion(){
        return $this->vTipoIdentificacion;
    }

    /**
      * Establece el valor del atributo 'vTipoIdentificacion'.
      *
      * @param string Valor.
      */
    public function setVTipoIdentificacion( $value ){

        $this->vTipoIdentificacion = $value;

    }

    /**
      * Obtiene el valor del atributo 'vEstadoCivil'.
      *
      * @return string
      */
    public function getVEstadoCivil(){
        return $this->vEstadoCivil;
    }

    /**
      * Establece el valor del atributo 'vEstadoCivil'.
      *
      * @param string Valor.
      */
    public function setVEstadoCivil( $value ){

        $this->vEstadoCivil = $value;

    }

    /**
      * Obtiene el valor del atributo 'vEstadoLaboral'.
      *
      * @return string
      */
    public function getVEstadoLaboral(){
        return $this->vEstadoLaboral;
    }

    /**
      * Establece el valor del atributo 'vEstadoLaboral'.
      *
      * @param string Valor.
      */
    public function setVEstadoLaboral( $value ){

        $this->vEstadoLaboral = $value;

    }

    /**
      * Obtiene el valor del atributo 'vNivelEstudios'.
      *
      * @return string
      */
    public function getVNivelEstudios(){
        return $this->vNivelEstudios;
    }

    /**
      * Establece el valor del atributo 'vNivelEstudios'.
      *
      * @param string Valor.
      */
    public function setVNivelEstudios( $value ){

        $this->vNivelEstudios = $value;

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
      * Obtiene el valor del atributo 'vPrimerApellido'.
      *
      * @return string
      */
    public function getVPrimerApellido(){
        return $this->vPrimerApellido;
    }

    /**
      * Establece el valor del atributo 'vPrimerApellido'.
      *
      * @param string Valor.
      */
    public function setVPrimerApellido( $value ){

        $this->vPrimerApellido = $value;

    }

    /**
      * Obtiene el valor del atributo 'vSegundoApellido'.
      *
      * @return string
      */
    public function getVSegundoApellido(){
        return $this->vSegundoApellido;
    }

    /**
      * Establece el valor del atributo 'vSegundoApellido'.
      *
      * @param string Valor.
      */
    public function setVSegundoApellido( $value ){

        $this->vSegundoApellido = $value;

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
      * Obtiene el valor del atributo 'vNumeroIdentificacion'.
      *
      * @return string
      */
    public function getVNumeroIdentificacion(){
        return $this->vNumeroIdentificacion;
    }

    /**
      * Establece el valor del atributo 'vNumeroIdentificacion'.
      *
      * @param string Valor.
      */
    public function setVNumeroIdentificacion( $value ){

        $this->vNumeroIdentificacion = $value;

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
      * Obtiene el valor del atributo 'dNacimiento'.
      *
      * @return string
      */
    public function getDNacimiento(){
        return $this->dNacimiento;
    }

    /**
      * Establece el valor del atributo 'dNacimiento'.
      *
      * @param string Valor.
      */
    public function setDNacimiento( $value ){

        $this->dNacimiento = $value;

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
      * Obtiene el valor del atributo 'vNumeroSS'.
      *
      * @return string
      */
    public function getVNumeroSS(){
        return $this->vNumeroSS;
    }

    /**
      * Establece el valor del atributo 'vNumeroSS'.
      *
      * @param string Valor.
      */
    public function setVNumeroSS( $value ){

        $this->vNumeroSS = $value;

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblCurso' relacionado.
     *
     * @return TblCurso
     */
    public function getTblCurso(){
        require_once('TblCurso.inc');
        return TblCurso::findByPrimaryKey( $this->_db, $this->fkCurso );
    }

    /**
     * Asigna el objeto 'TblCurso' relacionado.
     *
     * @param TblCurso $dataObject
     */
    public function setTblCurso( $dataObject ){
        require_once('TblCurso.inc');
        $this->setFkCurso( $dataObject->getIdCurso() );
    }
}
?>