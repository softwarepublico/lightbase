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


#ifndef	_CKEYSTRUCT_H_
#define	_CKEYSTRUCT_H_


class C_KeyStruct
{
public:
	char	*szKey;
	int		iNumber;
	BOOL	bCheckKey;

	C_KeyStruct()
	{
		szKey = NULL;
		iNumber = 0;
		bCheckKey = TRUE;
	}
	C_KeyStruct( char *szKeyPar, int iNumberPar )
	{
		szKey = new char [ strlen( szKeyPar ) + 1 ];
		if( szKey ){
			strcpy( szKey, szKeyPar );
		}
		iNumber = iNumberPar;
		bCheckKey = TRUE;
	}
	~C_KeyStruct()
	{
		if( szKey ){
			delete szKey;
		}
	}
	int	Compare( C_KeyStruct *pOther, int iType )
	{
		if( pOther ){
			switch( iType ){
			case 0:
				// pode ser 1 ou 2, dependendo de bCheckKey
				if( bCheckKey ){
					return( stricmp( szKey ? szKey : "", pOther->szKey ? pOther->szKey : "" ) );
				}
				return( iNumber == pOther->iNumber ? 0 : iNumber > pOther->iNumber ? 1 : -1 );

			case 1:
				return( stricmp( szKey ? szKey : "", pOther->szKey ? pOther->szKey : "" ) );
				
			case 2:
				return( iNumber == pOther->iNumber ? 0 : iNumber > pOther->iNumber ? 1 : -1 );
			}
		}
		return( 0 );
	}
	C_KeyStruct	*Duplicate()
	{
		return( NULL );
	}
};


#endif	// _CKEYSTRUCT_H_

