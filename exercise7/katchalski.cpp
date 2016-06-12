#include <BALL/FORMAT/PDBFile.h>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/chain.h>
#include <BALL/KERNEL/residue.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/protein.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/MATHS/vector3.h>
#include <array>
#include <iostream>
#include <fstream>

using namespace std;
using namespace BALL;

int alpha1 = 1;
int beta1 = 0;
int gamma1 = 2;

int main(int argc, char* argv[]){

  //   BALL::Vector3 translationVector(1,1,1);
   System kkSystem;
   PDBFile sourceFile;
   // BALL::PDBFile translateFile;

   vector<Vector3> atompos;
   Vector3 pos;
   vector<float> vwradii;
   float vwr;
  
   //Sanity checks for command-line arguments
   if(argc == 2){

      sourceFile.open(argv[1], ios::in);
      // translateFile.open(argv[2], std::ios::out);
   }else{

      cout << "Wrong amount of Parameters\n\n Useage: prog inFile \n";
      return 1;

   }

   if(sourceFile.is_open()){

      //the read action for a pdbfile reads the data into a system which can be manipulated afterwards - and saved
      sourceFile.read(kkSystem);
      sourceFile.close();
      
      // get only first protein
      Protein* protein = kkSystem.getProtein(0);
      
      if(protein->countChains() > 0){
	
	for(ChainIterator ch_it = protein->beginChain(); +ch_it; ++ch_it){

	  for(ResidueIterator r_it = ch_it->beginResidue(); +r_it; ++r_it){

	    for(AtomIterator a_it = r_it->beginAtom(); +a_it; ++a_it){
	      Element element = a_it->getElement();
	      // name
	      cout << element.getName() << " ";
	      // position
	      pos = a_it->getPosition();
	      // save position in vector
	      atompos.push_back(pos);
	      cout << pos  << " ";
	      // van der waals radius
	      vwr = element.getVanDerWaalsRadius();
	      cout << vwr << endl;
	      vwradii.push_back(vwr);
	    }                   
	  }
	}
      }
      for(int i(0); i < atompos.size(); i++){
	cout << atompos[i] << vwradii[i] << endl;
      }
   }else{

      cout << "Could not open PDB file." << '\n';

   }


   int n = 20;
   int m = 20;
   int l = 20;
   float px;
   float py;
   float pz;

   float kkgrid[n][m][l];
   // initialize kkgrid
   for (int i = 0; i < n; i++){
  
     for (int j = 0; j < m; j++){

       for (int k = 0; k < l; k++){
	 int c = 0;
	 while (c < atompos.size()){
	  
	   px = i-n/2;
	   py = j-m/2;
	   pz = k-l/2;

	   // inside 
	   if (px > (atompos[c][0] - 0.1*vwradii[c]) && px < (atompos[c][0] + 0.1*vwradii[c]) && py > (atompos[c][1] - 0.1*vwradii[c]) && py < (atompos[c][1] + 0.1*vwradii[c]) && pz > (atompos[c][2] - 0.1*vwradii[c]) && pz < (atompos[c][2] + 0.1*vwradii[c]) ){
	     kkgrid[i][j][k] = beta1;
	     break;
	   }
	   // outside
	   else if  (px < (atompos[c][0] - 0.1*vwradii[c]) ||  px > (atompos[c][0] + 0.1*vwradii[c]) || py > (atompos[c][1] - 0.1*vwradii[c]) || py < (atompos[c][1] + 0.1*vwradii[c]) || pz > (atompos[c][2] - 0.1*vwradii[c]) || pz < (atompos[c][2] + 0.1*vwradii[c]) ){
	     kkgrid[i][j][k] = gamma1;
	   }
	   // boundary
	   else{
	     kkgrid[i][j][k] = alpha1;
	   }
	   c++;

	 }
       }  
     }
   }

   ofstream kkfile;
   kkfile.open("kkgrid.txt");
   kkfile << "x y z value" << endl;
   // safe kkgrid to file
   for (int x(0); x < n; x++){

     for (int y(0); y < m; y++){

       for (int z(0); z < l; z++){
	 
	 kkfile << x-n/2 << " " << y-m/2 << " " << z-l/2 << " " << kkgrid[x][y][z] << endl; 
       }
     }
   }

   kkfile.close();
   
   return 0;

}
