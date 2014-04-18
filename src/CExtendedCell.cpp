/* 
 * File:   CExtendedCell.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 18, 2012, 11:09 PM
 */
#include <string>
#include <curses.h>
#include "exceptions.h"
#include "TList.h"
#include "CExtendedCell.h"
#include "CWorkerCell.h"
#include "CCursor.h"
                                CExtendedCell::CExtendedCell  ( CCursor*               _cursor, 
                                                                const TListDimensions* _list, 
                                                                const std::string&     _input ) : 
                                   CBaseCell(_cursor, _list)
{
    m_input = m_output = m_resultStr = _input;
    m_error = false;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                CExtendedCell::~CExtendedCell () {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
CWorkerCell*                    CExtendedCell::Convert2Worker () const
{
   return new CWorkerCell( m_cursor, m_list, m_input );  
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                            CExtendedCell::DrawEditLine   () const
{ /* Always clear the edit line before printing anything */
    unsigned int        LineLen    = ( m_list->m_Psize.m_cellWidth + CELL_BORDER ) *
                                       m_list->m_Vsize.m_columns.m_columnsMax - CELL_BORDER;
    std::string         cellOutput =   m_output.substr( 0, LineLen );
    
    m_cursor->Push();
    ClearEditLine();
    if ( m_cursor->ToEditLine() == true )
       wprintw(stdscr, "%s", cellOutput.c_str());
    m_cursor->Pop();
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                            CExtendedCell::SetCellOutput  () const
{ /* Always clear the cell place before printing something */
    std::string                 cellOutput = m_resultStr.substr( 0, m_list->m_Psize.m_cellWidth );
    
    m_cursor->Push();
    ClearCell();
    if ( m_cursor->Move( m_position.m_Y, m_position.m_X - m_list->m_Psize.m_cellWidth + 1 ) == true )
       wprintw(stdscr, "%s", cellOutput.c_str());
    m_cursor->Pop();
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                            CExtendedCell::DoIHaveErrors  () const { return m_error; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
const std::string&              CExtendedCell::MyResult       () const { return m_resultStr; }