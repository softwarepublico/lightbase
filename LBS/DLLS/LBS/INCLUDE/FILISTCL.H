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
// Module: FILISTCL.H
//	LBSC_FieldList class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last revision: 28/09/94
//


#ifndef	_FILISTCL_H_
#define	_FILISTCL_H_

//$$$class	LBSC_Field;

#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif
#ifndef	_FIELDCL_H_
#include	<fieldcl.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class _LBSCLASS LBSC_FieldList : public LBSC_DList<LBSC_Field>
{
	friend	class	_LBSCLASS LBSC_Base;
	friend	class	_LBSCLASS LBSC_Record;

	public:
				LBSC_FieldList() : LBSC_DList<LBSC_Field>(){};
				~LBSC_FieldList(){};
		int operator == ( LBSC_FieldList& aux )
		{
			if( NumElem() == 0 && aux.NumElem() == 0 ){
				return( 1 );
			}
			if( NumElem() != aux.NumElem() ){
				return( 0 );
			}
			aux.First();
			First();
#ifdef __BORLANDC__
#pragma warn -inl
#endif
			while( 1 ){
				if( Current()->Compare( aux.Current(), CMPFIELDSTRUCT ) != 0 ){
					return( 0 );
				}
				if( Next() == NULL ){
					break;
				}
				aux.Next();
			}
#ifdef __BORLANDC__
#pragma warn +inl
#endif
			return( 1 );
		}
};

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif // _FILISTCL_H_

