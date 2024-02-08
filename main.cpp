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


/*void mostrarLotes(const vector<Datos>& listaLote, vector<Datos>::const_iterator it, const Datos& objAux) {
  while (it != listaLote.end()) {
    const Datos& loteActual = *it;
    loteActual.toStringMostarlote();
    ++it;
  }
}*/
/*void mostrarLotes(const vector<Datos>& listaLote, int inicio, int fin) {
    for (int i = inicio; i < fin; ++i) {
        const Datos& loteActual = listaLote[i];
        loteActual.toStringMostarlote();
    }
}*/

/*void mostrarLotes(const vector<Datos>& listaLote, vector<Datos>::const_iterator inicio, int fin) {
    while (inicio != listaLote.end() && fin > 0) {
        const Datos& loteActual = *inicio;
        loteActual.toStringMostarlote();
        inicio++;
        fin--;
    }
}*/
void mostrarLotes(const vector<Datos>& listaLote, vector<Datos>::const_iterator inicio, int fin) {
    int contadorLotes = 0; // Contador de lotes mostrados
    while (inicio != listaLote.end() && fin > 0 && contadorLotes < fin) {
        const Datos& loteActual = *inicio;
        loteActual.toStringMostarlote();
        inicio++;
        contadorLotes++;
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
  int pos=0;
  int loteActual=1;
  int inicio = 0;

int procesosProcesados = 0;
int primerLoteAMostrar = 0; // Índice del primer lote a mostrar en cada iteración

while (it != listaLote.end()) {
    cout << "Mostrando procesos del " << primerLoteAMostrar + 1 << " al " << min(primerLoteAMostrar + procesoDeLote, static_cast<int>(listaLote.size())) << endl;
    mostrarLotes(listaLote, listaLote.begin() + primerLoteAMostrar, min(4, static_cast<int>(listaLote.size())));
    cout << "----------------------------------" << endl;

    // Procesar los lotes mostrados
    for (int i = 0; i < procesoDeLote && it != listaLote.end(); ++i) {
        const Datos& lote = *it;

        // Imprimir y procesar el lote actual
        lote.toStringProceso();
        listaLoteTerminados.push_back(lote);

        // Mostrar los procesos terminados en una posición fija en la consola
        for (const Datos& terminado : listaLoteTerminados) {
            terminado.toStringTerceraColumna();
        }

        this_thread::sleep_for(chrono::seconds(tiempo)); // Esperar el tiempo entre procesos

        it++; // Avanzar al siguiente elemento
    }

    primerLoteAMostrar += procesoDeLote; // Actualizar el índice del primer lote a mostrar en la próxima iteración
    system("cls");
}



  /*while (inicio < listaLote.size()) {
    cout << "Mostrando procesos del " << primerLoteAMostrar + 1 << " al " << min(primerLoteAMostrar + procesoDeLote, static_cast<int>(listaLote.size())) << endl;
    mostrarLotes(listaLote, listaLote.begin() + primerLoteAMostrar, min(primerLoteAMostrar + procesoDeLote, static_cast<int>(listaLote.size())));
    cout << "----------------------------------" << endl;

    int procesosProcesados = 0; // Inicializar el contador de procesos procesados
    while (it != listaLote.end()) {

        const Datos& lote = *it;
        // Si se han procesado menos de 4 procesos, continuar procesando
        if (procesosProcesados < 4) {
            // Imprimir y procesar el lote actual
            lote.toStringProceso();
            listaLoteTerminados.push_back(lote);
            procesosProcesados++;
        } else {
            // Si ya se procesaron 4 procesos, detener la iteración actual
            break;
        }

        // Mostrar los procesos terminados en una posición fija en la consola
        for (const Datos& terminado : listaLoteTerminados) {
            terminado.toStringTerceraColumna();
        }

        this_thread::sleep_for(chrono::seconds(tiempo)); // Esperar el tiempo entre procesos

        it++; // Avanzar al siguiente elemento
        //system("cls");
    }
      this_thread::sleep_for(chrono::seconds(tiempo)); // Tiempo entre procesos

    system("cls");

    inicio += procesoDeLote;
  }*/
/*int procesosProcesados = 0; // Inicializar el contador de procesos procesados
while (it != listaLote.end()) {
    cout << "Mostrando procesos del " << inicio + 1 << " al " << min(inicio + procesoDeLote, static_cast<int>(listaLote.size())) << endl;
    // Mostrar los lotes para esta iteración
    mostrarLotes(listaLote, listaLote.begin() + inicio, min(inicio + procesoDeLote, static_cast<int>(listaLote.size())));
    cout << "----------------------------------" << endl;
    // Procesar los lotes para esta iteración
    for (int i = 0; i < procesoDeLote && it != listaLote.end(); ++i) {
        // Se obtiene una referencia al elemento actual
        const Datos& lote = *it;

        // Si se han procesado menos de 4 procesos, continuar procesando
        if (procesosProcesados < 4) {
            // Imprimir y procesar el lote actual
            lote.toStringProceso();
            listaLoteTerminados.push_back(lote);
            procesosProcesados++;
        } else {
            // Si ya se procesaron 4 procesos, detener la iteración actual
            break;
        }

        it++; // Avanzar al siguiente elemento
    }

    // Mostrar los procesos terminados en una posición fija en la consola
    for (const Datos& terminado : listaLoteTerminados) {
        terminado.toStringTerceraColumna();
    }

    this_thread::sleep_for(chrono::seconds(tiempo)); // Esperar el tiempo entre procesos

    system("cls");
    inicio += procesoDeLote; // Actualizar el inicio para la próxima iteración
    procesosProcesados = 0; // Reiniciar el contador de procesos procesados
}*/
  return 0;
}
