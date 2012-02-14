/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o 
título "LICENCA.txt", junto com este programa, se não, escreva para a Fundação do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

/********************************************************
	Classe C_Person
	Metodos da DLL LBSTART
	Programador:
		Marcos Sebastian Alsina
		27/06/1996
********************************************************/


#include	<string.h>
#include	<stdio.h>
	
#include	<crypt.h>

#include	"personcl.h"




// Estrutura T_PERS global. Ela fara parte do codigo executavel e
// sera sobreposta pelo PERSON quando da instalacao.

T_PERS 	str_pers = "\
General failure while open files\0\0\0\0\0\0\0\0\0\
datainst\0\
nome\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
empresa\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
serie\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\
tp\0";


// Variaveis arrancadas da classe para estaticas
static BOOL	iIsDecrypt = FALSE;
static long	lPosicao = 0L;
static int	DESLOCTIPO = 0;
static int	DESLOCDATA = 0;
static int	DESLOCNUMTTY = 0;
static int	DESLOCSERIE = 0;

		
	
// Deslocamentos dos dados em relacao ao Numero de Serie


#define DATA(xy)	((xy) + O_SERIE + DESLOCDATA)
#define NUMTTY(xy)	((xy) + O_SERIE + DESLOCNUMTTY)
#define PARTSERIAL(xy)	((xy) + O_SERIE + DESLOCSERIE)




/***
	Seta o tipo da copia. Pode ser:
		cl - Copia cliente
		sr - Copia de servidor
		mn - Copia monousuario
		rt - Copia Runtime
		rd - Servidor preparado para modo rede
	Importante:
		O tipo deve ser com letras minúsculas
	Retorna:
		PE_OK ou
		PE_ERROR
***/
int
SetType( char *szFileName, char *szType )
{
	FILE	*fp;

	if( !ValidType( szType ) ){
		// O tipo passado inexiste
		return( PE_ERROR );
	}
	/* procura a estrutura str_pers
	 */
	if( (fp = localiza( szFileName, str_pers )) == NULL ) {
		return( PE_ERROR );
	}
	if( fseek( fp, lPosicao, 0 ) == -1 ) {
		fclose( fp );
		return( PE_ERROR );
	}
	// Nao decriptografo pois a informacao do tipo nao esta em
	// area criptografada.
	strcpy( TIPO( str_pers ), szType );
	if( fwrite( (char *) str_pers, sizeof str_pers, 1, fp ) != 1 ) {
		fclose( fp );
		return( PE_ERROR );
	}
	fclose( fp );
	return( PE_OK );
}


