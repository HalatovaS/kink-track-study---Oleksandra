#!/bin/sh

DATA_DIR="/sps/nemo/scratch/ohalatova/kink_track_study/test_of_jobs"

mkdir DATA
cd DATA

first_val=$1
second_val=$2
name_of_script=$3

for ((num=first_val; num<=second_val; num++))
do 
	mkdir "$num"
	
	cp ../simu.profile "$num"
	cp ../reco.conf "$num"
	cp ../pipeline.conf "$num"
	cp ../SNCutsPipeline.conf "$num"
	
	if ["$name_of_script" = "simu"]; then	
	
		sbatch \
		--output="${DATA_DIR}/DATA/$num/slurm-%j.out" \
		../send_simu.sh "$num"
	fi
	if ["$name_of_script" = "cuts"]; then
	
		sbatch \
		--output="${DATA_DIR}/DATA/$num/slurm-%j.out" \
		../send_cuts.sh "$num"
	fi
done

