<?php
/**
 * Este archivo ha sido generado con Ningen DoGen v.0.6
 * el 02 de November de 2010 a las 15:44:10
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/NingenConnection.inc');
require_once( 'dbase/NingenGenericDO.inc');
require_once( 'TrelPrecandidatoSearch.inc' );
require_once( 'TrelPrecandidatoPK.inc' );

/**
 * Objeto para acceder a la tabla trelPrecandidato.
 *
 * @package dataAccess
 */
class TrelPrecandidato extends NingenGenericDO{

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
        $this->fkPersona = $data['fkPersona'];
        $this->fkPlanCursoCentro = $data['fkPlanCursoCentro'];
        $this->dAlta = $data['dAlta'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelPrecandidato segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelPrecandidatoSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelPrecandidato';
        $where = array();
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
        return NingenGenericDO::createCollection( $db, $sql, 'TrelPrecandidato' );
}

    /**
     * Obtiene todas las filas de la tabla trelPrecandidato.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelPrecandidato';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelPrecandidato' );
    }

    /**
     * Obtiene el elemento de la tabla trelPrecandidato que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkPersona valor del campo 'fkPersona'.
     * @param integer $fkPlanCursoCentro valor del campo 'fkPlanCursoCentro'.
     * @return TrelPrecandidato
     */
    public static function findByPrimaryKey( $db, $fkPersona, $fkPlanCursoCentro ){

       $db->executeQuery("SELECT * FROM trelPrecandidato WHERE fkPersona = '$fkPersona' AND fkPlanCursoCentro = '$fkPlanCursoCentro'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TrelPrecandidato');

    }

    /**
     * Obtiene el elemento de la tabla trelPrecandidato que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelPrecandidatoPK $pk Objeto de la clave primaria.
     * @return TrelPrecandidato
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkPersona='".$pk->fkPersona."'";
        $where[]="fkPlanCursoCentro='".$pk->fkPlanCursoCentro."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelPrecandidato WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TrelPrecandidato');

    }

    /**
     * Obtiene todas las filas de la tabla trelPrecandidato que coinciden con el criterio fkPersona='$fkPersona'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPersona string Valor del campo fkPersona.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPersona( $db, $fkPersona, $orderBy='' ){
         $sql = "SELECT * FROM trelPrecandidato WHERE fkPersona='$fkPersona'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelPrecandidato' );
     }

    /**
     * Obtiene todas las filas de la tabla trelPrecandidato que coinciden con el criterio fkPlanCursoCentro='$fkPlanCursoCentro'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkPlanCursoCentro string Valor del campo fkPlanCursoCentro.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCurso( $db, $fkPlanCursoCentro, $orderBy='' ){
         $sql = "SELECT * FROM trelPrecandidato WHERE fkPlanCursoCentro='$fkPlanCursoCentro'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelPrecandidato' );
     }

    /**
     * Actualiza una fila de la tabla trelPrecandidato.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkPersona=' . ( ( ( $value = $this->fkPersona ) === null || !isset($this->fkPersona) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkPlanCursoCentro=' . ( ( ( $value = $this->fkPlanCursoCentro ) === null || !isset($this->fkPlanCursoCentro) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dAlta=' . ( ( ( $value = $this->dAlta ) === null || !isset($this->dAlta) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelPrecandidato SET $setStr WHERE fkPersona='".addslashes($this->_data['fkPersona'])."' AND fkPlanCursoCentro='".addslashes($this->_data['fkPlanCursoCentro'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelPrecandidato.
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
        if( $this->_db->executeQuery("INSERT INTO trelPrecandidato($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkPersona, $this->fkPlanCursoCentro );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelPrecandidato.
     */
    public function delete(){
        $where = array();
        $where[] = "fkPersona="."'".addslashes($this->fkPersona)."'";
        $where[] = "fkPlanCursoCentro="."'".addslashes($this->fkPlanCursoCentro)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelPrecandidato WHERE $where");
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