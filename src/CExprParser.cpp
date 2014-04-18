#include <string>
#include "CExprParser.h"
#include "CSparseArray.h"
#include "CNumCell.h"
#include "CExprCell.h"
#include "CStringCell.h"

                                CExprParser::CExprParser    ( TParserParams&      _params, 
                                                              const std::string&  _idx ) : 
                                    CParser(_params)
{ 
    m_cells     = new std::string*[MAX_CELLS_IN_EXPR];
    m_cellsMax  = MAX_CELLS_IN_EXPR;
    m_cellsNum  = 0;

    m_myCellIdx = _idx;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
                                CExprParser::~CExprParser   () 
{
    for (register int i = 0; i < m_cellsNum; i++)
        delete m_cells[i];
    
    delete [] m_cells;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool                            CExprParser::CheckInput     ()
{
    std::string                 noWhiteSpace = SkipWhiteSpace();
    unsigned const int          inputLength  = noWhiteSpace.length() - 1;
    int                         counter      = 0;
    
    for ( register unsigned int i = 1; i <= inputLength; i++ )
    {
        int k = noWhiteSpace[i];
        
        if ( (k >= '0' && k <= '9') || k == '+' || k == '-'  || k == '~' || 
              k == '*' || k == '/'  || k == '(' || k == ')'  || k == '.'  )
            continue;       
        if ( k == ':' ) { counter++; continue; }
        if ( counter % 2 != 1 ) { PARSER_ERROR }
    }
    
    if (counter % 2 != 0) { PARSER_ERROR }

    const CExtendedCell* cell_ptr = NULL;
    SetCellsInExpr(noWhiteSpace);
    for ( register int i = 0; i < m_cellsNum; i++ )
    {
        cell_ptr = m_parser.m_array->SearchIdx( *(m_cells[i]) );
        
        if ( cell_ptr != NULL )
        {
            if ( cell_ptr->DoIHaveErrors() == true || 
                 cell_ptr->AmIString()     == true ) { PARSER_ERROR }
            if ( cell_ptr->AmIExpr() == true )
            {
                CExprCell* cell_expr = (CExprCell*) cell_ptr;   
                if ( cell_expr->DoIPointToThisCell(m_myCellIdx, m_parser.m_array) == true )
                  { PARSER_ERROR }
            }    
        }
    }
    PARSER_SUCCESS
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
std::string                     CExprParser::ParseInput     ()
{   /* This is the thing that needs to be different to destroy the hell in m_array->ReEvaluate. But I am too unskilled jedi to do this */
    std::string                 noWhiteSpace = SkipWhiteSpace();
    std::string                 value        = "";
    const CExtendedCell*        help         = NULL;
    
    noWhiteSpace.erase( 0, 1 );
    if ( m_cellsNum == 0 )
        SetCellsInExpr(noWhiteSpace);
    
    for ( register int i = 0; i < m_cellsNum; i++ )
    {
        help = m_parser.m_array->SearchIdx( *(m_cells[i]) );
        
        if (help == NULL)
          value = "0";
        else
          value = help->MyResult();
        
        m_cells[i]->insert( 0, ":" );
        m_cells[i]->insert( m_cells[i]->length(), ":" );
        noWhiteSpace.replace( noWhiteSpace.find( *(m_cells[i]) ), m_cells[i]->length(), value );
    }
    return RPN( ShuntingYard( noWhiteSpace ) );
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void                            CExprParser::SetCellsInExpr ( const std::string& _expr )
{   /* Here is some ++i magic to extract cell names out of the string and create separate strings from them */
    unsigned const int          inputLength = _expr.length();
    
    for ( register unsigned int i = 0; i < inputLength; i++ )
    {
        int k = _expr[i];
        
        if ( k == ':' )
        {
            m_cells[m_cellsNum] = new std::string();
            k = _expr[++i];
            
            while ( k != ':' )
            {
                *(m_cells[m_cellsNum]) += k;
                k = _expr[++i];
            }
            
            if ( m_cells[m_cellsNum]->empty() != true )
                m_cellsNum++;
            else 
                delete m_cells[m_cellsNum];
        }
    }
}