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
  gSystem -> CompileMacro("src/Direction.cxx", opt.Data());
  gSystem -> CompileMacro("src/Particle.cxx", opt.Data());
  gSystem -> CompileMacro("src/Vertex.cxx", opt.Data());
  gSystem -> CompileMacro("src/Transport.cxx", opt.Data());
  gSystem -> CompileMacro("src/MultipleScattering.cxx", opt.Data());

}




// schifi da rimuovere ogni volta
// rm src/Direction_cxx.d src/Direction_cxx.so src/MultipleScattering_cxx.d src/MultipleScattering_cxx.so src/Particle_cxx.d src/Particle_cxx.so src/Point_cxx.d src/Point_cxx.so src/Transport_cxx.d src/Transport_cxx.so src/Vertex_cxx.d src/Vertex_cxx.so
