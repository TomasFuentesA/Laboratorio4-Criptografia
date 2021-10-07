#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;


void tomi_hash(vector<char> caracteres) {
    srand(2004);
    std::vector<char> palabra_hasheada;
    for (int i = 0; i < 25 ; i++) {
        int num = rand() % 126 + 32;
        if (int(caracteres[i]) > num) {       
            palabra_hasheada.push_back(char(int(caracteres[i]) - num +32 ));           
        } else {
            palabra_hasheada.push_back(char(num - int(caracteres[i])+32));         
        }   
    }

    string palabra;
    for (int i = 0; i < 25; i++) {
        palabra += palabra_hasheada[i];
        
    }
    cout << palabra << "\n";

}

void es_archivo(string nombre, string extension){
    string archivo = nombre + "." +extension;
    string linea;
    cout << archivo << "\n";
    ifstream f(archivo.c_str());
    while (getline(f, linea)) {
        std::vector<char> cantidad;
        for (int i = 0; i < linea.length() ; i++) {
            cantidad.push_back(linea[i]);
        }
        // Lo vamos imprimiendo
        tomi_hash(cantidad);
    }
}

void no_archivo(string texto) {
    std::vector<char> cantidad;
    for (int i = 0; i < texto.length() ; i++) {
        cantidad.push_back(texto[i]);
    }

    if (cantidad.size() < 25) {
        for (int i = 0; i < (25 - texto.size()); i ++) {
            cantidad.push_back(texto[i%texto.length()]);
        }

    } else {
        while (cantidad.size() > 25) {
            cantidad.pop_back();
        }
    }
    cout << cantidad.size() << "\n";
    tomi_hash(cantidad);
    
    
    
}

int main (int argc, char *argv[])
{
    if(argc!=2) {
        es_archivo(argv[1], argv[2]);
    } else if (argc == 2) {
        no_archivo(argv[1]);
    } else {
        cout << "ERROR" << "\n";
    }
    
    
    return 0;
}