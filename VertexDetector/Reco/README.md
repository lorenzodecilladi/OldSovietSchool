## README FILE for /VertexDetector/Reco


#### compile.C
- contains instruction for compiling classes and macros used in the reconstruction
- to be executed as follows:
```
~/OldSovietSchool/esercizi/VertexDetector/Reco$ root -l
root [0] .x compile.C("force");
```


#### reco.C
```
void reco(TString simfilePath = "../Sim/simFile.root", TString outFileName = "recoFile.root")
Bool_t eventAnalysis(Int_t event, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert, TH1D *histRecoVertices, TH1D *histCandidates, Point &recoVertex)
Bool_t findPeak(TH1D* histCandidates, Double_t &xCandMad)
Int_t findMaximum(TH1* hist, Int_t minBin, Int_t maxBin)

```
- macro for executing the Vertex Detector reconstruction: **reco**
- opens simFile and gets the tree stored in it, which contains info on generated Vertices and hits on beam pipe and detector's layers
- creates recoFile to store reconstruction output
- creates recoTree to store
    - reconstructed vertices
    - labels for the reconstructed vertices (to keep track of the fact that not all the simulated vertices are reconstructed by the algorithm)
- initialises histograms to store
    - all the vertex candidates for each event (one hist for each event) (*histCandidates*)
    - one recostructed vertex (if found) for each event (one hist for the whole data set) (*histRecoVertices*)
- for each event: **eventAnalysis**
    - loop over 1st layer's hits + geometry check (hits must be on the detector surface)
        - loop over 2nd layer's hits + geometry check
            - if checks are passed, then a tracklet is generated as a line joining the two hits (one per layer)
            - azimutal distance check (Tracklet::matchHits()): the tracklet is assumed as a viable candidate for a particle's trajectory only if the distance in phi between the two hits on the two layers is lower than a certain value, set to 0.01 rad
                - if the hits are matched and the tracklet accepted, then a vertex candidate is extrapolated as intersection between the tracklet and the beam line (Tracklet::extractVertex()). Only its z coordinate is considered (*zCandidate*).
                - *zCandidate* is added to the histogram *histCandidates*
                - *zCandidate* is added to a vector storing all the z coordinates of the vertex candidates
    - **findPeak** looks for a peak in the *histCandidates*. A peak must be higher than twice the height of any other bin in the histogram in order to be accepted.
    - if a peak is accepted, then the weighed average of the bins is computed and assumed as the z coordinate of the reconstructed vertex for the event. This value is added to *histRecoVertices*
    - if a vertex has been found, a reconstructed Vertex is created and a label specifying the number of the event is stored
    - **data saving**: reconstructed Vertex and corresponding label are stored in the recoTree's branches
- histograms and tree are written on the **output recoFile**
```
~/OldSovietSchool/esercizi/VertexDetector/Sim$ root -l
root [0] .X compile.C("force");
root [1] reco("../Sim/simFile.root", "recoFile.root");
```
