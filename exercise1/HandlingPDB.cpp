#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {


  std::string line;
  std::ifstream pdbfile
  std::ofstream translatefile
  std::vector<double> d;

  if(argc == 3){

    pdbfile.open(argv[1], std::ios::in);
    translatefile.open(argv[2], std::ios::out);
    d.assign(3,1);

  }else if(argc == 6){

    pdbfile.open(argv[1], std::ios::in);
    translatefile.open(argv[2], std::ios::out);
    d.push_back(stof(argv[3]));
    d.push_back(stof(argv[4]));
    d.push_back(stof(argv[5]));

  }else{

    std::cout << "Wrong amount of Parameters\n\n Useage: HandlingPDB inFile outFile\n";
    return 1;

  }
    
  if (pdbfile.is_open()){
    while (getline(pdbfile,line)){
      
      std::string buf;
      std::stringstream ss(line);
      std::vector<std::string> items;
      
      while (ss >> buf){
        items.push_back(buf);
      }
      
      std::vector<int>::size_type sz = items.size();
      
      if (items[0] == "ATOM"){
	for (unsigned i = 0; i < sz; i++){
	  // positions 6,7,8 contain x,y,z for an atom line in a pdb file
	  if (i == 6){
	    // translate x position
	    translatefile << stof(items[i]) + d[0] << ' ';
	    i++;
	    // translate y position
	    translatefile << stof(items[i]) + d[1] << ' ';
	    i++;
	    // translate z position
	    translatefile << stof(items[i]) + d[2] << ' ';
	  }
	  else{
	    translatefile << items[i] << ' ';
	  }
	}
	translatefile << std::endl;
      }
      
      else{
	// write non atom line
	for (unsigned i = 0; i < sz; i++){
	  translatefile << items[i] << ' ';
	}
	translatefile << std::endl;
      }
      
    }
    
    pdbfile.close();
    translatefile.close();

  }

  else std::cout << "Unable to open file"; 

  return 0;
}
