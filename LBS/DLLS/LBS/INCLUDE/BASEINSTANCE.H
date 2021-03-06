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