/***
	Personaliza um arquivo dado.
	Parametros:
		FileName: Nome do arquivo a personalizar
		Name: Nome do usuario
		Company: Nome da compania
		Serial: Serial Number
		ActKey: Chave de ativacao
	Inportante:
		· O número serial deve estar na forma 11.222222.3333.444444
		  com pontos separando os campos. Ele deve sempre ter o
		  strlen() <= 32.
		. O campo 1 eh de tamanho fixo. Os demais sao de tamanho variavel
		  ate o limite maximo de 32 caracteres.
		· 11 = tipo da cópia
		· 222222 = Data. Se começar com número > 0 é data absoluta.
		  Se começar (ATENCAO) com 0 é time bomb e se começar com letra
		  indica cópia não demo.
		· 3333 = Número de terminais
		· 444444 = Um número serial
	Retorna:
		PE_DATA: Chave com data absoluta ja expirou
		PE_TYPE: Tipo nao bate
		PE_ACTKEY: Chave de ativacao nao bate
		PE_SERIAL: Numero de serie com formacao ou tamanho errado
		PE_PARAM: Parametros invalidos
		PE_TIMEBOMB: Tentando personalizar copia time-bomb de novo. Deve Re-instalar
		PE_LOCALIZA: Nao achou marca no arquivo
		PE_POSERROR: Falhou no seek
		PE_WRITEERROR: Falhou ao tentar escrever no arquivo
		PE_OK: Ok
***/
int
Personalize( char *szFileName, char *szName, char *szCompany, char*szSerial, char *szActKey )
{
	char	data_hoje[MAXDATAINST+1];
	time_t	time_aux;
	FILE	*fp;
	int	check = 0;
	char	data[MAXDATA+1];
	char	szBufAux[MAXDATA+1];
	struct tm	*dma;
	long		tloc;
	


	if( szFileName == NULL || szName == NULL || szCompany == NULL || szSerial == NULL || szActKey == NULL ){
		return( PE_PARAM );
	}
	if( strlen( szSerial ) > MAXSIZESERIAL ){
		return( PE_SERIAL );
	}
	if( !ValidKey( szSerial, szActKey ) ){
		return( PE_ACTKEY );
	}
	// Calculo os deslocamentos variaveis em relacao ao serial passado
	if( CalculaDeslocamentos( szSerial ) != PE_OK ){
		return( PE_SERIAL );
	}

	// Verifico se eh uma data absoluta e se ja expirou.
	if( isdigit( szSerial[DESLOCDATA] ) && szSerial[DESLOCDATA]>'0' ){
		/* Eh uma copia demo com data absoluta. VAMOS VERIFICAR!!! */
		time( &tloc );
		dma = localtime( &tloc );
		sprintf( szBufAux, "%04.2d%02.2d",
			dma->tm_year + 1900,
			dma->tm_mon + 1
		);
		// MAXDATA deve ser 6 ; yyyymm. Assim mesmo nos protegemos procurando o '.'
		istrncpychar( data, szSerial+DESLOCDATA, MAXDATA, '.' );
		if( strncmp( szBufAux, data, MAXDATA ) > 0 ) {
			return( PE_DATA );
		}
	}

	/* procura a estrutura str_pers
	 */
	if( (fp = localiza( szFileName, str_pers )) == NULL ) {
		return( PE_LOCALIZA );
	}

	// Verifico TIPO da copia antes de decriptografar pois esta em
	// area nao criptografada.
	if( strncmp( TIPO( str_pers ), szSerial+DESLOCTIPO, MAXTIPO ) != 0 ){
		return( PE_TYPE );
	}

	if( PERS( str_pers ) == PE_PERS ) {
		/* Jah passou o "person" por aqui antes.
		 * decriptografo a estrutura, para nao perder as
		 * demais informacoes nela contidas: data_instalacao, num_serie, etc.
		 */
		Decriptografa( DATAINST(str_pers), CHECKSUM( str_pers ) );
		iIsDecrypt = TRUE;
	}
	
	if( szSerial[DESLOCDATA] == '0' ){
		// Eh um numero de serie time-bomb
		if( PERS( str_pers ) == PE_PERS ){
			/* Tentando fazer person de time bomb sobre uma copia
			 * previamente personalizada. Nao deixo!!!! Que o filho
			 * da mae re-instale o produto.
			 */
			fclose( fp );
			return( PE_TIMEBOMB );
		}
	}


	// Posiciono no inicio da marca para gravar estrutura de
	// personalizacao
	if( fseek( fp, lPosicao, 0 ) == -1 ) {
		fclose( fp );
		return( PE_POSERROR );
	}

	// Monto a estrutura de personalizacao
	time_aux = time( &time_aux );
	strftime( data_hoje, sizeof( data_hoje ), "%Y%m%d", localtime( &time_aux ) );
	istrncpy( DATAINST( str_pers ), data_hoje, MAXDATAINST );
	istrncpy( NOME( str_pers ), szName, MAXNOME );
	istrncpy( NAMECOMPANY( str_pers ), szCompany, MAXCOMPANY );
	istrncpy( SERIE( str_pers ), szSerial, MAXSIZESERIAL );

	// O tipo da copia ja vem pre-gravado e nao preciso colocar.

	/* indica que o produto estah personalizado */
	PERS( str_pers ) = PE_PERS;

	check = Criptografa( DATAINST( str_pers ), CHECKSUM( str_pers ) );
	CHECKSUM( str_pers )[ 0 ] = ( check & 0xFF00 ) >> 8;
	CHECKSUM( str_pers )[ 1 ] = ( check & 0x00FF );

	if( fwrite( (char *) str_pers, sizeof str_pers, 1, fp ) != 1 ) {
		fclose( fp );
		return( PE_WRITEERROR );
	}
	fclose( fp );
	return( PE_OK );
}




