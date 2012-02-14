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


/*************************************************************
//
// Arquivo principal de implementação da classe Comparator
//
// Jarbas Campos, em 20/01/96
**************************************************************/

#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#include <windows.h>
#include <string.h>
#include <comparator.h>

int Comparator::Compare( void *key1, void *key2 )
{
//
// Faz a comparação de duas chaves passadas nos parâmetros, de acordo com a
// regra definida no parâmetro de construção.
//

	int i = 0;
	int ret;

	if( BuildStatus != PARSEOK )		// ADRIANO
		return 2;

	for( i=0; i<NumbOfKeys; ++i )
	{
		switch( KeyCtl[i].comptype )
		{
		case NONE:
			ret = 0;
			break;

		case INCREASING:
			ret = compara( i, key1, key2 );
			break;

		case DECREASING:
			ret = compara( i, key2, key1 );
			break;
		}

		if( ret !=0 )
			return ret;
	}

	return ret;
	
}

int Comparator::compara( int i, void *key1, void *key2 )
{
//
// Faz a efetiva comparação se o elemento de chave de número i do parâmetro key1
// é menor, maior ou igual ao seu equivalente da chave 2
//

	int iOff = KeyCtl[i].offset;
	int iTam = KeyCtl[i].tamanho;
	double dbRet = 0;

	switch( KeyCtl[i].tipo )
	{
	case STRING:
		return strncmp( (char *)(key1)+iOff, (char *)(key2)+iOff,
		       iTam );

	case UCHAR:
		{
			unsigned char ucKey1 = 0;
			unsigned char ucKey2 = 0;

			memcpy( &ucKey1, (unsigned char *)(key1)+iOff, iTam); 
			memcpy( &ucKey2, (unsigned char *)(key2)+iOff, iTam); 
			return (int) (ucKey1 - ucKey2); 
		}

	case SHORT:
		{
			short sKey1 = 0;
			short sKey2 = 0;

			memcpy( &sKey1, (unsigned char *)(key1)+iOff, iTam); 
			memcpy( &sKey2, (unsigned char *)(key2)+iOff, iTam); 
			return (int) (sKey1 - sKey2); 
		}

	case FLOAT:
		{
			float fKey1 = 0;
			float fKey2 = 0;

			memcpy( &fKey1, (unsigned char *)(key1)+iOff, iTam); 
			memcpy( &fKey2, (unsigned char *)(key2)+iOff, iTam); 
			dbRet = fKey1 - fKey2; 
		}
		break;

	case DOUBLE:
		{
			double dbKey1 = 0;
			double dbKey2 = 0;

			memcpy( &dbKey1, (unsigned char *)(key1)+iOff, iTam); 
			memcpy( &dbKey2, (unsigned char *)(key2)+iOff, iTam); 
			dbRet = dbKey1 - dbKey2; 
		}
		break;

	case LONGINT:
		{
			long lKey1 = 0;
			long lKey2 = 0;

			memcpy( &lKey1, (unsigned char *)(key1)+iOff, iTam); 
			memcpy( &lKey2, (unsigned char *)(key2)+iOff, iTam); 
			return (int) (lKey1 - lKey2); 
		}
		break;

	case ULONG:
		{
			unsigned long ulKey1 = 0;
			unsigned long ulKey2 = 0;

			memcpy( &ulKey1, (unsigned char *)(key1)+iOff, iTam); 
			memcpy( &ulKey2, (unsigned char *)(key2)+iOff, iTam); 
			return (int) (ulKey1 - ulKey2); 
		}
		break;
	default:
		return 0;
	}

	return (dbRet > 0) ? 1 : ((dbRet < 0) ? -1 : 0);
}

