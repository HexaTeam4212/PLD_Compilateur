#include "Program.h"
//#include "Lecture.h"

Program::Program() 
{}

Program::~Program() 
{}

void Program::addFunction(Function* functionToAdd) {
      functions.push_back(functionToAdd);
}

void Program::printProgram(std::ostream &o) {
      o << "#####################################" << std::endl;
      o << "Program" << std::endl << "Functions :" << std::endl;
	  //std::string fileName = "sortie.s";
	  //Lecture *Read = new Lecture(fileName);

	 // Read->OuvrirFlux();
      for(int i = 0; i < functions.size(); i++) {
            functions.at(i)->printFunction(o);
      }
	  //Read->FermerFlux();
      o << "#####################################" << std::endl;
}