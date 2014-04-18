/* 
 * File:   CParser.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 24, 2012, 3:00 PM
 */
#include <string>
#include <stack>
#include <queue>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include "exceptions.h"
#include "CParser.h"
                                        CParser::CParser        ( TParserParams& _params ) : 
                                             m_parser(_params) {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                        CParser::~CParser       () {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
std::string                             CParser::SkipWhiteSpace () const
{
    std::string                         noWhiteSpace = "";
    unsigned const int                  inputLength  = m_parser.m_input.length();
    
    for ( register unsigned int i = 0; i < inputLength; i++ )
        if ( m_parser.m_input[i] != ' ' )
            noWhiteSpace += m_parser.m_input[i];
    return noWhiteSpace;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
std::string&                            CParser::ShuntingYard   ( std::string& _input ) const
{ /* This expects std::string with allowed (0-9 + - / *) chars only || (SEGFAULT && DEATH && WORLD END) */
    std::queue<char>                    stl_queue;                      /* Operators stack                  */
    std::stack<TRPNelements>            stl_stack;                      /* RPN queue                        */
    int                                 counter =  0;                   /* Parenthesis counter              */
    bool                                binaryMinus = false;            /* Unary minus detection            */
    bool                                AllowedLast = false;            /* + - * / ( must not be last       */
    TRPNelements                        elemToCheck = { 0, 0 };         /* Top element of stack             */
    TRPNelements                        elemToPush  = { 0, 0 };         /* Element to push this iteration   */
    unsigned const int                  inputLength = _input.length();  /* As it says...                    */
    
    for (register unsigned int i = 0; i < inputLength; i++)
    {
        char k = _input[i];
        
        if (k == '-' && binaryMinus == false)
            k = '~';
            
        if ( (k >= '0' &&  k <= '9') || k == '.' )
        {
           binaryMinus = true; 
           if (k == '.') AllowedLast = false; 
           else AllowedLast = true;
           stl_queue.push(k);
           continue;
        }
        elemToPush.m_val = k;
        
        switch (k)
        {
            case '~' :
                elemToPush.m_prio = 3;
                break;
            case '*' :
            case '/' :
                elemToPush.m_prio = 2;
                break;
            case '+' :
            case '-' :
                elemToPush.m_prio = 1;
                break;
            case '(' :
            case ')' :
                elemToPush.m_prio = 0;                
                break;
        }
              
        if (elemToPush.m_val == '(')
        { /* Left parenthesis has to be temporarily saved on the stack */
           binaryMinus = AllowedLast = false;
           counter++;
           stl_stack.push(elemToPush);
           continue;
        }
        
        if (elemToPush.m_val == ')')
        { /* Right parenthesis does it's mess and pop's out the left one */
            binaryMinus = AllowedLast = true;
            if (counter <= 0)
                throw CParserInvalidParenthesis();
            else
                counter--;
            
            elemToCheck = stl_stack.top();
            while (elemToCheck.m_val != '(')
            {
              stl_queue.push(' ');
              stl_queue.push(elemToCheck.m_val);
              stl_stack.pop();
              if (stl_stack.empty() == true)
                  throw CParserInvalidParenthesis();
              elemToCheck = stl_stack.top();
                
            }
            
            stl_stack.pop();
            continue;
        }
        
        binaryMinus = AllowedLast = false;
        stl_queue.push(' ');
        if (stl_stack.empty() != true) /* STL stack won't detect underflow */
           elemToCheck = stl_stack.top();
        else 
        { /* This should happen only in the case of first operand */
            stl_stack.push(elemToPush);
            continue;
        }
        
        while (elemToPush.m_prio <= elemToCheck.m_prio)
        { /* Well, do it just like Dijkstra said... */
            stl_queue.push(elemToCheck.m_val);
            stl_queue.push(' ');
            stl_stack.pop();
            if (stl_stack.empty() == true)
                break;
            elemToCheck = stl_stack.top();
        }
        stl_stack.push(elemToPush);
    }
    
    if (AllowedLast != true)
        throw CParserInvalidChar();
    
    while (stl_stack.empty() != true)
    { /* Rest of operands has to go to the queue which stores RPN */
        stl_queue.push(' ');
        elemToCheck = stl_stack.top(); stl_stack.pop();
        stl_queue.push(elemToCheck.m_val);
    }
    _input = "";
    while (stl_queue.empty() != true)
    { /* Create the RPN form */
        _input += stl_queue.front(); stl_queue.pop();
    }
    
    return _input;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
std::string&                            CParser::RPN            ( std::string& _input ) const
{ /* This expects clean && nice RPN string with no rubbish in it || (SEGFAULT && DEATH && WORLD END) */
    std::stack<std::string>             stl_stack;
    std::string                         helpStr  = "";
    std::string                         helpStr2 = "";
    std::stringstream                   ss; ss << std::fixed;
    bool                                lastWasNumber = false;
    unsigned const int                  inputLength   = _input.length();
       
    for(register unsigned int i = 0; i < inputLength; i++)
    {
        char k = _input[i];
        ss.str("");
        if ( (k >= '0' && k <= '9') || k == '.')
        { /* Number || dot = put it on the std::string stack */
            if (lastWasNumber == true)
            {
               STACK_CHECK 
               helpStr = stl_stack.top(); stl_stack.pop();
               helpStr += k;
            }
            else
               helpStr = k;
            
            stl_stack.push(helpStr);
            lastWasNumber = true;
            continue;
        }
        
        lastWasNumber = false;
        if (k == ' ') continue; /* Elements separated */
        
        STACK_CHECK
        helpStr   = stl_stack.top(); stl_stack.pop();
        double o1 = atof(helpStr.c_str());
     
        if (k == '~')
           o1 *= -1;
        else 
        { /* Do the math */
           STACK_CHECK 
           helpStr2  = stl_stack.top(); stl_stack.pop();
           double o2 = atof(helpStr2.c_str());
           if (o1 == 0 && k == '/') throw CParserDivisionByZero();
        
           if (k == '+') o2 += o1;
           if (k == '-') o2 -= o1;
           if (k == '*') o2 *= o1;
           if (k == '/') o2 /= o1;
        
           if (isnan(o2) || isinf(o2))
              throw CParserNaN();
           o1 = o2;
        }
        
        ss << o1;
        helpStr = ss.str();
        stl_stack.push(helpStr); /* Push evaluated std::string back on the stack */
    }
    
    _input = "";
    while (stl_stack.empty() != true) /* Create the output std::string */
    {
        helpStr = stl_stack.top(); stl_stack.pop();
        _input += helpStr;
    }
    
    return _input;
}