/*!     \file
 *      \brief Data structures and constants for CSheet class.      
 */
/**     \def BORDERS
 *      \brief Lines/columns wasted by borders  
 */
/**     \def COLOR
 *      \brief Used color pair num  
 */
/**     \def GREEN
 *      \brief Default foreground color  
 */
/**     \def BLACK
 *      \brief Default background color 
 */
/**     \def WIDTH
 *      \brief Default column width  
 */
/**     \def MAXLINES
 *      \brief Default number of lines  
 */
/**     \def KEY_CR
 *      \brief Enter-key code on Apple  
 */
/**     \def KEY_LF
 *      \brief Enter-key code on PC  
 */
/**     \def KEY_TAB
 *      \brief Tab-key code  
 */
/*!     \struct TSheetParams
 *      \brief Parametrs used by CSheet class      
 */
#ifndef TSHEET_H
#define	TSHEET_H
#define BORDERS                 2
#define COLOR                   1
#define GREEN                   2
#define BLACK                   0
#define WIDTH                   8
#define MAXLINES                "1000"
#define KEY_CR                  13
#define KEY_LF                  10
#define KEY_TAB                 9

struct TSheetParams
{
    int                         m_Fg;           ///< \brief Chosen foreground color
    int                         m_Bg;           ///< \brief Chosen background color
    int                         m_cellWidth;    ///< \brief Chosen column width color
    std::string                 m_maxLines;     ///< \brief Chosen number of lines
};
#endif	/* TSHEET_H */