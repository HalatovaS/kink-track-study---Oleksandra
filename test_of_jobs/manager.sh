#!/bin/sh


mkdir DATA
cd DATA

num_of_jobs=$1

for ((num=0; num < num_of_jobs; num++))
do 
	mkdir "$num"
	sbatch ../send.sh "$num"
done
