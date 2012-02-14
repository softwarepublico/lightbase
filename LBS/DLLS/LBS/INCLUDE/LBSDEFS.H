/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o título
"LICENCA.txt", junto com este programa, se não, escreva para a Fundação do Software 
Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

//
// Module: LBSDEFS.H
//	Defines several macros
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last revision: 21/10/94
//


#ifndef	_LBSDEFS_H_
#define	_LBSDEFS_H_

#ifndef	_INCLUDES_H_
#include	<includes.h>
#endif

#if !defined __DIR_H && !defined _INC_DIRECT
#include	DIR_H
#endif
#if !defined __VALUES_H && !defined _INC_LIMITS
#include	VALUES_H
#endif
#if !defined _INC_STDLIB			// apenas para o caso de MSVC20
#include	<stdlib.h>
#endif
#ifndef	_USERDEFS_H_
#include	<userdefs.h>
#endif
#ifndef	_LBSERROR_H_
#include	<lbserror.h>
#endif

// $$$ API LIGHT-TEXT
#include	"const.h"


// ultimo include
#ifndef	_DEFMACRO_H_
#include	<defmacro.h>
#endif

// General macros

#define	PROFILE_ERROR( X )		(strcmp( (char*) X, "" ) == 0)
#define	FISIC_OC_LIST			(pcOLList->GetCurrentIndex() == 0)

#define	LBS_LESSTHAN				-1
#define	LBS_GREATERTHAN				1
#define	LBS_EQUAL					0
#define	FILENAMESIZE				(MAXPATH) //(MAXFILE + MAXEXT)		// defined in dir.h file
#define	PATHNAMESIZE				(MAXPATH)			// defined in dir.h file
#define	FULLNAMESIZE				(MAXPATH)			// defined in dir.h file
#define	SERVERNAMESIZE				(50)
#define	SERIALNUMBERSIZE			(50)
#define	MACHINEADDRSIZE				50
#define	NUMRECREORGANIZE			0
#define	DEFBASEPASSWORD				"$"
#define	DEFRECORDPASSWORD			"$"
#define	DEFBASEPASSWORDTYPE			0
#define	DEFRECORDPASSWORDTYPE		0
#define	DEFUSERPASSWORD				"$"
#define	DEFUSERPASSWORDTYPE			0
#define	DEFBASEPASSTYPE				0
#define	FIELDNAMESIZE				32
#define	DATESIZE					8
#define	ALIASSIZE					10
#define	FIRSTDRIVELETTER			'A'
#define	CONTROLFILEEXT				".LB1"
#define	SLOTFILEEXT 				".LB2"
#define	STRUCTFILEEXT 				".LB3"
#define	REPETITIONFILEEXT 			".LB4"
#define	LOGFILE1EXT					".LB5"
#define	LB1BAKEXT					".LB6"
#define	ACLFILEEXT					".LB7"
#define	LOCKFILEEXT					".LCK"
#define	GOWORDFILEEXT				".LB"
#define	INDEXDIR					"INDEX"
#define	STDFILEEXT					".STD"	// arquivo de normalizadores
#define	CONFFILEEXT					".CONF"
#define	GOWORDSFILE					"GOWORDS.LB"
#define	STOPWORDFILENAME	 		"STOPWORD.LB"
#define	IDXCONTEXTFILE				"INDEX.CTX"
#define	DEFAULTSERVER				NULL
#define	OCLISTFILEEXT				".OL"
#define	LTIFILEEXT					".LTI"
#define	LICFILENAME					"LICFILE.LB"
#define	INFOFILENAME				"INFOFILE.LB"
#define	DEFAULTREORGRECQUANT		500
#define	CONTROLFILEHEADRECPOS		0
#define	CONTROLFILEFIRSTRECPOS		( sizeof( TControlRecHead ) )

