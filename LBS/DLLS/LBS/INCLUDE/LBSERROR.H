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
// Module: LBSERROR.H
//	Defines LBS error macros
//
// Programmer:	Adriano Sergio R. de Souza*
//		Tricia Souto Santos
//
// Last revision: 28/10/98
//


/*******************************************************************

  Codigos de erro entre -10004 e -11004, inclusive, sao
  erros da Winsock. Basta converte-los para valores positivos.
  Esses erros nao apresentam mensagens aqui neste arquivo, nem no
  lbs.ini. Use metodos da Winsock.dll para obter alguma informacao
  adicional sobre os erros.

*******************************************************************/

#define	SOCKERRORSTART	-11004
#define	SOCKERROREND	-10004

#ifndef	_LBSERROR_H_
#define	_LBSERROR_H_

#ifndef	_LBSE_OF_H_
#include	<lbse_of.h>
#endif

// Macro para setar erro antes de fazer o return
// (so serve para metodos que retornam int)
#define	ERETURN( X )	SetError( X );	\
						return( X )

#define	NRETURN( X )	SetError( X );	\
						return( NULL )

#define	RRETURN( x )	LB1.R_ReleaseHead(); \
						ERETURN( x )

// macros para tratamento de secoes criticas
#define	ERETDYING( x )	if( this->bIsDying ){	\
							ERETURN( x );	\
						}
#define	NRETDYING( x )	if( this->bIsDying ){	\
							ERETURN( x );	\
						}
#define	RETDYING		if( this->bIsDying ){	\
							SetError( x );	\
							return;		\
						}


