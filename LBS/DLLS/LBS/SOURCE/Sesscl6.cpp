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
// Module: SESSCL6.CPP
// Description:
//
//	Methods file for session handling.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 09/12/96
//


#ifndef __BORLANDC__
#pragma warning(disable:4270)
#endif

#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_SESSLIST_H_
#include	<sesslist.h>
#endif
#ifndef	_CSTRTOK_H_
#include	<cstrtok.h>
#endif

// para controle de invalidacao de licencas
extern	BOOL	_bInvalidLicence;

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo CreateBase
	Cria uma base no disco a partir de um arquivo recebido

	Parameters:
		- plbscTicketPar		-> ticket de seguranca
		- szEspecificationFileName

	Return:
		- LBS_OK se conseguir criar a base ou erro.

	Comments:
		- O metodo retorna erro se ja existir uma base com mesmo nome
		  no servidor.

***/
int
LBSC_Session::CreateBase( const LBSC_Ticket *plbscTicketPar, char *szEspecificationFileName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::CreateBase") );
	BYTE		bBaseType;
	int		iNumberOfSlots;
	int		iNumberOfCounters;
	int		iMaxKeySize;
	int		iNumFields;
	BOOL		bEncrypt;
	CL_StringN<200>	szTmp;
	char		szFullBaseName[ FULLNAMESIZE ];
	char		szBasePassword[ BASEPASSWORDSIZE ];
	char		szMaintenancePassword [ MAXMAINTENANCEPASS ];
	char		szUserBaseName[ FULLNAMESIZE ];
	char		*szToken;

	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	// Testar se o arquivo existe
        if( !C_File::Exist( szEspecificationFileName ) ){
        	ERETURN( LBSE_ERROR );
        }

	// Cabecalho da base
	GetPrivateProfileString( BASE_HEADER_SESSION, NAME_KEY, "", szFullBaseName, FULLNAMESIZE, szEspecificationFileName );
	if( PROFILE_ERROR( szFullBaseName ) ){
        	ERETURN( LBSE_ERROR );
	}
	GetPrivateProfileString( BASE_HEADER_SESSION, PWD_KEY, "", szBasePassword, BASEPASSWORDSIZE, szEspecificationFileName );
	GetPrivateProfileString( BASE_HEADER_SESSION, MPWD_KEY, "", szMaintenancePassword, MAXMAINTENANCEPASS, szEspecificationFileName );

	// Tipo da base
	GetPrivateProfileString( BASE_HEADER_SESSION, TYPE_KEY, "", (char*) szTmp, 200, szEspecificationFileName );
	if( PROFILE_ERROR( szTmp ) ){
		ERETURN( LBSE_ERROR );
	}

    bBaseType = (szTmp == (char*) "USER_BASE") ? USER_BASE :
		(szTmp == (char*) "BASE_PRIVATE") ? BASE_PRIVATE :
		(szTmp == (char*) "BASE_PUBLIC_REC_PRIVATE") ? BASE_PUBLIC_REC_PRIVATE :
		(szTmp == (char*) "BASE_PRIVATE_REC_PRIVATE") ? BASE_PRIVATE_REC_PRIVATE : BASE_PUBLIC;

	// O numero de slots
	iNumberOfSlots = GetPrivateProfileInt( BASE_HEADER_SESSION, SLOTNUM_KEY, 0, szEspecificationFileName );

	// o numero de contadores
	iNumberOfCounters = GetPrivateProfileInt( BASE_HEADER_SESSION, COUNTNUM_KEY, 0, szEspecificationFileName );

	// tamanho maximo de uma chave no sistema de indices
	iMaxKeySize = GetPrivateProfileInt( BASE_HEADER_SESSION, MAXKEYSIZE_KEY, 0, szEspecificationFileName );

	// Criptografada/nao
	GetPrivateProfileString( BASE_HEADER_SESSION, ENCRYPT_KEY, "", (char*) szTmp, 200, szEspecificationFileName );
	if( PROFILE_ERROR( szTmp ) ){
        	ERETURN( LBSE_ERROR );
	}
	bEncrypt = (szTmp == (char*) "TRUE");

	// Nome da base de usuarios
	GetPrivateProfileString( BASE_HEADER_SESSION, UDB_KEY, "", szUserBaseName, FULLNAMESIZE, szEspecificationFileName );

	// Numero de campos
	iNumFields = GetPrivateProfileInt( BASE_HEADER_SESSION, NUMFIELDS_KEY, 0, szEspecificationFileName );
        if( iNumFields == 0 ){
		ERETURN( LBSE_ERROR );
        }

	// $$$ Instanciar lista de campos
	TField	*ptfField = new TField [ iNumFields + 1 ];
	if( !ptfField ){
		ERETURN( LBSE_NOMEMORY );
	}

        // Montar a lista de campos
	for( int i = 0; i < iNumFields; i++ ){
                char		szSection[ 200 ];

        	sprintf( szSection, "%s_%d", FIELD_KEY, i );

                GetPrivateProfileString( szSection, FIELDNAME_KEY, "", (char*) (ptfField [ i ].szFieldAliasName), FIELDNAMESIZE, szEspecificationFileName );
		if( PROFILE_ERROR( ptfField [ i ].szFieldAliasName ) ){
	        	delete ptfField;
	        	ERETURN( LBSE_ERROR );
	        }
		GetPrivateProfileString( szSection, FIELDDESC_KEY, "", (char*) (ptfField [ i ].szFieldDescription), DESCRIPTIONSIZE, szEspecificationFileName );
		GetPrivateProfileString( szSection, FIELDPWD_KEY, "", (char*) (ptfField [ i ].szPasswordName), FIELDPASSWORDSIZE, szEspecificationFileName );
               	GetPrivateProfileString( szSection, FIELDTYPE_KEY, "", (char*) szTmp, 200, szEspecificationFileName );
		if( PROFILE_ERROR( szTmp ) ){
	        	delete ptfField;
	        	ERETURN( LBSE_ERROR );
	        }
		ptfField [ i ].tftFieldType = (szTmp == (char*) "VALUE_FIELD") ? VALUE_FIELD :
					      (szTmp == (char*) "DVALUE_FIELD") ? DVALUE_FIELD :
					      (szTmp == (char*) "DATE_FIELD") ? DATE_FIELD :
					      (szTmp == (char*) "TIME_FIELD") ? TIME_FIELD :
					      (szTmp == (char*) "ALPHA_FIELD") ? ALPHA_FIELD :
					      (szTmp == (char*) "REFERENCED_FIELD") ? REFERENCED_FIELD :
					      (szTmp == (char*) "BINARY_FIELD") ? BINARY_FIELD : TEXT_FIELD;

		ptfField [ i ].lFieldSize = (long) GetPrivateProfileInt( szSection, FIELDSIZE_KEY, 2, szEspecificationFileName );
		ptfField [ i ].uiFieldId = (UINT) GetPrivateProfileInt( szSection, FIELDID_KEY, 0, szEspecificationFileName );

               	GetPrivateProfileString( szSection, FIELDINDEX_KEY, "", (char*) szTmp, 200, szEspecificationFileName );
		ptfField [ i ].tiaIndexAttrib = 0;

		C_StrTok	cStrTok;

		szToken = cStrTok.StrTok( (char*) szTmp, " " );
		while( szToken ){
			if( strcmp( szToken, "WORDTREE" ) == 0 ){
				ptfField [ i ].tiaIndexAttrib |= WORDTREE;
			}else if( strcmp( szToken, "BACKTREE" ) == 0 ){
				ptfField [ i ].tiaIndexAttrib |= BACKTREE;
			}else if( strcmp( szToken, "VALUETREE" ) == 0 ){
				ptfField [ i ].tiaIndexAttrib |= VALUETREE;
			}else if( strcmp( szToken, "DATETREE" ) == 0 ){
				ptfField [ i ].tiaIndexAttrib |= DATETREE;
			}else if( strcmp( szToken, "TIMETREE" ) == 0 ){
				ptfField [ i ].tiaIndexAttrib |= TIMETREE;
			}else if( strcmp( szToken, "SOUNDTREE" ) == 0 ){
				ptfField [ i ].tiaIndexAttrib |= SOUNDTREE;
			}else if( strcmp( szToken, "REFERENCETREE" ) == 0 ){
				ptfField [ i ].tiaIndexAttrib |= REFERENCETREE;
			}else if( strcmp( szToken, "UNIQUETREE" ) == 0 ){
				ptfField [ i ].tiaIndexAttrib |= UNIQUETREE;
			}else if( strcmp( szToken, "ENTIRETREE" ) == 0 ){
				ptfField [ i ].tiaIndexAttrib |= ENTIRETREE;
			}
			szToken = cStrTok.StrTok( NULL, " " );
		}
	}
	if( i != iNumFields ){
		delete ptfField;
		ERETURN( LBSE_ERROR );
	}
	int iRet = CreateBase( plbscTicketPar, szFullBaseName, "",
				szBasePassword,
				szMaintenancePassword, bBaseType, bEncrypt,
				szUserBaseName, ptfField, iNumberOfSlots,
				iNumberOfCounters, iMaxKeySize );
	delete ptfField;;
	ERETURN( iRet );
}

