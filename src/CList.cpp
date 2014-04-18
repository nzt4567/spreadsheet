/* 
 * File:   CList.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 18, 2012, 11:13 PM
 */
#include <string>
#include <cmath>
#include <iostream>
#include "exceptions.h"
#include "CList.h"
#include "CCursor.h"
#include "CDrawer.h"
#include "CSparseArray.h"
#include "CExprCell.h"
#include "CStringCell.h"
#include "CNumCell.h"
#include "CWorkerCell.h"

                        CList::CList       () 
{
    m_actualCell  = NULL;
    m_workingCell = NULL;
    m_list        = new TListDimensions();
    m_cursor      = new CCursor( m_list );
    m_array       = new CSparseArray();
    m_drawer      = new CDrawer( m_list, m_cursor );
    
    m_list->m_Psize.m_cellWidth         = 
    m_list->m_Psize.m_cols              = 
    m_list->m_Psize.m_lines             =
    m_list->m_screen.m_H                = 
    m_list->m_screen.m_V                = 0;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                        CList::~CList      () 
{
    delete m_drawer;
    delete m_cursor;
    delete m_list;
    delete m_array;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CList::DrawMyself  ( TListPhysicalSize& _phys )
{ /* This should be very easily upgraded to make the scroll possible, everything is ready for it */
    bool        firstTime = ( m_list->m_Psize.m_cellWidth == 0 && 
                              m_list->m_Psize.m_cols      == 0 &&
                              m_list->m_Psize.m_lines     == 0 ) ? 
                              true : false;
    m_list->m_Psize = _phys;
    
    if ( firstTime == false )
        m_drawer->FreeRowsColumns();
    
    m_list->m_Vsize.m_columns.m_columnsMax = 
            ( m_list->m_Psize.m_cols - 
            ( m_list->m_Psize.m_maxLines.length() + CELL_BORDER )) / 
            ( m_list->m_Psize.m_cellWidth + CELL_BORDER );
    
    m_list->m_Vsize.m_rows.m_rowsMax = 
            ceil( (double) m_list->m_Psize.m_lines / 
                  (double) ROW_HEIGHT ) - WASTED_ROWS;
    
    m_list->m_editLine.m_Y = EDITLINE_Y;
    m_list->m_editLine.m_X = m_list->m_Psize.m_maxLines.length() + 
                             CELL_BORDER + SHEET_BORDER;
    m_drawer->DrawList();
    m_cursor->Init();
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CList::KeyDown     () 
{
    try 
    {
      if ( m_cursor->RowDown() == true )
         ShowCell();
    } catch ( CCursorFatalStackUnderflow ) { CURSOR_FATAL }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CList::KeyLeft     ()
{
    try 
    {
      if ( m_cursor->ColumnLeft() == true )
         ShowCell();
    } catch ( CCursorFatalStackUnderflow ) { CURSOR_FATAL }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CList::KeyRight    ()
{    
    try 
    {
      if ( m_cursor->ColumnRight() == true )
         ShowCell();
    } catch ( CCursorFatalStackUnderflow ) { CURSOR_FATAL }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CList::KeyUp       ()
{
    try 
    {
      if ( m_cursor->RowUp() == true )
         ShowCell();
    } catch ( CCursorFatalStackUnderflow ) { CURSOR_FATAL }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CList::KeyTab      ()
{ /* This launches all the mess, especially the m_array->ReEvaluate(). Do not look inside that method. */
    try 
    {
        m_cursor->Push();
        if ( m_actualCell == NULL )
           m_workingCell = new CWorkerCell( m_cursor, m_list );
        else
        {
           m_workingCell = m_actualCell->Convert2Worker();
           m_workingCell->ClearCell();
           m_array->Delete( m_cursor->CellIdx() );
        }
    
        m_workingCell->BeginEditMode();
        m_actualCell = m_workingCell->SetCellType();
        delete m_workingCell;
        
        if ( m_actualCell != NULL )
        { 
           m_array->Add( m_actualCell );
           m_actualCell->Evaluate( m_array );
        }
        
        m_array->ReEvaluate();
        if ( m_actualCell != NULL )
           m_actualCell->DrawEditLine();
        else
           m_drawer->DrawEmptyEditLine();
        m_cursor->Pop();
    } catch ( CCursorFatalStackUnderflow ) { CURSOR_FATAL }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CList::ShowCell    ()
{
    m_cursor->Push();
    m_actualCell = m_array->SearchIdx( m_cursor->CellIdx() );
        
    if ( m_actualCell == NULL )
       m_drawer->DrawEmptyEditLine();
    else
       m_actualCell->DrawEditLine();
    m_cursor->Pop();
}