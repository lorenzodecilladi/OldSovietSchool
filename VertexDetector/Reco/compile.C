//to be executed in ~/OldSovietSchool/esercizi/VertexDetector/Reco/$
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
  gSystem->AddIncludePath("-I./include");
  gSystem->AddIncludePath("-I../Utils");
  gSystem->AddIncludePath("-I../Geometry");
  gSystem->CompileMacro("../Sim/src/Point.cxx", opt.Data());
  gSystem->CompileMacro("../Sim/src/Vertex.cxx", opt.Data());
  gSystem->CompileMacro("src/Tracklet.cxx", opt.Data());
  gSystem->CompileMacro("reco.C", opt.Data());

}
