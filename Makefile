clear:
	rm -rf clearDbTest updateData test

test: clear
	g++ -I. Tests/TestMain.cpp Source/Libs/dominios.cpp -o test -lsqlite3 && ./test

updateData: clear
	g++ -I. Source/UpdateDadosHistoricos.cpp Source/Libs/dominios.cpp -o updateData -lsqlite3 && ./updateData

clearDbTest: clear
	g++ -I. Tests/ClearDbTest.cpp Source/Libs/dominios.cpp -o clearDbTest -lsqlite3 && ./clearDbTest
docs:
	doxygen Doxyfile
