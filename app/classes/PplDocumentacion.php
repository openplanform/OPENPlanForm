<?php

require_once 'OwlPdf.inc';


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
	 * Array donde se mapean los metodos indexados por
	 * el identificador de documento
	 * @var array
	 */
	protected $validDocs = array(
		'S-30', // docControlAsistencia
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
		if (!in_array($identificadorDocumento, $this->methodMap)){
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
		$sql = 'SELECT * FROM tblDocumento WHERE vIdentificador = ' . $this->identificadorDocumento;
		$this->db->executeQuery($sql);

		// Si hay dos documentos con el mismo identificador, solo se tomará el primero (no se muestra error)
		if (!$doc = $this->db->executeQuery($sql)){
			throw new OwlException('El documento dinámico ' . $this->identificadorDocumento . 'no existe', 500);
		}
		
		$docId = $doc['idDocumento'];
		$docName = $doc['vNombre'];
		
		// Se carga el documento
		$this->pdf = new OwlPdf(PUBDIR . 'docs/doc_' . $docId);
		
	}

	
	/**
	 * Establece la estructura para el documento 
	 * con identificador S-30
	 */
	public function docControlAsistencia(){
		
		// Paginas
	    $pdf->addFieldValue('pag1', 1, 'text');
	    $pdf->addFieldValue('de1', 1, 'text');

	    // Datos generales
	    $pdf->addFieldValue('numExpediente', '2010R64', 'text');
	    $pdf->addFieldValue('entidadSolicitante', '+Humana Consultora de recursos humanos', 'text');
	    $pdf->addFieldValue('cif', '123456789', 'text');
	    $pdf->addFieldValue('accionFormativa', 'Una denominación formativa, no se que es.', 'text');
	    $pdf->addFieldValue('numAf', '987654', 'text');
	    $pdf->addFieldValue('numGrupo', '123', 'text');
	    $pdf->addFieldValue('fechaInicio', '12/04/1983', 'text');
	    $pdf->addFieldValue('fechaFin', '13/04/1983', 'text');
	    $pdf->addFieldValue('responsableFormacion', 'Nicolás Daniel Palumbo', 'text');
	    $pdf->addFieldValue('numGrupo', '32', 'text');
	    $pdf->addFieldValue('numSesion', '52', 'text');
	    $pdf->addFieldValue('fechaSesion', '18/05/2001', 'text');
	    $pdf->addFieldValue('diasManyana', '5', 'text');
	    $pdf->addFieldValue('desdeManyana', '8:30', 'text');
	    $pdf->addFieldValue('hastaManyana', '12:30', 'text');
	    $pdf->addFieldValue('diasTarde', '4', 'text');
	    $pdf->addFieldValue('desdeTarde', '14:00', 'text');
	    $pdf->addFieldValue('hastaTarde', '17:00', 'text');
	    $pdf->addFieldValue('otroResponsable', 'Nuuuuuu', 'text');
	    $pdf->addFieldValue('observaciones1', 'Texto de observaciones, este es un texto de prueba', 'text');
	    
	    // Checks
	    $pdf->addFieldValue('cargo_formador', 1, 'checkbox');
	    $pdf->addFieldValue('cargo_responsable', 1, 'checkbox');
	    $pdf->addFieldValue('cargo_otro', 1, 'checkbox');
	    
	    // Filas de tablas
	    for ($x=1; $x<16; $x++){
	        
	        $pdf->addFieldValue('apellido' . $x, 'Apellido('.$x.')', 'text');
	        $pdf->addFieldValue('segundoApellido' . $x, 'Seg. Apellido('.$x.')', 'text');
	        $pdf->addFieldValue('nombre' . $x, 'Nombre('.$x.')', 'text');
	        $pdf->addFieldValue('nif' . $x, '123456789', 'text');
	        
	    }
	    
	    
	    $pdf->fillPdfForm();

	    $num = $pdf->writeFile(PUBDIR . 'img/tmp/out2.pdf');
	    echo "Se han escrito: <strong>$num</strong> bytes";
	    	    
		
	}
	
	
	
}

?>