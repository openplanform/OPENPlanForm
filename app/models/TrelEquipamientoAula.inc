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
require_once( 'TrelEquipamientoAulaSearch.inc' );
require_once( 'TrelEquipamientoAulaPK.inc' );

/**
 * Objeto para acceder a la tabla trelEquipamientoAula.
 *
 * @package dataAccess
 */
class TrelEquipamientoAula extends OwlGenericDO{

    /**
     * Atributo que representa el campo "fkAula"
     * @var integer
     */
    public $fkAula;

    /**
     * Atributo que representa el campo "fkEquipamiento"
     * @var integer
     */
    public $fkEquipamiento;

    /**
     * Atributo que representa el campo "iCantidad"
     * @var integer
     */
    public $iCantidad;

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
        $this->fkAula = $data['fkAula'];
        $this->fkEquipamiento = $data['fkEquipamiento'];
        $this->iCantidad = $data['iCantidad'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla trelEquipamientoAula segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelEquipamientoAulaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM trelEquipamientoAula';
        $where = array();
        if( $tmp = $searchItem->fkAula ){
            $where[] = "fkAula='$tmp'";
        }
        if( $tmp = $searchItem->fkEquipamiento ){
            $where[] = "fkEquipamiento='$tmp'";
        }
        if( $tmp = $searchItem->iCantidad ){
            $where[] = "iCantidad='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TrelEquipamientoAula' );
}

    /**
     * Obtiene todas las filas de la tabla trelEquipamientoAula.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM trelEquipamientoAula';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelEquipamientoAula' );
    }

    /**
     * Obtiene el elemento de la tabla trelEquipamientoAula que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $fkAula valor del campo 'fkAula'.
     * @param integer $fkEquipamiento valor del campo 'fkEquipamiento'.
     * @return TrelEquipamientoAula
     */
    public static function findByPrimaryKey( $db, $fkAula, $fkEquipamiento ){

       $db->executeQuery("SELECT * FROM trelEquipamientoAula WHERE fkAula = '$fkAula' AND fkEquipamiento = '$fkEquipamiento'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TrelEquipamientoAula');

    }

    /**
     * Obtiene el elemento de la tabla trelEquipamientoAula que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TrelEquipamientoAulaPK $pk Objeto de la clave primaria.
     * @return TrelEquipamientoAula
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="fkAula='".$pk->fkAula."'";
        $where[]="fkEquipamiento='".$pk->fkEquipamiento."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM trelEquipamientoAula WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TrelEquipamientoAula');

    }

    /**
     * Obtiene todas las filas de la tabla trelEquipamientoAula que coinciden con el criterio fkAula='$fkAula'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkAula string Valor del campo fkAula.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblAula( $db, $fkAula, $orderBy='' ){
         $sql = "SELECT * FROM trelEquipamientoAula WHERE fkAula='$fkAula'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelEquipamientoAula' );
     }

    /**
     * Obtiene todas las filas de la tabla trelEquipamientoAula que coinciden con el criterio fkEquipamiento='$fkEquipamiento'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkEquipamiento string Valor del campo fkEquipamiento.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblEquipamiento( $db, $fkEquipamiento, $orderBy='' ){
         $sql = "SELECT * FROM trelEquipamientoAula WHERE fkEquipamiento='$fkEquipamiento'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TrelEquipamientoAula' );
     }

    /**
     * Actualiza una fila de la tabla trelEquipamientoAula.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkAula=' . ( ( ( $value = $this->fkAula ) === null || !isset($this->fkAula) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkEquipamiento=' . ( ( ( $value = $this->fkEquipamiento ) === null || !isset($this->fkEquipamiento) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'iCantidad=' . ( ( ( $value = $this->iCantidad ) === null || !isset($this->iCantidad) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE trelEquipamientoAula SET $setStr WHERE fkAula='".addslashes($this->_data['fkAula'])."' AND fkEquipamiento='".addslashes($this->_data['fkEquipamiento'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla trelEquipamientoAula.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkAula';
        $attributes[] = 'fkEquipamiento';
        $attributes[] = 'iCantidad';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkAula ) === null || !isset($this->fkAula) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkEquipamiento ) === null || !isset($this->fkEquipamiento) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->iCantidad ) === null || !isset($this->iCantidad) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO trelEquipamientoAula($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->fkAula, $this->fkEquipamiento );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla trelEquipamientoAula.
     */
    public function delete(){
        $where = array();
        $where[] = "fkAula="."'".addslashes($this->fkAula)."'";
        $where[] = "fkEquipamiento="."'".addslashes($this->fkEquipamiento)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM trelEquipamientoAula WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'fkAula'.
      *
      * @return integer
      */
    public function getFkAula(){
        return $this->fkAula;
    }

    /**
      * Establece el valor del atributo 'fkAula'.
      *
      * @param integer Valor.
      */
    public function setFkAula( $value ){

        $this->fkAula = $value;

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

    // Relaciones

    /**
     * Obtiene el objeto 'TblAula' relacionado.
     *
     * @return TblAula
     */
    public function getTblAula(){
        require_once('TblAula.inc');
        return TblAula::findByPrimaryKey( $this->_db, $this->fkAula );
    }

    /**
     * Asigna el objeto 'TblAula' relacionado.
     *
     * @param TblAula $dataObject
     */
    public function setTblAula( $dataObject ){
        require_once('TblAula.inc');
        $this->setFkAula( $dataObject->getIdAula() );
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