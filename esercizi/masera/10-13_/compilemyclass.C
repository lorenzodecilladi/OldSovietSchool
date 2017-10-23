void compilemyclass(TString myopt="fast"){
  TString opt;
  if(myopt.Contains("force")){
    opt = "kfg";
  }
  else {
    opt = "kg";
  }
  gSystem->CompileMacro("MyRandom3.cxx",opt.Data());
  gSystem->CompileMacro("testrand3.C",opt.Data());
}
