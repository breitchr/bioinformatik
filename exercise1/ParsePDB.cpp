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
    while (getline(pdbfile,line)){
      string buf;
      stringstream ss(line);
      vector<string> items;
      while (ss >> buf){
        items.push_back(buf);
      }
      if (items[0] == "ATOM"){
	coordfile << items[6] << ' ' << items[7] << ' ' << items[8] << endl;
      }
    }
    pdbfile.close();
    coordfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}
