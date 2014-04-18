/*!     \file
 *      \brief Defines common controls for rows and columns.      
 */
/*!     \class CListControls
 *      \brief Defines common controls for rows and columns.      
 */
#ifndef CLISTCONTROLS_H
#define	CLISTCONTROLS_H
#include "TListControls.h"

class CListControls 
{
public:
                                /*! Implicit constructor \param _params see TControlParams*/
                                CListControls  ( const TControlParams& _params );
                                /*! Implicit destructor */
    virtual                     ~CListControls ();
                                /*! \return Returns real index of the control object. */
    const std::string&          ShowMyIdx      () const;
                                /*! \return Returns virtual name of the object. */
    const std::string&          ShowMyName     () const;
protected:
    const TControlParams        m_params;       ///< \brief See TControlParams
    std::string                 m_idx;          ///< \brief Real index of control, eg. A for column, 5 for row
    std::string                 m_name;         ///< \brief Virtual name of the control, eg. ### instead of AAAA for column width 3
};
#endif	/* CLISTCONTROLS_H */