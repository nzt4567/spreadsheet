/* 
 * File:   CNumParser.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 24, 2012, 3:13 PM
 */
#include <string>
#include "CNumParser.h"

                        CNumParser::CNumParser  ( TParserParams& _params ) : 
                           CParser(_params) {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                        CNumParser::~CNumParser () {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                    CNumParser::CheckInput  ()
{
    std::string                 noWhiteSpace = SkipWhiteSpace();
    unsigned const int          inputLength  = noWhiteSpace.length();
    
    for (register unsigned int i = 0; i < inputLength; i++)
    {
        int k = noWhiteSpace[i];
        if ( (k >= '0' && k <= '9') || k == '+' || k == '-'  || k == '~' ||
              k == '*' || k == '/'  || k == '(' || k == ')'  || k == '.'  ) 
            continue;
        else { PARSER_ERROR }
    }
    PARSER_SUCCESS
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
std::string             CNumParser::ParseInput  ()
{
    std::string         noWhiteSpace = SkipWhiteSpace();
    
    return RPN(ShuntingYard(noWhiteSpace));
}
