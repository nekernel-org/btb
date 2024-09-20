.PHONY: build-btb-core
build-btb-core:
	sudo g++ -I./inc $(wildcard src/*.cxx) -std=c++20 -fPIC -shared -o libbtb.so
	sudo cp libbtb.so /usr/local/lib

.PHONY: build-btb
build-btb:
	sudo g++ -I./inc $(wildcard cli/*.cxx) $(wildcard src/*.cxx) -std=c++20 -L/usr/local -lbtb -o btb
	sudo cp btb /usr/local/bin

.PHONY: help
help:
	@echo "=> build-btb-core"
	@echo "=> build-btb"
