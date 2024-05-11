#include "marco.hpp"
#include <iomanip>
#include <algorithm>
#include <iostream>

using namespace std;

Marco::Marco(){}

int Marco::getIdMarco() const { return idMarco; }

void Marco::setIdMarco(int _idMarco) {
     idMarco =_idMarco;
     }

string Marco::getIdProceso() const {
    return  idProceso;
     }

void Marco::setIdProceso(string _idProceso) {
    idProceso =_idProceso;
     }

string Marco::getTamanio() const {
    return tamanio;

}

void Marco::setTamanio(string _tamanio) {
    tamanio = _tamanio;
    }

bool Marco::operator==(const Marco& otro) const {
    return idProceso == otro.idProceso;
}