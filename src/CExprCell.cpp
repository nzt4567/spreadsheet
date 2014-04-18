/* 
 * File:   CExprCell.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 18, 2012, 11:11 PM
 */
#include <string>
#include "exceptions.h"
#include "CExprCell.h"
#include "CExprParser.h"

                        CExprCell::CExprCell          ( CCursor*               _cursor, 
                                                        const TListDimensions* _list, 
                                                        const std::string&     _input ) : 
                          CExtendedCell(_cursor, _list, _input) { m_type = EXPRCELL; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                        CExprCell::~CExprCell         () {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                    CExprCell::AmIExpr            () const { return true;  }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                    CExprCell::AmINum             () const { return false; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                    CExprCell::AmIString          () const { return false; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                    CExprCell::DoIPointToThisCell ( const std::string&  _cell, 
                                                        CSparseArray*       _array )
{ /* This should find the cycle always && always, but it isn't perfect for multiple cycling - marks first cycle and quits */
    size_t found;
    found = m_input.find(_cell);
    
    if ( found != std::string::npos )
        return true;
    
    TParserParams params = { m_input, _array };
    CExprParser*  temp   = new CExprParser(params, _cell);
    
    bool   what = temp->CheckInput();
    delete temp;
    
    return what;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CExprCell::Evaluate           ( CSparseArray*       _array )
{
    TParserParams params   = { m_input, _array };
                  m_parser = new CExprParser(params, m_index);
    EVALUATE
    delete m_parser;
}