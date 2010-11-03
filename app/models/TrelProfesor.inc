<?php
/**
 * Este archivo ha sido generado con Ningen DoGen v.0.6
 * el 02 de November de 2010 a las 12:43:47
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/NingenConnection.inc');
require_once( 'dbase/NingenGenericDO.inc');
require_once( 'TrelProfesorSearch.inc' );
require_once( 'TrelProfesorPK.inc' );

/**
 * Objeto para acceder a la tabla trelProfesor.
 *
 * @package dataAccess
 */
class TrelProfesor extends NingenGenericDO{

    /**
     * Atributo que representa el campo "fkPersona"
     * @var integer
     */
    public $fkPersona;

    /**
     * Atributo que representa el campo "fkPlanCursoAula"
     * @var integer
     */
    public $fkPlanCursoAula;

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
        $this->fkPlanCursoAula = $data['fkPlanCursoAula'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelProfesor segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelProfesorSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelProfesor';
        $where = array();
        if( $tmp = $searchItem->fkPersona ){
            $where[] = "fkPersona='$tmp'";
        }
        if( $tmp = $searchItem->fkPlanCursoAula ){
            $where[] = "fkPlanCursoAula='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return NingenGenericDO::createCollection( $db, $sql, 'TrelProfesor' );
}

    /**
     * Obtiene todas las filas de la tabla trelProfesor.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelProfesor';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelProfesor' );
    }

    /**
     * Obtiene el elemento de la tabla trelProfesor que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkPersona valor del campo 'fkPersona'.
     * @param integer $fkPlanCursoAula valor del campo 'fkPlanCursoAula'.
     * @return TrelProfesor
     */
    public static function findByPrimaryKey( $db, $fkPersona, $fkPlanCursoAula ){

       $db->executeQuery("SELECT * FROM trelProfesor WHERE fkPersona = '$fkPersona' AND fkPlanCursoAula = '$fkPlanCursoAula'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TrelProfesor');

    }

    /**
     * Obtiene el elemento de la tabla trelProfesor que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelProfesorPK $pk Objeto de la clave primaria.
     * @return TrelProfesor
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkPersona='".$pk->fkPersona."'";
        $where[]="fkPlanCursoAula='".$pk->fkPlanCursoAula."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelProfesor WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TrelProfesor');

    }

    /**
     * Obtiene todas las filas de la tabla trelProfesor que coinciden con el criterio fkPersona='$fkPersona'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPersona string Valor del campo fkPersona.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPersona( $db, $fkPersona, $orderBy='' ){
         $sql = "SELECT * FROM trelProfesor WHERE fkPersona='$fkPersona'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelProfesor' );
     }

    /**
     * Obtiene todas las filas de la tabla trelProfesor que coinciden con el criterio fkPlanCursoAula='$fkPlanCursoAula'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPlanCursoAula string Valor del campo fkPlanCursoAula.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCurso( $db, $fkPlanCursoAula, $orderBy='' ){
         $sql = "SELECT * FROM trelProfesor WHERE fkPlanCursoAula='$fkPlanCursoAula'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelProfesor' );
     }

    /**
     * Actualiza una fila de la tabla trelProfesor.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkPersona=' . ( ( ( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkPlanCursoAula=' . ( ( ( $value = $this->fkPlanCursoAula ) === null || !isset($this->fkPlanCursoAula) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelProfesor SET $setStr WHERE fkPersona='".addslashes($this->_data['fkPersona'])."' AND fkPlanCursoAula='".addslashes($this->_data['fkPlanCursoAula'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelProfesor.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkPersona';
        $attributes[] = 'fkPlanCursoAula';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkPlanCursoAula ) === null || !isset($this->fkPlanCursoAula) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelProfesor($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkPersona, $this->fkPlanCursoAula );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelProfesor.
     */
    public function delete(){
        $where = array();
        $where[] = "fkPersona="."'".addslashes($this->fkPersona)."'";
        $where[] = "fkPlanCursoAula="."'".addslashes($this->fkPlanCursoAula)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelProfesor WHERE $where");
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
      * Obtiene el valor del atributo 'fkPlanCursoAula'.
      *
      * @return integer
      */
    public function getFkPlanCursoAula(){
        return $this->fkPlanCursoAula;
    }

    /**
      * Establece el valor del atributo 'fkPlanCursoAula'.
      *
      * @param integer Valor.
      */
    public function setFkPlanCursoAula( $value ){

        $this->fkPlanCursoAula = $value;

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
     * Obtiene el objeto 'TblCurso' relacionado.
     *
     * @return TblCurso
     */
    public function getTblCurso(){
        require_once('TblCurso.inc');
        return TblCurso::findByPrimaryKey( $this->_db, $this->fkPlanCursoAula );
    }

    /**
     * Asigna el objeto 'TblCurso' relacionado.
     *
     * @param TblCurso $dataObject
     */
    public function setTblCurso( $dataObject ){
        require_once('TblCurso.inc');
        $this->setFkPlanCursoAula( $dataObject->getIdCurso() );
    }
}
?>