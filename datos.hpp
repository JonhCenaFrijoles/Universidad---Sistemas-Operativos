#ifndef __DATOS_H__
#define __DATOS_H__

using namespace std;
#include <sstream>

#include "string"

class Datos {
 private:
  int ID;
  int loteID;
  int T_Estimado;
  int T_Duracion;
  int T_Transcurrido = 0;
  string resultado;
  string operadores;
  string operador;
  int tiempoBloq;

 public:

  bool mostrarProceso() const;

  void SetTiempoEstimado(int);
  int GetTiempoEstimado() const;

  void SetTiempo(int);
  int GetTiempo() const;

  void setTiempoBloq(int);
  int getTiempoBloq()const;

  void SetTiempoTranscurrido(int);
  int GetTiempoTranscurrido() const;

  int GetID() const;
  void SetId(int);

  int getLoteID() const;
  void setLoteID(int);

  void setOperadores(string, string, string);
  string getOperadores() const;

  void setOperador(string);
  string getOperador() const;

  string getResultado() const;
  void setResultado(string);

  bool operator==(const Datos& otro) const;

  int toStringProceso(int) const;

  void toStringTerminados(int lote) const;
};

#endif  // __DATOS_H__
