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
     * Atributo que representa el campo "fkEstadoCivil"
     * @var integer
     */
    public $fkEstadoCivil;

    /**
     * Atributo que representa el campo "fkEstadoLaboral"
     * @var integer
     */
    public $fkEstadoLaboral;

    /**
     * Atributo que representa el campo "fkCurso"
     * @var integer
     */
    public $fkCurso;

    /**
     * Atributo que representa el campo "fkPais"
     * @var string
     */
    public $fkPais;

    /**
     * Atributo que representa el campo "fkTipoIdentificacion"
     * @var integer
     */
    public $fkTipoIdentificacion;

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
     * Atributo que representa el campo "iUsuario"
     * @var integer
     */
    public $iUsuario;

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
        $this->fkEstadoCivil = $data['fkEstadoCivil'];
        $this->fkEstadoLaboral = $data['fkEstadoLaboral'];
        $this->fkCurso = $data['fkCurso'];
        $this->fkPais = $data['fkPais'];
        $this->fkTipoIdentificacion = $data['fkTipoIdentificacion'];
        $this->vNombre = $data['vNombre'];
        $this->vPrimerApellido = $data['vPrimerApellido'];
        $this->vSegundoApellido = $data['vSegundoApellido'];
        $this->vPoblacion = $data['vPoblacion'];
        $this->iUsuario = $data['iUsuario'];
        $this->vNumeroIdentificacion = $data['vNumeroIdentificacion'];
        $this->vEmail = $data['vEmail'];
        $this->vDireccion = $data['vDireccion'];
        $this->bActiva = $data['bActiva'];
        $this->dAlta = $data['dAlta'];
        $this->dNacimiento = $data['dNacimiento'];
        $this->dBaja = $data['dBaja'];

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
        if( $tmp = $searchItem->fkEstadoCivil ){
            $where[] = "fkEstadoCivil='$tmp'";
        }
        if( $tmp = $searchItem->fkEstadoLaboral ){
            $where[] = "fkEstadoLaboral='$tmp'";
        }
        if( $tmp = $searchItem->fkCurso ){
            $where[] = "fkCurso='$tmp'";
        }
        if( $tmp = $searchItem->fkPais ){
            $where[] = "fkPais='$tmp'";
        }
        if( $tmp = $searchItem->fkTipoIdentificacion ){
            $where[] = "fkTipoIdentificacion='$tmp'";
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
        if( $tmp = $searchItem->iUsuario ){
            $where[] = "iUsuario='$tmp'";
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
     * Obtiene todas las filas de la tabla tblAlumno que coinciden con el criterio fkEstadoCivil='$fkEstadoCivil'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkEstadoCivil string Valor del campo fkEstadoCivil.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblEstadoCivil( $db, $fkEstadoCivil, $orderBy='' ){
         $sql = "SELECT * FROM tblAlumno WHERE fkEstadoCivil='$fkEstadoCivil'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblAlumno' );
     }

    /**
     * Obtiene todas las filas de la tabla tblAlumno que coinciden con el criterio fkEstadoLaboral='$fkEstadoLaboral'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkEstadoLaboral string Valor del campo fkEstadoLaboral.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblEstadoLaboral( $db, $fkEstadoLaboral, $orderBy='' ){
         $sql = "SELECT * FROM tblAlumno WHERE fkEstadoLaboral='$fkEstadoLaboral'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblAlumno' );
     }

    /**
     * Obtiene todas las filas de la tabla tblAlumno que coinciden con el criterio fkPais='$fkPais'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string fkPais string Valor del campo fkPais.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPais( $db, $fkPais, $orderBy='' ){
         $sql = "SELECT * FROM tblAlumno WHERE fkPais='$fkPais'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblAlumno' );
     }

    /**
     * Obtiene todas las filas de la tabla tblAlumno que coinciden con el criterio fkTipoIdentificacion='$fkTipoIdentificacion'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkTipoIdentificacion string Valor del campo fkTipoIdentificacion.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblTipoIdentificacion( $db, $fkTipoIdentificacion, $orderBy='' ){
         $sql = "SELECT * FROM tblAlumno WHERE fkTipoIdentificacion='$fkTipoIdentificacion'";
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
        $sets[] = 'fkEstadoCivil=' . ( ( ( $value = $this->fkEstadoCivil ) === null || !isset($this->fkEstadoCivil) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkEstadoLaboral=' . ( ( ( $value = $this->fkEstadoLaboral ) === null || !isset($this->fkEstadoLaboral) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkCurso=' . ( ( ( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkPais=' . ( ( ( $value = $this->fkPais ) === null || !isset($this->fkPais) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkTipoIdentificacion=' . ( ( ( $value = $this->fkTipoIdentificacion ) === null || !isset($this->fkTipoIdentificacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vPrimerApellido=' . ( ( ( $value = $this->vPrimerApellido ) === null || !isset($this->vPrimerApellido) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vSegundoApellido=' . ( ( ( $value = $this->vSegundoApellido ) === null || !isset($this->vSegundoApellido) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vPoblacion=' . ( ( ( $value = $this->vPoblacion ) === null || !isset($this->vPoblacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iUsuario=' . ( ( ( $value = $this->iUsuario ) === null || !isset($this->iUsuario) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNumeroIdentificacion=' . ( ( ( $value = $this->vNumeroIdentificacion ) === null || !isset($this->vNumeroIdentificacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vEmail=' . ( ( ( $value = $this->vEmail ) === null || !isset($this->vEmail) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDireccion=' . ( ( ( $value = $this->vDireccion ) === null || !isset($this->vDireccion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bActiva=' . ( ( ( $value = $this->bActiva ) === null || !isset($this->bActiva) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dAlta=' . ( ( ( $value = $this->dAlta ) === null || !isset($this->dAlta) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dNacimiento=' . ( ( ( $value = $this->dNacimiento ) === null || !isset($this->dNacimiento) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dBaja=' . ( ( ( $value = $this->dBaja ) === null || !isset($this->dBaja) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblAlumno SET $setStr WHERE idAlumno='".addslashes($this->_data['idAlumno'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblAlumno.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkEstadoCivil';
        $attributes[] = 'fkEstadoLaboral';
        $attributes[] = 'fkCurso';
        $attributes[] = 'fkPais';
        $attributes[] = 'fkTipoIdentificacion';
        $attributes[] = 'vNombre';
        $attributes[] = 'vPrimerApellido';
        $attributes[] = 'vSegundoApellido';
        $attributes[] = 'vPoblacion';
        $attributes[] = 'iUsuario';
        $attributes[] = 'vNumeroIdentificacion';
        $attributes[] = 'vEmail';
        $attributes[] = 'vDireccion';
        $attributes[] = 'bActiva';
        $attributes[] = 'dAlta';
        $attributes[] = 'dNacimiento';
        $attributes[] = 'dBaja';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkEstadoCivil ) === null || !isset($this->fkEstadoCivil) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkEstadoLaboral ) === null || !isset($this->fkEstadoLaboral) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkPais ) === null || !isset($this->fkPais) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkTipoIdentificacion ) === null || !isset($this->fkTipoIdentificacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vPrimerApellido ) === null || !isset($this->vPrimerApellido) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vSegundoApellido ) === null || !isset($this->vSegundoApellido) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vPoblacion ) === null || !isset($this->vPoblacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iUsuario ) === null || !isset($this->iUsuario) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNumeroIdentificacion ) === null || !isset($this->vNumeroIdentificacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vEmail ) === null || !isset($this->vEmail) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDireccion ) === null || !isset($this->vDireccion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bActiva ) === null || !isset($this->bActiva) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dAlta ) === null || !isset($this->dAlta) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dNacimiento ) === null || !isset($this->dNacimiento) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dBaja ) === null || !isset($this->dBaja) ) ? 'null' : "'".addslashes($value)."'";
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
      * Obtiene el valor del atributo 'fkEstadoCivil'.
      *
      * @return integer
      */
    public function getFkEstadoCivil(){
        return $this->fkEstadoCivil;
    }

    /**
      * Establece el valor del atributo 'fkEstadoCivil'.
      *
      * @param integer Valor.
      */
    public function setFkEstadoCivil( $value ){

        $this->fkEstadoCivil = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkEstadoLaboral'.
      *
      * @return integer
      */
    public function getFkEstadoLaboral(){
        return $this->fkEstadoLaboral;
    }

    /**
      * Establece el valor del atributo 'fkEstadoLaboral'.
      *
      * @param integer Valor.
      */
    public function setFkEstadoLaboral( $value ){

        $this->fkEstadoLaboral = $value;

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
      * Obtiene el valor del atributo 'fkTipoIdentificacion'.
      *
      * @return integer
      */
    public function getFkTipoIdentificacion(){
        return $this->fkTipoIdentificacion;
    }

    /**
      * Establece el valor del atributo 'fkTipoIdentificacion'.
      *
      * @param integer Valor.
      */
    public function setFkTipoIdentificacion( $value ){

        $this->fkTipoIdentificacion = $value;

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

    /**
     * Obtiene el objeto 'TblEstadoCivil' relacionado.
     *
     * @return TblEstadoCivil
     */
    public function getTblEstadoCivil(){
        require_once('TblEstadoCivil.inc');
        return TblEstadoCivil::findByPrimaryKey( $this->_db, $this->fkEstadoCivil );
    }

    /**
     * Asigna el objeto 'TblEstadoCivil' relacionado.
     *
     * @param TblEstadoCivil $dataObject
     */
    public function setTblEstadoCivil( $dataObject ){
        require_once('TblEstadoCivil.inc');
        $this->setFkEstadoCivil( $dataObject->getIdEstadoCivil() );
    }

    /**
     * Obtiene el objeto 'TblEstadoLaboral' relacionado.
     *
     * @return TblEstadoLaboral
     */
    public function getTblEstadoLaboral(){
        require_once('TblEstadoLaboral.inc');
        return TblEstadoLaboral::findByPrimaryKey( $this->_db, $this->fkEstadoLaboral );
    }

    /**
     * Asigna el objeto 'TblEstadoLaboral' relacionado.
     *
     * @param TblEstadoLaboral $dataObject
     */
    public function setTblEstadoLaboral( $dataObject ){
        require_once('TblEstadoLaboral.inc');
        $this->setFkEstadoLaboral( $dataObject->getIdEstadoLaboral() );
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
     * Obtiene el objeto 'TblTipoIdentificacion' relacionado.
     *
     * @return TblTipoIdentificacion
     */
    public function getTblTipoIdentificacion(){
        require_once('TblTipoIdentificacion.inc');
        return TblTipoIdentificacion::findByPrimaryKey( $this->_db, $this->fkTipoIdentificacion );
    }

    /**
     * Asigna el objeto 'TblTipoIdentificacion' relacionado.
     *
     * @param TblTipoIdentificacion $dataObject
     */
    public function setTblTipoIdentificacion( $dataObject ){
        require_once('TblTipoIdentificacion.inc');
        $this->setFkTipoIdentificacion( $dataObject->getIdTipoIdentificacion() );
    }
}
?>