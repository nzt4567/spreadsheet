/*!     \file
 *      \brief Class to store cells containing strings      
 */
/*!     \class CStringCell
 *      \brief Class to store cells containing strings.  
 */
#ifndef CSTRINGCELL_H
#define	CSTRINGCELL_H
#include "CExtendedCell.h"

class CStringCell : public CExtendedCell
{
public:
                                /*! Implicit constructor \param _cursor Screen cursor 
                                 * \param _list List dimensions \param _input User input */
                                CStringCell  ( CCursor* _cursor, const TListDimensions* _list, 
                                               const std::string& _input );
                                /*! Implicit destructor */
    virtual                     ~CStringCell ();
    virtual bool                AmIString    () const;
    virtual bool                AmIExpr      () const;
    virtual bool                AmINum       () const;
    virtual void                Evaluate     ( CSparseArray* _array );
private:
    CStringCell(const CStringCell& orig);
};
#endif	/* CSTRINGCELL_H */