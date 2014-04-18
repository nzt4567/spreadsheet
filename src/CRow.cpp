/* 
 * File:   CRow.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 19, 2012, 9:37 AM
 */
#include <string>
#include <sstream>
#include "CRow.h"

                        CRow::CRow  ( const TControlParams& _params ) : 
                             CListControls(_params)
{  /* Just determine the name && index of the cell */
   std::stringstream ss;                         
   int abs_num = m_params.m_screen * m_params.m_controls + 
                 m_params.m_myNum + 1;
   
   ss << abs_num;
   m_idx = ss.str();
   
   if ( m_idx.length() > (unsigned int) m_params.m_cellWidth )
        m_name.assign(m_params.m_cellWidth, '#');
   else 
        m_name = m_idx;
}