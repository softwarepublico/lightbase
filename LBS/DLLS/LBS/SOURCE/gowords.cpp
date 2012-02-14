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

// definicao de textos do arquivo gowords.lb

const char *_LBS_GoWordsMsg[] = {
	"; Este arquivo define informações de configuração",
	"; para a base",
	" ",
	"[MAIN]",
	" ",
	"; ===================================================",
	"; tamanho minimo de uma chave para ser indexada",
	"MINKEYSIZE=1",
	" ",
	"; definicoes das gowords de cada campo",
	"; Exemplo:",
	";[apelido_do_campo1]",
	";GW1=goword1, goword2, goword3",
	"; ",
	";[apelido_do_campo2]",
	";GW1=goword1",
	";GW2=goword2",
	";",
	"; Configuração do log de uso",
	"[USAGELOG]",
	"; Campo chave a ser registrado",
	"FIELD=",
	";",
	"; Módulos clientes (separados por vírgula) para os quais nao se deve gerar log",
	"EXCLUDE_MODULES=",
	";",
	"; Apelidos dos campos (separados por vírgula) que devem ser monitorados durante a edição de registros",
	"FIELDSFORUPDATELOG=",
	";",
	"; Máscara em hexadecimal para as operações a serem registradas. As possíveis operações são:",
	"; ABERTURA=0x01",
	"; LEITURA=0x02",
	"; ATUALIZAÇÃO=0x04",
	"; INCLUSÃO=0x08",
	"; EXCLUSÃO=0x10",
	"; SUCESSO NA PESQUISA=0x20",
	"; ERRO NA PESQUISA=0x40",
	"; FECHAMENTO=0x80",
	"OPERATIONS=",
	""
};
