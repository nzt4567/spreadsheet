/*!     \file
 *      \brief CColumn class. Represents sheet columns.      
 */
/*!     \class CColumn
 *      \brief CColumn class. Represents sheet columns.      
 */
#ifndef CCOLUMN_H
#define	CCOLUMN_H
#include "CListControls.h"

class CColumn : public CListControls
{
public:
                /*! Implicit constructor \param _params see TControlParams*/
                CColumn(const TControlParams& _params);    
};
#endif	/* CCOLUMN_H */

