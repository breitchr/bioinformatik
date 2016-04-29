#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//using namespace std;

int main(int argc, char* argv[]) {

  std::string line;
  std::ifstream pdbfile (argv[1], std::ios::in);
  std::ofstream coordfile (argv[2], std::ios::out);
    
  if (pdbfile.is_open()){  
    while (getline(pdbfile,line)){
      std::string buf;
      std::stringstream ss(line);
      std::vector<std::string> items;
      while (ss >> buf){
        items.push_back(buf);
      }
      if (items[0] == "ATOM"){
	coordfile << items[6] << ' ' << items[7] << ' ' << items[8] << std::endl;
      }
    }
    pdbfile.close();
    coordfile.close();
  }

  else std::cout << "Unable to open file"; 

  return 0;
}
