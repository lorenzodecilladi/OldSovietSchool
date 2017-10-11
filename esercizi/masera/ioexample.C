#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#endif
void ioexample(const char *fimpName, const char *foupName){
  ifstream in(fimpName);
  if(!in){
    cout<<"Il file "<<fimpName<<" non esiste "<<endl;
    return;
  }
  ofstream fout(foupName);
  int number1,number2;
  int count = 0;
  while((in>>number1>>number2)){
    count++;   // incremento del contatore 
    // scrittura su standard output
    cout<<count<<") ";
    cout<<"Numero 1 = "<<number1<<"; Numero2 = "<<number2<<endl;
    // scrittura su file
    fout<<count<<" ";
    fout<<"Numero 1 = "<<number1<<"; Numero2 = "<<number2<<endl;
  }
    in.close();
  fout.close();
}
