/* 
 * File:   CWorkerCell.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 18, 2012, 11:05 PM
 */
#include <string>
#include <curses.h>
#include <stdexcept>
#include "TSheet.h"
#include "CWorkerCell.h"
#include "CCursor.h"
#include "CExprCell.h"
#include "CStringCell.h"
#include "CNumCell.h"

                        CWorkerCell::CWorkerCell   ( CCursor*               _cursor, 
                                                     const TListDimensions* _list   ) : 
                           CBaseCell(_cursor, _list) {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                        CWorkerCell::CWorkerCell   ( CCursor*                _cursor, 
                                                     const TListDimensions*  _list,
                                                     const std::string&      _input ) : 
                           CBaseCell(_cursor, _list) { m_input = _input; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                        CWorkerCell::~CWorkerCell  () {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CWorkerCell::BeginEditMode ()
{   /* This catches some exceptions, but does not react. (No edit to the string == no edit to the screen) => user knows something is wrong.  */
    int                 c       = 0;
    unsigned int        i       = 0;
    unsigned int        LineLen = ( m_list->m_Psize.m_cellWidth + CELL_BORDER ) *
                                    m_list->m_Vsize.m_columns.m_columnsMax - CELL_BORDER;    
    m_cursor->Push();
    DrawEditLine();
    while ( (c = getch()) != KEY_TAB )
    {   
        if ( c == KEY_ENTER || c == KEY_LF || c == KEY_CR ) break;
        
        switch(c)
        {
           case KEY_DOWN   :
           case KEY_UP     :          
           case KEY_CR     :
           case KEY_LF     :
           case KEY_RESIZE :
               break;
               
           case KEY_RIGHT  :
                if ( i < m_input.length() && m_cursor->EditLineMove
                     ( m_cursor->GetY(), m_cursor->GetX() + 1 ) == true )
                   i++;
               break;
     
           case KEY_LEFT   :
                if ( i > 0 && m_cursor->EditLineMove
                     ( m_cursor->GetY(), m_cursor->GetX() - 1 ) == true )
                  i--;
               break;
           
          case KEY_BACKSPACE :
               if ( m_input.length() > 0 && m_cursor->EditLineMove
                    ( m_cursor->GetY(), m_cursor->GetX() - 1 ) == true )
                 try
                 {
                      m_input.erase(--i, 1);
                      ClearEditLine();
                      PrintEditLine();
                 }
                 catch ( std::out_of_range& err ) {};       
               break;
               
           case KEY_DC :
               if (i < m_input.length() && i >= 0)
                 try
                 {
                   m_input.erase(i, 1);
                   ClearEditLine();
                   PrintEditLine();
                 }
                 catch ( std::out_of_range& err ) {};
               break;
               
           default :
               if ( m_input.length() < LineLen && m_cursor->EditLineMove
                    ( m_cursor->GetY(), m_cursor->GetX() + 1 ) == true )
                 try
                 {
                      m_input.insert(i++, 1, c);
                      PrintEditLine();
                 }
                 catch ( std::out_of_range& err ) {};
               break;               
       }
    }
    m_cursor->Pop();
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CWorkerCell::DrawEditLine  () const
{ /* Starts the edit mode, by moving to the edit line and printing (last user input || nothing) */
    ClearEditLine();
    if ( m_cursor->ToEditLine() == true )
        wprintw( stdscr, "%s", m_input.c_str());
    m_cursor->ToEditLine();
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CWorkerCell::PrintEditLine () const
{ /* Make the user see the changes to the input */
    m_cursor->Push();
    if ( m_cursor->ToEditLine() == true )
       wprintw( stdscr, "%s", m_input.c_str() );
    m_cursor->Pop();
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
CExtendedCell*          CWorkerCell::SetCellType   () const
{    /* I don't think this needs a comment at all... */
    unsigned const int inputLength = m_input.length();
    
     for ( register unsigned int i = 0; i < inputLength; i++ )
        if ( m_input[i] == ' ' ) continue;
        else if ( m_input[i] == '=' ) 
            return new CExprCell   ( m_cursor, m_list, m_input );
        else if ( m_input[i] == '"' )
            return new CStringCell ( m_cursor, m_list, m_input );
        else
            return new CNumCell    ( m_cursor, m_list, m_input );
    return NULL;
}
