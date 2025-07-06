clear:
	rm -rf clearDbTest updateData test

test: clear
	g++ -I. Tests/TestMain.cpp Source/Libs/dominios.cpp Source/Presentation/AuthenticationPre.cpp -o test -lsqlite3 && ./test

run: clear
	g++ -I. Source/main.cpp Source/Libs/dominios.cpp -o main -lsqlite3 && ./main

updateData: clear
	g++ -I. Source/UpdateDadosHistoricos.cpp Source/Libs/dominios.cpp -o updateData -lsqlite3 && ./updateData

clearDbTest: clear
	g++ -I. Tests/ClearDbTest.cpp Source/Libs/dominios.cpp -o clearDbTest -lsqlite3 && ./clearDbTest
docs:
	doxygen Doxyfile
