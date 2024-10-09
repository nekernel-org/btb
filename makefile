.PHONY: build-btb-core
build-btb-core:
	sudo g++ -I./inc I./vendor $(wildcard src/*.cxx) -std=c++20 -fPIC -shared -o libbtb.so
	sudo cp libbtb.so /usr/local/lib

.PHONY: build-btb
build-btb:
	sudo g++ -I./inc I./vendor $(wildcard cli/*.cxx) $(wildcard src/*.cxx) -std=c++20 -L/usr/local -lbtb -o btb
	sudo cp btb /usr/local/bin

.PHONY: build-btb-windows
build-btb-windows:
	x86_64-w64-mingw32-g++.exe -I./inc -I./vendor $(wildcard cli/*.cxx) $(wildcard src/*.cxx) -std=c++20 -o btb.exe

.PHONY: help
help:
	@echo "=> build-btb-core"
	@echo "=> build-btb"