/***
	Verifica se a chave de ativacao bate com o numero de serie dado
	Retorna:
		TRUE se bateu OK
		FALSE se chave e num. serie nao batem.
***/
BOOL
ValidKey( char *szSerial, char *szActKey )
{
	char	cripserie[MAXSIZESERIAL+1];
	int	size_serie;
	int	size_key;

	size_serie = strlen( szSerial );
	size_key = strlen( szActKey );
	if( size_serie > MAXSIZESERIAL || size_key > size_serie ) {
		// Se tamanho do num. serie nao OK -> ERRO
		return( FALSE );
	}
	if( size_key < 3 ){
		// Se tamanho da chave menor que 3 nao pode
		return( FALSE );
	}
	
	strcpy( cripserie, szSerial );
	crypt_key( cripserie, cripserie + size_serie );
	// Pegamos apenas os ultimos caracteres da chave
	// para fins de comparacao
	if( strcmp( szActKey, cripserie + size_serie - size_key ) == 0 ){
		/* a chave de ativacao fornecida bate com a do numero
		 * de serie fornecido.
		 */
		return( TRUE );
	}
	return( FALSE );
}



static FILE *
localiza( char *szArq, T_PERS tpPers )
{
	char	buf[MAXTAG+1];
	FILE	*fp;
	int	iSizeTag;
	int	c;

	strcpy( buf, TAG( tpPers ) );
	iSizeTag = strlen( buf );
	if( ( fp = fopen( szArq, "r+b" ) ) == NULL ) {
		return( NULL );
	}

	/* Vamos procurar a Marca da estrutura (TAG).
	 */
	while( 1 ) {
		while( ( c = getc( fp ) ) != buf[ 0 ] && c != EOF )
			;
		if( c != buf[ 0 ] ) {
			// EOF
			return( NULL );
		}
		ungetc( c, fp );
		// Guarda a posicao para uso posterior.
		lPosicao = ftell( fp );
		if( fread( (char *) tpPers, sizeof (T_PERS), 1, fp ) != 1 ) {
			return( NULL );
		}

		if( strncmp( buf, TAG( tpPers ), iSizeTag ) == 0 ) {
			break;
		}

		/* um falso inicio de marca.
		 * Continuemos a busca ...
		 */
		if( fseek( fp, lPosicao + 1, 0 ) == -1 ) {
			return NULL;
		}
	}
	return( fp );
}





/***
	Retorna se a estrutura de personalizacao ja foi
	decriptografada ou nao.
	Retorno: TRUE ou FALSE
***/
static int
IsUncrypt(){
	return( iIsDecrypt );
}


/***
	Retorna a data de expiracao do produto na forma:
	 - AAAAMM se for data absoluta ou
	 - DDDDDD indicando o numero de dias a partir da data de
	   instalação em que a cópia eh válida
	 - Qualquer coisa diferente de números indica cópia não demo.
***/
char*
GetData()
{
	static char	szData[MAXDATA+1];

	if( !iIsDecrypt ){
		return( NULL );
	}
	if( CalculaDeslocamentos( SERIE( str_pers ) ) != PE_OK ){
		return( NULL ); // algum pau no numero de serie
	}
	istrncpychar( szData, DATA(str_pers), MAXDATA, '.' );
	return( szData );
}



