#!/bin/sh

DATA_DIR="/sps/nemo/scratch/ohalatova/kink_track_study/Bi-207"

mkdir -p DATA
cd DATA

first_val=$1
second_val=$2
name_of_script=$3

for ((num=first_val; num<=second_val; num++))
do 
	mkdir -p "$num"
	cd "$num"
	
	cp ../../simu.profile
	cp ../../reco.conf 
	cp ../../pipeline.conf 
	cp ../../SNCutsAndMimodule.conf 
	cp ../../simu_setup.conf 
		
		sbatch \
		--output="${DATA_DIR}/DATA/$num/slurm-%j.out" \
		../../"$name_of_script" "$num"
		
done

