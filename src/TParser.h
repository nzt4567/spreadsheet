/*!     \file
 *      \brief Data structures and constants for CParser class.      
 */
/**     \def PARSER_ERROR
 *      \brief Value to return if parser founds an string error.  
 */
/**     \def PARSER_SUCCESS
 *      \brief Value to return if parser founds an string error.  
 */
/**     \def MAX_CELLS_IN_EXPR
 *      \brief Max cells in one expression.  
 */
/**     \def STACK_CHECK
 *      \brief Checks the std:;stack against underflow.  
 */
/*!     \struct TParserParams
 *      \brief Parameters used by CParser class.
 */
/*!     \struct TRPNelements
 *      \brief Small structure to make the shunting yard algorithm work.
 */
#ifndef TPARSER_H
#define	TPARSER_H
#define PARSER_ERROR            return true;
#define PARSER_SUCCESS          return false;
#define MAX_CELLS_IN_EXPR       100
#define STACK_CHECK             if ( stl_stack.empty() == true ) throw CParserInvalidChar();
class CSparseArray;

struct TParserParams
{
    const std::string&          m_input;        ///< \brief Parsed cell input.
    CSparseArray*               m_array;        ///< \brief Access to other cells for evaluation.
};

struct TRPNelements
{
    int                         m_prio;         ///< \brief Operator priority.
    char                        m_val;          ///< \brief Operator.
};
#endif	/* TPARSER_H */