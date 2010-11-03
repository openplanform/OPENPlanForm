<?php

require_once 'NingenController.inc';
require_once 'helper/NingenDatabase.inc';

require_once NINGENCMS_MODELDIR . 'TblEmpresa.inc';
require_once NINGENCMS_MODELDIR . 'TblEstadoPlan.inc';
require_once NINGENCMS_MODELDIR . 'TblPais.inc';
require_once NINGENCMS_MODELDIR . 'TblPersona.inc';
require_once NINGENCMS_MODELDIR . 'TblProvincia.inc';
require_once NINGENCMS_MODELDIR . 'TblTipoConvocatoria.inc';
require_once NINGENCMS_MODELDIR . 'TblTipoPlan.inc';

class PplCacheBO {
	
	/**
     * Referencia a la base de datos
     * @var NingenConnection
     */
    protected $db;
    
    /**
     * Convocatoria indexadas por su clave
     * @var array
     */
    private $convocatoriasIDX;
    
    /**
     * Flag que indica que las convocatorias han sido cargadas
     * @var boolean
     */
    private $convocatorias_fetched = false;
    
	/**
     * Tipos de convocatoria indexados por su clave
     * @var array
     */
    private $tiposConvocatoriaIDX;
    
    /**
     * Flag que indica que los tipos de convocatoria han sido cargados
     * @var boolean
     */
    private $tiposConvocatoria_fetched = false;
	
    /**
     * Planes indexados por su clave
     * @var array
     */
    private $planesIDX;
    
    /**
     * Flag que indica que los planes han sido cargados
     * @var boolean
     */
    private $planes_fetched = false;
    
    /**
     * Tipos de plan indexados por su clave
     * @var array
     */
    private $tiposPlanIDX;
    
    /**
     * Flag que indica que los tipos de plan han sido cargados
     * @var boolean
     */
    private $tiposPlan_fetched = false;
    
    /**
     * Estados de plan indexados por su clave
     * @var array
     */
    private $estadosPlanIDX;
    
    /**
     * Flag que indica que los estados de plan han sido cargados
     * @var boolean
     */
    private $estadosPlan_fetched = false;
    
    /**
     * Requisitos indexados por su clave
     * @var array
     */
    private $requisitosIDX;
    
    /**
     * Flag que indica que los requisitos han sido cargados
     * @var boolean
     */
    private $requisitos_fetched = false;
    
    /**
     * Empresas indexadas por su clave
     * @var array
     */
    private $empresasIDX;
    
    /**
     * Flag que indica que las empresas han sido cargadas
     * @var boolean
     */
    private $empresas_fetched = false;
    
    /**
     * Academias indexadas por su clave
     * @var array
     */
    private $academiasIDX;
    
    /**
     * Flag que indica que las academias han sido cargadas
     * @var boolean
     */
    private $academias_fetched = false;
    
    /**
     * consultoras indexadas por su clave
     * @var array
     */
    private $consultorasIDX;
    
    /**
     * Flag que indica que las consultoras han sido cargadas
     * @var boolean
     */
    private $consultoras_fetched = false;
    
    /**
     * centros indexados por su clave
     * @var array
     */
    private $centrosIDX;
    
    /**
     * Flag que indica que los centros han sido cargadas
     * @var boolean
     */
    private $centros_fetched = false;
    
    /**
     * colectivos indexados por su clave
     * @var array
     */
    private $colectivosIDX;
    
    /**
     * Flag que indica que los colectivos han sido cargadas
     * @var boolean
     */
    private $colectivos_fetched = false;
    
    /**
     * modalidades indexadas por su clave
     * @var array
     */
    private $modalidadesIDX;
    
    /**
     * Flag que indica que las modalidades han sido cargadas
     * @var boolean
     */
    private $modalidades_fetched = false;
    
    /**
     * sectores indexados por su clave
     * @var array
     */
    private $sectoresIDX;
    
    /**
     * Flag que indica que los sectores han sido cargados
     * @var boolean
     */
    private $sectores_fetched = false;
    
