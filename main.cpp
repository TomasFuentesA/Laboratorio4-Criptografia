#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ctime>
#include <math.h>       /*¨log2*/
#include "sha1.hpp"
#include "sha256.h"
#include "md5.h"
using namespace std;



void entropia(string palabra) {
    int l = palabra.length();
    int n = 126-33;
    int e = l*log2(n);
    cout << e << '\n';
}

void Sha1(string palabra) {
    SHA1 checksum;
    checksum.update(palabra);
    const string hash = checksum.final();
    cout << "SHA1: " << hash << " | ";
    entropia(hash);
}

void Sha256(string palabra) {
    string output1 = sha256(palabra);
 
    cout << "SHA256: " << output1 << " | ";
    entropia(output1);
}

void Md5(string palabra) {
    string output = md5(palabra);
    cout << "MD5': " << output << " | ";
    entropia(output);
}

/*************************
La funcion tomi_hash toma el string
y gracias a una seed que cambia cada hora, genera numeros aleatorios
entre 33 y 126 (codigo ascii)
Se verifica cual es mayor y cual es menor, entre
El codigo ASCII del caracter y nuestro numero aleatorio
se realiza una pequeña operacion matematica y se verifica que el valor
no se salga del rango 33-126, en caso de escaparse, se genera un nuevo numero aleatorio
Una vez obtenido el digito nuevo, se procede a calcular su caracter asociado y ser concatenado
Al string "Hasheado"
**************************/

void tomi_hash(vector<char> caracteres) {
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    srand(local_time->tm_hour*60);
    std::vector<char> palabra_hasheada;
    for (int i = 0; i < 25 ; i++) {
        int num = 33 + rand() % (125-33);
        if (int(caracteres[i]) > num) {
            if ( (int(caracteres[i]) - num +32 < 33) ||  (int(caracteres[i]) - num +32 > 126) ) {
                
                int num_2 = 33 + rand() % (125-33);
                palabra_hasheada.push_back(char(num_2));    
            } else {
                palabra_hasheada.push_back(char(int(caracteres[i]) - num +32 ));   
            }
                                   
        } else {
            
            if ( (num - int(caracteres[i])+32 < 33) ||  (num - int(caracteres[i])+32 > 126) ) {
                
                int num_2 = 33 + rand() % (125 - 32);
                palabra_hasheada.push_back(char(num_2));    
            } else {
                palabra_hasheada.push_back(char(num - int(caracteres[i])+32));   
            }
                    
        }   
    }

    string palabra;
    for (int i = 0; i < 25; i++) {
        palabra += palabra_hasheada[i];
        
    }
    cout << palabra << " | ";
    entropia(palabra);
}

/*************************
En caso de ser un archivo
Se lee linea a linea el archivo
Si el largo de la linea es menor a 25 
se repite hasta que sea de ese largo.
En caso de ser mayor se recorta el string
De derecha a izquierda.
**************************/

void es_archivo(string nombre, string extension){
    string archivo = nombre + "." +extension;
    string linea;
    ifstream f(archivo.c_str());
    while (getline(f, linea)) {
        
        Md5(linea);
        Sha1(linea);
        Sha256(linea);
        if (linea == ""){
            continue;
        } else {
            std::vector<char> cantidad;
            for (long unsigned int i = 0; i < linea.length() ; i++) {
                cantidad.push_back(linea[i]);
            }

            if (cantidad.size() < 25) {
            for (long unsigned int i = 0; i < (25 - linea.size()); i ++) {
                cantidad.push_back(linea[i%linea.length()]);
            }

            } else {
                while (cantidad.size() > 25) {
                    cantidad.pop_back();
                }
            }
            // Lo vamos imprimiendo
            
            tomi_hash(cantidad);
            
    
        }
    }
}

/*************************
En caso de no ser un archivo
Se verifica el largo del string
Si es menor a 25 se repite hasta que
sea de ese largo.
En caso de ser mayor se recorta el string
De derecha a izquierda
**************************/

void no_archivo(string texto) {
    
    std::vector<char> cantidad;
    for (long unsigned int i = 0; i < texto.length() ; i++) {
        
        cantidad.push_back(texto[i]);
    }

    if (cantidad.size() < 25) {
        for (long unsigned int i = 0; i < (25 - texto.size()); i ++) {
            cantidad.push_back(texto[i%texto.length()]);
        }

    } else {
        while (cantidad.size() > 25) {
            cantidad.pop_back();
        }
    }
    tomi_hash(cantidad);
    Sha1(texto);
    Sha256(texto);
    Md5(texto);
    
}

int main (int argc, char *argv[])
{
    auto begin = std::chrono::high_resolution_clock::now();
    //En el main se detecta si es un archivo o un string simple
    if(argc!=2) {
        es_archivo(argv[1], argv[2]); 
    } else if (argc == 2) {
        
        no_archivo(argv[1]);
    } else {
        cout << "ERROR" << "\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}