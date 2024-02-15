#ifndef __LOTE_H__
#define __LOTE_H__

#include "datos.hpp"
#include "vector"

class Lote {
 private:
  vector<Datos> listaLote;
  int loteID;

 public:
  // Constructor
  Lote();

  // Método para agregar un objeto a la lista
  void agregarElemento(const Datos& elemento);

  // Método para eliminar un dato de la lista
  void eliminarElemento(const Datos& elemento);

  // Método para obtener el tamaño de la lista
  int obtenerTamaño() const;

  // Método para verificar si la lista está vacía
  bool estaVacia() const;

  void vaciarLote();

  // Método para asignar un lote
  void setLoteID(int);

  // Método para obtener el lote
  int getLoteID() const;

  // Método para mostrar un lote
  void mostrarLote(const Lote& lote) const;

  // Método para obtener el objeto
  Datos obtenerElemento(int posicion) const;
};

#endif  // __LOTE_H__