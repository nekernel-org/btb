.PHONY: build-zpt-core
build-zpt-core:
	g++ -I./inc $(wildcard src/*.cxx) -std=c++20 -fPIC -shared -o libzpt-core.so
	cp libzpt-core.so /usr/lib

.PHONY: build-btbuild
build-btbuild:
	g++ -I./inc $(wildcard btbuild/*.cxx) -lzpt-core -o btb
