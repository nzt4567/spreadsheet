/*!     \file
 *      \brief Class representing cells that have numbers in input.
 */
/*!     \class CNumCell
 *      \brief Class representing cells that have numbers in input.  
 */
#ifndef CNUMCELL_H
#define	CNUMCELL_H
#include "CExtendedCell.h"

class CNumCell : public CExtendedCell
{
public:
                                /*! Implicit constructor \param _cursor Screen cursor 
                                 * \param _list List dimensions \param _input User input */
                                CNumCell  ( CCursor* _cursor, const TListDimensions* _list, 
                                            const std::string& _input );
                                /*! Implicit destructor */
    virtual                     ~CNumCell ();
    virtual void                Evaluate  ( CSparseArray* _array );
    virtual bool                AmIString () const;
    virtual bool                AmIExpr   () const;
    virtual bool                AmINum    () const;
private:
    CNumCell(const CNumCell& orig);
};
#endif	/* CNUMCELL_H */