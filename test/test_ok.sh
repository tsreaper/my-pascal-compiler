#!/usr/bin/env bash

OS_Type=`uname`
if [ $OS_Type -eq "Darwin" ]
then
    alias timeout=gtimeout
fi

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
    in_file=$test_dir"/in.txt"
    out_file="out.txt"
    ans_file=$test_dir"/ans.txt"

    if [ ! -f $pas_src ]
    then
        echo -e "${RED}p.pas not found${WHITE}"
        continue
    fi
    if [ ! -f $in_file ]
    then
        echo -e "${RED}in.txt not found${WHITE}"
        continue
    fi
    if [ ! -f $ans_file ]
    then
        echo -e "${RED}ans.txt not found${WHITE}"
        continue
    fi

    timeout $TIMEOUT $mpc -o p $pas_src
    if [ $? -ne 0 ]
    then
        echo -e "${RED}Compilation failure or compilation time out${WHITE}"
        continue
    fi

    timeout $TIMEOUT ./p < $in_file > $out_file
    if [ $? -ne 0 ]
    then
        echo -e "${RED}Execution failure or execution time out${WHITE}"
        continue
    fi

    diff $out_file $ans_file
    if [ $? -ne 0 ]
    then
        echo -e "${RED}Wrong answer${WHITE}"
        continue
    fi

    let ok=ok+1
    echo -e "${GREEN}PASSED${WHITE}"
done

rm p 2> /dev/null
rm $out_file 2> /dev/null

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
