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
require_once( 'TblMaterialCursoSearch.inc' );
require_once( 'TblMaterialCursoPK.inc' );

/**
 * Objeto para acceder a la tabla tblMaterialCurso.
 *
 * @package dataAccess
 */
class TblMaterialCurso extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idMaterialCurso"
     * @var integer
     */
    public $idMaterialCurso;

    /**
     * Atributo que representa el campo "fkCurso"
     * @var integer
     */
    public $fkCurso;

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

    /**
     * Atributo que representa el campo "iCantidad"
     * @var integer
     */
    public $iCantidad;

    /**
     * Atributo que representa el campo "ePrecio"
     * @var string
     */
    public $ePrecio;

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
        $this->idMaterialCurso = $data['idMaterialCurso'];
        $this->fkCurso = $data['fkCurso'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];
        $this->iCantidad = $data['iCantidad'];
        $this->ePrecio = $data['ePrecio'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblMaterialCurso segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblMaterialCursoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblMaterialCurso';
        $where = array();
        if( $tmp = $searchItem->idMaterialCurso ){
            $where[] = "idMaterialCurso='$tmp'";
        }
        if( $tmp = $searchItem->fkCurso ){
            $where[] = "fkCurso='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->vDescripcion ){
            $where[] = "vDescripcion='$tmp'";
        }
        if( $tmp = $searchItem->iCantidad ){
            $where[] = "iCantidad='$tmp'";
        }
        if( $tmp = $searchItem->ePrecio ){
            $where[] = "ePrecio='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return NingenGenericDO::createCollection( $db, $sql, 'TblMaterialCurso' );
}

    /**
     * Obtiene todas las filas de la tabla tblMaterialCurso.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblMaterialCurso';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblMaterialCurso' );
    }

    /**
     * Obtiene el elemento de la tabla tblMaterialCurso que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idMaterialCurso valor del campo 'idMaterialCurso'.
     * @return TblMaterialCurso
     */
    public static function findByPrimaryKey( $db, $idMaterialCurso ){

       $db->executeQuery("SELECT * FROM tblMaterialCurso WHERE idMaterialCurso = '$idMaterialCurso'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TblMaterialCurso');

    }

    /**
     * Obtiene el elemento de la tabla tblMaterialCurso que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblMaterialCursoPK $pk Objeto de la clave primaria.
     * @return TblMaterialCurso
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idMaterialCurso='".$pk->idMaterialCurso."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblMaterialCurso WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TblMaterialCurso');

    }

    /**
     * Obtiene todas las filas de la tabla tblMaterialCurso que coinciden con el criterio fkCurso='$fkCurso'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCurso string Valor del campo fkCurso.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCurso( $db, $fkCurso, $orderBy='' ){
         $sql = "SELECT * FROM tblMaterialCurso WHERE fkCurso='$fkCurso'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblMaterialCurso' );
     }

    /**
     * Actualiza una fila de la tabla tblMaterialCurso.
     */
    public function update(){
        $sets = array();
        $sets[] = 'idMaterialCurso=' . ( ( ( $value = $this->idMaterialCurso ) === null || !isset($this->idMaterialCurso) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkCurso=' . ( ( ( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iCantidad=' . ( ( ( $value = $this->iCantidad ) === null || !isset($this->iCantidad) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'ePrecio=' . ( ( ( $value = $this->ePrecio ) === null || !isset($this->ePrecio) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblMaterialCurso SET $setStr WHERE idMaterialCurso='".addslashes($this->_data['idMaterialCurso'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblMaterialCurso.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'idMaterialCurso';
        $attributes[] = 'fkCurso';
        $attributes[] = 'vNombre';
        $attributes[] = 'vDescripcion';
        $attributes[] = 'iCantidad';
        $attributes[] = 'ePrecio';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->idMaterialCurso ) === null || !isset($this->idMaterialCurso) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iCantidad ) === null || !isset($this->iCantidad) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->ePrecio ) === null || !isset($this->ePrecio) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblMaterialCurso($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->idMaterialCurso );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblMaterialCurso.
     */
    public function delete(){
        $where = array();
        $where[] = "idMaterialCurso="."'".addslashes($this->idMaterialCurso)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblMaterialCurso WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idMaterialCurso'.
      *
      * @return integer
      */
    public function getIdMaterialCurso(){
        return $this->idMaterialCurso;
    }

    /**
      * Establece el valor del atributo 'idMaterialCurso'.
      *
      * @param integer Valor.
      */
    public function setIdMaterialCurso( $value ){

        $this->idMaterialCurso = $value;

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
      * Obtiene el valor del atributo 'iCantidad'.
      *
      * @return integer
      */
    public function getICantidad(){
        return $this->iCantidad;
    }

    /**
      * Establece el valor del atributo 'iCantidad'.
      *
      * @param integer Valor.
      */
    public function setICantidad( $value ){

        $this->iCantidad = $value;

    }

    /**
      * Obtiene el valor del atributo 'ePrecio'.
      *
      * @return string
      */
    public function getEPrecio(){
        return $this->ePrecio;
    }

    /**
      * Establece el valor del atributo 'ePrecio'.
      *
      * @param string Valor.
      */
    public function setEPrecio( $value ){

        $this->ePrecio = $value;

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
}
?>