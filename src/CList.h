/*!     \file
 *      \brief Representation of one list in sheet
 */
/*!     \class CList
 *      \brief Representation of one list in sheet  
 */
#ifndef CLIST_H
#define	CLIST_H
#include "TList.h"
class CCursor;
class CSparseArray;
class CExtendedCell;
class CWorkerCell;
class CDrawer;

class CList 
{
public:
                                /*! Implicit constructor */
                                CList      ();
                                /*! Implicit destructor */
                                ~CList     ();
                                /*! Draw this list on screen \param _phys Physical dimensions of terminal */
    void                        DrawMyself ( TListPhysicalSize& _phys );
                                /*! Reaction on KEY_UP press */
    void                        KeyUp      ();
                                /*! Reaction on KEY_DOWN press */
    void                        KeyDown    ();
                                /*! Reaction on KEY_LEFT press */
    void                        KeyLeft    ();
                                /*! Reaction on KEY_RIGHT press */
    void                        KeyRight   ();
                                /*! Reaction on KEY_TAB press */
    void                        KeyTab     ();
protected:
                                /*! Draw output of actual cell */
    void                        ShowCell();
    TListDimensions*            m_list;  ///< See TListDimensions
    CCursor*                    m_cursor; ///< See CCursor
    CSparseArray*               m_array; ///< See CSparseArray
    CExtendedCell*              m_actualCell; ///< See CExtendedCell
    CWorkerCell*                m_workingCell; ///< See CWorkerCell
    CDrawer*                    m_drawer; ///< See CDrawer
private:
    CList(const CList& orig);
};
#endif	/* CLIST_H */