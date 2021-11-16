#!/bin/bash
[ -e /usr/lib/libTectonicPlate.so ] && sudo rm -v /usr/lib/libTectonicPlate.so ; [ -e libTectonicPlate.so ] && rm -v libTectonicPlate.so ; make && [ -e examples/triangle ] && rm examples/triangle ; make -C examples/ && ./examples/triangle
