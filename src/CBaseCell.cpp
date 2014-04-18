/* 
 * File:   CBaseCell.cpp
 * Author: ubuntu
 * 
 * Created on May 18, 2012, 10:31 PM
 */
#include <string>
#include <curses.h>
#include "CBaseCell.h"
#include "CCursor.h"
                        CBaseCell::CBaseCell     ( CCursor*               _cursor, 
                                                   const TListDimensions*  _list ) : 
                             m_index(_cursor->CellIdx()), m_cursor(_cursor), m_list(_list) 
{
    m_screen.m_H = m_list->m_screen.m_H;
    m_screen.m_V = m_list->m_screen.m_V;
    m_position.m_X = m_cursor->GetX();
    m_position.m_Y = m_cursor->GetY();
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                        CBaseCell::~CBaseCell    () {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CBaseCell::ClearEditLine () const
{
    
    m_cursor->Push();
    if ( m_cursor->ToEditLine() == true ) 
    {
        int editLineLength = ( m_list->m_Psize.m_cellWidth + CELL_BORDER ) *
                               m_list->m_Vsize.m_columns.m_columnsMax - CELL_BORDER;
        std::string emptyEditLine;
        
        emptyEditLine.assign(editLineLength, ' ');
        wprintw(stdscr, "%s", emptyEditLine.c_str());
    }
    m_cursor->Pop();
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                    CBaseCell::IsMyIdx       ( const std::string& _idx ) const { return _idx == m_index; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CBaseCell::ClearCell     () const
{
    std::string str = "";
    
    m_cursor->Push();
    str.assign(m_list->m_Psize.m_cellWidth, ' ');
    m_cursor->Move(m_position.m_Y, m_position.m_X - m_list->m_Psize.m_cellWidth + 1);
    wprintw(stdscr, "%s", str.c_str());
    m_cursor->Pop();
}