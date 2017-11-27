//to be executed in ~/OldSovietSchool/esercizi/VertexDetector/Sim/$
//$root -l
//.L compile.C

void compile(TString myopt="fast"){
  TString opt;
  if(myopt.Contains("force")){
    opt = "kfg";
  }
  else{
    opt = "kg";
  }

  gSystem->AddIncludePath("-I./include");
  gSystem->AddIncludePath("-I../Utils");
  gSystem->AddIncludePath("-I../Geometry");
  gSystem -> CompileMacro("src/Point.cxx", opt.Data());
  gSystem -> CompileMacro("src/Particle.cxx", opt.Data());
  gSystem -> CompileMacro("src/Vertex.cxx", opt.Data());
  gSystem -> CompileMacro("src/Transport.cxx", opt.Data());

}