#define	CONTENTFILEHEADRECPOS		0
#define	CONTENTFILEFEFIRSTRECPOS	( sizeof( TContentRecHead ) )
#define	CONTENTFREESPACEPOS			( sizeof( TContentRecHead ) - sizeof( TFreeSpace ) )

#define	STRUCTFILEHEADRECPOS		0
#define	STRUCTFILEFIRSTRECPOS		( sizeof( TStructHeadRec ) )

#define	REPETITIONFILHEADRECPOS		0
#define	REPETITIONFILEFEFIRSTRECPOS	( sizeof( TRepetitionRecHead ) )
#define	REPETITIONFREESPACEPOS		( sizeof( TRepetitionRecHead ) - sizeof( TFreeSpace ) )

#define	BASEPASSWORDSIZE			PASSWORDSIZE

// lista de versoes de base
#define	BEFORECRYPTO_MAGICNUMBER	3			// numero magico para bases antigas
#define	CRYPTO_MAGICNUMBER			4			// numero magico para bases atuais (v. 3.1.7)
#define	LICFILE_MAGICNUMBER			5			// numero magico para arquivo de controle de licencas em rede (v. 3.1.7)
#define	COMPRESS_MAGICNUMBER		6			// numero magico para bases que utilizam o mecanismo de compressao de dados.
#define	REFERENCE_MAGICNUMBER		7			// numero magico para bases que utilizam compressao em campos reference (v. 3.2.18)
#define	OCCTREE_MAGICNUMBER			8			// numero magico para bases que utilizam uma arvore para as ocorrencias (v. 3.3)
#define	COMPONENTPERM_MAGICNUMBER	9			// numero magico para bases que utilizam esquemas de permissoes para componentes (v. 3.3.3) - conv automatica
#define	SORTGROUP_MAGICNUMBER		10			// numero magico para bases que corrigem bug de tratamento de grupos com campos ordenados - create.dll (v. 3.3.4)- conv automatica
#define	LOCKCOUNT_MAGICNUMBER		11			// numero magico para bases que suportam lock de contadores (v. 3.3.5) - conv automatica
#define	OCCUNIQUETREE_MAGICNUMBER	12			// numero magico para bases que utilizam a arvore das ocorrencias para chave unica (v. 3.3.6)
#define	EMPTYTREE_MAGICNUMBER		13			// numero magico para bases que utilizam a arvore EMPTY (v. 3.6)
#define	OCCFILE_MAGICNUMBER			14			// numero magico para bases que utilizam a arquivos separados para as ocorrencias (v. 3.7/3.8)
#define	SOUNDEX_MAGICNUMBER			15			// numero magico para bases que contem o indice soundex e o novo indice de conteudo vazio (v. 3.9)
#define	PAGEFILE_MAGICNUMBER		16			// numero magico para bases cujo LB4 eh um pagefile 
#define	CURRENT_MAGICNUMBER			PAGEFILE_MAGICNUMBER		// versao atual

// lista de versoes da UDB
#define	SEMARROBA_UDBMAGICNUMBER		(OCCFILE_MAGICNUMBER+1)			// numero magico para remover os "arrobas" dos nomes dos campos
#define	SECURITYFIELDS_UDBMAGICNUMBER	(SEMARROBA_UDBMAGICNUMBER+1)	// numero magico para incluir campos necessarios aas verificacoes de seguranca
#define	CURRENT_UDBMAGICNUMBER			SECURITYFIELDS_UDBMAGICNUMBER	// versao atual

#define	RECORDPASSWORDSIZE			PASSWORDSIZE
#define	FIELDPASSWORDSIZE			PASSWORDSIZE
#define	FIRSTSTRUCTRECORD			0
#define	CONTROLFILETMPEXT			".TB1"
#define	CONTENTFILETMPEXT			".TB2"
#define	STRUCTFILETMPEXT			".TB3"
#define	REPETITIONFILETMPEXT		".TB4"

