<?php

require_once 'OwlPdf.inc';
require_once 'helper/OwlFile.inc';
require_once 'helper/OwlDate.inc';


/**
 * Clase que contiene la definición de estructura para 
 * informes pdf generados. 
 * @author nico
 *
 */
class PplDocumentacion{
	
	/**
	 * Objeto de tratamiento de archivos pdf
	 * @var OwlPdf
	 */
	protected $pdf;
	
	/**
	 * Referencia a la base de datos
	 * @var OwlConnection
	 */
	protected $db;
	
	/**
	 * Identificador del documento
	 * @var string
	 */
	protected $identificadorDocumento;

	/**
	 * Gestor de archivos
	 * @var OwlFile
	 */
	protected $fileMan;
	
	/**
	 * Identificador interno del documento
	 * @var integer
	 */
	protected $docId;
	
	/**
	 * Array donde se mapean los metodos indexados por
	 * el identificador de documento
	 * @var array
	 */
	protected $validDocs = array(
		'S-30', // docControlAsistencia
		'S-20', // docListadoInicialAsistentes
		'S-10', // docInicioAccionFormativa
	);
	
	
	/**
	 * Establece el documento a tratar y la conexión a la base de datos.
	 * Si los datos son correctos llama al método para cargar el archivos a tratar.
	 * 
	 * @param OwlConnection $db
	 * @param string $identificadorDocumento
	 */
	public function __construct(OwlConnection $db, $identificadorDocumento){
		
		// Datos y objetos necesarios
		$this->db = $db;
		$this->identificadorDocumento = $identificadorDocumento;
		$this->fileMan = new OwlFile();
		
		// Verificamos que exista un método para el documento a tratar
		if (!in_array($identificadorDocumento, $this->validDocs)){
			throw new OwlException('No se ha definido un método para tratar el documento: ' . $identificadorDocumento, 500);
		}
		
		// Se carga el documento
		$this->loadBaseDocument();
		
	}
	
	
	/**
	 * Carga el documento a tratar
	 * @throws OwlException
	 */
	protected function loadBaseDocument(){
		
		// Se verifica si el documento a tratar existe en la base de datos
		$sql = "SELECT * FROM tblDocumento WHERE vIdentificador = '" . $this->identificadorDocumento . "'";
		$this->db->executeQuery($sql);
		
		// Si hay dos documentos con el mismo identificador, solo se tomará el primero (no se muestra error)
		if (!$doc = $this->db->fetchRow()){
			throw new OwlException('El documento dinámico <strong>' . $this->identificadorDocumento . '</strong> no existe', 500);
		}
		
		$this->docId = $doc['idDocumento'];
		
	}

	
	/**
	 * Establece la estructura para el documento con identificador S-30
	 * @param tblCurso $cursoDO
	 * @param tblPlan $planDO
	 * @param array $profesorDO
	 * @param array $alumnosCOL
	 * @param array $horariosCOL
	 * @param boolean $dosPaginas
	 */
	public function docControlAsistencia(TblCurso $cursoDO, TblPlan $planDO, TblPersona $profesorDO, $alumnosCOL, $horariosCOL, $dosPaginas = false){
		
		// Datos iniciales
		$propietarioDO = $planDO->getTblEmpresaPropietaria();
		$fileList = array();
		
		// Dos páginas
		if ($dosPaginas){
			
			/**
			 * @TODO cargar documento de dos páginas
			 */
			
		}
		
		// Se generará un S-30 por cada sesión
		foreach ($horariosCOL as $horarioDO){
			
			// Se carga el documento original
			$this->pdf = new OwlPdf(PUBDIR . 'docs/doc_' . $this->docId);
	
			// Paginas
		    $this->pdf->addFieldValue('pag1', 1, 'text');
		    $this->pdf->addFieldValue('de1', 1, 'text');
	
		    /**
		     * @TODO Los números de expediente estan hardcoded!
		     */
		    
		    // Datos generales
		    $this->pdf->addFieldValue('numExpediente', '2010R64', 'text');
		    $this->pdf->addFieldValue('entidadSolicitante', $propietarioDO->getVNombre(), 'text');
		    $this->pdf->addFieldValue('cif', $propietarioDO->getVCif(), 'text');
		    $this->pdf->addFieldValue('accionFormativa', $cursoDO->getVNombre(), 'text');
		    $this->pdf->addFieldValue('numAf', $cursoDO->getIAccion(), 'text');
		    $this->pdf->addFieldValue('numGrupo', $cursoDO->getIGrupo(), 'text');
		    $this->pdf->addFieldValue('fechaInicio', OwlDate::getDiaMesAno($cursoDO->getDInicio()), 'text');
		    $this->pdf->addFieldValue('fechaFin', OwlDate::getDiaMesAno($cursoDO->getDFin()), 'text');
		    $this->pdf->addFieldValue('responsableFormacion', $profesorDO->getVNombre() . ' ' . $profesorDO->getVPrimerApellido() . ' ' . $profesorDO->getVSegundoApellido(), 'text');
		    $this->pdf->addFieldValue('numGrupo', $cursoDO->getIGrupo(), 'text');
		    $this->pdf->addFieldValue('numSesion', $horarioDO->getISesion(), 'text');
		    $this->pdf->addFieldValue('fechaSesion', OwlDate::getDiaMesAno($horarioDO->getDDia()), 'text');
		    $this->pdf->addFieldValue('diasManyana', '', 'text');
		    $this->pdf->addFieldValue('desdeManyana', date('H:i', strtotime($horarioDO->getIDesde())), 'text');
		    $this->pdf->addFieldValue('hastaManyana', date('H:i', strtotime($horarioDO->getIHasta())), 'text');
		    $this->pdf->addFieldValue('diasTarde', '', 'text');
		    $this->pdf->addFieldValue('desdeTarde', '', 'text');
		    $this->pdf->addFieldValue('hastaTarde', '', 'text');
		    $this->pdf->addFieldValue('otroResponsable', '', 'text');
		    $this->pdf->addFieldValue('observaciones1', $cursoDO->getVObservaciones(), 'text');
		    
		    // Checks ( El cargo firmante siempre será el formador )
		    $this->pdf->addFieldValue('cargo_formador', 1, 'checkbox');
		    $this->pdf->addFieldValue('cargo_responsable', 0, 'checkbox');
		    $this->pdf->addFieldValue('cargo_otro', 0, 'checkbox');
	
		    // Alumnos
		    $x=1;
		    foreach ($alumnosCOL as $alumnoDO){
		    	
				$this->pdf->addFieldValue('apellido' . $x, $alumnoDO->getVPrimerApellido(), 'text');
		        $this->pdf->addFieldValue('segundoApellido' . $x, $alumnoDO->getVSegundoApellido(), 'text');
		        $this->pdf->addFieldValue('nombre' . $x, $alumnoDO->getVNombre(), 'text');
		        $this->pdf->addFieldValue('nif' . $x, $alumnoDO->getVNumeroIdentificacion(), 'text');
	
		        $x++;
		        
		        // Temp: el documento solo admite 15 alumnos
	        	if ($x == 16){
		    		break;
		    	}	        
		    	
		    }
		    
		    // Se escribe el archivo
		    $this->pdf->fillPdfForm();
		    
		    // Metadata del archivo generado
		    $fileName = 'S30_c' . $cursoDO->getIdCurso() . 's' . $horarioDO->getISesion() . '.pdf';
		    $fileList[] = array(
		    	'label' => 'S-30 - Sesión ' . $horarioDO->getISesion() . ' - ' . OwlDate::getDiaMesAno($horarioDO->getDDia()),
		    	'file' => $fileName
		    );
	
		    // Se compone el nombre del archivo
		    $num = $this->pdf->writeFile(PUBDIR . 'tmp/' . $fileName);
		    
		}		    
		    
		// Se devuelve el array de archivos para ser pasado a la vista
	    return $fileList;
	    	    
		
	}
	
	
	/**
	 * Establece la estructura para el documento con identificador S-30 (A dos páginas, para más de 15 alumnos)
	 * @param tblCurso $cursoDO
	 * @param tblPlan $planDO
	 * @param array $profesorDO
	 * @param array $alumnosCOL
	 * @param array $horariosCOL
	 * @param boolean $dosPaginas
	 */
	public function docControlAsistencia2p(TblCurso $cursoDO, TblPlan $planDO, TblPersona $profesorDO, $alumnosCOL, $horariosCOL){
		
		return $this->docControlAsistencia($cursoDO, $planDO, $profesorDO, $alumnosCOL, $horariosCOL, true);
		
	}


