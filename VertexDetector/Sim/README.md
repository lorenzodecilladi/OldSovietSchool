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
number of events | integer >= 0
multiplicity option | gaus, fixed, uniform
par1 | mean if gaus, multiplicity if fixed, lowest multiplicity if uniform
par2 | sigma if gaus, 0. if fixed, highest multiplicity if uniform
multiple scattering | 1 if ON, 0 if OFF
(gaussian) noise | 1 if ON, 0 if OFF
z of generated vertex | float mean value of gaussian distribution


#### noiseConfig.txt
- contains noise input parameters for the simulation

Parameter | Value
------------ | -------------
noise option (distribution of noise hits' number) | gaus, fixed
par1 | mean if gaus, hits' number if fixed
par2 | sigma if gaus, 0. if fixed


#### sim.C
```
void sim(TString outFileName = "simFile.root")
```
- macro for executing the Vertex Detector simulation
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
        - noise parameters are passed throung the *noiseConfig.txt* file
        - extraction of the number of noise hits, than can follow a gaussian (e.g. mean 5, sigma 1) or fixed distribution
        - cylindric uniform extraction of the noise hits' position on the detector
    - **data saving**: Vertex, hits on BP, hits on 1L and hits on 2L are stored in the simTree's corresponding branches
- histograms and tree are written on the **output simFile**
```
~/OldSovietSchool/esercizi/VertexDetector/Sim$ root -l
root [0] .x compile.C("force");
root [1] sim("sim_file.root");
```
