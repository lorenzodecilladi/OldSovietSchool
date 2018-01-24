//to be executed in ~/OldSovietSchool/esercizi/VertexDetector/Analysis/$
//$root -l
//.x compile.C("force");

void compile(TString myopt="fast"){
  TString opt;
  if(myopt.Contains("force")){
    opt = "kfg";
  }
  else{
    opt = "kg";
  }

  gSystem->AddIncludePath("-I../Sim/include");
  gSystem->AddIncludePath("-I../Utils");
  gSystem->AddIncludePath("-I../Geometry");
  gSystem->CompileMacro("../Sim/src/Point.cxx", opt.Data());
  gSystem->CompileMacro("../Sim/src/Direction.cxx", opt.Data());
  gSystem->CompileMacro("../Sim/src/Particle.cxx", opt.Data());
  gSystem->CompileMacro("../Sim/src/Vertex.cxx", opt.Data());
  gSystem->AddIncludePath("-I../Reco/include");
  gSystem->CompileMacro("../Reco/src/Tracklet.cxx", opt.Data());
  gSystem->CompileMacro("analysis.C", opt.Data());
  gSystem->CompileMacro("combinedAnalysis.C", opt.Data());
}
