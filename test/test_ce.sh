#!/usr/bin/env bash

mpc=$1
dir=$2
TIMEOUT=5

RED="\033[1;31m"
GREEN="\033[1;32m"
BLUE="\033[1;34m"
WHITE="\033[0m"

ok=0
total=0

for test_dir in `find $dir -name *test-*`
do
    let total+=1
    echo -e "${BLUE}[TEST]${WHITE} $test_dir"

    pas_src=$test_dir"/p.pas"

    if [ ! -f $pas_src ]
    then
        echo -e "${RED}p.pas not found${WHITE}"
        continue
    fi

    timeout $TIMEOUT $mpc -o p $pas_src
    if [ $? -ne 2 ]
    then
        echo -e "${RED}Expecting compilation failure${WHITE}"
        continue
    fi

    let ok=ok+1
    echo -e "${GREEN}PASSED${WHITE}"
done

rm p 2> /dev/null

echo "----------------------------------------"
if [ $total -eq $ok ]
then
    echo -e "${GREEN}All tests passed${WHITE}    Total: $total"
    echo "----------------------------------------"
    exit 0
else
    fail=$total
    let fail-=$ok
    echo -e "Total: $total    ${GREEN}Passed: $ok${WHITE}    ${RED}Failed: $fail${WHITE}"
    echo "----------------------------------------"
    exit 1
fi
