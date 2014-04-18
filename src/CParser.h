/*!     \file
 *      \brief Base class for parsing input.      
 */
/*!     \class CParser
 *      \brief Base class for parsing input.  
 */
#ifndef CPARSER_H
#define	CPARSER_H
#include "TParser.h"

class CParser 
{
public:
                                        /*! Implicit constructor \param _params See TParserParams */
                                        CParser        ( TParserParams& _params);
                                        /*! Implicit destructor */
    virtual                             ~CParser       ();
                                        /*! Checks user input for invalid chars. 
                                         * \return True if input contains invalid chars */
    virtual bool                        CheckInput     () = 0;
                                        /*! Parses and calculates user input.  
                                         * \return Evaluated output. */
    virtual std::string                 ParseInput     () = 0;
                                        /*! Calculates expression in RPN. See  http://en.wikipedia.org/wiki/Reverse_Polish_notation 
                                         * \param _input RPN expression to calculate \return String containing the calculated result */
    std::string&                        RPN            ( std::string& _input ) const;
                                        /*! Creates RPN from infix notation. See http://en.wikipedia.org/wiki/Shunting-yard_algorithm 
                                         * \param _input Infix notation of mathematical expression \return RPN */
    std::string&                        ShuntingYard   ( std::string& _input ) const;
protected:
                                        /*! Skips white space in user input. \return Input without whitespace */
    std::string                         SkipWhiteSpace ()                      const;    
    TParserParams                       m_parser; ///< See TParserParams
private:
    CParser(const CParser& orig);
};
#endif	/* CPARSER_H */