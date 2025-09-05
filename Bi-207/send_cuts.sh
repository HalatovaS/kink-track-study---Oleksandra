#!/bin/sh

# SLURM options:

#SBATCH --job-name=exercise_job
#SBATCH --mem=3500M
#SBATCH --licenses=sps

#SBATCH --time=01:00:00
#SBATCH --cpus-per-task=1

source ${THRONG_DIR}/config/supernemo_profile.bash  
snswmgr_load_setup falaise@5.1.5

FAL_DIR=/sps/nemo/sw/redhat-9-x86_64/snsw/opt2/falaise-5.1.5/bin
MY_DIR=/sps/nemo/scratch/ohalatova/kink_track_study/Bi-207

num=$1

${FAL_DIR}/flreconstruct -i ${MY_DIR}/DATA/$num/CM_reco_Bi_$num.brio -p ${MY_DIR}/str_SNCutsAndMiModule.conf -o ${MY_DIR}/DATA/$num/str_cut_reco_$num.brio

#${FAL_DIR}/flreconstruct -i ${MY_DIR}/DATA/$num/CM_reco_Bi_$num.brio -p ${MY_DIR}/knk_SNCutsAndMiModule.conf -o ${MY_DIR}/DATA/$num/knk_cut_reco_$num.brio
