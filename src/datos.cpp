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
void Datos::setTamanio(int _tamanio){
 tamanio =_tamanio;
}

int Datos::getTamanio() const{
    return tamanio;
    }

int Datos::getPaginas() const {
    return paginas;
    }

void Datos::setPaginas(int _paginas) {
  paginas = _paginas;
}

int Datos::getResiduo() const {
  return residuo;
}

void Datos::setResiduo(int _residuo) {
  residuo = _residuo;
}

void Datos::SetId(int _id) { ID = _id; }
int Datos::GetID() const { return ID; }

void Datos::setLoteID(int _loteID) { loteID = _loteID; }

int Datos::getTiempoLlegada() const { return T_Llegada; }

void Datos::setTiempoLlegada(int _tiempoLlegada) { T_Llegada = _tiempoLlegada; }

int Datos::getTiempoFinalizacion() const { return T_Finalizacion; }

void Datos::setTiempoFinalizacion(int _tiempoFinalizacion) {
  T_Finalizacion = _tiempoFinalizacion;
}

void Datos::setQuantum(int _quantum){
    quantum = _quantum;
    }

int Datos::getQuantum()const{
    return quantum;
    }

int Datos::getTiempoRetorno() const { return T_Retorno; }

void Datos::setTiempoRetorno(int _tiempoFinalizacion, int _tiempoLlegada) {
  T_Retorno = _tiempoFinalizacion - _tiempoLlegada;
}

int Datos::getTiempoRespuesta() const { return T_Respuesta; }

void Datos::setTiempoRespuesta(int _Tr) { T_Respuesta = _Tr; }

bool Datos::getTiempoRespuestaVerificar() const {
  return T_RespuestaVerificador;
}

void Datos::setTiempoRespuestaVerificar(bool consulta) {
  T_RespuestaVerificador = consulta;
}

bool Datos::getTiempoLlegadaVerificar() const { return verificarLlegada; }

void Datos::setTiempoLlegadaVerificar(bool tiempoLlegada) {
  verificarLlegada = tiempoLlegada;
}

int Datos::getTiempoEspera() const { return T_Espera - 1; }

void Datos::setTiempoEspera(int _tiempoRetorno, int _tiempoDuracion) {
  T_Espera = _tiempoRetorno - _tiempoDuracion + 1;
}

int Datos::getTiempoServicio() const { return T_Servicio; }

void Datos::setTiempoServicio(int _tiempoServicio) {
  T_Servicio = _tiempoServicio;
}

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

void Datos::setOperadores(const string& operadores) {
  this->operadores = operadores;
  cout << "Operadores guardados: " << this->operadores << endl;
}
std::string Datos::getOperadores() const { return operadores; }

void Datos::setTiempoBloq(int _tB) { tiempoBloq = _tB; }
int Datos::getTiempoBloq() const { return tiempoBloq; }

void Datos::setVerificarBloqueado(bool bloqueado) {
  verificarBloqueo = bloqueado;
}

bool Datos::getVerificarBloqueado() const { return verificarBloqueo; }

// Sobrecarga del operador ==
bool Datos::operator==(const Datos& otro) const {
  return ID == otro.ID;  // Aquí puedes comparar los miembros relevantes para
                         // determinar la igualdad
}

void Datos::toStringTerminados(int lote) const {
  cout << "ID  OPE  RES  NL " << endl;
  cout << ID << "    " << resultado << "    " << lote << endl << endl;
}

string Datos::toString() const {
  return "ID: " + to_string(ID) + ", Tamanio: " + to_string(tamanio);
}