// LBS error codes
#define	LBS_OK						(0)						// Operacao OK. Nao houve erro.
#define	LBSE_BADARG					(-1 - LBSERROR_OFFSET)	// Algum parametro invalido foi passado.
#define	LBSE_NOMEMORY				(-2 - LBSERROR_OFFSET)	// Erro de alocacao de memoria.
#define	LBSE_EMPTYLIST				(-3 - LBSERROR_OFFSET)	// Tentativa de acesso a uma lista vazia
#define	LBSE_DIRNOTFOUND			(-4 - LBSERROR_OFFSET)	// O diretorio especificado nao foi encontrado
#define	LBSE_DRIVENOTFOUND			(-5 - LBSERROR_OFFSET)	// O drive especificado nao foi encontrado
#define	LBSE_DSKERROR				(-6 - LBSERROR_OFFSET)	// Erro de disco (consulte a variavel errno)
#define	LBSE_NOPERMISSION			(-7 - LBSERROR_OFFSET)	// Tentativa de acesso sem permissao
#define	LBSE_ENDOFLIST				(-8 - LBSERROR_OFFSET)	// Tentativa de caminhar em uma lista que ja estah no fim
#define LBSE_INVALIDDATA			(-9 - LBSERROR_OFFSET)	// Dado invalido encontrado
#define	LBSE_FILEERROR				(-10 - LBSERROR_OFFSET)	// Erro de i/o em algum arquivo
#define LBSE_RECORDNOTWROTE			(-11 - LBSERROR_OFFSET)	// Registro nao foi gravado
#define LBSE_RECORDNOTLOCKED		(-12 - LBSERROR_OFFSET)	// Registro nao foi travado
#define	LBSE_DUPERROR				(-13 - LBSERROR_OFFSET)	// Erro na duplicacao de um objeto
#define	LBSE_LINKNOTFOUND			(-14 - LBSERROR_OFFSET)	// Referencia a um link que nao existe
#define LBSE_REPETITIONNOTFOUND		(-15 - LBSERROR_OFFSET)	// Referencia a uma repeticao que nao existe
#define	LBSE_BASEFIELDLISTNOTWRITED	(-16 - LBSERROR_OFFSET)	// A lista de campos de uma base nao foi gravada
#define	LBSE_INVALIDBASEPASSWORD	(-17 - LBSERROR_OFFSET)	// A password da base eh invalida
#define	LBSE_ERROR					(-18 - LBSERROR_OFFSET)	// Erro generico
#define	LBSE_INDEXNOTFOUND			(-19 - LBSERROR_OFFSET)	// Indice nao foi encontrado
#define	LBSE_FIELDNOTFOUND			(-20 - LBSERROR_OFFSET)	// O campo especificado nao foi encontrado
#define	LBSE_FIELDNOTDELETED		(-21 - LBSERROR_OFFSET)	// O campo especificado nao foi deletado
#define	LBSE_LBSINIERROR			(-22 - LBSERROR_OFFSET)	// Erro no arquivo LBS.INI
#define	LBSE_OBJNOTOK				(-23 - LBSERROR_OFFSET)	// O objeto LBSC_Base nao foi criado com sucesso
#define LBSE_BASENOTCREATED			(-24 - LBSERROR_OFFSET)	// A base nao foi criada com sucesso
#define LBSE_BASENOTFOUND			(-25 - LBSERROR_OFFSET)	// A base nao foi encontrada
#define	LBSE_USERLOGGED				(-26 - LBSERROR_OFFSET)	// O usuario ja estah logado
#define	LBSE_USERNOTLOGGED			(-27 - LBSERROR_OFFSET)	// O usuario nao estah logado
#define	LBSE_USERNOTFOUND			(-28 - LBSERROR_OFFSET)	// O usuario nao foi encontrado
#define	LBSE_INVALIDPASSWORD		(-29 - LBSERROR_OFFSET)	// A password nao eh valida
#define	LBSE_DUPLICATEBASE			(-30 - LBSERROR_OFFSET)	// A base ja existe
#define	LBSE_BASENOTEXCLUSIVE		(-31 - LBSERROR_OFFSET)	// A operacao requer que a base esteja aberta em modo exclusivo
#define LBSE_BASENOTOPEN			(-32 - LBSERROR_OFFSET)	// A base nao foi aberta
#define LBSE_USERNOTOWNERBASE		(-33 - LBSERROR_OFFSET)	// O usuario nao eh o dono da base
#define	LBSE_BASEREADONLY			(-34 - LBSERROR_OFFSET)	// A base estah aberta somente para leitura
#define	LBSE_NOTOPEN				(-35 - LBSERROR_OFFSET)	// O(s) arquivo(s) nao foi(ram) aberto(s)
#define	LBSE_DIFFLISTS				(-36 - LBSERROR_OFFSET)	// As listas diferem
#define	LBSE_NOSTRUCT				(-37 - LBSERROR_OFFSET)	// A base nao possui estrutura definida
#define	LBSE_USERBASENOTFOUND		(-38 - LBSERROR_OFFSET)	// A base de usuarios nao foi encontrada
#define LBSE_CONVERTIONERROR		(-39 - LBSERROR_OFFSET)	// Houve um erro durante a conversao
#define	LBSE_BASEOPEN				(-40 - LBSERROR_OFFSET)	// A base ja estah aberta
#define	LBSE_NOBASESFILE			(-41 - LBSERROR_OFFSET)	// O arquivo de bases nao foi encontrado
#define	LBSE_CANNOTOPENINDSYST		(-42 - LBSERROR_OFFSET)	// Erro na abertura do sistema de indices
#define	LBSE_INVALIDINDEXSYSTEM		(-43 - LBSERROR_OFFSET)	// O sistema de indices eh invalido
#define	LBSE_INVALIDINDEXTYPE		(-44 - LBSERROR_OFFSET)	// O tipo do indice eh invalido
#define	LBSE_ERRINDEX				(-45 - LBSERROR_OFFSET)	// Erro generico no tratamento de indices
#define	LBSE_INVALIDFIELDTYPE		(-46 - LBSERROR_OFFSET)	// Tipo de campo eh invalido
#define	LBSE_NORECORD				(-47 - LBSERROR_OFFSET)	// Nao ha registros na base ou houve um erro de i/o de registro
#define	LBSE_NOFIELD				(-48 - LBSERROR_OFFSET)	// Nao ha campos na lista de campos
#define	LBSE_EXCLUDEDREC			(-49 - LBSERROR_OFFSET)	// Registro estah deletado
#define	LBSE_FIELDNOTCLEANED		(-50 - LBSERROR_OFFSET)	// A operacao Clear no campo nao foi terminada com sucesso
#define	LBSE_POSITIONERROR			(-51 - LBSERROR_OFFSET)	// Tentativa de se posicionar fora dos limites de uma lista
#define	LBSE_INVALIDUSERBASE		(-52 - LBSERROR_OFFSET)	// BU invalida (identificador nao bate)
#define	LBSE_REPOVERFLOW			(-53 - LBSERROR_OFFSET)	// Tentativa de adicionar mais repeticoes do que o permitido
#define	LBSE_UBNOTOK				(-54 - LBSERROR_OFFSET)	// BU nao foi instanciada com sucesso
#define	LBSE_FIELDIDCONFLICT		(-55 - LBSERROR_OFFSET)	// Tentativa de adicionar um campo com mesmo id de um campo ja existente
#define	LBSE_INVALIDSIZE			(-56 - LBSERROR_OFFSET)	// Tentativa de adicionar uma repeticao de tamanho maior que o permitido
#define LBSE_NOTFULLACCESS			(-57 - LBSERROR_OFFSET)	// Acesso à manutencao negado
#define LBSE_TICKETNOTOK			(-58 - LBSERROR_OFFSET)	// Ticket invalido
#define	LBSE_INVALIDNAME			(-59 - LBSERROR_OFFSET)	// Nome (provavelmente de base) invalido
#define	LBSE_LASTRECORD				(-60 - LBSERROR_OFFSET)	// A base ja estah no ultimo registro
#define	LBSE_FIRSTRECORD			(-61 - LBSERROR_OFFSET)	// A base ja estah no primeiro registro
#define	LBSE_INVALIDFIELD			(-62 - LBSERROR_OFFSET)	// campo invalido
#define LBSE_NAMENOTFOUND			(-63 - LBSERROR_OFFSET)	// Nome/Grupo nao encontrado na lista de ACL
#define LBSE_IDNOTFOUND				(-64 - LBSERROR_OFFSET)	// Campo/Registro nao encontrado na lista de permissoes
#define	LBSE_WRONGRECORD			(-65 - LBSERROR_OFFSET)	// Registro invalido encontrado
#define	LBSE_ZERORECORD				(-66 - LBSERROR_OFFSET)	// Cabecalho de registro (LB1) aponta para lugar vazio em LB2
#define	LBSE_NOTEXPORTABLEBASE		(-67 - LBSERROR_OFFSET)	// Base nao pode ser exportada
#define	LBSE_DUPKEY					(-68 - LBSERROR_OFFSET)	// Tentativa de duplicar chave-unica
#define LBSE_NOOCCURRENCE			(-69 - LBSERROR_OFFSET)	// Ocorrencia nao existe
#define	LBSE_FIRSTOCCURRENCE		(-70 - LBSERROR_OFFSET)	// Tentativa de caminhar para tras em uma LO que ja' esta' no inicio
#define	LBSE_LASTOCCURRENCE			(-71 - LBSERROR_OFFSET)	// Tentativa de caminhar para frente em uma LO que ja' esta' no fim
#define	LBSE_INVALIDOCLIST			(-72 - LBSERROR_OFFSET)	// Lista de ocorrencias invalida
#define	LBSE_EMPTYINDEX				(-73 - LBSERROR_OFFSET)	// Indice nao contem nehuma chave armazenada
#define	LBSE_INVALIDRECPOSITION		(-74 - LBSERROR_OFFSET)	// Tentativa de fazer seek com um valor fora de faixa
#define	LBSE_CREATEFIELDINDEX		(-75 - LBSERROR_OFFSET)	// Erro na criacao do indice especial de um campo
#define	LBSE_OPENFIELDINDEX			(-76 - LBSERROR_OFFSET)	// Erro na abertura do indice especial de um campo
#define	LBSE_FILEEXIST				(-77 - LBSERROR_OFFSET)	// Arquivo ja existe
#define	LBSE_NOOCLIST				(-78 - LBSERROR_OFFSET)	// Nao ha' LO setada
#define	LBSE_INFISICOCLIST			(-79 - LBSERROR_OFFSET)	// A LO corrente e' a LO fisica
#define	LBSE_DELFISICOL				(-80 - LBSERROR_OFFSET)	// Tentativa de deletar a LO fisica
#define	LBSE_DELCURROL				(-81 - LBSERROR_OFFSET)	// Tentativa de deletar a LO corrente
#define	LBSE_ENABLE					(-82 - LBSERROR_OFFSET)	// Erro na tentativa de habilitar uma LO
#define	LBSE_RESTRICT				(-83 - LBSERROR_OFFSET)	// Erro na tentativa de restringir uma LO
#define	LBSE_EMPTYSLOT				(-84 - LBSERROR_OFFSET)	// Slot vazio
#define	LBSE_USINGNAVINDEX			(-85 - LBSERROR_OFFSET)	// O LBS esta' usando a navegacao de registros por indice
#define	LBSE_USINGNAVKEY			(-86 - LBSERROR_OFFSET)	// O LBS esta' usando a navegacao de registros por uma chave
#define	LBSE_UNDEFINEDRECORD		(-87 - LBSERROR_OFFSET)	// nao ha' registro corrente definido
#define	LBSE_OLDRECORD				(-88 - LBSERROR_OFFSET)	// o registro em memoria esta' velho em relacao ao registro que esta' em disco
#define	LBSE_HEADERROR				(-89 - LBSERROR_OFFSET)	// houve um erro no tratamento do header de LB1/LB3 (provavelmente erro de lock)
#define	LBSE_LOCKERROR				(-90 - LBSERROR_OFFSET)	// houve um erro na tentativa de travar algum arquivo
#define	LBSE_DUPLICATE				(-91 - LBSERROR_OFFSET)	// tentativa de criar um objeto que ja' existe (duplicacao de objeto)
#define	LBSE_INVALIDID				(-92 - LBSERROR_OFFSET)	// identificador errado (o contexto depende do metodo)
#define	LBSE_BADUSERBASE			(-93 - LBSERROR_OFFSET)	// A UDB esta' danificada (provavelmente o sistema de indices)
#define	LBSE_MAINTMODE				(-94 - LBSERROR_OFFSET)	// A base esta' aberta para manutencao. Nao eh permitido acesso aos dados.
#define	LBSE_INVALIDUSERTYPE		(-95 - LBSERROR_OFFSET)	// O tipo do usuario nao permite realizar a operacao desejada
#define	LBSE_OBJDYING				(-96 - LBSERROR_OFFSET)	// O destrutor do objeto esta' sendo processado por outro thread
#define	LBSE_THEREAREUSERS			(-97 - LBSERROR_OFFSET)	// Ha' outros usuarios logados.
#define	LBSE_MONOMODE				(-98 - LBSERROR_OFFSET)	// O servidor esta' em modo monousuario
#define	LBSE_EXPRERROR				(-99 - LBSERROR_OFFSET)	// Erro na expressao
#define	LBSE_ARGTOOLONG				(-100 -LBSERROR_OFFSET)	// Parametro grande demais
#define	LBSE_MAXSERVERLOGIN			(-101 -LBSERROR_OFFSET)	// Numero maximo de licencas de uso do servidor foi atingido
#define	LBSE_MAXCLIENTLOGIN			(-102 -LBSERROR_OFFSET)	// Numero maximo de licencas de uso do cliente foi atingido
#define	LBSE_DIREXIST				(-103 -LBSERROR_OFFSET)	// Erro na tentativa de criar um diretorio
#define	LBSE_SORTERROR				(-104 -LBSERROR_OFFSET)	// Erro na tentativa de ordenar um objeto
#define	LBSE_UNDEFINEDRECNUM		(-105 -LBSERROR_OFFSET)	// Numero indefinido de registros na LO corrente
#define	LBSE_UDBWITHBASE			(-106 -LBSERROR_OFFSET)	// A UDB possui pelo menos uma base ligada a ela
#define	LBSE_SERVEREXPIRED			(-107 -LBSERROR_OFFSET)	// A data de validade do servidor estoutou
#define	LBSE_SERVERNOTPERS			(-108 -LBSERROR_OFFSET)	// O servidor ainda nao foi personalizado
#define	LBSE_USERALREADYEXIST		(-109 -LBSERROR_OFFSET)	// O usuario ja' existe
#define	LBSE_RECORDLOCKED			(-110 -LBSERROR_OFFSET)	// O registro requerido esta' travado
#define	LBSE_BUSY					(-111 -LBSERROR_OFFSET)	// Nao foi possivel realizar a operacao. Tente novamete.
#define	LBSE_INVALIDSERIALNUM		(-112 -LBSERROR_OFFSET)	// Numero de serie invalido
#define	LBSE_FATALLIC				(-113 -LBSERROR_OFFSET)	// Alguem deletou o arquivo de licencas indevidamente. Favor resetar todo o sistema.
#define	LBSE_INVALIDCLIENTNAME		(-114 -LBSERROR_OFFSET)	// Nome do cliente eh invalido. Provavelmente duplicado na rede.
#define	LBSE_PRIVUSERNAMEFAULT		(-115 -LBSERROR_OFFSET)	// A operacao requer o nome do usuario, mas esse nome nao foi informado.
#define	LBSE_PRIVPASSWORDFAULT		(-116 -LBSERROR_OFFSET)	// A operacao requer uma senha, mas ela nao foi informada.
#define	LBSE_BADBASENOTRDONLY		(-117 -LBSERROR_OFFSET)	// A base nao pode ser aberta em modo read_only porque precisa ser recuperada de algum crash.
#define	LBSE_INCONSISTBASE			(-118 -LBSERROR_OFFSET)	// A base esta' com seus dados inconsistentes. E' necessario reprocessa-la.
#define	LBSE_SECUREWRITE			(-119 -LBSERROR_OFFSET)	// Nao consegui gravar informacoes de controle. Verifique se ha' espaco em disco e, se for o caso, reprocesse a base.
#define	LBSE_CANTOPENRDONLY			(-120 -LBSERROR_OFFSET)	// Nao consegui abrir a base em modo read_only. Verifique se outro processo esta' usando a base em modo exclusivo.
#define	LBSE_BADCTRLFILE			(-121 -LBSERROR_OFFSET)	// A versao do arquivo de controle do LBS esta' incorreta.
#define	LBSE_NOMONOMODE				(-122 -LBSERROR_OFFSET)	// O usuario nao esta' logado em modo monousuario e a operacao requer isso.
#define	LBSE_OLDBASEVERSION			(-123 -LBSERROR_OFFSET)	// A versao da base referenciada eh antiga. Eh necessario converte-la para poder usa-la.
#define	LBSE_CANTOPENEXCLUSIVE		(-124 -LBSERROR_OFFSET)	// Nao consegui abrir a base em modo exclusivo. Verifique se outro processo esta' usando a referida base.
#define	LBSE_BADLICFILE				(-125 -LBSERROR_OFFSET)	// A versao do arquivo de controle de licencas do LBS esta' incorreta. Eh necessario fechar todas as aplicacoes e apagar o arquivo.
#define	LBSE_ONLYBASEOWNER			(-126 -LBSERROR_OFFSET)	// Esta operacao so' podera' ser realizada pelo dono da base.
#define	LBSE_CANTOPENFILE			(-127 -LBSERROR_OFFSET)	// Nao consegui abrir os arquivos da base. Verifique se algum outro modulo esta' usando a base em modo exclusivo e tente novamente.
#define	LBSE_CANTINITLBS			(-128 -LBSERROR_OFFSET)	// Nao foi possivel inicializar o LBS.
#define	LBSE_INVALIDLIC				(-129 -LBSERROR_OFFSET)	// A licenca reservada para esta maquina foi invalidada por outra aplicacao. Por favor feche todas as aplicacoes desta maquina e inicialize-as novamente.
#define	LBSE_CANNOTINDEXOLDVERSION	(-130 -LBSERROR_OFFSET)	// Esta versão do LightBase não permite indexação de bases de outras versões. Por favor reprocesse a abase.
#define	LBSE_URLNOTFOUND			(-131 -LBSERROR_OFFSET)	// URL não encontrada. Por favor, verifique se o diretório definido em REFDIRBASE no arquivo lbs.ini está correto ou se a URL está escrita corretamente e sua conexão de rede está funcionando.
#define	LBSE_INVALIDINDEX			(-132 -LBSERROR_OFFSET)	// Índice inválido para o conjunto. (depende da operação)
#define	LBSE_UNDEFINEDACL			(-133 -LBSERROR_OFFSET)	// Permissão indefinida.
#define	LBSE_BASERESERVED			(-134 -LBSERROR_OFFSET)	// Base reservada para manutencao. Nao pode ser aberta neste momento.
#define	LBSE_BASEALREADYRESERVED	(-135 -LBSERROR_OFFSET)	// A base já está reservada para manutenção por outro usuário.
#define	LBSE_BASENOTRESERVED		(-136 -LBSERROR_OFFSET)	// A base não está reservada para manutenção.
#define	LBSE_HTTPOPINTERRUPTED		(-137 -LBSERROR_OFFSET)	// Erro http: Operation interrupted
#define	LBSE_HTTPCANTOPENATT		(-138 -LBSERROR_OFFSET)	// Erro http: Can't open AttachedFile
#define	LBSE_HTTPPROTOCOLERROR		(-139 -LBSERROR_OFFSET)	// Erro http: HTTP protocol error
#define	LBSE_HTTPNOSERVERINURL		(-140 -LBSERROR_OFFSET)	// Erro http: No server specified in URL
#define	LBSE_HTTPINVALIDURLSCHEME	(-141 -LBSERROR_OFFSET)	// Erro http: Specified URLScheme is invalid
#define	LBSE_CANNOTBACKUPFILES		(-142 -LBSERROR_OFFSET)	// Erro ao fazer backup dos arquivos da base; verifique se há espaço em disco suficiente
#define	LBSE_HTTPURLNOTFOUND		(-143 -LBSERROR_OFFSET)	// Erro http: URL not found 
#define	LBSE_HTTPTIMEOUT			(-144 -LBSERROR_OFFSET)	// Erro http: Gateway Timeout 
#define	LBSE_HTTPACCESSFORBIDDEN	(-145 -LBSERROR_OFFSET)	// Erro http: Access forbidden 
#define	LBSE_HTTPINTERNALERROR		(-146 -LBSERROR_OFFSET)	// Erro http: Server internal error 
#define	LBSE_HTTPUNAVAILABLE		(-147 -LBSERROR_OFFSET)	// Erro http: Service unavailable
#define	LBSE_USERBLOCKED			(-148 -LBSERROR_OFFSET)	// Usuário bloqueado devido a seguidas tentativas de login incorretas
#define	LBSE_PASSWORDEXPIRED		(-149 -LBSERROR_OFFSET)	// Senha do usuário expirada
#define	LBSE_INVALIDPASSWORDFORMAT	(-150 -LBSERROR_OFFSET) // Formato inválido para a senha
#define	LBSE_EQUALSSTOREDPASSWORDS	(-151 -LBSERROR_OFFSET) // Nova senha não pode ser igual às ultimas senhas armazenadas
#define	LBSE_USERBLOCKING			(-152 -LBSERROR_OFFSET) // Senha inválida. Verifique sua senha: você pode ter seu acesso bloqueado se não informar a senha correta
#define	LBSE_CONTROLFILENOTOK		(-153 -LBSERROR_OFFSET) // Arquivo de controle não foi instanciado corretamente
#define	LBSE_CONVERTWITHLB_V3		(-154 -LBSERROR_OFFSET) // Esta base nao pode ser convertida pela versão atual. Utilize um LightBase versão 3.* para converte-la primeiro
#define	LBSE_TOOMANYOPENFILES		(-155 -LBSERROR_OFFSET) // Limite de arquivos abertos atingido

