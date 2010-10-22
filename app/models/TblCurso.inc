<?php
/**
 * Este archivo ha sido generado con Ningen DoGen v.0.6
 * el 21 de October de 2010 a las 10:48:39
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/NingenConnection.inc');
require_once( 'dbase/NingenGenericDO.inc');
require_once( 'TblCursoSearch.inc' );
require_once( 'TblCursoPK.inc' );

/**
 * Objeto para acceder a la tabla tblCurso.
 *
 * @package dataAccess
 */
class TblCurso extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idCurso"
     * @var integer
     */
    public $idCurso;

    /**
     * Atributo que representa el campo "fkPlan"
     * @var integer
     */
    public $fkPlan;

    /**
     * Atributo que representa el campo "fkCategoria"
     * @var integer
     */
    public $fkCategoria;

    /**
     * Atributo que representa el campo "fkColectivo"
     * @var integer
     */
    public $fkColectivo;

    /**
     * Atributo que representa el campo "fkSector"
     * @var integer
     */
    public $fkSector;

    /**
     * Atributo que representa el campo "fkModalidad"
     * @var integer
     */
    public $fkModalidad;

    /**
     * Atributo que representa el campo "fkAula"
     * @var integer
     */
    public $fkAula;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

    /**
     * Atributo que representa el campo "iHorasPresenciales"
     * @var integer
     */
    public $iHorasPresenciales;

    /**
     * Atributo que representa el campo "iHorasDistancia"
     * @var integer
     */
    public $iHorasDistancia;

    /**
     * Atributo que representa el campo "iHorasTutoria"
     * @var integer
     */
    public $iHorasTutoria;

    /**
     * Atributo que representa el campo "dInicio"
     * @var string
     */
    public $dInicio;

    /**
     * Atributo que representa el campo "dFin"
     * @var string
     */
    public $dFin;

    /**
     * Atributo que representa el campo "iNumeroAlumnos"
     * @var integer
     */
    public $iNumeroAlumnos;

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
        $this->idCurso = $data['idCurso'];
        $this->fkPlan = $data['fkPlan'];
        $this->fkCategoria = $data['fkCategoria'];
        $this->fkColectivo = $data['fkColectivo'];
        $this->fkSector = $data['fkSector'];
        $this->fkModalidad = $data['fkModalidad'];
        $this->fkAula = $data['fkAula'];
        $this->vNombre = $data['vNombre'];
        $this->iHorasPresenciales = $data['iHorasPresenciales'];
        $this->iHorasDistancia = $data['iHorasDistancia'];
        $this->iHorasTutoria = $data['iHorasTutoria'];
        $this->dInicio = $data['dInicio'];
        $this->dFin = $data['dFin'];
        $this->iNumeroAlumnos = $data['iNumeroAlumnos'];
        $this->modUser = $data['mod_user'];
        $this->lastModified = $data['last_modified'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblCurso segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblCursoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblCurso';
        $where = array();
        if( $tmp = $searchItem->idCurso ){
            $where[] = "idCurso='$tmp'";
        }
        if( $tmp = $searchItem->fkPlan ){
            $where[] = "fkPlan='$tmp'";
        }
        if( $tmp = $searchItem->fkCategoria ){
            $where[] = "fkCategoria='$tmp'";
        }
        if( $tmp = $searchItem->fkColectivo ){
            $where[] = "fkColectivo='$tmp'";
        }
        if( $tmp = $searchItem->fkSector ){
            $where[] = "fkSector='$tmp'";
        }
        if( $tmp = $searchItem->fkModalidad ){
            $where[] = "fkModalidad='$tmp'";
        }
        if( $tmp = $searchItem->fkAula ){
            $where[] = "fkAula='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->iHorasPresenciales ){
            $where[] = "iHorasPresenciales='$tmp'";
        }
        if( $tmp = $searchItem->iHorasDistancia ){
            $where[] = "iHorasDistancia='$tmp'";
        }
        if( $tmp = $searchItem->iHorasTutoria ){
            $where[] = "iHorasTutoria='$tmp'";
        }
        if( $tmp = $searchItem->dInicio ){
            $where[] = "dInicio='$tmp'";
        }
        if( $tmp = $searchItem->dFin ){
            $where[] = "dFin='$tmp'";
        }
        if( $tmp = $searchItem->iNumeroAlumnos ){
            $where[] = "iNumeroAlumnos='$tmp'";
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
        return NingenGenericDO::createCollection( $db, $sql, 'TblCurso' );
}

    /**
     * Obtiene todas las filas de la tabla tblCurso.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblCurso';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblCurso' );
    }

    /**
     * Obtiene el elemento de la tabla tblCurso que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idCurso valor del campo 'idCurso'.
     * @return TblCurso
     */
    public static function findByPrimaryKey( $db, $idCurso ){

       $db->executeQuery("SELECT * FROM tblCurso WHERE idCurso = '$idCurso'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TblCurso');

    }

    /**
     * Obtiene el elemento de la tabla tblCurso que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblCursoPK $pk Objeto de la clave primaria.
     * @return TblCurso
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idCurso='".$pk->idCurso."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblCurso WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TblCurso');

    }

    /**
     * Obtiene todas las filas de la tabla tblCurso que coinciden con el criterio fkPlan='$fkPlan'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPlan string Valor del campo fkPlan.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPlan( $db, $fkPlan, $orderBy='' ){
         $sql = "SELECT * FROM tblCurso WHERE fkPlan='$fkPlan'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblCurso' );
     }

    /**
     * Obtiene todas las filas de la tabla tblCurso que coinciden con el criterio fkSector='$fkSector'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkSector string Valor del campo fkSector.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblSector( $db, $fkSector, $orderBy='' ){
         $sql = "SELECT * FROM tblCurso WHERE fkSector='$fkSector'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblCurso' );
     }

    /**
     * Obtiene todas las filas de la tabla tblCurso que coinciden con el criterio fkAula='$fkAula'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkAula string Valor del campo fkAula.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblAula( $db, $fkAula, $orderBy='' ){
         $sql = "SELECT * FROM tblCurso WHERE fkAula='$fkAula'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblCurso' );
     }

    /**
     * Obtiene todas las filas de la tabla tblCurso que coinciden con el criterio fkCategoria='$fkCategoria'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCategoria string Valor del campo fkCategoria.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCategoria( $db, $fkCategoria, $orderBy='' ){
         $sql = "SELECT * FROM tblCurso WHERE fkCategoria='$fkCategoria'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblCurso' );
     }

    /**
     * Obtiene todas las filas de la tabla tblCurso que coinciden con el criterio fkColectivo='$fkColectivo'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkColectivo string Valor del campo fkColectivo.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblColectivo( $db, $fkColectivo, $orderBy='' ){
         $sql = "SELECT * FROM tblCurso WHERE fkColectivo='$fkColectivo'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblCurso' );
     }

    /**
     * Obtiene todas las filas de la tabla tblCurso que coinciden con el criterio fkModalidad='$fkModalidad'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkModalidad string Valor del campo fkModalidad.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblModalidad( $db, $fkModalidad, $orderBy='' ){
         $sql = "SELECT * FROM tblCurso WHERE fkModalidad='$fkModalidad'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblCurso' );
     }

    /**
     * Actualiza una fila de la tabla tblCurso.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkPlan=' . ( ( ( $value = $this->fkPlan ) === null || !isset($this->fkPlan) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkCategoria=' . ( ( ( $value = $this->fkCategoria ) === null || !isset($this->fkCategoria) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkColectivo=' . ( ( ( $value = $this->fkColectivo ) === null || !isset($this->fkColectivo) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkSector=' . ( ( ( $value = $this->fkSector ) === null || !isset($this->fkSector) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkModalidad=' . ( ( ( $value = $this->fkModalidad ) === null || !isset($this->fkModalidad) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkAula=' . ( ( ( $value = $this->fkAula ) === null || !isset($this->fkAula) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iHorasPresenciales=' . ( ( ( $value = $this->iHorasPresenciales ) === null || !isset($this->iHorasPresenciales) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iHorasDistancia=' . ( ( ( $value = $this->iHorasDistancia ) === null || !isset($this->iHorasDistancia) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iHorasTutoria=' . ( ( ( $value = $this->iHorasTutoria ) === null || !isset($this->iHorasTutoria) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dInicio=' . ( ( ( $value = $this->dInicio ) === null || !isset($this->dInicio) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dFin=' . ( ( ( $value = $this->dFin ) === null || !isset($this->dFin) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iNumeroAlumnos=' . ( ( ( $value = $this->iNumeroAlumnos ) === null || !isset($this->iNumeroAlumnos) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'mod_user=' . ( ( ( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'last_modified=' . ( ( ( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblCurso SET $setStr WHERE idCurso='".addslashes($this->_data['idCurso'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblCurso.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkPlan';
        $attributes[] = 'fkCategoria';
        $attributes[] = 'fkColectivo';
        $attributes[] = 'fkSector';
        $attributes[] = 'fkModalidad';
        $attributes[] = 'fkAula';
        $attributes[] = 'vNombre';
        $attributes[] = 'iHorasPresenciales';
        $attributes[] = 'iHorasDistancia';
        $attributes[] = 'iHorasTutoria';
        $attributes[] = 'dInicio';
        $attributes[] = 'dFin';
        $attributes[] = 'iNumeroAlumnos';
        $attributes[] = 'mod_user';
        $attributes[] = 'last_modified';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkPlan ) === null || !isset($this->fkPlan) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkCategoria ) === null || !isset($this->fkCategoria) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkColectivo ) === null || !isset($this->fkColectivo) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkSector ) === null || !isset($this->fkSector) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkModalidad ) === null || !isset($this->fkModalidad) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkAula ) === null || !isset($this->fkAula) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iHorasPresenciales ) === null || !isset($this->iHorasPresenciales) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iHorasDistancia ) === null || !isset($this->iHorasDistancia) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iHorasTutoria ) === null || !isset($this->iHorasTutoria) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dInicio ) === null || !isset($this->dInicio) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dFin ) === null || !isset($this->dFin) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iNumeroAlumnos ) === null || !isset($this->iNumeroAlumnos) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblCurso($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblCurso.
     */
    public function delete(){
        $where = array();
        $where[] = "idCurso="."'".addslashes($this->idCurso)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblCurso WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idCurso'.
      *
      * @return integer
      */
    public function getIdCurso(){
        return $this->idCurso;
    }

    /**
      * Obtiene el valor del atributo 'fkPlan'.
      *
      * @return integer
      */
    public function getFkPlan(){
        return $this->fkPlan;
    }

    /**
      * Establece el valor del atributo 'fkPlan'.
      *
      * @param integer Valor.
      */
    public function setFkPlan( $value ){

        $this->fkPlan = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkCategoria'.
      *
      * @return integer
      */
    public function getFkCategoria(){
        return $this->fkCategoria;
    }

    /**
      * Establece el valor del atributo 'fkCategoria'.
      *
      * @param integer Valor.
      */
    public function setFkCategoria( $value ){

        $this->fkCategoria = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkColectivo'.
      *
      * @return integer
      */
    public function getFkColectivo(){
        return $this->fkColectivo;
    }

    /**
      * Establece el valor del atributo 'fkColectivo'.
      *
      * @param integer Valor.
      */
    public function setFkColectivo( $value ){

        $this->fkColectivo = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkSector'.
      *
      * @return integer
      */
    public function getFkSector(){
        return $this->fkSector;
    }

    /**
      * Establece el valor del atributo 'fkSector'.
      *
      * @param integer Valor.
      */
    public function setFkSector( $value ){

        $this->fkSector = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkModalidad'.
      *
      * @return integer
      */
    public function getFkModalidad(){
        return $this->fkModalidad;
    }

    /**
      * Establece el valor del atributo 'fkModalidad'.
      *
      * @param integer Valor.
      */
    public function setFkModalidad( $value ){

        $this->fkModalidad = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkAula'.
      *
      * @return integer
      */
    public function getFkAula(){
        return $this->fkAula;
    }

    /**
      * Establece el valor del atributo 'fkAula'.
      *
      * @param integer Valor.
      */
    public function setFkAula( $value ){

        $this->fkAula = $value;

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
      * Obtiene el valor del atributo 'iHorasPresenciales'.
      *
      * @return integer
      */
    public function getIHorasPresenciales(){
        return $this->iHorasPresenciales;
    }

    /**
      * Establece el valor del atributo 'iHorasPresenciales'.
      *
      * @param integer Valor.
      */
    public function setIHorasPresenciales( $value ){

        $this->iHorasPresenciales = $value;

    }

    /**
      * Obtiene el valor del atributo 'iHorasDistancia'.
      *
      * @return integer
      */
    public function getIHorasDistancia(){
        return $this->iHorasDistancia;
    }

    /**
      * Establece el valor del atributo 'iHorasDistancia'.
      *
      * @param integer Valor.
      */
    public function setIHorasDistancia( $value ){

        $this->iHorasDistancia = $value;

    }

    /**
      * Obtiene el valor del atributo 'iHorasTutoria'.
      *
      * @return integer
      */
    public function getIHorasTutoria(){
        return $this->iHorasTutoria;
    }

    /**
      * Establece el valor del atributo 'iHorasTutoria'.
      *
      * @param integer Valor.
      */
    public function setIHorasTutoria( $value ){

        $this->iHorasTutoria = $value;

    }

    /**
      * Obtiene el valor del atributo 'dInicio'.
      *
      * @return string
      */
    public function getDInicio(){
        return $this->dInicio;
    }

    /**
      * Establece el valor del atributo 'dInicio'.
      *
      * @param string Valor.
      */
    public function setDInicio( $value ){

        $this->dInicio = $value;

    }

    /**
      * Obtiene el valor del atributo 'dFin'.
      *
      * @return string
      */
    public function getDFin(){
        return $this->dFin;
    }

    /**
      * Establece el valor del atributo 'dFin'.
      *
      * @param string Valor.
      */
    public function setDFin( $value ){

        $this->dFin = $value;

    }

    /**
      * Obtiene el valor del atributo 'iNumeroAlumnos'.
      *
      * @return integer
      */
    public function getINumeroAlumnos(){
        return $this->iNumeroAlumnos;
    }

    /**
      * Establece el valor del atributo 'iNumeroAlumnos'.
      *
      * @param integer Valor.
      */
    public function setINumeroAlumnos( $value ){

        $this->iNumeroAlumnos = $value;

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
     * Obtiene todos los elementos relacionados de la tabla 'tblAlumno'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblAlumnos( $orderBy='' ){

        include_once('TblAlumno.inc');
        return TblAlumno::findByTblCurso( $this->_db, $this->idCurso, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblMaterialCurso'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblMaterialCursos( $orderBy='' ){

        include_once('TblMaterialCurso.inc');
        return TblMaterialCurso::findByTblCurso( $this->_db, $this->idCurso, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelCandidato'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelCandidatos( $orderBy='' ){

        include_once('TrelCandidato.inc');
        return TrelCandidato::findByTblCurso( $this->_db, $this->idCurso, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelDocumentoCurso'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelDocumentoCursos( $orderBy='' ){

        include_once('TrelDocumentoCurso.inc');
        return TrelDocumentoCurso::findByTblCurso( $this->_db, $this->idCurso, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelEquipamientoPlanCursoAula'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelEquipamientoPlanCursoAulas( $orderBy='' ){

        include_once('TrelEquipamientoPlanCursoAula.inc');
        return TrelEquipamientoPlanCursoAula::findByTblCurso( $this->_db, $this->idCurso, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelPersonaCurso'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelPersonaCursos( $orderBy='' ){

        include_once('TrelPersonaCurso.inc');
        return TrelPersonaCurso::findByTblCurso( $this->_db, $this->idCurso, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelProfesor'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelProfesors( $orderBy='' ){

        include_once('TrelProfesor.inc');
        return TrelProfesor::findByTblCurso( $this->_db, $this->idCurso, $orderBy );

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblPlan' relacionado.
     *
     * @return TblPlan
     */
    public function getTblPlan(){
        require_once('TblPlan.inc');
        return TblPlan::findByPrimaryKey( $this->_db, $this->fkPlan );
    }

    /**
     * Asigna el objeto 'TblPlan' relacionado.
     *
     * @param TblPlan $dataObject
     */
    public function setTblPlan( $dataObject ){
        require_once('TblPlan.inc');
        $this->setFkPlan( $dataObject->getIdPlan() );
    }

    /**
     * Obtiene el objeto 'TblSector' relacionado.
     *
     * @return TblSector
     */
    public function getTblSector(){
        require_once('TblSector.inc');
        return TblSector::findByPrimaryKey( $this->_db, $this->fkSector );
    }

    /**
     * Asigna el objeto 'TblSector' relacionado.
     *
     * @param TblSector $dataObject
     */
    public function setTblSector( $dataObject ){
        require_once('TblSector.inc');
        $this->setFkSector( $dataObject->getIdSector() );
    }

    /**
     * Obtiene el objeto 'TblAula' relacionado.
     *
     * @return TblAula
     */
    public function getTblAula(){
        require_once('TblAula.inc');
        return TblAula::findByPrimaryKey( $this->_db, $this->fkAula );
    }

    /**
     * Asigna el objeto 'TblAula' relacionado.
     *
     * @param TblAula $dataObject
     */
    public function setTblAula( $dataObject ){
        require_once('TblAula.inc');
        $this->setFkAula( $dataObject->getIdAula() );
    }

    /**
     * Obtiene el objeto 'TblCategoria' relacionado.
     *
     * @return TblCategoria
     */
    public function getTblCategoria(){
        require_once('TblCategoria.inc');
        return TblCategoria::findByPrimaryKey( $this->_db, $this->fkCategoria );
    }

    /**
     * Asigna el objeto 'TblCategoria' relacionado.
     *
     * @param TblCategoria $dataObject
     */
    public function setTblCategoria( $dataObject ){
        require_once('TblCategoria.inc');
        $this->setFkCategoria( $dataObject->getIdCategoria() );
    }

    /**
     * Obtiene el objeto 'TblColectivo' relacionado.
     *
     * @return TblColectivo
     */
    public function getTblColectivo(){
        require_once('TblColectivo.inc');
        return TblColectivo::findByPrimaryKey( $this->_db, $this->fkColectivo );
    }

    /**
     * Asigna el objeto 'TblColectivo' relacionado.
     *
     * @param TblColectivo $dataObject
     */
    public function setTblColectivo( $dataObject ){
        require_once('TblColectivo.inc');
        $this->setFkColectivo( $dataObject->getIdColectivo() );
    }

    /**
     * Obtiene el objeto 'TblModalidad' relacionado.
     *
     * @return TblModalidad
     */
    public function getTblModalidad(){
        require_once('TblModalidad.inc');
        return TblModalidad::findByPrimaryKey( $this->_db, $this->fkModalidad );
    }

    /**
     * Asigna el objeto 'TblModalidad' relacionado.
     *
     * @param TblModalidad $dataObject
     */
    public function setTblModalidad( $dataObject ){
        require_once('TblModalidad.inc');
        $this->setFkModalidad( $dataObject->getIdModalidad() );
    }
}
?>