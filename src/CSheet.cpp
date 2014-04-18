/* 
 * File:   CSheet.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 18, 2012, 11:13 PM
 */
#include <string>
#include <curses.h>
#include "exceptions.h"
#include "CSheet.h"
#include "CList.h"

                        CSheet::CSheet         ( const TSheetParams& _params ) : 
                               m_params(_params)
{ /* ncurses initialization  */
    initscr   ();    
    clear     ();
    cbreak    ();
    intrflush ( stdscr, FALSE );
    keypad    ( stdscr, TRUE  );
    nodelay   ( stdscr, FALSE );
    timeout   ( -1 );
    noecho    ();
    curs_set  ( 1 );
    
    if (start_color() != ERR)
    {
        init_pair(COLOR, m_params.m_Fg, m_params.m_Bg);
        attron(COLOR_PAIR(COLOR));
    }
    
    attron (A_BOLD);  
    border(0, 0, 0, 0, 0, 0, 0, 0);
    attroff(A_BOLD);
    refresh();
    
    m_actualList = new CList();
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                        CSheet::~CSheet        () 
{ /* Bring the term back to normal state */
  if ( isendwin() == FALSE )
       endwin();

   delete m_actualList;      
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CSheet::DrawSheet      () const
{
    TListPhysicalSize Psize = { LINES - BORDERS, COLS - BORDERS, 
                                m_params.m_cellWidth, m_params.m_maxLines};
    
    if ( Psize.m_cellWidth >= Psize.m_cols - 
         (signed int) m_params.m_maxLines.length() - CELL_BORDER)
    {
        endwin();
        throw CSheetTooWideColumn();
    }
           

    m_actualList->DrawMyself( Psize );
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CSheet::Interactivity  () const
{    /* Very straight forward interactivity */
    int c = 0;
    
    while ( (c=getch()) != KEY_F(4) ) 
    {
       switch(c)
       {
           case KEY_RIGHT :
               m_actualList->KeyRight();
               break;
               
           case KEY_DOWN :
               m_actualList->KeyDown();
               break;
               
           case KEY_LEFT :
               m_actualList->KeyLeft();
               break;
               
           case KEY_UP :
               m_actualList->KeyUp();
               break;
                
           case KEY_CR    :
           case KEY_LF    :
           case KEY_ENTER :
           case KEY_TAB   :
               m_actualList->KeyTab();
               break;
               
           case KEY_BACKSPACE :
           case KEY_DC :
           case KEY_RESIZE :
           default :
               break;
       }
    }
}