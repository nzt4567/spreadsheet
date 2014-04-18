/*!     \file
 *      \brief Definitions and structures for CListControls.      
 */
/**     \def ALPHABET_CHARS
 *      \brief Number of alphabet chars in ASCII.  
 */
/*!     \struct TControlParams
 *      \brief Common controls for both of CRow and CColumn.  
 */
#ifndef TLISTCONTROLS_H
#define	TLISTCONTROLS_H
#define ALPHABET_CHARS          26

struct TControlParams
{
    int                         m_controls;             ///< \brief Number of controls on one screen.
    int                         m_myNum;                ///< \brief This controls offset number from the start of the screen.
    int                         m_cellWidth;            ///< \brief Physical width of one cell.
    int                         m_screen;               ///< \brief Number of either vertical or horizontal screen.
};
#endif	/* TLISTCONTROLS_H */