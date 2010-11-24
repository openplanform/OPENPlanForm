<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 24 de November de 2010 a las 08:55:33
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TblConvocatoriaSearch.inc' );
require_once( 'TblConvocatoriaPK.inc' );

/**
 * Objeto para acceder a la tabla tblConvocatoria.
 *
 * @package dataAccess
 */
class TblConvocatoria extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idConvocatoria"
     * @var integer
     */
    public $idConvocatoria;

    /**
     * Atributo que representa el campo "fkTipoConvocatoria"
     * @var integer
     */
    public $fkTipoConvocatoria;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

    /**
     * Atributo que representa el campo "iAno"
     * @var string
     */
    public $iAno;

    /**
     * Atributo que representa el campo "ePresupuesto"
     * @var string
     */
    public $ePresupuesto;

    /**
     * Atributo que representa el campo "vDescripcion"
     * @var string
     */
    public $vDescripcion;

    /**
     * Atributo que representa el campo "mod_user"
     * @var string
     */
    public $modUser;

    /**
     * Atributo que representa el campo "last_modified"
     * @var string
     */
    public $lastModified;

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
        $this->idConvocatoria = $data['idConvocatoria'];
        $this->fkTipoConvocatoria = $data['fkTipoConvocatoria'];
        $this->vNombre = $data['vNombre'];
        $this->iAno = $data['iAno'];
        $this->ePresupuesto = $data['ePresupuesto'];
        $this->vDescripcion = $data['vDescripcion'];
        $this->modUser = $data['mod_user'];
        $this->lastModified = $data['last_modified'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblConvocatoria segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblConvocatoriaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblConvocatoria';
        $where = array();
        if( $tmp = $searchItem->idConvocatoria ){
            $where[] = "idConvocatoria='$tmp'";
        }
        if( $tmp = $searchItem->fkTipoConvocatoria ){
            $where[] = "fkTipoConvocatoria='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->iAno ){
            $where[] = "iAno='$tmp'";
        }
        if( $tmp = $searchItem->ePresupuesto ){
            $where[] = "ePresupuesto='$tmp'";
        }
        if( $tmp = $searchItem->vDescripcion ){
            $where[] = "vDescripcion='$tmp'";
        }
        if( $tmp = $searchItem->modUser ){
            $where[] = "mod_user='$tmp'";
        }
        if( $tmp = $searchItem->lastModified ){
            $where[] = "last_modified='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblConvocatoria' );
}

    /**
     * Obtiene todas las filas de la tabla tblConvocatoria.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblConvocatoria';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblConvocatoria' );
    }

    /**
     * Obtiene el elemento de la tabla tblConvocatoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idConvocatoria valor del campo 'idConvocatoria'.
     * @return TblConvocatoria
     */
    public static function findByPrimaryKey( $db, $idConvocatoria ){

       $db->executeQuery("SELECT * FROM tblConvocatoria WHERE idConvocatoria = '$idConvocatoria'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblConvocatoria');

    }

    /**
     * Obtiene el elemento de la tabla tblConvocatoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblConvocatoriaPK $pk Objeto de la clave primaria.
     * @return TblConvocatoria
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idConvocatoria='".$pk->idConvocatoria."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblConvocatoria WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblConvocatoria');

    }

    /**
     * Obtiene todas las filas de la tabla tblConvocatoria que coinciden con el criterio fkTipoConvocatoria='$fkTipoConvocatoria'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkTipoConvocatoria string Valor del campo fkTipoConvocatoria.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblTipoConvocatoria( $db, $fkTipoConvocatoria, $orderBy='' ){
         $sql = "SELECT * FROM tblConvocatoria WHERE fkTipoConvocatoria='$fkTipoConvocatoria'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblConvocatoria' );
     }

    /**
     * Actualiza una fila de la tabla tblConvocatoria.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkTipoConvocatoria=' . ( ( ( $value = $this->fkTipoConvocatoria ) === null || !isset($this->fkTipoConvocatoria) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iAno=' . ( ( ( $value = $this->iAno ) === null || !isset($this->iAno) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'ePresupuesto=' . ( ( ( $value = $this->ePresupuesto ) === null || !isset($this->ePresupuesto) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'mod_user=' . ( ( ( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'last_modified=' . ( ( ( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblConvocatoria SET $setStr WHERE idConvocatoria='".addslashes($this->_data['idConvocatoria'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblConvocatoria.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkTipoConvocatoria';
        $attributes[] = 'vNombre';
        $attributes[] = 'iAno';
        $attributes[] = 'ePresupuesto';
        $attributes[] = 'vDescripcion';
        $attributes[] = 'mod_user';
        $attributes[] = 'last_modified';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkTipoConvocatoria ) === null || !isset($this->fkTipoConvocatoria) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iAno ) === null || !isset($this->iAno) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->ePresupuesto ) === null || !isset($this->ePresupuesto) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblConvocatoria($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblConvocatoria.
     */
    public function delete(){
        $where = array();
        $where[] = "idConvocatoria="."'".addslashes($this->idConvocatoria)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblConvocatoria WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idConvocatoria'.
      *
      * @return integer
      */
    public function getIdConvocatoria(){
        return $this->idConvocatoria;
    }

    /**
      * Obtiene el valor del atributo 'fkTipoConvocatoria'.
      *
      * @return integer
      */
    public function getFkTipoConvocatoria(){
        return $this->fkTipoConvocatoria;
    }

    /**
      * Establece el valor del atributo 'fkTipoConvocatoria'.
      *
      * @param integer Valor.
      */
    public function setFkTipoConvocatoria( $value ){

        $this->fkTipoConvocatoria = $value;

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
      * Obtiene el valor del atributo 'iAno'.
      *
      * @return string
      */
    public function getIAno(){
        return $this->iAno;
    }

    /**
      * Establece el valor del atributo 'iAno'.
      *
      * @param string Valor.
      */
    public function setIAno( $value ){

        $this->iAno = $value;

    }

    /**
      * Obtiene el valor del atributo 'ePresupuesto'.
      *
      * @return string
      */
    public function getEPresupuesto(){
        return $this->ePresupuesto;
    }

    /**
      * Establece el valor del atributo 'ePresupuesto'.
      *
      * @param string Valor.
      */
    public function setEPresupuesto( $value ){

        $this->ePresupuesto = $value;

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
      * Obtiene el valor del atributo 'mod_user'.
      *
      * @return string
      */
    public function getModUser(){
        return $this->modUser;
    }

    /**
      * Establece el valor del atributo 'mod_user'.
      *
      * @param string Valor.
      */
    public function setModUser( $value ){

        $this->modUser = $value;

    }

    /**
      * Obtiene el valor del atributo 'last_modified'.
      *
      * @return string
      */
    public function getLastModified(){
        return $this->lastModified;
    }

    /**
      * Establece el valor del atributo 'last_modified'.
      *
      * @param string Valor.
      */
    public function setLastModified( $value ){

        $this->lastModified = $value;

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblPlan'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblPlans( $orderBy='' ){

        include_once('TblPlan.inc');
        return TblPlan::findByTblConvocatoria( $this->_db, $this->idConvocatoria, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelDocumentacionConvocatoria'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelDocumentacionConvocatorias( $orderBy='' ){

        include_once('TrelDocumentacionConvocatoria.inc');
        return TrelDocumentacionConvocatoria::findByTblConvocatoria( $this->_db, $this->idConvocatoria, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelRequisitoConvocatoria'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelRequisitoConvocatorias( $orderBy='' ){

        include_once('TrelRequisitoConvocatoria.inc');
        return TrelRequisitoConvocatoria::findByTblConvocatoria( $this->_db, $this->idConvocatoria, $orderBy );

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblTipoConvocatoria' relacionado.
     *
     * @return TblTipoConvocatoria
     */
    public function getTblTipoConvocatoria(){
        require_once('TblTipoConvocatoria.inc');
        return TblTipoConvocatoria::findByPrimaryKey( $this->_db, $this->fkTipoConvocatoria );
    }

    /**
     * Asigna el objeto 'TblTipoConvocatoria' relacionado.
     *
     * @param TblTipoConvocatoria $dataObject
     */
    public function setTblTipoConvocatoria( $dataObject ){
        require_once('TblTipoConvocatoria.inc');
        $this->setFkTipoConvocatoria( $dataObject->getIdTipoConvocatoria() );
    }
}
?>