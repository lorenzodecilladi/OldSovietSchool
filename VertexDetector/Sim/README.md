## README FILE for /VertexDetector/Sim


#### compile.C
- contains instruction for compiling classes and macros used in the simulation
- to be executed as follows:
```
~/OldSovietSchool/esercizi/VertexDetector/Sim$ root -l
root [0] .x compile.C("force");
```


#### config.txt
- contains simulation input parameters

Parameter | Value
------------ | -------------
**nEvents** = number of events | integer >= 0
**multOpt** = vertex' multiplicity option | gaus, fixed, uniform, hist (multiplicity distribution from input histogram hmul stored in kinem.root)
**par1** | mean (if gaus), multiplicity (if fixed), lowest multiplicity (if uniform), 0. (if hist)
**par2** | sigma (if gaus), 0. (if fixed), highest multiplicity (if uniform), 0. (if hist)
**multScatt** = multiple scattering | 1 if ON, 0 if OFF
**noise** = gaussian noise | 1 if ON, 0 if OFF
**zGenVertex** = z-coordinate of generated vertex | (float) mean value of gaussian distribution for vertex' z coordinate
**inputEta** | 1 if pseudorapidity distribution is obtained as input from histogram heta stored in kinem.root; 0 if uniformly generated in [-2., 2.]


#### kinem.root
contains:
- histogram hmul, from which multiplicity distribution is extracted if multOpt = hist in *config.txt*
- histogram heta, from which pseudorapidity distribution is extracted if inputEta = 1 in *config.txt*


#### noiseConfig.txt
- contains noise input parameters for the simulation

Parameter | Value
------------ | -------------
noise option (distribution of noise hits' number) | gaus, fixed
par1 | mean (if gaus), noise hits' number (if fixed)
par2 | sigma (if gaus), 0. (if fixed)


#### sim.C
```
void sim(TString outFileName = "simFile.root")
```
- macro for executing the Vertex Detector simulation
- output root file's name can be passed as argument
- gets and prints sim parameters from *config.txt*
- initialises a root file and a tree for storing the output
- initialises histograms (for multiplicity and for the z coordinate of the generated vertex)
- for each event:
    - **Vertex generation**, with a certain associated multiplicity (= number of particles)
    - each histograms is filled with an entry (multiplicity, z coord of the vertex)
    - for each particle:
        - transport from vertex to beam pipe (BP)
        - multiple scattering on beam pipe
        - transport from beam pipe to 1st layer (1L) of the detector and **hit** generation (with gaussian smearing)
        - multiple scattering on 1st layer of the detector
        - transport from 1st layer to 2nd layer (2L) of the detector and **hit** generation (with gaussian smearing)
    - if **noise** is switched on, noise generation follows
        - noise parameters are passed through *noiseConfig.txt*
        - extraction of the number of noise hits, than can follow a gaussian (e.g. mean 5, sigma 1) or fixed distribution
        - uniform extraction in cylindric coordinates of the noise hits' position on the detector's layers
    - **data saving**: Vertex, hits on BP, hits on 1L and hits on 2L are stored in the simTree's corresponding branches
- histograms and tree are written on the **output simFile**
```
~/OldSovietSchool/esercizi/VertexDetector/Sim$ root -l
root [0] .x compile.C("force");
root [1] sim("sim_file.root");
```
- in order to open the simulation output file:
```
~/OldSovietSchool/esercizi/VertexDetector/Sim$ root -l simFile.root
root [0] TBrowser a;
```