void *Comparator::BuildKey( void **keycomponents )
{
//
// Monta uma chave baseado nos componentes contidos no vetor "keycomponents"
// 
	int i, j;
	i = j = 0;
	char *key;
	
	if( BuildStatus != PARSEOK )
		return NULL;

	// primeiro alocar o tamanho necessário para a montagem da chave.

	key = new char[ KeySize ];
	if( !key ) return NULL;

	memset( key, 0, KeySize );

	// Área alocada com sucesso.
	
	// Colocar as chaves

	for( i=0, j=0; i<NumbOfKeys; ++i, ++j ) {
		if( keycomponents[j] == NULL ) {
			continue;
		}

		int iOff = KeyCtl[i].offset;
		int iTam = KeyCtl[i].tamanho;

		if ( KeyCtl[i].tipo == STRING && KeyCtl[i].fixos ) {
			memcpy( key+iOff, KeyCtl[i].fixos, iTam );
		}
		else {
			memcpy( (unsigned char *)(key)+iOff, 
						(unsigned char *)keycomponents[j], iTam);
		}
/**
		switch( KeyCtl[i].tipo )
		{
		case UCHAR:
			*(unsigned char *)(key+KeyCtl[i].offset) = *(unsigned char *)keycomponents[j];
			++j;
			break;

		case FLOAT:
			*(float *)(key+KeyCtl[i].offset) = *(float *)keycomponents[j];
			++j;
			break;

		case DOUBLE:
			*(double *)(key+KeyCtl[i].offset) = *(double *)keycomponents[j];
			++j;
			break;

		case LONGINT:
			*(long *)(key+KeyCtl[i].offset) = *(long *)keycomponents[j];
			++j;
			break;

		case ULONG:
			*(unsigned long *)(key+KeyCtl[i].offset) = *(unsigned long *)keycomponents[j];
			++j;
			break;

		case SHORT:
			*(short *)(key+KeyCtl[i].offset) = *(short *)keycomponents[j];
			++j;
			break;

		default:  // Só sobrou string
			if( KeyCtl[i].fixos )
//				strncpy( key+KeyCtl[i].offset, KeyCtl[i].fixos, KeyCtl[i].tamanho );
				// ADRIANO:
				memcpy( key+KeyCtl[i].offset, KeyCtl[i].fixos, KeyCtl[i].tamanho );
			else
			{
//				memcpy( key+KeyCtl[i].offset, (char *)keycomponents[j], strlen((char *)keycomponents[j]) );
				// ADRIANO:
				memcpy( key+KeyCtl[i].offset, (char *)keycomponents[j], KeyCtl[i].tamanho );
				++j;
			}
			break;
		}
*****/
	}

	return (void *) key;

}


Comparator::Comparator( void )
{
//
// Construtor que não recebe descritor.
//

	BuildStatus = PREMATUREEND;
	NumbOfKeys = 0;

	return;

}

Comparator::Comparator( char *descritor )
{
//
// Construtor que recebe descritor.
//
	SetDescriptor( descritor );

	return;

}

