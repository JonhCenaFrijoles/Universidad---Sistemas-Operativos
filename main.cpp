#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <conio.h>
#include "datos.hpp"
#include "lote.hpp"

using namespace std;

// Definición de la función para verificar ID repetido
bool verificarIdRepetido(const vector<Datos>& listaProcesos, int id) {
  for (const Datos& proceso : listaProcesos) {
    if (proceso.GetID() == id) {
      cout << "Error: El ID " << id
           << " ya ha sido registrado. Ingresa un ID único." << endl;
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
  string nombre;        // Nombre del proceso
  int id;               // ID del proceso
  string resultado;     // Resultado del proceso
  int tiempoEstimado;   // Tiempo estimado del proceso
  int contadorProceso;  // Contador del proceso+

  // Añadir proceso
  while (i < numeroProcesoTotal) {
    while (contadorProceso < 4 && i < numeroProcesoTotal) {
      system("cls");

      cout << "Proceso No.  " << i + 1 << endl << endl;

      lote.setLoteID(numeroLote);  // Asigna el número del lote (ID)

      int opcionOperacion, numeroUno, numeroDos;  // Declaración de variables

      cin.ignore();
      cout << "Inserta tu nombre: " << endl;
      getline(cin, nombre);
      proceso.SetNombre(nombre);
      do {
        cout << "Ingresa tu ID: " << endl;
        cin >> id;
      } while (verificarIdRepetido(listaProcesos,
                                   id));  // verifica el id con la funcion

      proceso.SetId(id);  // ingresa el id al objeto

      cout << "Ingresa el tiempo estimado: " << endl;
      cin >> tiempoEstimado;
      proceso.SetTiempo(
          tiempoEstimado);  // ingresa el tiempo estimado al objeto

      cout << " ------ Selecciona la operación ------ " << endl;
      cout << "1.- Multiplicacion " << endl;
      cout << "2.- Division " << endl;
      cout << "3.- Suma " << endl;
      cout << "4.- restar " << endl;
      cout << "5.- residuo " << endl;
      cin >> opcionOperacion;

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
        } break;
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
            getch(); // Leer y descartar el carácter del búfer de entrada (para que no te salgan letras a lo pendejo
    }
    // Procesar los lotes mostrados
    int posicion = 0;
    while (bandera) {
      Lote& lote = *contador;  // Obtenemos el primer lote
      Datos variableSexy;
      // Obtenemos el primer proceso del lote
      Datos proceso = lote.obtenerElemento(posicion);


      lote.eliminarElemento(proceso);  // Eliminar el objeto del lote

      lote.mostrarLote(lote);  // Mostramos el lote

      cout << "----------------------------------" << endl;

      // Imprimir y procesar el proceso actual
         // Imprimir y procesar el proceso actual
            int totalTime = proceso.GetTiempo();
            int tiempoRestante = proceso.GetTiempo();
            int tiempoSumado = 0;
            cout << "         Ejecucion        " << endl;
            cout << "Nombre: " << proceso.GetNombre() << endl;
            cout << "ID: " << proceso.GetID() << endl;
            cout << "Operadores: " << proceso.getOperadores() << endl;
            while (tiempoRestante > 0) {
                 if (kbhit()) {
                    char tecla = getch(); // Obtener la tecla presionada
                    cout << "Tecla presionada: " << tecla << endl;

                    if (tecla == 'q') {
                        break; // Salir del bucle si se presiona 'q'
                        }
                    if (tecla == 'e') {
                        Datos objetoAux; // Crear un nuevo objeto auxiliar para guardar los datos

                        // Eliminar el proceso actual del lote
                        objetoAux=proceso;// se guardan los datos de este proceso en un nuevo proceso
                        objetoAux.SetId(proceso.GetID());
                        lote.eliminarElemento(proceso);
                        objetoAux.SetTiempo(totalTime - tiempoRestante); // Actualizar su tiempo
                        // Agregar el objeto auxiliar al lote
                        lote.agregarElemento(objetoAux);
                        // Mover al siguiente proceso
                        system("cls");

                        // Mostrar el lote actualizado
                        lote.mostrarLote(lote);
                        cout << "terminados" << endl;
                        for (const Datos& proceso : listaLoteTerminados) {
                            proceso.toStringTerminados(proceso.getLoteID());
                        }
                        system("pause");

                        // Continuar con el siguiente proceso
                        break;
                    }

                }

                // Imprimir información del proceso
                cout << "Tiempo restante: " << tiempoRestante << " segundos" << endl;
                cout << "Tiempo de proceso: " << tiempoSumado << " segundos" << endl;
                cout << "Tiempo total: " << tiempoTotal << " segundos" << endl;
                // Pausa de un segundo para simular el tiempo
                this_thread::sleep_for(chrono::seconds(1));
                cout << "\033[3A\033[K";  // Retrocede dos líneas y las limpia
                tiempoRestante--;
                tiempoSumado++;
                tiempoTotal++;
                if(tiempoSumado == totalTime){
                    listaLoteTerminados.push_back(proceso);

                }

            }
            cout << endl;
      //tiempoTotal = proceso.toStringProceso(tiempoTotal);



      cout << "         Terminados          " << endl;
      int contSeparacion =1;

      // Mostrar los procesos terminados en una posición fija en la consola
      for (const Datos& proceso : listaLoteTerminados) {
        proceso.toStringTerminados(proceso.getLoteID());
        if(contSeparacion % 4==0){
            cout<<"////////////////////////////////////////////"<<endl;
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

  system("pause");
  return 0;
}
