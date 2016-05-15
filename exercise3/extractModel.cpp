#include <BALL/FORMAT/PDBFile.h>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/chain.h>
#include <BALL/KERNEL/residue.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/protein.h>
#include <BALL/MATHS/angle.h>

int main(int argc, char* argv[]){

   BALL::Vector3 xAxisVector(1,0,0);
   BALL::Angle angle = BALL::Angle(BALL::Constants::PI/3, true);
   BALL::System translationSystem;
   BALL::PDBFile sourceFile;
   BALL::PDBFile rotatedFile;
   BALL::Matrix4x4 rotationMatrix;
   rotationMatrix.setRotation(angle, xAxisVector);

   //Sanity checks for command-line arguments
   if(argc == 3){

      sourceFile.open(argv[1], std::ios::in);
      rotatedFile.open(argv[2], std::ios::out);

   }else{

      std::cout << "Wrong amount of Parameters\n\n Useage: prog inFile outFile\n";
      return 1;

   }

   if(sourceFile.is_open()){

      //the read action for a pdbfile reads the data into a system which can be manipulated afterwards - and saved
      sourceFile.selectModel(1);
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

                        //Rotating Atom-Positions; it may be necessary to move them to origin, rotate and put them back
                        //but since are single Atoms it should not matter
                        a_it->setPosition(rotationMatrix * a_it->getPosition());

                     }                   
                  }
               }
            }
         }
      }

      //writing to out-file
      if(rotatedFile.is_open()){

         rotatedFile.write(translationSystem);

      }else{

            std::cout << "Could not write to system" << '\n';
            return 1;

      }

   }else{

      std::cout << "Could not open PDB file." << '\n';
      return 1;

   }
}