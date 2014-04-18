/* 
 * File:   CListControls.cpp
 * Author: Thomas Kvasnicka
 * 
 * Created on May 21, 2012, 4:07 PM
 */
#include <string>
#include "CListControls.h"

                        CListControls::CListControls  ( const TControlParams& _params ) : 
                            m_params(_params) {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                        CListControls::~CListControls () {}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/                       
const std::string&      CListControls::ShowMyIdx      () const { return m_idx;  }
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
const std::string&      CListControls::ShowMyName     () const { return m_name; }