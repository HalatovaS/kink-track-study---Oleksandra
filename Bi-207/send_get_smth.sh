#!/bin/sh

# SLURM options:

#SBATCH --job-name=exercise_job
#SBATCH --mem=1GB
#SBATCH --licenses=sps

#SBATCH --time=02:00:00
#SBATCH --cpus-per-task=1

source ${THRONG_DIR}/config/supernemo_profile.bash  
snswmgr_load_setup falaise@5.1.5

root get_str_vertices.cpp
#root get_knk_vertices.cpp
#root get_str_energy.cpp
#root get_knk_energy.cpp
