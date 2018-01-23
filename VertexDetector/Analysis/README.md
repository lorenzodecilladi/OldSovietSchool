## README FILE for /VertexDetector/Analysis


#### compile.C
- contains instruction for compiling classes and macros used in the analysis
- to be executed as follows:
```
~/OldSovietSchool/esercizi/VertexDetector/Analysis$ root -l
root [0] .x compile.C("force");
```


#### analysis.C
```
void analysis(TString simfilePath, TString recofilePath, TString outFileName)
```
- macro for executing the Vertex Detector analysis for a single data set (a simFile and the corresponding recoFile)
- opens simFile, gets simTree and histograms (reconstructed vertices' z coordinate (zRecoVertex) distribution)
  1) gets number of simulated events (*nSimEvents*)
  2) evaluates number of simulated events with vertex's z coordinate withing 1 sigma (= 5.3 cm) (*nSimEvents1sig*)
- opens recoFile, gets recoTree and histograms (generated multiplicity distribution, generated vertices' z coordinate (zSimVertex) distribution)
on)
  1) gets number of reconstructed events (*nRecoEvents*)
- initialises a root file (analysisFile) for storing the output
- initialises histogram (for residual of vertices' z coordinate)
- initialises vector to store output variables (resolution, efficiency, efficiency for particles generated within 1 sigma)
- for each reconstructed event:
  - evaluates the residual along the Z coordinate (residualZ = zRecoVertex - zSimVertex)
  - the residual value is stored in the residuals' histogram
- evaluates the number of reconstructed events among those events whose vertex's z coord was generated within 1 sigma (*nRecoEvents1sig*)
- **resolution** = sigma of gaussian fit of residuals' histogram
- **efficiency** = *nRecoEvents*/*nSimEvents*, with binomial error
- **efficiency for particles generated within 1 sigma** = *nRecoEvents1sig*/*nSimEvents1sig*, with binomial error
- **data saving**: the following are stored on the output file:
  - vector containing resolution and efficiencies, with corresponding uncertainties
  - histograms:
    - generated multiplicity
    - distribution of z coordinate of simulated vertices
    - distribution of z coordinate of reconstructed vertices
    - residuals along the z coordinate
```
~/OldSovietSchool/esercizi/VertexDetector/Analysis$ root -l
root [0] .X compile.C("force");
root [1] analysis("../Sim/simFile.root", "../Reco/recoFile.root", "analysisFile.root");
```
- in order to open the analysis output file:
```
~/OldSovietSchool/esercizi/VertexDetector/Sim$ root -l analysisFile.root
root [0] TBrowser a;
```



#### inputFileList.txt
- contains list of input files for combinedAnalysis().
- every input file is an output file of analysis(), obtained from the analysis of a single data set (one simFile and the corresponding recoFile).


#### combinedAnalysis.C
```
void combinedAnalysis(TString inputListFile, TString outFileName = "combAnalysisFile.root")
```
- macro for executing the Vertex Detector combined analysis for multiple data sets
- input files are the analysis' output files
- for each input file:
  - opens analysisFile
    1) gets the simulated multiplicity
    2) gets mean and sigma of the distribution of generated vertices' z coordinate
    3) gets resolution, efficiency and efficiency for particles generated within 1 sigma
- initialises a root file (combAnalysisFile) for storing the output
- output plots:
  - resolution vs mean generated z
  - resolution vs multiplicity
  - efficiency vs multiplicity
  - efficiency (for particles generated within 1 sigma) vs multiplicity
- plots are stored in the output file
```
~/OldSovietSchool/esercizi/VertexDetector/Analysis$ root -l
root [0] .X compile.C("force");
root [1] combinedAnalysis("inputFileList.txt", "combAnalysisFile.root");
```
- in order to open the combined analysis output file:
```
~/OldSovietSchool/esercizi/VertexDetector/Sim$ root -l combAnalysisFile.root
root [0] TBrowser a;
```