/*!     \file
 *      \brief Class parsing input in expression cells.      
 */
/*!     \class CExprParser
 *      \brief Class parsing input in expression cells.  
 */
#ifndef CEXPRPARSER_H
#define	CEXPRPARSER_H
#include "CParser.h"

class CExprParser : public CParser
{
public:
                                        /*! Implicit constructor \param _params See TParserParams 
                                         * \param _idx Cell index */
                                        CExprParser    ( TParserParams& _params, 
                                                         const std::string& _idx  );
                                        /*! Implicit destructor */
    virtual                             ~CExprParser   ();
    virtual bool                        CheckInput     ();
    virtual std::string                 ParseInput     ();
                                        /*! Creates array of strings containing cells in expression
                                         * \param _expr Expression from which to extract cell names */
    void                                SetCellsInExpr ( const std::string& _expr );
protected:
    std::string**                       m_cells; ///< Array of cell names
    std::string                         m_myCellIdx; ///< This cell name
    int                                 m_cellsNum; ///< Cell names count
    int                                 m_cellsMax; ///< See MAX_CELLS_IN_EXPR
private:
    CExprParser(const CExprParser& orig);
};
#endif	/* CEXPRPARSER_H */