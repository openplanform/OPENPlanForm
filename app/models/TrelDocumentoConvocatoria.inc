<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 10 de December de 2010 a las 06:28:02
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TrelDocumentoConvocatoriaSearch.inc' );
require_once( 'TrelDocumentoConvocatoriaPK.inc' );

/**
 * Objeto para acceder a la tabla trelDocumentoConvocatoria.
 *
 * @package dataAccess
 */
class TrelDocumentoConvocatoria extends OwlGenericDO{

    /**
     * Atributo que representa el campo "fkConvocatoria"
     * @var integer
     */
    public $fkConvocatoria;

    /**
     * Atributo que representa el campo "fkDocumento"
     * @var integer
     */
    public $fkDocumento;

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
        $this->fkDocumento = $data['fkDocumento'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelDocumentoConvocatoria segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelDocumentoConvocatoriaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelDocumentoConvocatoria';
        $where = array();
        if( $tmp = $searchItem->fkConvocatoria ){
            $where[] = "fkConvocatoria='$tmp'";
        }
        if( $tmp = $searchItem->fkDocumento ){
            $where[] = "fkDocumento='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TrelDocumentoConvocatoria' );
}

    /**
     * Obtiene todas las filas de la tabla trelDocumentoConvocatoria.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelDocumentoConvocatoria';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelDocumentoConvocatoria' );
    }

    /**
     * Obtiene el elemento de la tabla trelDocumentoConvocatoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkConvocatoria valor del campo 'fkConvocatoria'.
     * @param integer $fkDocumento valor del campo 'fkDocumento'.
     * @return TrelDocumentoConvocatoria
     */
    public static function findByPrimaryKey( $db, $fkConvocatoria, $fkDocumento ){

       $db->executeQuery("SELECT * FROM trelDocumentoConvocatoria WHERE fkConvocatoria = '$fkConvocatoria' AND fkDocumento = '$fkDocumento'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TrelDocumentoConvocatoria');

    }

    /**
     * Obtiene el elemento de la tabla trelDocumentoConvocatoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelDocumentoConvocatoriaPK $pk Objeto de la clave primaria.
     * @return TrelDocumentoConvocatoria
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkConvocatoria='".$pk->fkConvocatoria."'";
        $where[]="fkDocumento='".$pk->fkDocumento."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelDocumentoConvocatoria WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TrelDocumentoConvocatoria');

    }

    /**
     * Obtiene todas las filas de la tabla trelDocumentoConvocatoria que coinciden con el criterio fkDocumento='$fkDocumento'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkDocumento string Valor del campo fkDocumento.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblDocumento( $db, $fkDocumento, $orderBy='' ){
         $sql = "SELECT * FROM trelDocumentoConvocatoria WHERE fkDocumento='$fkDocumento'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelDocumentoConvocatoria' );
     }

    /**
     * Obtiene todas las filas de la tabla trelDocumentoConvocatoria que coinciden con el criterio fkConvocatoria='$fkConvocatoria'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkConvocatoria string Valor del campo fkConvocatoria.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblConvocatoria( $db, $fkConvocatoria, $orderBy='' ){
         $sql = "SELECT * FROM trelDocumentoConvocatoria WHERE fkConvocatoria='$fkConvocatoria'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelDocumentoConvocatoria' );
     }

    /**
     * Actualiza una fila de la tabla trelDocumentoConvocatoria.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkConvocatoria=' . ( ( ( $value = $this->fkConvocatoria ) === null || !isset($this->fkConvocatoria) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkDocumento=' . ( ( ( $value = $this->fkDocumento ) === null || !isset($this->fkDocumento) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelDocumentoConvocatoria SET $setStr WHERE fkConvocatoria='".addslashes($this->_data['fkConvocatoria'])."' AND fkDocumento='".addslashes($this->_data['fkDocumento'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelDocumentoConvocatoria.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkConvocatoria';
        $attributes[] = 'fkDocumento';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkConvocatoria ) === null || !isset($this->fkConvocatoria) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkDocumento ) === null || !isset($this->fkDocumento) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelDocumentoConvocatoria($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkConvocatoria, $this->fkDocumento );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelDocumentoConvocatoria.
     */
    public function delete(){
        $where = array();
        $where[] = "fkConvocatoria="."'".addslashes($this->fkConvocatoria)."'";
        $where[] = "fkDocumento="."'".addslashes($this->fkDocumento)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelDocumentoConvocatoria WHERE $where");
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
      * Obtiene el valor del atributo 'fkDocumento'.
      *
      * @return integer
      */
    public function getFkDocumento(){
        return $this->fkDocumento;
    }

    /**
      * Establece el valor del atributo 'fkDocumento'.
      *
      * @param integer Valor.
      */
    public function setFkDocumento( $value ){

        $this->fkDocumento = $value;

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblDocumento' relacionado.
     *
     * @return TblDocumento
     */
    public function getTblDocumento(){
        require_once('TblDocumento.inc');
        return TblDocumento::findByPrimaryKey( $this->_db, $this->fkDocumento );
    }

    /**
     * Asigna el objeto 'TblDocumento' relacionado.
     *
     * @param TblDocumento $dataObject
     */
    public function setTblDocumento( $dataObject ){
        require_once('TblDocumento.inc');
        $this->setFkDocumento( $dataObject->getIdDocumento() );
    }

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
}
?>