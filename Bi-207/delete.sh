#!/bin/bash


first_val=$1
second_val=$2

for ((num=first_val; num<=second_val; num++))
do 
	#rm -f DATA/$num/str_SNCutsAndMiModule.conf
	#rm -f DATA/$num/knk_SNCutsAndMiModule.conf
	#rm -f DATA/$num/vertices.root
	rm -f DATA/$num/Default.root
	rm -f DATA/$num/str_energy.root
	#rm -f DATA/$num/knk_cut_reco_$num.brio
	#rm -f DATA/$num/str_cut_reco_$num.brio
	#rm -f DATA/$num/cuts-slurm_$num.out
	
done

