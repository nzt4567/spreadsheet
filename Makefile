CXX     = g++
LD      = g++
DOXYGEN = doxygen
CFLAGS  = -Wall -pedantic -Wno-long-long -O0 -ggdb
LIBS    = -lncurses

all: compile doc
compile: kvasntom 
kvasntom: main.o cbasecell.o ccolumn.o ccursor.o cdrawer.o cexprcell.o cexprparser.o cextendedcell.o clist.o clistcontrols.o cnumcell.o cnumparser.o cparser.o crow.o csheet.o csparsearray.o cstringcell.o cstringparser.o cworkercell.o
	$(LD) main.o cbasecell.o ccolumn.o ccursor.o cdrawer.o cexprcell.o cexprparser.o cextendedcell.o clist.o clistcontrols.o cnumcell.o cnumparser.o cparser.o crow.o csheet.o csparsearray.o cstringcell.o cstringparser.o cworkercell.o -o kvasntom $(LIBS)

main.o: src/CBaseCell.cpp src/CBaseCell.h src/CColumn.cpp src/CColumn.h src/CCursor.cpp src/CCursor.h src/CDrawer.cpp src/CDrawer.h src/CExprCell.cpp src/CExprCell.h src/CExprParser.cpp src/CExprParser.h src/CExtendedCell.cpp src/CExtendedCell.h src/CListControls.cpp src/CListControls.h src/CList.cpp src/CList.h src/CNumCell.cpp src/CNumCell.h src/CNumParser.cpp src/CNumParser.h src/CParser.cpp src/CParser.h src/CRow.cpp src/CRow.h src/CSheet.cpp src/CSheet.h src/CSparseArray.cpp src/CSparseArray.h src/CStringCell.cpp src/CStringCell.h src/CStringParser.cpp src/CStringParser.h src/CWorkerCell.cpp src/CWorkerCell.h src/main.cpp src/TBaseCell.h src/TCursor.h src/TDrawer.h src/TListControls.h src/TList.h src/TParser.h src/TSheet.h src/TSparseArray.h src/exceptions.h
	$(CXX) $(CFLAGS) -c -o main.o src/main.cpp
cbasecell.o:
	$(CXX) $(CFLAGS) -c -o cbasecell.o src/CBaseCell.cpp
ccolumn.o:
	$(CXX) $(CFLAGS) -c -o ccolumn.o src/CColumn.cpp
ccursor.o:
	$(CXX) $(CFLAGS) -c -o ccursor.o src/CCursor.cpp
cdrawer.o:
	$(CXX) $(CFLAGS) -c -o cdrawer.o src/CDrawer.cpp
cexprcell.o:
	$(CXX) $(CFLAGS) -c -o cexprcell.o src/CExprCell.cpp
cexprparser.o:
	$(CXX) $(CFLAGS) -c -o cexprparser.o src/CExprParser.cpp
cextendedcell.o:
	$(CXX) $(CFLAGS) -c -o cextendedcell.o src/CExtendedCell.cpp
clist.o:
	$(CXX) $(CFLAGS) -c -o clist.o src/CList.cpp
clistcontrols.o:
	$(CXX) $(CFLAGS) -c -o clistcontrols.o src/CListControls.cpp
cnumcell.o:
	$(CXX) $(CFLAGS) -c -o cnumcell.o src/CNumCell.cpp
cnumparser.o:
	$(CXX) $(CFLAGS) -c -o cnumparser.o src/CNumParser.cpp
cparser.o:
	$(CXX) $(CFLAGS) -c -o cparser.o src/CParser.cpp
crow.o:
	$(CXX) $(CFLAGS) -c -o crow.o src/CRow.cpp
csheet.o:
	$(CXX) $(CFLAGS) -c -o csheet.o src/CSheet.cpp
csparsearray.o:
	$(CXX) $(CFLAGS) -c -o csparsearray.o src/CSparseArray.cpp
cstringcell.o:
	$(CXX) $(CFLAGS) -c -o cstringcell.o src/CStringCell.cpp
cstringparser.o:
	$(CXX) $(CFLAGS) -c -o cstringparser.o src/CStringParser.cpp
cworkercell.o:
	$(CXX) $(CFLAGS) -c -o cworkercell.o src/CWorkerCell.cpp

doc:
	$(DOXYGEN)

run: 
	./kvasntom

clean:
	rm -f *.o kvasntom
	rm -rf doc
