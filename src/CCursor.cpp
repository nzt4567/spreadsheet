/* 
 * File:   CCursor.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 18, 2012, 10:59 PM
 */
#include <string>
#include <curses.h>
#include "exceptions.h"
#include "CCursor.h"
#include "CColumn.h"
#include "CRow.h"
                                CCursor::CCursor      ( const TListDimensions* _list ) : m_list(_list) {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                CCursor::~CCursor     () {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                            CCursor::Move         ( const int _y, const int _x )
{    
    if ( _y <= m_list->m_Psize.m_lines && _x <= m_list->m_Psize.m_cols && _x > 0 && _y > 0 ) 
    {
        wmove(stdscr, _y, _x);
        m_cursor.m_physical.m_X = _x; m_cursor.m_physical.m_Y = _y;
        return true;
    }
    return false;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
const int                       CCursor::GetX         () const { return m_cursor.m_physical.m_X; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
const int                       CCursor::GetY         () const { return m_cursor.m_physical.m_Y; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                            CCursor::setIdx       ()
{
    m_cursor.m_virtual.m_cellIdx = 
            m_list->m_Vsize.m_columns.m_column[m_cursor.m_virtual.m_column]->ShowMyIdx();
    m_cursor.m_virtual.m_cellIdx += 
            m_list->m_Vsize.m_rows.m_row[m_cursor.m_virtual.m_row]->ShowMyIdx();
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                            CCursor::Init         ()
{
    Move( A1_Y, m_list->m_Psize.m_maxLines.length() + 
                CELL_BORDER + m_list->m_Psize.m_cellWidth );
    m_cursor.m_virtual.m_row = A1; m_cursor.m_virtual.m_column = A1;
    setIdx();
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                            CCursor::RowUp        ()
{
    if ( m_cursor.m_virtual.m_row - 1 >= 0 && Move(GetY() - ROW_HEIGHT, GetX()) == true )
    {
            m_cursor.m_virtual.m_row--;
            setIdx();
            return true;
    }
    return false;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                            CCursor::RowDown      ()
{
    if ( m_cursor.m_virtual.m_row + 1 < m_list->m_Vsize.m_rows.m_rowsMax && 
         Move(GetY() + ROW_HEIGHT, GetX()) == true)
    {
            m_cursor.m_virtual.m_row++;
            setIdx();
            return true;
    }
    return false;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                            CCursor::ColumnLeft   ()
{
    if ( m_cursor.m_virtual.m_column - 1 >= 0 && 
         Move(GetY(), GetX() - m_list->m_Psize.m_cellWidth - CELL_BORDER) == true )
    {
            m_cursor.m_virtual.m_column--;
            setIdx();
            return true;
    }
    return false;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                            CCursor::ColumnRight  ()
{
    if ( m_cursor.m_virtual.m_column + 1 < m_list->m_Vsize.m_columns.m_columnsMax && 
         Move(GetY(), GetX() + m_list->m_Psize.m_cellWidth + CELL_BORDER) == true )
    {
            m_cursor.m_virtual.m_column++;
            setIdx();
            return true;
    }
    return false;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                            CCursor::ToEditLine   () { return Move(m_list->m_editLine.m_Y, m_list->m_editLine.m_X ); }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
const std::string&              CCursor::CellIdx      () const { return m_cursor.m_virtual.m_cellIdx; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                            CCursor::EditLineMove ( const int _y, const int _x )
{
    if ( _y == m_list->m_editLine.m_Y )
    {
        int sheet_width = ( m_list->m_Psize.m_cellWidth + CELL_BORDER ) *
                            m_list->m_Vsize.m_columns.m_columnsMax + 
                          ( m_list->m_Psize.m_maxLines.length() + CELL_BORDER );
        if ( _x >= m_list->m_editLine.m_X && _x < sheet_width )
            if ( Move(_y, _x) == true )
                return true;
    }
    return false;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                            CCursor::Pop          ()
{
    if (m_stack.empty() == true)
        throw CCursorFatalStackUnderflow();
    
    m_cursor = m_stack.top(); m_stack.pop();
    Move( GetY(), GetX() );
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                            CCursor::Push         () { m_stack.push(m_cursor); }