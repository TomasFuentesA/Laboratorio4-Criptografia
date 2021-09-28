#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;




int main ()
{

    
    int option;

    do {
        cout << "Escoja una opción: " << endl;

        cout << "1.- Para un texto.\n";
        cout << "2.- Para un archivo de texto de N líneas.\n";
        cin >> option;
        switch (option)
        {
        
            case 1:
                cout << "Opcion 1.\n";
                break;
            
            case 2:
                cout << "Opcion 2.\n";
                break;

            case 0:
                cout << "Finalizo este programa.\n";
        }
    } while (option != 0);
     
    

    
    
    
    //srand (time(NULL));
    //int v1;
    //v1 = rand() % 100;
    //cout <<  v1 << "\n";
    return 0;
}