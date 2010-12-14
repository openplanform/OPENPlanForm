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
require_once( 'TrelDocumentoCursoSearch.inc' );
require_once( 'TrelDocumentoCursoPK.inc' );

/**
 * Objeto para acceder a la tabla trelDocumentoCurso.
 *
 * @package dataAccess
 */
class TrelDocumentoCurso extends OwlGenericDO{

    /**
     * Atributo que representa el campo "fkCurso"
     * @var integer
     */
    public $fkCurso;

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
        $this->fkCurso = $data['fkCurso'];
        $this->fkDocumento = $data['fkDocumento'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelDocumentoCurso segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelDocumentoCursoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelDocumentoCurso';
        $where = array();
        if( $tmp = $searchItem->fkCurso ){
            $where[] = "fkCurso='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TrelDocumentoCurso' );
}

    /**
     * Obtiene todas las filas de la tabla trelDocumentoCurso.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelDocumentoCurso';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelDocumentoCurso' );
    }

    /**
     * Obtiene el elemento de la tabla trelDocumentoCurso que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkCurso valor del campo 'fkCurso'.
     * @param integer $fkDocumento valor del campo 'fkDocumento'.
     * @return TrelDocumentoCurso
     */
    public static function findByPrimaryKey( $db, $fkCurso, $fkDocumento ){

       $db->executeQuery("SELECT * FROM trelDocumentoCurso WHERE fkCurso = '$fkCurso' AND fkDocumento = '$fkDocumento'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TrelDocumentoCurso');

    }

    /**
     * Obtiene el elemento de la tabla trelDocumentoCurso que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelDocumentoCursoPK $pk Objeto de la clave primaria.
     * @return TrelDocumentoCurso
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkCurso='".$pk->fkCurso."'";
        $where[]="fkDocumento='".$pk->fkDocumento."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelDocumentoCurso WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TrelDocumentoCurso');

    }

    /**
     * Obtiene todas las filas de la tabla trelDocumentoCurso que coinciden con el criterio fkCurso='$fkCurso'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCurso string Valor del campo fkCurso.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCurso( $db, $fkCurso, $orderBy='' ){
         $sql = "SELECT * FROM trelDocumentoCurso WHERE fkCurso='$fkCurso'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelDocumentoCurso' );
     }

    /**
     * Obtiene todas las filas de la tabla trelDocumentoCurso que coinciden con el criterio fkDocumento='$fkDocumento'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkDocumento string Valor del campo fkDocumento.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblDocumento( $db, $fkDocumento, $orderBy='' ){
         $sql = "SELECT * FROM trelDocumentoCurso WHERE fkDocumento='$fkDocumento'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelDocumentoCurso' );
     }

    /**
     * Actualiza una fila de la tabla trelDocumentoCurso.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkCurso=' . ( ( ( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkDocumento=' . ( ( ( $value = $this->fkDocumento ) === null || !isset($this->fkDocumento) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelDocumentoCurso SET $setStr WHERE fkCurso='".addslashes($this->_data['fkCurso'])."' AND fkDocumento='".addslashes($this->_data['fkDocumento'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelDocumentoCurso.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkCurso';
        $attributes[] = 'fkDocumento';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkDocumento ) === null || !isset($this->fkDocumento) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelDocumentoCurso($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkCurso, $this->fkDocumento );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelDocumentoCurso.
     */
    public function delete(){
        $where = array();
        $where[] = "fkCurso="."'".addslashes($this->fkCurso)."'";
        $where[] = "fkDocumento="."'".addslashes($this->fkDocumento)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelDocumentoCurso WHERE $where");
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
}
?>