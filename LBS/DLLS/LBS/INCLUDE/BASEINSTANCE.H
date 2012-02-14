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

#ifndef	_BASEINSTANCE_H_
#define	_BASEINSTANCE_H_


#include <regcrit.h>
#include <machine.h>
#include <hashtab.h>
#include <LB4Struct.h>
#include <FILISTCL.h>
#include <IndexManager.h>
#include <acllist.h>

#define BIGPRIMO		100003


class BaseInstance {
	char		*Dir;
	char		*BaseName;	
	CPageFile	*DataFile;
	BOOL		ReadOnly;

public:
	CLBRegCrit	DataFileCritSect;
	CLBRegCrit	FieldListCritSect;
	CLBRegCrit	AclListCritSect;
	LBSC_FieldList			lbscflFieldList;
	IndexInfo	*Indexes;
	int			MinKeySize;
	LTC_TERMVECT *StopWordVect;
	TACL_Lists	*ACLLists;
	CL_StringN<FIELDNAMESIZE>	strLogFieldAliasName;	// alias do campo que deve ir para o log de uso.
	int							iOperationLogMask;		// mascara para as operacoes para as quais se quer log de uso
	CL_StringN<FULLNAMESIZE>	szExcludeModulesFromLog;	// modulos a serem excluidos da geracao de log de uso, mesmo com a mascara setada
	CL_StringN<FULLNAMESIZE>	szFieldsForUpdateLog;	// campos para os quais se deve gerar log dos valores anteriores aa alteracao


	BaseInstance( char *Dir, char *BaseName, BOOL ReadOnly );
	~BaseInstance();
	BOOL OpenDataFile();
	const char *GetDir() { return Dir;};
	CPageFile *GetDataFile() { return DataFile; };
	int Compare (BaseInstance *pOther);

	BOOL DataFileLoaded();
	void InvalidateDataFile();
	BOOL BaseStructLoaded();
	void InvalidateBaseStruct();
	BOOL IndexesLoaded();
	void InvalidateIndexes();
	BOOL ACLsLoaded();
	void InvalidateACLs();

	void InvalidateAll();
};

class BaseInstanceManager {
	CLBRegCrit					HashCritSect;
	LTC_HASHTAB<BaseInstance>	*BaseInstances;

public:
	BaseInstanceManager();
	~BaseInstanceManager();
	BOOL Add( BaseInstance * );
	BaseInstance *Search( char *Dir );
};

#endif	_BASEINSTANCE_H_