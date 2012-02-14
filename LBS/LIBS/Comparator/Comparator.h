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


/*******************************************************
//
// Arquivo de definição da classe COMPARATOR
//
//  Jarbas, em 19/01/96
//
*********************************************************/

#ifndef _COMPARATOR
#define _COMPARATOR

// Simbologia dos tipos básicos

#define STRING     's'
#define UCHAR      'c'
#define SHORT      'd'
#define LONGINT    'l'
#define ULONG      'u'
#define FLOAT      'f'
#define DOUBLE     'w'

#define MAIOR      '>'
#define MENOR      '<'

#define PARSEOK        0
#define PREMATUREEND   1
#define STRIGZEROSIZE  2
#define UNKNOWNTYPE    3

#define NONE        0
#define INCREASING  1
#define DECREASING  2

typedef struct tagKeyParts {
	int		tipo;				// tipo do dado básico
	int		tamanho;			// tamanho, quando for string
	char	comptype;			// tipo de comparação em cadeia
	int		offset;				// offset do elemento dentro da string chave
	char	*fixos;				// bytes constantes na chave (alocado)
} KeyParts;

class Comparator {

	public:
		Comparator (char *);
		Comparator (void);
		~Comparator ( void );
		void *BuildKey( void ** );
		int Compare( void *, void * );
		int SetDescriptor( char * );

		void verdados( void *, int );

		int BuildStatus;
		KeyParts KeyCtl[32];

	private:
		int compara( int, void *, void * );
		void killfixos( void );
		int NumbOfKeys;
		int KeySize;
};

#endif
