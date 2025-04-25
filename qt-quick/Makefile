all: nissyqt

build:
	mkdir -p build

build/nissy.h:
	cp ../nissy-core/cpp/nissy.h build/

build/nissy.cpp:
	cp ../nissy-core/cpp/nissy.cpp build/

../nissy-core/config.mk:
	cd ../nissy-core && ./configure.sh

build/nissy.o: build ../nissy-core/config.mk
	cd ../nissy-core && make nissy.o
	cp ../nissy-core/nissy.o build/

nissyqt: build/nissy.o build/nissy.h build/nissy.cpp
	cmake . -B build
	cd build && make
	cp build/appnissyqt ./run

run:
	QT_LOGGING_RULES="*.debug=true; qt.*.debug=false" ./run

clean:
	rm -rf run build

.PHONY: all nissyqt run clean