#define REC_INDEXED					0x01	// $$$ indica que o registro está indexado
#define	REC_EXCLUDED				0x02	// $$$ indica que o registro está deletado
#define	REC_LOCKED					0x04	// $$$ indica que o registro está travado
#define	REC_UPDATED					0x08	// $$$ indica que o registro está atualizado
#define	REC_INLOGFILE				0x10	// $$$ em memória e precisa ser regravado

#define BASE_PRIVATE            	0x00
#define	BASE_PUBLIC					0x01
#define	BASE_PUBLIC_REC_PRIVATE		0x02
#define	BASE_PRIVATE_REC_PRIVATE	0x03
#define	USER_BASE					0x10
//#define	LBSINIFILE					"LBS.INI"	// nome do arquivo de inicializacao
#define	LBSINIFILE					(GetAppIniPath( "LBS" ))	// nome do arquivo de inicializacao com o path
#define	LBSINILBSSECTION			"LIGHTBASESERVER"
#define	LBSINISECURITYSECTION		"SECURITY"
#define DCESECTION				"LBS_DCE"
#define	LBSINILIGHTDIR				"LBSDIR"	// diretorio das bases LBS
#define	LBSINILIGHTTEMPDIR			"LBSTEMPDIR"	// diretorio de trabalho do LBS
#define	LBSINIBASESFILENAME			"BFILENAME"	// nome do arquivo de controle
#define	LBSINIDEFMSG				"NOT FOUND"	// mensagem default
#define	LBSOCCTMOUTKEY				"OCCLIST_TIMEOUT"
#define	MAXKEYSIZESTR				"MAXKEYSIZE"	// tamanho maximo de uma chave para o sistema de indices
#define	INTPARTSTR					"INTPART"	// tamanho da parte inteira de uma chave numerica
#define	DECPARTSTR					"DECPART"	// tamanho da parte decimal de uma chave numerica
#define	STOPINDEX					100		// numero de registro a indexar antes de salvar contexto
#define	STOPINDEXSTR				"STOPINDEX"	//
#define	TEMPBASENAME				"base_t"	//
#define	DIR_BASE_KEY				"DIR_BASE"	//
#define	LOCKTIMESLEEP				2000		// tempo de espera para novo lock - em milisegundos
#define	LOCKTIMESLEEPSTR			"LOCKTIMESLEEP"	//
#define	LOCKTIMEOUT					60000		// time-out de lock - em milisegundos
#define	LOCKTIMEOUTSTR				"LOCKTIMEOUT"	//
#define	LBSINISERVERNAME			"SERVERNAME"	// nome do servidor
#define	MAXNUMFILE32SSTR			"MAXNUMFILE32S"	// numero maximo de arquivos para Win32s
#define	MAXNUMFILE32S				-1
#define	CLOSESTDFILESSTR			"CLOSESTDFILES"	// indica se os stdfiles devem ser fechados
#define	HOSTKEYSIZE					10
#define	HOSTSIZE					60
#define	HOSTKEY						"H"
#define	LBSINIHOSTSECTION			"HOSTS"
#define SERVERPROTOKEY				"SERVER_PROTOCOL"
#define CLIENTPROTOKEY				"CLIENT_PROTOCOL"
#define PROTOSIZE					20
#define TCP_STR						"TCPIP"
#define TCPIP_PROTO					"ncacn_ip_tcp"
#define TCPIP_ENDPOINT				"2022"
#define NP_STR						"NP"
#define NP_PROTO					"ncacn_np"
#define NP_ENDPOINT					"\\pipe\\lbsrpc"
#define NB_STR						"NB"
#define NB_PROTO					"ncacn_nb_nb"
#define NB_ENDPOINT					"171"
#define	NETTIMEOUTKEY				"NETTIMEOUT"
#define	LBSANONYMOUSNAME			"ANONYMOUS"
#define	ANONYMOUS_USERNAME			"X-BLZW1-X"
#define	GWMAINSECTION				"MAIN"
#define	GWMINKEYSIZE				"MINKEYSIZE"
#define	GWFIELDKEY					"FIELD"
#define	GWKEY						"GW"
#define	COMPRESSKEY					"COMPRESS"
#define	COMPRESSDEFVAL				0
#define	REFERENCEDIRBASE			"REFDIRBASE"
#define	REFERENCEDEFDIRBASE			""
#define	DEF_MAINTBASE_WARNINGMSG	"DEF_MAINTBASE_WARNINGMSG"
#define LOGUSE_FIELD_KEY			"FIELD"
#define LOGUSE_EXCLUDE_MODULES_KEY	"EXCLUDE_MODULES"
#define LOGUSE_FIELDSFORUPDATELOG_KEY	"FIELDSFORUPDATELOG"
#define LOGUSE_OPERATIONS_KEY		"OPERATIONS"
#define LOGUSE_SECTION				"USAGELOG"

