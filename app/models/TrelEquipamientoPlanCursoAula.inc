<?php
/**
 * Este archivo ha sido generado con Ningen DoGen v.0.6
 * el 15 de November de 2010 a las 08:53:54
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/NingenConnection.inc');
require_once( 'dbase/NingenGenericDO.inc');
require_once( 'TrelEquipamientoPlanCursoAulaSearch.inc' );
require_once( 'TrelEquipamientoPlanCursoAulaPK.inc' );

/**
 * Objeto para acceder a la tabla trelEquipamientoPlanCursoAula.
 *
 * @package dataAccess
 */
class TrelEquipamientoPlanCursoAula extends NingenGenericDO{

    /**
     * Atributo que representa el campo "idEquipamientoPlanCursoAula"
     * @var integer
     */
    public $idEquipamientoPlanCursoAula;

    /**
     * Atributo que representa el campo "fkEquipamiento"
     * @var integer
     */
    public $fkEquipamiento;

    /**
     * Atributo que representa el campo "fkCurso"
     * @var integer
     */
    public $fkCurso;

    /**
     * Atributo que representa el campo "iCantidad"
     * @var integer
     */
    public $iCantidad;

    /**
     * Atributo que representa el campo "ePrecio"
     * @var string
     */
    public $ePrecio;

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
        $this->idEquipamientoPlanCursoAula = $data['idEquipamientoPlanCursoAula'];
        $this->fkEquipamiento = $data['fkEquipamiento'];
        $this->fkCurso = $data['fkCurso'];
        $this->iCantidad = $data['iCantidad'];
        $this->ePrecio = $data['ePrecio'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelEquipamientoPlanCursoAula segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelEquipamientoPlanCursoAulaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelEquipamientoPlanCursoAula';
        $where = array();
        if( $tmp = $searchItem->idEquipamientoPlanCursoAula ){
            $where[] = "idEquipamientoPlanCursoAula='$tmp'";
        }
        if( $tmp = $searchItem->fkEquipamiento ){
            $where[] = "fkEquipamiento='$tmp'";
        }
        if( $tmp = $searchItem->fkCurso ){
            $where[] = "fkCurso='$tmp'";
        }
        if( $tmp = $searchItem->iCantidad ){
            $where[] = "iCantidad='$tmp'";
        }
        if( $tmp = $searchItem->ePrecio ){
            $where[] = "ePrecio='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return NingenGenericDO::createCollection( $db, $sql, 'TrelEquipamientoPlanCursoAula' );
}

    /**
     * Obtiene todas las filas de la tabla trelEquipamientoPlanCursoAula.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelEquipamientoPlanCursoAula';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelEquipamientoPlanCursoAula' );
    }

    /**
     * Obtiene el elemento de la tabla trelEquipamientoPlanCursoAula que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idEquipamientoPlanCursoAula valor del campo 'idEquipamientoPlanCursoAula'.
     * @return TrelEquipamientoPlanCursoAula
     */
    public static function findByPrimaryKey( $db, $idEquipamientoPlanCursoAula ){

       $db->executeQuery("SELECT * FROM trelEquipamientoPlanCursoAula WHERE idEquipamientoPlanCursoAula = '$idEquipamientoPlanCursoAula'");
       $data = $db->fetchRow();
       return NingenGenericDO::createDO( $db, $data, 'TrelEquipamientoPlanCursoAula');

    }

    /**
     * Obtiene el elemento de la tabla trelEquipamientoPlanCursoAula que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelEquipamientoPlanCursoAulaPK $pk Objeto de la clave primaria.
     * @return TrelEquipamientoPlanCursoAula
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idEquipamientoPlanCursoAula='".$pk->idEquipamientoPlanCursoAula."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelEquipamientoPlanCursoAula WHERE $where");
        $data = $db->fetchRow();
        return NingenGenericDO::createDO( $db, $data, 'TrelEquipamientoPlanCursoAula');

    }

    /**
     * Obtiene todas las filas de la tabla trelEquipamientoPlanCursoAula que coinciden con el criterio fkCurso='$fkCurso'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCurso string Valor del campo fkCurso.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCurso( $db, $fkCurso, $orderBy='' ){
         $sql = "SELECT * FROM trelEquipamientoPlanCursoAula WHERE fkCurso='$fkCurso'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelEquipamientoPlanCursoAula' );
     }

    /**
     * Obtiene todas las filas de la tabla trelEquipamientoPlanCursoAula que coinciden con el criterio fkEquipamiento='$fkEquipamiento'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkEquipamiento string Valor del campo fkEquipamiento.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblEquipamiento( $db, $fkEquipamiento, $orderBy='' ){
         $sql = "SELECT * FROM trelEquipamientoPlanCursoAula WHERE fkEquipamiento='$fkEquipamiento'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return NingenGenericDO::createCollection( $db, $sql, 'TrelEquipamientoPlanCursoAula' );
     }

    /**
     * Actualiza una fila de la tabla trelEquipamientoPlanCursoAula.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkEquipamiento=' . ( ( ( $value = $this->fkEquipamiento ) === null || !isset($this->fkEquipamiento) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkCurso=' . ( ( ( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iCantidad=' . ( ( ( $value = $this->iCantidad ) === null || !isset($this->iCantidad) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'ePrecio=' . ( ( ( $value = $this->ePrecio ) === null || !isset($this->ePrecio) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelEquipamientoPlanCursoAula SET $setStr WHERE idEquipamientoPlanCursoAula='".addslashes($this->_data['idEquipamientoPlanCursoAula'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelEquipamientoPlanCursoAula.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkEquipamiento';
        $attributes[] = 'fkCurso';
        $attributes[] = 'iCantidad';
        $attributes[] = 'ePrecio';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkEquipamiento ) === null || !isset($this->fkEquipamiento) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkCurso ) === null || !isset($this->fkCurso) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iCantidad ) === null || !isset($this->iCantidad) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->ePrecio ) === null || !isset($this->ePrecio) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelEquipamientoPlanCursoAula($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelEquipamientoPlanCursoAula.
     */
    public function delete(){
        $where = array();
        $where[] = "idEquipamientoPlanCursoAula="."'".addslashes($this->idEquipamientoPlanCursoAula)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelEquipamientoPlanCursoAula WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idEquipamientoPlanCursoAula'.
      *
      * @return integer
      */
    public function getIdEquipamientoPlanCursoAula(){
        return $this->idEquipamientoPlanCursoAula;
    }

    /**
      * Obtiene el valor del atributo 'fkEquipamiento'.
      *
      * @return integer
      */
    public function getFkEquipamiento(){
        return $this->fkEquipamiento;
    }

    /**
      * Establece el valor del atributo 'fkEquipamiento'.
      *
      * @param integer Valor.
      */
    public function setFkEquipamiento( $value ){

        $this->fkEquipamiento = $value;

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
      * Obtiene el valor del atributo 'iCantidad'.
      *
      * @return integer
      */
    public function getICantidad(){
        return $this->iCantidad;
    }

    /**
      * Establece el valor del atributo 'iCantidad'.
      *
      * @param integer Valor.
      */
    public function setICantidad( $value ){

        $this->iCantidad = $value;

    }

    /**
      * Obtiene el valor del atributo 'ePrecio'.
      *
      * @return string
      */
    public function getEPrecio(){
        return $this->ePrecio;
    }

    /**
      * Establece el valor del atributo 'ePrecio'.
      *
      * @param string Valor.
      */
    public function setEPrecio( $value ){

        $this->ePrecio = $value;

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
     * Obtiene el objeto 'TblEquipamiento' relacionado.
     *
     * @return TblEquipamiento
     */
    public function getTblEquipamiento(){
        require_once('TblEquipamiento.inc');
        return TblEquipamiento::findByPrimaryKey( $this->_db, $this->fkEquipamiento );
    }

    /**
     * Asigna el objeto 'TblEquipamiento' relacionado.
     *
     * @param TblEquipamiento $dataObject
     */
    public function setTblEquipamiento( $dataObject ){
        require_once('TblEquipamiento.inc');
        $this->setFkEquipamiento( $dataObject->getIdEquipamiento() );
    }
}
?>