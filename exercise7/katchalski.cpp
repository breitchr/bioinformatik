#include <BALL/FORMAT/PDBFile.h>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/chain.h>
#include <BALL/KERNEL/residue.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/protein.h>
#include <BALL/KERNEL/PTE.h>

using namespace std;

int main(int argc, char* argv[]){

  //   BALL::Vector3 translationVector(1,1,1);
   BALL::System kkSystem;
   BALL::PDBFile sourceFile;
   // BALL::PDBFile translateFile;

   //Sanity checks for command-line arguments
   if(argc == 2){

      sourceFile.open(argv[1], std::ios::in);
      // translateFile.open(argv[2], std::ios::out);
   }else{

      std::cout << "Wrong amount of Parameters\n\n Useage: prog inFile \n";
      return 1;

   }

   if(sourceFile.is_open()){

      //the read action for a pdbfile reads the data into a system which can be manipulated afterwards - and saved
      sourceFile.read(kkSystem);
      sourceFile.close();
      
      // get only first protein
      BALL::Protein* protein = kkSystem.getProtein(0);
      
      if(protein->countChains() > 0){
	
	for(BALL::ChainIterator ch_it = protein->beginChain(); +ch_it; ++ch_it){

	  for(BALL::ResidueIterator r_it = ch_it->beginResidue(); +r_it; ++r_it){

	    for(BALL::AtomIterator a_it = r_it->beginAtom(); +a_it; ++a_it){
	      BALL::Element element = a_it->getElement();
	      // name
	      cout << element.getName() << " ";
	      // position
	      cout << a_it->getPosition() << " ";
	      // van der waals radius
	      cout << element.getVanDerWaalsRadius() << endl;
	      
	    }                   
	  }
	}
      }
    
      
   }else{

      std::cout << "Could not open PDB file." << '\n';

   }


   return 0;

}
