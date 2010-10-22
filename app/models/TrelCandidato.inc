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
require_once( 'TrelCandidatoSearch.inc' );
require_once( 'TrelCandidatoPK.inc' );

/**
 * Objeto para acceder a la tabla trelCandidato.
 *
 * @package dataAccess
 */
class TrelCandidato extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idCandidato"
     * @var integer
     */
    public $idCandidato;

    /**
     * Atributo que representa el campo "fkPersona"
     * @var integer
     */
    public $fkPersona;

    /**
     * Atributo que representa el campo "fkPlanCursoCentro"
     * @var integer
     */
    public $fkPlanCursoCentro;

    /**
     * Atributo que representa el campo "dAlta"
     * @var string
     */
    public $dAlta;

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
        $this->idCandidato = $data['idCandidato'];
        $this->fkPersona = $data['fkPersona'];
        $this->fkPlanCursoCentro = $data['fkPlanCursoCentro'];
        $this->dAlta = $data['dAlta'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelCandidato segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelCandidatoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelCandidato';
        $where = array();
        if( $tmp = $searchItem->idCandidato ){
            $where[] = "idCandidato='$tmp'";
        }
        if( $tmp = $searchItem->fkPersona ){
            $where[] = "fkPersona='$tmp'";
        }
        if( $tmp = $searchItem->fkPlanCursoCentro ){
            $where[] = "fkPlanCursoCentro='$tmp'";
        }
        if( $tmp = $searchItem->dAlta ){
            $where[] = "dAlta='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return NingenGenericDO::createCollection( $db, $sql, 'TrelCandidato' );
}

    /**
     * Obtiene todas las filas de la tabla trelCandidato.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelCandidato';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelCandidato' );
    }

    /**
     * Obtiene el elemento de la tabla trelCandidato que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idCandidato valor del campo 'idCandidato'.
     * @return TrelCandidato
     */
    public static function findByPrimaryKey( $db, $idCandidato ){

       $db->executeQuery("SELECT * FROM trelCandidato WHERE idCandidato = '$idCandidato'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TrelCandidato');

    }

    /**
     * Obtiene el elemento de la tabla trelCandidato que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelCandidatoPK $pk Objeto de la clave primaria.
     * @return TrelCandidato
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idCandidato='".$pk->idCandidato."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelCandidato WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TrelCandidato');

    }

    /**
     * Obtiene todas las filas de la tabla trelCandidato que coinciden con el criterio fkPersona='$fkPersona'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPersona string Valor del campo fkPersona.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPersona( $db, $fkPersona, $orderBy='' ){
         $sql = "SELECT * FROM trelCandidato WHERE fkPersona='$fkPersona'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelCandidato' );
     }

    /**
     * Obtiene todas las filas de la tabla trelCandidato que coinciden con el criterio fkPlanCursoCentro='$fkPlanCursoCentro'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPlanCursoCentro string Valor del campo fkPlanCursoCentro.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCurso( $db, $fkPlanCursoCentro, $orderBy='' ){
         $sql = "SELECT * FROM trelCandidato WHERE fkPlanCursoCentro='$fkPlanCursoCentro'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelCandidato' );
     }

    /**
     * Actualiza una fila de la tabla trelCandidato.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkPersona=' . ( ( ( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkPlanCursoCentro=' . ( ( ( $value = $this->fkPlanCursoCentro ) === null || !isset($this->fkPlanCursoCentro) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dAlta=' . ( ( ( $value = $this->dAlta ) === null || !isset($this->dAlta) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelCandidato SET $setStr WHERE idCandidato='".addslashes($this->_data['idCandidato'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelCandidato.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkPersona';
        $attributes[] = 'fkPlanCursoCentro';
        $attributes[] = 'dAlta';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkPlanCursoCentro ) === null || !isset($this->fkPlanCursoCentro) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dAlta ) === null || !isset($this->dAlta) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelCandidato($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelCandidato.
     */
    public function delete(){
        $where = array();
        $where[] = "idCandidato="."'".addslashes($this->idCandidato)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelCandidato WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idCandidato'.
      *
      * @return integer
      */
    public function getIdCandidato(){
        return $this->idCandidato;
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
      * Obtiene el valor del atributo 'fkPlanCursoCentro'.
      *
      * @return integer
      */
    public function getFkPlanCursoCentro(){
        return $this->fkPlanCursoCentro;
    }

    /**
      * Establece el valor del atributo 'fkPlanCursoCentro'.
      *
      * @param integer Valor.
      */
    public function setFkPlanCursoCentro( $value ){

        $this->fkPlanCursoCentro = $value;

    }

    /**
      * Obtiene el valor del atributo 'dAlta'.
      *
      * @return string
      */
    public function getDAlta(){
        return $this->dAlta;
    }

    /**
      * Establece el valor del atributo 'dAlta'.
      *
      * @param string Valor.
      */
    public function setDAlta( $value ){

        $this->dAlta = $value;

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
        return TblCurso::findByPrimaryKey( $this->_db, $this->fkPlanCursoCentro );
    }

    /**
     * Asigna el objeto 'TblCurso' relacionado.
     *
     * @param TblCurso $dataObject
     */
    public function setTblCurso( $dataObject ){
        require_once('TblCurso.inc');
        $this->setFkPlanCursoCentro( $dataObject->getIdCurso() );
    }
}
?>