# Kinked tracks study 
## Introduction
This repository contains a simulation-based study of electron tracks from the calibration source Bi-207 for the SuperNEMO experiment. The work focuses on counting the number of straight and kinked tracks, and also comparing the results using histograms and energy spectra. 
## Instalation
Clone this repository to your local drive, using git clone command.
## Simulating events
In a **Bi-207 folder** there are:
- simu.profile -- simulation profile, produced by fisimulate-configure;
- simu_setup.conf -- sets the number of events per job. You will need to enter **your path to the simu.profile**;
- pipeline.conf -- reconstruction pipeline, that contains MockCalibration, TKReconstruct, ChargeParticleTracker and GammaClusterizer;
- reco.conf -- configuration file from CimrmanModule. You will need to enter your paths to **/simu.profile, /CimrmanModule/build/ and /pipeline.conf**.

A new sample of events can be simulated using manager.sh:
```bash
./manager.sh 100 199 send_simu.sh
```
It will create 100 folders from 100 to 199.
## Applying cuts
There were used calibration cuts implemented to SNCuts. SNCuts pipeline is merged with MiModule pipeline and kept separate for straight (*str_SNCutsAndMiModule.conf*) and kinked (*knk_SNCutsAndMiModule.conf*) tracks. You wiil also need to enter your paths in pipelines to **/simu.profile, SNCuts/lib/, MiModule/lib/ and CalibrationTools/lib/**. To apply cuts run
```bash
./manager.sh 0 99 send_cuts.sh
```
Running this command will apply cuts to a .brio files in a specified folders, which were produced by send_simu.sh. It will also create Default.root file in each folder. 