    /**
     * categorias indexadas por su clave
     * @var array
     */
    private $categoriasIDX;
    
    /**
     * Flag que indica que las categorias han sido cargadas
     * @var boolean
     */
    private $categorias_fetched = false;
    
    /**
     * aulas indexadas por su clave
     * @var array
     */
    private $aulasIDX;
    
    /**
     * Flag que indica que las aulas han sido cargadas
     * @var boolean
     */
    private $aulas_fetched = false;
    
    /**
     * profesores indexados por su clave
     * @var array
     */
    private $profesoresIDX;
    
    /**
     * Flag que indica que los profesores han sido cargados
     * @var boolean
     */
    private $profesores_fetched = false;
    
    /**
     * personas indexadas por su clave
     * @var array
     */
    private $personasIDX;
    
    /**
     * Flag que indica que las personas han sido cargadas
     * @var boolean
     */
    private $personas_fetched = false;
    
    /**
     * Constructora, propaga la referencia a la base de datos 
     * @param NingenConnection $db
     */
    public function __construct( NingenConnection $db ){
    	
        $this->db = $db;
        
    }
    
	/**
	 * Obtiene las convocatorias
	 * @return array
	 */
	public function getConvocatorias() {
		
		if ( $this->convocatorias_fetched ){
			return $this->convocatoriasIDX;
		}
		
		$convocatoriasCOL = TblConvocatoria::findAll($this->db, 'vNombre');
		$convocatoriasIDX = array();
		
		// Se indexarán las convocatorias por su clave
		foreach ($convocatoriasCOL as $convocatoriaDO){
		    
		    $convocatoriasIDX[$convocatoriaDO->getIdConvocatoria()] = $convocatoriaDO->getVNombre();
		    
		}
		
		$this->convocatoriasIDX = $convocatoriasIDX;
		$this->convocatorias_fetched = true;
		
		return $this->convocatoriasIDX;
		
	}
    
	/**
	 * Obtiene los tipos de convocatoria
	 * @return array
	 */
	public function getTiposConvocatoria() {
		
		if ( $this->tiposConvocatoria_fetched ){
			return $this->tiposConvocatoriaIDX;
		}
		
		$tiposConvocatoriaCOL = TblTipoConvocatoria::findAll($this->db, 'vNombre');
		$tiposConvocatoriaIDX = array();
		
		// Se indexarán los tipos de convocatoria por su clave
		foreach ($tiposConvocatoriaCOL as $tipoConvocatoriaDO){
		    
		    $tiposConvocatoriaIDX[$tipoConvocatoriaDO->getIdTipoConvocatoria()] = $tipoConvocatoriaDO->getVNombre();
		    
		}
		
		$this->tiposConvocatoriaIDX = $tiposConvocatoriaIDX;
		$this->tiposConvocatoria_fetched = true;
		
		return $this->tiposConvocatoriaIDX;
		
	}
	
	/**
	 * Obtiene los planes
	 * @return array
	 */
	public function getPlanes() {
		
		if ( $this->planes_fetched ){
			return $this->planesIDX;
		}
		
		$planesCOL = TblPlan::findAll($this->db, 'vNombre');
		$planesIDX = array();
		
		// Se indexarán las planes por su clave
		foreach ($planesCOL as $planDO){
		    
		    $planesIDX[$planDO->getIdPlan()] = $planDO->getVNombre();
		    
		}
		
		$this->planesIDX = $planesIDX;
		$this->planes_fetched = true;
		
		return $this->planesIDX;
		
	}
	
	/**
	 * Obtiene los tipos de plan
	 * @return array
	 */
	public function getTiposPlan() {
		
		if ( $this->tiposPlan_fetched ){
			return $this->tiposPlanIDX;
		}
		
		$tiposPlanCOL = TblTipoPlan::findAll($this->db, 'vNombre');
		$tiposPlanIDX = array();
		
		// Se indexarán los tipos de Plan por su clave
		foreach ($tiposPlanCOL as $tipoPlanDO){
		    
		    $tiposPlanIDX[$tipoPlanDO->getIdTipoPlan()] = $tipoPlanDO->getVNombre();
		    
		}
		
		$this->tiposPlanIDX = $tiposPlanIDX;
		$this->tiposPlan_fetched = true;
		
		return $this->tiposPlanIDX;
		
	}
	
