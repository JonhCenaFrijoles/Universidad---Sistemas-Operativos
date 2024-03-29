#include "datos.hpp"

#include <conio.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

using namespace std;
std::mutex mtx;

void Datos::SetId(int _id) { ID = _id; }
int Datos::GetID() const { return ID; }

void Datos::setLoteID(int _loteID) { loteID = _loteID; }

int Datos::getTiempoLlegada() const { return T_Llegada; }

void Datos::setTiempoLlegada(int _tiempoLlegada) { T_Llegada = _tiempoLlegada; }

int Datos::getTiempoFinalizacion() const { return T_Finalizacion; }

void Datos::setTiempoFinalizacion(int _tiempoFinalizacion) {
  T_Finalizacion = _tiempoFinalizacion;
}

int Datos::getTiempoRetorno() const { return T_Retorno; }

void Datos::setTiempoRetorno(int _tiempoFinalizacion, int _tiempoLlegada) { T_Retorno = _tiempoFinalizacion - _tiempoLlegada; }

int Datos::getTiempoRespuesta() const { return T_Respuesta; }

void Datos::setTiempoRespuesta(int _tiempoDuracion, int _tiempoLlegada) {
  T_Respuesta = _tiempoDuracion - _tiempoLlegada;
}

int Datos::getTiempoEspera() const { return T_Espera; }

void Datos::setTiempoEspera(int _tiempoRespuesta, int _tiempoDuracion) { T_Espera = _tiempoRespuesta - _tiempoDuracion; }

int Datos::getLoteID() const { return loteID; }

void Datos::SetTiempoEstimado(int _TiempoEstimado) {
  T_Estimado = _TiempoEstimado;
}
int Datos::GetTiempoEstimado() const { return T_Estimado; }

void Datos::SetTiempo(int _Tiempo) { T_Duracion = _Tiempo; }
int Datos::GetTiempo() const { return T_Duracion; }

void Datos::SetTiempoTranscurrido(int _TiempoT) { T_Transcurrido = _TiempoT; }
int Datos::GetTiempoTranscurrido() const { return T_Transcurrido; }

void Datos::setResultado(string _resultado) { resultado = _resultado; }

string Datos::getResultado() const { return resultado; }

void Datos::setOperador(string _operador) { operador = _operador; }

string Datos::getOperador() const { return operador; }

void Datos::setOperadores(string _operadorUno, string _operadorDos,
                          string _operador) {
  operadores = _operadorUno + _operador + _operadorDos;
}
std::string Datos::getOperadores() const { return operadores; }

void Datos::setTiempoBloq(int _tB) { tiempoBloq = _tB; }
int Datos::getTiempoBloq() const { return tiempoBloq; }

// Sobrecarga del operador ==
bool Datos::operator==(const Datos& otro) const {
  return ID == otro.ID;  // Aquí puedes comparar los miembros relevantes para
                         // determinar la igualdad
}
// mostrar procesos de los datos bloqueados
bool Datos::mostrarProceso() const {
  int tiempoTotal = 8;
  int tiempoTranscurrido = 0;
  while (tiempoTotal != 0) {
    cout << "Tiempo restante: " << tiempoTotal << " segundos" << endl;
    cout << "Tiempo ejecutado: " << tiempoTranscurrido << " segundos" << endl;
    // Pausa de un segundo para simular el tiempo
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\033[2A\033[K";  // Retrocede dos líneas y las limpia
    tiempoTotal--;

    tiempoTranscurrido++;
    if (tiempoTotal == 0) {
      return true;
    }
  }
  return false;  // Return false if tiempoTotal != 0
}

int Datos::toStringProceso(int tiempoTotal) const {
  int tiempoRestante = GetTiempo();
  int tiempoSumado = 0;
  cout << "         Ejecucion        " << endl;
  cout << "ID: " << ID << endl;
  cout << "Operadores: " << operadores << endl;
  while (tiempoRestante > 0) {
    // Imprimir informaci�n de toStringProceso
    cout << "Tiempo restante: " << tiempoRestante << " segundos" << endl;
    cout << "Tiempo de proceso: " << tiempoSumado << " segundos" << endl;
    cout << "Tiempo total: " << tiempoTotal << " segundos" << endl;
    // Pausa de un segundo para simular el tiempo
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\033[3A\033[K";  // Retrocede dos l�neas y las limpia
    tiempoRestante--;
    tiempoSumado++;
    tiempoTotal++;
  }
  cout << endl;
  return tiempoTotal;
}

void Datos::toStringTerminados(int lote) const {
  cout << "ID  OPE  RES  NL " << endl;
  cout << ID << "    " << resultado << "    " << lote << endl << endl;
}

void Datos::calcularTiempos() {
  setTiempoRetorno(getTiempoFinalizacion(),getTiempoLlegada());
  setTiempoRespuesta(GetTiempo(),getTiempoLlegada());
  setTiempoEspera(getTiempoRespuesta(), GetTiempo());
}
