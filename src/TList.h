/*!     \file
 *      \brief Definitions and structures for CList.      
 */
/**     \def CELL_BORDER
 *      \brief Width of every cell border.  
 */
/**     \def WASTED_ROWS
 *      \brief Rows wasted by edit line and row for letters naming columns.  
 */
/**     \def ROW_HEIGHT
 *      \brief Height of every row in terminal lines.  
 */
/**     \def EDITLINE_Y
 *      \brief Y-coordinate of edit line beginning.  
 */
/*!     \struct TListRows
 *      \brief Representation of rows in list.  
 */
/*!     \struct TListColumns
 *      \brief Representation of columns in list.  
 */
/*!     \struct TListPhysicalSize
 *      \brief Representation of some physical limitations of the list.  
 */
/*!     \struct TListVirtualSize
 *      \brief Representation of some virtual limitations of the list.  
 */
/*!     \struct TListEditLinePos
 *      \brief Physical position of the edit line.  
 */
/*!     \struct TListScreen
 *      \brief Actual screen number where the list is.  
 */
/*!     \struct TListDimensions
 *      \brief One big structure for encapsulation of the others.  
 */
#ifndef TLIST_H
#define	TLIST_H
#define CELL_BORDER     1
#define WASTED_ROWS     2
#define ROW_HEIGHT      2
#define EDITLINE_Y      3
#define CURSOR_FATAL    std::cerr << "This is a very fatal cursor (or STL) error. Mail me!" << std::endl;\
                        m_cursor->Init();
class CRow;
class CColumn;

struct TListRows
{
    CRow**                      m_row;          ///< \brief Array of pointers to CRow.
    int                         m_rowsMax;      ///< \brief Num of pointers in array.
};

struct TListColumns
{
    CColumn**                   m_column;       ///< \brief Array of pointers to CColumn.
    int                         m_columnsMax;   ///< \brief Array of pointers to CColumn.
};

struct TListPhysicalSize
{
    int                         m_lines;        ///< \brief Num of lines available for the list.
    int                         m_cols;         ///< \brief Num of columns available for the list.
    int                         m_cellWidth;    ///< \brief Width of one cell.
    std::string                 m_maxLines;     ///< \brief Maximum number of lines the user will need.
};

struct TListVirtualSize
{
    TListColumns                m_columns;      ///< \brief Columns on one screen.
    TListRows                   m_rows;         ///< \brief Rows on one screen.
};

struct TListEditLinePos
{
    int                         m_Y;            ///< \brief Y coordinate of edit line beginning.
    int                         m_X;            ///< \brief X coordinate of edit line beginning.
};

struct TListScreen
{
    int                         m_H;            ///< \brief Actual horizontal screen.
    int                         m_V;            ///< \brief Actual vertical screen.
};

struct TListDimensions
{
    TListVirtualSize            m_Vsize;        ///< \brief See TListVirtualSize.  
    TListPhysicalSize           m_Psize;        ///< \brief See TListPhysicalSize.
    TListScreen                 m_screen;       ///< \brief See TListScreen.
    TListEditLinePos            m_editLine;     ///< \brief See TListEditLinePos.
};
#endif	/* TLIST_H */