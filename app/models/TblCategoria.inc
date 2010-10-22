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
require_once( 'TblCategoriaSearch.inc' );
require_once( 'TblCategoriaPK.inc' );

/**
 * Objeto para acceder a la tabla tblCategoria.
 *
 * @package dataAccess
 */
class TblCategoria extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idCategoria"
     * @var integer
     */
    public $idCategoria;

    /**
     * Atributo que representa el campo "fkPadre"
     * @var integer
     */
    public $fkPadre;

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
        $this->idCategoria = $data['idCategoria'];
        $this->fkPadre = $data['fkPadre'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblCategoria segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblCategoriaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblCategoria';
        $where = array();
        if( $tmp = $searchItem->idCategoria ){
            $where[] = "idCategoria='$tmp'";
        }
        if( $tmp = $searchItem->fkPadre ){
            $where[] = "fkPadre='$tmp'";
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
        return NingenGenericDO::createCollection( $db, $sql, 'TblCategoria' );
}

    /**
     * Obtiene todas las filas de la tabla tblCategoria.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblCategoria';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblCategoria' );
    }

    /**
     * Obtiene el elemento de la tabla tblCategoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idCategoria valor del campo 'idCategoria'.
     * @param integer $fkPadre valor del campo 'fkPadre'.
     * @return TblCategoria
     */
    public static function findByPrimaryKey( $db, $idCategoria, $fkPadre ){

       $db->executeQuery("SELECT * FROM tblCategoria WHERE idCategoria = '$idCategoria' AND fkPadre = '$fkPadre'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TblCategoria');

    }

    /**
     * Obtiene el elemento de la tabla tblCategoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblCategoriaPK $pk Objeto de la clave primaria.
     * @return TblCategoria
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idCategoria='".$pk->idCategoria."'";
        $where[]="fkPadre='".$pk->fkPadre."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblCategoria WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TblCategoria');

    }

    /**
     * Obtiene todas las filas de la tabla tblCategoria que coinciden con el criterio fkPadre='$fkPadre'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPadre string Valor del campo fkPadre.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCategoria( $db, $fkPadre, $orderBy='' ){
         $sql = "SELECT * FROM tblCategoria WHERE fkPadre='$fkPadre'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblCategoria' );
     }

    /**
     * Actualiza una fila de la tabla tblCategoria.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkPadre=' . ( ( ( $value = $this->fkPadre ) === null || !isset($this->fkPadre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblCategoria SET $setStr WHERE idCategoria='".addslashes($this->_data['idCategoria'])."' AND fkPadre='".addslashes($this->_data['fkPadre'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblCategoria.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkPadre';
        $attributes[] = 'vNombre';
        $attributes[] = 'vDescripcion';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkPadre ) === null || !isset($this->fkPadre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblCategoria($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId(), $this->fkPadre );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblCategoria.
     */
    public function delete(){
        $where = array();
        $where[] = "idCategoria="."'".addslashes($this->idCategoria)."'";
        $where[] = "fkPadre="."'".addslashes($this->fkPadre)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblCategoria WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idCategoria'.
      *
      * @return integer
      */
    public function getIdCategoria(){
        return $this->idCategoria;
    }

    /**
      * Obtiene el valor del atributo 'fkPadre'.
      *
      * @return integer
      */
    public function getFkPadre(){
        return $this->fkPadre;
    }

    /**
      * Establece el valor del atributo 'fkPadre'.
      *
      * @param integer Valor.
      */
    public function setFkPadre( $value ){

        $this->fkPadre = $value;

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
     * Obtiene todos los elementos relacionados de la tabla 'tblCategoria'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblCategorias( $orderBy='' ){

        include_once('TblCategoria.inc');
        return TblCategoria::findByTblCategoria( $this->_db, $this->idCategoria, $this->fkPadre, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblCurso'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblCursos( $orderBy='' ){

        include_once('TblCurso.inc');
        return TblCurso::findByTblCategoria( $this->_db, $this->idCategoria, $this->fkPadre, $orderBy );

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblCategoria' relacionado.
     *
     * @return TblCategoria
     */
    public function getTblCategoria(){
        require_once('TblCategoria.inc');
        return TblCategoria::findByPrimaryKey( $this->_db, $this->fkPadre );
    }

    /**
     * Asigna el objeto 'TblCategoria' relacionado.
     *
     * @param TblCategoria $dataObject
     */
    public function setTblCategoria( $dataObject ){
        require_once('TblCategoria.inc');
        $this->setFkPadre( $dataObject->getIdCategoria() );
    }
}
?>