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

// definicao de textos do arquivo gowords.lb

const char *_LBS_GoWordsMsg[] = {
	"; Este arquivo define informa��es de configura��o",
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
	"; Configura��o do log de uso",
	"[USAGELOG]",
	"; Campo chave a ser registrado",
	"FIELD=",
	";",
	"; M�dulos clientes (separados por v�rgula) para os quais nao se deve gerar log",
	"EXCLUDE_MODULES=",
	";",
	"; Apelidos dos campos (separados por v�rgula) que devem ser monitorados durante a edi��o de registros",
	"FIELDSFORUPDATELOG=",
	";",
	"; M�scara em hexadecimal para as opera��es a serem registradas. As poss�veis opera��es s�o:",
	"; ABERTURA=0x01",
	"; LEITURA=0x02",
	"; ATUALIZA��O=0x04",
	"; INCLUS�O=0x08",
	"; EXCLUS�O=0x10",
	"; SUCESSO NA PESQUISA=0x20",
	"; ERRO NA PESQUISA=0x40",
	"; FECHAMENTO=0x80",
	"OPERATIONS=",
	""
};
