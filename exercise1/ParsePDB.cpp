#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//using namespace std;

int main(int argc, char* argv[]) {

  std::string line;
  std::ifstream pdbfile; //(argv[1], std::ios::in);
  std::ofstream coordfile; //(argv[2], std::ios::out);

  //Sanity check for correct number of arguments

  switch(argc){

    case 2:
      pdbfile.open(argv[1], std::ios::in);
      break;

    case 3:
      pdbfile.open(argv[1], std::ios::in);
      coordfile.open(argv[2], std::ios::out);
      break;

    default:
      std::cout << "Wrong number of arguments.\n\n Useage: ParsePDB inFile [outFile]" << "\n";
      return 1;
  }
    
  if (pdbfile.is_open()){  
    while (getline(pdbfile,line)){
      //std::string buf;
      //std::stringstream ss(line);
      //std::vector<std::string> items;
      //while (ss >> buf){
       // items.push_back(buf);
      //}
      if (line.substr(0,4) == "ATOM"){

        //x:31-38, y:39-46, z:47-54; one less because arrays in C++ are 0-based
        //a single space is added because it may be, that all coordinates are the maximum allowed size.
        //no trimming is done. could be added later on.
        switch(argc){
          case 2:
            std::cout << line.substr(30,8) << ' ' << line.substr(38,8) << ' ' << line.substr(46,8) << '\n';//substr(position, length); just a reminder for myself
            break;
          case 3:
            coordfile << line.substr(30,8) << ' ' << line.substr(38,8) << ' ' << line.substr(46,8) << '\n';
            break;

        }
	
      }
    }
    pdbfile.close();
    coordfile.close();
  }

  else std::cout << "Unable to open file"; 

  return 0;
}
