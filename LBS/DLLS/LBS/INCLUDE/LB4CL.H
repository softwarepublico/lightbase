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

#ifndef _LB4_
#define _LB4_

#ifndef	_DYNFILE_
#include	<dynfile.h>
#endif
#ifndef	_LBSDEFS_H_
#include	<lbsdefs.h>
#endif

class C_LB4 : public C_DynamicFile{
	public:
		C_LB4( char *, char *, const char * = NULL, int = SH_DENYNONE );
		C_LB4();
		int Open( char *, char *, const char * = NULL, int = SH_DENYNONE );

		// overload de metodos virtuais
		void Encrypt( void *, char *, size_t );
		void Decrypt( void *, char *, size_t );

};

#endif
