#ifndef __MARCO_HPP__
#define __MARCO_HPP__

#include "datos.hpp"
#include "vector"

class Marco {
 private:
  int idMarco;
  string idProceso;
  string tamanio;

 public:
  Marco();
  Marco(int idMarco, int espacio);

  void setIdMarco(int);
  int getIdMarco() const;

  void setIdProceso(string);
  string getIdProceso() const;

  void setTamanio(string);
  string getTamanio() const;

  bool operator==(const Marco& otro) const;

};

#endif  // __Marco__HPP__

