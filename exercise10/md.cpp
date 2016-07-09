#include <BALL/FORMAT/PDBFile.h>
#include <BALL/KERNEL/selector.h>
#include <BALL/STRUCTURE/defaultProcessors.h>
#include <BALL/STRUCTURE/residueChecker.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/KERNEL/protein.h>
#include <BALL/KERNEL/system.h>

using namespace BALL;
using namespace std;

int main(int argc, char** argv)
{

  //Sanity checks for command-line arguments	
  if(argc != 3){
    cout << "Wrong amount of Parameters\n\n Useage: ";
    cout << "prog pdbin pdbout" << endl;
    return 1;
  }

  // open a PDB file with the name of the first argument
  PDBFile file(argv[1]);

  // create a system and read the contents of the PDB file
  System S;
  file >> S;
  file.close();

  cout << "read " << S.countAtoms() << " atoms." << endl;

  // prepare the protein by adding missing information
  FragmentDB fragment_db("");
  S.apply(fragment_db.normalize_names);
  S.apply(fragment_db.add_hydrogens);  
  S.apply(fragment_db.build_bonds);

  ResidueChecker checker(fragment_db);
  S.apply(checker);

  if (!(S.getMolecule(0))){
    cout << "no molecule found" << endl;
    return 1;
  }

  Molecule* m0 = S.getMolecule(0);

  System Smin;
  Smin.insert(*m0);

  PDBFile outfile(argv[2], File::MODE_OUT);
  outfile << Smin;
  outfile.close();

  // md simulation with gromacs
  system(("pdb2gmx -ff amber03 -water none -f " + string(argv[2])).c_str());
  system("editconf -f conf.gro -bt cubic -d 0.5 -o box.gro");
  // add solvent
  // system(("genbox -cp box.gro -p topol.top -o " + string(argv[2])).c_str());
  system("grompp -f ../em.mdp -p topol.top -c box.gro -o em.tpr");
  system("mdrun -v -deffnm em");
  system("trjconv -f em.gro -s em.tpr -o em.pdb");

  // get scores with clusco
  system(("~/clusco/build/src/./clusco_cpu -e em.pdb -t " + string(argv[1]) + " -s rmsd -o cl_rmsd.txt").c_str());
  system(("~/clusco/build/src/./clusco_cpu -e em.pdb -t " + string(argv[1]) + " -s drmsd -o cl_drmsd.txt").c_str());
  system(("~/clusco/build/src/./clusco_cpu -e em.pdb -t " + string(argv[1]) + " -s gdt -o cl_gdt.txt").c_str());
  system(("~/clusco/build/src/./clusco_cpu -e em.pdb -t " + string(argv[1]) + " -s gdtExt -o cl_gdtExt.txt").c_str());
  system(("~/clusco/build/src/./clusco_cpu -e em.pdb -t " + string(argv[1]) + " -s tmscore -o cl_tmscore.txt").c_str());
  system(("~/clusco/build/src/./clusco_cpu -e em.pdb -t " + string(argv[1]) + " -s maxsub -o cl_maxsub.txt").c_str());
  system(("~/clusco/build/src/./clusco_cpu -e em.pdb -t " + string(argv[1]) + " -s CMO -o cl_CMO.txt").c_str());
  system(("~/clusco/build/src/./clusco_cpu -e em.pdb -t " + string(argv[1]) + " -s CMOn -o cl_CMOn.txt").c_str());

  return 0;
}