	/**
	 * Obtiene los estados de plan
	 * @return array
	 */
	public function getEstadosPlan() {
		
		if ( $this->estadosPlan_fetched ){
			return $this->tiposPlanIDX;
		}
		
		$estadosPlanCOL = TblEstadoPlan::findAll($this->db, 'vNombre');
		$estadosPlanIDX = array();
		
		// Se indexarán los estados de Plan por su clave
		foreach ($estadosPlanCOL as $tipoPlanDO){
		    
		    $estadosPlanIDX[$tipoPlanDO->getIdEstadoPlan()] = $tipoPlanDO->getVNombre();
		    
		}
		
		$this->estadosPlanIDX = $estadosPlanIDX;
		$this->estadosPlan_fetched = true;
		
		return $this->estadosPlanIDX;
		
	}
	
	/**
	 * Obtiene los requisitos
	 * @return array
	 */
	public function getRequisitos() {
		
		if ( $this->requisitos_fetched ){
			return $this->requisitosIDX;
		}
		
		$requisitosCOL = TblRequisito::findAll($this->db, 'vNombre');
		$requisitosIDX = array();
		
		// Se indexarán los requisitos por su clave
		foreach ($requisitosCOL as $requisitoDO){
		    
		    $requisitosIDX[$requisitoDO->getIdRequisito()] = $requisitoDO->getVNombre();
		    
		}
		
		$this->requisitosIDX = $requisitosIDX;
		$this->requisitos_fetched = true;
		
		return $this->requisitosIDX;
		
	}
	
	/**
	 * Obtiene las empresas
	 * @return array
	 */
	public function getEmpresas() {
		
		if ( $this->empresas_fetched ){
			return $this->empresasIDX;
		}
		
		$empresasCOL = TblEmpresa::findAll($this->db, 'vNombre');
		$empresasIDX = array();
		
		// Se indexarán los empresas por su clave
		foreach ($empresasCOL as $empresaDO){
		    
		    $empresasIDX[$empresaDO->getIdEmpresa()] = $empresaDO->getVNombre();
		    
		}
		
		$this->empresasIDX = $empresasIDX;
		$this->empresas_fetched = true;
		
		return $this->empresasIDX;
		
	}
	
	/**
	 * Obtiene las academias
	 * @return array
	 */
	public function getAcademias() {
		
		if ( $this->academias_fetched ){
			return $this->academiasIDX;
		}
        
		$academiasCOL = TblEmpresa::findAll($this->db, 'vNombre');
		$sql = 'SELECT * FROM tblEmpresa e WHERE EXISTS ( SELECT NULL FROM trelRolUsuario ru WHERE e.fkUsuario = ru.fkUsuario AND ru.fkRol = ' . PplAclManager::ROL_ACADEMIA . ')';
		$this->db->executeQuery($sql);
        
        
		$academiasIDX = array();
		
		// Se indexarán los empresas por su clave
        while ( $row = $this->db->fetchRow() ){
        	$academiasIDX[$row['idEmpresa']] = $row['vNombre'];	
        }
		
		$this->academiasIDX = $academiasIDX;
		$this->academias_fetched = true;
		
		return $this->academiasIDX;
		
	}
	
