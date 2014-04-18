/*!     \file
 *      \brief Helper class for drawing the sheet.      
 */
/*!     \class CDrawer
 *      \brief Helper class for drawing the sheet.  
 */
#ifndef CDRAWER_H
#define	CDRAWER_H
#include "TList.h"
#include "TDrawer.h"
class CCursor;

class CDrawer 
{
public:
                                /*! Implicit constructor \param _list List dimensions
                                 *  \param _cursor Screen cursor */
                                CDrawer           ( TListDimensions* _list, 
                                                    CCursor* _cursor );
                                /*! Implicit destructor */
                                ~CDrawer          ();
                                /*! Encapsulation method to draw the whole list */
    void                        DrawList          ();
                                /*! Clear the edit line */
    void                        DrawEmptyEditLine () const;
                                /*! Free all existing CRow and CColumn objects */
    void                        FreeRowsColumns   ();
protected:
                                /*! Allocate appropriate number of CRow and CColumn objects */
    void                        AllocRowsColumns  ();
                                /*! Draw rows */
    void                        DrawRows          () const;
                                /*! Draw columns */
    void                        DrawColumns       () const;
    TListDimensions*            m_list; ///< List dimensions for calculations 
    CCursor*                    m_cursor; ///< Cursor to move on the screen
    bool                        m_allocatedAtLeastOnce; ///< For scroll usage
private:
        CDrawer(const CDrawer& orig);  
};
#endif	/* CDRAWER_H */