#define	OLDUSERBASEUSERNAME			"@UserName@"
#define	OLDUSERBASEUSERPASSWORD		"@Password@"
#define	OLDUSERBASEUSERTYPE			"@UserType@"
#define	OLDUSERBASEUSERDESCRIPTION	"@Description@"
#define	OLDUSERBASEUSERADDRESS		"@Address@"
#define	OLDUSERBASEUSERPHONE		"@Phone@"
#define OLDUSERBASEGROUPLIST		"@GroupList@"
#define	OLDUSERBASEUSERCREATEDATE	"@CreateDate@"
#define OLDUSERBASEUSERUPDATEDATE	"@UpdateDate@"
#define OLDUSERBASEACCESSBASES		"@AccessBases@"
#define OLDUSERBASEACCESSTYPES		"@AccessTypes@"

#define	USERBASEUSERNAME			"UserName"
#define	USERBASEUSERPASSWORD		"Password"
#define	USERBASEUSERTYPE			"UserType"
#define	USERBASEUSERDESCRIPTION		"Description"
#define	USERBASEUSERADDRESS			"Address"
#define	USERBASEUSERPHONE			"Phone"
#define USERBASEGROUPLIST			"GroupList"
#define	USERBASEUSERCREATEDATE		"CreateDate"
#define USERBASEUSERUPDATEDATE		"UpdateDate"
#define USERBASEACCESSBASES			"AccessBases"
#define USERBASEACCESSTYPES			"AccessTypes"
#define USERBASELOGINATTEMPTS		"InvalidLoginAttempts"
#define USERBASEPASSWORDCHANGEDATE	"PasswordChangeDate"

#define	MAXTERM				100

#define MAXBASEID			MAXINT
#define MAXPSWTYPESIZE			4
#define MAXBASETYPESIZE			25
#define MAXNUMFIELDSSIZE		4
#define MAXFIELDTYPESIZE		15
#define MAXFIELDPSWTYPESIZE		4
#define MAXFIELDSIZESIZE		4
#define MAXFIELDIDSIZE			4
#define MAXENCRYPTSIZE			10
#define MAXTOKENSIZE			50
#define MAXKEYSIZE			50
#define MAXINDEXATRIBSIZE		255
#define	INTPART				10
#define	DECPART				5
#define	MAXINDEXSYSTEMNUMSTR		"MAXINDEXSYSTEMNUM"
#define	MAXINDEXSYSTEMNUM		20
#define MAXMAINTENANCEPASS		PASSWORDSIZE
#define MAXBASEPASS			PASSWORDSIZE

#define	MAXERRORMSGSIZE			256

// maxima repeticao a ser indexada
#define MAXREPETITION	0xFFFF

// tipos de ACLs
#define	ACL_GROUP	0
#define	ACL_USER	1

// Tipos de comparacao para o metodo Compare das classes e estruturas
// Para FIELD
#define	CMPFIELDNAME			0
#define	CMPFIELDORIGNAME		1
#define	CMPFIELDDESCRIPTION		2
#define	CMPFIELDSTRUCT			3
#define	CMPFIELDID			4

