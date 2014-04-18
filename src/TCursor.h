/*!     \file
 *      \brief Data structures and constants for CParser class.      
 */
/**     \def CURSOR_DEFAULT
 *      \brief Cursor default virtual && physical position.  
 */
/**     \def A1_Y
 *      \brief Default position of A1.  
 */
/**     \def A1
 *      \brief Default position of A1.  
 */
/*!     \struct TCursorVirtualPos
 *      \brief Virtual position of the cursor.
 */
/*!     \struct TCursorPhysicalPos
 *      \brief Physical position of the cursor.
 */
/*!     \struct TCursorDimensions
 *      \brief Bigger structure to encapsulate those smaller.
 */
#ifndef TCURSOR_H
#define	TCURSOR_H
#define CURSOR_DEFAULT          0
#define A1_Y                    5
#define A1                      0

struct TCursorVirtualPos
{
    /*! \brief Implicit constructor */
    TCursorVirtualPos() :
        m_row(CURSOR_DEFAULT), m_column(CURSOR_DEFAULT) {};
    int                         m_row;          ///< \brief Row of the cursor.
    int                         m_column;       ///< \brief Column of the cursor.
    std::string                 m_cellIdx;      ///< \brief Name of the cell where the cursor is.
};

struct TCursorPhysicalPos
{
    /*! \brief Implicit constructor */
    TCursorPhysicalPos() :
        m_X(CURSOR_DEFAULT), m_Y(CURSOR_DEFAULT) {};
    int                         m_X;            ///< \brief X coordinate of the cursor.
    int                         m_Y;            ///< \brief Y coordinate of the cursor.
};

struct TCursorDimensions
{
    TCursorPhysicalPos          m_physical;     ///< \brief See TCursorPhysicalPos.
    TCursorVirtualPos           m_virtual;      ///< \brief See TCursorVirtualPos.
};
#endif	/* TCURSOR_H */