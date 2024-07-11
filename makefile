.PHONY: build-zpt-core
build-zpt-core:
	g++ -I./inc $(wildcard src/*.cxx) -fPIC -shared -o libzpt-core.so
