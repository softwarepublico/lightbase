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

