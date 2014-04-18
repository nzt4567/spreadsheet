/* 
 * File:   CColumn.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 19, 2012, 9:38 AM
 */
#include <string>
#include "CColumn.h"

                        CColumn::CColumn( const TControlParams& _params ) : 
                             CListControls(_params) 
{
    int abs_number = m_params.m_screen * m_params.m_controls + m_params.m_myNum;
    int strlen     = ( abs_number % ALPHABET_CHARS == 0 ) ?
                       abs_number / ALPHABET_CHARS        : 
                       abs_number / ALPHABET_CHARS  +  1  ;
    char letter    = ( abs_number % ALPHABET_CHARS) + 'A' ;
    
    if ( letter == 'A' )
        strlen++;
    for ( register int i = 0; i < strlen; i++ )
        m_idx += letter;
    
    if ( strlen > m_params.m_cellWidth )
    {
        letter = '#';
        strlen = m_params.m_cellWidth;
        for ( register int i = 0; i < strlen; i++ )
            m_name += letter;
    }
    else 
        m_name = m_idx;
}
