/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o 
título "LICENCA.txt", junto com este programa, se não, escreva para a Fundação do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#include	<string.h>

#include	"crypt.h"


/*-----------------------------------------------------------
 * Criptografa
 *
 * criptografa todos os caracteres entre dois 
 * apontadores dados. Este algoritmo eh inversivel
 * pela funcao 'decriptografa'. 
 *
 * retorna um "checksum"
 *
 */
int
Criptografa( char *bufi, char *buff )
{
	register int	c;
	register int	ant = 0;
	register int	soma = 0;

	for( ; bufi < buff; ++bufi ) {
		c = *bufi;
		c = (c + ant - soma) & 0377;  
		ant = c;
		soma += ( c * (ant + 1 ) );
		*bufi = c;
	}
	return( soma & 0xFFFF );
}



/*-----------------------------------------------------------
 * Decriptografa
 *
 * decriptografa todos os caracteres entre dois 
 * apontadores dados. Este algoritmo desfaz o que a funcao
 * 'criptografa' faz. 
 *
 * retorna um "checksum"
 *
 */
int
Decriptografa( char *bufi, char *buff )
{
	register int	ant = 0;
	register int	soma = 0;
	register int	c;

	for( ; bufi < buff; ++bufi ) {
		c = *bufi & 0377;
		*bufi = ( c - ant + soma ) & 0377; 
		ant = c;
		soma += ( c * ( ant + 1 ) );

	}
	return( soma & 0xFFFF );
}



/*-----------------------------------------------------------
 * crypt_key
 *
 * criptografa todos os caracteres entre dois 
 * apontadores dados usando um algoritmo NAO INVERSIVEL. 
 * Este algoritmo mapeia todos os caracteres gerados para 
 * caracteres entre 'a' e 'z' (inclusive). Isto porque o string
 * resultante serah usado como uma senha "digitavel" (Activation Key),
 * que nao pode conter caracteres de controle ou outros caracteres
 * nao imprimiveis. 
 *
 * retorna nada
 *
 */
void
crypt_key( char *str_ini, char *str_fim )
{
	register int	soma = 0;
	register int	ant = 0;
	register int	c;

	soma = Criptografa( str_ini, str_fim );
	--str_fim;
	do {
		c = (*str_fim + ant - soma) & 0377;
		soma += ( c * (ant + 1) );
		ant = c;
		/* mapeia para um numero entre 0 e 25
		 * (as letras do alfabeto) e obtem 
 		 * uma letra entre 'a' e 'z'
 		 */ 
		c = (c % 26) + 'a';
		*str_fim = c;
	} while( str_fim-- > str_ini );
}



/*
 * rotina:
 *    istrncpy
 * objetivo:
 *    copia n caracteres de orig em dest colocando um 
 *    NULL no fim de dest.
 * parametros de entrada:
 *    dest -> apontador para a cadeia destino;
 *    orig -> apontador para a cadeia de origem;
 *    tam -> numero de caracteres a ser copiado;
 * chamada por:
 * retorno: dest; 
 * algoritmo: obvio.
 */

char*
istrncpy( register char *dest, register char *orig, register int tam )
{
	char	*aux;

	aux = strncpy( dest, orig, tam );
	dest[ tam ] = '\0';
	return( aux );
}
