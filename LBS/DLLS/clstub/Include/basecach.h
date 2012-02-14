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
//	Definicao das estruturas de cache para o cliente e o servidor
//
//	Vladimir Catao - 29.11.96
//
//

#ifndef	_BASECACH_H_
#define _BASECACH_H_

#ifndef	_ACLLIST_H_
	#include <acllist.h>
#endif

#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif

#ifndef	_BUFFERCL_H_
#include <buffercl.h>
#endif

#ifndef	_DDECLIENT_OCCURRENCE_H_
#include <occurcl.h>
#endif

#ifdef _TESTE
#define private		public
#define protected	public
#endif

// macro para retorno int dos métodos de cache; deve setar o last error
#define CLRETURN(x)		pOwnerBase->SetLastError( x );	\
						return ( x );


class LBSC_Ticket;

// minimo de tentativas GENERICO para se aceitar um acesso a cache
#define MINGENERALCACHE_TENTAT	3	

// minimo de tentativas PARA A CLASSE DE REPETICOES para se aceitar 
// um acesso a cache
#define MINREPCACHE_TENTAT	2

class _LBSCLASS CCache {
	friend void AlocaBasicCache( CCache * );

	friend void SetaMaxLong( CCache * );

protected:
	void *pCache;	// deve ser acessado pelas subclasses via casts 
	LBSC_Base *pOwnerBase;
	long lTentat;
	long lMinTentat;

public:
	CCache( LBSC_Base *pBase );
	void InvalidaCache();
	BOOL IsCacheValid();
	virtual BOOL UsandoCache();
	virtual void AtualizaCache(){};
	virtual void DeleteCache(){};
	BOOL PodeUsarCache();
};

class _LBSCLASS CACL_Cache: public CCache {
public:
	CACL_Cache( LBSC_Base *pBase ) : CCache( pBase ) {}
	~CACL_Cache();
	void AtualizaCache();
	void DeleteCache();
	int GetACLPerm_Cache( char *szName, long lId, int iList, BOOL = TRUE );
	BOOL UsandoCache();
};

class RepInfo {
public:
	void	*pvRep;
	long	lMaxSize;
	long	lCurSize;

	RepInfo();
	~RepInfo();
	void FreeRepetition();
};

class FieldInfo {
public:
	UINT uiId;			// id 
	BYTE bFieldType;		// tipo 
	char szFieldName[FIELDNAMESIZE];	// nome 
	long lNumRep;
	RepInfo	*pRepetitions;
	BOOL bValid;

	FieldInfo();
	~FieldInfo();
	void FreeRepetitions();
};

class FieldInfoAux {
public:
	char szFieldName[FIELDNAMESIZE];	// nome 
	long lPos;

	FieldInfoAux();
};

class _LBSCLASS CRep_Cache: public CCache {
private:
	TRecordBufferHeader	*pRecordFieldsHeader;
	long				lNumFieldsInHeader;
	FieldInfoAux		*pFieldInfoAux;
	FieldInfo			*pFieldInfoById;
	long				lNumFieldsInBase;
	long				lRecNum;

	FieldInfo			*GetFieldFromAlias( char *szAlias );
	FieldInfo			*GetFieldFromId( UINT uId );
	BOOL				GetRepetition(int iRep, FieldInfo *pField, void *pvRep, long *plRepSize );
	BOOL				Read(FieldInfo *pField, int iRep);

public:
	CRep_Cache(LBSC_Base *);
	~CRep_Cache();
	void AtualizaCache();
	void DeleteCache();
	BOOL UsandoCache();
	void AtualizaSvcContext();
	int GetFieldRepetition_Cache( void *, int ,	void *, BOOL, BYTE );
	int GetNumberOfRepetition_Cache(void *, BOOL );
	long GetFieldRepetitionSize_Cache(void *, int, BOOL );
	long GetOLRecNumber_Cache( const LBSC_Ticket * );
	void SetFieldsInfo( TField * );
};


class _LBSCLASS CFieldSlot_Cache: public CCache {
private:

public:
	CFieldSlot_Cache(LBSC_Base *);
	~CFieldSlot_Cache();
	void AtualizaCache();
	BOOL UsandoCache();
	void DeleteCache();
	int GetFieldSlot_Cache( UINT , void * );
	long GetFieldSlotSize_Cache( UINT );
};


class _LBSCLASS COccur_Cache: public CCache {
private:

public:
	COccur_Cache(LBSC_Base *);
	~COccur_Cache();
	void AtualizaCache();
	BOOL UsandoCache();
	void DeleteCache();
	LBSC_Occurrence *GetNextOccurrence_Cache( );
	LBSC_Occurrence *GetPreviousOccurrence_Cache( );
	LBSC_Occurrence *GetCurrentOccurrence_Cache( );
	LBSC_Occurrence *GetFirstOccurrence_Cache( );
	LBSC_Occurrence *GetLastOccurrence_Cache( );
	LBSC_Occurrence *GetNthOccurrence_Cache( long lPos );
};

#endif // _BASECACH_H_
