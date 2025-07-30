#!/bin/sh

# SLURM options:

#SBATCH --job-name=exercise_job
#SBATCH --mem=10G
#SBATCH --licenses=sps

#SBATCH --time=10:00
#SBATCH --cpus-per-task=1

FAL_DIR=/sps/nemo/sw/redhat-9-x86_64/snsw/opt2/falaise-5.1.5/bin
CONF_FAL=/sps/nemo/sw/Falaise/install_develop/share/Falaise-4.1.0/resources/snemo/demonstrator/reconstruction/
MY_DIR=/sps/nemo/scratch/ohalatova/kink_track_study/Bi207

source ${THRONG_DIR}/config/supernemo_profile.bash   # load Falaise
snswmgr_load_setup falaise@5.1.5

${FAL_DIR}/flsimulate -c ${MY_DIR}/simu_setup.conf -o ${MY_DIR}/simu_Bi.brio

${FAL_DIR}/flreconstruct -i ${MY_DIR}/simu_Bi.brio -p ${CONF_FAL}/official-2.0.0.conf -o ${MY_DIR}/reco_Bi.brio

${FAL_DIR}/flreconstruct -i ${MY_DIR}/reco_Bi.brio -p /sps/nemo/scratch/ohalatova/softwares/CimrmanModule/reco.conf -o ${MY_DIR}/CM_reco_Bi.brio

# ${FAL_DIR}/flreconstruct -i ${MY_DIR}/CM_reco_Bi.brio -p /sps/nemo/scratch/ohalatova/softwares/SNCuts/build/SNCutsPipeline.conf -o ${MY_DIR}/SNC_reco_Bi.brio
