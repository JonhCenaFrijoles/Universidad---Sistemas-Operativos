#include <conio.h>

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <list>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "datos.hpp"
#include "lote.hpp"

using namespace std;

// Definición de la función para verificar ID repetido
bool verificarIdRepetido(const vector<Datos>& listaProcesos, int id) {
  for (const Datos& proceso : listaProcesos) {
    if (proceso.GetID() == id) {
      /* cout << "Error: El ID " << id
           << " ya ha sido registrado. Ingresa un ID único." << endl; */
      return true;
    }
  }
  return false;  // ID único, no se ha encontrado repetido
}

// Definición de la función para verificar la división entre 0.
void verificarDivision(int numeroDos) {
  while (numeroDos <= 0) {
    cout << "Division invalida, no puedes dividir entre 0.\nRe-ingresa el "
            "valor: "
         << endl;
    cin >> numeroDos;
  }
}

// Definición de la función para aleatorizar los números con parámetros.
int generarEnterosAleatorios(int minimo, int maximo) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribucion(minimo, maximo);
    return distribucion(gen);
}

// Definición de la función para aleatorizar los números sin parámetros
int generarEnterosAleatorios() { return generarEnterosAleatorios(0, 100); }

int main() {
  int numeroLote = 1;  // variable para imprimir el numero de proceso en proceso
  Datos proceso;       // Objeto proceso
  Lote lote;           // Objeto proceso
  vector<Datos> listaProcesos;
  vector<Lote> listaLote;  // lista de lotes
  vector<Datos> listaLoteTerminados;

  cout << "Ingresa el numero de procesos" << endl;
  int numeroProcesoTotal;  // Numero de procesos total
  cin >> numeroProcesoTotal;

  int i = 0;            // Contador de procesos
  string resultado;     // Resultado del proceso
  int tiempoEstimado;   // Tiempo estimado del proceso
  int contadorProceso;  // Contador del proceso

  // Añadir proceso
  while (i < numeroProcesoTotal) {
    while (contadorProceso < 4 && i < numeroProcesoTotal) {
      system("cls");

      cout << "Proceso No.  " << i + 1 << endl << endl;

      lote.setLoteID(numeroLote);  // Asigna el número del lote (ID)

      int opcionOperacion, numeroUno, numeroDos;  // Declaración de variables

      proceso.SetId(i + 1);  // ingresa el id al objeto

      tiempoEstimado = generarEnterosAleatorios(1, 5);
      proceso.SetTiempo(
          tiempoEstimado);  // ingresa el tiempo estimado al objeto
      generarEnterosAleatorios(1, 5);
      opcionOperacion = generarEnterosAleatorios(1, 5);

      switch (opcionOperacion) {
        case 1:
          proceso.setOperador("'Multiplicación'");
          break;
        case 2:
          proceso.setOperador("'División'");
          break;
        case 3:
          proceso.setOperador("'Suma'");
          break;
        case 4:
          proceso.setOperador("'Resta'");
          break;
        case 5:
          proceso.setOperador("'Residuo'");
          break;
      }

      cout << "La operacion sera " << proceso.getOperador() << endl;
      cout << "Ingresa el primer operando: " << endl;
      cin >> numeroUno;
      cout << "Ingresa el segundo operando: " << endl;
      cin >> numeroDos;

      switch (opcionOperacion) {  // Asignar operación
        case 1: {
          proceso.setResultado(to_string(numeroUno) + "x" +
                               to_string(numeroDos) + "=" +
                               to_string(numeroUno * numeroDos));

          proceso.setOperadores(to_string(numeroUno), to_string(numeroDos),
                                " x ");
          break;
        }
        case 2: {
          // Verificación de la division entre 0.
          verificarDivision(numeroDos);
          proceso.setResultado(to_string(numeroUno) + "/" +
                               to_string(numeroDos) + "=" +
                               to_string(numeroUno / numeroDos));
          proceso.setOperadores(to_string(numeroUno), to_string(numeroDos),
                                " / ");
          break;
        }
        case 3: {
          proceso.setResultado(to_string(numeroUno) + "+" +
                               to_string(numeroDos) + "=" +
                               to_string(numeroUno + numeroDos));
          proceso.setOperadores(to_string(numeroUno), to_string(numeroDos),
                                " + ");
          break;
        }
        case 4: {
          proceso.setResultado(to_string(numeroUno) + "-" +
                               to_string(numeroDos) + "=" +
                               to_string(numeroUno - numeroDos));
          proceso.setOperadores(to_string(numeroUno), to_string(numeroDos),
                                " - ");
          break;
        }
        case 5: {
          // Verificación de la división entre 0.
          verificarDivision(numeroDos);
          proceso.setResultado(to_string(numeroUno) + "%" +
                               to_string(numeroDos) + "=" +
                               to_string(numeroUno % numeroDos));
          proceso.setOperadores(to_string(numeroUno), to_string(numeroDos),
                                " % ");
          break;
        }
      }

      proceso.setLoteID(numeroLote);
      listaProcesos.push_back(proceso);  // Lista de los procesos
      lote.agregarElemento(proceso);     // Agrega el proceso a su lotes
      i++;
      contadorProceso++;
    }

    numeroLote++;         // Aumenta el número del lote
    contadorProceso = 0;  // Reincia el contador de procesos asignados al lote
    listaLote.push_back(lote);  // Ingresa el lote
    lote.mostrarLote(lote);     // Muestra el lote completo antes de limpiarlo
    lote.vaciarLote();          // Vacia el lote para usar otro nuevo
  }

  // Limpia la terminal para pasar a procesar.
  system("cls");

  auto contador = listaLote.begin();  // Se inicializa el iterador apuntando al
                                      // primer elemento de listaLote
  bool bandera = true;

  int tiempo = 1;
  int tiempoTotal = 0;

  while (contador != listaLote.end()) {
    while (kbhit()) {
      getch();  // Leer y descartar el carácter del búfer de entrada (para que
                // no te salgan letras a lo pendejo
    }
    // Procesar los lotes mostrados
    int posicion = 0;

    while (bandera) {
      Lote& lote = *contador;  // Obtenemos el primer lote
      Datos variableSexy;
      // Obtenemos el primer proceso del lote
      Datos proceso = lote.obtenerElemento(posicion);

      lote.eliminarElemento(proceso);  // Eliminar el objeto del lote

      // Mostramos el lote
      cout << "Lotes Faltantes: " << listaLote.size() - 1
      << "\n\nLote Actual:  " << lote.getLoteID() << endl;
      lote.mostrarLote(lote);

      cout << "\n----------------------------------" << endl;

      // Imprimir y procesar el proceso actual
      int totalTime = proceso.GetTiempo();
      int tiempoRestante = proceso.GetTiempo();
      int tiempoSumado = 0;
      cout << "         Ejecucion        " << endl;
      cout << "ID: " << proceso.GetID() << endl;
      cout << "Operadores: " << proceso.getOperadores() << endl;

      bool pausado = false;

      // Bucle para la interrumpción y la terminación de procesos
      while (tiempoRestante > 0) {
        if (kbhit()) {
          char tecla = getch();  // Obtener la tecla presionada

          // Tecla para pausar el proceso actual
          if (tecla == 'q') {
            pausado = true;
            cout << "Proceso pausado. Presiona 'c' para reanudar." << endl;
          } else if (tecla == 'c') { // Tecla para reanudar el proceso actual
            pausado = false;
            cout << "Proceso reanudado." << endl;
          }
          if (tecla == 'e') {
            Datos objetoAux;  // Crear un nuevo objeto auxiliar para guardar los
                              // datos

            // Eliminar el proceso actual del lote
            objetoAux = proceso;  // se guardan los datos de este proceso en un
                                  // nuevo proceso
            objetoAux.SetId(proceso.GetID());
            lote.eliminarElemento(proceso);
            objetoAux.SetTiempo(totalTime-tiempoSumado);
            objetoAux.SetTiempoTranscurrido(totalTime-tiempoSumado);  // Actualizar su tiempo
            // Agregar el objeto auxiliar al lote
            lote.agregarElemento(objetoAux);
            // Mover al siguiente proceso
            system("cls");

            // Mostrar el lote actualizado
            lote.mostrarLote(lote);

            // Hacer un segundo de retraso antes de continuar con el siguiente
            // proceso
            this_thread::sleep_for(chrono::seconds(1));

            break;
          }
          // Tecla para interrupir el proceso actual y generar un error
          if (tecla == 'w') {
            // El resultado resulta ERROR
            proceso.setResultado("ERROR");
            // Pasamos el proceso a la lista de terminados y pasamos al otro siguiente
            listaLoteTerminados.push_back(proceso);

            this_thread::sleep_for(chrono::seconds(1));

            break;
          }
        }

        // Si no esta pausado, sigue el proceso como si nada
        if (!pausado) {
          // Imprimir información del proceso
          cout << "Tiempo restante: " << tiempoRestante << " segundos" << endl;
          cout << "Tiempo de proceso: " << tiempoSumado << " segundos" << endl;
          proceso.SetTiempoTranscurrido(tiempoSumado);
          cout << "Tiempo total: " << tiempoTotal << " segundos" << endl;
          // Pausa de un segundo para simular el tiempo
          this_thread::sleep_for(chrono::seconds(1));
          cout << "\033[3A\033[K";  // Retrocede dos líneas y las limpia
          tiempoRestante--;
          tiempoSumado++;
          tiempoTotal++;
          if (tiempoSumado == totalTime) {
            listaLoteTerminados.push_back(proceso);
          }
        }
      }

      cout << endl;
      cout << "         Terminados          " << endl;
      int contSeparacion = 1;

      // Mostrar los procesos terminados en una posición fija en la consola
      for (const Datos& proceso : listaLoteTerminados) {
        proceso.toStringTerminados(proceso.getLoteID());
        if (contSeparacion % 4 == 0) {
          cout << "\n----------------------------------" << endl;
        }
        contSeparacion++;
      }

      // Esperar el tiempo entre procesos
      this_thread::sleep_for(chrono::seconds(tiempo));

      system("cls");  // Limpiamos la terminal

      // Si el lote esta vacío, levantamos la bandera y salimos del bucle
      // interior
      if (lote.estaVacia()) {
        bandera = false;
      }
    }

    bandera = true;  // Reiniciamos la bandera
    contador++;      // Cambiamos de lote
  }
  this_thread::sleep_for(chrono::seconds(10));
  return 0;
}
