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



