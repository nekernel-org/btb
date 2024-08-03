.PHONY: build-btb-core
build-btb-core:
	g++ -I./inc $(wildcard src/*.cxx) -std=c++20 -fPIC -shared -o libbtb.so
	cp libbtb.so /usr/lib

.PHONY: build-btb
build-btb:
	g++ -I./inc $(wildcard cli/*.cxx) -lbtb -o btb
	cp btb /usr/bin

.PHONY: help
help:
	@echo "=> build-zpt-core"
	@echo "=> build-btbuild"
