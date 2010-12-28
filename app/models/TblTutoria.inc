<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 20 de December de 2010 a las 09:07:46
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TblTutoriaSearch.inc' );
require_once( 'TblTutoriaPK.inc' );

/**
 * Objeto para acceder a la tabla tblTutoria.
 *
 * @package dataAccess
 */
class TblTutoria extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idTutoria"
     * @var integer
     */
    public $idTutoria;

    /**
     * Atributo que representa el campo "fkCurso"
     * @var integer
     */
    public $fkCurso;

    /**
     * Atributo que representa el campo "fkModalidad"
     * @var integer
     */
    public $fkModalidad;

    /**
     * Atributo que representa el campo "fkTutor"
     * @var integer
     */
    public $fkTutor;

    /**
     * Atributo que representa el campo "iHoras"
     * @var integer
     */
    public $iHoras;

    /**
     * Atributo que representa el campo "bLunes"
     * @var boolean
     */
    public $bLunes;

    /**
     * Atributo que representa el campo "bMartes"
     * @var boolean
     */
    public $bMartes;

    /**
     * Atributo que representa el campo "bMiercoles"
     * @var boolean
     */
    public $bMiercoles;

    /**
     * Atributo que representa el campo "bJueves"
     * @var boolean
     */
    public $bJueves;

    /**
     * Atributo que representa el campo "bViernes"
     * @var boolean
     */
    public $bViernes;

    /**
     * Atributo que representa el campo "bSabado"
     * @var boolean
     */
    public $bSabado;

    /**
     * Atributo que representa el campo "bDomingo"
     * @var boolean
     */
    public $bDomingo;

    /**
     * Atributo que representa el campo "iDesdeManana"
     * @var string
     */
    public $iDesdeManana;

    /**
     * Atributo que representa el campo "iHastaManana"
     * @var string
     */
    public $iHastaManana;

    /**
     * Atributo que representa el campo "iDesdeTarde"
     * @var string
     */
    public $iDesdeTarde;

    /**
     * Atributo que representa el campo "iHastaTarde"
     * @var string
     */
    public $iHastaTarde;

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
        $this->idTutoria = $data['idTutoria'];
        $this->fkCurso = $data['fkCurso'];
        $this->fkModalidad = $data['fkModalidad'];
        $this->fkTutor = $data['fkTutor'];
        $this->iHoras = $data['iHoras'];
        $this->bLunes = $data['bLunes'];
        $this->bMartes = $data['bMartes'];
        $this->bMiercoles = $data['bMiercoles'];
        $this->bJueves = $data['bJueves'];
        $this->bViernes = $data['bViernes'];
        $this->bSabado = $data['bSabado'];
        $this->bDomingo = $data['bDomingo'];
        $this->iDesdeManana = $data['iDesdeManana'];
        $this->iHastaManana = $data['iHastaManana'];
        $this->iDesdeTarde = $data['iDesdeTarde'];
        $this->iHastaTarde = $data['iHastaTarde'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblTutoria segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblTutoriaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblTutoria';
        $where = array();
        if( $tmp = $searchItem->idTutoria ){
            $where[] = "idTutoria='$tmp'";
        }
        if( $tmp = $searchItem->fkCurso ){
            $where[] = "fkCurso='$tmp'";
        }
        if( $tmp = $searchItem->fkModalidad ){
            $where[] = "fkModalidad='$tmp'";
        }
        if( $tmp = $searchItem->fkTutor ){
            $where[] = "fkTutor='$tmp'";
        }
        if( $tmp = $searchItem->iHoras ){
            $where[] = "iHoras='$tmp'";
        }
        if( $tmp = $searchItem->bLunes ){
            $where[] = "bLunes='$tmp'";
        }
        if( $tmp = $searchItem->bMartes ){
            $where[] = "bMartes='$tmp'";
        }
        if( $tmp = $searchItem->bMiercoles ){
            $where[] = "bMiercoles='$tmp'";
        }
        if( $tmp = $searchItem->bJueves ){
            $where[] = "bJueves='$tmp'";
        }
        if( $tmp = $searchItem->bViernes ){
            $where[] = "bViernes='$tmp'";
        }
        if( $tmp = $searchItem->bSabado ){
            $where[] = "bSabado='$tmp'";
        }
        if( $tmp = $searchItem->bDomingo ){
            $where[] = "bDomingo='$tmp'";
        }
        if( $tmp = $searchItem->iDesdeManana ){
            $where[] = "iDesdeManana='$tmp'";
        }
        if( $tmp = $searchItem->iHastaManana ){
            $where[] = "iHastaManana='$tmp'";
        }
        if( $tmp = $searchItem->iDesdeTarde ){
            $where[] = "iDesdeTarde='$tmp'";
        }
        if( $tmp = $searchItem->iHastaTarde ){
            $where[] = "iHastaTarde='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblTutoria' );
}

    /**
     * Obtiene todas las filas de la tabla tblTutoria.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblTutoria';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblTutoria' );
    }

    /**
     * Obtiene el elemento de la tabla tblTutoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idTutoria valor del campo 'idTutoria'.
     * @return TblTutoria
     */
    public static function findByPrimaryKey( $db, $idTutoria ){

       $db->executeQuery("SELECT * FROM tblTutoria WHERE idTutoria = '$idTutoria'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblTutoria');

    }

    /**
     * Obtiene el elemento de la tabla tblTutoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblTutoriaPK $pk Objeto de la clave primaria.
     * @return TblTutoria
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idTutoria='".$pk->idTutoria."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblTutoria WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblTutoria');

    }

    /**
     * Obtiene todas las filas de la tabla tblTutoria que coinciden con el criterio fkTutor='$fkTutor'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkTutor string Valor del campo fkTutor.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPersona( $db, $fkTutor, $orderBy='' ){
         $sql = "SELECT * FROM tblTutoria WHERE fkTutor='$fkTutor'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblTutoria' );
     }

    /**
     * Obtiene todas las filas de la tabla tblTutoria que coinciden con el criterio fkCurso='$fkCurso'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCurso string Valor del campo fkCurso.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCurso( $db, $fkCurso, $orderBy='' ){
         $sql = "SELECT * FROM tblTutoria WHERE fkCurso='$fkCurso'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblTutoria' );
     }

    /**
     * Obtiene todas las filas de la tabla tblTutoria que coinciden con el criterio fkModalidad='$fkModalidad'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkModalidad string Valor del campo fkModalidad.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblModalidad( $db, $fkModalidad, $orderBy='' ){
         $sql = "SELECT * FROM tblTutoria WHERE fkModalidad='$fkModalidad'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblTutoria' );
     }

    /**
     * Actualiza una fila de la tabla tblTutoria.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkCurso=' . ( ( ( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkModalidad=' . ( ( ( $value = $this->fkModalidad ) === null || !isset($this->fkModalidad) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkTutor=' . ( ( ( $value = $this->fkTutor ) === null || !isset($this->fkTutor) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iHoras=' . ( ( ( $value = $this->iHoras ) === null || !isset($this->iHoras) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bLunes=' . ( ( ( $value = $this->bLunes ) === null || !isset($this->bLunes) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bMartes=' . ( ( ( $value = $this->bMartes ) === null || !isset($this->bMartes) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bMiercoles=' . ( ( ( $value = $this->bMiercoles ) === null || !isset($this->bMiercoles) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bJueves=' . ( ( ( $value = $this->bJueves ) === null || !isset($this->bJueves) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bViernes=' . ( ( ( $value = $this->bViernes ) === null || !isset($this->bViernes) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bSabado=' . ( ( ( $value = $this->bSabado ) === null || !isset($this->bSabado) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bDomingo=' . ( ( ( $value = $this->bDomingo ) === null || !isset($this->bDomingo) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iDesdeManana=' . ( ( ( $value = $this->iDesdeManana ) === null || !isset($this->iDesdeManana) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iHastaManana=' . ( ( ( $value = $this->iHastaManana ) === null || !isset($this->iHastaManana) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iDesdeTarde=' . ( ( ( $value = $this->iDesdeTarde ) === null || !isset($this->iDesdeTarde) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iHastaTarde=' . ( ( ( $value = $this->iHastaTarde ) === null || !isset($this->iHastaTarde) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblTutoria SET $setStr WHERE idTutoria='".addslashes($this->_data['idTutoria'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblTutoria.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkCurso';
        $attributes[] = 'fkModalidad';
        $attributes[] = 'fkTutor';
        $attributes[] = 'iHoras';
        $attributes[] = 'bLunes';
        $attributes[] = 'bMartes';
        $attributes[] = 'bMiercoles';
        $attributes[] = 'bJueves';
        $attributes[] = 'bViernes';
        $attributes[] = 'bSabado';
        $attributes[] = 'bDomingo';
        $attributes[] = 'iDesdeManana';
        $attributes[] = 'iHastaManana';
        $attributes[] = 'iDesdeTarde';
        $attributes[] = 'iHastaTarde';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkModalidad ) === null || !isset($this->fkModalidad) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkTutor ) === null || !isset($this->fkTutor) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iHoras ) === null || !isset($this->iHoras) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bLunes ) === null || !isset($this->bLunes) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bMartes ) === null || !isset($this->bMartes) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bMiercoles ) === null || !isset($this->bMiercoles) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bJueves ) === null || !isset($this->bJueves) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bViernes ) === null || !isset($this->bViernes) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bSabado ) === null || !isset($this->bSabado) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bDomingo ) === null || !isset($this->bDomingo) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iDesdeManana ) === null || !isset($this->iDesdeManana) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iHastaManana ) === null || !isset($this->iHastaManana) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iDesdeTarde ) === null || !isset($this->iDesdeTarde) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iHastaTarde ) === null || !isset($this->iHastaTarde) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblTutoria($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblTutoria.
     */
    public function delete(){
        $where = array();
        $where[] = "idTutoria="."'".addslashes($this->idTutoria)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblTutoria WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idTutoria'.
      *
      * @return integer
      */
    public function getIdTutoria(){
        return $this->idTutoria;
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
      * Obtiene el valor del atributo 'fkModalidad'.
      *
      * @return integer
      */
    public function getFkModalidad(){
        return $this->fkModalidad;
    }

    /**
      * Establece el valor del atributo 'fkModalidad'.
      *
      * @param integer Valor.
      */
    public function setFkModalidad( $value ){

        $this->fkModalidad = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkTutor'.
      *
      * @return integer
      */
    public function getFkTutor(){
        return $this->fkTutor;
    }

    /**
      * Establece el valor del atributo 'fkTutor'.
      *
      * @param integer Valor.
      */
    public function setFkTutor( $value ){

        $this->fkTutor = $value;

    }

    /**
      * Obtiene el valor del atributo 'iHoras'.
      *
      * @return integer
      */
    public function getIHoras(){
        return $this->iHoras;
    }

    /**
      * Establece el valor del atributo 'iHoras'.
      *
      * @param integer Valor.
      */
    public function setIHoras( $value ){

        $this->iHoras = $value;

    }

    /**
      * Obtiene el valor del atributo 'bLunes'.
      *
      * @return boolean
      */
    public function isBLunes(){
        return ($this->bLunes ? true : false);
    }

    /**
      * Establece el valor del atributo 'bLunes'.
      *
      * @param boolean Valor.
      */
    public function setBLunes( $value ){

        $this->bLunes = $value;

    }

    /**
      * Obtiene el valor del atributo 'bMartes'.
      *
      * @return boolean
      */
    public function isBMartes(){
        return ($this->bMartes ? true : false);
    }

    /**
      * Establece el valor del atributo 'bMartes'.
      *
      * @param boolean Valor.
      */
    public function setBMartes( $value ){

        $this->bMartes = $value;

    }

    /**
      * Obtiene el valor del atributo 'bMiercoles'.
      *
      * @return boolean
      */
    public function isBMiercoles(){
        return ($this->bMiercoles ? true : false);
    }

    /**
      * Establece el valor del atributo 'bMiercoles'.
      *
      * @param boolean Valor.
      */
    public function setBMiercoles( $value ){

        $this->bMiercoles = $value;

    }

    /**
      * Obtiene el valor del atributo 'bJueves'.
      *
      * @return boolean
      */
    public function isBJueves(){
        return ($this->bJueves ? true : false);
    }

    /**
      * Establece el valor del atributo 'bJueves'.
      *
      * @param boolean Valor.
      */
    public function setBJueves( $value ){

        $this->bJueves = $value;

    }

    /**
      * Obtiene el valor del atributo 'bViernes'.
      *
      * @return boolean
      */
    public function isBViernes(){
        return ($this->bViernes ? true : false);
    }

    /**
      * Establece el valor del atributo 'bViernes'.
      *
      * @param boolean Valor.
      */
    public function setBViernes( $value ){

        $this->bViernes = $value;

    }

    /**
      * Obtiene el valor del atributo 'bSabado'.
      *
      * @return boolean
      */
    public function isBSabado(){
        return ($this->bSabado ? true : false);
    }

    /**
      * Establece el valor del atributo 'bSabado'.
      *
      * @param boolean Valor.
      */
    public function setBSabado( $value ){

        $this->bSabado = $value;

    }

    /**
      * Obtiene el valor del atributo 'bDomingo'.
      *
      * @return boolean
      */
    public function isBDomingo(){
        return ($this->bDomingo ? true : false);
    }

    /**
      * Establece el valor del atributo 'bDomingo'.
      *
      * @param boolean Valor.
      */
    public function setBDomingo( $value ){

        $this->bDomingo = $value;

    }

    /**
      * Obtiene el valor del atributo 'iDesdeManana'.
      *
      * @return string
      */
    public function getIDesdeManana(){
        return $this->iDesdeManana;
    }

    /**
      * Establece el valor del atributo 'iDesdeManana'.
      *
      * @param string Valor.
      */
    public function setIDesdeManana( $value ){

        $this->iDesdeManana = $value;

    }

    /**
      * Obtiene el valor del atributo 'iHastaManana'.
      *
      * @return string
      */
    public function getIHastaManana(){
        return $this->iHastaManana;
    }

    /**
      * Establece el valor del atributo 'iHastaManana'.
      *
      * @param string Valor.
      */
    public function setIHastaManana( $value ){

        $this->iHastaManana = $value;

    }

    /**
      * Obtiene el valor del atributo 'iDesdeTarde'.
      *
      * @return string
      */
    public function getIDesdeTarde(){
        return $this->iDesdeTarde;
    }

    /**
      * Establece el valor del atributo 'iDesdeTarde'.
      *
      * @param string Valor.
      */
    public function setIDesdeTarde( $value ){

        $this->iDesdeTarde = $value;

    }

    /**
      * Obtiene el valor del atributo 'iHastaTarde'.
      *
      * @return string
      */
    public function getIHastaTarde(){
        return $this->iHastaTarde;
    }

    /**
      * Establece el valor del atributo 'iHastaTarde'.
      *
      * @param string Valor.
      */
    public function setIHastaTarde( $value ){

        $this->iHastaTarde = $value;

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblPersona' relacionado.
     *
     * @return TblPersona
     */
    public function getTblPersona(){
        require_once('TblPersona.inc');
        return TblPersona::findByPrimaryKey( $this->_db, $this->fkTutor );
    }

    /**
     * Asigna el objeto 'TblPersona' relacionado.
     *
     * @param TblPersona $dataObject
     */
    public function setTblPersona( $dataObject ){
        require_once('TblPersona.inc');
        $this->setFkTutor( $dataObject->getIdPersona() );
    }

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

    /**
     * Obtiene el objeto 'TblModalidad' relacionado.
     *
     * @return TblModalidad
     */
    public function getTblModalidad(){
        require_once('TblModalidad.inc');
        return TblModalidad::findByPrimaryKey( $this->_db, $this->fkModalidad );
    }

    /**
     * Asigna el objeto 'TblModalidad' relacionado.
     *
     * @param TblModalidad $dataObject
     */
    public function setTblModalidad( $dataObject ){
        require_once('TblModalidad.inc');
        $this->setFkModalidad( $dataObject->getIdModalidad() );
    }
}
?>