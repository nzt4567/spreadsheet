/*!     \file
 *      \brief Sparsearray for storing the cells      
 */
/*!     \class CSparseArray
 *      \brief Sparsearray for storing the cells.  
 */
#ifndef CSPARSEARRAY_H
#define	CSPARSEARRAY_H
#include "TSparseArray.h"
class CExprCell;

class CSparseArray 
{
public:
                                /*! Implicit constructor */
                                CSparseArray  ();
                                /*! Implicit destructor */
                                ~CSparseArray ();
                                /*! Evaluates the whole sparsearray. This is pure evil.*/
    void                        ReEvaluate    ();
                                /*! Adds pointer on cell to the array \param _val Pointer to add */
    void                        Add           ( CExtendedCell* _val );
                                /*! Deletes cell with particular index \param _idx Cell index to search for */
    void                        Delete        ( const std::string& _idx );
                                /*! Searches for particular index index \param _idx Cell index to search for
                                 *  \return Pointer to searched cell or NULL if not found */
    CExtendedCell*              SearchIdx     ( const std::string& _idx ) const;
protected:
    TElement*                   m_first; ///< Pointer on first sparsearray element
    TElement*                   m_last; ///< Pointer on last sparsearray element
    int                         m_size; ///< Elements count
private:
        CSparseArray(const CSparseArray& orig);
};
#endif	/* CSPARSEARRAY_H */