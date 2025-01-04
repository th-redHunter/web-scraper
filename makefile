assemble:
	g++ src/main.cpp src/logic.cpp -o bin/web-scrapper -lcurl -lgumbo
clear:
	rm bin/*
