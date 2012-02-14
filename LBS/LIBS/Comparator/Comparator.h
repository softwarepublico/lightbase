/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo � parte do programa LightBase - Banco de Dados Textual Documental

O LightBase � um software livre; voc� pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o do Software 
Livre (FSF); na vers�o 2 da Licen�a.

Este programa � distribu�do na esperan�a que possa ser �til, mas SEM NENHUMA 
GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO ou APLICA��O 
EM PARTICULAR. Veja a Licen�a P�blica Geral GNU para maiores detalhes.

Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU versao 2, sob o 
t�tulo "LICENCA.txt", junto com este programa, se n�o, escreva para a Funda��o do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


/*******************************************************
//
// Arquivo de defini��o da classe COMPARATOR
//
//  Jarbas, em 19/01/96
//
*********************************************************/

#ifndef _COMPARATOR
#define _COMPARATOR

// Simbologia dos tipos b�sicos

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
	int		tipo;				// tipo do dado b�sico
	int		tamanho;			// tamanho, quando for string
	char	comptype;			// tipo de compara��o em cadeia
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
