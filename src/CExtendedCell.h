/*!     \file
 *      \brief Base class for cells storing values.      
 */
/**     \def EVALUATE
 *      \brief Macro for expression evaluation.  
 */
/*!     \class CExtendedCell
 *      \brief Base class for cells storing values.  
 */
#ifndef CEXTENDEDCELL_H
#define	CEXTENDEDCELL_H
#include "CBaseCell.h"
#define EVALUATE           m_error = m_parser->CheckInput();\
                           if (m_error == false)\
                              try { m_resultStr = m_parser->ParseInput(); }\
                                 catch (CParserInvalidChar)        { m_error = true; }\
                                 catch (CParserInvalidParenthesis) { m_error = true; }\
                                 catch (CParserDivisionByZero)     { m_error = true; }\
                                 catch (CParserNaN)                { m_error = true; }\
                           if (m_error == true)\
                           {\
                              m_resultStr = "ERROR";\
                              m_output    = "INVALID INPUT DETECTED. USE -h FOR SOME HELP.";\
                           }\
                           else\
                           {\
                              m_output = m_input;\
                              m_output += "     [";\
                              m_output += m_resultStr;\
                              m_output += "]";\
                           }\
                           SetCellOutput();
class CWorkerCell;
class CParser;
class CSparseArray;

class CExtendedCell : public CBaseCell
{
public:
                                /*! Implicit constructor \param _cursor Pointer on screen cursor 
                                 * \param _list List dimensions \param _input Input string of the cell */
                                CExtendedCell  ( CCursor* _cursor, const TListDimensions* _list, 
                                                 const std::string& _input );
                                /*! Implicit destructor */                            
    virtual                     ~CExtendedCell ();
                                /*! This evaluates the input in cell.  \param _array Pointer on sparse array*/
    virtual void                Evaluate       ( CSparseArray* _array ) = 0;
                                /*! Check if the cell has type string. \return True for CStringCell */
    virtual bool                AmIString      () const                 = 0;
                                /*! Check if the cell has type expression. \return True for CExprCell */
    virtual bool                AmIExpr        () const                 = 0;
                                /*! Check if the cell has type number. \return True for CNumCell */
    virtual bool                AmINum         () const                 = 0;
    virtual void                DrawEditLine   () const;
                                /*!  \return Returns m_ResultStr */
    const std::string&          MyResult       () const;
                                /*!  \return Returns true if the cell is in error state. */
    bool                        DoIHaveErrors  () const;
                                /*!  Converts the cell to CWorkerCell */
    CWorkerCell*                Convert2Worker () const;
                                /*!  Draw cell output to appropriate place on the screen */
    void                        SetCellOutput  () const;
protected:
    std::string                 m_output; ///< Output that is drawn by DrawEditLine
    std::string                 m_resultStr; ///< Output that is drawn by SetCellOutput
    bool                        m_error; ///< True if the cell is in error state
    int                         m_type; ///< Cell type ID
    CParser*                    m_parser; ///< Cell parser, see CParser
private:
    CExtendedCell(const CExtendedCell& orig);
};
#endif	/* CEXTENDEDCELL_H */