// Para DATA
#define	CMPDATASORT			0
#define	CMPDATA				1
#define	CMPDATASIZE			2
#define	CMPREPETNUM			3

// Para SESSION
#define	CMPSESSIONPOINTER		0
#define	CMPSESSIONISLOGGED		1

// Para BASE
#define	CMPBASENAME			0
#define	CMPBASEPOINTER			1

// Para TUserBaseName
#define	CMPUSERBASENAME			0

// Para BASETIMERS
#define	CMPBASEADDR			0
#define	CMPTIMERID			1

// Para TNETINFO e TLicInfo
#define	CMPBASICELEM			10
#define	CMPSERIALNUM			11
#define	CMPCLIENTNAME			12
#define	CMPUSERNAME			13
#define	CMPTNIPOINTER			14

// chaves de criptografia
#define	LB1HEADKEY			"Chokito"
#define	LB3HEADKEY			"Prestigio"
#define	LBDEFKEY			"Lolo"
#define	CONTROLFILE_KEY			"Baton"

// Importacao/Exportacao
#define	SERIALNUMBERMAXSIZE	20

// Tratamento de GoWords
#define	GOWORDLISTNOTFOUND	0
#define	GOWORDLISTFOUND		1

// $$$ Tratamento de ACL's
#define	USERBASE		0
#define	GROUPBASE		1
#define	USERFIELD		2
#define	GROUPFIELD		3
#define	USERRECORD		4
#define	GROUPRECORD		5
#define	USERFORM		6
#define	GROUPFORM		7
#define	USERREPORT		8
#define	GROUPREPORT		9

// Inicializacao lib GREEN
#define	MAXFILES			30

// macros para caminhamento na lista de chaves da GREEN (metodos Get*Key)
#define	FIRSTKEY		1
#define	LASTKEY			2
#define	NEXTKEY			3
#define	PREVIOUSKEY		4
#define	DEFINEDKEY		5
#define	CURRKEY			6

#define	FIRSTOC			1
#define	NEXTOC			2
#define	PREVIOUSOC		3
#define	LASTOC			4
#define	CURROC			5

#define	NAVIGATIONBYINDEX	1
#define	NAVIGATIONBYKEY		2

// macros para selecao dos metodos Get*Expr da GREEN
#define	FIRSTEXPR		1
#define	LASTEXPR    		2
#define	NEXTEXPR    		3
#define	PREVIOUSEXPR		4
#define	RESULTEXPR		5

// macros para definicao dos tipos de batimentos entre LO's
#define	OL_AND			1
#define	OL_OR			2
#define	OL_XOR			3
#define	OL_NOT			4

// macros para a gravacao/leitura do arquivo de exportacao
// de formato de base
#define	BASE_HEADER_SESSION	"BASE_HEADER"
#define	NAME_KEY		"BASE_NAME"
#define	PWD_KEY			"BASE_PASSWORD"
#define	MPWD_KEY		"BASE_MAINT_PASSWORD"
#define	TYPE_KEY		"BASE_TYPE"
#define	SLOTNUM_KEY		"NUM_OF_SLOTS"
#define	COUNTNUM_KEY		"NUM_OF_COUNTERS"
#define	MAXKEYSIZE_KEY		"MAX_KEY_SIZE"
#define	ENCRYPT_KEY		"IS_ENCRYPT"
#define	UDB_KEY			"UDB_NAME"
#define	SERVER_KEY		"SERVER_NAME"
#define	NUMFIELDS_KEY		"NUM_OF_FIELDS"
#define	FIELD_KEY		"FIELD"
#define	FIELDNAME_KEY		"FIELD_NAME"
#define	FIELDDESC_KEY		"FIELD_DESCRIPTION"
#define	FIELDPWD_KEY		"FIELD_PASSWORD"
#define	FIELDTYPE_KEY		"FIELD_TYPE"
#define	FIELDSIZE_KEY		"FIELD_SIZE"
#define	FIELDID_KEY		"FIELD_ID"
#define	FIELDINDEX_KEY		"FIELD_INDEX"


