<?php
/**
 * Este archivo ha sido generado con Owl DoGen v.0.6
 * el 21 de January de 2011 a las 10:11:21
 * @package dataAccess
 */

/**
 * Archivos requeridos.
 */
require_once( 'dbase/OwlConnection.inc');
require_once( 'dbase/OwlGenericDO.inc');
require_once( 'TblPersonaSearch.inc' );
require_once( 'TblPersonaPK.inc' );

/**
 * Objeto para acceder a la tabla tblPersona.
 *
 * @package dataAccess
 */
class TblPersona extends OwlGenericDO{

    /**
     * Atributo que representa el campo "idPersona"
     * @var integer
     */
    public $idPersona;

    /**
     * Atributo que representa el campo "fkUsuario"
     * @var integer
     */
    public $fkUsuario;

    /**
     * Atributo que representa el campo "fkPais"
     * @var string
     */
    public $fkPais;

    /**
     * Atributo que representa el campo "fkProvincia"
     * @var integer
     */
    public $fkProvincia;

    /**
     * Atributo que representa el campo "fkTipoIdentificacion"
     * @var integer
     */
    public $fkTipoIdentificacion;

    /**
     * Atributo que representa el campo "fkEstadoCivil"
     * @var integer
     */
    public $fkEstadoCivil;

    /**
     * Atributo que representa el campo "fkEstadoLaboral"
     * @var integer
     */
    public $fkEstadoLaboral;

    /**
     * Atributo que representa el campo "fkNivelEstudios"
     * @var integer
     */
    public $fkNivelEstudios;

    /**
     * Atributo que representa el campo "vNombre"
     * @var string
     */
    public $vNombre;

    /**
     * Atributo que representa el campo "vPrimerApellido"
     * @var string
     */
    public $vPrimerApellido;

    /**
     * Atributo que representa el campo "vSegundoApellido"
     * @var string
     */
    public $vSegundoApellido;

    /**
     * Atributo que representa el campo "vSexo"
     * @var string
     */
    public $vSexo;

    /**
     * Atributo que representa el campo "vPoblacion"
     * @var string
     */
    public $vPoblacion;

    /**
     * Atributo que representa el campo "vCp"
     * @var string
     */
    public $vCp;

    /**
     * Atributo que representa el campo "vNumeroIdentificacion"
     * @var string
     */
    public $vNumeroIdentificacion;

    /**
     * Atributo que representa el campo "vNumeroSS"
     * @var string
     */
    public $vNumeroSS;

    /**
     * Atributo que representa el campo "vDireccion"
     * @var string
     */
    public $vDireccion;

    /**
     * Atributo que representa el campo "vTelefono"
     * @var string
     */
    public $vTelefono;

    /**
     * Atributo que representa el campo "vMovil"
     * @var string
     */
    public $vMovil;

    /**
     * Atributo que representa el campo "bActiva"
     * @var boolean
     */
    public $bActiva;

    /**
     * Atributo que representa el campo "dAlta"
     * @var string
     */
    public $dAlta;

    /**
     * Atributo que representa el campo "dNacimiento"
     * @var string
     */
    public $dNacimiento;

    /**
     * Atributo que representa el campo "bDiscapacidad"
     * @var integer
     */
    public $bDiscapacidad;

    /**
     * Atributo que representa el campo "vObservaciones"
     * @var string
     */
    public $vObservaciones;

    /**
     * Atributo que representa el campo "dBaja"
     * @var string
     */
    public $dBaja;

    /**
     * Atributo que representa el campo "fkCobros"
     * @var integer
     */
    public $fkCobros;

    /**
     * Atributo que representa el campo "dAntiguedadParo"
     * @var string
     */
    public $dAntiguedadParo;

    /**
     * Atributo que representa el campo "fkTrabajoParo"
     * @var integer
     */
    public $fkTrabajoParo;

    /**
     * Atributo que representa el campo "vSectorEmpresaActual"
     * @var string
     */
    public $vSectorEmpresaActual;

    /**
     * Atributo que representa el campo "fkCategoriaEmpleo"
     * @var integer
     */
    public $fkCategoriaEmpleo;

    /**
     * Atributo que representa el campo "bMas250Trabajadores"
     * @var integer
     */
    public $bMas250Trabajadores;

    /**
     * Atributo que representa el campo "vRazonSocialEmpresaActual"
     * @var string
     */
    public $vRazonSocialEmpresaActual;

    /**
     * Atributo que representa el campo "vCifEmpresaActual"
     * @var string
     */
    public $vCifEmpresaActual;

    /**
     * Atributo que representa el campo "vDomicilioCentroTrabajo"
     * @var string
     */
    public $vDomicilioCentroTrabajo;

    /**
     * Atributo que representa el campo "vLocalidadCentroTrabajo"
     * @var string
     */
    public $vLocalidadCentroTrabajo;

    /**
     * Atributo que representa el campo "vCpCentroTrabajo"
     * @var string
     */
    public $vCpCentroTrabajo;

    /**
     * Atributo que representa el campo "mod_user"
     * @var string
     */
    public $modUser;

