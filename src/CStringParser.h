/*!     \file
 *      \brief Parser for cells containing strings      
 */
/*!     \class CStringParser
 *      \brief Parser for cells containing strings  
 */
#ifndef CSTRINGPARSER_H
#define	CSTRINGPARSER_H
#include "CParser.h"
class CSparseArray;

class CStringParser : public CParser 
{
public:
                                /*! Implicit constructor \param _params See TParserParams */
                                CStringParser  ( TParserParams& _params );
                                /*! Implicit destructor */
    virtual                     ~CStringParser ();
    virtual bool                CheckInput     ();
    virtual std::string         ParseInput     ();
private:
    CStringParser(const CStringParser& orig);
};
#endif	/* CSTRINGPARSER_H */