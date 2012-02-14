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

// redefine macros para porte
// Adriano Sergio
// 01.09.95

#ifndef	_DEFMACRO_H_
#define	_DEFMACRO_H_


#ifndef __BORLANDC__
#	define	SH_DENYNONE	_SH_DENYNO
#	define	MAXPATH		_MAX_PATH
#	define	MAXINT		INT_MAX
#	define	MAXDRIVE	_MAX_DRIVE
#	define	MAXDIR		_MAX_DIR
#	define	MAXEXT		_MAX_EXT
#	define	MAXFILE		_MAX_FNAME
#	define	S_IWRITE	_S_IWRITE
#	define	S_IREAD		_S_IREAD
#	define	O_RDWR		_O_RDWR
#	define	O_BINARY	_O_BINARY
#	define	O_CREAT		_O_CREAT
#	define	O_TEXT		_O_TEXT
#	define	O_RDONLY	_O_RDONLY
#endif


#endif	// _DEFMACRO_H_


