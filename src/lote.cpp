#include "lote.hpp"
#include <iomanip>
#include <algorithm>
#include <iostream>

using namespace std;

// Constructor
Lote::Lote() {}

// Método para agregar un objeto a la lista
void Lote::agregarElemento(const Datos& elemento) {
  listaLote.push_back(elemento);
}
void Lote::agregarElementoBloq(const Datos& elemento) {
  listaBloqueados.push_back(elemento);
}

// Método para eliminar un dato de la lista
void Lote::eliminarElemento(const Datos& elemento) {
  // Buscar el elemento en la lista
  auto it = listaLote.begin();
  while (it != listaLote.end()) {
    if (*it == elemento) {
      listaLote.erase(it);
      break;
    }
    ++it;
  }
}

// Método para eliminar un dato de la lista
void Lote::eliminarElementoBloq(const Datos& elemento) {
  // Buscar el elemento en la lista
  auto it = listaBloqueados.begin();
  while (it != listaBloqueados.end()) {
    if (*it == elemento) {
      listaBloqueados.erase(it);
      break;
    }
    ++it;
  }
}

// Método para obtener el tamaño de la lista
int Lote::obtenerTamanio() const { return listaLote.size(); }

// Método para verificar si la lista está vacía
bool Lote::estaVacia() const { return listaLote.empty() && listaBloqueados.empty(); }

bool Lote::estaVaciaLote() const { return listaLote.empty(); }

// Método para asignar un Lote
void Lote::setLoteID(int _lote) { loteID = _lote; }

// Método para obtener el Lote
int Lote::getLoteID() const { return loteID; }

// Método para mostrar un Lote
void Lote::mostrarLote(const Lote& lote) const {
  for (const Datos& proceso : lote.listaLote) {
    cout << "\nID: " << proceso.GetID() << "\n";
    cout << "TR: " << proceso.GetTiempo() << endl;
    cout << "TT: " << proceso.GetTiempoTranscurrido() << endl;
  }
}



//funcioo para mostrar lotes bloqueados
void Lote::mostrarBloqueados(Lote& lote)const{
    for (const Datos& proceso : lote.listaBloqueados) {
        cout << "\nID: " << proceso.GetID() << "\n";
}
}



void Lote::vaciarLote() { listaLote.clear(); }

Datos Lote::obtenerElemento(int posicion) const {
  // Verificar si la posición es válida
  if (posicion >= 0 && posicion < listaLote.size()) {
    return listaLote[posicion];
  } /*else {
    // Manejar el caso de una posición inválida, puedes lanzar una excepción o
    // devolver un valor por defecto
    throw std::out_of_range("Posición inválida");
  }*/
}


Datos Lote::obtenerElementoBloq(int posicion) const {
  // Verificar si la posición es válida
  if (posicion >= 0 && posicion < listaBloqueados.size()) {
    return listaBloqueados[posicion];
  } else {
    // Manejar el caso de una posición inválida, puedes lanzar una excepción o
    // devolver un valor por defecto
    throw std::out_of_range("Posición inválida");
  }
}
