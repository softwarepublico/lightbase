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
