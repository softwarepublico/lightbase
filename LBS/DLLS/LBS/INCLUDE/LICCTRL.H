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

//
// Module: LICCTRL.H
// Description:
//
//	LBSC_LicControl class definition.
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 21/10/96
//

#ifndef	_LICCTRL_H_
#define	_LICCTRL_H_

#define	LIC_INC		0
#define	LIC_DEC		1
#define	NUMTRYLIC	240

class	LBSC_LicControl
{
	private:
		C_RecordFile	cLicFile;				// arquivo de controle de licencas usado em copia rede
		int				iMaxLogin;				// numero maximo de logins que podemos fazer
		BYTE			bControlType;			// tipo de controle de licenca a ser feito (incrementar/decrementar)
		BOOL			bCanceled;				// indica se o processamento deve ser interrompido.
		int				*piNumLic;				// apontador para o contador de licencas de session.
		time_t			*ptLicFileCreateTime;	// apontador para data de criacao do arquivo de licencas
		BOOL			bSomeMonoLog;			// indica se ha' algum login em modo mono.
		long			lLicFilePos;			// posicao no arquivo de licencas
		TNetInfo		*ptni;					// apontador para uma estrutura TNetInfo, vinda de session
		BOOL			bIncSrvLic;				// indica se o numero de licencas do servidor deve ou nao ser incrementado
		BOOL			bDone;					// indica se alguma operacao foi realizada ou nao, para que o destrutor trabalhe ou nao


		int		IncNetLicence();
		int		IncCSLicence( LBSC_Session * );
		int		FinishIncNetLicence();
		int		FinishIncCSLicence();
		int		DecNetLicence( BOOL, LBSC_Session * );
		int		DecCSLicence( LBSC_Session * );
		int		FinishDecNetLicence();
		int		FinishDecCSLicence();
		long	NumLicRec();

	public:
				LBSC_LicControl( time_t * );
				~LBSC_LicControl();
		int		IncLicense( int *, TNetInfo *, LBSC_Session * );
		int		DecLicense( int *, BOOL, LBSC_Session * );
		int		UndoProcess();
		void	SetMono( BOOL );
};


#endif	// _LICCTRL_H_



