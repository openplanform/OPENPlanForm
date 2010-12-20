<?php

require_once 'OwlController.inc';
require_once 'dbase/OwlDatabase.inc';

require_once MODELDIR . 'TblEmpresa.inc';
require_once MODELDIR . 'TblEstadoLaboral.inc';
require_once MODELDIR . 'TblEstadoPlan.inc';
require_once MODELDIR . 'TblNivelEstudios.inc';
require_once MODELDIR . 'TblPais.inc';
require_once MODELDIR . 'TblPersona.inc';
require_once MODELDIR . 'TblProvincia.inc';
require_once MODELDIR . 'TblTipoConvocatoria.inc';
require_once MODELDIR . 'TblTipoIdentificacion.inc';
require_once MODELDIR . 'TblTipoPlan.inc';
require_once MODELDIR . 'TblDocumento.inc';


class PplCacheBO {
	
	/**
	 * Valor del estado laboral "Ocupado" en la bbdd
	 * @var intenger
	 */
	const CLAVE_OCUPADO = 1;
	
	/**
	 * Valor del estado laboral "Desocupado" en la bbdd
	 * @var intenger
	 */
	const CLAVE_DESOCUPADO = 2;
	
	/**
     * Referencia a la base de datos
     * @var OwlConnection
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
     * carnets indexados por su clave
     * @var array
     */
    private $carnetsIDX;
    
    /**
     * Flag que indica que los carnets han sido cargados
     * @var boolean
     */
    private $carnets_fetched = false;
    
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
     * estados civiles indexados por su clave
     * @var array
     */
    private $estadosCivilesIDX;
    
    /**
     * Flag que indica que los estados civiles han sido cargados
     * @var boolean
     */
    private $estadosCiviles_fetched = false;
    
    /**
     * Estados laborales, indexados por su clave
     * @var array
     */
    private $estadosLaboralesIDX = null;
    
    /**
     * Niveles de estudios, indexados por su clave
     * @var array
     */
    private $nivelesEstudioIDX = null;
    
    /**
     * Tipos de identificación, indexados por su clave
     * @var array
     */
    private $tiposIdentificacionIDX = null;
    
    /**
     * Cobros de parto indexados por su clave
     * @var array
     */
    private $cobrosParoIDX = null;
    
