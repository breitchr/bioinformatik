#include <BALL/FORMAT/PDBFile.h>
#include <BALL/STRUCTURE/peptides.h>
#include <BALL/STRUCTURE/peptideBuilder.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/chain.h>
#include <BALL/KERNEL/protein.h>

using namespace std;
using namespace BALL;

int main(int argc, char* argv[]){
  
  PDBFile sourceFile;
  System mdSystem;
  string url = "http://www.rcsb.org/pdb/files/";
  string pdbid;

  //Sanity checks for command-line arguments	
  if(argc == 2){
    pdbid.append(argv[1] + string(".pdb"));
    url.append(pdbid);
  }else{
    cout << "Wrong amount of Parameters\n\n Useage: prog pdbid" << endl;
    return 1;
  }

  // download pdb file (-N : if not exists or newer version online)
  system((string("wget -N ") + url).c_str());
  sourceFile.open(pdbid);
  if(sourceFile.is_open()){
    sourceFile.read(mdSystem);
    sourceFile.close();
  }

  if (mdSystem.getProtein(0)){
    Protein* protein = mdSystem.getProtein(0);
    Chain* chain = protein->getChain(0);
    String sequence = Peptides::GetSequence(*chain);
    // test sequence of aminoacids
    cout << sequence << endl;

    // create new long sequence of aminoacids
    String newSeq;
    for (int i = 0; i < 10; i++){
      newSeq.append(sequence);
    }

    Peptides::PeptideBuilder* pb = new Peptides::PeptideBuilder(newSeq);

    FragmentDB fdb("");
    pb->setFragmentDB(&fdb);
    
    pb->setChainName("new_long_Chain");
    pb->setProteinName("new_Protein");
    
    Protein* newProt = pb->construct();
    
    // test newProt
    cout << Peptides::GetSequence(*newProt) << endl;

    //System newSystem;
    mdSystem.insert(*newProt);
    PDBFile outFile(string("new_")+pdbid,ios::out);
    outFile << mdSystem;
    outFile.close();

    // System((string("gmx pdb2gmx -f ")+pdbid+string(".pdb -o ")+pdbid+string(".gro")).c_str());

  }
 
  return 0;
}
