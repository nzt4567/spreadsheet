/*!     \file
 *      \brief Class representing cells that have expressions in input.      
 */
/*!     \class CExprCell
 *      \brief Class representing cells that have expressions in input.  
 */
#ifndef CEXPRCELL_H
#define	CEXPRCELL_H
#include "CExtendedCell.h"

class CExprCell : public CExtendedCell
{
public:
                                /*! Implicit constructor \param _cursor Cursor for screen move 
                                 * \param _list List dimensions \param _input User input */
                                CExprCell          (  CCursor* _cursor, 
                                                      const TListDimensions* _list, 
                                                      const std::string& _input );
                                /*! Implicit destructor */
    virtual                     ~CExprCell         ();
    virtual bool                AmIString          () const;
    virtual bool                AmIExpr            () const;
    virtual bool                AmINum             () const;
                                /*! Expression cycle checking. Ugly recursion.
                                 *  \param _cell Cell name to check for. 
                                 *  \param _array Access to other cells. 
                                 *  \return True if cells create cycle. */ 
    bool                        DoIPointToThisCell (  const std::string& _cell, 
                                                      CSparseArray* _array );
    virtual void                Evaluate           (  CSparseArray* _array );
private:
    CExprCell(const CExprCell& orig);
};
#endif	/* CEXPRCELL_H */