#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>



/**
 * Abstract class that represent instruction inside a function 
 */
class Lecture {

public:
      Lecture(std::string fileName);
      ~Lecture();
	  void OuvrirFlux();
	  void FermerFlux();

private :
	std::string fileName;
	std::streambuf *bufferEntree;
	std::streambuf *bufferSortie;

};