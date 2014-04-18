/* 
 * File:   CNumCell.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 18, 2012, 11:10 PM
 */
#include <string>
#include "exceptions.h"
#include "CNumCell.h"
#include "CNumParser.h"

                        CNumCell::CNumCell  ( CCursor*               _cursor, 
                                              const TListDimensions* _list, 
                                              const std::string&     _input ) : 
                          CExtendedCell(_cursor, _list, _input) { m_type = NUMCELL; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                        CNumCell::~CNumCell () {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                    CNumCell::AmIExpr   () const { return false; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                    CNumCell::AmINum    () const { return true;  }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                    CNumCell::AmIString () const { return false; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CNumCell::Evaluate  ( CSparseArray* _array )
{
    TParserParams params = { m_input, _array };
    m_parser = new CNumParser(params);
    EVALUATE
    delete m_parser;    
}