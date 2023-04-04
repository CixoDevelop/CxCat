SOURCES_DIR=../sources/
SOURCES=("core.c animations.c cutes.c performer.c coloraround.c driver.c")
LIBS=../libs
OBJECTS_DIR=./
EXEC_BIN=core.bin

CC="avr-gcc"
CC_FLAGS="-Wall -Wextra -Os -std=c11 -fearly-inlining \
    -fshort-enums -Wl,--gc-sections -fdata-sections -Wno-unused-parameter\
    -ffunction-sections -DAIKO_SHORT_NUMBERS -mmcu=atmega8 \
    -I$LIBS/aiko/headers/ -L$LIBS/aiko/build-avr-gcc/ -laiko -DF_CPU=8000000\
    -I$LIBS/colorstripe/headers/ -L$LIBS/colorstripe/build-gcc-avr/ -lcolorstripe\
    -I$LIBS/stdavr/headers/ -L$LIBS/stdavr/build-avr-gcc/ -lstdavr"

SIZE="avr-size"
SIZE_FLAGS="-C --mcu atmega8"

set -x

rm $OBJECTS_DIR/*.o -f
rm $OBJECTS_DIR/*.bin -f

for SOURCE in $SOURCES; do
    $CC $CC_FLAGS -c $SOURCES_DIR/$SOURCE -o "$OBJECTS_DIR/$(basename $SOURCE .c).o"
done

$CC $(ls $OBJECTS_DIR/*.o) -o $EXEC_BIN $CC_FLAGS

$SIZE $SIZE_FLAGS $EXEC_BIN

rm $OBJECTS_DIR/*.o -f
