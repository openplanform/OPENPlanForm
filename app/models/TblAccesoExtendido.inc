<?php

require_once NINGENCMS_MODELDIR . 'TblAcceso.inc';

class TblAccesoExtendido extends TblAcceso{
    
    /**
     * Obtiene el elemento de la tabla tblAcceso que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idAcceso valor del campo 'idAcceso'.
     * @return TblAcceso
     */
    public static function findByPrimaryKeyId( $db, $idAcceso){

       $db->executeQuery("SELECT * FROM tblAcceso WHERE idAcceso = '$idAcceso'");
       $data = $db->fetchRow();
       
       return NingenGenericDO::createDO( $db, $data, 'TblAcceso');

    }    
    
}

?>
