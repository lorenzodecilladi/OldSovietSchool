## README FILE for /VertexDetector/Utils


#### Rootils.h
- contains functions aimed at extracting random numbers from Uniform or Gaussian distibuted sequences


#### Math.h
- defines a namespace containing *pi*(=3.1415...) and two functions that convert deg to rad and viceversa


#### distGen
- contains macros for generating random sequences which follow a certain distribution. The generated sequences are written on an outputFile.txt

```
gausGen(Int_t numEvts=10000, Int_t mean=20, Int_t sigma=5, const char *foutName = "outFile.txt")
```
