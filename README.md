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
## send_get_smth.sh usage
send_get_smth.sh is used to send jod, that will extract the vertex positions or energy of calo hit from the Deafault.root. You need to uncomment what you need to run inside the code and then run
```bash
sbatch send_get_smth.sh
```
### Histogram of the vertices
To extract the positions of verices from Defaut.root in each folder and to create a histogram, which will be saved as a .root file, you need to uncomment *root get_str/knk_vertices.cpp*. Visualization is kept separate in a str/knk_visu.cpp. As a result you get the .png histogram.
### Energy spectrum 
To extract energy and save in a .root file use get_str/knk_energy.cpp. Then, if 2 separate 1D histograms are needed, use str/knk_visu.cpp. If you need to plot straight and kinked on one historam, run scale_energy.cpp to scale straight and kinked histograms and create a .root histogram with both spectra first. Then run scaled_visu.cpp to visualize.  







