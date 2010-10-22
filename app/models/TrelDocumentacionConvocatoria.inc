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
require_once( 'TrelDocumentacionConvocatoriaSearch.inc' );
require_once( 'TrelDocumentacionConvocatoriaPK.inc' );

/**
 * Objeto para acceder a la tabla trelDocumentacionConvocatoria.
 *
 * @package dataAccess
 */
class TrelDocumentacionConvocatoria extends NingenGenericDO{

    /**
     * Atributo que representa el campo "fkConvocatoria"
     * @var integer
     */
    public $fkConvocatoria;

    /**
     * Atributo que representa el campo "fkDocumentacion"
     * @var integer
     */
    public $fkDocumentacion;

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
        $this->fkDocumentacion = $data['fkDocumentacion'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelDocumentacionConvocatoria segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelDocumentacionConvocatoriaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelDocumentacionConvocatoria';
        $where = array();
        if( $tmp = $searchItem->fkConvocatoria ){
            $where[] = "fkConvocatoria='$tmp'";
        }
        if( $tmp = $searchItem->fkDocumentacion ){
            $where[] = "fkDocumentacion='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return NingenGenericDO::createCollection( $db, $sql, 'TrelDocumentacionConvocatoria' );
}

    /**
     * Obtiene todas las filas de la tabla trelDocumentacionConvocatoria.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelDocumentacionConvocatoria';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelDocumentacionConvocatoria' );
    }

    /**
     * Obtiene el elemento de la tabla trelDocumentacionConvocatoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkConvocatoria valor del campo 'fkConvocatoria'.
     * @param integer $fkDocumentacion valor del campo 'fkDocumentacion'.
     * @return TrelDocumentacionConvocatoria
     */
    public static function findByPrimaryKey( $db, $fkConvocatoria, $fkDocumentacion ){

       $db->executeQuery("SELECT * FROM trelDocumentacionConvocatoria WHERE fkConvocatoria = '$fkConvocatoria' AND fkDocumentacion = '$fkDocumentacion'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TrelDocumentacionConvocatoria');

    }

    /**
     * Obtiene el elemento de la tabla trelDocumentacionConvocatoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelDocumentacionConvocatoriaPK $pk Objeto de la clave primaria.
     * @return TrelDocumentacionConvocatoria
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkConvocatoria='".$pk->fkConvocatoria."'";
        $where[]="fkDocumentacion='".$pk->fkDocumentacion."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelDocumentacionConvocatoria WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TrelDocumentacionConvocatoria');

    }

    /**
     * Obtiene todas las filas de la tabla trelDocumentacionConvocatoria que coinciden con el criterio fkConvocatoria='$fkConvocatoria'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkConvocatoria string Valor del campo fkConvocatoria.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblConvocatoria( $db, $fkConvocatoria, $orderBy='' ){
         $sql = "SELECT * FROM trelDocumentacionConvocatoria WHERE fkConvocatoria='$fkConvocatoria'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelDocumentacionConvocatoria' );
     }

    /**
     * Obtiene todas las filas de la tabla trelDocumentacionConvocatoria que coinciden con el criterio fkDocumentacion='$fkDocumentacion'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkDocumentacion string Valor del campo fkDocumentacion.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblDocumentacion( $db, $fkDocumentacion, $orderBy='' ){
         $sql = "SELECT * FROM trelDocumentacionConvocatoria WHERE fkDocumentacion='$fkDocumentacion'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelDocumentacionConvocatoria' );
     }

    /**
     * Actualiza una fila de la tabla trelDocumentacionConvocatoria.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkConvocatoria=' . ( ( ( $value = $this->fkConvocatoria ) === null || !isset($this->fkConvocatoria) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkDocumentacion=' . ( ( ( $value = $this->fkDocumentacion ) === null || !isset($this->fkDocumentacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelDocumentacionConvocatoria SET $setStr WHERE fkConvocatoria='".addslashes($this->_data['fkConvocatoria'])."' AND fkDocumentacion='".addslashes($this->_data['fkDocumentacion'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelDocumentacionConvocatoria.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkConvocatoria';
        $attributes[] = 'fkDocumentacion';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkConvocatoria ) === null || !isset($this->fkConvocatoria) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkDocumentacion ) === null || !isset($this->fkDocumentacion) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelDocumentacionConvocatoria($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkConvocatoria, $this->fkDocumentacion );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelDocumentacionConvocatoria.
     */
    public function delete(){
        $where = array();
        $where[] = "fkConvocatoria="."'".addslashes($this->fkConvocatoria)."'";
        $where[] = "fkDocumentacion="."'".addslashes($this->fkDocumentacion)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelDocumentacionConvocatoria WHERE $where");
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
      * Obtiene el valor del atributo 'fkDocumentacion'.
      *
      * @return integer
      */
    public function getFkDocumentacion(){
        return $this->fkDocumentacion;
    }

    /**
      * Establece el valor del atributo 'fkDocumentacion'.
      *
      * @param integer Valor.
      */
    public function setFkDocumentacion( $value ){

        $this->fkDocumentacion = $value;

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
     * Obtiene el objeto 'TblDocumentacion' relacionado.
     *
     * @return TblDocumentacion
     */
    public function getTblDocumentacion(){
        require_once('TblDocumentacion.inc');
        return TblDocumentacion::findByPrimaryKey( $this->_db, $this->fkDocumentacion );
    }

    /**
     * Asigna el objeto 'TblDocumentacion' relacionado.
     *
     * @param TblDocumentacion $dataObject
     */
    public function setTblDocumentacion( $dataObject ){
        require_once('TblDocumentacion.inc');
        $this->setFkDocumentacion( $dataObject->getIdDocumentacion() );
    }
}
?>