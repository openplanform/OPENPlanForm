<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 29 de December de 2010 a las 10:57:19
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TrelEstudioPersonaSearch.inc' );
require_once( 'TrelEstudioPersonaPK.inc' );

/**
 * Objeto para acceder a la tabla trelEstudioPersona.
 *
 * @package dataAccess
 */
class TrelEstudioPersona extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idEstudioPersona"
     * @var integer
     */
    public $idEstudioPersona;

    /**
     * Atributo que representa el campo "fkTipoEstudio"
     * @var integer
     */
    public $fkTipoEstudio;

    /**
     * Atributo que representa el campo "fkPersona"
     * @var integer
     */
    public $fkPersona;

    /**
     * Atributo que representa el campo "iAnyo"
     * @var string
     */
    public $iAnyo;

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
        $this->idEstudioPersona = $data['idEstudioPersona'];
        $this->fkTipoEstudio = $data['fkTipoEstudio'];
        $this->fkPersona = $data['fkPersona'];
        $this->iAnyo = $data['iAnyo'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelEstudioPersona segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelEstudioPersonaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelEstudioPersona';
        $where = array();
        if( $tmp = $searchItem->idEstudioPersona ){
            $where[] = "idEstudioPersona='$tmp'";
        }
        if( $tmp = $searchItem->fkTipoEstudio ){
            $where[] = "fkTipoEstudio='$tmp'";
        }
        if( $tmp = $searchItem->fkPersona ){
            $where[] = "fkPersona='$tmp'";
        }
        if( $tmp = $searchItem->iAnyo ){
            $where[] = "iAnyo='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TrelEstudioPersona' );
}

    /**
     * Obtiene todas las filas de la tabla trelEstudioPersona.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelEstudioPersona';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelEstudioPersona' );
    }

    /**
     * Obtiene el elemento de la tabla trelEstudioPersona que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idEstudioPersona valor del campo 'idEstudioPersona'.
     * @param integer $fkTipoEstudio valor del campo 'fkTipoEstudio'.
     * @param integer $fkPersona valor del campo 'fkPersona'.
     * @return TrelEstudioPersona
     */
    public static function findByPrimaryKey( $db, $idEstudioPersona, $fkTipoEstudio, $fkPersona ){

       $db->executeQuery("SELECT * FROM trelEstudioPersona WHERE idEstudioPersona = '$idEstudioPersona' AND fkTipoEstudio = '$fkTipoEstudio' AND fkPersona = '$fkPersona'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TrelEstudioPersona');

    }

    /**
     * Obtiene el elemento de la tabla trelEstudioPersona que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelEstudioPersonaPK $pk Objeto de la clave primaria.
     * @return TrelEstudioPersona
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idEstudioPersona='".$pk->idEstudioPersona."'";
        $where[]="fkTipoEstudio='".$pk->fkTipoEstudio."'";
        $where[]="fkPersona='".$pk->fkPersona."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelEstudioPersona WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TrelEstudioPersona');

    }

    /**
     * Obtiene todas las filas de la tabla trelEstudioPersona que coinciden con el criterio fkTipoEstudio='$fkTipoEstudio'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkTipoEstudio string Valor del campo fkTipoEstudio.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblEstudio( $db, $fkTipoEstudio, $orderBy='' ){
         $sql = "SELECT * FROM trelEstudioPersona WHERE fkTipoEstudio='$fkTipoEstudio'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelEstudioPersona' );
     }

    /**
     * Obtiene todas las filas de la tabla trelEstudioPersona que coinciden con el criterio fkPersona='$fkPersona'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPersona string Valor del campo fkPersona.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPersona( $db, $fkPersona, $orderBy='' ){
         $sql = "SELECT * FROM trelEstudioPersona WHERE fkPersona='$fkPersona'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelEstudioPersona' );
     }

    /**
     * Actualiza una fila de la tabla trelEstudioPersona.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkTipoEstudio=' . ( ( ( $value = $this->fkTipoEstudio ) === null || !isset($this->fkTipoEstudio) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkPersona=' . ( ( ( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iAnyo=' . ( ( ( $value = $this->iAnyo ) === null || !isset($this->iAnyo) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelEstudioPersona SET $setStr WHERE idEstudioPersona='".addslashes($this->_data['idEstudioPersona'])."' AND fkTipoEstudio='".addslashes($this->_data['fkTipoEstudio'])."' AND fkPersona='".addslashes($this->_data['fkPersona'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelEstudioPersona.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkTipoEstudio';
        $attributes[] = 'fkPersona';
        $attributes[] = 'iAnyo';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkTipoEstudio ) === null || !isset($this->fkTipoEstudio) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iAnyo ) === null || !isset($this->iAnyo) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelEstudioPersona($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId(), $this->fkTipoEstudio, $this->fkPersona );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelEstudioPersona.
     */
    public function delete(){
        $where = array();
        $where[] = "idEstudioPersona="."'".addslashes($this->idEstudioPersona)."'";
        $where[] = "fkTipoEstudio="."'".addslashes($this->fkTipoEstudio)."'";
        $where[] = "fkPersona="."'".addslashes($this->fkPersona)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelEstudioPersona WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idEstudioPersona'.
      *
      * @return integer
      */
    public function getIdEstudioPersona(){
        return $this->idEstudioPersona;
    }

    /**
      * Obtiene el valor del atributo 'fkTipoEstudio'.
      *
      * @return integer
      */
    public function getFkTipoEstudio(){
        return $this->fkTipoEstudio;
    }

    /**
      * Establece el valor del atributo 'fkTipoEstudio'.
      *
      * @param integer Valor.
      */
    public function setFkTipoEstudio( $value ){

        $this->fkTipoEstudio = $value;

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
      * Obtiene el valor del atributo 'iAnyo'.
      *
      * @return string
      */
    public function getIAnyo(){
        return $this->iAnyo;
    }

    /**
      * Establece el valor del atributo 'iAnyo'.
      *
      * @param string Valor.
      */
    public function setIAnyo( $value ){

        $this->iAnyo = $value;

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblEstudio' relacionado.
     *
     * @return TblEstudio
     */
    public function getTblEstudio(){
        require_once('TblEstudio.inc');
        return TblEstudio::findByPrimaryKey( $this->_db, $this->fkTipoEstudio );
    }

    /**
     * Asigna el objeto 'TblEstudio' relacionado.
     *
     * @param TblEstudio $dataObject
     */
    public function setTblEstudio( $dataObject ){
        require_once('TblEstudio.inc');
        $this->setFkTipoEstudio( $dataObject->getIdEstudio() );
    }

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
}
?>