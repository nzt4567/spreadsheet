/*!     \file
 *      \brief Class representing cells accepting user input      
 */
/*!     \class CWorkerCell
 *      \brief Class representing cells accepting user input  
 */
#ifndef CWORKERCELL_H
#define	CWORKERCELL_H
#include "CBaseCell.h"
class CExtendedCell;
class CCursor;

class CWorkerCell : public CBaseCell 
{
public:
                                /*! Implicit constructor \param _cursor Screen cursor 
                                 * \param _list List dimensions */
                                CWorkerCell   ( CCursor* _cursor, const TListDimensions* _list );
                                /*! Constructor for conversion from CExtendedCell to CWorkerCell 
                                 * \param _cursor Screen cursor \param _list List dimensions 
                                 * \param _input User input in CExtendedCell */
                                CWorkerCell   ( CCursor* _cursor, const TListDimensions* _list,
                                                const std::string& _input );
                                /*! Implicit destructor */
    virtual                     ~CWorkerCell  ();  
                                /*! Create appropriate cell based on user input
                                 * \return Pointer on newly allocated cell */
    CExtendedCell*              SetCellType   ()  const;
                                /*! Accept user input, control edit line */
    void                        BeginEditMode ();
                                /*! Draw edit line containing actual user input */
    virtual void                DrawEditLine  ()  const;
protected:
                                /*! Draw edit line containing actual user input */
    void                        PrintEditLine ()  const;    
private:
    CWorkerCell(const CWorkerCell& orig);
};
#endif	/* CWORKERCELL_H */