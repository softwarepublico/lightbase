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

#ifndef _OLDLB3_
#define _OLDLB3_

#ifndef	_RECFILCL_
#include	<recfilcl.h>
#endif
#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif
#ifndef	_OLDTYPES_H_
#include "oldtypes.h"
#endif
#ifndef	_LIFILE_DEFCLASS_H_
#include	<lifdef.h>
#endif

class _LIFILECLASS C_OldLB3 : public C_OldRecordFile{
	public:
		TOldStructHeadRec	tsHead;

		C_OldLB3( char *, char *, const char * = NULL, int = SH_DENYNONE, int = 0 );
		C_OldLB3();
		int Open( char *, char *, const char * = NULL, int = SH_DENYNONE, int = 0 );
		int	LB3_LockHead( TOldStructHeadRec * );
		int	LB3_ReleaseHead( TOldStructHeadRec * );

		// overload de metodos virtuais
		void Encrypt( void *, char *, size_t );
		void Decrypt( void *, char *, size_t );

};

#endif
