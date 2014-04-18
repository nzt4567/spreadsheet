/*!     \file
 *      \brief Data structures and constants for CParser class.      
 */
/**     \def STRINGCELL
 *      \brief String cell ID.  
 */
/**     \def NUMCELL
 *      \brief Number cell ID.  
 */
/**     \def EXPRCELL
 *      \brief Expression cell ID.  
 */
/*!     \struct TBaseCellPhysicalPos
 *      \brief Physical position of the cell.
 */
/*!     \struct TBaseCellScreen
 *      \brief Screen of the cell.
 */
#ifndef TBASECELL_H
#define	TBASECELL_H
#define STRINGCELL      0
#define NUMCELL         1
#define EXPRCELL        2

struct TBaseCellPhysicalPos
{
    int                 m_X;    ///< \brief X coordinate of the cell.
    int                 m_Y;    ///< \brief Y coordinate of the cell.
};

struct TBaseCellScreen
{
    int                 m_H;    ///< \brief Horizontal screen of the cell.
    int                 m_V;    ///< \brief Vertical screen of the cell.
};
#endif	/* TBASECELL_H */