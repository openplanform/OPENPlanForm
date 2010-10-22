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
require_once( 'TblDesiderataSearch.inc' );
require_once( 'TblDesiderataPK.inc' );

/**
 * Objeto para acceder a la tabla tblDesiderata.
 *
 * @package dataAccess
 */
class TblDesiderata extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idDesiderata"
     * @var integer
     */
    public $idDesiderata;

    /**
     * Atributo que representa el campo "fkPersona"
     * @var integer
     */
    public $fkPersona;

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
        $this->idDesiderata = $data['idDesiderata'];
        $this->fkPersona = $data['fkPersona'];
        $this->vDescripcion = $data['vDescripcion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblDesiderata segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblDesiderataSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblDesiderata';
        $where = array();
        if( $tmp = $searchItem->idDesiderata ){
            $where[] = "idDesiderata='$tmp'";
        }
        if( $tmp = $searchItem->fkPersona ){
            $where[] = "fkPersona='$tmp'";
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
        return NingenGenericDO::createCollection( $db, $sql, 'TblDesiderata' );
}

    /**
     * Obtiene todas las filas de la tabla tblDesiderata.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblDesiderata';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblDesiderata' );
    }

    /**
     * Obtiene el elemento de la tabla tblDesiderata que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idDesiderata valor del campo 'idDesiderata'.
     * @return TblDesiderata
     */
    public static function findByPrimaryKey( $db, $idDesiderata ){

       $db->executeQuery("SELECT * FROM tblDesiderata WHERE idDesiderata = '$idDesiderata'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TblDesiderata');

    }

    /**
     * Obtiene el elemento de la tabla tblDesiderata que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblDesiderataPK $pk Objeto de la clave primaria.
     * @return TblDesiderata
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idDesiderata='".$pk->idDesiderata."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblDesiderata WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TblDesiderata');

    }

    /**
     * Obtiene todas las filas de la tabla tblDesiderata que coinciden con el criterio fkPersona='$fkPersona'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPersona string Valor del campo fkPersona.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPersona( $db, $fkPersona, $orderBy='' ){
         $sql = "SELECT * FROM tblDesiderata WHERE fkPersona='$fkPersona'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblDesiderata' );
     }

    /**
     * Actualiza una fila de la tabla tblDesiderata.
     */
    public function update(){
        $sets = array();
        $sets[] = 'idDesiderata=' . ( ( ( $value = $this->idDesiderata ) === null || !isset($this->idDesiderata) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkPersona=' . ( ( ( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblDesiderata SET $setStr WHERE idDesiderata='".addslashes($this->_data['idDesiderata'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblDesiderata.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'idDesiderata';
        $attributes[] = 'fkPersona';
        $attributes[] = 'vDescripcion';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->idDesiderata ) === null || !isset($this->idDesiderata) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblDesiderata($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->idDesiderata );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblDesiderata.
     */
    public function delete(){
        $where = array();
        $where[] = "idDesiderata="."'".addslashes($this->idDesiderata)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblDesiderata WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idDesiderata'.
      *
      * @return integer
      */
    public function getIdDesiderata(){
        return $this->idDesiderata;
    }

    /**
      * Establece el valor del atributo 'idDesiderata'.
      *
      * @param integer Valor.
      */
    public function setIdDesiderata( $value ){

        $this->idDesiderata = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkPersona'.
      *
      * @return integer
      */
    public function getFkPersona(){
        return $this->fkPersona;
    }

    /**
      * Establece el valor del atributo 'fkPersona'.
      *
      * @param integer Valor.
      */
    public function setFkPersona( $value ){

        $this->fkPersona = $value;

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

    // Relaciones

    /**
     * Obtiene el objeto 'TblPersona' relacionado.
     *
     * @return TblPersona
     */
    public function getTblPersona(){
        require_once('TblPersona.inc');
        return TblPersona::findByPrimaryKey( $this->_db, $this->fkPersona );
    }

    /**
     * Asigna el objeto 'TblPersona' relacionado.
     *
     * @param TblPersona $dataObject
     */
    public function setTblPersona( $dataObject ){
        require_once('TblPersona.inc');
        $this->setFkPersona( $dataObject->getIdPersona() );
    }
}
?>