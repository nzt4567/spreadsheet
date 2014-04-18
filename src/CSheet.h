/*!     \file
 *      \brief Representation of the whole sheet.      
 */
/*!     \class CSheet
 *      \brief Representation of the whole sheet.  
 */
#ifndef CSHEET_H
#define	CSHEET_H
#include "TSheet.h"
class CList;

class CSheet 
{
public:
                                /*! Implicit constructor \param _params See TSheetParams*/
                                CSheet        ( const TSheetParams& _params );
                                /*! Implicit destructor */
                                ~CSheet       ();
                                /*! Draw this sheet */
    void                        DrawSheet     () const;
                                /*! Launch interactivity */
    void                        Interactivity () const;
protected:
    CList*                      m_actualList; ///< See CList
    const TSheetParams          m_params; ///< See TSheetParams
};
#endif	/* CSHEET_H */