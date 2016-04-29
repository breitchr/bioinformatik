#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

  string line;
  ifstream pdbfile (argv[1], ios::in);
  ofstream coordfile (argv[2], ios::out);
    
  if (pdbfile.is_open()){
    
    while (getline(pdbfile,line) ){
      string buf;
      stringstream ss(line);
      vector<string> tokens;
      while (ss >> buf){
        tokens.push_back(buf);
      }
      vector<int>::size_type sz = tokens.size();
      if (tokens[0] == "ATOM"){
	// debug print
	//cout << tokens[6] << ' ' << tokens[7] << ' ' << tokens[8] << endl;
	// write in file
	coordfile << tokens[6] << ' ' << tokens[7] << ' ' << tokens[8] << endl;
      }
    }
    pdbfile.close();
    coordfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}
