#include "Lecture.h"



Lecture::Lecture(std::string fileName) :
	fileName(fileName),bufferEntree(nullptr),bufferSortie(nullptr)
{

}

Lecture::~Lecture()
{}


void Lecture::OuvrirFlux()
{
	std::ifstream fic(fileName.c_str());

	std::fstream entree("Entree.txt");
	bufferEntree = std::cin.rdbuf();
	std::cin.rdbuf(entree.rdbuf()); //redirige l'entr�e cin vers entree soit Entree.txt

	std::ofstream fichier(fileName.c_str());
	bufferSortie = std::cout.rdbuf();
	std::cout << "2prim" << std::endl;
	std::cout.rdbuf(fichier.rdbuf()); //redirige les cout vers le fichier

	std::cout << "3" << std::endl;
	//std::cin.rdbuf(bufferEntree);   //Revient � l'entr�e standard
	//std::cout.rdbuf(bufferSortie);
}

void Lecture::FermerFlux()
{
	std::cin.rdbuf(bufferEntree);   //Revient � l'entr�e standard
	std::cout.rdbuf(bufferSortie); //Revient � la sortie standard

}