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
require_once( 'TblTipoConvocatoriaSearch.inc' );
require_once( 'TblTipoConvocatoriaPK.inc' );

/**
 * Objeto para acceder a la tabla tblTipoConvocatoria.
 *
 * @package dataAccess
 */
class TblTipoConvocatoria extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idTipoConvocatoria"
     * @var integer
     */
    public $idTipoConvocatoria;

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
        $this->idTipoConvocatoria = $data['idTipoConvocatoria'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblTipoConvocatoria segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblTipoConvocatoriaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblTipoConvocatoria';
        $where = array();
        if( $tmp = $searchItem->idTipoConvocatoria ){
            $where[] = "idTipoConvocatoria='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TblTipoConvocatoria' );
}

    /**
     * Obtiene todas las filas de la tabla tblTipoConvocatoria.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblTipoConvocatoria';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblTipoConvocatoria' );
    }

    /**
     * Obtiene el elemento de la tabla tblTipoConvocatoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idTipoConvocatoria valor del campo 'idTipoConvocatoria'.
     * @return TblTipoConvocatoria
     */
    public static function findByPrimaryKey( $db, $idTipoConvocatoria ){

       $db->executeQuery("SELECT * FROM tblTipoConvocatoria WHERE idTipoConvocatoria = '$idTipoConvocatoria'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblTipoConvocatoria');

    }

    /**
     * Obtiene el elemento de la tabla tblTipoConvocatoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblTipoConvocatoriaPK $pk Objeto de la clave primaria.
     * @return TblTipoConvocatoria
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idTipoConvocatoria='".$pk->idTipoConvocatoria."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblTipoConvocatoria WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblTipoConvocatoria');

    }

    /**
     * Actualiza una fila de la tabla tblTipoConvocatoria.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblTipoConvocatoria SET $setStr WHERE idTipoConvocatoria='".addslashes($this->_data['idTipoConvocatoria'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblTipoConvocatoria.
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
        if( $this->_db->executeQuery("INSERT INTO tblTipoConvocatoria($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblTipoConvocatoria.
     */
    public function delete(){
        $where = array();
        $where[] = "idTipoConvocatoria="."'".addslashes($this->idTipoConvocatoria)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblTipoConvocatoria WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idTipoConvocatoria'.
      *
      * @return integer
      */
    public function getIdTipoConvocatoria(){
        return $this->idTipoConvocatoria;
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
     * Obtiene todos los elementos relacionados de la tabla 'tblConvocatoria'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblConvocatorias( $orderBy='' ){

        include_once('TblConvocatoria.inc');
        return TblConvocatoria::findByTblTipoConvocatoria( $this->_db, $this->idTipoConvocatoria, $orderBy );

    }
}
?>