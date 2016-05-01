#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//using namespace std;

int main(int argc, char* argv[]) {


  std::string line;
  std::ifstream pdbfile;
  std::ofstream translatefile;
  std::vector<double> d;

  if(argc == 3){

    pdbfile.open(argv[1], std::ios::in);
    translatefile.open(argv[2], std::ios::out);
    d.assign(3,1.000);

  }else if(argc == 6){

    pdbfile.open(argv[1], std::ios::in);
    translatefile.open(argv[2], std::ios::out);
  
    d.push_back(std::stod(argv[3]));
    d.push_back(std::stod(argv[4]));
    d.push_back(std::stod(argv[5]));

  }else{

    std::cout << "Wrong amount of Parameters\n\n Useage: HandlingPDB inFile outFile\n";
    return 1;

  }

  //Basic idea:
  // Checking ATOM
  // Grabbing Coordinates based on columns
  // Parsing to double, adding offset
  // And the c++ way to parsing double to string with fixed size and precision is to set up an outsream correctly
  // Important: If you want a precision of 3, i.e 3 digits after the dot, you need an outstream.precision of 4. Otherwise
  // it get rounded to early.
  // Lastly, replacing the new string in the selected line
  if (pdbfile.is_open()){
    while (getline(pdbfile,line)){
      
      //std::string buf;
      //std::stringstream ss(line);
      //std::vector<std::string> items;
      
      /*
      while (ss >> buf){
        items.push_back(buf);
      }*/
      
      //std::vector<int>::size_type sz = items.size();
      
      if (line.substr(0,4) == "ATOM"){

        double xCoord = stod(line.substr(30,8));
        double yCoord = stod(line.substr(38,8));
        double zCoord = stod(line.substr(46,8));


        xCoord += d[0];
        yCoord += d[1];
        zCoord += d[2];

        std::ostringstream xCoordStrs;
        std::ostringstream yCoordStrs;
        std::ostringstream zCoordStrs;

        xCoordStrs.width(8);
        xCoordStrs.precision(4);
        yCoordStrs.width(8);
        yCoordStrs.precision(4);
        zCoordStrs.width(8);
        zCoordStrs.precision(4);

        xCoordStrs << xCoord;
        yCoordStrs << yCoord;
        zCoordStrs << zCoord;

        line.replace(30,8,xCoordStrs.str());
        line.replace(38,8,yCoordStrs.str());
        line.replace(46,8,zCoordStrs.str());
      }

      translatefile << line << '\n';

    }

  }else{

    std::cout << "Unable to open file";

  }
      /*

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
	    translatefile << line;
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
*/

  return 0;
}