/***
	PUBLIC
	Metodo ExportBaseFormat
	Exporta para um arquivo texto o formato de uma base

	Parameters:
		- plbscTicketPar		-> ticket de seguranca
		- pcbBase			-> apontador para uma base ja
						   aberta
		- szEspecificationFileName	-> nome de um arquivo a ser criado
						   por este metodo

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- O metodo retorna erro se ja existir um arquivo com o nome igual
		  ao szEspecificationFileName
		- As passwords (de base e de campo) NAO sao exportadas
                - O arquivo gerado possui formato semelhante aos .INI do WINDOWS

***/
int
LBSC_Session::ExportBaseFormat( const LBSC_Ticket *plbscTicketPar, LBSC_Base *pcbBase, char *szEspecificationFileName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::ExportBaseFormat") );
	int	iNumFields;
	char	szTmp[ 100 ];

	// $$$ Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	// $$$ Verifica a validade do ticket de seguranca
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	if( lbscblBaseList.Find( pcbBase, CMPBASEPOINTER ) == NULL ){
		ERETURN( LBSE_BASENOTOPEN );
	}

	// Testar se o arquivo existe
	if( C_File::Exist( szEspecificationFileName ) ){
		ERETURN( LBSE_FILEEXIST );
	}

	// Cabecalho da base
	if( !WritePrivateProfileString( BASE_HEADER_SESSION, NAME_KEY, (char *)pcbBase->szBaseName, szEspecificationFileName ) ){
		ERETURN( LBSE_ERROR );
	}
	if( !WritePrivateProfileString( BASE_HEADER_SESSION, PWD_KEY, "", szEspecificationFileName ) ){
		ERETURN( LBSE_ERROR );
	}
	if( !WritePrivateProfileString( BASE_HEADER_SESSION, MPWD_KEY, "", szEspecificationFileName ) ){
		ERETURN( LBSE_ERROR );
	}

	// Tipo da base
	switch ( pcbBase->GetBaseType() ){
	case BASE_PRIVATE:
		if( !WritePrivateProfileString( BASE_HEADER_SESSION, TYPE_KEY, "BASE_PRIVATE", szEspecificationFileName ) ){
			ERETURN( LBSE_ERROR );
		}
		break;
	case BASE_PUBLIC:
		if( !WritePrivateProfileString( BASE_HEADER_SESSION, TYPE_KEY, "BASE_PUBLIC", szEspecificationFileName ) ){
			ERETURN( LBSE_ERROR );
		}
		break;
	case BASE_PUBLIC_REC_PRIVATE:
                if( !WritePrivateProfileString( BASE_HEADER_SESSION, TYPE_KEY, "BASE_PUBLIC_REC_PRIVATE", szEspecificationFileName ) ){
			ERETURN( LBSE_ERROR );
                }
		break;
	case BASE_PRIVATE_REC_PRIVATE:
                if( !WritePrivateProfileString( BASE_HEADER_SESSION, TYPE_KEY, "BASE_PRIVATE_REC_PRIVATE", szEspecificationFileName ) ){
                        ERETURN( LBSE_ERROR );
                }
		break;
	case USER_BASE:
                if( !WritePrivateProfileString( BASE_HEADER_SESSION, TYPE_KEY, "USER_BASE", szEspecificationFileName ) ){
                        ERETURN( LBSE_ERROR );
                }
		break;
	}

	// O numero de slots
	itoa( pcbBase->GetNumberOfSlots(), szTmp, 10 );
	if( !WritePrivateProfileString( BASE_HEADER_SESSION, SLOTNUM_KEY, szTmp, szEspecificationFileName ) ){
		ERETURN( LBSE_ERROR );
	}

	// o numero de contadores
	itoa( pcbBase->GetNumberOfCounters(), szTmp, 10 );
	if( !WritePrivateProfileString( BASE_HEADER_SESSION, COUNTNUM_KEY, szTmp, szEspecificationFileName ) ){
		ERETURN( LBSE_ERROR );
	}

	// tamanho maximo de uma chave no sistema de indices
	itoa( pcbBase->LB1.tcrHead.iMaxKeySize, szTmp, 10 );
	if( !WritePrivateProfileString( BASE_HEADER_SESSION, MAXKEYSIZE_KEY, szTmp, szEspecificationFileName ) ){
		ERETURN( LBSE_ERROR );
	}

	// Criptografada/nao
	if( !WritePrivateProfileString( BASE_HEADER_SESSION, ENCRYPT_KEY, pcbBase->IsEncrypt() ? "TRUE" : "FALSE", szEspecificationFileName ) ){
        	ERETURN( LBSE_ERROR );
        }

	// Nome da base de usuarios
	if( !WritePrivateProfileString( BASE_HEADER_SESSION, UDB_KEY, (char *) pcbBase->LB1.tcrHead.szUserBase, szEspecificationFileName ) ){
        	ERETURN( LBSE_ERROR );
        }

	// Numero de campos
	iNumFields = pcbBase->lbscrCurrRecord.GetNumberOfFields();
        itoa( iNumFields, szTmp, 10 );
	if( !WritePrivateProfileString( BASE_HEADER_SESSION, NUMFIELDS_KEY, szTmp, szEspecificationFileName ) ){
        	ERETURN( LBSE_ERROR );
        }

        // Gravar todos os campos
        for( int i = 0; i < iNumFields; i++ ){
			LBSC_Field	*pcf = (*pcbBase)[ i ];
                char		szSection[ 100 ];
                char		szIndex[ 200 ];
		int		iIndexAtrrib;

       	sprintf( szSection, "%s_%d", FIELD_KEY, i );

        if( !WritePrivateProfileString( szSection, FIELDNAME_KEY, pcf->GetAliasName(), szEspecificationFileName ) ){
                ERETURN( LBSE_ERROR );
        }

        if( !WritePrivateProfileString( szSection, FIELDDESC_KEY, pcf->GetDescription(), szEspecificationFileName ) ){
                ERETURN( LBSE_ERROR );
        }

		if( !WritePrivateProfileString( szSection, FIELDPWD_KEY, "", szEspecificationFileName ) ){
			ERETURN( LBSE_ERROR );
		}

		switch( pcf->GetType() ){
		case VALUE_FIELD:
			if( !WritePrivateProfileString( szSection, FIELDTYPE_KEY, "VALUE_FIELD", szEspecificationFileName ) ){
				ERETURN( LBSE_ERROR );
			}
			break;
		case DVALUE_FIELD:
			if( !WritePrivateProfileString( szSection, FIELDTYPE_KEY, "DVALUE_FIELD", szEspecificationFileName ) ){
				ERETURN( LBSE_ERROR );
			}
			break;
		case DATE_FIELD:
                	if( !WritePrivateProfileString( szSection, FIELDTYPE_KEY, "DATE_FIELD", szEspecificationFileName ) ){
				ERETURN( LBSE_ERROR );
			}
			break;
		case TIME_FIELD:
                	if( !WritePrivateProfileString( szSection, FIELDTYPE_KEY, "TIME_FIELD", szEspecificationFileName ) ){
				ERETURN( LBSE_ERROR );
			}
			break;
		case ALPHA_FIELD:
                	if( !WritePrivateProfileString( szSection, FIELDTYPE_KEY, "ALPHA_FIELD", szEspecificationFileName ) ){
				ERETURN( LBSE_ERROR );
			}
			break;
		case TEXT_FIELD:
			if( !WritePrivateProfileString( szSection, FIELDTYPE_KEY, "TEXT_FIELD", szEspecificationFileName ) ){
				ERETURN( LBSE_ERROR );
			}
			break;
		case BINARY_FIELD:
			if( !WritePrivateProfileString( szSection, FIELDTYPE_KEY, "BINARY_FIELD", szEspecificationFileName ) ){
				ERETURN( LBSE_ERROR );
			}
			break;
		case REFERENCED_FIELD:
			if( !WritePrivateProfileString( szSection, FIELDTYPE_KEY, "REFERENCED_FIELD", szEspecificationFileName ) ){
				ERETURN( LBSE_ERROR );
			}
			break;
		}

		itoa( pcf->GetSize(), szTmp, 10 );
		if( !WritePrivateProfileString( szSection, FIELDSIZE_KEY, szTmp, szEspecificationFileName ) ){
			ERETURN( LBSE_ERROR );
		}

		itoa( pcf->GetId(), szTmp, 10 );
		if( !WritePrivateProfileString( szSection, FIELDID_KEY, szTmp, szEspecificationFileName ) ){
			ERETURN( LBSE_ERROR );
		}

		iIndexAtrrib = pcf->GetIndexAttrib();

		if( iIndexAtrrib & WORDTREE ){
			strcpy( szIndex, "WORDTREE" );
		}
		if( iIndexAtrrib & BACKTREE ){
			strcat( szIndex, " BACKTREE" );
		}
		if( iIndexAtrrib & VALUETREE ){
			strcat( szIndex, " VALUETREE" );
		}
		if( iIndexAtrrib & DATETREE ){
			strcat( szIndex, " DATETREE" );
		}
		if( iIndexAtrrib & TIMETREE ){
			strcat( szIndex, " TIMETREE" );
		}
		if( iIndexAtrrib & SOUNDTREE ){
			strcat( szIndex, " SOUNDTREE" );
		}
		if( iIndexAtrrib & REFERENCETREE ){
			strcat( szIndex, " REFERENCETREE" );
		}
		if( iIndexAtrrib & UNIQUETREE ){
			strcat( szIndex, " UNIQUETREE" );
		}
		if( iIndexAtrrib & ENTIRETREE ){
			strcat( szIndex, " ENTIRETREE" );
		}

		if( !WritePrivateProfileString( szSection, FIELDINDEX_KEY, szIndex, szEspecificationFileName ) ){
			ERETURN( LBSE_ERROR );
		}

	}
	ERETURN( LBS_OK );
}



