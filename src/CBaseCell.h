/*!     \file
 *      \brief Base class for all cells.      
 */
/*!     \class CBaseCell
 *      \brief Base class for all cells. 
 */
#ifndef CBASECELL_H
#define	CBASECELL_H
#include "TBaseCell.h"
#include "TList.h"
class CCursor;

class CBaseCell 
{
public:
                                 /*! Implicit constructor \param _cursor Pointer on screen cursor 
                                  * \param _list List dimensions */
                                CBaseCell     ( CCursor* _cursor, 
                                                const TListDimensions* _list );
                                /*! Implicit destructor */
    virtual                     ~CBaseCell    ();
                                /*! Draws cell output to edit line.*/
    virtual void                DrawEditLine  () const = 0;
                                /*! Checks input against index of the cell. 
                                 * \param _idx String co check. \return Returns true if string's match.*/
    bool                        IsMyIdx       (  const std::string& _idx ) const;
                                /*! Fills edit line with ' '. */ 
    void                        ClearEditLine () const;
                                /*! Fills cell screen place with ' '. */
    void                        ClearCell     () const;
protected:
    TBaseCellScreen             m_screen; ///< Screen where the cell should be.
    TBaseCellPhysicalPos        m_position; ///< Position inside the screen.
    const std::string           m_index; ///< Index of the cell
    std::string                 m_input; ///< User input of the cell
    CCursor*                    m_cursor; ///< Cursor for screen manipulation
    const TListDimensions*      m_list; ///< List dimensions to be able to calculate some things
private:
    CBaseCell(const CBaseCell& orig); 
};
#endif	/* CBASECELL_H */