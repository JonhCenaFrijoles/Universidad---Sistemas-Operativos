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

void mostrarLotes(const vector<Datos>& listaLote,
                  vector<Datos>::const_iterator inicio, int fin) {

  int contadorLotes = 0;  // Contador de lotes mostrados
  
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
  vector<Datos> ListaDeProcesosParaMostrar;

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
        // Verificación de la division entre 0.
        while (numeroDos == 0){
          cout << "Division invalida, no puedes dividir entre 0.\nRe-ingresa el valor: " << endl;
          cin >> numeroDos;
        }
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
  int tiempoTotal = 0;

  int loteActual = 1;
  int inicio = 0;

  int procesosProcesados = 0;
  int primerLoteAMostrar =
      0;  // Índice del primer lote a mostrar en cada iteración

  while (it != listaLote.end()) {
    // Procesar los lotes mostrados

    for (int i = 0; i < procesoDeLote && it != listaLote.end(); ++i) {
      /* cout << "Mostrando procesos del " << primerLoteAMostrar + 1 << " al "
            << min(primerLoteAMostrar + procesoDeLote, static_cast<int>(listaLote.size())) << endl; */



      mostrarLotes(listaLote, listaLote.begin() + primerLoteAMostrar, min(4, static_cast<int>(listaLote.size())));

      cout << "----------------------------------" << endl;

      const Datos& lote = *it;

      // Imprimir y procesar el lote actual
      tiempoTotal = lote.toStringProceso(tiempoTotal);

      listaLoteTerminados.push_back(lote);

      cout << "         Terminados          " << endl;

      // Mostrar los procesos terminados en una posición fija en la consola
      for (const Datos& terminado : listaLoteTerminados) {
        terminado.toStringTerceraColumna();
      }

      this_thread::sleep_for(chrono::seconds(tiempo));  // Esperar el tiempo entre procesos

      it++;  // Avanzar al siguiente elemento
      //it = listaLote.erase(it); // Borra el dato
      system("cls");

    }

    primerLoteAMostrar =+ procesoDeLote;  // Actualizar el índice del primer lote a mostrar en la
                        // próxima iteración
    system("cls");
  }

  system("pause");
  return 0;
}

// Intento de usar la lista para procesar ******

/* Datos terminado;

  auto it = listaLote.begin();  // Se inicializa el iterador apuntando al primer
                                // elemento de listaLote
  int cont = 1;
  int procesoDeLote = 4;
  int tiempo = 1;
  int tiempoTotal = 0;

  int loteActual = 1;
  int inicio = 0;

  int procesosProcesados = 0;
  int primerLoteAMostrar =
      0;  // Índice del primer lote a mostrar en cada iteración

  while (it != listaLote.end()) {
    // Procesar los lotes mostrados
    cout << "entro aqui: " << endl;
    const Datos& lote = *it;
    listaDeProcesosParaMostrar.push_back(lote);
    listaLote.erase(it);
    // Si el contador es igual a 4 ó la lista se queda sin objetos, entran a procesarse
    if (cont == 4 || listaLote.empty()) {
      for (int i = 0; i < procesoDeLote && it != listaDeProcesosParaMostrar.end(); ++i) {
        mostrarLotes(listaDeProcesosParaMostrar, listaDeProcesosParaMostrar.begin() + primerLoteAMostrar,
                     min(4, static_cast<int>(listaDeProcesosParaMostrar.size())));

        cout << "----------------------------------" << endl;

        // Imprimir y procesar el lote actual
        tiempoTotal = lote.toStringProceso(tiempoTotal);

        listaLoteTerminados.push_back(lote);

        cout << "         Terminados          " << endl;

        // Mostrar los procesos terminados en una posición fija en la consola
        for (const Datos& terminado : listaLoteTerminados) {
          terminado.toStringTerceraColumna();
        }

        this_thread::sleep_for(
            chrono::seconds(tiempo));  // Esperar el tiempo entre procesos

        //it++;  // Avanzar al siguiente elemento
        it = listaDeProcesosParaMostrar.erase(it); // Borra el dato
        system("cls");
      }
      cont = 1;
      primerLoteAMostrar =
        +procesoDeLote;  // Actualizar el índice del primer lote a mostrar en la
                         // próxima iteración
    }
    cont++;

    
    system("cls");
  } */