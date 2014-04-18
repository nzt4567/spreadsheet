/*!     \file
 *      \brief CRow class. Represents sheet rows.      
 */
/*!     \class CRow
 *      \brief CRow class. Represents sheet rows.      
 */
#ifndef CROW_H
#define	CROW_H
#include "CListControls.h"

class CRow : public CListControls
{
public:
                /*! Implicit constructor \param _params see TControlParams*/
                CRow( const TControlParams& _params ); 
};
#endif	/* CROW_H */

