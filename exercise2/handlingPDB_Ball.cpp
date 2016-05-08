#include <BALL/FORMAT/PDBFile.h>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/chain.h>
#include <BALL/KERNEL/residue.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/protein.h>


int main(int argc, char* argv[]){

   BALL::Vector3 translationVector(1,1,1);
   BALL::System translationSystem;
   BALL::PDBFile sourceFile;
   BALL::PDBFile translateFile;

   //Sanity checks for command-line arguments
   if(argc == 3){

      sourceFile.open(argv[1], std::ios::in);
      translateFile.open(argv[2], std::ios::out);

   }else if(argc == 6){

   sourceFile.open(argv[1], std::ios::in);
   translateFile.open(argv[2], std::ios::out);
  
   translationVector = BALL::Vector3(std::stod(argv[3]), std::stod(argv[4]), std::stod(argv[5]));

   }else{

      std::cout << "Wrong amount of Parameters\n\n Useage: prog inFile outFile\n";
      return 1;

   }

   if(sourceFile.is_open()){

      //the read action for a pdbfile reads the data into a system which can be manipulated afterwards - and saved
      sourceFile.read(translationSystem);
      sourceFile.close();

      // iterate over all proteins
      for(BALL::MoleculeIterator m_it = translationSystem.beginMolecule(); +m_it; ++m_it){

         //We need to check if the molecule we just grabbed with m_it is indeed a protein. if it is not,
         //We cannot iterate over chains and residues.
         if (BALL::RTTI::isKindOf<BALL::Protein>(*(m_it))){

             BALL::Protein* protein = BALL::RTTI::castTo<BALL::Protein>(*(m_it));

             if(protein->countChains() > 0){

               for(BALL::ChainIterator ch_it = protein->beginChain(); +ch_it; ++ch_it){

                  for(BALL::ResidueIterator r_it = ch_it->beginResidue(); +r_it; ++r_it){

                     for(BALL::AtomIterator a_it = r_it->beginAtom(); +a_it; ++a_it){

                        //Exercise 2: Printing C-Alphas
                        if(a_it->getName() == "CA"){

                           std::cout << a_it->getPosition() << '\n';

                        }
                        //Exercise 1: Translating Atom-Positions
                        a_it->setPosition(a_it->getPosition() + translationVector);
                     }                   
                  }
               }
            }
         }
      }
   }else{

      std::cout << "Could not open PDB file." << '\n';

   }

   //Writing translatedFile


   if(translateFile.is_open()){

      translateFile.write(translationSystem);
      translateFile.close();

   }else{

      std::cout << "Could not write translated PDB file." << '\n';

   }

   return 0;

}