/***
	Retorna o numero maximo de terminais permitidos ou PE_ERROR
	no caso de erros.
***/
long
GetUsers()
{
	static char	szTTY[MAXNUMTTY+1];

	if( !iIsDecrypt ){
		return( PE_ERROR );
	}
	if( CalculaDeslocamentos( SERIE( str_pers ) ) != PE_OK ){
		return( PE_ERROR ); // algum pau no numero de serie
	}
	istrncpychar( szTTY, NUMTTY(str_pers), MAXNUMTTY, '.' );
	return( atol(szTTY) );
}



/***
	Retorna o tipo de copia do produto.
	Pode ser:
		cl - Copia cliente
		sr - Copia de servidor
		mn - Copia monousuario
		rt - Copia Runtime
		rd - Servidor preparado para modo rede
***/
char*
GetType()
{
	// Nao preciso de variavel estatica auxiliar pois na
	// estrutura ja tem o \0. Nao pegamos do numero de serie
	// Tambem nao verificamos se esta criptografada ou nao
	// pois essa informacao esta na parte nao criptografada.
	return( TIPO( str_pers ) );
}





/***
	Retorna o tipo de copia do produto.
	Pode ser:
		PE_CLIENT - Copia cliente
		PE_SERVER - Copia de servidor
		PE_MONO - Copia monousuario
		PE_RUNTIME - Copia Runtime
		PE_REDE - Servidor preparado para modo rede
		PE_UNKNOWN - Tipo desconhecido
***/
int
GetTypeInt()
{
	// Nao preciso de variavel estatica auxiliar pois na
	// estrutura ja tem o \0. Nao pegamos do numero de serie
	// Tambem nao verificamos se esta criptografada ou nao
	// pois essa informacao esta na parte nao criptografada.
	char	*szTipo = TIPO( str_pers );

	if( stricmp( szTipo, PE_STRREDE ) == 0 ){
		return PE_REDE;
	}
	if( stricmp( szTipo, PE_STRSERV ) == 0 ){
		return PE_SERVER;
	}
	if( stricmp( szTipo, PE_STRMONO ) == 0 ){
		return PE_MONO;
	}
	if( stricmp( szTipo, PE_STRCLNT ) == 0 ){
		return PE_CLIENT;
	}
	if( stricmp( szTipo, PE_STRRUNT ) == 0 ){
		return PE_RUNTIME;
	}
	return PE_UNKNOWN;
}



/***
	Retorna o nome do cliente que instalou o produto.
***/
char*
GetName()
{
	// Nao preciso de variavel estatica auxiliar pois na
	// estrutura ja tem o \0. Nao preciso calcular os des-
	// locamentos aqui.
	if( !iIsDecrypt ){
		return( NULL );
	}
	return( NOME( str_pers ) );
}




/***
	Retorna o nome do companhia que instalou o produto.
***/
char*
GetCompany()
{
	// Nao preciso de variavel estatica auxiliar pois na
	// estrutura ja tem o \0. Nao preciso calcular os des-
	// locamentos aqui.
	if( !iIsDecrypt ){
		return( NULL );
	}
	return( NAMECOMPANY( str_pers ) );
}




/***
	Retorna a data de instalacao do produto.
***/
char*
GetDataInst()
{
	// Nao preciso de variavel estatica auxiliar pois na
	// estrutura ja tem o \0. Nao preciso calcular os des-
	// locamentos aqui.
	if( !iIsDecrypt ){
		return( NULL );
	}
	return( DATAINST( str_pers ) );
}



/***
	Retorna o numero serial do produto sem as partes relativas
	a data, numero de terminais e tipo da copia.
***/
char*
GetSerialPart()
{
	static char	szSerialPart[MAXSERIALPART+1];

	if( !iIsDecrypt ){
		return( NULL );
	}
	if( CalculaDeslocamentos( SERIE( str_pers ) ) != PE_OK ){
		return( NULL ); // algum pau no numero de serie
	}
	istrncpychar( szSerialPart, PARTSERIAL( str_pers ), MAXSERIALPART, '.' );
	return( szSerialPart );
}



