README FILE for /VertexDetector/Sim


compile.C
- contains instruction for compiling classes and macros used in the simulation
- to be executed in ~/OldSovietSchool/esercizi/VertexDetector/Sim/.
$root -l compile.C

config.txt
- contains simulation input parameters:
--> number of events
--> multiplicity option (gaus, fixed, uniform)
--> par1 (mean if gaus, multiplicity if fixed, lowest multiplicity if uniform)
--> par2 (sigma if gaus, 0. if fixed, highest multiplicity if uniform)
--> multScat (1 if ON, 0 if OFF)
--> noise (1 of gaussian noise ON, 0 if gaussian noise OFF)(number of noise hits is gaussian)
--> zGenVertez (gaussian mean of the genereted vertex's z coordinate)

sim.C
- macro for executing the Vertex Detector simulation
- gets and prints sim parameters from config.txt
- initialises a root file and a tree for storing the output
- initialises histograms (for multiplicity and for the z coordinate of the generated vertex)
- for each event:
    - vertex generation, with a certain associated multiplicity (= number of particles)
    - each histograms is filled with an entry (multiplicity, z coord of the vertex)
    - for each particle:
        - transport from vertex to beam pipe (BP)
        - multiple scattering on beam pipe
        - transport from beam pipe to 1st layer (1L) of the detector and hit generation
        - multiple scattering on 1st layer of the detector
        - transport from 1st layer to 2nd layer (2L) of the detector and hit generation
    - if noise is switched on, noise generation follows. Default: gaussian extraction of the number of hits (mean 5, sigma 1) and cylindric uniform extraction of the noise hits position on the detector.
    - DATA SAVING: Vertex, hits on BP, hits on 1L and hits on 2L are stored in the simTree corresponding branches
- histograms and tree are written on the output simFile


