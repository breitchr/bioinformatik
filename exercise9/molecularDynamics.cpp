#include <BALL/KERNEL/system.h>
#include <BALL/FORMAT/PDBFile.h>

using namespace std;
using namespace BALL;

int main(int argc, char* argv[]){
  
  PDBFile sourceFile;
  System mdSystem;
  string url = "http://www.rcsb.org/pdb/files/";
  string pdbid;
  //Sanity checks for command-line arguments	
  if(argc == 3){
    pdbid.append(argv[1] + string(".pdb"));
    s.append(pdbid);
  }else{
    cout << "Wrong amount of Parameters\n\n Useage: prog pdbid" << endl;
    return 1;
  }

  system("wget ");
  sourceFile.open(pdbid + string(".pdb"));
  if(sourceFile.is_open()){
    sourceFile.read(mdSystem);
    sourceFile.close();
  }

  

  return 0;
}