    /**
     * Categorías de empleo indexadas por su clave
     * @var array
     */
    private $categoriasEmpleoIDX = null;
    
    
    /**
     * Constructora, propaga la referencia a la base de datos 
     * @param OwlConnection $db
     */
    public function __construct( OwlConnection $db ){
    	
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
	 * Devuelve todos los nombres de modalidades indexadas por su clave
	 * @return array
	 */
	public function getModalidades() {
		
		if ( $this->modalidades_fetched ){
			return $this->modalidadesIDX;
		}
		
		$modalidadCOL = TblModalidad::findAll($this->db, 'vNombre');
		$modalidadIDX = array();
		
		// Se indexarán los modalidad por su clave
		foreach ($modalidadCOL as $modalidadDO){
		    
		    $modalidadIDX[$modalidadDO->getIdModalidad()] = $modalidadDO->getVNombre();
		    
		}
		
		$this->modalidadesIDX = $modalidadIDX;
		$this->modalidades_fetched = true;
		
		return $this->modalidadesIDX;
		
	}
	
	
	/**
	 * Devuelve todos los nombres de sectores indexados por su clave
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
	    $paisesIDX = OwlDatabase::indexFor('vIso', $paisesCOL);
	    
	    return $paisesIDX;
	    
	}
	
	
	/**
	 * Devuelve un array con todas las provincias indexadas por su clave
	 */
	public function getProvincias(){
	    
	    $provinciasCOL = TblProvincia::findAll($this->db, 'vNombre_es');
	    $provinciasIDX = OwlDatabase::indexFor('idProvincia', $provinciasCOL);
	    
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
	    $personasIDX = OwlDatabase::indexFor('idPersona', $personasCOL);
		
		$this->personasIDX = $personasIDX;
		$this->personas_fetched = true;
		
		return $this->personasIDX;
	    
	}
	
	/**
	 * Devuelve el directorio de subida de archivos,
	 * siempre obtenerlo desde aqui, nunca hardcodearlo
	 * @return string
	 */
	static public function getUploadDir(){
	    
	    return PUBDIR . 'docs/';
	    
	}
	
    /**
     * Devuelve la ruta completa para el frontend de un documento
     * @param $docDO
     * @return string
     */
	static public function getDocLink(TblDocumento $docDO){

	    return '/docs/doc_' . $docDO->getIdDocumento();
	    
	}
	
	
	/**
	 * Devuelve todos los documentos dinámicos
	 * @return array
	 */
	public function getDocumentosDinamicos(){
		
		$sql = "SELECT * FROM tblDocumento WHERE bDinamico = 1";
		$this->db->executeQuery($sql);
		
		$returnARR = array();
		while ($row = $this->db->fetchRow()){
			
			$returnARR[] = $row;
			
		}
		
		return $returnARR;
		
	}
	
	
	/**
	 * Obtiene los carnets
	 * @return array
	 */
	public function getCarnets() {
		
		if ( $this->carnets_fetched ){
			return $this->carnetsIDX;
		}
		
		$carnetCOL = TblCarnetConducir::findAll($this->db, 'vNombre');
		$carnetIDX = array();
		
		// Se indexarán los carnet por su clave
		foreach ($carnetCOL as $carnetDO){
		    
		    $carnetIDX[$carnetDO->getIdCarnetConducir()] = $carnetDO->getVNombre() . '(' . $carnetDO->getVDescripcion() . ')';
		    
		}
		
		$this->carnetIDX = $carnetIDX;
		$this->carnet_fetched = true;
		
		return $this->carnetIDX;
		
	}
	

	/**
	 * Devuelve la coleccion de documentos dinámicos seleccionados para una convocatoria
	 * 
	 * @param integer $idConvocatoria
	 * @return array
	 */
	public function getDocumentacionConvocatoria($idConvocatoria){
		
		$sql = "SELECT *
				FROM   tblDocumento d
				WHERE  EXISTS(SELECT NULL
				              FROM   trelDocumentoConvocatoria dc
				              WHERE  d.idDocumento = dc.fkDocumento
				                     AND dc.fkConvocatoria = $idConvocatoria)
				ORDER  BY d.last_modified ASC";
		
		return OwlGenericDO::createCollection( $this->db, $sql, 'TblDocumento' );
		
	}
	
	
	/**
	 * Devuelve la colección de documentos dinámicos seleccionados para un curso
	 * a partir de la clave de plan.
	 * 
	 * @param integer $idCurso
	 */
	public function getDocumentacionCurso($idPlan){
		
		$sql = "SELECT *
				FROM   tblDocumento d
				WHERE  EXISTS(SELECT NULL
				              FROM   trelDocumentoConvocatoria dc
				              WHERE  dc.fkDocumento = d.idDocumento
				                     AND fkConvocatoria = (SELECT fkConvocatoria
				                                           FROM   tblPlan
				                                           WHERE  idPlan = $idPlan));  ";	
		
		return OwlGenericDO::createCollection( $this->db, $sql, 'TblDocumento' );
		
	}
	
	
	/**
	 * Obtiene los estados civiles
	 * @return array
	 */
	public function getEstadosCiviles() {
		
		if ( $this->estadosCiviles_fetched ){
			return $this->estadosCivilesIDX;
		}
		
		$estadosCivilesCOL = TblEstadoCivil::findAll($this->db, 'vNombre');
		$estadosCivilesIDX = OwlDatabase::indexFor('idEstadoCivil', $estadosCivilesCOL);
		
		
		$this->estadosCivilesIDX = $estadosCivilesIDX;
		$this->estadosCiviles_fetched = true;
		
		return $this->estadosCivilesIDX;
		
	}

	
	/**
	 * Obtiene los estados laborales
	 * @return array
	 */
	public function getEstadosLaborales() {
		
		if (is_null($this->estadosLaboralesIDX) ){

			$estadosLaboralesCOL = TblEstadoLaboral::findAll($this->db, 'vNombre');
			$estadosLaboralesIDX = OwlDatabase::indexFor('idEstadoLaboral', $estadosLaboralesCOL);
			
			$this->estadosLaboralesIDX = $estadosLaboralesIDX;
			$this->estadosLaborales_fetched = true;
			
		}
		
		return $this->estadosLaboralesIDX;
		
	}
	
	
	/**
	 * Devuelve todos los niveles de estudios indexados por su clave
	 * @return array
	 */
	public function getNivelesEstudio(){
		
		if (is_null($this->nivelesEstudioIDX)){

			$nivelesEstudioCOL = TblNivelEstudios::findAll($this->db, 'vNombre ASC');
			$nivelesEstudioIDX = OwlDatabase::indexFor('idNivelEstudios', $nivelesEstudioCOL);
			
			$this->nivelesEstudioIDX = $nivelesEstudioIDX;
			
		}
		
		return $this->nivelesEstudioIDX;
		
	}
	
	
	/**
	 * Devuelve todos los tipos de identificacion indexados por su clave
	 * @return array
	 */
	public function getTiposIdentificacion(){
		
		if (is_null($this->tiposIdentificacionIDX)){
			
			$tiposIdentificacionCOL = TblTipoIdentificacion::findAll($this->db, 'vNombre ASC');
			$tiposIdentificacionIDX = OwlDatabase::indexFor('idTipoIdentificacion', $tiposIdentificacionCOL);
			
			$this->tiposIdentificacionIDX = $tiposIdentificacionIDX;
			
		}
		
		return $this->tiposIdentificacionIDX;
		
	}
	
	
	/**
	 * Devuelve una colección con el/los profesores asignados a un curso en particular
	 * @param integer $idCurso
	 */
	public function getProfesoresCurso($idCurso){
		
		$sql = "SELECT *
				FROM   tblPersona per
				WHERE  EXISTS (SELECT NULL
				               FROM   trelProfesor pro
				               WHERE  per.idPersona = pro.fkPersona
				                      AND pro.fkCurso = $idCurso)
				ORDER  BY per.vNombre ASC;";
		
		
		return OwlGenericDO::createCollection( $this->db, $sql, 'TblPersona' );
		
	}
	
	/**
	 * Devuelve los cobros de paro indexados por su clave
	 * @return array
	 */
	public function getCobrosParo(){
		
		if ( is_null($this->cobrosParoIDX) ){
			
			$cobrosParoCOL = TblCobroParo::findAll($this->db, 'idCobroParo');
			$cobrosParoIDX = OwlDatabase::indexFor('idCobroParo', $cobrosParoCOL);
			$this->cobrosParoIDX = $cobrosParoIDX;
			
		}
		
		return $this->cobrosParoIDX;
		
	}
	
	/**
	 * Devuelve las categorías de empleo indexadas por su clave
	 * @return array
	 */
	public function getCategoriasEmpleo(){
		
		if ( is_null($this->categoriasEmpleoIDX) ){
			
			$categoriasEmpleoCOL = TblCategoriaEmpleo::findAll($this->db, 'idCategoriaEmpleo');
			$categoriasEmpleoIDX = OwlDatabase::indexFor('idCategoriaEmpleo', $categoriasEmpleoCOL);
			$this->categoriasEmpleoIDX = $categoriasEmpleoIDX;
			
		}
		
		return $this->categoriasEmpleoIDX;
		
	}
	
}

?>