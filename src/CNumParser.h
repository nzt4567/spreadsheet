/*!     \file
 *      \brief Class parsing input in cells containing numbers.      
 */
/*!     \class CNumParser
 *      \brief Class parsing input in cells containing numbers.  
 */
#ifndef CNUMPARSER_H
#define	CNUMPARSER_H
#include "CParser.h"

class CNumParser : public CParser 
{
public:
                                /*! Implicit constructor \param _params See TParserParams */
                                CNumParser  ( TParserParams& _params );
                                /*! Implicit destructor */
    virtual                     ~CNumParser ();
    virtual bool                CheckInput  ();
    virtual std::string         ParseInput  ();
private:
    CNumParser(const CNumParser& orig);
};
#endif	/* CNUMPARSER_H */