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

/*
	Define macros a serem utilizadas pelo LBWError
	para o tratamento de classes a serem exportadas
	pelo Compress.dll
*/

#ifndef	_COMPRESS_DEFCLASS_H_
#define	_COMPRESS_DEFCLASS_H_

#if defined (BUILDING_COMPRESS_DLL)
#   if defined __BORLANDC__
#      define _COMPRESSCLASS _export
#      define _COMPRESSFUNC  _export
#   else
#      define _COMPRESSCLASS	__declspec( dllexport )
#      define _COMPRESSFUNC  __declspec( dllexport )
#   endif
#elif defined (COMPRESS_DLL)
#   if defined __BORLANDC__
#      define _COMPRESSCLASS _import
#      define _COMPRESSFUNC
#   else
#      define _COMPRESSCLASS	__declspec( dllimport )
#      define _COMPRESSFUNC	__declspec( dllimport )
#   endif
#else
#   define _COMPRESSCLASS
#   define _COMPRESSFUNC
#endif	// BUILDING_LBWERROR_DLL


#endif	//_LBWERROR_DEFCLASS_H_