/***
	Retorna o numero serial do produto COMPLETO
***/
char*
GetSerialNumber()
{
	// Aqui pegamos da estrutura que ja tem o \0
	if( !iIsDecrypt ){
		return( NULL );
	}
	return( SERIE( str_pers ) );
}



/***
	Verifica se a copia pode executar normalmente.
	Parametros:
		nenhum
	Retorno:
		PE_INSTALA - Copia nao personalizada
		PE_DATA - Copia Out of date (estouro de data)
		PE_OK - Pode executar numa boa.
***/
int
CheckForRun()
{
	int	iIsTimeBomb = FALSE;
	int	check = 0;
	int	chk_check;
	char	data[MAXDATA+1];
	char	szBufAux[MAXDATA+1];
	struct tm	*dma;
	struct tm	data_aux;
	time_t		t1;
	time_t		t2;
	int		num_dias;
	long		tloc;

	if( !iIsDecrypt ){
		check = Decriptografa( DATAINST(str_pers), CHECKSUM( str_pers ) );
		iIsDecrypt = TRUE;
		chk_check = ((CHECKSUM( str_pers )[0]&0xFF)<<8) | (CHECKSUM( str_pers )[1] & 0xFF);
		chk_check &= 0xFFFF;
		if( check != chk_check ) {
			return( PE_INSTALA );
		}
	}
	if( PERS( str_pers ) != PE_PERS ){
		return( PE_INSTALA ); // Copia nao personalizada
	}

	// Calcula os deslocamentos para DATA, NUMTTY, SERIE, ETC.
	if( CalculaDeslocamentos( SERIE( str_pers ) ) != PE_OK ){
		return( PE_INSTALA ); // algum pau no numero de serie
	}

	/* Verificando Time Bomb */
	if( DATA( str_pers )[0] == '0' ){
		iIsTimeBomb = TRUE;
	}

	if( iIsTimeBomb ){	/* Tem time bomb */
		t1 = time( &t1 ); /* Dia de hoje em segundos */
		memset( &data_aux, 0, sizeof(data_aux) );
		// Pego o dia da instalacao do produto e somo o numero de dias
		// do time bomb. Tudo em segundos.
		data_aux.tm_year = (1000*(DATAINST(str_pers)[0]-'0')) +
				   (100*(DATAINST(str_pers)[1]-'0')) +
				   (10*(DATAINST(str_pers)[2]-'0')) +
				   DATAINST(str_pers)[3] - '0' - 1900;
		data_aux.tm_mon = (10* (DATAINST(str_pers)[4]-'0') ) + DATAINST(str_pers)[5] - '0' - 1 ;
		data_aux.tm_mday = (10* (DATAINST(str_pers)[6]-'0') ) + DATAINST(str_pers)[7] - '0';
		t2 = mktime( &data_aux );	/* Dia da instalacao do produto */
		if( t1 < t2 ) {
			/* O sacana mudou a data voltou a data para tras
			 * para rodar o aplicativo.
			 * Pau nele.
			 */
			return( PE_DATA );
		}
		/* o dia de instalacao nao guarda horas/minutos e portanto
		 * eh como se tivessemos instalado a meia noite do dia.
		 * por isso, dah um dia de graca. Pegamos agora o
		 * numero de dias do time bomb.
		 */
		istrncpychar( data, DATA(str_pers), MAXDATA, '.' );
		t2 += ( atol(data) + 1 ) * 3600 * 24;
		num_dias = CmpDatas( t2, t1 );
		if( num_dias < 0 ) {
			return( PE_DATA );
		}
		return( PE_OK );
	}
	if( isdigit( DATA(str_pers)[0] ) && DATA(str_pers)[0]>'0' ){
		/* Eh uma copia demo com data absoluta. VAMOS VERIFICAR!!! */
		time( &tloc );
		dma = localtime( &tloc );
		sprintf( szBufAux, "%04.2d%02.2d",
			dma->tm_year + 1900,
			dma->tm_mon + 1
		);
		// MAXDATA deve ser 6 ; yyyymm. Assim mesmo nos protegemos procurando o '.'
		istrncpychar( data, DATA(str_pers), MAXDATA, '.' );
		if( strncmp( szBufAux, data, MAXDATA ) > 0 ) {
			return( PE_DATA );
		}
		return( PE_OK );
	}
	// Qualquer outra coisa no campo data indica uma copia
	// Full (nao demo). Logo, retornamos PE_OK para a galera.
	return( PE_OK );
}




