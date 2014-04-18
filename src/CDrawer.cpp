/* 
 * File:   CDrawer.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 22, 2012, 12:27 PM
 */
#include <string>
#include <curses.h>
#include "CDrawer.h"
#include "CColumn.h"
#include "CRow.h"
#include "CCursor.h"

                        CDrawer::CDrawer           ( TListDimensions* _list, 
                                                     CCursor*         _cursor )
{
   m_cursor = _cursor;
   m_list   = _list;
   m_allocatedAtLeastOnce = false;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                        CDrawer::~CDrawer          () { FreeRowsColumns(); }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/                        
void                    CDrawer::DrawList          () 
{
    AllocRowsColumns();
    DrawRows();
    DrawColumns();
}                        
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CDrawer::AllocRowsColumns  ()
{
    m_allocatedAtLeastOnce = true;
    
    m_list->m_Vsize.m_columns.m_column = 
            new CColumn*[m_list->m_Vsize.m_columns.m_columnsMax];
    for ( register int i = 0; i < m_list->m_Vsize.m_columns.m_columnsMax; i++ )
    {
        TControlParams params = 
                { m_list->m_Vsize.m_columns.m_columnsMax, i,
                  m_list->m_Psize.m_cellWidth, m_list->m_screen.m_H };
        
        m_list->m_Vsize.m_columns.m_column[i] = new CColumn(params);
    }
    
    m_list->m_Vsize.m_rows.m_row = 
            new CRow*[m_list->m_Vsize.m_rows.m_rowsMax];
    for ( register int i = 0; i < m_list->m_Vsize.m_rows.m_rowsMax; i++ )
    {
        TControlParams params = 
                { m_list->m_Vsize.m_rows.m_rowsMax, i,
                  m_list->m_Psize.m_maxLines.length(), m_list->m_screen.m_V };
        
        m_list->m_Vsize.m_rows.m_row[i] = new CRow(params);
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CDrawer::FreeRowsColumns   ()
{
    if ( m_allocatedAtLeastOnce == true ) 
    {
        for ( register int i = 0; i < m_list->m_Vsize.m_columns.m_columnsMax; i++ )
            delete m_list->m_Vsize.m_columns.m_column[i];
        delete [] m_list->m_Vsize.m_columns.m_column;
    
        for ( register int i = 0; i < m_list->m_Vsize.m_rows.m_rowsMax; i++ )
            delete m_list->m_Vsize.m_rows.m_row[i];
        delete [] m_list->m_Vsize.m_rows.m_row;
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CDrawer::DrawRows          () const
{

    int y_coord     = FIRST_ROW;
    int sheet_width = ( m_list->m_Psize.m_cellWidth + CELL_BORDER ) *
                        m_list->m_Vsize.m_columns.m_columnsMax + 
                      ( m_list->m_Psize.m_maxLines.length() + CELL_BORDER );
    
    for ( register int i = 0; i < m_list->m_Vsize.m_rows.m_rowsMax + WASTED_ROWS; i++ )
    {
        if (i > ROWS_WITHOUT_NUMBER)
        {   
            const std::string& name = m_list->m_Vsize.m_rows.m_row[i-2]->ShowMyName();
            int y             = y_coord - 1;
            int x             = ( ( m_list->m_Psize.m_maxLines.length() - 
                                   name.length() ) / 2 ) + SHEET_BORDER;
            
            mvwprintw(stdscr, y, x, "%s", name.c_str());
        }
        
       if (m_cursor->Move(y_coord, SHEET_BORDER) == true)
       { 
           if (i == 0 || i == 1)
               mvwhline( stdscr, m_cursor->GetY(), m_cursor->GetX(), 
                         ACS_HLINE, sheet_width - 1 );
           else
               mvwhline( stdscr, m_cursor->GetY(), m_cursor->GetX(),
                         ACS_HLINE, sheet_width );
           
           y_coord += ROW_HEIGHT;
       }
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CDrawer::DrawColumns       () const
{
    if ( m_cursor->Move( SHEET_BORDER, m_list->m_Psize.m_maxLines.length() + SHEET_BORDER ) == true ) 
         mvwvline( stdscr, m_cursor->GetY(), m_cursor->GetX(),
                  ACS_VLINE, m_list->m_Psize.m_lines );
    
    int x_coord = m_list->m_Psize.m_maxLines.length() + 
                  m_list->m_Psize.m_cellWidth + SHEET_BORDER + CELL_BORDER;
    
    for ( register int i = 0; i < m_list->m_Vsize.m_columns.m_columnsMax; i++ )
    {
        if ( m_cursor->Move( SHEET_BORDER, x_coord ) == true )
        {
            const std::string& name = m_list->m_Vsize.m_columns.m_column[i]->ShowMyName();
            int y             = COLUMN_NAME_POS;
            int x             = m_cursor->GetX() - ( (m_list->m_Psize.m_cellWidth - 
                               name.length()) / 2 ) - name.length();
            
            mvwprintw(stdscr, y, x, "%s", name.c_str());
            
            if ( i == m_list->m_Vsize.m_columns.m_columnsMax - 1 )
                mvwvline( stdscr, m_cursor->GetY(), m_cursor->GetX(), 
                          ACS_VLINE, m_list->m_Psize.m_lines );
            else
            {
                mvwvline( stdscr, m_cursor->GetY(), m_cursor->GetX(),
                          ACS_VLINE, CELL_HEIGHT );
                mvwvline( stdscr, m_cursor->GetY() + SPACE_FOR_EDITLINE, 
                          m_cursor->GetX(), ACS_VLINE, m_list->m_Psize.m_lines - 
                          SPACE_FOR_EDITLINE );
            }
        }
        x_coord += m_list->m_Psize.m_cellWidth + CELL_BORDER;
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CDrawer::DrawEmptyEditLine () const
{
    m_cursor->Push();
    if (m_cursor->ToEditLine() == true) 
    {
        int editLineLength = ( m_list->m_Psize.m_cellWidth + CELL_BORDER ) *
                               m_list->m_Vsize.m_columns.m_columnsMax - CELL_BORDER;
        std::string emptyEditLine;
        
        emptyEditLine.assign(editLineLength, ' ');
        wprintw(stdscr, "%s", emptyEditLine.c_str());
    }
    m_cursor->Pop();
}