	/**
	 * Obtiene las consultoras
	 * @return array
	 */
	public function getConsultoras() {
		
		if ( $this->consultoras_fetched ){
			return $this->consultorasIDX;
		}
        
		//$consultorasCOL = TblEmpresa::findAll($this->db, 'vNombre');
		$sql = 'SELECT * FROM tblEmpresa e WHERE EXISTS ( SELECT NULL FROM trelRolUsuario ru WHERE e.fkUsuario = ru.fkUsuario AND ru.fkRol IN (' . PplAclManager::ROL_CONSULTORA . ', ' . PplAclManager::ROL_PROPIETARIO . ') )';
		$this->db->executeQuery($sql);
        
        
		$consultorasIDX = array();
		
		// Se indexarán los empresas por su clave
        while ( $row = $this->db->fetchRow() ){
        	$consultorasIDX[$row['idEmpresa']] = $row['vNombre'];	
        }
		
		$this->consultorasIDX = $consultorasIDX;
		$this->consultoras_fetched = true;
		
		return $this->consultorasIDX;
		
	}
	
	/**
	 * Obtiene los centros
	 * @return array
	 */
	public function getCentros() {
		
		if ( $this->centros_fetched ){
			return $this->centrosIDX;
		}
		
		$centrosCOL = TblCentro::findAll($this->db, 'vNombre');
		$centrosIDX = array();
		
		// Se indexarán los centros por su clave
		foreach ($centrosCOL as $centroDO){
		    
		    $centrosIDX[$centroDO->getIdCentro()] = $centroDO->getVNombre();
		    
		}
		
		$this->centrosIDX = $centrosIDX;
		$this->centros_fetched = true;
		
		return $this->centrosIDX;
		
	}
	
	/**
	 * Obtiene los colectivos
	 * @return array
	 */
	public function getColectivos() {
		
		if ( $this->colectivos_fetched ){
			return $this->colectivoIDX;
		}
		
		$colectivoCOL = TblColectivo::findAll($this->db, 'vNombre');
		$colectivoIDX = array();
		
		// Se indexarán los colectivo por su clave
		foreach ($colectivoCOL as $colectivoDO){
		    
		    $colectivoIDX[$colectivoDO->getIdColectivo()] = $colectivoDO->getVNombre();
		    
		}
		
		$this->colectivoIDX = $colectivoIDX;
		$this->colectivo_fetched = true;
		
		return $this->colectivoIDX;
		
	}
	
	/**
	 * Obtiene la modalidad
	 * @return array
	 */
	public function getModalidades() {
		
		if ( $this->modalidades_fetched ){
			return $this->modalidadIDX;
		}
		
		$modalidadCOL = TblModalidad::findAll($this->db, 'vNombre');
		$modalidadIDX = array();
		
		// Se indexarán los modalidad por su clave
		foreach ($modalidadCOL as $modalidadDO){
		    
		    $modalidadIDX[$modalidadDO->getIdModalidad()] = $modalidadDO->getVNombre();
		    
		}
		
		$this->modalidadIDX = $modalidadIDX;
		$this->modalidad_fetched = true;
		
		return $this->modalidadIDX;
		
	}
	
	/**
	 * Obtiene los sectores
	 * @return array
	 */
	public function getSectores() {
		
		if ( $this->sectores_fetched ){
			return $this->sectorIDX;
		}
		
		$sectorCOL = TblSector::findAll($this->db, 'vNombre');
		$sectorIDX = array();
		
		// Se indexarán los sector por su clave
		foreach ($sectorCOL as $sectorDO){
		    
		    $sectorIDX[$sectorDO->getIdSector()] = $sectorDO->getVNombre();
		    
		}
		
		$this->sectorIDX = $sectorIDX;
		$this->sector_fetched = true;
		
		return $this->sectorIDX;
		
	}
	
	/**
	 * Obtiene las categorías
	 * @return array
	 */
	public function getCategorias() {
		
		if ( $this->categorias_fetched ){
			return $this->categoriaIDX;
		}
		
		$categoriaCOL = TblCategoria::findAll($this->db, 'vNombre');
		$categoriaIDX = array();
		
		// Se indexarán los categoria por su clave
		foreach ($categoriaCOL as $categoriaDO){
		    
		    $categoriaIDX[$categoriaDO->getIdcategoria()] = $categoriaDO->getVNombre();
		    
		}
		
		$this->categoriaIDX = $categoriaIDX;
		$this->categoria_fetched = true;
		
		return $this->categoriaIDX;
		
	}
	
