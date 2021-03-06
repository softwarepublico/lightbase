/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo � parte do programa LightBase - Banco de Dados Textual Documental

O LightBase � um software livre; voc� pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o do Software 
Livre (FSF); na vers�o 2 da Licen�a.

Este programa � distribu�do na esperan�a que possa ser �til, mas SEM NENHUMA 
GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO ou APLICA��O 
EM PARTICULAR. Veja a Licen�a P�blica Geral GNU para maiores detalhes.

Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU versao 2, sob o t�tulo
"LICENCA.txt", junto com este programa, se n�o, escreva para a Funda��o do Software 
Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#ifndef	_MMCOMM_H_
#define	_MMCOMM_H_
/*
#include	<buffercl.h>
#include	<explist.h>
#include	<serlst.h>
#include	<svbasel.h>
#include	<allbasel.h>
#include	<permlist.h>

#define	SERVER_SUFFIX		"S"
#define	CLIENT_SUFFIX		"C"
#define	APPLICATION_SUFFIX	"A"
#define	MMSERVERCLASSNAME	"MMSRVCLASSNAME"
#define	MMSERVERWINDOWNAME	"MMSRVWINDOWNAME"

#define	NO_RETURN		1	// indica que nao ha' retorno do
					// servidor para o cliente. Observe
	// que o numero 1 nao indica que o servidor esta' criando um arquivo
	// "falso" ou qualquer outra coisa que "nao retorne valor para cliente".
	// O que faz com o que cliente nao receba o retorno do servidor e'
	// o proprio cliente, quando passa NULL no terceiro parametro
	// da funcao ExecuteOnServer. O NO_RETURN e' apenas uma "simbologia".
	// O que importa e' que o valor de NO_RETURN nao seja zero, pois esse
	// numero representa, para o cliente, um erro no tratamento do metodo
        // pelo servidor.



extern int _iNumFile;

HANDLE	CreateFile( long, int *, char * );
HANDLE	OpenFile( int, char * );
BOOL	DataToView( int, char *, void *, int );
BOOL	ViewToData( int , char *, void *, int );
int		GetFileSize( int, char * );
void	FileName( int, char *, char * );

char	*MakeStrFromBuffer( C_Buffer& );
void	*MakeVoidFromBuffer( C_Buffer& );
int		MakeBufferFromList( LBSC_ExportBaseList *, C_Buffer ** );
int		MakeBufferFromList( LBSC_SerialNumberList *, C_Buffer ** );
int		MakeBufferFromList( LBSC_AllBasesList *, C_Buffer ** );
int		MakeBufferFromList( LBSC_ServerBasesList *, C_Buffer ** );
int		MakeBufferFromList( LBSC_PermList *, C_Buffer ** );
int		MakeExportBaseList( LBSC_ExportBaseList *, C_Buffer& );
int		MakeSerialNumberList( LBSC_SerialNumberList *, C_Buffer& );
TField	*MakeFieldArray( C_Buffer& );


*/

#endif	// _MMCOMM_H_


