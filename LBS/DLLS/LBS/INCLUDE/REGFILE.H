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

#ifndef	_REG_FILE_
#define	_REG_FILE_

#include	<FileCl.h>

#define	RF_NOSEEK	-1
#define	RF_NOWRITE	-2
#define	RF_NOREAD	-3
#define	RF_NOAPPEND	-4
#define RF_NOSEARCH	-5
#define RF_NOMEMORY	-6
#define	RF_OK		0

class C_RegFile : public C_File {
	private:
		size_t	stRegLen;
		long	lActualPos;
	public:
		C_RegFile( const char *szNameFile, size_t stRegLen );

		long	ActualPos( void );
		long	FileSize( void );

		size_t Write( void *pvBuffer );
		size_t Read( void *pvBuffer );
		size_t Append( void *pvBuffer );
		size_t RegLen( void );

		int Seek( long lPos );
		int Search( void *pvBuffer, char (*fCmp) ( void *a, void *b ) );
};

#endif