	/**
	 * Obtiene las aulas
	 * @return array
	 */
	public function getAulas() {
		
		if ( $this->aulas_fetched ){
			return $this->aulaIDX;
		}
		
		$aulaCOL = TblAula::findAll($this->db, 'vNombre');
		$aulaIDX = array();
		
		// Se indexarán los aula por su clave
		foreach ($aulaCOL as $aulaDO){
		    
		    $aulaIDX[$aulaDO->getIdAula()] = $aulaDO->getVNombre();
		    
		}
		
		$this->aulaIDX = $aulaIDX;
		$this->aula_fetched = true;
		
		return $this->aulaIDX;
		
	}
	
	/**
	 * Devuelve todos los paises indexados por su iso
	 * @return array
	 */
	public function getPaises(){
	    
	    $paisesCOL = TblPais::findAll($this->db, 'vNombre_es');
	    $paisesIDX = NingenDatabase::indexFor('vIso', $paisesCOL);
	    
	    return $paisesIDX;
	    
	}
	
	/**
	 * Devuelve un array con todas las provincias indexadas por su clave
	 */
	public function getProvincias(){
	    
	    $provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
	    $provinciasIDX = NingenDatabase::indexFor('idProvincia', $provinciasCOL);
	    
	    return $provinciasIDX;
	    
	}
	
	/**
	 * Obtiene los profesores
	 * @return array
	 */
	public function getProfesores() {
		
		if ( $this->profesores_fetched ){
			return $this->profesoresIDX;
		}
        
		$sql = 'SELECT * FROM tblPersona e WHERE EXISTS ( SELECT NULL FROM trelRolUsuario ru WHERE e.fkUsuario = ru.fkUsuario AND ru.fkRol = ' . PplAclManager::ROL_PROFESOR . ') ORDER BY vNombre';
		$this->db->executeQuery($sql);
        
        
		$profesoresIDX = array();
		
		// Se indexarán los empresas por su clave
        while ( $row = $this->db->fetchRow() ){
        	$profesoresIDX[$row['idPersona']] = $row['vNombre'] . ' ' . $row['vPrimerApellido'] . ' ' . $row['vSegundoApellido'];
        }
		
		$this->profesoresIDX = $profesoresIDX;
		$this->profesores_fetched = true;
		
		return $this->profesoresIDX;
		
	}
	
	/**
	 * Devuelve todas las categorías de todos los profesores.
	 * Array indexado por la clave de profesor
	 * @return array
	 */
	public function getProfesoresCategorias(){
	    
	    $rolProfesor = PplAclManager::ROL_PROFESOR;
	    
        $sql = "SELECT p.idPersona,
                       pc.fkCategoria
                FROM   tblPersona p
                       INNER JOIN trelPersonaCategoria pc
                         ON p.idPersona = pc.fkPersona
                WHERE  EXISTS(SELECT NULL
                              FROM   trelRolUsuario ru
                              WHERE  p.fkUsuario = ru.fkUsuario
                                     AND ru.fkRol = $rolProfesor)
                ORDER  BY p.idPersona;";
	   
        $this->db->executeQuery($sql);
        
        $resultARR = array();
        while ($row = $this->db->fetchRow()){
            $resultARR[$row['idPersona']][] = $row['fkCategoria'];
        }
        
        return $resultARR;
	   
	}
	
	/**
	 * Devuelve un array con todas las personas indexadas por su clave
	 */
	public function getPersonas(){
	    
	    if ( $this->personas_fetched ){
			return $this->personasIDX;
		}
		
		$personasCOL = TblPersona::findAll($this->db, 'vNombre');
	    $personasIDX = NingenDatabase::indexFor('idPersona', $personasCOL);
		
		$this->personasIDX = $personasIDX;
		$this->personas_fetched = true;
		
		return $this->personasIDX;
	    
	}
	
}

?>