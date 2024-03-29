#ifndef __DATOS_H__
#define __DATOS_H__

using namespace std;
#include <sstream>

#include "string"

class Datos {
 private:
  int ID;
  int loteID;

  int T_Llegada;
  int T_Finalizacion;
  int T_Retorno;
  int T_Respuesta;
  int T_Espera;

  int T_Estimado;
  int T_Duracion;  // Tiempo Servicio
  int T_Transcurrido = 0;
  string resultado;
  string operadores;
  string operador;
  int tiempoBloq;

 public:
  int GetID() const;
  void SetId(int);

  int getLoteID() const;
  void setLoteID(int);

  // Tiempos de proceso

  int getTiempoLlegada() const;
  void setTiempoLlegada(int);

  int getTiempoFinalizacion() const;
  void setTiempoFinalizacion(int);

  int getTiempoRetorno() const;
  void setTiempoRetorno(int, int);

  int getTiempoRespuesta() const;
  void setTiempoRespuesta(int);

  int getTiempoEspera() const;
  void setTiempoEspera(int, int);

  // ----------

  bool mostrarProceso() const;

  void SetTiempoEstimado(int);
  int GetTiempoEstimado() const;

  void SetTiempo(int);
  int GetTiempo() const;

  void setTiempoBloq(int);
  int getTiempoBloq() const;

  void SetTiempoTranscurrido(int);
  int GetTiempoTranscurrido() const;

  void setOperadores(string, string, string);
  string getOperadores() const;

  void setOperador(string);
  string getOperador() const;

  string getResultado() const;
  void setResultado(string);

  bool operator==(const Datos& otro) const;

  int toStringProceso(int) const;

  void toStringTerminados(int lote) const;

  void calcularTiempos();
};

#endif  // __DATOS_H__
