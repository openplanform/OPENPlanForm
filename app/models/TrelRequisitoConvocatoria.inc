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
require_once( 'TrelRequisitoConvocatoriaSearch.inc' );
require_once( 'TrelRequisitoConvocatoriaPK.inc' );

/**
 * Objeto para acceder a la tabla trelRequisitoConvocatoria.
 *
 * @package dataAccess
 */
class TrelRequisitoConvocatoria extends OwlGenericDO{

    /**
     * Atributo que representa el campo "fkConvocatoria"
     * @var integer
     */
    public $fkConvocatoria;

    /**
     * Atributo que representa el campo "fkRequisito"
     * @var integer
     */
    public $fkRequisito;

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
        $this->fkConvocatoria = $data['fkConvocatoria'];
        $this->fkRequisito = $data['fkRequisito'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelRequisitoConvocatoria segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelRequisitoConvocatoriaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelRequisitoConvocatoria';
        $where = array();
        if( $tmp = $searchItem->fkConvocatoria ){
            $where[] = "fkConvocatoria='$tmp'";
        }
        if( $tmp = $searchItem->fkRequisito ){
            $where[] = "fkRequisito='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TrelRequisitoConvocatoria' );
}

    /**
     * Obtiene todas las filas de la tabla trelRequisitoConvocatoria.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelRequisitoConvocatoria';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelRequisitoConvocatoria' );
    }

    /**
     * Obtiene el elemento de la tabla trelRequisitoConvocatoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkConvocatoria valor del campo 'fkConvocatoria'.
     * @param integer $fkRequisito valor del campo 'fkRequisito'.
     * @return TrelRequisitoConvocatoria
     */
    public static function findByPrimaryKey( $db, $fkConvocatoria, $fkRequisito ){

       $db->executeQuery("SELECT * FROM trelRequisitoConvocatoria WHERE fkConvocatoria = '$fkConvocatoria' AND fkRequisito = '$fkRequisito'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TrelRequisitoConvocatoria');

    }

    /**
     * Obtiene el elemento de la tabla trelRequisitoConvocatoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelRequisitoConvocatoriaPK $pk Objeto de la clave primaria.
     * @return TrelRequisitoConvocatoria
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkConvocatoria='".$pk->fkConvocatoria."'";
        $where[]="fkRequisito='".$pk->fkRequisito."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelRequisitoConvocatoria WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TrelRequisitoConvocatoria');

    }

    /**
     * Obtiene todas las filas de la tabla trelRequisitoConvocatoria que coinciden con el criterio fkConvocatoria='$fkConvocatoria'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkConvocatoria string Valor del campo fkConvocatoria.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblConvocatoria( $db, $fkConvocatoria, $orderBy='' ){
         $sql = "SELECT * FROM trelRequisitoConvocatoria WHERE fkConvocatoria='$fkConvocatoria'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelRequisitoConvocatoria' );
     }

    /**
     * Obtiene todas las filas de la tabla trelRequisitoConvocatoria que coinciden con el criterio fkRequisito='$fkRequisito'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkRequisito string Valor del campo fkRequisito.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblRequisito( $db, $fkRequisito, $orderBy='' ){
         $sql = "SELECT * FROM trelRequisitoConvocatoria WHERE fkRequisito='$fkRequisito'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelRequisitoConvocatoria' );
     }

    /**
     * Actualiza una fila de la tabla trelRequisitoConvocatoria.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkConvocatoria=' . ( ( ( $value = $this->fkConvocatoria ) === null || !isset($this->fkConvocatoria) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkRequisito=' . ( ( ( $value = $this->fkRequisito ) === null || !isset($this->fkRequisito) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelRequisitoConvocatoria SET $setStr WHERE fkConvocatoria='".addslashes($this->_data['fkConvocatoria'])."' AND fkRequisito='".addslashes($this->_data['fkRequisito'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelRequisitoConvocatoria.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkConvocatoria';
        $attributes[] = 'fkRequisito';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkConvocatoria ) === null || !isset($this->fkConvocatoria) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkRequisito ) === null || !isset($this->fkRequisito) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelRequisitoConvocatoria($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkConvocatoria, $this->fkRequisito );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelRequisitoConvocatoria.
     */
    public function delete(){
        $where = array();
        $where[] = "fkConvocatoria="."'".addslashes($this->fkConvocatoria)."'";
        $where[] = "fkRequisito="."'".addslashes($this->fkRequisito)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelRequisitoConvocatoria WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'fkConvocatoria'.
      *
      * @return integer
      */
    public function getFkConvocatoria(){
        return $this->fkConvocatoria;
    }

    /**
      * Establece el valor del atributo 'fkConvocatoria'.
      *
      * @param integer Valor.
      */
    public function setFkConvocatoria( $value ){

        $this->fkConvocatoria = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkRequisito'.
      *
      * @return integer
      */
    public function getFkRequisito(){
        return $this->fkRequisito;
    }

    /**
      * Establece el valor del atributo 'fkRequisito'.
      *
      * @param integer Valor.
      */
    public function setFkRequisito( $value ){

        $this->fkRequisito = $value;

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblConvocatoria' relacionado.
     *
     * @return TblConvocatoria
     */
    public function getTblConvocatoria(){
        require_once('TblConvocatoria.inc');
        return TblConvocatoria::findByPrimaryKey( $this->_db, $this->fkConvocatoria );
    }

    /**
     * Asigna el objeto 'TblConvocatoria' relacionado.
     *
     * @param TblConvocatoria $dataObject
     */
    public function setTblConvocatoria( $dataObject ){
        require_once('TblConvocatoria.inc');
        $this->setFkConvocatoria( $dataObject->getIdConvocatoria() );
    }

    /**
     * Obtiene el objeto 'TblRequisito' relacionado.
     *
     * @return TblRequisito
     */
    public function getTblRequisito(){
        require_once('TblRequisito.inc');
        return TblRequisito::findByPrimaryKey( $this->_db, $this->fkRequisito );
    }

    /**
     * Asigna el objeto 'TblRequisito' relacionado.
     *
     * @param TblRequisito $dataObject
     */
    public function setTblRequisito( $dataObject ){
        require_once('TblRequisito.inc');
        $this->setFkRequisito( $dataObject->getIdRequisito() );
    }
}
?>