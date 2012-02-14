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
// Module: USERDEFS.H
//	Defines several macros
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last revision: 28/10/95
//

#ifndef	_USERDEFS_H_
#define	_USERDEFS_H_

#ifndef	_DATECL_H_
#include	<datecl.h>
#endif
#ifndef _CONST
#include	<const.h>
#endif


// Tipos de base
// Alterar a ordem/valor dessas macros pode ser perigoso. Consulte
// a equipe de desenvolvimento do LBS para esclarecimentos
#define BASE_PRIVATE            	0x00
#define	BASE_PUBLIC			0x01
#define	BASE_PUBLIC_REC_PRIVATE		0x02
#define	BASE_PRIVATE_REC_PRIVATE	0x03
#define	USER_BASE			0x10

// tipos de campo
#define	VALUE_FIELD			0	// long
#define	DVALUE_FIELD		1	// double
#define	ALPHA_FIELD			2	// char[] - tam tamanho limitado
#define	TEXT_FIELD			3	// char * - nao tem limite de tamanho
#define	BINARY_FIELD		4	// binario
#define	DATE_FIELD			5	// data
#define	TIME_FIELD			6	// hora
#define	REFERENCED_FIELD	7	// campo com referência para documentos
#define	BYTE_FIELD			8	// byte
#define	SINT_FIELD			9	// short int
#define	FLOAT_FIELD			10	// float

// tamanhos de campo
#define	DATEFIELDSIZE			( sizeof( JulTy ) )
#define	TIMEFIELDSIZE			( sizeof( ClockTy ) )
#define	VALUEFIELDSIZE			( sizeof( long ) )
#define	LVALUEFIELDSIZE			( sizeof( double ) )

// Iníco código Katyusco
// Definições dos tamanhos máximos para as partes decimal e inteira. Representa o tamanho maximo
// de uma chave para os valores do tipo moeda ou decimal de sistema de indice da base.
#define DECIMAL_PART	10
#define INTEGER_PART	18
// Fim código Katyusco

// This defines are for the Add method (list)
#define	AFTER			1
#define	BEFORE			2
#define	HEAD			3
#define	TAIL			4
#define	ASC_ORDER		5
#define	DESC_ORDER		6

// This defines are for the Search method (list)
#define	SEARCH_EQUAL	1
#define	SEARCH_LESS	2
#define	SEARCH_GREAT	4

// tipos de usuario
#define MASTER_USER	1
#define USUAL_USER	2
#define	NOP_USER	3

// tipos de indexacao
#define	TOTAL_INDEX	0
#define	PARTIAL_INDEX	1

// Mascaras para indexacao

#define ALLINDEX	( WORDTREE |		\
					  BACKTREE |		\
					  VALUETREE |		\
					  DATETREE |		\
					  TIMETREE |		\
					  SOUNDTREE |		\
					  UNIQUETREE |		\
					  ENTIRETREE |		\
					  EMPTYTREE )

// Valores default
#define	DEFAULTUSERBASE		"DEFUDB"
#define	DEFAULTOCLISTNAME	"OCLIST"

// tamanhos de campos para uma UDB
#define	USERNAMESIZE			32
#define	GROUPNAMESIZE			15
#define	DESCRIPTIONSIZE			64
#define	PASSWORDSIZE			10
#define	ADDRESSSIZE				100
#define	PHONESIZE				20

// tamanho de um nome para componente
#define	COMPONENTNAMESIZE		64

// mascaras de permissoes para ACL's
#define ACL_NONE		(0x00)
#define ACL_READ		(0x01)
#define ACL_WRITE		(0x02)
#define ACL_APPEND		(0x04)
#define ACL_DEL			(0x08)
#define ACL_ADM			(ACL_READ | ACL_WRITE | ACL_APPEND | ACL_DEL)
#define ACL_RD_WR		(ACL_READ | ACL_WRITE)
#define ACL_WR_APP		(ACL_WRITE | ACL_APPEND)
#define ACL_RW_APP		(ACL_READ | ACL_WRITE | ACL_APPEND)
#define	ACL_ASTERISK	(0xFE)	// indica que a consulta deve retornar OK se encontrar qualquer ACL

// identificador especial para campos
#define	ID_ASTERISK		(-1)
#define	SZID_ASTERISK	"*"
// identificador especial para indicar permissao de base
#define	ID_BASE			(-2)
// nome especial para representar todos os usuarios/grupos
#define	NAME_ASTERISK		"*"

// acl especial para pesquisas
#define	ACL_BEST		(0xFF)	// indica que a consulta deve retornar a melhor permissao possivel

// tamanho da string de informacoes para progress control
#define	OPINFOSIZE		80


// tipos de campo para REFERENCED_FIELD
#define	LBSRT_URL		100
#define	LBSRT_WORD		200


// possiveis estados para um field
#define	NULL_ATTRIB		(0x00)	// nenhum atributo especial setado
#define	DELETED_FIELD	(0x01)	// indica um campo deletado
#define	ASC_ORD_FIELD	(0x02)	// indica um campo com ordenacao ascendente de repeticoes
#define	DESC_ORD_FIELD	(0x04)	// indica um campo com ordenacao descendente de repeticoes
								// (ASC_ORD_FIELD E DESC_ORD_FIELD nao devem ser combinados - sao exclusivos)

// tamanho maximo de um nome de um grupo de campos multivalorados
#define	FIELDGROUPNAMESIZE	(128)

// macro para comparacao de grupo
#define	CMP_GRUPO			1


#endif	// _USERDEFS_H_

