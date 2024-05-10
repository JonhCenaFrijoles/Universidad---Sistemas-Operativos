#ifndef __MARCO_HPP__
#define __MARCO_HPP__

#include "datos.hpp"
#include "vector"

class Marco {
 private:
  int idMarco;
  int idProceso;
  int espacio;

 public:
  Marco();
  Marco(int idMarco, int espacio);

  void setIdMarco(int);
  int getIdMarco() const;

  void setIdProceso(int);
  int getIdProceso() const;

  void setEspacio(int);
  int getEspacio() const;

};

#endif  // __Marco__HPP__