// define o conjunto default de caracteres de normalizacao.
// (sao 256 caracteres)
#define	DEFAULTSTANDARDIZERARRAY	"01234567  \n\
12\r4567890\
1234567890\
1 !\"#$%&'(\
)*+,-./012\
3456789:;<\
=>?@ABCDEF\
GHIJKLMNOP\
QRSTUVWXYZ\
[\\]^_`ABCD\
EFGHIJKLMN\
OPQRSTUVWX\
YZ{|}~¦CUE\
AAAACEEEII\
IAAEXAOOOU\
UYOUAAAXAA\
IOUNNAOAAA\
AAAAAAAAAA\
AAAAAAAACA\
AAAAAAAACE\
EEAIIIAANO\
OOOIIIUUUU\
AIAAAAAOOU\
CEEEUIIIAA\
NOOOOAAAUU\
UU3AA"


// conjunto de caracteres para pre-normalizacao
#define	PRESTANDARDIZEARRAY	"01234567  \n\
12\r4567890\
1234567890\
1 !\"#$%&'(\
)*+,-./012\
3456789:;<\
=>?@ABCDEF\
GHIJKLMNOP\
QRSTUVWXYZ\
[\\]^_`abcd\
efghijklmn\
opqrstuvwx\
yz{|}~¦CUE\
AAAACEEEII\
IAAEXAOOOU\
UYOUAAAXAA\
IOUNNAOAAA\
AAAAAAAAAA\
AAAAAAAACA\
AAAAAAAACE\
EEAIIIAANO\
OOOIIIUUUU\
AIAaaaaOOU\
ceeeUiiiAA\
nooooAAAuu\
uu3AA"


// numero do slot privado
#define	PRIVATESLOT	0


// macros para RPC
#define	RPC_USERNAMESIZE = (USERNAMESIZE + 1)
#define	RPC_DESCRIPTIONSIZE = (DESCRIPTIONSIZE + 1)
#define	RPC_PASSWORDSIZE = (PASSWORDSIZE + 1)
#define	RPC_FULLNAMESIZE = (FULLNAMESIZE + 1)
#define	RPC_GROUPNAMESIZE = (GROUPNAMESIZE + 1)
#define	RPC_SERVERNAMESIZE = (SERVERNAMESIZE + 1)
#define	RPC_SERIALNUMBERSIZE = (SERIALNUMBERSIZE + 1)
#define	RPC_FIELDNAMESIZE = (FIELDNAMESIZE + 1)


// macros que definem os numeros (que servem de nomes) de regioes criticas
// para os objetos
#define	CRITSECT0		0
#define	CRITSECT1		1
#define	CRITSECT2		2
#define	CRITSECT3		3
#define	CRITSECT4		4
#define	CRITSECT5		5
#define	CRITSECT6		6
#define	CRITSECT7		7
#define	CRITSECT8		8
#define	CRITSECT9		9
#define	CRITSECT10		10
#define	CRITSECT11		11
#define	CRITSECT12		12
#define	CRITSECT13		13
#define	CRITSECT14		14
#define	CRITSECT15		15
#define	CRITSECT16		16
#define	CRITSECT17		17
#define	CRITSECT18		18
#define	CRITSECT19		19
#define	CRITSECT20		20


// para os stubs de rede:
#define	RPC_RETRY			1
#define	RPC_CANCEL			2
#define	RPC_OK				3
#define	RPC_ABORT			4
							
#define	LBSPROTO_TCPIP		5
#define	LBSPROTO_NETBEUI	6
#define	LBSPROTO_NAMEDPIPE	7
#define	LBS_CS_LOW_TIMEOUT	8
#define	LBS_CS_MED_TIMEOUT	9
#define	LBS_CS_HIGH_TIMEOUT	10
#define	LBS_CS_INF_TIMEOUT	11


