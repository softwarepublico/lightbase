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

#ifndef	_TE_TOKEN_H_
#define	_TE_TOKEN_H_

#define   TER_TOKERROR         1
#define   TER_TOKOK            0

#define   TER_TOKENDBUFFER     3
#define   TER_TOKPAR           2
#define   TER_TOKPHRASE        1
#define   TER_TOKWORD          0


#ifdef __cplusplus
extern "C"
{
#endif


class	C_TERGetToken
{
private:
	char		*tmp_pvBuffer;
	char		*pvInitBuffer;
	int			iInitBufSize;
	int			iFmtSignLen;
	int			EhData( char *, int & );
	int			EhHora( char *, int & );

public:
	C_TERGetToken();
	~C_TERGetToken();

	int GetToken( const void *, int, char *, int * );
};

#ifdef __cplusplus
}
#endif

#endif	// _TE_TOKEN_H_

