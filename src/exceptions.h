/*!     \file
 *      \brief Exceptions classes      
 */
/*!     \class CParserInvalidChar
 *      \brief Thrown if invalid character is found  
 */
/*!     \class CParserInvalidParenthesis
 *      \brief Thrown if odd number of parenthesis is found  
 */
/*!     \class CParserDivisionByZero
 *      \brief Thrown if division by zero is detected  
 */
/*!     \class CParserNaN
 *      \brief Thrown if result is Not-A-Number. See IEEE754  
 */
/*!     \class CSheetTooWideColumn
 *      \brief Thrown if column width > COLS - BORDERS  
 */
/*!     \class CCursorFatalStackUnderflow
 *      \brief Thrown if (std::stack.empty() == true) but there was std::stack.push() before!   
 */
#ifndef EXCEPTIONS_H
#define	EXCEPTIONS_H

class CParserInvalidChar
{
public:
    /*! Implicit constructor */
    CParserInvalidChar() {};
    /*! Implicit destructor  */
   ~CParserInvalidChar() {}; 
};

class CParserInvalidParenthesis
{
public:
    /*! Implicit constructor */
    CParserInvalidParenthesis() {};
    /*! Implicit destructor  */
   ~CParserInvalidParenthesis() {}; 
};

class CParserDivisionByZero
{
public:
    /*! Implicit constructor */
    CParserDivisionByZero() {};
    /*! Implicit destructor  */
   ~CParserDivisionByZero() {}; 
};

class CParserNaN
{
public:
    /*! Implicit constructor */
    CParserNaN() {};
    /*! Implicit destructor  */
   ~CParserNaN() {}; 
};

class CSheetTooWideColumn
{
public:
    /*! Implicit constructor */
    CSheetTooWideColumn() {};
    /*! Implicit destructor  */
   ~CSheetTooWideColumn() {};
};

class CCursorFatalStackUnderflow
{
public:
    /*! Implicit constructor */
    CCursorFatalStackUnderflow() {};
    /*! Implicit destructor  */
   ~CCursorFatalStackUnderflow() {};
};
#endif	/* EXCEPTIONS_H */