#define	LBSE_NETERROR				(-200 -LBSERROR_OFFSET)	// Erro de rede
#define	LBS_CS_INVALIDPROTO			(-201 -LBSERROR_OFFSET)	// Protocolo invalido
#define	LBS_CS_INVALIDPORT			(-202 -LBSERROR_OFFSET)	// Porta invalida
#define	LBS_CS_INVALIDTMOUT			(-203 -LBSERROR_OFFSET)	// Timeout invalido
#define	LBS_CS_INVALIDCLIENT		(-204 -LBSERROR_OFFSET)	// Cliente invalido
#define	LBS_CS_INVALIDSERVERS		(-205 -LBSERROR_OFFSET)	// Servidores invalidos
#define	LBS_CS_INVALIDPORT32S		(-206 -LBSERROR_OFFSET)	// Porta 32s invalida
#define	LBS_CS_NOAPP				(-207 -LBSERROR_OFFSET)	// Aplicacao nao encontrada
#define	LBSE_REINSTALL				(-208 -LBSERROR_OFFSET)	// Versão incompatível entre o servidor e o cliente; favor instalar o cliente com uma versao mais nova

#define	LBSE_FATAL					(-249 -LBSERROR_OFFSET)	// Erro fatal

// Warnings
#define	LBSW_NOTREADY				(-250 -LBSERROR_OFFSET)	// Metodo ainda nao implementado
#define	LBSW_OPENNOIS				(-251 -LBSERROR_OFFSET)	// A base foi aberta, mas o sistema de indices 
															// nao esta' disponivel (precisa ser regerado)
#define	LBSW_INDEXSTOPED			(-252 -LBSERROR_OFFSET)	// A (re)indexacao foi parcialmente concluida (o contexto foi gravado).
#define	LBSW_FAILURE				(-253 -LBSERROR_OFFSET)	// A operacao NAO foi totalmente realizada
#define	LBSW_OPCANCEL				(-254 -LBSERROR_OFFSET)	// A operacao foi cancelada pelo usuario.
#define	LBSW_OPENBUTNEEDREPROC		(-255 -LBSERROR_OFFSET)	// A base foi aberta, mas sua estrutura esta'
															// desatualizada e precisa ser reprocessada
#define	LBSW_DAMAGEDBUTREPROC		(-256 -LBSERROR_OFFSET)	// A base foi reprocessada, mas registros danificados foram encontrados e eliminados; verifique o arquivo reproc.log no diretório da base para maiores detalhes"

#endif // _LBSERROR_H_


