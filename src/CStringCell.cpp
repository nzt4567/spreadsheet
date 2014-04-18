/* 
 * File:   CStringCell.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 18, 2012, 11:11 PM
 */
#include <string>
#include "exceptions.h"
#include "CStringCell.h"
#include "CStringParser.h"

                        CStringCell::CStringCell  ( CCursor*                _cursor, 
                                                    const TListDimensions*  _list, 
                                                    const std::string&      _input ) : 
                           CExtendedCell(_cursor, _list, _input) { m_type = STRINGCELL; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                        CStringCell::~CStringCell () {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                    CStringCell::AmIExpr      () const { return false; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                    CStringCell::AmINum       () const { return false; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                    CStringCell::AmIString    () const { return true;  }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CStringCell::Evaluate     ( CSparseArray* _array )
{
    TParserParams params = { m_input, _array};
    m_parser = new CStringParser(params);
    EVALUATE
    delete m_parser;
}