/***
	Verifica se um tipo dado eh valido
	Parametros:
		- szType: Pode ser
		cl - Copia cliente
		sr - Copia de servidor
		mn - Copia monousuario
		rt - Copia Runtime
		rd - Servidor preparado para modo rede
	Retorno:
		TRUE or FALSE
***/
static BOOL
ValidType( char *szType )
{
#define	MAXVALIDTYPES	5
	int	i;

	char	ValidTypes[MAXVALIDTYPES][MAXTIPO+1] = {
		PE_STRREDE,
		PE_STRSERV,
		PE_STRMONO,
		PE_STRCLNT,
		PE_STRRUNT,
	};

	for( i=0; i<MAXVALIDTYPES; i++ ){
		if( strcmp( szType, ValidTypes[i] ) == 0 ){
			return( TRUE );
		}
	}
	return( FALSE );
}



/*
 * Retorna o numero de dias existentes entre duas datas. A primeira data
 * eh a data de expiracao e a segunda data eh a data de hoje.
 */
static int
CmpDatas( time_t data, time_t hoje )
{
	if( hoje > data ){
		return( -1 );
	}
	return( (data - hoje) / ( 3600 * 24 ) );
}




 /***
	Seta os valores dos deslocamentos necessarios para se
	atingir um determinado campo dentro do numero de serie
	passado como parametro.
	Parametros:
		szSerie: Numero de serie a ser analizado
	Retorno:
		PE_OK ou PE_ERROR
***/
static int
CalculaDeslocamentos( char *szSerie )
{
	char	*szAux = NULL;

	DESLOCTIPO = 0;
	if( (szAux = strchr( szSerie, '.' )) == NULL ){
		return( PE_ERROR );
	}
	DESLOCDATA = szAux + 1 - szSerie;
	if( (szAux = strchr( szAux+1, '.' )) == NULL ){
		return( PE_ERROR );
	}
	DESLOCNUMTTY = szAux + 1 - szSerie;
	if( (szAux = strchr( szAux + 1, '.' )) == NULL ){
		return( PE_ERROR );
	}
	DESLOCSERIE = szAux + 1 - szSerie;
	return( PE_OK );
}



/*
 * rotina:
 *    istrncpychar
 * objetivo:
 *    copia n caracteres de orig em dest colocando um 
 *    NULL no fim de dest. A copia eh feita ate encontrar
 *    um '\0', tam ser atingido ou ainda se o separador 'separ'
 *    for encontrado antes.
 * parametros de entrada:
 *    dest -> apontador para a cadeia destino;
 *    orig -> apontador para a cadeia de origem;
 *    tam -> numero de caracteres a ser copiado;
 *    separ -> um caractere separador indicando fim de string
 * algoritmo: obvio.
 */

static char*
istrncpychar( register char *dest, register char *orig, register int tam, register int separ )
{
	char	*aux = dest;

	while( *orig != '\0' && *orig != '.' && tam-- > 0 ){
		*dest++ = *orig++;
	}
	*dest = '\0';
	return( aux );
}





