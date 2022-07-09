#!/bin/bash
echo -e "        \t最大値抽出法\t      \t二分探索木
データ数\t未ソート\tソート済\t未ソート\tソート済"

for (( i = 10000; i <= 100000; i+=10000 )); do
    echo -e "$i\t\c"
    ./gendata $i input.txt
    ./ex09 gpa ./input.txt ./output.txt
    echo -e "\t\c"
    ./ex09 gpa ./output.txt ./outoutput.txt
    echo -e "\t\c"
    ./ex12 gpa ./input.txt ./output.txt
    echo -e "\t\c"
    ./ex12 gpa ./output.txt ./outoutput.txt
    echo -e "\n\c"
done
