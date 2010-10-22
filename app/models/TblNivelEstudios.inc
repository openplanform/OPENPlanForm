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
require_once( 'TblNivelEstudiosSearch.inc' );
require_once( 'TblNivelEstudiosPK.inc' );

/**
 * Objeto para acceder a la tabla tblNivelEstudios.
 *
 * @package dataAccess
 */
class TblNivelEstudios extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idNivelEstudios"
     * @var integer
     */
    public $idNivelEstudios;

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
        $this->idNivelEstudios = $data['idNivelEstudios'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblNivelEstudios segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblNivelEstudiosSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblNivelEstudios';
        $where = array();
        if( $tmp = $searchItem->idNivelEstudios ){
            $where[] = "idNivelEstudios='$tmp'";
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
        return NingenGenericDO::createCollection( $db, $sql, 'TblNivelEstudios' );
}

    /**
     * Obtiene todas las filas de la tabla tblNivelEstudios.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblNivelEstudios';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblNivelEstudios' );
    }

    /**
     * Obtiene el elemento de la tabla tblNivelEstudios que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idNivelEstudios valor del campo 'idNivelEstudios'.
     * @return TblNivelEstudios
     */
    public static function findByPrimaryKey( $db, $idNivelEstudios ){

       $db->executeQuery("SELECT * FROM tblNivelEstudios WHERE idNivelEstudios = '$idNivelEstudios'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TblNivelEstudios');

    }

    /**
     * Obtiene el elemento de la tabla tblNivelEstudios que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblNivelEstudiosPK $pk Objeto de la clave primaria.
     * @return TblNivelEstudios
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idNivelEstudios='".$pk->idNivelEstudios."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblNivelEstudios WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TblNivelEstudios');

    }

    /**
     * Actualiza una fila de la tabla tblNivelEstudios.
     */
    public function update(){
        $sets = array();
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblNivelEstudios SET $setStr WHERE idNivelEstudios='".addslashes($this->_data['idNivelEstudios'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblNivelEstudios.
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
        if( $this->_db->executeQuery("INSERT INTO tblNivelEstudios($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblNivelEstudios.
     */
    public function delete(){
        $where = array();
        $where[] = "idNivelEstudios="."'".addslashes($this->idNivelEstudios)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblNivelEstudios WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idNivelEstudios'.
      *
      * @return integer
      */
    public function getIdNivelEstudios(){
        return $this->idNivelEstudios;
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
     * Obtiene todos los elementos relacionados de la tabla 'tblPersona'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPersonas( $orderBy='' ){

        include_once('TblPersona.inc');
        return TblPersona::findByTblNivelEstudios( $this->_db, $this->idNivelEstudios, $orderBy );

    }
}
?>