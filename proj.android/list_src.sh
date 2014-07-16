#!/bin/sh
#
# ---------------------------------------
# 
# Script to generate the src file and include used by jni/Android.mk
# 
# Please define the Main source directory
# ---------------------------------------

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

SRC_DIR=$DIR/../Classes
OUT_FILE=$DIR/jni/Sources.mk
EXCLUDE_DIR="Win32|UnitTest\+\+\/tests"
MAIN_CPP="main.cpp"

echo "Script to generate the project src and include list"
echo "WORK_DIR=$DIR"
echo "OUT_FILE=$OUT_FILE"
echo "SRC_DIR=$DIR"


# some debugging message
#echo "${#SRC_DIR}"

# find the prefix path count for trimming
TRIM_COUNT=${#SRC_DIR}

# Clean up
echo "" > $OUT_FILE

echo "# List of CPP File #" >> $OUT_FILE


	echo "LOCAL_SRC_FILES := $MAIN_CPP" >> $OUT_FILE
find $SRC_DIR/* \( -name '*.cpp' -o -name '*.c' \) | egrep -v "($EXCLUDE_DIR)" \
	| sed "s/^.\{$TRIM_COUNT\}//g" \
	| sed 's/^/LOCAL_SRC_FILES += $(CLASS_PATH)/' \
	>> $OUT_FILE

echo "" >> $OUT_FILE
echo "" >> $OUT_FILE



echo "#Include DIR #" >> $OUT_FILE
echo 'LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(CLASS_PATH)' >> $OUT_FILE
echo 'LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(CLASS_PATH)/libs' >> $OUT_FILE
find $SRC_DIR/* -type d | egrep -v "($EXCLUDE_DIR)" \
	| sed "s/^.\{$TRIM_COUNT\}//g" \
	| sed 's/^/LOCAL_C_INCLUDES += $(LOCAL_PATH)\/$(CLASS_PATH)/' \
	>> $OUT_FILE


echo "source is generated. use ./build_native.sh to compile"
echo "file: $OUT_FILE"
#
# 

