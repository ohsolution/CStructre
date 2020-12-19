ORI=mips-ori
SIM=mips-sim

for i in $(seq 1 8) 
do
    for j in $(seq 1 30) 
    do
    ./$ORI ../data/proj3_$i.bin $j reg >> ret$i.txt
    echo $j >> ret$i.txt
    ./$SIM ../data/proj3_$i.bin $j reg >> out$i.txt
    echo $j >> out$i.txt
    done
done

for i in $(seq 1 8) 
do
    for j in $(seq 1 30) 
    do
    ./$ORI ../data/proj3_$i.bin $j mem 0x10000000 1000 >> ret$i.txt
    ./$SIM ../data/proj3_$i.bin $j mem 0x10000000 1000 >> out$i.txt;
    done
done


for i in $(seq 1 8)
do
    diff -bsq ret$i.txt out$i.txt >> result.txt
done