#include <BALL/FORMAT/PDBFile.h>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/chain.h>
#include <BALL/KERNEL/residue.h>
#include <BALL/KERNEL/atom.h>


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