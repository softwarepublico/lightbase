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
