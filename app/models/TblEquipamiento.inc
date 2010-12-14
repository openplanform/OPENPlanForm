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
require_once( 'TblEquipamientoSearch.inc' );
require_once( 'TblEquipamientoPK.inc' );

/**
 * Objeto para acceder a la tabla tblEquipamiento.
 *
 * @package dataAccess
 */
class TblEquipamiento extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idEquipamiento"
     * @var integer
     */
    public $idEquipamiento;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

    /**
     * Atributo que representa el campo "vDescripcion"
     * @var string
     */
    public $vDescripcion;

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
        $this->idEquipamiento = $data['idEquipamiento'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblEquipamiento segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblEquipamientoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblEquipamiento';
        $where = array();
        if( $tmp = $searchItem->idEquipamiento ){
            $where[] = "idEquipamiento='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->vDescripcion ){
            $where[] = "vDescripcion='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblEquipamiento' );
}

    /**
     * Obtiene todas las filas de la tabla tblEquipamiento.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblEquipamiento';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblEquipamiento' );
    }

    /**
     * Obtiene el elemento de la tabla tblEquipamiento que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idEquipamiento valor del campo 'idEquipamiento'.
     * @return TblEquipamiento
     */
    public static function findByPrimaryKey( $db, $idEquipamiento ){

       $db->executeQuery("SELECT * FROM tblEquipamiento WHERE idEquipamiento = '$idEquipamiento'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblEquipamiento');

    }

    /**
     * Obtiene el elemento de la tabla tblEquipamiento que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblEquipamientoPK $pk Objeto de la clave primaria.
     * @return TblEquipamiento
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idEquipamiento='".$pk->idEquipamiento."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblEquipamiento WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblEquipamiento');

    }

    /**
     * Actualiza una fila de la tabla tblEquipamiento.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblEquipamiento SET $setStr WHERE idEquipamiento='".addslashes($this->_data['idEquipamiento'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblEquipamiento.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'vNombre';
        $attributes[] = 'vDescripcion';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblEquipamiento($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblEquipamiento.
     */
    public function delete(){
        $where = array();
        $where[] = "idEquipamiento="."'".addslashes($this->idEquipamiento)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblEquipamiento WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idEquipamiento'.
      *
      * @return integer
      */
    public function getIdEquipamiento(){
        return $this->idEquipamiento;
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
     * Obtiene todos los elementos relacionados de la tabla 'trelEquipamientoAula'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelEquipamientoAulas( $orderBy='' ){

        include_once('TrelEquipamientoAula.inc');
        return TrelEquipamientoAula::findByTblEquipamiento( $this->_db, $this->idEquipamiento, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelEquipamientoPlanCursoAula'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelEquipamientoPlanCursoAulas( $orderBy='' ){

        include_once('TrelEquipamientoPlanCursoAula.inc');
        return TrelEquipamientoPlanCursoAula::findByTblEquipamiento( $this->_db, $this->idEquipamiento, $orderBy );

    }
}
?>