// tratamento de repeticoes
#define	CURR_REPETITION		(-1)
#define	TAIL_REPETITION		(-2)

// bits (flags) para desligamento de verificacao de seguranca
#define	BS_LICENSE		0x00000001


// texto do arquivo de gowords
#define	GWTABSIZE	40

extern const char *_LBS_GoWordsMsg[];

//
//	Definicoes para uso automatico de regies criticas  
//
// todas as classes que usam regioes criticas como objetos automaticos e que 
// quiserem detectar possiveis deadlocks devem declarar esses objetos automaticos 
// com os nomes abaixo; aqui redefinimos cada uma para incluirem a linha e o arquivo em que estao sendo chamadas
// o x representa um ponteiro para dados do usuario(DWORD); o y a regiao a ser entrada 
#define	cCS0( x, y )					cCS0( (x), (y), __FILE__, __LINE__ )
#define	cCS1( x, y )					cCS1( (x), (y), __FILE__, __LINE__ )
#define	cCS2( x, y )					cCS2( (x), (y), __FILE__, __LINE__ )
#define	cCS3( x, y )					cCS3( (x), (y), __FILE__, __LINE__ )
#define	cCS4( x, y )					cCS4( (x), (y), __FILE__, __LINE__ )
#define	cCS5( x, y )					cCS5( (x), (y), __FILE__, __LINE__ )
#define	cCS6( x, y )					cCS6( (x), (y), __FILE__, __LINE__ )
#define	cCS7( x, y )					cCS7( (x), (y), __FILE__, __LINE__ )
#define	cCS8( x, y )					cCS8( (x), (y), __FILE__, __LINE__ )
#define	cCS9( x, y )					cCS9( (x), (y), __FILE__, __LINE__ )
#define	cCS10( x, y )					cCS10( (x), (y), __FILE__, __LINE__ )
#define	cCS11( x, y )					cCS11( (x), (y), __FILE__, __LINE__ )
#define	cCS12( x, y )					cCS12( (x), (y), __FILE__, __LINE__ )
#define	cCS13( x, y )					cCS13( (x), (y), __FILE__, __LINE__ )
#define	cCS14( x, y )					cCS14( (x), (y), __FILE__, __LINE__ )
#define	cCS15( x, y )					cCS15( (x), (y), __FILE__, __LINE__ )
#define	cCS16( x, y )					cCS16( (x), (y), __FILE__, __LINE__ )
#define	cCS17( x, y )					cCS17( (x), (y), __FILE__, __LINE__ )
#define	cCS18( x, y )					cCS18( (x), (y), __FILE__, __LINE__ )
#define	cCS19( x, y )					cCS19( (x), (y), __FILE__, __LINE__ )
#define	cCS20( x, y )					cCS20( (x), (y), __FILE__, __LINE__ )
#define	cCS21( x, y )					cCS21( (x), (y), __FILE__, __LINE__ )
#define	cCS22( x, y )					cCS22( (x), (y), __FILE__, __LINE__ )
#define	cCS23( x, y )					cCS23( (x), (y), __FILE__, __LINE__ )
#define	cCS24( x, y )					cCS24( (x), (y), __FILE__, __LINE__ )
#define	cCS25( x, y )					cCS25( (x), (y), __FILE__, __LINE__ )
#define	cCS26( x, y )					cCS26( (x), (y), __FILE__, __LINE__ )
#define	cCS27( x, y )					cCS27( (x), (y), __FILE__, __LINE__ )
#define	cCS28( x, y )					cCS28( (x), (y), __FILE__, __LINE__ )
#define	cCS29( x, y )					cCS29( (x), (y), __FILE__, __LINE__ )
#define	cCS30( x, y )					cCS30( (x), (y), __FILE__, __LINE__ )
#define	cCS31( x, y )					cCS31( (x), (y), __FILE__, __LINE__ )


#endif	// _LBSDEFS_H_


