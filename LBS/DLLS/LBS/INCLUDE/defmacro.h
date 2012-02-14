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


