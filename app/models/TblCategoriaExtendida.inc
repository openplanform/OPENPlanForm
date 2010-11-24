<?php

require_once MODELDIR . 'TblCategoria.inc';

class TblCategoriaExtendida extends TblCategoria{
    
    /**
     * Obtiene el elemento de la tabla tblCategoria que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idCategoria valor del campo 'idCategoria'.
     * @return TblCategoria
     */
    public static function findByPrimaryKeyId( $db, $idCategoria ){

       $db->executeQuery("SELECT * FROM tblCategoria WHERE idCategoria = '$idCategoria'");
       $data = $db->fetchRow();
       
       return OwlGenericDO::createDO( $db, $data, 'TblCategoria');

    }    
    
}

?>