	/**
	 * Establece la estructura para el documento con identificador S-20 
	 * @param TblCurso $cursoDO
	 * @param unknown_type $alumnosCOL
	 * @param TblPersona $tutorDO
	 * @param TblPlan $planDO
	 * @param unknown_type $modalidadesIDX
	 */
	public function docListadoInicialAsistentes(TblCurso $cursoDO, $alumnosCOL, TblPersona $tutorDO, TblPlan $planDO, $modalidadesIDX){
		
		// Datos iniciales
		$propietarioDO = $planDO->getTblEmpresaPropietaria();
		$fileList = array();

		// Modalidad de la tutoría a distancia
		$modalidadTutoria = '';
		$fkModalidadTutoria = $cursoDO->getFkModalidadTutoria();
		if (array_key_exists($fkModalidadTutoria, $modalidadesIDX)){
			$modalidadTutoria = $modalidadesIDX[$fkModalidadTutoria];
		}
		
		// Se carga el documento original
		$this->pdf = new OwlPdf(PUBDIR . 'docs/doc_' . $this->docId);
	
		// Paginas
	    $this->pdf->addFieldValue('pag', 1, 'text');
	    $this->pdf->addFieldValue('de', 1, 'text');

		/**
	     * @TODO Los números de expediente estan hardcoded!
	     */	    
		
	    // Datos generales

		$this->pdf->addFieldValue('numExpediente', '2010R64', 'text');
		$this->pdf->addFieldValue('entidadSolicitante', $propietarioDO->getVNombre(), 'text');
		$this->pdf->addFieldValue('cifEntidad', $propietarioDO->getVCif(), 'text');
		$this->pdf->addFieldValue('accionFormativa', $cursoDO->getVNombre(), 'text');
		$this->pdf->addFieldValue('numAccionFormativa', $cursoDO->getIAccion(), 'text');
		$this->pdf->addFieldValue('numGrupo', $cursoDO->getIGrupo(), 'text');
		$this->pdf->addFieldValue('fechaInicio', OwlDate::getDiaMesAno($cursoDO->getDInicio()), 'text');
		$this->pdf->addFieldValue('fechaFin', OwlDate::getDiaMesAno($cursoDO->getDFin()), 'text');
		$this->pdf->addFieldValue('profesorDistancia', $tutorDO->getVNombre() . ' ' . $tutorDO->getVPrimerApellido() . ' ' . $tutorDO->getVSegundoApellido(), 'text');
		$this->pdf->addFieldValue('nifProfesoresDistancia', $tutorDO->getVNumeroIdentificacion(), 'text');
		$this->pdf->addFieldValue('numHorasDisponibles', $cursoDO->getIHorasTutoria(), 'text');
		$this->pdf->addFieldValue('tiposTutorias', $modalidadTutoria, 'text');

		// Alumnos
		$x=1;
		foreach ($alumnosCOL as $alumnoDO){
			
			if ($x == 32){
				break;
			}
			
			$this->pdf->addFieldValue('nombre' . $x, $alumnoDO->getVNombre(), 'text');
			$this->pdf->addFieldValue('apellido' . $x, $alumnoDO->getVPrimerApellido(), 'text');
			$this->pdf->addFieldValue('segApellido' . $x, $alumnoDO->getVSegundoApellido(), 'text');
			$this->pdf->addFieldValue('nif' . $x, $alumnoDO->getVNumeroIdentificacion(), 'text');
			$this->pdf->addFieldValue('niss' . $x, $alumnoDO->getVNumeroSS(), 'text');
			$this->pdf->addFieldValue('sitLaboral' . $x, $alumnoDO->getVEstadoLaboral(), 'text');
			
			$x++;
			
		}

		// Nombre de archivo
	    $fileName['file'] = 'S20_c' . $cursoDO->getIdCurso() . '.pdf';
	    $fileName['label'] = 'S-20 - Listado inicial de asistentes';
			    
	    // Se escribe el archivo
	    $this->pdf->fillPdfForm();
	    $num = $this->pdf->writeFile(PUBDIR . 'tmp/' . $fileName['file']);	    
	    
	    return $fileName;
	    
	}
	
	
	
	public function docInicioAccionFormativa(TblPlan $planDO){
		
		// Se carga el documento original
		$this->pdf = new OwlPdf(PUBDIR . 'docs/doc_' . $this->docId);
		
		
		
	}
	
	
}

?>