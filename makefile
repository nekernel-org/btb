SUDO=sudo
GCC=g++
GCC_MINGW=x86_64-w64-mingw32-g++
CXXFLAGS=-I./lib -I./vendor
CXXSTD= -std=c++20
SRC=$(wildcard cli/*.cc) $(wildcard src/*.cc)
OUT=btb
CP=cp

.PHONY: build-btb
build-btb:
	$(SUDO) $(GCC) $(CXXFLAGS) $(SRC) $(CXXSTD) -o $(OUT)
	$(SUDO) $(CP) $(OUT) /usr/local/bin

.PHONY: build-btb-windows
build-btb-windows:
	$(GCC_MINGW) $(CXXFLAGS) $(SRC) -o $(OUT).exe

.PHONY: help
help:
	@echo "=> help: Show this help message."
	@echo "=> build-btb-windows: Build BTB for Windows."
	@echo "=> build-btb: Build BTB for POSIX."
