#!/bin/bash

rm -rf build
mkdir build
for prog in `find . -type f -iname "*.c" `
do
    bn=$(basename "$prog")
    out=$(echo "$bn" | sed "s&\.c*&&")
    g++ -g $prog -o build/$out
done

if [ "x$1" == "xtest" ]; then
    for prog in `find ./build -type f | sort`; do
        EXPECTED_EXIT_CODE=0
        echo "[TEST] ${prog}"
        bn=$(basename "${prog}")
        grep "${bn}" tests_expect_failure.txt >/dev/null 2>&1
        if [ $? -eq 0 ]; then
            EXPECTED_EXIT_CODE=1
        fi
        ./${prog} >> ./build/test.log 2>&1
        if [ $? -ne ${EXPECTED_EXIT_CODE} ]; then
            echo "[FAIL] Test failed: ${prog}"
            exit 1
        fi
    done
fi