/*!     \file
 *      \brief CCursor class. Controls the screen cursor.      
 */
/*!     \class CCursor
 *      \brief CCursor class. Controls the screen cursor.      
 */
#ifndef CCURSOR_H
#define	CCURSOR_H
#include <stack>
#include "TList.h"
#include "TCursor.h"

class CCursor 
{
public:                                 /*! Implicit constructor \param _list List dimensions */
                                        CCursor      ( const TListDimensions* _list );
                                        /*! Implicit destructor */
                                        ~CCursor     ();
                                        /*! Initialize the cursor and set it's position to A1 */
    void                                Init         ();
                                        /*! Backup current position */
    void                                Push         ();
                                        /*! Restore position from last backup */
    void                                Pop          ();
                                        /*! Move one row up \return True if possible */
    bool                                RowUp        ();
                                        /*! Move one row down \return True if possible */
    bool                                RowDown      ();
                                        /*! Move one column left \return True if possible */
    bool                                ColumnLeft   ();
                                        /*! Move one column right \return True if possible */
    bool                                ColumnRight  ();
                                        /*! Move to the edit line \return True if possible */
    bool                                ToEditLine   ();
                                        /*! Go to the specified physical coordinates 
                                         * \param _y Y coordinate \param _x X coordinate 
                                         * \return True if possible */
    bool                                Move         ( const int _y, const int _x );
                                        /*! Go to the specified physical coordinates, but only
                                         *  if the are inside edit line. 
                                         * \param _y Y coordinate \param _x X coordinate 
                                         * \return True if possible */
    bool                                EditLineMove ( const int _y, const int _x );
                                        /*! Get current Y coordinate \return Y coordinate */
    const int                           GetY         () const;
                                        /*! Get current X coordinate \return X coordinate */
    const int                           GetX         () const;
                                        /*! Get current cell index \return Index of actual cell */
    const std::string&                  CellIdx      () const;
protected:
                                        /*! Set current cell index */
    void                                setIdx();     
    const TListDimensions*              m_list; ///< List dimensions to detect moves out of the screen
    TCursorDimensions                   m_cursor; ///< See TCursorDimensions
    std::stack<TCursorDimensions>       m_stack; ///< Stack for backuping current cursor position
private:
    CCursor(const CCursor& orig);
};
#endif	/* CCURSOR_H */