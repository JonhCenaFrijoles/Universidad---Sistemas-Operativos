#include "marco.hpp"
#include <iomanip>
#include <algorithm>
#include <iostream>

using namespace std;

// Constructor
/*Marco::Marco(int idMarco, int espacio) {
    setIdMarco(idMarco);
    setEspacio(espacio);
}*/

Marco::Marco(){}

int Marco::getIdMarco() const { return idMarco; }

void Marco::setIdMarco(int _idMarco) {
     idMarco =_idMarco;
     }

int Marco::getIdProceso() const {
    return  idProceso;
     }

void Marco::setIdProceso(int _idProceso) {
    idProceso =_idProceso;
     }

int Marco::getEspacio() const {
    return espacio;

}

void Marco::setEspacio(int _espacio) {
    espacio =_espacio;
    }
