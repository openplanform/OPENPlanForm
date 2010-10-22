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
require_once( 'TblPlanSearch.inc' );
require_once( 'TblPlanPK.inc' );

/**
 * Objeto para acceder a la tabla tblPlan.
 *
 * @package dataAccess
 */
class TblPlan extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idPlan"
     * @var integer
     */
    public $idPlan;

    /**
     * Atributo que representa el campo "fkTipoPlan"
     * @var integer
     */
    public $fkTipoPlan;

    /**
     * Atributo que representa el campo "fkConvocatoria"
     * @var integer
     */
    public $fkConvocatoria;

    /**
     * Atributo que representa el campo "fkEmpresaConsultora"
     * @var integer
     */
    public $fkEmpresaConsultora;

    /**
     * Atributo que representa el campo "fkEmpresaPropietaria"
     * @var integer
     */
    public $fkEmpresaPropietaria;

    /**
     * Atributo que representa el campo "fkEstadoPlan"
     * @var integer
     */
    public $fkEstadoPlan;

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
     * Atributo que representa el campo "ePresupuestoAsignado"
     * @var string
     */
    public $ePresupuestoAsignado;

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
        $this->idPlan = $data['idPlan'];
        $this->fkTipoPlan = $data['fkTipoPlan'];
        $this->fkConvocatoria = $data['fkConvocatoria'];
        $this->fkEmpresaConsultora = $data['fkEmpresaConsultora'];
        $this->fkEmpresaPropietaria = $data['fkEmpresaPropietaria'];
        $this->fkEstadoPlan = $data['fkEstadoPlan'];
        $this->vNombre = $data['vNombre'];
        $this->vDescripcion = $data['vDescripcion'];
        $this->ePresupuestoAsignado = $data['ePresupuestoAsignado'];
        $this->modUser = $data['mod_user'];
        $this->lastModified = $data['last_modified'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblPlan segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblPlanSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblPlan';
        $where = array();
        if( $tmp = $searchItem->idPlan ){
            $where[] = "idPlan='$tmp'";
        }
        if( $tmp = $searchItem->fkTipoPlan ){
            $where[] = "fkTipoPlan='$tmp'";
        }
        if( $tmp = $searchItem->fkConvocatoria ){
            $where[] = "fkConvocatoria='$tmp'";
        }
        if( $tmp = $searchItem->fkEmpresaConsultora ){
            $where[] = "fkEmpresaConsultora='$tmp'";
        }
        if( $tmp = $searchItem->fkEmpresaPropietaria ){
            $where[] = "fkEmpresaPropietaria='$tmp'";
        }
        if( $tmp = $searchItem->fkEstadoPlan ){
            $where[] = "fkEstadoPlan='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->vDescripcion ){
            $where[] = "vDescripcion='$tmp'";
        }
        if( $tmp = $searchItem->ePresupuestoAsignado ){
            $where[] = "ePresupuestoAsignado='$tmp'";
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
        return NingenGenericDO::createCollection( $db, $sql, 'TblPlan' );
}

    /**
     * Obtiene todas las filas de la tabla tblPlan.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblPlan';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblPlan' );
    }

    /**
     * Obtiene el elemento de la tabla tblPlan que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idPlan valor del campo 'idPlan'.
     * @return TblPlan
     */
    public static function findByPrimaryKey( $db, $idPlan ){

       $db->executeQuery("SELECT * FROM tblPlan WHERE idPlan = '$idPlan'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TblPlan');

    }

    /**
     * Obtiene el elemento de la tabla tblPlan que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblPlanPK $pk Objeto de la clave primaria.
     * @return TblPlan
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idPlan='".$pk->idPlan."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblPlan WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TblPlan');

    }

    /**
     * Obtiene todas las filas de la tabla tblPlan que coinciden con el criterio fkTipoPlan='$fkTipoPlan'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkTipoPlan string Valor del campo fkTipoPlan.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblTipoPlan( $db, $fkTipoPlan, $orderBy='' ){
         $sql = "SELECT * FROM tblPlan WHERE fkTipoPlan='$fkTipoPlan'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblPlan' );
     }

    /**
     * Obtiene todas las filas de la tabla tblPlan que coinciden con el criterio fkEstadoPlan='$fkEstadoPlan'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkEstadoPlan string Valor del campo fkEstadoPlan.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblEstadoPlan( $db, $fkEstadoPlan, $orderBy='' ){
         $sql = "SELECT * FROM tblPlan WHERE fkEstadoPlan='$fkEstadoPlan'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblPlan' );
     }

    /**
     * Obtiene todas las filas de la tabla tblPlan que coinciden con el criterio fkConvocatoria='$fkConvocatoria'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkConvocatoria string Valor del campo fkConvocatoria.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblConvocatoria( $db, $fkConvocatoria, $orderBy='' ){
         $sql = "SELECT * FROM tblPlan WHERE fkConvocatoria='$fkConvocatoria'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblPlan' );
     }

	/**
     * Obtiene todas las filas de la tabla tblPlan que coinciden con el criterio fkEmpresaConsultora='$fkEmpresaConsultora'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkEmpresaConsultora string Valor del campo fkEmpresaConsultora.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblEmpresaConsultora( $db, $fkEmpresaConsultora, $orderBy='' ){
         $sql = "SELECT * FROM tblPlan WHERE fkEmpresaConsultora='$fkEmpresaConsultora'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblPlan' );
     }

    /**
     * Obtiene todas las filas de la tabla tblPlan que coinciden con el criterio fkEmpresaPropietaria='$fkEmpresaPropietaria'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkEmpresaPropietaria string Valor del campo fkEmpresaPropietaria.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblEmpresaPropietaria( $db, $fkEmpresaPropietaria, $orderBy='' ){
         $sql = "SELECT * FROM tblPlan WHERE fkEmpresaPropietaria='$fkEmpresaPropietaria'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TblPlan' );
     }

    /**
     * Actualiza una fila de la tabla tblPlan.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkTipoPlan=' . ( ( ( $value = $this->fkTipoPlan ) === null || !isset($this->fkTipoPlan) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkConvocatoria=' . ( ( ( $value = $this->fkConvocatoria ) === null || !isset($this->fkConvocatoria) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkEmpresaConsultora=' . ( ( ( $value = $this->fkEmpresaConsultora ) === null || !isset($this->fkEmpresaConsultora) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkEmpresaPropietaria=' . ( ( ( $value = $this->fkEmpresaPropietaria ) === null || !isset($this->fkEmpresaPropietaria) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkEstadoPlan=' . ( ( ( $value = $this->fkEstadoPlan ) === null || !isset($this->fkEstadoPlan) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDescripcion=' . ( ( ( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'ePresupuestoAsignado=' . ( ( ( $value = $this->ePresupuestoAsignado ) === null || !isset($this->ePresupuestoAsignado) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'mod_user=' . ( ( ( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'last_modified=' . ( ( ( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblPlan SET $setStr WHERE idPlan='".addslashes($this->_data['idPlan'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblPlan.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkTipoPlan';
        $attributes[] = 'fkConvocatoria';
        $attributes[] = 'fkEmpresaConsultora';
        $attributes[] = 'fkEmpresaPropietaria';
        $attributes[] = 'fkEstadoPlan';
        $attributes[] = 'vNombre';
        $attributes[] = 'vDescripcion';
        $attributes[] = 'ePresupuestoAsignado';
        $attributes[] = 'mod_user';
        $attributes[] = 'last_modified';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkTipoPlan ) === null || !isset($this->fkTipoPlan) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkConvocatoria ) === null || !isset($this->fkConvocatoria) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkEmpresaConsultora ) === null || !isset($this->fkEmpresaConsultora) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkEmpresaPropietaria ) === null || !isset($this->fkEmpresaPropietaria) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkEstadoPlan ) === null || !isset($this->fkEstadoPlan) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDescripcion ) === null || !isset($this->vDescripcion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->ePresupuestoAsignado ) === null || !isset($this->ePresupuestoAsignado) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblPlan($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblPlan.
     */
    public function delete(){
        $where = array();
        $where[] = "idPlan="."'".addslashes($this->idPlan)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblPlan WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idPlan'.
      *
      * @return integer
      */
    public function getIdPlan(){
        return $this->idPlan;
    }

    /**
      * Obtiene el valor del atributo 'fkTipoPlan'.
      *
      * @return integer
      */
    public function getFkTipoPlan(){
        return $this->fkTipoPlan;
    }

    /**
      * Establece el valor del atributo 'fkTipoPlan'.
      *
      * @param integer Valor.
      */
    public function setFkTipoPlan( $value ){

        $this->fkTipoPlan = $value;

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
      * Obtiene el valor del atributo 'fkEmpresaConsultora'.
      *
      * @return integer
      */
    public function getFkEmpresaConsultora(){
        return $this->fkEmpresaConsultora;
    }

    /**
      * Establece el valor del atributo 'fkEmpresaConsultora'.
      *
      * @param integer Valor.
      */
    public function setFkEmpresaConsultora( $value ){

        $this->fkEmpresaConsultora = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkEmpresaPropietaria'.
      *
      * @return integer
      */
    public function getFkEmpresaPropietaria(){
        return $this->fkEmpresaPropietaria;
    }

    /**
      * Establece el valor del atributo 'fkEmpresaPropietaria'.
      *
      * @param integer Valor.
      */
    public function setFkEmpresaPropietaria( $value ){

        $this->fkEmpresaPropietaria = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkEstadoPlan'.
      *
      * @return integer
      */
    public function getFkEstadoPlan(){
        return $this->fkEstadoPlan;
    }

    /**
      * Establece el valor del atributo 'fkEstadoPlan'.
      *
      * @param integer Valor.
      */
    public function setFkEstadoPlan( $value ){

        $this->fkEstadoPlan = $value;

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
      * Obtiene el valor del atributo 'ePresupuestoAsignado'.
      *
      * @return string
      */
    public function getEPresupuestoAsignado(){
        return $this->ePresupuestoAsignado;
    }

    /**
      * Establece el valor del atributo 'ePresupuestoAsignado'.
      *
      * @param string Valor.
      */
    public function setEPresupuestoAsignado( $value ){

        $this->ePresupuestoAsignado = $value;

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
     * Obtiene todos los elementos relacionados de la tabla 'tblCurso'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblCursos( $orderBy='' ){

        include_once('TblCurso.inc');
        return TblCurso::findByTblPlan( $this->_db, $this->idPlan, $orderBy );

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblTipoPlan' relacionado.
     *
     * @return TblTipoPlan
     */
    public function getTblTipoPlan(){
        require_once('TblTipoPlan.inc');
        return TblTipoPlan::findByPrimaryKey( $this->_db, $this->fkTipoPlan );
    }

    /**
     * Asigna el objeto 'TblTipoPlan' relacionado.
     *
     * @param TblTipoPlan $dataObject
     */
    public function setTblTipoPlan( $dataObject ){
        require_once('TblTipoPlan.inc');
        $this->setFkTipoPlan( $dataObject->getIdTipoPlan() );
    }

    /**
     * Obtiene el objeto 'TblEstadoPlan' relacionado.
     *
     * @return TblEstadoPlan
     */
    public function getTblEstadoPlan(){
        require_once('TblEstadoPlan.inc');
        return TblEstadoPlan::findByPrimaryKey( $this->_db, $this->fkEstadoPlan );
    }

    /**
     * Asigna el objeto 'TblEstadoPlan' relacionado.
     *
     * @param TblEstadoPlan $dataObject
     */
    public function setTblEstadoPlan( $dataObject ){
        require_once('TblEstadoPlan.inc');
        $this->setFkEstadoPlan( $dataObject->getIdEstadoPlan() );
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

    /**
     * Obtiene el objeto 'TblEmpresa' relacionado.
     *
     * @return TblEmpresa
     */
    public function getTblEmpresaConsultora(){
        require_once('TblEmpresa.inc');
        return TblEmpresa::findByPrimaryKey( $this->_db, $this->fkEmpresaConsultora );
    }

    /**
     * Asigna el objeto 'TblEmpresa' relacionado.
     *
     * @param TblEmpresa $dataObject
     */
    public function setTblEmpresaConsultora( $dataObject ){
        require_once('TblEmpresa.inc');
        $this->setFkEmpresaConsultora( $dataObject->getIdEmpresa() );
    }

    /**
     * Obtiene el objeto 'TblEmpresa' relacionado.
     *
     * @return TblEmpresa
     */
    public function getTblEmpresaPropietaria(){
        require_once('TblEmpresa.inc');
        return TblEmpresa::findByPrimaryKey( $this->_db, $this->fkEmpresaPropietaria );
    }

    /**
     * Asigna el objeto 'TblEmpresa' relacionado.
     *
     * @param TblEmpresa $dataObject
     */
    public function setTblEmpresaPropietaria( $dataObject ){
        require_once('TblEmpresa.inc');
        $this->setFkEmpresaPropietaria( $dataObject->getIdEmpresa() );
    }
}
?>