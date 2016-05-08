#include <BALL/FORMAT/PDBFile.h>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/chain.h>
#include <BALL/KERNEL/residue.h>
#include <BALL/KERNEL/atom.h>


int main(int argc, char* argv[]){

   BALL::Vector3 translationVector(1,1,1);
   BALL::System translationSystem;


   if(argc == 3){

    pdbfile.open(argv[1], std::ios::in);
    translatefile.open(argv[2], std::ios::out);

   }else if(argc == 6){

   pdbfile.open(argv[1], std::ios::in);
   translatefile.open(argv[2], std::ios::out);
  
   translationVector = Vector3(std::stod(argv[3]), std::stod(argv[4]), std::stod(argv[5]))

   }else{

   std::cout << "Wrong amount of Parameters\n\n Useage: HandlingPDB inFile outFile\n";
   return 1;

   }




}






// read the PDB-file into a BALL::System
PDBFile f("myProtein.pdb");
System S;
f >> S; 

// check the first molecule
if (RTTI::isKindOf<Protein>(*(S.getMolecule(0))))
{
   // cast the system's first molecule to BALL::Protein
   Protein* protein = RTTI::castTo<Protein>(*(S.getMolecule(0)));

   // get the first chain
   Chain* chain =  protein->getChain(0);
   if (!chain || (chain->countResidues() == 0))
   {
      return;
   }

   // get the first residue
   Residue* residue = chain->getResidue(0);
   if (residue)
   {
      // iterate over all atoms
      AtomIterator a_it = residue->beginAtom();
      for (; +a_it; ++a_it)
      {
         cout << a_it->getElement().getSymbol() << endl;

         // get a pointer to the current atom by
         Atom* atom = &*a_it;
      }
   }
}