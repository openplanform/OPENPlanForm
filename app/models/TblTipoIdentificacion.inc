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
require_once( 'TblTipoIdentificacionSearch.inc' );
require_once( 'TblTipoIdentificacionPK.inc' );

/**
 * Objeto para acceder a la tabla tblTipoIdentificacion.
 *
 * @package dataAccess
 */
class TblTipoIdentificacion extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idTipoIdentificacion"
     * @var integer
     */
    public $idTipoIdentificacion;

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
        $this->idTipoIdentificacion = $data['idTipoIdentificacion'];
        $this->vNombre = $data['vNombre'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblTipoIdentificacion segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblTipoIdentificacionSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblTipoIdentificacion';
        $where = array();
        if( $tmp = $searchItem->idTipoIdentificacion ){
            $where[] = "idTipoIdentificacion='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TblTipoIdentificacion' );
}

    /**
     * Obtiene todas las filas de la tabla tblTipoIdentificacion.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblTipoIdentificacion';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblTipoIdentificacion' );
    }

    /**
     * Obtiene el elemento de la tabla tblTipoIdentificacion que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idTipoIdentificacion valor del campo 'idTipoIdentificacion'.
     * @return TblTipoIdentificacion
     */
    public static function findByPrimaryKey( $db, $idTipoIdentificacion ){

       $db->executeQuery("SELECT * FROM tblTipoIdentificacion WHERE idTipoIdentificacion = '$idTipoIdentificacion'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblTipoIdentificacion');

    }

    /**
     * Obtiene el elemento de la tabla tblTipoIdentificacion que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblTipoIdentificacionPK $pk Objeto de la clave primaria.
     * @return TblTipoIdentificacion
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idTipoIdentificacion='".$pk->idTipoIdentificacion."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblTipoIdentificacion WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblTipoIdentificacion');

    }

    /**
     * Actualiza una fila de la tabla tblTipoIdentificacion.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblTipoIdentificacion SET $setStr WHERE idTipoIdentificacion='".addslashes($this->_data['idTipoIdentificacion'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblTipoIdentificacion.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vNombre';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblTipoIdentificacion($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblTipoIdentificacion.
     */
    public function delete(){
        $where = array();
        $where[] = "idTipoIdentificacion="."'".addslashes($this->idTipoIdentificacion)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblTipoIdentificacion WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idTipoIdentificacion'.
      *
      * @return integer
      */
    public function getIdTipoIdentificacion(){
        return $this->idTipoIdentificacion;
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
        return TblAlumno::findByTblTipoIdentificacion( $this->_db, $this->idTipoIdentificacion, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblPersona'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPersonas( $orderBy='' ){

        include_once('TblPersona.inc');
        return TblPersona::findByTblTipoIdentificacion( $this->_db, $this->idTipoIdentificacion, $orderBy );

    }
}
?>