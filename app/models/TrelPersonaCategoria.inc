<?php
/**
 * Este archivo ha sido generado con Ningen DoGen v.0.6
 * el 25 de October de 2010 a las 09:30:07
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/NingenConnection.inc');
require_once( 'dbase/NingenGenericDO.inc');
require_once( 'TrelPersonaCategoriaSearch.inc' );
require_once( 'TrelPersonaCategoriaPK.inc' );

/**
 * Objeto para acceder a la tabla trelPersonaCategoria.
 *
 * @package dataAccess
 */
class TrelPersonaCategoria extends NingenGenericDO{

    /**
     * Atributo que representa el campo "fkPersona"
     * @var integer
     */
    public $fkPersona;

    /**
     * Atributo que representa el campo "fkCategoria"
     * @var integer
     */
    public $fkCategoria;

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
        $this->fkPersona = $data['fkPersona'];
        $this->fkCategoria = $data['fkCategoria'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelPersonaCategoria segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelPersonaCategoriaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelPersonaCategoria';
        $where = array();
        if( $tmp = $searchItem->fkPersona ){
            $where[] = "fkPersona='$tmp'";
        }
        if( $tmp = $searchItem->fkCategoria ){
            $where[] = "fkCategoria='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return NingenGenericDO::createCollection( $db, $sql, 'TrelPersonaCategoria' );
}

    /**
     * Obtiene todas las filas de la tabla trelPersonaCategoria.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelPersonaCategoria';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelPersonaCategoria' );
    }

    /**
     * Obtiene el elemento de la tabla trelPersonaCategoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkPersona valor del campo 'fkPersona'.
     * @param integer $fkCategoria valor del campo 'fkCategoria'.
     * @return TrelPersonaCategoria
     */
    public static function findByPrimaryKey( $db, $fkPersona, $fkCategoria ){

       $db->executeQuery("SELECT * FROM trelPersonaCategoria WHERE fkPersona = '$fkPersona' AND fkCategoria = '$fkCategoria'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TrelPersonaCategoria');

    }

    /**
     * Obtiene el elemento de la tabla trelPersonaCategoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelPersonaCategoriaPK $pk Objeto de la clave primaria.
     * @return TrelPersonaCategoria
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkPersona='".$pk->fkPersona."'";
        $where[]="fkCategoria='".$pk->fkCategoria."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelPersonaCategoria WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TrelPersonaCategoria');

    }

    /**
     * Obtiene todas las filas de la tabla trelPersonaCategoria que coinciden con el criterio fkPersona='$fkPersona'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPersona string Valor del campo fkPersona.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPersona( $db, $fkPersona, $orderBy='' ){
         $sql = "SELECT * FROM trelPersonaCategoria WHERE fkPersona='$fkPersona'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelPersonaCategoria' );
     }

    /**
     * Obtiene todas las filas de la tabla trelPersonaCategoria que coinciden con el criterio fkCategoria='$fkCategoria'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCategoria string Valor del campo fkCategoria.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCategoria( $db, $fkCategoria, $orderBy='' ){
         $sql = "SELECT * FROM trelPersonaCategoria WHERE fkCategoria='$fkCategoria'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelPersonaCategoria' );
     }

    /**
     * Actualiza una fila de la tabla trelPersonaCategoria.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkPersona=' . ( ( ( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkCategoria=' . ( ( ( $value = $this->fkCategoria ) === null || !isset($this->fkCategoria) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelPersonaCategoria SET $setStr WHERE fkPersona='".addslashes($this->_data['fkPersona'])."' AND fkCategoria='".addslashes($this->_data['fkCategoria'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelPersonaCategoria.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkPersona';
        $attributes[] = 'fkCategoria';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkCategoria ) === null || !isset($this->fkCategoria) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelPersonaCategoria($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkPersona, $this->fkCategoria );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelPersonaCategoria.
     */
    public function delete(){
        $where = array();
        $where[] = "fkPersona="."'".addslashes($this->fkPersona)."'";
        $where[] = "fkCategoria="."'".addslashes($this->fkCategoria)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelPersonaCategoria WHERE $where");
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
      * Obtiene el valor del atributo 'fkCategoria'.
      *
      * @return integer
      */
    public function getFkCategoria(){
        return $this->fkCategoria;
    }

    /**
      * Establece el valor del atributo 'fkCategoria'.
      *
      * @param integer Valor.
      */
    public function setFkCategoria( $value ){

        $this->fkCategoria = $value;

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

    /**
     * Obtiene el objeto 'TblCategoria' relacionado.
     *
     * @return TblCategoria
     */
    public function getTblCategoria(){
        require_once('TblCategoria.inc');
        return TblCategoria::findByPrimaryKey( $this->_db, $this->fkCategoria );
    }

    /**
     * Asigna el objeto 'TblCategoria' relacionado.
     *
     * @param TblCategoria $dataObject
     */
    public function setTblCategoria( $dataObject ){
        require_once('TblCategoria.inc');
        $this->setFkCategoria( $dataObject->getIdCategoria() );
    }
}
?>