/***
	Funcao para o instalador
***/
_LBSFUNC BOOL WINAPI
CheckKey(LPDLLCALLPARAMS parms)
{
   // Chega aqui serial@chave

   char *key;

   key = strchr( parms->lpszParam, '@' );
   if( !key )
   {
       MessageBox( NULL, "Erro grave na instalação.", "Erro!", MB_OK );
       return TRUE;               // Doideira, nao veio a virgula
   }

   *key = 0;
   ++key;   // key agora aponta para o inicio da chave de ativacao.

   if( ValidKey( parms->lpszParam, key ) )
       return FALSE;
    
   return TRUE;
}




/***
	Funcao para o instalador
***/
_LBSFUNC BOOL WINAPI
ExecPers(LPDLLCALLPARAMS parms)
{

   // Chega aqui arquivo@nome@empresa@serial@chave

   BOOL bResult;
   char file[256];

   char *path, *arquivo, *nome, *empresa, *serial, *key;

   //MessageBox( NULL, parms->lpszParam, "Erro!", MB_OK );
   path    = parms->lpszParam;
   arquivo = strchr( path, '@' );          *arquivo = 0;    arquivo++;
   nome    = strchr( arquivo, '@' );       *nome    = 0;    nome++;
   empresa = strchr( nome, '@' );          *empresa = 0;    empresa++;
   serial  = strchr( empresa, '@' );       *serial  = 0;    serial++;
   key     = strchr( serial, '@' );        *key     = 0;    key++;

   strcpy( file, path );
   strcat( file, "\\" );
   strcat( file, arquivo );
   bResult = Personalize( file, nome, empresa, serial, key );
   
   if( !bResult ) return FALSE;

   sprintf( file, "Erro na personalização: %d", bResult );
   MessageBox( NULL, file, "Erro!", MB_OK );
   return TRUE;
}




/***
	Retorna o numero maximo de terminais permitidos a partir de um
	Serial Number dado ou PE_ERROR no caso de erros.
***/
long
GetUsersFromSN( char *szSerialAux )
{
	static char	szTTY[MAXNUMTTY+1];

	if( CalculaDeslocamentos( szSerialAux ) != PE_OK ){
		return( PE_ERROR ); // algum pau no numero de serie
	}
	istrncpychar( szTTY, szSerialAux+DESLOCNUMTTY, MAXNUMTTY, '.' );
	CalculaDeslocamentos( SERIE( str_pers ) );
	return( atol(szTTY) );
}



/***
	Retorna o path dos .INIs do  LBW ou LBS (LBW.INI ou LBS.INI)
	Parametro:
		szIni = Nome do .INI desejado. Pode assumir dois valores
				distintos: LBW ou LBS.
	Algoritmo:
***/
const char*
GetAppIniPath( const char *szIni )
{
	static int	iCalled = 0;
	static char	szLBWIniFileName[512];
	static char	szLBSIniFileName[512];
	HMODULE		hModule;
	char		*pAux;

	if( iCalled == 0 ){
		szLBWIniFileName[0] = '\0';
		szLBSIniFileName[0] = '\0';
		hModule = GetModuleHandle( "lbstart.dll" );
		if( !hModule ){
			return NULL;
		} else {
			GetModuleFileName( hModule, szLBWIniFileName, 512 );
			GetModuleFileName( hModule, szLBSIniFileName, 512 );
			pAux = strrchr( szLBWIniFileName, '\\' );
			if( pAux ){
				*(pAux+1) = '\0';
			}
			strcat( szLBWIniFileName, "lbw.ini" );
			pAux = strrchr( szLBSIniFileName, '\\' );
			if( pAux ){
				*(pAux+1) = '\0';
			}
			strcat( szLBSIniFileName, "lbs.ini" );
		}
		iCalled = 1;
	}

	if( stricmp( szIni, "lbw" ) == 0 ){
		return szLBWIniFileName;
	} else {
		return szLBSIniFileName;
	}
	return( NULL );
}

