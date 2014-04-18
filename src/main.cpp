/* 
 * File:   main.cpp
 * Author: Thomas Kvasnicka
 *
 * Created on May 18, 2012, 10:31 PM
 */
#include <iostream>
#include <cstdlib>
#include "exceptions.h"
#include "CSheet.h"

#define INVALID_USAGE                     cout << "Invalid argument value!";\
                                          usage(argv[0]);\
                                          return(EXIT_FAILURE);
using namespace std;

void                                                                       usage ( const char* name )
{   /* Prints out the usage message using current file name as program name */
    cout << "\nTK SPREADSHEET\n";
    cout << "Simple spreadsheet editor written using ncurses v 5.7 by Thomas "  ;
    cout << "Kvasnicka as a term paper for subject BI-PA2. This program is for" ;
    cout << " educational purposes only, use at your own risk. Some rights may ";
    cout << "be reserved by CTU Prague. For more information && bug reports "   ;
    cout << "(BUG? What's that?) feel free to contact me using my mail: "       ;
    cout << "kvasntom@fit.cvut.cz" << endl << endl;
    cout << "Basic HOWTO:" << endl;
    cout << "Navigate to the cell you want using arrows, TAB / ENTER takes you ";
    cout << "to the edit mode. Here you can type expressions for calculation. " ;
    cout << "After typing expression, press TAB / ENTER again to evaluate it. " ;
    cout << "For using the cell as string type, the input has to start and end" ; 
    cout << " with \" eg: \" Enter whatever you want in here, I accept it. \". ";
    cout << "For using the cell as number type, just start typing the input. "  ; 
    cout << "Allowed characters are: 0 1 2 3 4 5 6 7 8 9 + - *  / ( ) and dot. ";
    cout << "Anything else will result in error. Whitespaces are ingored. "     ;
    cout << "To use the cell as expression type, the input has to start with "  ;
    cout << "= and allowed characters are same as for number type cell. Name of";
    cout << " each cell has to start and end with : eg: =(:A1: + :B3:) * 2.35 " ;
    cout << endl << endl;
    
    cout << "Usage:  " << name <<"  [-f color]   [-b color]   [-c width]   [-m maxlines]" << endl;
    cout << "\t -f color \t Color should be a positive integer between 0 - 7. See the bottom of this message for more info about colors." << endl;
    cout << "\t -b color \t Color should be a positive integer between 0 - 7. See the bottom of this message for more info about colors." << endl;
    cout << "\t -m maxlines \t The maximum number of lines you will probably need." << endl;
    cout << "\t -w width \t Width should be a positive integer >= 1, but values grater than 15 are not recommended." << endl;
    cout << "\t          \t Basically width stands for the width of each cell - use with sense." << endl << endl;

    cout << "Colors are standard terminal colors as used by ncurses. Each number stands for one color." << endl;
    cout << "\t 0 \t Black" << endl;
    cout << "\t 1 \t Red" << endl;
    cout << "\t 2 \t Green" << endl;
    cout << "\t 3 \t Yellow" << endl;
    cout << "\t 4 \t Blue" << endl;
    cout << "\t 5 \t Magneta" << endl;
    cout << "\t 6 \t Cyan" << endl;
    cout << "\t 7 \t White" << endl;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int                                                                        main  ( int         argc, 
                                                                                   char**      argv ) 
{   /* Read the usage please, it explains everything that happens in here */

    TSheetParams params = { GREEN, BLACK, WIDTH, MAXLINES };
    int option = 0;
    
    option = getopt(argc, argv, "m:f:b:w:h?");
    while ( option != -1 )
    { /* Parse the arguments and set the options */
        switch(option)
        {
            case 'f' :
                if ( atoi(optarg) >= 0 && atoi(optarg) <= 7 )
                   params.m_Fg = atoi(optarg);
                else { INVALID_USAGE }
                break;
            case 'b' :
                if ( atoi(optarg) >= 0 && atoi(optarg) <= 7 )
                   params.m_Bg = atoi(optarg);
                else { INVALID_USAGE }
                break;
            case 'w' :
                if ( atoi(optarg) >= 1 )
                   params.m_cellWidth = atoi(optarg);
                else { INVALID_USAGE }
                break;
           case 'm' :
                if ( atoi(optarg) >= 0 )
                   params.m_maxLines = optarg;
                else { INVALID_USAGE }
                break;     
            case 'h' :
            case '?' :
                usage(argv[0]);
                return (EXIT_FAILURE);
        }
        option = getopt(argc, argv, "m:f:b:w:h?");
    }
    CSheet main_sheet(params);
    
    try   { main_sheet.DrawSheet(); }
    catch ( CSheetTooWideColumn )   { INVALID_USAGE }
    
    main_sheet.Interactivity();
    return 0;
}