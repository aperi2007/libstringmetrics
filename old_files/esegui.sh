rm -Rf m4
mkdir m4

rm -Rf config
mkdir config

rm -Rf autom4te.cache

rm Makefile.in
cd src
rm Makefile.in
cd ..


rm -Rf build

rm makefile
rm src/makefile


./autogen.sh
mkdir build
cd build
../configure
make
