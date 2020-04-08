# C compiler with antlr4/c++

[![Build Status](https://travis-ci.com/HexaTeam4212/PLD_Compilateur.svg?branch=master)](https://travis-ci.com/HexaTeam4212/PLD_Compilateur)

## Instructions for docker run

The two scripts `run.sh` and `stop.sh` can be used to automaticaly run and stop a container for the project.  

The run script will create a container with everything you need to make the project compile. Once running, you can modify your source files and they will directly be available inside the container, no need to rerun the container.  
If you close the console which was inside the container, the run script will give access again to the shell witout restarting the container.  

The stop script simply stop and delete the container.  

--------------  

Exécuter la commande ./run.sh, cela mettra en marche le conteneur et donnera accès à un shell pour naviguer dans le conteneur.  
Faire la commande make dans le dossier nommé compiler afin de générer l'exécutable ifcc, notre compilateur.  
Ensuite exécuter une commande ./ifcc [paramètres] <fichier.c>  

Exemple de commande quand on se situe dans le dossier compilateur:  
- `./ifcc -p -o 2_mult.s ../tests/tests/ExprArithmetique/2_mult.c`
- `./ifcc -p -o 14_exprComplexe.s ../tests/tests/ExprArithmetique/14_exprComplexe.c`

Remarque :  
En  cas de doute sur l'utilisation de la commande, vous pouvez l’exécuter sans arguments et un message vous donnera les instructions d’exécution.  
Deux paramètres sont actuellement disponibles :  
- -p : Permet d’afficher dans la sortie standard la représentation de l’AST
- -o <file_name> : Permet de choisir le fichier de sortie. Par défaut, sans cette option, l’affichage du code assembleur se fait dans la sortie standard du terminal.

Pour effectuer des test :  
Faire ../tests/test_if.sh pour exécuter le programme de test automatique.  

Pour tester un fichier de sortie manuellement :  
- `./ifcc -p -o nom_fichier.s nom_fichier.c`
- `as -o nom_fichier.o nom_fichier.s`
- `gcc -o nom_executable nom_fichier.o`
- `./nom executable`