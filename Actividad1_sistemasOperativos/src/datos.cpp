#include "datos.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>  // Para std::this_thread

using namespace std;
std::mutex mtx;

void Datos::SetNombre(string _nombre) { nombre = _nombre; }
string Datos::GetNombre() const { return nombre; }

void Datos::SetId(int _id) { ID = _id; }

int Datos::GetID() const { return ID; }

void Datos::SetTiempo(int _Tiempo) { T_Duracion = _Tiempo; }
int Datos::GetTiempo() const { return T_Duracion; }

void Datos::setOperacion(string _operacion) { Operacion = _operacion; }

string Datos::getOperacion() const { return Operacion; }

void Datos::setOperador(string _operador) { operador = _operador; }

string Datos::getOperador() const { return operador; }

void Datos::setOperadores(string _operadorUno, string _operadorDos,
                          string _operador) {
  operadores = _operadorUno + _operador + _operadorDos;
}

void Datos::setLote(int _lote) { lote = _lote; }

int Datos::getLote() const { return lote; }

void Datos::toStringMostarlote() const {
  std::lock_guard<std::mutex> lock(mtx);  // Adquiere el bloqueo del mutex para
                                          // garantizar la salida sincronizada
  cout << setw(5) << "Lote Actual: " << lote << "\n";
  cout << setw(5) << "ID: " << ID << "\n";
  cout << setw(5) << "TME: " << T_Duracion << endl;
  // Puedes agregar m�s informaci�n si es necesario
}

void Datos::toStringProceso() const {
  int tiempoRestante = GetTiempo();
  int tiempoSumado = 0;
  cout << "         Ejecucion        " << endl;
  cout << "Nombre: " << nombre << endl;
  cout << "ID: " << ID << endl;
  cout << "Operadores: " << operadores << endl;
  while (tiempoRestante > 0) {
    // Imprimir informaci�n de toStringProceso
    cout << "Tiempo restante: " << tiempoRestante << " segundos" << endl;
    cout << "Tiempo de proceso: " << tiempoSumado << " segundos" << endl;
    // Pausa de un segundo para simular el tiempo
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\033[2A\033[K";  // Retrocede dos l�neas y las limpia
    tiempoRestante--;
    tiempoSumado++;
  }

  cout << endl;
}

void Datos::toStringTerceraColumna() const {
  cout << "         Terminados          " << endl;
  cout << "ID  OPE  RES  NL " << endl;
  cout << ID << "    " << Operacion << "    " << lote << endl;
}

int Datos::getContador() const {
  int tiempoRestante = GetTiempo();
  while (tiempoRestante > 0) {
    this_thread::sleep_for(chrono::seconds(1));
    tiempoRestante--;
  }
}

/*void Datos::toStringProceso() const {
       int tiempoRestante = GetTiempo();
       int tiempoSumado = 0;
       std::lock_guard<std::mutex> lock(mtx); // Adquiere el bloqueo del mutex
para garantizar la salida sincronizada std::cout << "         Ejecucion        "
<< std::endl; std::cout << "Nombre: " << nombre << std::endl; std::cout << "ID:
" << ID << std::endl; std::cout << "Operadores: " << operadores << std::endl;
       while (tiempoRestante > 0) {
           // Imprimir información de toStringProceso
           std::cout << "Tiempo restante: " << tiempoRestante << " segundos" <<
std::endl; std::cout << "Tiempo de proceso: " << tiempoSumado << " segundos" <<
std::endl;
           // Pausa de un segundo para simular el tiempo
           std::this_thread::sleep_for(std::chrono::seconds(1));
           std::cout << "\033[2A\033[K";  // Retrocede dos líneas y las limpia
           tiempoRestante--;
           tiempoSumado++;
       }
       std::cout << std::endl;
   }

void Datos::toStringTerceraColumna() const {
       std::lock_guard<std::mutex> lock(mtx); // Adquiere el bloqueo del mutex
para garantizar la salida sincronizada std::cout << "         Terminados " <<
std::endl; std::cout << "ID  OPE  RES  NL " << std::endl; std::cout << ID << "
" << Operacion << "    " << lote << std::endl;
   }*/
