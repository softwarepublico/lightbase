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

#ifndef	_CONTROLFILE_H_
#define _CONTROLFILE_H_

#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif
#ifndef	_RECFILCL_
#include	<recfilcl.h>
#endif


#include <regcrit.h>

class _LBSCLASS LBSC_ControlFile
{
private:
	TBasesFile	*pBasesInfo;
	CLBRegCrit	rcRegCrit;	// para proteger os atributos da classe de acesso concorrente 
	long		lSize;
	BOOL		Open( C_RecordFile &, BOOL bReadOnly );

public:
	LBSC_ControlFile();
	~LBSC_ControlFile();
	BOOL		Init();
	BOOL		Insert( TBasesFile tbNewBaseInfo );
	BOOL		Set( TBasesFile tbNewBaseInfo );
	const TBasesFile	*Get( long lPos );
	const TBasesFile	*Get( char *szBaseName );
	long		Size();
	BOOL		Del( char *szBaseName );
};

#endif