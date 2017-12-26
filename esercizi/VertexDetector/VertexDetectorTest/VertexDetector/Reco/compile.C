//to be executed in ~/OldSovietSchool/esercizi/VertexDetector/Reco/$
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

  gSystem->AddIncludePath("-I../Sim/include"); // Sim/include
  gSystem->AddIncludePath("-I./include"); // Reco/include
  gSystem->AddIncludePath("-I../Utils");
  gSystem->AddIncludePath("-I../Geometry");
  gSystem->CompileMacro("../Sim/src/Point.cxx", opt.Data());
  gSystem->CompileMacro("../Sim/src/Vertex.cxx", opt.Data());
  gSystem->CompileMacro("src/Tracklet.cxx", opt.Data());
  gSystem->CompileMacro("src/Smearing.cxx", opt.Data());
  gSystem->CompileMacro("reco2.C", opt.Data());

}




// schifi da rimuovere ogni volta
// non più necessario perchè non più tracciati da git (vd .gitignore)
// per rimuoverli: git clean -x -i  (seguire istruzioni)
// rm src/Direction_cxx.d src/Direction_cxx.so src/MultipleScattering_cxx.d src/MultipleScattering_cxx.so src/Particle_cxx.d src/Particle_cxx.so src/Point_cxx.d src/Point_cxx.so src/Transport_cxx.d src/Transport_cxx.so src/Vertex_cxx.d src/Vertex_cxx.so sim_C.d sim_C.so
