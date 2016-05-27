#include <vector>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/selector.h>
#include <BALL/FORMAT/PDBFile.h>
#include <BALL/MOLMEC/MDSIMULATION/microCanonicalMD.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/STRUCTURE/residueChecker.h>
#include <BALL/MOLMEC/AMBER/amber.h>
#include <BALL/MOLMEC/MINIMIZATION/conjugateGradient.h>

using namespace std;
using namespace BALL;

int main(int argc, char* argv[]){
  
  PDBFile sourceFile;
  System mdSystem;
  
  //Sanity checks for command-line arguments	
  if(argc == 3){
    sourceFile.open(argv[1], ios::in);
  }else{
    cout << "Wrong amount of Parameters\n\n Useage: prog sourceFile simulationTime\n";
    return 1;
  }
  
  if(sourceFile.is_open()){
    sourceFile.read(mdSystem);
    sourceFile.close();
  }
    
  FragmentDB db("");
  mdSystem.apply(db.normalize_names);
  mdSystem.apply(db.add_hydrogens);
  mdSystem.apply(db.build_bonds);

  ResidueChecker rc(db);
  mdSystem.apply(rc);

  // create hydrogen bonds and force field 
  AmberFF amber(mdSystem);
  Selector hydrogen_selector("element(H)");
  mdSystem.apply(hydrogen_selector);

  amber.options[PeriodicBoundary::Option::PERIODIC_BOX_ENABLED]="true";
  amber.setup(mdSystem);

  MicroCanonicalMD md(amber);
  md.setReferenceTemperature(300.0);
  md.setEnergyOutputFrequency(500.0);

  // redirect std::cout to file. Found no other possibility to write MD simulation output directly to file 
  ofstream finalMD("finalMD.txt");
  streambuf *coutbuf = cout.rdbuf();
  cout.rdbuf(finalMD.rdbuf());
  md.simulateTime(stod(argv[2]));
  cout.rdbuf(coutbuf);
  finalMD.close();

  return 0;
}
