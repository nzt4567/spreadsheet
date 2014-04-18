/* 
 * File:   CStringParser.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 24, 2012, 3:13 PM
 */
#include <string>
#include "CStringParser.h"

                                CStringParser::CStringParser  ( TParserParams& _params ) : 
                                     CParser(_params) {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                CStringParser::~CStringParser () {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                            CStringParser::CheckInput     ()
{
    std::string noWhiteSpace = SkipWhiteSpace();
    
    if ( noWhiteSpace[0] == '"' && noWhiteSpace[noWhiteSpace.length() - 1] == '"' )
        PARSER_SUCCESS;
    PARSER_ERROR
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
std::string                     CStringParser::ParseInput     () 
{ 
    return m_parser.m_input; 
}