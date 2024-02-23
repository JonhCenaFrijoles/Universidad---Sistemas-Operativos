#include "lote.hpp"

#include <algorithm>
#include <iostream>

using namespace std;

// Constructor
Lote::Lote() {}

// Método para agregar un objeto a la lista
void Lote::agregarElemento(const Datos& elemento) {
  listaLote.push_back(elemento);
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

// Método para obtener el tamaño de la lista
int Lote::obtenerTamanio() const { return listaLote.size(); }

// Método para verificar si la lista está vacía
bool Lote::estaVacia() const { return listaLote.empty(); }

// Método para asignar un Lote
void Lote::setLoteID(int _lote) { loteID = _lote; }

// Método para obtener el Lote
int Lote::getLoteID() const { return loteID; }

// Método para mostrar un Lote
void Lote::mostrarLote(const Lote& lote) const {
  for (const Datos& proceso : lote.listaLote) {
    cout << "\nID: " << proceso.GetID() << "\n";
    cout << "TME: " << proceso.GetTiempo() << endl;
    cout << "TT: " << proceso.GetTiempoTranscurrido() << endl;
  }
}

void Lote::vaciarLote() { listaLote.clear(); }

Datos Lote::obtenerElemento(int posicion) const {
  // Verificar si la posición es válida
  if (posicion >= 0 && posicion < listaLote.size()) {
    return listaLote[posicion];
  } else {
    // Manejar el caso de una posición inválida, puedes lanzar una excepción o
    // devolver un valor por defecto
    throw std::out_of_range("Posición inválida");
  }
}
