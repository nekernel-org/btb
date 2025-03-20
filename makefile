
.PHONY: build-btb
build-btb:
	sudo g++ -I./lib -I./vendor $(wildcard cli/*.cc) $(wildcard src/*.cc) -std=c++20 -o btb
	sudo cp btb /usr/local/bin

.PHONY: build-btb-windows
build-btb-windows:
	x86_64-w64-mingw32-g++.exe -I./lib -I./vendor $(wildcard cli/*.cc) $(wildcard src/*.cc) -std=c++20 -o btb.exe

.PHONY: help
help:
	@echo "=> build-btb-windows"
	@echo "=> build-btb"
