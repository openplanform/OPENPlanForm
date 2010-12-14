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
require_once( 'TblColectivoSearch.inc' );
require_once( 'TblColectivoPK.inc' );

/**
 * Objeto para acceder a la tabla tblColectivo.
 *
 * @package dataAccess
 */
class TblColectivo extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idColectivo"
     * @var integer
     */
    public $idColectivo;

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
        $this->idColectivo = $data['idColectivo'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblColectivo segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblColectivoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblColectivo';
        $where = array();
        if( $tmp = $searchItem->idColectivo ){
            $where[] = "idColectivo='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TblColectivo' );
}

    /**
     * Obtiene todas las filas de la tabla tblColectivo.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblColectivo';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblColectivo' );
    }

    /**
     * Obtiene el elemento de la tabla tblColectivo que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idColectivo valor del campo 'idColectivo'.
     * @return TblColectivo
     */
    public static function findByPrimaryKey( $db, $idColectivo ){

       $db->executeQuery("SELECT * FROM tblColectivo WHERE idColectivo = '$idColectivo'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblColectivo');

    }

    /**
     * Obtiene el elemento de la tabla tblColectivo que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblColectivoPK $pk Objeto de la clave primaria.
     * @return TblColectivo
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idColectivo='".$pk->idColectivo."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblColectivo WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblColectivo');

    }

    /**
     * Actualiza una fila de la tabla tblColectivo.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblColectivo SET $setStr WHERE idColectivo='".addslashes($this->_data['idColectivo'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblColectivo.
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
        if( $this->_db->executeQuery("INSERT INTO tblColectivo($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblColectivo.
     */
    public function delete(){
        $where = array();
        $where[] = "idColectivo="."'".addslashes($this->idColectivo)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblColectivo WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idColectivo'.
      *
      * @return integer
      */
    public function getIdColectivo(){
        return $this->idColectivo;
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
     * Obtiene todos los elementos relacionados de la tabla 'tblCurso'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblCursos( $orderBy='' ){

        include_once('TblCurso.inc');
        return TblCurso::findByTblColectivo( $this->_db, $this->idColectivo, $orderBy );

    }
}
?>