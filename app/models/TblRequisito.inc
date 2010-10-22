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
require_once( 'TblRequisitoSearch.inc' );
require_once( 'TblRequisitoPK.inc' );

/**
 * Objeto para acceder a la tabla tblRequisito.
 *
 * @package dataAccess
 */
class TblRequisito extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idRequisito"
     * @var integer
     */
    public $idRequisito;

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
        $this->idRequisito = $data['idRequisito'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblRequisito segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblRequisitoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblRequisito';
        $where = array();
        if( $tmp = $searchItem->idRequisito ){
            $where[] = "idRequisito='$tmp'";
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
        return NingenGenericDO::createCollection( $db, $sql, 'TblRequisito' );
}

    /**
     * Obtiene todas las filas de la tabla tblRequisito.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblRequisito';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblRequisito' );
    }

    /**
     * Obtiene el elemento de la tabla tblRequisito que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idRequisito valor del campo 'idRequisito'.
     * @return TblRequisito
     */
    public static function findByPrimaryKey( $db, $idRequisito ){

       $db->executeQuery("SELECT * FROM tblRequisito WHERE idRequisito = '$idRequisito'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TblRequisito');

    }

    /**
     * Obtiene el elemento de la tabla tblRequisito que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblRequisitoPK $pk Objeto de la clave primaria.
     * @return TblRequisito
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idRequisito='".$pk->idRequisito."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblRequisito WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TblRequisito');

    }

    /**
     * Actualiza una fila de la tabla tblRequisito.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblRequisito SET $setStr WHERE idRequisito='".addslashes($this->_data['idRequisito'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblRequisito.
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
        if( $this->_db->executeQuery("INSERT INTO tblRequisito($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblRequisito.
     */
    public function delete(){
        $where = array();
        $where[] = "idRequisito="."'".addslashes($this->idRequisito)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblRequisito WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idRequisito'.
      *
      * @return integer
      */
    public function getIdRequisito(){
        return $this->idRequisito;
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
     * Obtiene todos los elementos relacionados de la tabla 'trelRequisitoConvocatoria'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelRequisitoConvocatorias( $orderBy='' ){

        include_once('TrelRequisitoConvocatoria.inc');
        return TrelRequisitoConvocatoria::findByTblRequisito( $this->_db, $this->idRequisito, $orderBy );

    }
}
?>