#!/bin/sh

DATA_DIR="/sps/nemo/scratch/ohalatova/kink_track_study/test_of_jobs"

mkdir DATA
cd DATA

num_of_jobs=$1

for ((num=0; num < num_of_jobs; num++))
do 
	mkdir "$num"
	
	cp ../simu.profile "$num"
	cp ../reco.conf "$num"
	cp ../pipeline.conf "$num"
	
	
	sbatch \
	--output="${DATA_DIR}/DATA/$num/slurm-%j.out" \
	../send.sh "$num"
done

