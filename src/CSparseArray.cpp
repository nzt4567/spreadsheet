/* 
 * File:   CSparseArray.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 19, 2012, 9:47 AM
 */
#include <string>
#include "CSparseArray.h"
#include "CStringCell.h"
#include "CExprCell.h"
#include "CNumCell.h"

                        CSparseArray::CSparseArray  () { m_first = m_last = NULL; m_size = 0; }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                        CSparseArray::~CSparseArray () 
{
    TElement* help;
    
    while (m_first != NULL)
    {
        help = m_first;
        m_first = m_first->m_next;
        delete help->m_item;
        delete help;
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CSparseArray::Add           ( CExtendedCell*      _val )
{
    m_size++;
    if (m_first == NULL && m_last == NULL)
    {
       m_last = m_first = new TElement( _val, NULL ); return;  
    }
    TElement* help = new TElement( _val, m_last );
    m_last->m_next = help; m_last = help;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
CExtendedCell*          CSparseArray::SearchIdx     ( const std::string&  _idx ) const
{
    TElement* help = m_first;
    
    while (help != NULL)
    {
       if (help->m_item->IsMyIdx(_idx) == true)
          break;
       help = help->m_next;
    }
    
    if (help != NULL)
        return help->m_item;
    return NULL;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CSparseArray::Delete        ( const std::string&  _idx )
{
    TElement* help = m_first;
    
    while (help != NULL)
    {
       if (help->m_item->IsMyIdx(_idx) == true)
          break;
       help = help->m_next;
    }
    
    if (help != NULL)
    {
        if (help == m_last && help == m_first)
            m_first = m_last = NULL;
          else if (help == m_last) 
        {
              m_last = m_last->m_prev;
              m_last->m_next = NULL;
        } else if (help == m_first)
        {
          m_first = m_first->m_next;
          m_first->m_prev = NULL;
        
        } else 
        {
          help->m_prev->m_next = help->m_next;
          help->m_next->m_prev = help->m_prev;
        }
        delete help->m_item;
        delete help;
        m_size--;
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                    CSparseArray::ReEvaluate    ()
{    /* I am very ashamed to do it this way. I will end up in hell for doing this for sure. */

    TElement* help = m_first;
    
    for ( register int i = 0; i < m_size; i++ ) 
    {
      while (help != NULL)
      {
        help->m_item->Evaluate(this);
        help = help->m_next;
      }
      help = m_first;
    }
}