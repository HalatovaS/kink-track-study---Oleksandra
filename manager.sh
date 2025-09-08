#!/bin/sh

DATA_DIR="/sps/nemo/scratch/ohalatova/kink_track_study"

mkdir -p DATA
cd DATA

first_val=$1
second_val=$2
name_of_script=$3

for ((num=first_val; num<=second_val; num++))
do 
	mkdir -p "$num"
	
	cp ../Bi-207/simu.profile "$num"
	cp ../Bi-207/reco.conf "$num"
	cp ../Bi-207/pipeline.conf "$num"
	cp ../Bi-207/simu_setup.conf "$num"
	cp ../str_SNCutsAndMiModule.conf "$num"
	cp ../knk_SNCutsAndMiModule.conf "$num"
		
		cd "$num"
		
		sbatch \
		--output="${DATA_DIR}/DATA/$num/cuts-slurm_$num.out" \
		../../"$name_of_script" "$num"
		
	cd ..
			
done

