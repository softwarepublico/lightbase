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

#ifndef _OLDLB1_
#define _OLDLB1_

#ifndef	_OLDRECFILCL_H_
#include	<oldrecf.h>
#endif
#ifndef	_OLDTYPES_H_
#include "oldtypes.h"
#endif
#ifndef	_LIFILE_DEFCLASS_H_
#include	<lifdef.h>
#endif
#include	<LB1CL.h>

#define	E_NEWHEAD	-989
#define	E_LOCK		-988

class _LIFILECLASS C_OldLB1 : public C_OldRecordFile{
	public:
		TOldControlRecHead	tcrHead;

		C_OldLB1( char *, char *, const char * = NULL, int = SH_DENYNONE );
		C_OldLB1();
		int	Open( char *, char *, const char * = NULL, int = SH_DENYNONE );
		int	LB1_LockHead();
		int	LB1_ReleaseHead();
		int	R_WriteHead();
		int	R_WriteHead( TOldControlRecHead * );
		int	R_ReadHead();
		int	R_ReadHead( TOldControlRecHead * );

		// overload de metodos virtuais
		void Encrypt( void *, char *, size_t );
		void Decrypt( void *, char *, size_t );

};

class _LIFILECLASS C_LB1_V3 : public C_LB1 {
	public:
		int	Open( char *, char *, const char * = NULL, int = SH_DENYNONE );
};

#endif
