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

#ifndef _LB1_
#define _LB1_

#ifndef	_RECFILCL_
#include	<recfilcl.h>
#endif
#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

#define	E_NEWHEAD		-989
#define	E_LOCK			-988
#define	E_REMOVEDFILE	-987

class _LBSCLASS C_LB1 : public C_RecordFile{
	public:
		TControlRecHead	tcrHead;

		C_LB1( char *, char *, const char * = NULL, int = SH_DENYNONE );
		C_LB1( );
		int	Open( char *, char *, const char * = NULL, int = SH_DENYNONE );
		int	LB1_LockHead( BOOL = TRUE );
		int	LB1_ReleaseHead( BOOL = TRUE );
		int	R_WriteHead();
		int	R_WriteHead( TControlRecHead * );
		int	LB1_WriteHead();
		int	R_ReadHead();
		int	R_ReadHead( TControlRecHead * );

		// overload de metodos virtuais
		void Encrypt( void *, char *, size_t );
		void Decrypt( void *, char *, size_t );

};

#endif
