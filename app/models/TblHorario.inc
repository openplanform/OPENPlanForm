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
require_once( 'TblHorarioSearch.inc' );
require_once( 'TblHorarioPK.inc' );

/**
 * Objeto para acceder a la tabla tblHorario.
 *
 * @package dataAccess
 */
class TblHorario extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idHorario"
     * @var integer
     */
    public $idHorario;

    /**
     * Atributo que representa el campo "iDesde"
     * @var integer
     */
    public $iDesde;

    /**
     * Atributo que representa el campo "iHasta"
     * @var integer
     */
    public $iHasta;

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
        $this->idHorario = $data['idHorario'];
        $this->iDesde = $data['iDesde'];
        $this->iHasta = $data['iHasta'];
        $this->fkCurso = $data['fkCurso'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblHorario segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblHorarioSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblHorario';
        $where = array();
        if( $tmp = $searchItem->idHorario ){
            $where[] = "idHorario='$tmp'";
        }
        if( $tmp = $searchItem->iDesde ){
            $where[] = "iDesde='$tmp'";
        }
        if( $tmp = $searchItem->iHasta ){
            $where[] = "iHasta='$tmp'";
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
        return OwlGenericDO::createCollection( $db, $sql, 'TblHorario' );
}

    /**
     * Obtiene todas las filas de la tabla tblHorario.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblHorario';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblHorario' );
    }

    /**
     * Obtiene el elemento de la tabla tblHorario que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idHorario valor del campo 'idHorario'.
     * @return TblHorario
     */
    public static function findByPrimaryKey( $db, $idHorario ){

       $db->executeQuery("SELECT * FROM tblHorario WHERE idHorario = '$idHorario'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblHorario');

    }

    /**
     * Obtiene el elemento de la tabla tblHorario que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblHorarioPK $pk Objeto de la clave primaria.
     * @return TblHorario
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idHorario='".$pk->idHorario."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblHorario WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblHorario');

    }

    /**
     * Obtiene todas las filas de la tabla tblHorario que coinciden con el criterio fkCurso='$fkCurso'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCurso string Valor del campo fkCurso.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCurso( $db, $fkCurso, $orderBy='' ){
         $sql = "SELECT * FROM tblHorario WHERE fkCurso='$fkCurso'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblHorario' );
     }

    /**
     * Actualiza una fila de la tabla tblHorario.
     */
    public function update(){
        $sets = array();
        $sets[] = 'idHorario=' . ( ( ( $value = $this->idHorario ) === null || !isset($this->idHorario) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iDesde=' . ( ( ( $value = $this->iDesde ) === null || !isset($this->iDesde) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iHasta=' . ( ( ( $value = $this->iHasta ) === null || !isset($this->iHasta) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkCurso=' . ( ( ( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblHorario SET $setStr WHERE idHorario='".addslashes($this->_data['idHorario'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblHorario.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'idHorario';
        $attributes[] = 'iDesde';
        $attributes[] = 'iHasta';
        $attributes[] = 'fkCurso';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->idHorario ) === null || !isset($this->idHorario) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iDesde ) === null || !isset($this->iDesde) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iHasta ) === null || !isset($this->iHasta) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblHorario($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->idHorario );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblHorario.
     */
    public function delete(){
        $where = array();
        $where[] = "idHorario="."'".addslashes($this->idHorario)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblHorario WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idHorario'.
      *
      * @return integer
      */
    public function getIdHorario(){
        return $this->idHorario;
    }

    /**
      * Establece el valor del atributo 'idHorario'.
      *
      * @param integer Valor.
      */
    public function setIdHorario( $value ){

        $this->idHorario = $value;

    }

    /**
      * Obtiene el valor del atributo 'iDesde'.
      *
      * @return integer
      */
    public function getIDesde(){
        return $this->iDesde;
    }

    /**
      * Establece el valor del atributo 'iDesde'.
      *
      * @param integer Valor.
      */
    public function setIDesde( $value ){

        $this->iDesde = $value;

    }

    /**
      * Obtiene el valor del atributo 'iHasta'.
      *
      * @return integer
      */
    public function getIHasta(){
        return $this->iHasta;
    }

    /**
      * Establece el valor del atributo 'iHasta'.
      *
      * @param integer Valor.
      */
    public function setIHasta( $value ){

        $this->iHasta = $value;

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