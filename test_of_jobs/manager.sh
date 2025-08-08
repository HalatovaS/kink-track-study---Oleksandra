#!/bin/sh

DATA_DIR="/sps/nemo/scratch/ohalatova/kink_track_study/test_of_jobs"

mkdir DATA
cd DATA

first_val=$1
second_val=$2

for ((num=first_val; num<=second_val; num++))
do 
	mkdir "$num"
	
	cp ../simu.profile "$num"
	cp ../reco.conf "$num"
	cp ../pipeline.conf "$num"
	
	
	sbatch \
	--output="${DATA_DIR}/DATA/$num/slurm-%j.out" \
	../send.sh "$num"
done

