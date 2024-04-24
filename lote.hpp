#ifndef __LOTE_HPP__
#define __LOTE_HPP__

#include "datos.hpp"
#include "vector"

class Lote {
 private:
  vector<Datos> listaLote;
  vector<Datos> listaBloqueados;
  int loteID;

 public:
  // Constructor
  Lote();
 int obtenerNumeroProcesos() const;
  void mostarProceso();
  // Método para agregar un objeto a la lista
  void agregarElemento(const Datos& elemento);

  //Metodo para agregar elemento a la lista de bloqueos
  void agregarElementoBloq(const Datos& elemento);

  // Método para eliminar un dato de la lista
  void eliminarElemento(const Datos& elemento);

  //eliminar elemento de la lista de bloqueados
  void eliminarElementoBloq(const Datos& elemento);
  // Método para obtener el tamaño de la lista
 int obtenerTamanio() const;

  // Método para verificar si la lista está vacía
  bool estaVacia() const;

  bool estaVaciaLote() const;

  void vaciarLote();

  // Método para asignar un lote
  void setLoteID(int);

  // Método para obtener el lote
  int getLoteID() const;

  //metodo para mostar los procesos blqueados
  void mostrarBloqueados(Lote& lote)const;

  // Método para mostrar un lote
  void mostrarLote(const Lote& lote) const;

  // Método para obtener el objeto
  Datos obtenerElemento(int posicion) const;

  Datos obtenerElementoBloq(int posicion) const;

};

#endif  // __LOTE_HPP__
