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
require_once( 'TrelPersonaCursoSearch.inc' );
require_once( 'TrelPersonaCursoPK.inc' );

/**
 * Objeto para acceder a la tabla trelPersonaCurso.
 *
 * @package dataAccess
 */
class TrelPersonaCurso extends NingenGenericDO{

    /**
     * Atributo que representa el campo "fkPersona"
     * @var integer
     */
    public $fkPersona;

    /**
     * Atributo que representa el campo "fkCurso"
     * @var integer
     */
    public $fkCurso;

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
        $this->fkCurso = $data['fkCurso'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelPersonaCurso segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelPersonaCursoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelPersonaCurso';
        $where = array();
        if( $tmp = $searchItem->fkPersona ){
            $where[] = "fkPersona='$tmp'";
        }
        if( $tmp = $searchItem->fkCurso ){
            $where[] = "fkCurso='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return NingenGenericDO::createCollection( $db, $sql, 'TrelPersonaCurso' );
}

    /**
     * Obtiene todas las filas de la tabla trelPersonaCurso.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelPersonaCurso';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelPersonaCurso' );
    }

    /**
     * Obtiene el elemento de la tabla trelPersonaCurso que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkPersona valor del campo 'fkPersona'.
     * @param integer $fkCurso valor del campo 'fkCurso'.
     * @return TrelPersonaCurso
     */
    public static function findByPrimaryKey( $db, $fkPersona, $fkCurso ){

       $db->executeQuery("SELECT * FROM trelPersonaCurso WHERE fkPersona = '$fkPersona' AND fkCurso = '$fkCurso'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TrelPersonaCurso');

    }

    /**
     * Obtiene el elemento de la tabla trelPersonaCurso que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelPersonaCursoPK $pk Objeto de la clave primaria.
     * @return TrelPersonaCurso
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkPersona='".$pk->fkPersona."'";
        $where[]="fkCurso='".$pk->fkCurso."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelPersonaCurso WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TrelPersonaCurso');

    }

    /**
     * Obtiene todas las filas de la tabla trelPersonaCurso que coinciden con el criterio fkPersona='$fkPersona'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPersona string Valor del campo fkPersona.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPersona( $db, $fkPersona, $orderBy='' ){
         $sql = "SELECT * FROM trelPersonaCurso WHERE fkPersona='$fkPersona'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelPersonaCurso' );
     }

    /**
     * Obtiene todas las filas de la tabla trelPersonaCurso que coinciden con el criterio fkCurso='$fkCurso'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCurso string Valor del campo fkCurso.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCurso( $db, $fkCurso, $orderBy='' ){
         $sql = "SELECT * FROM trelPersonaCurso WHERE fkCurso='$fkCurso'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelPersonaCurso' );
     }

    /**
     * Actualiza una fila de la tabla trelPersonaCurso.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkPersona=' . ( ( ( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkCurso=' . ( ( ( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelPersonaCurso SET $setStr WHERE fkPersona='".addslashes($this->_data['fkPersona'])."' AND fkCurso='".addslashes($this->_data['fkCurso'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelPersonaCurso.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkPersona';
        $attributes[] = 'fkCurso';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelPersonaCurso($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkPersona, $this->fkCurso );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelPersonaCurso.
     */
    public function delete(){
        $where = array();
        $where[] = "fkPersona="."'".addslashes($this->fkPersona)."'";
        $where[] = "fkCurso="."'".addslashes($this->fkCurso)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelPersonaCurso WHERE $where");
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