int Comparator::SetDescriptor( char *descritor )
{
//
// Simplesmente faz o parsing da string descritora
//
// Recebe apenas a string de descrição da composição da chave, de
// acordo com o formato previamente estabelecido.
//

	int i,j,k,l;

	char fixos[132];

	killfixos();

	i = NumbOfKeys = l = 0;
	NumbOfKeys = 0;
	while( descritor[i] )
	{
		j = 0;
		KeyCtl[ NumbOfKeys ].fixos = NULL;
		// Para constantes
		k = i;
		while( descritor[i] && descritor[i] != '%' )
		{
			if( descritor[i] == '\\' )
				memcpy( descritor+i, descritor+i+1, strlen( descritor+i+1 ) );
			++j;++i;
		} 
		if( j )   // Achou uma constante
		{
			KeyCtl[ NumbOfKeys ].tipo = STRING;
			KeyCtl[ NumbOfKeys ].tamanho = j;
			KeyCtl[ NumbOfKeys ].comptype = NONE;
			strncpy( fixos, descritor+k, j );
			fixos[j]=0;
		}
		else        // Achou um tipo básico (%)
		{
			KeyCtl[ NumbOfKeys ].tamanho = 0;
			++i;
			if( isdigit(descritor[i]) )     // se tem repetidor ...
			{
				KeyCtl[ NumbOfKeys ].tamanho = atoi( descritor+i );
				while ( descritor[i] && isdigit(descritor[i]) ) ++i;
				if( !descritor[i] ||  // descritor terminou prematuramente 
					descritor[i] != 's') // Repetidor implica em tipo 's'

				{
					BuildStatus = PREMATUREEND;
					return 0;
				}
				KeyCtl[ NumbOfKeys ].tipo = STRING;
				KeyCtl[ NumbOfKeys ].comptype = NONE;
				KeyCtl[ NumbOfKeys ].offset = l;
			}

			// ver o tipo
			switch( descritor[i] )
			{
			case STRING:
				if( !KeyCtl[ NumbOfKeys ].tamanho )
				{
					BuildStatus = STRIGZEROSIZE;
					return 0;
				}
				KeyCtl[ NumbOfKeys ].tipo = STRING;
				break;

			case UCHAR:
				KeyCtl[ NumbOfKeys ].tamanho = 1;
				KeyCtl[ NumbOfKeys ].tipo = UCHAR;
				break;

			case FLOAT:
				KeyCtl[ NumbOfKeys ].tamanho = sizeof( float );
				KeyCtl[ NumbOfKeys ].tipo = FLOAT;
				break;

			case DOUBLE:
				KeyCtl[ NumbOfKeys ].tamanho = sizeof( double );
				KeyCtl[ NumbOfKeys ].tipo = DOUBLE;
				break;

			case SHORT:
				KeyCtl[ NumbOfKeys ].tamanho = sizeof( short int );
				KeyCtl[ NumbOfKeys ].tipo = SHORT;
				break;

			case LONGINT:
				KeyCtl[ NumbOfKeys ].tamanho = sizeof( long );
				KeyCtl[ NumbOfKeys ].tipo = LONGINT;
				break;

			case ULONG:
				KeyCtl[ NumbOfKeys ].tamanho = sizeof( unsigned long );
				KeyCtl[ NumbOfKeys ].tipo = ULONG;
				break;

			default:
				BuildStatus = UNKNOWNTYPE;
				return 0;
			}

			++i;
			// ver tipo de ordenação
			switch( descritor[i] )
			{
			case 0:
				KeyCtl[ NumbOfKeys ].comptype = NONE;
				break;

			case MAIOR:
				KeyCtl[ NumbOfKeys ].comptype = INCREASING;
				++i;
				break;

			case MENOR:
				KeyCtl[ NumbOfKeys ].comptype = DECREASING;
				++i;
				break;

			default:
				KeyCtl[ NumbOfKeys ].comptype = NONE;	// ADRIANO
				break;
			}

		}

		KeyCtl[ NumbOfKeys ].offset = l;
		l += KeyCtl[ NumbOfKeys ].tamanho;
		int resto = l%sizeof(DWORD);
		if( resto ) 
		{
			l += sizeof(DWORD);
			resto = l/sizeof(DWORD);
			l = resto*sizeof(DWORD);
		}
		if( j )
		{
			KeyCtl[ NumbOfKeys ].fixos = new char[j+1];
			strcpy( KeyCtl[ NumbOfKeys ].fixos, fixos );
		}
      else
         KeyCtl[ NumbOfKeys ].fixos = NULL;

		++NumbOfKeys;
	}

	BuildStatus = PARSEOK;

	// Calcular o tamanho da chave, para manter já calculado.

	KeySize = KeyCtl[ NumbOfKeys-1 ].offset+KeyCtl[ NumbOfKeys-1 ].tamanho;

	return KeySize;
}

Comparator::~Comparator( void )
{
//
// Destrutor
//

	killfixos();
	return;
}

void Comparator::killfixos( void )
{
//
// Deleta as constantes que vieram no descritor como parte da chave.
//

	if( NumbOfKeys )
		for( int i = 0; i<NumbOfKeys; ++i )
			if(KeyCtl[ i ].fixos) 
				delete KeyCtl[ i ].fixos;

	return;
}

void Comparator::verdados( void *key1, int pos )
{
//
// Função para depuração
//

 	///////
	char *ss;
	int ii;
	float ff;
	double db;
	long ll;
	unsigned long ul;
	unsigned char bb;
	/////

	int start = 0, end = NumbOfKeys;

	if( pos != -1 )
	{
		start = pos;
		end = pos+1;
	}

    for( int i = start; i<end; ++i )
	{
		switch( KeyCtl[i].tipo )
		{
		case STRING:
			ss = (char *)(key1)+KeyCtl[i].offset;
			break;

		case UCHAR:
			bb   = *((unsigned char *)(key1)+KeyCtl[i].offset);
			break;

		case SHORT:
			ii = *((short *)((char *)(key1)+KeyCtl[i].offset));
			break;

		case FLOAT:
			ff = *((float *)((char *)(key1)+KeyCtl[i].offset));
			break;

		case DOUBLE:
			db = *((double *)((char *)(key1)+KeyCtl[i].offset));
			break;

		case LONGINT:
			ll = *((long *)((char *)(key1)+KeyCtl[i].offset));
			break;

		case ULONG:
			ul = *((unsigned long *)((char *)(key1)+KeyCtl[i].offset));
			break;

		}
    }

	return;
}
