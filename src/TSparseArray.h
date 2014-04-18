/*!     \file
 *      \brief Data structures and constants for CSparseArray class.      
 */
/**     \def MAX_EXPR_CELLS
 *      \brief Maximum number of expression cells in one expression  
 */
/*!     \struct TElement
 *      \brief Structure stored in CSparsearray      
 */
#ifndef TSPARSEARRAY_H
#define	TSPARSEARRAY_H
#define MAX_EXPR_CELLS  100
class CExtendedCell;

struct TElement
{
    /*! Implicit constructor \param _val Value to store. \param _prev Pointer at previous element. */
    TElement(CExtendedCell* _val, TElement* _prev) :  
        m_item(_val), m_next(NULL), m_prev(_prev) {};
    CExtendedCell*      m_item;         ///< \brief Pointer to CExtendedCell stored in CSparseArray
    TElement*           m_next;         ///< \brief Next TElement pointer
    TElement*           m_prev;         ///< \brief Previous TElement pointer
};
#endif	/* TSPARSEARRAY_H */