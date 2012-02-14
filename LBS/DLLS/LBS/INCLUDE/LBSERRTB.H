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
// Module: LBSERRTB.H
// Description:
//
//	LBS Error Table definition file
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 07/12/94
//

#ifndef	_LBSERRTB_H_
#define	_LBSERRTB_H_

const char *_LBS_ErrorTable[] = {

	"Nao houve erro",							// 0
	"Parametro invalido",							// 1
	"Erro em alocacao de memoria",						// 2
	"Tentativa de acesso a uma lista vazia",				// 3
	"Diretorio nao encontrado",						// 4
	"Drive nao encontrado",							// 5
	"Erro de disco",							// 6
	"Tentativa de acesso sem permissao",					// 7
	"Tentativa de caminhar em uma lista que ja' esta' no seu fim",		// 8
	"Informacao invalida",							// 9
	"Erro de e/s em um dos arquivos",					// 10
	"Registro nao foi gravado",
	"Registro nao foi travado",
	"Erro na duplicacao de um objeto",
	"Referencia a um link que nao existe",
	"Referencia a uma repeticao que nao existe",
	"A lista de campos da base nao foi gravada",
	"A password da base e' invalida",
	"Erro generico",
	"Indice nao foi encontrado",
	"Campo nao foi encontrado",						// 20
	"Campo nao foi deletado",
	"Erro no arquivo .ini",
	"O objeto BASE nao foi criado com sucesso",
	"A base de dados nao foi criada",
	"A base de dados nao foi encontrada",
	"O usuario ja' esta' logado",
	"O usuario nao esta' logado",
	"Usuario nao encontrado",
	"Password invalida",
	"A base ja' existe",							// 30
	"Esta operacao requer que a base esteja aberta em modo exclusivo",
	"A base nao foi aberta",
	"O usuario nao e' o dono da base",
	"A base esta' aberta somente para leitura",
	"O(s) arquivo(s) nao foi(am) aberto(s)",
	"As listas diferem",
	"A base nao possui estrutura definida",
	"A base de usuarios nao foi encontrada",
	"Erro de conversao",
	"A base ja' esta' aberta",						// 40
	"O arquivo de controle do LBS nao foi encontrado",
	"Erro na abertura do sistema de indices",
	"Sistema de indices invalido",
	"Indice invalido",
	"Erro no tratamento dos indices",
	"Tipo de campo invalido",
	"Nao ha' registros na base",
	"Nao ha' campos na estrutura da base",
	"Registro esta' deletado",
	"A operacao CLEAR no campo nao foi bem-sucedida",			// 50
	"Tentativa de se posicionar fora dos limites de uma lista",
	"Base de usuarios invalida",
	"Tentativa de adicionar mais repeticoes do que o permitido",
	"Base de usuarios nao foi instanciada com sucesso",
	"Tentativa de criar um campo com identificador ja' existente",
	"Tentativa de adicionar uma repeticao com tamanho maior que o permitido",
	"Usuario nao possui acesso para manutencao da base",
	"Ticket de acesso e' invalido",
	"Nome invalido",
	"A base ja' esta' posicionada sobre o ultimo registro",			// 60
	"A base ja' esta' posicionada sobre o primeiro registro",
	"Campo invalido",
	"Nome ou grupo nao encontrado nas ACL's",
	"Campo ou registro nao encontrado nas ACL's",
	"Registro invalido",
	"Cabecalho de registro aponta para lugar vazio no arquivo de dados",
	"Base nao pode ser exportada",
	"Tentativa de gravar uma chave unica que ja' existe",
	"Tentativa de acessar uma ocorrencia que nao existe",
	"Tentativa de caminhar para tras em uma LO que ja' esta' no inicio",	// 70
	"Tentativa de caminhar para frente em uma LO que ja' esta' no fim",
	"Lista de ocorrencias invalida",
	"Indice nao contem nehuma chave armazenada",
	"Tentativa de fazer seek com um valor fora de faixa",
	"Erro na criacao do indice especial de um campo",
	"Erro na abertura do indice especial de um campo",
	"Arquivo ja existe",
	"Nao ha' LO setada",
	"A LO corrente e' a LO fisica",
	"Tentativa de deletar a LO fisica",					// 80
	"Tentativa de deletar a LO corrente",
	"Erro na tentativa de habilitar uma LO",
	"Erro na tentativa de restringir uma LO",
	"Slot vazio",
	"O LBS esta' usando a navegacao de registros por indice",
	"O LBS esta' usando a navegacao de registros por uma chave",
	"Nao ha' registro corrente definido",
	"O registro em memoria esta' velho em relacao ao registro que esta' em disco",
	"Houve um erro no tratamento do header de LB1/LB3 (provavelmente erro de lock)",
	"Houve um erro na tentativa de travar algum arquivo",			// 90
	"Tentativa de criar um objeto que ja' existe (duplicacao de objeto)",
	"Identificador errado (o contexto depende do metodo)",
	"A UDB esta' danificada (provavelmente o sistema de indices)",
	"A base esta' aberta para manutencao. Nao eh permitido acesso aos dados.",
	"O tipo do usuario nao permite realizar a operacao desejada",
	"O destrutor do objeto esta' sendo processado por outro thread",
	"Ha' outros usuarios logados.",
	"O servidor esta' em modo monousuário",
	"Erro na expressao",
	"Parametro grande demais",						// 100
	"Numero maximo de licencas de uso do servidor foi atingido",
	"Numero maximo de licencas de uso do cliente foi atingido",
	"Erro na tentativa de criar um diretorio",
	"Erro na tentativa de ordenar um objeto",
	"Numero indefinido de registros na LO corrente",
	"A UDB possui pelo menos uma base ligada a ela",
	"A data de validade do servidor estoutou",
	"O servidor ainda nao foi personalizado",
	"O usuario ja' existe",
	"O registro requerido esta' travado",			// 110
	"Nao foi possivel realizar a operacao. Tente novamete.",
	"Numero de serie invalido",
	"Alguem deletou o arquivo de licencas indevidamente. Favor resetar todo o sistema.",
	"Nome do cliente eh invalido. Provavelmente duplicado na rede.",
	"A operacao requer o nome do usuario, mas esse nome nao foi informado.",
	"A operacao requer uma senha, mas ela nao foi informada.",
	"A base nao pode ser aberta em modo read_only porque precisa ser recuperada de algum crash.",
	"A base esta' com seus dados inconsistentes. E' necessario reprocessa-la.",
	"Nao consegui gravar informacoes de controle. Verifique se ha' espaco em disco e, se for o caso, reprocesse a base.",
	"Nao consegui abrir a base em modo read_only. Verifique se outro processo esta' usando a base em modo exclusivo.",		// 120
	"A versao do arquivo de controle do LBS esta' incorreta.",
	"O usuario nao esta' logado em modo monousuario e a operacao requer isso.",
	"A versao da base referenciada eh antiga. Eh necessario converte-la para poder usa-la.",
	"Nao consegui abrir a base em modo exclusivo. Verifique se outro processo esta' usando a referida base.",
	"A versao do arquivo de controle de licencas do LBS esta' incorreta. Eh necessario fechar todas as aplicacoes e apagar o arquivo.",
	"Esta operacao so' podera' ser realizada pelo dono da base.",
	"Nao consegui abrir os arquivos da base. Verifique se algum outro modulo esta' usando a base em modo exclusivo e tente novamente.",
	"Nao foi possivel inicializar o LBS.",
	"A licenca reservada para esta maquina foi invalidada por outra aplicacao. Por favor feche todas as aplicacoes desta maquina e inicialize-as novamente.",
	"Esta versão do LightBase não permite indexação de bases de outras versões. Por favor reprocesse a abase.",						// 130
	"URL não encontrada. Por favor, verifique se o diretório definido em REFDIRBASE no arquivo lbs.ini está correto ou se a URL está escrita corretamente e sua conexão de rede está funcionando.",
	"Índice inválido para o conjunto. (interpretação depende da operação)."
	"Permissão indefinida.",
	"Base reservada para manutencao. Nao pode ser aberta neste momento.",
	"A base já está reservada para manutenção por outro usuário.",
	"A base não está reservada para manutenção.",
	"Erro http: Operação interrompida.",
	"Erro http: Não consegui abrir o arquivo 'attach'.",
	"Erro http: Erro no protocolo HTTP.",
	"Erro http: Nao há servidor especificado na URL.",
	"Erro http: URL especificada é inválida.",
	"Erro ao fazer backup dos arquivos da base; verifique se há espaço em disco suficiente.",
	"Erro http: Não foi possível encontrar URL.",
	"Erro http: Gateway Timeout.",
	"Erro http: Acesso proibido.",
	"Erro http: Erro interno do servidor.",
	"Erro http: Serviço indisponível.",
	"Usuário bloqueado devido a seguidas tentativas de login incorretas",
	"A senha do usuário expirou",
	"Formato inválido para a senha",						// 150
	"Nova senha não pode ser igual às ultimas senhas armazenadas",
	"Senha inválida. Verifique sua senha: você pode ter seu acesso bloqueado se não informar a senha correta",
	"Arquivo de controle não foi instanciado corretamente",
	"Esta base nao pode ser convertida pela versão atual. Utilize um LightBase versão 3.* para converte-la primeiro",
	"Limite de arquivos abertos atingido",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",						// 160
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",						// 170
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",						// 180
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",						// 190
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"CODIGO DE ERRO RESERVADO",
	"Erro de rede",									// 200
	"Protocolo invalido.",
	"Porta invalida.",
	"Timeout invalido."
	"Cliente invalido."
	"Servidores invalidos."
	"Porta 32s invalida",
	"Aplicacao nao encontrada.",
	"Versão incompatível entre o servidor e o cliente; favor instalar o cliente com uma versao mais nova",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",				// 210
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",				// 220
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",				// 230
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",				// 240
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"CODIGO DE ERRO DE REDE RESERVADO",
	"Erro fatal",
	"Metodo ainda nao implementado",				// 250
	"A base foi aberta, mas o sistema de indices nao esta' disponivel",
	"A (re)indexacao foi parcialmente concluida (o contexto foi gravado)",
	"A operacao NAO foi totalmente realizada",
	"A operacao foi cancelada pelo usuario.",
	"A base foi aberta, mas sua estrutura está desatualizada e precisa ser reprocessada.",
	"A base foi reprocessada, mas registros danificados foram encontrados e eliminados; verifique o arquivo reproc.log no diretório da base para maiores detalhes",
	"CODIGO DE WARNING RESERVADO",
	"CODIGO DE WARNING RESERVADO",
	"CODIGO DE WARNING RESERVADO",
	"CODIGO DE WARNING RESERVADO"						// 260

};

#define	ERRORTABLESIZE	260

#endif	// _LBSERRTB_H_



