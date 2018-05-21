#!/bin/bash

echo $@

union_part="%union {"$'\n'
first_part=""
second_part="%%"$'\n'
third_part="%%"$'\n'

fileno=0
for bison_file in "$@"
do
    let fileno+=1
    if [ $fileno -le 2 ]
    then
        continue
    fi

    file_union=""
    file_first=""
    file_second=""
    file_third=""
    stage=0
    while IFS='' read -r line || [[ -n "$line" ]]; do
        if [ "$line" = "#union" ]
        then
            stage=1
        elif [ "$line" = "%%" ]
        then
            let stage+=1
        else
            if [ $stage -eq 0 ]
            then
                file_union="$file_union    $line"$'\n'
            elif [ $stage -eq 1 ]
            then
                file_first="$file_first$line"$'\n'
            elif [ $stage -eq 2 ]
            then
                file_second="$file_second$line"$'\n'
            elif [ $stage -eq 3 ]
            then
                file_third="$file_third$line"$'\n'
            fi
        fi
    done < $bison_file

    union_part="$union_part"$'\n'"    // from $bison_file"$'\n'"$file_union"
    first_part="$first_part"$'\n'"// from $bison_file"$'\n'"$file_first"
    second_part="$second_part"$'\n'"// from $bison_file"$'\n'"$file_second"
    thrid_part="$third_part"$'\n'"// from $bison_file"$'\n'"$file_third"
done

union_part="$union_part}"$'\n'
echo "`cat $2`"$'\n'"$union_part$first_part$second_part$third_part" > $1
