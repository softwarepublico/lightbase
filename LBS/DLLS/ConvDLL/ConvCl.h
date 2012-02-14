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

//	ConvCl.h


#ifndef	_CVB_DEFCLASS_H_
#include	<cvbclass.h>
#endif
#ifndef	_RECFILCL_
#include	<recfilcl.h>
#endif

class CString;
class C_FeedBackDlg;
#define	LASTERRORSIZE	255

class _CONVBASECLASS C_ConvBase
{
private:
	BOOL			bDefUdbConv;	// indica se DEFUDB ja' foi convertida
	BOOL			bLBWNamesConv;	// indica se LBWNames ja' foi convertida
	BOOL			bKeepOrig;
	char			szLastError[ LASTERRORSIZE ];

	int GetControlFileVersion( char *szFileName );
	int ConvertControlFile( CString &sFileName, C_FeedBackDlg &cProgDlg );
	BOOL GetBaseDir( char *szBaseDir );
	BOOL GetControlFileName( char *szFileName );
	int GetBaseVersion( const char *szBaseName );
	BOOL ConvertBase3to4( CString &sBaseName, C_FeedBackDlg &cProgDlg, C_RecordFile &cfBasesFile, CString &sFileName );
	int PutLongNamesInControlFile( C_FeedBackDlg &cProgDlg, C_RecordFile &cfBasesFile );
	int PutBaseDescription( C_RecordFile &cfBasesFile, char *szBaseName, char *szDescrip );
	BOOL VerifyCancel();
	BOOL FieldInArray( UINT *pArray, UINT uiFieldId, int iArraySize );
	BOOL MakeDir( char *szDirName );
	char * NextTok( char *szStr, char *szSeparator );

public:
	C_ConvBase();
	~C_ConvBase();
	BOOL VerifyConvBase( char *szBaseName );
	int ConvertBase( BOOL bKeepOrigPar, char *szBaseName );
	LPCTSTR LastErrorDesc();
};

