#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "datos.hpp"
using namespace std;

// Definición de la función para verificar ID repetido
bool verificarIdRepetido(const vector<Datos>& listaLote, int id) {
  for (const Datos& lote : listaLote) {
    if (lote.GetID() == id) {
      cout << "Error: El ID " << id
           << " ya ha sido registrado. Ingresa un ID �nico." << endl;
      return true;
    }
  }
  return false;  // ID único, no se ha encontrado repetido
}

// Definición de la función para mostrar los procesos de un lote
void mostrarLotes(const vector<Datos>& listaLote, vector<Datos>::const_iterator it, const Datos& objAux) {
  while (it != listaLote.end()) {
    const Datos& loteActual = *it;
    loteActual.toStringMostarlote();
    ++it;
  }
}

int main() {
  int numeroLote = 1;  // variable para imprimir el numero de lote en proceso
  Datos lote;
  vector<Datos> listaLote;  // lista de lote
  vector<Datos> listaLoteTerminados;

  cout << "Ingresa el numero de procesos" << endl;
  int numeroProcesoTotal;  // Numero de procesos total
  cin >> numeroProcesoTotal;

  int i = 0;
  string nombre;
  int id;  // id del lote
  string operacion;
  int tiempoEstimado;
  int contadorProceso;

  // Añadir proceso
  while (i < numeroProcesoTotal) {
    if (contadorProceso == 4) {
      numeroLote++;
      contadorProceso = 0;
      lote.setLote(numeroLote);
    } else {
      lote.setLote(numeroLote);
    }

    int opcionOperacion;
    int numeroUno;
    int numeroDos;

    cin.ignore();
    cout << "Inserta tu nombre" << endl;
    getline(cin, nombre);
    lote.SetNombre(nombre);
    do {
      cout << "Ingresa tu ID" << endl;
      cin >> id;
    } while (
        verificarIdRepetido(listaLote, id));  // verifica el id con la funcion

    lote.SetId(id);  // ingresa el id al objeto

    cout << "Ingresa el tiempo estimado" << endl;
    cin >> tiempoEstimado;
    lote.SetTiempo(tiempoEstimado);  // ingresa el tiempo estimado al objeto

    cout << "selecciona la operacion" << endl;
    cout << "(1)Multiplicacion" << endl;
    cout << "(2)Division" << endl;
    cout << "(3)Suma" << endl;
    cout << "(4)restar" << endl;
    cout << "(5) residuo" << endl;
    cin >> opcionOperacion;

    cout << "ingresa el primer numero" << endl;
    cin >> numeroUno;
    cout << "ingresa el segundo numero" << endl;
    cin >> numeroDos;

    switch (opcionOperacion) {  // Asignar operación
      case 1: {
        lote.setOperacion(to_string(numeroUno) + "x" + to_string(numeroDos) +
                          "=" + to_string(numeroUno * numeroDos));

        lote.setOperadores(to_string(numeroUno), to_string(numeroDos), " x ");
        break;
      }
      case 2: {
        lote.setOperacion(to_string(numeroUno) + "/" + to_string(numeroDos) +
                          "=" + to_string(numeroUno / numeroDos));
        lote.setOperadores(to_string(numeroUno), to_string(numeroDos), " / ");
        break;
      }
      case 3: {
        lote.setOperacion(to_string(numeroUno) + "+" + to_string(numeroDos) +
                          "=" + to_string(numeroUno + numeroDos));
        lote.setOperadores(to_string(numeroUno), to_string(numeroDos), " + ");
        break;
      }
      case 4: {
        lote.setOperacion(to_string(numeroUno) + "-" + to_string(numeroDos) +
                          "=" + to_string(numeroUno - numeroDos));
        lote.setOperadores(to_string(numeroUno), to_string(numeroDos), " - ");
        break;
      }
      case 5: {
        lote.setOperacion(to_string(numeroUno) + "%" + to_string(numeroDos) +
                          "=" + to_string(numeroUno % numeroDos));
        lote.setOperadores(to_string(numeroUno), to_string(numeroDos), " % ");
        break;
      } break;
    }

    listaLote.push_back(lote);
    i++;
    contadorProceso++;
  }

  system("cls");

  Datos terminado;

  auto it = listaLote.begin();  // Se inicializa el iterador apuntando al primer
                                // elemento de listaLote
  bool cont = true;
  int procesoDeLote = 4;
  int tiempo = 1;

  while (it != listaLote.end()) {
    // Se obtiene una referencia al elemento actual
    const Datos& lote = *it;

    mostrarLotes(listaLote, it, *it);
    cout << "----------------------------------" << endl;

    auto prev = it;

    // Si es la primera iteración, espera por 1 segundo, de lo contrario,
    // utiliza el contador del objeto anterior
    if (cont) {
      this_thread::sleep_for(chrono::seconds(tiempo));
      cont = false;
    } else {
      Datos& prevLote = *(--prev);
      tiempo = prevLote.GetTiempo();
      //this_thread::sleep_for(chrono::seconds(tiempo));
    }

    
    lote.toStringProceso(); // Imprime los procesos

    listaLoteTerminados.push_back(lote);

    // Muestra los procesos terminados en una posición fija en la consola pero
    // se borran despues
    for (const Datos& terminado : listaLoteTerminados) {
      terminado.toStringTerceraColumna();
    }

    this_thread::sleep_for(chrono::seconds(tiempo)); // Tiempo entre procesos al terminar de imprimir "terminados", (use el que tienen entre procesos)

    system("cls");
    it++;  // Se avanza al siguiente elemento para la próxima iteración
  }

  system("pause");
  return 0;
}
