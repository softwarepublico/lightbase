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

#include <baseinstance.h>


BaseInstance::BaseInstance( char *DirPar, char *BaseNamePar, BOOL ReadOnlyPar )
{
	BaseName = strdup(BaseNamePar);
	Dir = strdup(DirPar);
	ReadOnly = ReadOnlyPar;
	Indexes = NULL;
	StopWordVect = NULL;
	MinKeySize = -1;
	ACLLists = NULL;
	DataFile = NULL;
	strLogFieldAliasName = "";
	szExcludeModulesFromLog = "";
	szFieldsForUpdateLog = "";
	iOperationLogMask = 0;
}

BOOL
BaseInstance::OpenDataFile()
{
	if ( !BaseName || !Dir ) {
		return FALSE;
	}

	CLBAutoRegCrit	AutoRegCrit( &DataFileCritSect );

	if ( !DataFile ) {
		char	szAux[ FILENAMESIZE ];
		sprintf( szAux, "%s\\%s%s", (char*) Dir, (char*)BaseName, REPETITIONFILEEXT );
		DataFile = new CPageFile(szAux, ReadOnly);

		if ( !DataFile ) {
			return FALSE;
		}
	}

	if ( DataFile->IsOpen() ) {
		return TRUE;
	}

	return DataFile->Open();
}

BaseInstance::~BaseInstance()
{
	if ( BaseName ) {
		free(BaseName);
	}

	if ( Dir ) {
		free(Dir);
	}

	InvalidateAll();
}

int 
BaseInstance::Compare (BaseInstance *Other)
{
	return stricmp( Dir, Other->Dir );
}

BOOL BaseInstance::DataFileLoaded()
{
	CLBAutoRegCrit	AutoRegCrit( &DataFileCritSect );
	return ( DataFile && DataFile->IsOpen() );
}

void BaseInstance::InvalidateDataFile()
{
	CLBAutoRegCrit	AutoRegCrit( &DataFileCritSect );
	if ( DataFile ) {
		delete DataFile;
	}
	DataFile = NULL;
}

BOOL 
BaseInstance::BaseStructLoaded()
{
	// protegendo a manipulacao da lista de campos
	CLBAutoRegCrit	AutoRegCrit( &FieldListCritSect );

	return ( StopWordVect && (lbscflFieldList.NumElem() > 0) && (MinKeySize > 0) );
}

void 
BaseInstance::InvalidateBaseStruct()
{
	// protegendo a manipulacao da lista de campos
	CLBAutoRegCrit	AutoRegCrit( &FieldListCritSect );

	if ( StopWordVect ) {
		delete StopWordVect;
	}
	StopWordVect = NULL;
	lbscflFieldList.DelAll();
	MinKeySize = -1;
	strLogFieldAliasName = "";
	szExcludeModulesFromLog = "";
	szFieldsForUpdateLog = "";
	iOperationLogMask = 0;
}

BOOL 
BaseInstance::ACLsLoaded()
{
	return ( ACLLists != NULL );
}

void 
BaseInstance::InvalidateACLs()
{
	CLBAutoRegCrit	AutoRegCrit( &AclListCritSect );

	if ( ACLLists ) {
		delete ACLLists;
	}
	ACLLists = NULL;
}

BOOL 
BaseInstance::IndexesLoaded()
{
	return ( Indexes != NULL );
}

void 
BaseInstance::InvalidateIndexes()
{
	if ( Indexes ) {
		Indexes->Close();
		delete Indexes;
	}
	Indexes = NULL;
}

void 
BaseInstance::InvalidateAll()
{
	InvalidateDataFile();
	InvalidateIndexes();
	InvalidateBaseStruct();
	InvalidateACLs();
}


/////////////////////////////////////////////////////////////////////////

BaseInstanceManager::BaseInstanceManager()
{
	BaseInstances = new LTC_HASHTAB<BaseInstance>;
	if ( BaseInstances ) {
		BaseInstances->AllocTab(BIGPRIMO);
	}
}

BaseInstanceManager::~BaseInstanceManager()
{
	if ( BaseInstances ) {
		delete BaseInstances;
	}
}


BOOL 
BaseInstanceManager::Add( BaseInstance *NewInstance )
{
	if ( !BaseInstances ) {
		return FALSE;
	}

	CLBAutoRegCrit	AutoRegCrit( &HashCritSect );

	if ( BaseInstances->Search( NewInstance, (char *)(NewInstance->GetDir()) ) ) {
		return FALSE;
	}

	return (BaseInstances->Add( NewInstance, (char *)(NewInstance->GetDir())) != NULL );
}

BaseInstance *
BaseInstanceManager::Search( char *Dir )
{
	if ( !BaseInstances ) {
		return NULL;
	}

	CLBAutoRegCrit	AutoRegCrit( &HashCritSect );

	BaseInstance FindObj( Dir, NULL, FALSE );
	BaseInstance *FoundObj = BaseInstances->Search( &FindObj, (char *)(FindObj.GetDir()) );
	return FoundObj;
}


