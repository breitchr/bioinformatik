#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/MATHS/vector3.h>
#include <BALL/MATHS/angle.h>
#include <BALL/FORMAT/PDBFile.h>

int main(int argc, char* argv[]){

	BALL::PDBFile outFile;

	//Sanity checks for command-line arguments	
	if(argc == 2){

      outFile.open(argv[1], std::ios::out);

	}else{

    	std::cout << "Wrong amount of Parameters\n\n Useage: prog outFile\n";
    	return 1;

   }

    BALL::Angle phi, theta, phi2, phi3;
    BALL::Atom* nitrogen = new BALL::Atom;//(BALL::PTE[Element::OXYGEN]);
    BALL::Atom* hydro1 = new BALL::Atom;
    BALL::Atom* hydro2 = new BALL::Atom;
    BALL::Atom* hydro3 = new BALL::Atom;

	phi = BALL::Angle(2*M_PI/3, true); //to ensure that the molecule is planar
	theta = BALL::Angle(0, true); //angle to
	phi2 = BALL::Angle(4*M_PI/3, true); //to ensure that the molecule is planar
	phi3 = BALL::Angle(2*M_PI/3, true); //to ensure that the molecule is planar

	BALL::Vector3 nitroPos(0, 0, 0); // nitrogen placed in origin
	BALL::Vector3 hdyro1_1Pos(101.7/100, phi, theta); //101.7/100 = distance in angstrom
	BALL::Vector3 hdyro2_1Pos(101.7/100, theta, phi2);
	BALL::Vector3 hdyro3_1Pos(101.7/100, theta, phi3);

	nitrogen->setElement(BALL::PTE[BALL::Element::NITROGEN]);
	nitrogen->setPosition(nitroPos);
	hydro1->setElement(BALL::PTE[BALL::Element::HYDROGEN]);
	hydro1->setPosition(hdyro1_1Pos);
	hydro2->setElement(BALL::PTE[BALL::Element::HYDROGEN]);
	hydro2->setPosition(hdyro2_1Pos);
	hydro3->setElement(BALL::PTE[BALL::Element::HYDROGEN]);
	hydro3->setPosition(hdyro3_1Pos);

	BALL::Molecule* h3n = new BALL::Molecule;
	BALL::Bond* n_f = hydro1->createBond(*nitrogen);
	BALL::Bond* n_s = hydro2->createBond(*nitrogen);
	BALL::Bond* n_t = hydro3->createBond(*nitrogen);
	
	h3n->append(*nitrogen);
	h3n->append(*hydro1);
	h3n->append(*hydro2);
	h3n->append(*hydro3);

	BALL::System systemHN3("H3N");

	systemHN3.append(*h3n);

	if(outFile.is_open()){

		outFile.write(systemHN3);

	}else{

		std::cout << "Could not write to file" << argv[2] << '\n';

	}	

	return 0;
}