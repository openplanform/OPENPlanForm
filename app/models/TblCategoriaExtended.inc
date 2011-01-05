<?php

require_once MODELDIR . 'TblCategoria.inc';

class TblCategoriaExtended extends TblCategoria{
	
	/**
	 * @param unknown_type $db
	 * @param unknown_type $idCategoria
	 * @return TblCategoria
	 */
	public static function findByPrimaryKey($db, $idCategoria){
		
       $db->executeQuery("SELECT * FROM tblCategoria WHERE idCategoria = '$idCategoria'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblCategoria');		
		
	}
	
}

?>