    /**
     * Atributo que representa el campo "last_modified"
     * @var string
     */
    public $lastModified;

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
        $this->idPersona = $data['idPersona'];
        $this->fkUsuario = $data['fkUsuario'];
        $this->fkPais = $data['fkPais'];
        $this->fkProvincia = $data['fkProvincia'];
        $this->fkTipoIdentificacion = $data['fkTipoIdentificacion'];
        $this->fkEstadoCivil = $data['fkEstadoCivil'];
        $this->fkEstadoLaboral = $data['fkEstadoLaboral'];
        $this->fkNivelEstudios = $data['fkNivelEstudios'];
        $this->vNombre = $data['vNombre'];
        $this->vPrimerApellido = $data['vPrimerApellido'];
        $this->vSegundoApellido = $data['vSegundoApellido'];
        $this->vSexo = $data['vSexo'];
        $this->vPoblacion = $data['vPoblacion'];
        $this->vCp = $data['vCp'];
        $this->vNumeroIdentificacion = $data['vNumeroIdentificacion'];
        $this->vNumeroSS = $data['vNumeroSS'];
        $this->vDireccion = $data['vDireccion'];
        $this->vTelefono = $data['vTelefono'];
        $this->vMovil = $data['vMovil'];
        $this->bActiva = $data['bActiva'];
        $this->dAlta = $data['dAlta'];
        $this->dNacimiento = $data['dNacimiento'];
        $this->bDiscapacidad = $data['bDiscapacidad'];
        $this->vObservaciones = $data['vObservaciones'];
        $this->dBaja = $data['dBaja'];
        $this->fkCobros = $data['fkCobros'];
        $this->dAntiguedadParo = $data['dAntiguedadParo'];
        $this->fkTrabajoParo = $data['fkTrabajoParo'];
        $this->vSectorEmpresaActual = $data['vSectorEmpresaActual'];
        $this->fkCategoriaEmpleo = $data['fkCategoriaEmpleo'];
        $this->bMas250Trabajadores = $data['bMas250Trabajadores'];
        $this->vRazonSocialEmpresaActual = $data['vRazonSocialEmpresaActual'];
        $this->vCifEmpresaActual = $data['vCifEmpresaActual'];
        $this->vDomicilioCentroTrabajo = $data['vDomicilioCentroTrabajo'];
        $this->vLocalidadCentroTrabajo = $data['vLocalidadCentroTrabajo'];
        $this->vCpCentroTrabajo = $data['vCpCentroTrabajo'];
        $this->modUser = $data['mod_user'];
        $this->lastModified = $data['last_modified'];

    }

    // Métodos find

    /**
     * Realiza una búsqueda en la tabla tblPersona segun los atributos asignados en $searchItem.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblPersonaSearch $searchItem Objeto con los atributos de búsqueda.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public static function find( $db , $searchItem, $orderBy='' ){

        $sql = 'SELECT * FROM tblPersona';
        $where = array();
        if( $tmp = $searchItem->idPersona ){
            $where[] = "idPersona='$tmp'";
        }
        if( $tmp = $searchItem->fkUsuario ){
            $where[] = "fkUsuario='$tmp'";
        }
        if( $tmp = $searchItem->fkPais ){
            $where[] = "fkPais='$tmp'";
        }
        if( $tmp = $searchItem->fkProvincia ){
            $where[] = "fkProvincia='$tmp'";
        }
        if( $tmp = $searchItem->fkTipoIdentificacion ){
            $where[] = "fkTipoIdentificacion='$tmp'";
        }
        if( $tmp = $searchItem->fkEstadoCivil ){
            $where[] = "fkEstadoCivil='$tmp'";
        }
        if( $tmp = $searchItem->fkEstadoLaboral ){
            $where[] = "fkEstadoLaboral='$tmp'";
        }
        if( $tmp = $searchItem->fkNivelEstudios ){
            $where[] = "fkNivelEstudios='$tmp'";
        }
        if( $tmp = $searchItem->vNombre ){
            $where[] = "vNombre='$tmp'";
        }
        if( $tmp = $searchItem->vPrimerApellido ){
            $where[] = "vPrimerApellido='$tmp'";
        }
        if( $tmp = $searchItem->vSegundoApellido ){
            $where[] = "vSegundoApellido='$tmp'";
        }
        if( $tmp = $searchItem->vSexo ){
            $where[] = "vSexo='$tmp'";
        }
        if( $tmp = $searchItem->vPoblacion ){
            $where[] = "vPoblacion='$tmp'";
        }
        if( $tmp = $searchItem->vCp ){
            $where[] = "vCp='$tmp'";
        }
        if( $tmp = $searchItem->vNumeroIdentificacion ){
            $where[] = "vNumeroIdentificacion='$tmp'";
        }
        if( $tmp = $searchItem->vNumeroSS ){
            $where[] = "vNumeroSS='$tmp'";
        }
        if( $tmp = $searchItem->vDireccion ){
            $where[] = "vDireccion='$tmp'";
        }
        if( $tmp = $searchItem->vTelefono ){
            $where[] = "vTelefono='$tmp'";
        }
        if( $tmp = $searchItem->vMovil ){
            $where[] = "vMovil='$tmp'";
        }
        if( $tmp = $searchItem->bActiva ){
            $where[] = "bActiva='$tmp'";
        }
        if( $tmp = $searchItem->dAlta ){
            $where[] = "dAlta='$tmp'";
        }
        if( $tmp = $searchItem->dNacimiento ){
            $where[] = "dNacimiento='$tmp'";
        }
        if( $tmp = $searchItem->bDiscapacidad ){
            $where[] = "bDiscapacidad='$tmp'";
        }
        if( $tmp = $searchItem->vObservaciones ){
            $where[] = "vObservaciones='$tmp'";
        }
        if( $tmp = $searchItem->dBaja ){
            $where[] = "dBaja='$tmp'";
        }
        if( $tmp = $searchItem->fkCobros ){
            $where[] = "fkCobros='$tmp'";
        }
        if( $tmp = $searchItem->dAntiguedadParo ){
            $where[] = "dAntiguedadParo='$tmp'";
        }
        if( $tmp = $searchItem->fkTrabajoParo ){
            $where[] = "fkTrabajoParo='$tmp'";
        }
        if( $tmp = $searchItem->vSectorEmpresaActual ){
            $where[] = "vSectorEmpresaActual='$tmp'";
        }
        if( $tmp = $searchItem->fkCategoriaEmpleo ){
            $where[] = "fkCategoriaEmpleo='$tmp'";
        }
        if( $tmp = $searchItem->bMas250Trabajadores ){
            $where[] = "bMas250Trabajadores='$tmp'";
        }
        if( $tmp = $searchItem->vRazonSocialEmpresaActual ){
            $where[] = "vRazonSocialEmpresaActual='$tmp'";
        }
        if( $tmp = $searchItem->vCifEmpresaActual ){
            $where[] = "vCifEmpresaActual='$tmp'";
        }
        if( $tmp = $searchItem->vDomicilioCentroTrabajo ){
            $where[] = "vDomicilioCentroTrabajo='$tmp'";
        }
        if( $tmp = $searchItem->vLocalidadCentroTrabajo ){
            $where[] = "vLocalidadCentroTrabajo='$tmp'";
        }
        if( $tmp = $searchItem->vCpCentroTrabajo ){
            $where[] = "vCpCentroTrabajo='$tmp'";
        }
        if( $tmp = $searchItem->modUser ){
            $where[] = "mod_user='$tmp'";
        }
        if( $tmp = $searchItem->lastModified ){
            $where[] = "last_modified='$tmp'";
        }
        if( count($where) > 0 ){
            $where = implode( ' and ', $where );
            $sql.=' WHERE '.$where;
        }
        if( $orderBy != '' ){
            $sql.=" ORDER BY $orderBy";
        }
        return OwlGenericDO::createCollection( $db, $sql, 'TblPersona' );
}

    /**
     * Obtiene todas las filas de la tabla tblPersona.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
    public static function findAll( $db, $orderBy='' ){
         $sql = 'SELECT * FROM tblPersona';
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblPersona' );
    }

    /**
     * Obtiene el elemento de la tabla tblPersona que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer $idPersona valor del campo 'idPersona'.
     * @return TblPersona
     */
    public static function findByPrimaryKey( $db, $idPersona ){

       $db->executeQuery("SELECT * FROM tblPersona WHERE idPersona = '$idPersona'");
       $data = $db->fetchRow();
       return OwlGenericDO::createDO( $db, $data, 'TblPersona');

    }

    /**
     * Obtiene el elemento de la tabla tblPersona que coincide con la clave primaria especificada.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param TblPersonaPK $pk Objeto de la clave primaria.
     * @return TblPersona
     */
    public static function findByPKObject( $db, $pk ){

        $where = array();
        $where[]="idPersona='".$pk->idPersona."'";
        $where = implode(' AND ',$where);
        $db->executeQuery("SELECT * FROM tblPersona WHERE $where");
        $data = $db->fetchRow();
        return OwlGenericDO::createDO( $db, $data, 'TblPersona');

    }

    /**
     * Obtiene todas las filas de la tabla tblPersona que coinciden con el criterio fkTrabajoParo='$fkTrabajoParo'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkTrabajoParo string Valor del campo fkTrabajoParo.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblTrabajoParo( $db, $fkTrabajoParo, $orderBy='' ){
         $sql = "SELECT * FROM tblPersona WHERE fkTrabajoParo='$fkTrabajoParo'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblPersona' );
     }

    /**
     * Obtiene todas las filas de la tabla tblPersona que coinciden con el criterio fkCategoriaEmpleo='$fkCategoriaEmpleo'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCategoriaEmpleo string Valor del campo fkCategoriaEmpleo.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCategoriaEmpleo( $db, $fkCategoriaEmpleo, $orderBy='' ){
         $sql = "SELECT * FROM tblPersona WHERE fkCategoriaEmpleo='$fkCategoriaEmpleo'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblPersona' );
     }

    /**
     * Obtiene todas las filas de la tabla tblPersona que coinciden con el criterio fkCobros='$fkCobros'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkCobros string Valor del campo fkCobros.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblCobroParo( $db, $fkCobros, $orderBy='' ){
         $sql = "SELECT * FROM tblPersona WHERE fkCobros='$fkCobros'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblPersona' );
     }

    /**
     * Obtiene todas las filas de la tabla tblPersona que coinciden con el criterio fkEstadoCivil='$fkEstadoCivil'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkEstadoCivil string Valor del campo fkEstadoCivil.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblEstadoCivil( $db, $fkEstadoCivil, $orderBy='' ){
         $sql = "SELECT * FROM tblPersona WHERE fkEstadoCivil='$fkEstadoCivil'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblPersona' );
     }

    /**
     * Obtiene todas las filas de la tabla tblPersona que coinciden con el criterio fkEstadoLaboral='$fkEstadoLaboral'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkEstadoLaboral string Valor del campo fkEstadoLaboral.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblEstadoLaboral( $db, $fkEstadoLaboral, $orderBy='' ){
         $sql = "SELECT * FROM tblPersona WHERE fkEstadoLaboral='$fkEstadoLaboral'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblPersona' );
     }

    /**
     * Obtiene todas las filas de la tabla tblPersona que coinciden con el criterio fkNivelEstudios='$fkNivelEstudios'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkNivelEstudios string Valor del campo fkNivelEstudios.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblNivelEstudios( $db, $fkNivelEstudios, $orderBy='' ){
         $sql = "SELECT * FROM tblPersona WHERE fkNivelEstudios='$fkNivelEstudios'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblPersona' );
     }

    /**
     * Obtiene todas las filas de la tabla tblPersona que coinciden con el criterio fkPais='$fkPais'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string fkPais string Valor del campo fkPais.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblPais( $db, $fkPais, $orderBy='' ){
         $sql = "SELECT * FROM tblPersona WHERE fkPais='$fkPais'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblPersona' );
     }

    /**
     * Obtiene todas las filas de la tabla tblPersona que coinciden con el criterio fkProvincia='$fkProvincia'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkProvincia string Valor del campo fkProvincia.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblProvincia( $db, $fkProvincia, $orderBy='' ){
         $sql = "SELECT * FROM tblPersona WHERE fkProvincia='$fkProvincia'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblPersona' );
     }

    /**
     * Obtiene todas las filas de la tabla tblPersona que coinciden con el criterio fkTipoIdentificacion='$fkTipoIdentificacion'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkTipoIdentificacion string Valor del campo fkTipoIdentificacion.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblTipoIdentificacion( $db, $fkTipoIdentificacion, $orderBy='' ){
         $sql = "SELECT * FROM tblPersona WHERE fkTipoIdentificacion='$fkTipoIdentificacion'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblPersona' );
     }

    /**
     * Obtiene todas las filas de la tabla tblPersona que coinciden con el criterio fkUsuario='$fkUsuario'.
     *
     * @param Connection $db Conexión con la base de datos.
     * @param integer fkUsuario string Valor del campo fkUsuario.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     * @return array
     */
     public static function findByTblUsuario( $db, $fkUsuario, $orderBy='' ){
         $sql = "SELECT * FROM tblPersona WHERE fkUsuario='$fkUsuario'";
         if( $orderBy != '' ){
             $sql .= " ORDER BY $orderBy";
         }
         return OwlGenericDO::createCollection( $db, $sql, 'TblPersona' );
     }

    /**
     * Actualiza una fila de la tabla tblPersona.
     */
    public function update(){
        $sets = array();
        $sets[] = 'fkUsuario=' . ( ( ( $value = $this->fkUsuario ) === null || !isset($this->fkUsuario) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkPais=' . ( ( ( $value = $this->fkPais ) === null || !isset($this->fkPais) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkProvincia=' . ( ( ( $value = $this->fkProvincia ) === null || !isset($this->fkProvincia) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkTipoIdentificacion=' . ( ( ( $value = $this->fkTipoIdentificacion ) === null || !isset($this->fkTipoIdentificacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkEstadoCivil=' . ( ( ( $value = $this->fkEstadoCivil ) === null || !isset($this->fkEstadoCivil) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkEstadoLaboral=' . ( ( ( $value = $this->fkEstadoLaboral ) === null || !isset($this->fkEstadoLaboral) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkNivelEstudios=' . ( ( ( $value = $this->fkNivelEstudios ) === null || !isset($this->fkNivelEstudios) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNombre=' . ( ( ( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vPrimerApellido=' . ( ( ( $value = $this->vPrimerApellido ) === null || !isset($this->vPrimerApellido) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vSegundoApellido=' . ( ( ( $value = $this->vSegundoApellido ) === null || !isset($this->vSegundoApellido) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vSexo=' . ( ( ( $value = $this->vSexo ) === null || !isset($this->vSexo) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vPoblacion=' . ( ( ( $value = $this->vPoblacion ) === null || !isset($this->vPoblacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vCp=' . ( ( ( $value = $this->vCp ) === null || !isset($this->vCp) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNumeroIdentificacion=' . ( ( ( $value = $this->vNumeroIdentificacion ) === null || !isset($this->vNumeroIdentificacion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vNumeroSS=' . ( ( ( $value = $this->vNumeroSS ) === null || !isset($this->vNumeroSS) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDireccion=' . ( ( ( $value = $this->vDireccion ) === null || !isset($this->vDireccion) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vTelefono=' . ( ( ( $value = $this->vTelefono ) === null || !isset($this->vTelefono) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vMovil=' . ( ( ( $value = $this->vMovil ) === null || !isset($this->vMovil) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bActiva=' . ( ( ( $value = $this->bActiva ) === null || !isset($this->bActiva) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dAlta=' . ( ( ( $value = $this->dAlta ) === null || !isset($this->dAlta) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dNacimiento=' . ( ( ( $value = $this->dNacimiento ) === null || !isset($this->dNacimiento) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bDiscapacidad=' . ( ( ( $value = $this->bDiscapacidad ) === null || !isset($this->bDiscapacidad) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vObservaciones=' . ( ( ( $value = $this->vObservaciones ) === null || !isset($this->vObservaciones) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dBaja=' . ( ( ( $value = $this->dBaja ) === null || !isset($this->dBaja) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkCobros=' . ( ( ( $value = $this->fkCobros ) === null || !isset($this->fkCobros) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'dAntiguedadParo=' . ( ( ( $value = $this->dAntiguedadParo ) === null || !isset($this->dAntiguedadParo) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkTrabajoParo=' . ( ( ( $value = $this->fkTrabajoParo ) === null || !isset($this->fkTrabajoParo) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vSectorEmpresaActual=' . ( ( ( $value = $this->vSectorEmpresaActual ) === null || !isset($this->vSectorEmpresaActual) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'fkCategoriaEmpleo=' . ( ( ( $value = $this->fkCategoriaEmpleo ) === null || !isset($this->fkCategoriaEmpleo) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'bMas250Trabajadores=' . ( ( ( $value = $this->bMas250Trabajadores ) === null || !isset($this->bMas250Trabajadores) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vRazonSocialEmpresaActual=' . ( ( ( $value = $this->vRazonSocialEmpresaActual ) === null || !isset($this->vRazonSocialEmpresaActual) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vCifEmpresaActual=' . ( ( ( $value = $this->vCifEmpresaActual ) === null || !isset($this->vCifEmpresaActual) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vDomicilioCentroTrabajo=' . ( ( ( $value = $this->vDomicilioCentroTrabajo ) === null || !isset($this->vDomicilioCentroTrabajo) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vLocalidadCentroTrabajo=' . ( ( ( $value = $this->vLocalidadCentroTrabajo ) === null || !isset($this->vLocalidadCentroTrabajo) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'vCpCentroTrabajo=' . ( ( ( $value = $this->vCpCentroTrabajo ) === null || !isset($this->vCpCentroTrabajo) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'mod_user=' . ( ( ( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' :  "'".addslashes($value)."'" );
        $sets[] = 'last_modified=' . ( ( ( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' :  "'".addslashes($value)."'" );
        $setStr = implode(',', $sets);
        return $this->_db->executeQuery("UPDATE tblPersona SET $setStr WHERE idPersona='".addslashes($this->_data['idPersona'])."'");
    }

    /**
      * Inserta una nueva fila en la tabla tblPersona.
      */
    public function insert(){
        $attributes = array();
        $attributes[] = 'fkUsuario';
        $attributes[] = 'fkPais';
        $attributes[] = 'fkProvincia';
        $attributes[] = 'fkTipoIdentificacion';
        $attributes[] = 'fkEstadoCivil';
        $attributes[] = 'fkEstadoLaboral';
        $attributes[] = 'fkNivelEstudios';
        $attributes[] = 'vNombre';
        $attributes[] = 'vPrimerApellido';
        $attributes[] = 'vSegundoApellido';
        $attributes[] = 'vSexo';
        $attributes[] = 'vPoblacion';
        $attributes[] = 'vCp';
        $attributes[] = 'vNumeroIdentificacion';
        $attributes[] = 'vNumeroSS';
        $attributes[] = 'vDireccion';
        $attributes[] = 'vTelefono';
        $attributes[] = 'vMovil';
        $attributes[] = 'bActiva';
        $attributes[] = 'dAlta';
        $attributes[] = 'dNacimiento';
        $attributes[] = 'bDiscapacidad';
        $attributes[] = 'vObservaciones';
        $attributes[] = 'dBaja';
        $attributes[] = 'fkCobros';
        $attributes[] = 'dAntiguedadParo';
        $attributes[] = 'fkTrabajoParo';
        $attributes[] = 'vSectorEmpresaActual';
        $attributes[] = 'fkCategoriaEmpleo';
        $attributes[] = 'bMas250Trabajadores';
        $attributes[] = 'vRazonSocialEmpresaActual';
        $attributes[] = 'vCifEmpresaActual';
        $attributes[] = 'vDomicilioCentroTrabajo';
        $attributes[] = 'vLocalidadCentroTrabajo';
        $attributes[] = 'vCpCentroTrabajo';
        $attributes[] = 'mod_user';
        $attributes[] = 'last_modified';
        $attributes = implode(',', $attributes);
        $values = array();
        $values[] = (( $value = $this->fkUsuario ) === null || !isset($this->fkUsuario) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkPais ) === null || !isset($this->fkPais) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkProvincia ) === null || !isset($this->fkProvincia) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkTipoIdentificacion ) === null || !isset($this->fkTipoIdentificacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkEstadoCivil ) === null || !isset($this->fkEstadoCivil) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkEstadoLaboral ) === null || !isset($this->fkEstadoLaboral) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkNivelEstudios ) === null || !isset($this->fkNivelEstudios) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNombre ) === null || !isset($this->vNombre) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vPrimerApellido ) === null || !isset($this->vPrimerApellido) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vSegundoApellido ) === null || !isset($this->vSegundoApellido) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vSexo ) === null || !isset($this->vSexo) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vPoblacion ) === null || !isset($this->vPoblacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vCp ) === null || !isset($this->vCp) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNumeroIdentificacion ) === null || !isset($this->vNumeroIdentificacion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vNumeroSS ) === null || !isset($this->vNumeroSS) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDireccion ) === null || !isset($this->vDireccion) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vTelefono ) === null || !isset($this->vTelefono) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vMovil ) === null || !isset($this->vMovil) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bActiva ) === null || !isset($this->bActiva) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dAlta ) === null || !isset($this->dAlta) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dNacimiento ) === null || !isset($this->dNacimiento) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bDiscapacidad ) === null || !isset($this->bDiscapacidad) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vObservaciones ) === null || !isset($this->vObservaciones) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dBaja ) === null || !isset($this->dBaja) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkCobros ) === null || !isset($this->fkCobros) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->dAntiguedadParo ) === null || !isset($this->dAntiguedadParo) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkTrabajoParo ) === null || !isset($this->fkTrabajoParo) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vSectorEmpresaActual ) === null || !isset($this->vSectorEmpresaActual) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->fkCategoriaEmpleo ) === null || !isset($this->fkCategoriaEmpleo) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->bMas250Trabajadores ) === null || !isset($this->bMas250Trabajadores) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vRazonSocialEmpresaActual ) === null || !isset($this->vRazonSocialEmpresaActual) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vCifEmpresaActual ) === null || !isset($this->vCifEmpresaActual) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vDomicilioCentroTrabajo ) === null || !isset($this->vDomicilioCentroTrabajo) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vLocalidadCentroTrabajo ) === null || !isset($this->vLocalidadCentroTrabajo) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->vCpCentroTrabajo ) === null || !isset($this->vCpCentroTrabajo) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->modUser ) === null || !isset($this->modUser) ) ? 'null' : "'".addslashes($value)."'";
        $values[] = (( $value = $this->lastModified ) === null || !isset($this->lastModified) ) ? 'null' : "'".addslashes($value)."'";
        $values = implode(',', $values);
        if( $this->_db->executeQuery("INSERT INTO tblPersona($attributes) VALUES($values)") ){
            $eleDO = $this->findByPrimaryKey( $this->_db, $this->_db->getLastInsertId() );
            $this->_setData($eleDO->_data);
            return true;
        }
        return false;
    }

    /**
     * Borra una fila de la tabla tblPersona.
     */
    public function delete(){
        $where = array();
        $where[] = "idPersona="."'".addslashes($this->idPersona)."'";
        $where = implode(" AND ", $where);
        return $this->_db->executeQuery("DELETE FROM tblPersona WHERE $where");
    }

    /**
      * Obtiene el valor del atributo 'idPersona'.
      *
      * @return integer
      */
    public function getIdPersona(){
        return $this->idPersona;
    }

    /**
      * Obtiene el valor del atributo 'fkUsuario'.
      *
      * @return integer
      */
    public function getFkUsuario(){
        return $this->fkUsuario;
    }

    /**
      * Establece el valor del atributo 'fkUsuario'.
      *
      * @param integer Valor.
      */
    public function setFkUsuario( $value ){

        $this->fkUsuario = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkPais'.
      *
      * @return string
      */
    public function getFkPais(){
        return $this->fkPais;
    }

    /**
      * Establece el valor del atributo 'fkPais'.
      *
      * @param string Valor.
      */
    public function setFkPais( $value ){

        $this->fkPais = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkProvincia'.
      *
      * @return integer
      */
    public function getFkProvincia(){
        return $this->fkProvincia;
    }

    /**
      * Establece el valor del atributo 'fkProvincia'.
      *
      * @param integer Valor.
      */
    public function setFkProvincia( $value ){

        $this->fkProvincia = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkTipoIdentificacion'.
      *
      * @return integer
      */
    public function getFkTipoIdentificacion(){
        return $this->fkTipoIdentificacion;
    }

    /**
      * Establece el valor del atributo 'fkTipoIdentificacion'.
      *
      * @param integer Valor.
      */
    public function setFkTipoIdentificacion( $value ){

        $this->fkTipoIdentificacion = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkEstadoCivil'.
      *
      * @return integer
      */
    public function getFkEstadoCivil(){
        return $this->fkEstadoCivil;
    }

    /**
      * Establece el valor del atributo 'fkEstadoCivil'.
      *
      * @param integer Valor.
      */
    public function setFkEstadoCivil( $value ){

        $this->fkEstadoCivil = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkEstadoLaboral'.
      *
      * @return integer
      */
    public function getFkEstadoLaboral(){
        return $this->fkEstadoLaboral;
    }

    /**
      * Establece el valor del atributo 'fkEstadoLaboral'.
      *
      * @param integer Valor.
      */
    public function setFkEstadoLaboral( $value ){

        $this->fkEstadoLaboral = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkNivelEstudios'.
      *
      * @return integer
      */
    public function getFkNivelEstudios(){
        return $this->fkNivelEstudios;
    }

    /**
      * Establece el valor del atributo 'fkNivelEstudios'.
      *
      * @param integer Valor.
      */
    public function setFkNivelEstudios( $value ){

        $this->fkNivelEstudios = $value;

    }

    /**
      * Obtiene el valor del atributo 'vNombre'.
      *
      * @return string
      */
    public function getVNombre(){
        return $this->vNombre;
    }

    /**
      * Establece el valor del atributo 'vNombre'.
      *
      * @param string Valor.
      */
    public function setVNombre( $value ){

        $this->vNombre = $value;

    }

    /**
      * Obtiene el valor del atributo 'vPrimerApellido'.
      *
      * @return string
      */
    public function getVPrimerApellido(){
        return $this->vPrimerApellido;
    }

    /**
      * Establece el valor del atributo 'vPrimerApellido'.
      *
      * @param string Valor.
      */
    public function setVPrimerApellido( $value ){

        $this->vPrimerApellido = $value;

    }

    /**
      * Obtiene el valor del atributo 'vSegundoApellido'.
      *
      * @return string
      */
    public function getVSegundoApellido(){
        return $this->vSegundoApellido;
    }

    /**
      * Establece el valor del atributo 'vSegundoApellido'.
      *
      * @param string Valor.
      */
    public function setVSegundoApellido( $value ){

        $this->vSegundoApellido = $value;

    }

    /**
      * Obtiene el valor del atributo 'vSexo'.
      *
      * @return string
      */
    public function getVSexo(){
        return $this->vSexo;
    }

    /**
      * Establece el valor del atributo 'vSexo'.
      *
      * @param string Valor.
      */
    public function setVSexo( $value ){

        $this->vSexo = $value;

    }

    /**
      * Obtiene el valor del atributo 'vPoblacion'.
      *
      * @return string
      */
    public function getVPoblacion(){
        return $this->vPoblacion;
    }

    /**
      * Establece el valor del atributo 'vPoblacion'.
      *
      * @param string Valor.
      */
    public function setVPoblacion( $value ){

        $this->vPoblacion = $value;

    }

    /**
      * Obtiene el valor del atributo 'vCp'.
      *
      * @return string
      */
    public function getVCp(){
        return $this->vCp;
    }

    /**
      * Establece el valor del atributo 'vCp'.
      *
      * @param string Valor.
      */
    public function setVCp( $value ){

        $this->vCp = $value;

    }

    /**
      * Obtiene el valor del atributo 'vNumeroIdentificacion'.
      *
      * @return string
      */
    public function getVNumeroIdentificacion(){
        return $this->vNumeroIdentificacion;
    }

    /**
      * Establece el valor del atributo 'vNumeroIdentificacion'.
      *
      * @param string Valor.
      */
    public function setVNumeroIdentificacion( $value ){

        $this->vNumeroIdentificacion = $value;

    }

    /**
      * Obtiene el valor del atributo 'vNumeroSS'.
      *
      * @return string
      */
    public function getVNumeroSS(){
        return $this->vNumeroSS;
    }

    /**
      * Establece el valor del atributo 'vNumeroSS'.
      *
      * @param string Valor.
      */
    public function setVNumeroSS( $value ){

        $this->vNumeroSS = $value;

    }

    /**
      * Obtiene el valor del atributo 'vDireccion'.
      *
      * @return string
      */
    public function getVDireccion(){
        return $this->vDireccion;
    }

    /**
      * Establece el valor del atributo 'vDireccion'.
      *
      * @param string Valor.
      */
    public function setVDireccion( $value ){

        $this->vDireccion = $value;

    }

    /**
      * Obtiene el valor del atributo 'vTelefono'.
      *
      * @return string
      */
    public function getVTelefono(){
        return $this->vTelefono;
    }

    /**
      * Establece el valor del atributo 'vTelefono'.
      *
      * @param string Valor.
      */
    public function setVTelefono( $value ){

        $this->vTelefono = $value;

    }

    /**
      * Obtiene el valor del atributo 'vMovil'.
      *
      * @return string
      */
    public function getVMovil(){
        return $this->vMovil;
    }

    /**
      * Establece el valor del atributo 'vMovil'.
      *
      * @param string Valor.
      */
    public function setVMovil( $value ){

        $this->vMovil = $value;

    }

    /**
      * Obtiene el valor del atributo 'bActiva'.
      *
      * @return boolean
      */
    public function isBActiva(){
        return ($this->bActiva ? true : false);
    }

    /**
      * Establece el valor del atributo 'bActiva'.
      *
      * @param boolean Valor.
      */
    public function setBActiva( $value ){

        $this->bActiva = $value;

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

    /**
      * Obtiene el valor del atributo 'dNacimiento'.
      *
      * @return string
      */
    public function getDNacimiento(){
        return $this->dNacimiento;
    }

    /**
      * Establece el valor del atributo 'dNacimiento'.
      *
      * @param string Valor.
      */
    public function setDNacimiento( $value ){

        $this->dNacimiento = $value;

    }

    /**
      * Obtiene el valor del atributo 'bDiscapacidad'.
      *
      * @return integer
      */
    public function getBDiscapacidad(){
        return $this->bDiscapacidad;
    }

    /**
      * Establece el valor del atributo 'bDiscapacidad'.
      *
      * @param integer Valor.
      */
    public function setBDiscapacidad( $value ){

        $this->bDiscapacidad = $value;

    }

    /**
      * Obtiene el valor del atributo 'vObservaciones'.
      *
      * @return string
      */
    public function getVObservaciones(){
        return $this->vObservaciones;
    }

    /**
      * Establece el valor del atributo 'vObservaciones'.
      *
      * @param string Valor.
      */
    public function setVObservaciones( $value ){

        $this->vObservaciones = $value;

    }

    /**
      * Obtiene el valor del atributo 'dBaja'.
      *
      * @return string
      */
    public function getDBaja(){
        return $this->dBaja;
    }

    /**
      * Establece el valor del atributo 'dBaja'.
      *
      * @param string Valor.
      */
    public function setDBaja( $value ){

        $this->dBaja = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkCobros'.
      *
      * @return integer
      */
    public function getFkCobros(){
        return $this->fkCobros;
    }

    /**
      * Establece el valor del atributo 'fkCobros'.
      *
      * @param integer Valor.
      */
    public function setFkCobros( $value ){

        $this->fkCobros = $value;

    }

    /**
      * Obtiene el valor del atributo 'dAntiguedadParo'.
      *
      * @return string
      */
    public function getDAntiguedadParo(){
        return $this->dAntiguedadParo;
    }

    /**
      * Establece el valor del atributo 'dAntiguedadParo'.
      *
      * @param string Valor.
      */
    public function setDAntiguedadParo( $value ){

        $this->dAntiguedadParo = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkTrabajoParo'.
      *
      * @return integer
      */
    public function getFkTrabajoParo(){
        return $this->fkTrabajoParo;
    }

    /**
      * Establece el valor del atributo 'fkTrabajoParo'.
      *
      * @param integer Valor.
      */
    public function setFkTrabajoParo( $value ){

        $this->fkTrabajoParo = $value;

    }

    /**
      * Obtiene el valor del atributo 'vSectorEmpresaActual'.
      *
      * @return string
      */
    public function getVSectorEmpresaActual(){
        return $this->vSectorEmpresaActual;
    }

    /**
      * Establece el valor del atributo 'vSectorEmpresaActual'.
      *
      * @param string Valor.
      */
    public function setVSectorEmpresaActual( $value ){

        $this->vSectorEmpresaActual = $value;

    }

    /**
      * Obtiene el valor del atributo 'fkCategoriaEmpleo'.
      *
      * @return integer
      */
    public function getFkCategoriaEmpleo(){
        return $this->fkCategoriaEmpleo;
    }

    /**
      * Establece el valor del atributo 'fkCategoriaEmpleo'.
      *
      * @param integer Valor.
      */
    public function setFkCategoriaEmpleo( $value ){

        $this->fkCategoriaEmpleo = $value;

    }

    /**
      * Obtiene el valor del atributo 'bMas250Trabajadores'.
      *
      * @return integer
      */
    public function getBMas250Trabajadores(){
        return $this->bMas250Trabajadores;
    }

    /**
      * Establece el valor del atributo 'bMas250Trabajadores'.
      *
      * @param integer Valor.
      */
    public function setBMas250Trabajadores( $value ){

        $this->bMas250Trabajadores = $value;

    }

    /**
      * Obtiene el valor del atributo 'vRazonSocialEmpresaActual'.
      *
      * @return string
      */
    public function getVRazonSocialEmpresaActual(){
        return $this->vRazonSocialEmpresaActual;
    }

    /**
      * Establece el valor del atributo 'vRazonSocialEmpresaActual'.
      *
      * @param string Valor.
      */
    public function setVRazonSocialEmpresaActual( $value ){

        $this->vRazonSocialEmpresaActual = $value;

    }

    /**
      * Obtiene el valor del atributo 'vCifEmpresaActual'.
      *
      * @return string
      */
    public function getVCifEmpresaActual(){
        return $this->vCifEmpresaActual;
    }

    /**
      * Establece el valor del atributo 'vCifEmpresaActual'.
      *
      * @param string Valor.
      */
    public function setVCifEmpresaActual( $value ){

        $this->vCifEmpresaActual = $value;

    }

    /**
      * Obtiene el valor del atributo 'vDomicilioCentroTrabajo'.
      *
      * @return string
      */
    public function getVDomicilioCentroTrabajo(){
        return $this->vDomicilioCentroTrabajo;
    }

    /**
      * Establece el valor del atributo 'vDomicilioCentroTrabajo'.
      *
      * @param string Valor.
      */
    public function setVDomicilioCentroTrabajo( $value ){

        $this->vDomicilioCentroTrabajo = $value;

    }

    /**
      * Obtiene el valor del atributo 'vLocalidadCentroTrabajo'.
      *
      * @return string
      */
    public function getVLocalidadCentroTrabajo(){
        return $this->vLocalidadCentroTrabajo;
    }

    /**
      * Establece el valor del atributo 'vLocalidadCentroTrabajo'.
      *
      * @param string Valor.
      */
    public function setVLocalidadCentroTrabajo( $value ){

        $this->vLocalidadCentroTrabajo = $value;

    }

    /**
      * Obtiene el valor del atributo 'vCpCentroTrabajo'.
      *
      * @return string
      */
    public function getVCpCentroTrabajo(){
        return $this->vCpCentroTrabajo;
    }

    /**
      * Establece el valor del atributo 'vCpCentroTrabajo'.
      *
      * @param string Valor.
      */
    public function setVCpCentroTrabajo( $value ){

        $this->vCpCentroTrabajo = $value;

    }

    /**
      * Obtiene el valor del atributo 'mod_user'.
      *
      * @return string
      */
    public function getModUser(){
        return $this->modUser;
    }

    /**
      * Establece el valor del atributo 'mod_user'.
      *
      * @param string Valor.
      */
    public function setModUser( $value ){

        $this->modUser = $value;

    }

    /**
      * Obtiene el valor del atributo 'last_modified'.
      *
      * @return string
      */
    public function getLastModified(){
        return $this->lastModified;
    }

    /**
      * Establece el valor del atributo 'last_modified'.
      *
      * @param string Valor.
      */
    public function setLastModified( $value ){

        $this->lastModified = $value;

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblDesiderata'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblDesideratas( $orderBy='' ){

        include_once('TblDesiderata.inc');
        return TblDesiderata::findByTblPersona( $this->_db, $this->idPersona, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblDisponibilidadProfesor'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblDisponibilidadProfesors( $orderBy='' ){

        include_once('TblDisponibilidadProfesor.inc');
        return TblDisponibilidadProfesor::findByTblPersona( $this->_db, $this->idPersona, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'tblTutoria'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTblTutorias( $orderBy='' ){

        include_once('TblTutoria.inc');
        return TblTutoria::findByTblPersona( $this->_db, $this->idPersona, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelCandidato'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelCandidatos( $orderBy='' ){

        include_once('TrelCandidato.inc');
        return TrelCandidato::findByTblPersona( $this->_db, $this->idPersona, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelEstudioPersona'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelEstudioPersonas( $orderBy='' ){

        include_once('TrelEstudioPersona.inc');
        return TrelEstudioPersona::findByTblPersona( $this->_db, $this->idPersona, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelNotificacionPersona'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelNotificacionPersonas( $orderBy='' ){

        include_once('TrelNotificacionPersona.inc');
        return TrelNotificacionPersona::findByTblPersona( $this->_db, $this->idPersona, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelPersonaCarnet'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelPersonaCarnets( $orderBy='' ){

        include_once('TrelPersonaCarnet.inc');
        return TrelPersonaCarnet::findByTblPersona( $this->_db, $this->idPersona, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelPersonaCategoria'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelPersonaCategorias( $orderBy='' ){

        include_once('TrelPersonaCategoria.inc');
        return TrelPersonaCategoria::findByTblPersona( $this->_db, $this->idPersona, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelPrecandidato'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelPrecandidatos( $orderBy='' ){

        include_once('TrelPrecandidato.inc');
        return TrelPrecandidato::findByTblPersona( $this->_db, $this->idPersona, $orderBy );

    }

    /**
     * Obtiene todos los elementos relacionados de la tabla 'trelProfesor'
     *
     * @param Connection $db Conexión con la base de datos.
     * @param string $orderBy Cadena con los campos de ordenación separados por comas.
     */
    public function getTrelProfesors( $orderBy='' ){

        include_once('TrelProfesor.inc');
        return TrelProfesor::findByTblPersona( $this->_db, $this->idPersona, $orderBy );

    }

    // Relaciones

    /**
     * Obtiene el objeto 'TblTrabajoParo' relacionado.
     *
     * @return TblTrabajoParo
     */
    public function getTblTrabajoParo(){
        require_once('TblTrabajoParo.inc');
        return TblTrabajoParo::findByPrimaryKey( $this->_db, $this->fkTrabajoParo );
    }

    /**
     * Asigna el objeto 'TblTrabajoParo' relacionado.
     *
     * @param TblTrabajoParo $dataObject
     */
    public function setTblTrabajoParo( $dataObject ){
        require_once('TblTrabajoParo.inc');
        $this->setFkTrabajoParo( $dataObject->getIdTrabajoParo() );
    }

    /**
     * Obtiene el objeto 'TblCategoriaEmpleo' relacionado.
     *
     * @return TblCategoriaEmpleo
     */
    public function getTblCategoriaEmpleo(){
        require_once('TblCategoriaEmpleo.inc');
        return TblCategoriaEmpleo::findByPrimaryKey( $this->_db, $this->fkCategoriaEmpleo );
    }

    /**
     * Asigna el objeto 'TblCategoriaEmpleo' relacionado.
     *
     * @param TblCategoriaEmpleo $dataObject
     */
    public function setTblCategoriaEmpleo( $dataObject ){
        require_once('TblCategoriaEmpleo.inc');
        $this->setFkCategoriaEmpleo( $dataObject->getIdCategoriaEmpleo() );
    }

    /**
     * Obtiene el objeto 'TblCobroParo' relacionado.
     *
     * @return TblCobroParo
     */
    public function getTblCobroParo(){
        require_once('TblCobroParo.inc');
        return TblCobroParo::findByPrimaryKey( $this->_db, $this->fkCobros );
    }

    /**
     * Asigna el objeto 'TblCobroParo' relacionado.
     *
     * @param TblCobroParo $dataObject
     */
    public function setTblCobroParo( $dataObject ){
        require_once('TblCobroParo.inc');
        $this->setFkCobros( $dataObject->getIdCobroParo() );
    }

    /**
     * Obtiene el objeto 'TblEstadoCivil' relacionado.
     *
     * @return TblEstadoCivil
     */
    public function getTblEstadoCivil(){
        require_once('TblEstadoCivil.inc');
        return TblEstadoCivil::findByPrimaryKey( $this->_db, $this->fkEstadoCivil );
    }

    /**
     * Asigna el objeto 'TblEstadoCivil' relacionado.
     *
     * @param TblEstadoCivil $dataObject
     */
    public function setTblEstadoCivil( $dataObject ){
        require_once('TblEstadoCivil.inc');
        $this->setFkEstadoCivil( $dataObject->getIdEstadoCivil() );
    }

    /**
     * Obtiene el objeto 'TblEstadoLaboral' relacionado.
     *
     * @return TblEstadoLaboral
     */
    public function getTblEstadoLaboral(){
        require_once('TblEstadoLaboral.inc');
        return TblEstadoLaboral::findByPrimaryKey( $this->_db, $this->fkEstadoLaboral );
    }

    /**
     * Asigna el objeto 'TblEstadoLaboral' relacionado.
     *
     * @param TblEstadoLaboral $dataObject
     */
    public function setTblEstadoLaboral( $dataObject ){
        require_once('TblEstadoLaboral.inc');
        $this->setFkEstadoLaboral( $dataObject->getIdEstadoLaboral() );
    }

    /**
     * Obtiene el objeto 'TblNivelEstudios' relacionado.
     *
     * @return TblNivelEstudios
     */
    public function getTblNivelEstudios(){
        require_once('TblNivelEstudios.inc');
        return TblNivelEstudios::findByPrimaryKey( $this->_db, $this->fkNivelEstudios );
    }

    /**
     * Asigna el objeto 'TblNivelEstudios' relacionado.
     *
     * @param TblNivelEstudios $dataObject
     */
    public function setTblNivelEstudios( $dataObject ){
        require_once('TblNivelEstudios.inc');
        $this->setFkNivelEstudios( $dataObject->getIdNivelEstudios() );
    }

    /**
     * Obtiene el objeto 'TblPais' relacionado.
     *
     * @return TblPais
     */
    public function getTblPais(){
        require_once('TblPais.inc');
        return TblPais::findByPrimaryKey( $this->_db, $this->fkPais );
    }

    /**
     * Asigna el objeto 'TblPais' relacionado.
     *
     * @param TblPais $dataObject
     */
    public function setTblPais( $dataObject ){
        require_once('TblPais.inc');
        $this->setFkPais( $dataObject->getVIso() );
    }

    /**
     * Obtiene el objeto 'TblProvincia' relacionado.
     *
     * @return TblProvincia
     */
    public function getTblProvincia(){
        require_once('TblProvincia.inc');
        return TblProvincia::findByPrimaryKey( $this->_db, $this->fkProvincia );
    }

    /**
     * Asigna el objeto 'TblProvincia' relacionado.
     *
     * @param TblProvincia $dataObject
     */
    public function setTblProvincia( $dataObject ){
        require_once('TblProvincia.inc');
        $this->setFkProvincia( $dataObject->getIdProvincia() );
    }

    /**
     * Obtiene el objeto 'TblTipoIdentificacion' relacionado.
     *
     * @return TblTipoIdentificacion
     */
    public function getTblTipoIdentificacion(){
        require_once('TblTipoIdentificacion.inc');
        return TblTipoIdentificacion::findByPrimaryKey( $this->_db, $this->fkTipoIdentificacion );
    }

    /**
     * Asigna el objeto 'TblTipoIdentificacion' relacionado.
     *
     * @param TblTipoIdentificacion $dataObject
     */
    public function setTblTipoIdentificacion( $dataObject ){
        require_once('TblTipoIdentificacion.inc');
        $this->setFkTipoIdentificacion( $dataObject->getIdTipoIdentificacion() );
    }

    /**
     * Obtiene el objeto 'TblUsuario' relacionado.
     *
     * @return TblUsuario
     */
    public function getTblUsuario(){
        require_once('TblUsuario.inc');
        return TblUsuario::findByPrimaryKey( $this->_db, $this->fkUsuario );
    }

    /**
     * Asigna el objeto 'TblUsuario' relacionado.
     *
     * @param TblUsuario $dataObject
     */
    public function setTblUsuario( $dataObject ){
        require_once('TblUsuario.inc');
        $this->setFkUsuario( $dataObject->getIdUsuario() );
    }
}
?>