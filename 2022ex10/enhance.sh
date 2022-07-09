#!/bin/bash
echo -e "        \t入力データ\t      \t連結リスト版
データ数\t未ソート\tソート済\t未ソート\tソート済"

for (( i = 10000; i <= 100000; i+=10000 )); do
    echo -e "$i\t\c"
    ./gendata $i input.txt
    ./2022ex9 gpa ./input.txt ./output.txt
    echo -e "\t\c"
    ./2022ex9 gpa ./output.txt ./outoutput.txt
    echo -e "\t\c"
    ./gendata -n $i input.txt
    ./2022ex7 gpa ./input.txt ./output.txt
    echo -e "\t\c"
    ./2022ex7 gpa ./output.txt ./outoutput.txt
    echo -e "\n\c"
done