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
require_once( 'TblEstadoLaboralSearch.inc' );
require_once( 'TblEstadoLaboralPK.inc' );

/**
 * Objeto para acceder a la tabla tblEstadoLaboral.
 *
 * @package dataAccess
 */
class TblEstadoLaboral extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idEstadoLaboral"
     * @var integer
     */
    public $idEstadoLaboral;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

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
        $this->idEstadoLaboral = $data['idEstadoLaboral'];
        $this->vNombre = $data['vNombre'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblEstadoLaboral segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblEstadoLaboralSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblEstadoLaboral';
        $where = array();
        if( $tmp = $searchItem->idEstadoLaboral ){
            $where[] = "idEstadoLaboral='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblEstadoLaboral' );
}

    /**
     * Obtiene todas las filas de la tabla tblEstadoLaboral.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblEstadoLaboral';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblEstadoLaboral' );
    }

    /**
     * Obtiene el elemento de la tabla tblEstadoLaboral que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idEstadoLaboral valor del campo 'idEstadoLaboral'.
     * @return TblEstadoLaboral
     */
    public static function findByPrimaryKey( $db, $idEstadoLaboral ){

       $db->executeQuery("SELECT * FROM tblEstadoLaboral WHERE idEstadoLaboral = '$idEstadoLaboral'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblEstadoLaboral');

    }

    /**
     * Obtiene el elemento de la tabla tblEstadoLaboral que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblEstadoLaboralPK $pk Objeto de la clave primaria.
     * @return TblEstadoLaboral
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idEstadoLaboral='".$pk->idEstadoLaboral."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblEstadoLaboral WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblEstadoLaboral');

    }

    /**
     * Actualiza una fila de la tabla tblEstadoLaboral.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblEstadoLaboral SET $setStr WHERE idEstadoLaboral='".addslashes($this->_data['idEstadoLaboral'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblEstadoLaboral.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vNombre';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblEstadoLaboral($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblEstadoLaboral.
     */
    public function delete(){
        $where = array();
        $where[] = "idEstadoLaboral="."'".addslashes($this->idEstadoLaboral)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblEstadoLaboral WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idEstadoLaboral'.
      *
      * @return integer
      */
    public function getIdEstadoLaboral(){
        return $this->idEstadoLaboral;
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
     * Obtiene todos los elementos relacionados de la tabla 'tblAlumno'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblAlumnos( $orderBy='' ){

        include_once('TblAlumno.inc');
        return TblAlumno::findByTblEstadoLaboral( $this->_db, $this->idEstadoLaboral, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblPersona'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPersonas( $orderBy='' ){

        include_once('TblPersona.inc');
        return TblPersona::findByTblEstadoLaboral( $this->_db, $this->idEstadoLaboral, $orderBy );

    }
}
?>