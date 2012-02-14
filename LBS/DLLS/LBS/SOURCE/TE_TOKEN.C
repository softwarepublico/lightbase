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

//#undef  INC_OLE2
//#define INC_OLE1

#include <windows.h>
#include <te_token.h>
#include <stdlib.h>
#include <io.h>

static char *pcCfmtSign = "~`!@#$%^&*()-+|=-TeCfMt";

//                                   11111111 112222222 22 2 3    3   3  
//                         012345678901234567 890123456 78 9 0    1   2
static char *separators = "~`#%^&*()-+={}[]:\";'<>?,./\\ \r\n\xff\x9\xb6";
//                          indicadores de fim-----------+

//_declspec (dllexport) int WINAPI GetToken(const void *pvBuffer,int iBufSize,char **pszRetorno,int *piStatus, HWND hWnd)

//int WINAPI _export GetToken(const void *pvBuffer,int iBufSize,char **pszRetorno,int *piStatus)
int
GetToken(const void *pvBuffer,int iBufSize,char *pszRetorno,int *piStatus)
{
	static char *tmp_pvBuffer,*pvInitBuffer;
	static int  iInitBufSize;
	char *pvInitWord;
	BOOL ponto;

	if (pvBuffer) {          // Se chamando pela primeira vez, inicia o processo
		tmp_pvBuffer=pvInitBuffer=(char *)pvBuffer;
        	iInitBufSize=iBufSize;
		pvInitWord = NULL;
   	}

	// ADRIANO:
	pszRetorno[ 0 ] = '\0';
//	*pszRetorno = NULL;

	// Analiza separadores.
	ponto = FALSE;
	while( strchr( separators, (BYTE)*tmp_pvBuffer ) ) {
		switch( (BYTE)*tmp_pvBuffer )
		{
		case '~':	// Possibilidade de fim de arquivo
			if( !strncmp( tmp_pvBuffer, pcCfmtSign, strlen( pcCfmtSign ) ) )
			{
				*piStatus=TER_TOKENDBUFFER;
				return(TER_TOKOK);
			}
			break;

		case 0xb6:
	      		tmp_pvBuffer++;
	      		*piStatus=TER_TOKPAR;
	      		return(TER_TOKOK);

		case ' ':
			if( ponto )
			{
				*piStatus=TER_TOKPHRASE;
		      		tmp_pvBuffer++;
				return(TER_TOKOK);
			}
			break;

		case '.':
      case '!':
      case '?':
			ponto = TRUE;
			break;

		default:
         if( ponto )
            ponto = FALSE;
			break;
		}
		++tmp_pvBuffer;
		if( (tmp_pvBuffer - pvInitBuffer) > iInitBufSize )
		{
			*piStatus = TER_TOKENDBUFFER;
			return (TER_TOKOK );     // bom para lb dos, que nÃo tem terminador
		}
	}

   if( ponto )
	{
		*piStatus=TER_TOKPHRASE;
		return(TER_TOKOK);
	}

	// separar uma token.

	pvInitWord = tmp_pvBuffer;
	while( TRUE ) 
	{
		// juntar a token.
		char *ptr = strchr( separators, *tmp_pvBuffer );
		if( ptr ) // Se for separador
		{
			// Se for ponto tem que tomar cuidado.
			if ( *tmp_pvBuffer == '.' )
			{
				ptr = strchr( separators, *(tmp_pvBuffer+1) );
				if( ptr )
				{
					if( ptr - separators >27 )  // é fim de parágrafo ou frase.
						break;
				}
				// Ver se é digito
				if( isdigit( *(tmp_pvBuffer+1) ) )
				{
					++tmp_pvBuffer;
					continue;
				}
				else
					break;
			}
			else
				break;
		}
		else
			++tmp_pvBuffer;

		if( (tmp_pvBuffer - pvInitBuffer) > iInitBufSize )
			break;
	}

	if( pvInitWord == tmp_pvBuffer )  // situação esdrúxula
	{
		*piStatus = TER_TOKENDBUFFER;
		return(TER_TOKERROR);
	}

	*piStatus=TER_TOKWORD;

	// ADRIANO
/*	*pszRetorno=(char*)malloc(128);  // Alocar bastante.
	if (*pszRetorno==NULL) {
		*piStatus = TER_TOKENDBUFFER;
		return(TER_TOKERROR);
	}
*/
	// ADRIANO
//	memset( *pszRetorno, 0, 128 );
	memcpy( pszRetorno, pvInitWord, tmp_pvBuffer - pvInitWord );
	memset( pszRetorno + (tmp_pvBuffer - pvInitWord), 0, 1 );

	return(TER_TOKOK);
}

//int WINAPI _export GetTokenFile(int iFile,char **pszRetorno,int *piStatus)
int
GetTokenFile(int iFile,char *pszRetorno,int *piStatus)
{
   static unsigned char *pvBuffer;
   static int iTmpFile=-1;
   int iRet;
   static long iFileLength;

   if(iTmpFile!=iFile){
      iTmpFile=iFile;
      if(iFile!=-1){
         iFileLength=filelength(iFile);
{
char mmm[50];
wsprintf(mmm, "Numero de bytes %ld", iFileLength );
MessageBox(NULL, mmm,mmm,MB_OK);
}
         free(pvBuffer);
         lseek(iFile,0L,SEEK_SET);
         pvBuffer=(unsigned char *)malloc(iFileLength);
         if(pvBuffer==NULL||
            read(iFile,pvBuffer,iFileLength)!=iFileLength){
            pszRetorno=NULL;
            return(TER_TOKERROR);
         }
      } else {
         iTmpFile=-1;
         free(pvBuffer);
      }
   }

   iRet=GetToken((const void *)pvBuffer,iFileLength,pszRetorno,piStatus);

   if(iRet==TER_TOKERROR||*piStatus==TER_TOKENDBUFFER){
      iTmpFile=-1;
      free(pvBuffer);
   }

   return(iRet);

}
