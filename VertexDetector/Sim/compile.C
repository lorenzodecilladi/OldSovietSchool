//to be executed in ~/OldSovietSchool/esercizi/VertexDetector/Sim/$
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

  gSystem->AddIncludePath("-I./include");
  gSystem->AddIncludePath("-I../Utils");
  gSystem->AddIncludePath("-I../Geometry");
  gSystem->CompileMacro("src/Point.cxx", opt.Data());
  gSystem->CompileMacro("src/Direction.cxx", opt.Data());
  gSystem->CompileMacro("src/Particle.cxx", opt.Data());
  gSystem->CompileMacro("src/Vertex.cxx", opt.Data());
  gSystem->CompileMacro("sim.C", opt.Data());
}

