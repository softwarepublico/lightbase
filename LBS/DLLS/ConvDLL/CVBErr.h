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

// definicoes dos erros de conversao de base

#ifndef	_CVBERR_H_
#define	_CVBERR_H_

#define	CONV_OK						0
#define	CONVE_CONTROLNOTFOUND		-1
#define	CONVE_CONTROLCONVERROR		-2
#define	CONVE_CONTROLOPENERROR		-3
#define	CONVE_ERRCONV				-4
#define	CONVE_UNKNOWNBASEVERSION	-5
#define	CONVE_NOBASESTOCONV			-6


#endif	// _CVBERR_H_