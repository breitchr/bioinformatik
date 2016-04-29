#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

  string line;
  ifstream pdbfile (argv[1], ios::in);
  ofstream translatefile (argv[2], ios::out);

  vector<int> d;

  // set translation vector with command line arguments
  if (argc > 3){
    d.push_back(stof(argv[3]));
    d.push_back(stof(argv[4]));
    d.push_back(stof(argv[5]));
  }
  // default translation vector (1,1,1)
  else{
    d.assign(3,1);
  }
    
  if (pdbfile.is_open()){
    while (getline(pdbfile,line)){
      
      string buf;
      stringstream ss(line);
      vector<string> items;
      
      while (ss >> buf){
        items.push_back(buf);
      }
      
      vector<int>::size_type sz = items.size();
      
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
	translatefile << endl;
      }
      
      else{
	// write non atom line
	for (unsigned i = 0; i < sz; i++){
	  translatefile << items[i] << ' ';
	}
	translatefile << endl;
      }
      
    }
    
    pdbfile.close();
    translatefile.close();

  }

  else cout << "Unable to open file"; 

  return 0;
}
