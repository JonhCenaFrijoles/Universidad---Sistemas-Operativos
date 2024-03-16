#include <conio.h>

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "datos.hpp"
#include "lote.hpp"

using namespace std;

// funcion para recorrer el proceso de los bloqueados
void recorrerListaBloq(vector<Datos>& listaBloq, Lote& lote) {
  for (auto it = listaBloq.begin(); it != listaBloq.end(); ++it) {
    Datos& proceso = *it;  // esto para la pocision y despues poder elminar
    int tiempoActualizado =
        proceso.getTiempoBloq();  // se obtiene el proceso de bloqueados que se
                                  // inicializa en 0
    tiempoActualizado++;          // se suma en cada iteracion
    proceso.setTiempoBloq(tiempoActualizado);  // se actualiza en cada iteracion
                                               // el proceso de bloqueado
    cout << proceso.GetID() << " : " << proceso.getTiempoBloq() << "     ";
    if (proceso.getTiempoBloq() == 8) {
      lote.agregarElemento(proceso);  // se agrega de nuevo
      lote.eliminarElementoBloq(
          proceso);  // aqui tambien se elimina de la lista de los objetos
      it = listaBloq.erase(
          it);  // Eliminar el proceso del vector y actualizar el iterador
      // if (it == listaBloq.end()) break; // Verificar si se alcanzó el final
      // del vector
      break;
    }
  }
}

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
  while (numeroDos == 0) {
    cout << "Division invalida, no puedes dividir entre 0.\nRe-ingresa el "
            "valor: "
         << endl;
    cin >> numeroDos;
  }
}

// Definición de la función para aleatorizar los números con parámetros.
int generarEnterosAleatorios(int minimo, int maximo) {
  static random_device rd;
  static mt19937 gen(rd());
  uniform_int_distribution<> distribucion(minimo, maximo);
  return distribucion(gen);
}

// Definición de la función para aleatorizar los números sin parámetros
int generarEnterosAleatorios() { return generarEnterosAleatorios(0, 100); }

int validarEntero() {
  int numero;
  while (true) {
    if (cin >> numero) {
      break;
    } else {
      cout << "Entrada invalida. Por favor, ingresa un número entero." << endl;
      cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n');  // Ignorar el resto de la entrada
    }
  }
  return numero;
}

void imprimirTiempos(Datos proceso) {
  cout << "Proceso " << proceso.GetID()
       << "||   Tiempo de Llegada: " << proceso.getTiempoLlegada()
       << "||   Tiempo de Finalizacion: " << proceso.getTiempoFinalizacion()
       << "||   Tiempo de Retorno: " << proceso.getTiempoRetorno()
       << "||   Tiempo de Respuesta: " << proceso.getTiempoRespuesta()
       << "||   Tiempo de Espera: " << proceso.getTiempoEspera()
       << "||   Tiempo de Servicio: " << proceso.GetTiempo() << "\n";
}

int main() {
  int numeroLote = 1;  // variable para imprimir el numero de proceso en proceso
  Datos proceso;       // Objeto proceso
  Lote lote;           // Objeto proceso
  vector<Datos> listaProcesos;
  vector<Lote> listaLote;  // lista de lotes
  vector<Datos> listaLoteTerminados;
  vector<Datos> listaBloq;

  cout << "Ingresa el numero de procesos" << endl;
  int numeroProcesoTotal = validarEntero();  // Numero de procesos total

  int i = 0;            // Contador de procesos
  string resultado;     // Resultado del proceso
  int tiempoEstimado;   // Tiempo estimado del proceso
  int contadorProceso;  // Contador del proceso

  // Añadir proceso
  while (i < numeroProcesoTotal) {
    system("cls");

    cout << "Proceso No.  " << i + 1 << endl << endl;

    lote.setLoteID(numeroLote);  // Asigna el número del lote (ID)

    int opcionOperacion, numeroUno, numeroDos;  // Declaración de variables

    proceso.SetId(i + 1);  // ingresa el id al objeto

    tiempoEstimado = generarEnterosAleatorios(3, 5);

    // ingresa el tiempo estimado al objeto
    proceso.SetTiempo(tiempoEstimado);
    proceso.SetTiempoEstimado(tiempoEstimado);

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

    numeroUno = generarEnterosAleatorios(1, 100);
    numeroDos = generarEnterosAleatorios(1, 100);

    switch (opcionOperacion) {  // Asignar operación
      case 1: {
        proceso.setResultado(to_string(numeroUno) + "x" + to_string(numeroDos) +
                             "=" + to_string(numeroUno * numeroDos));

        proceso.setOperadores(to_string(numeroUno), to_string(numeroDos),
                              " x ");
        break;
      }
      case 2: {
        // Verificación de la division entre 0.
        verificarDivision(numeroDos);
        proceso.setResultado(to_string(numeroUno) + "/" + to_string(numeroDos) +
                             "=" + to_string(numeroUno / numeroDos));
        proceso.setOperadores(to_string(numeroUno), to_string(numeroDos),
                              " / ");
        break;
      }
      case 3: {
        proceso.setResultado(to_string(numeroUno) + "+" + to_string(numeroDos) +
                             "=" + to_string(numeroUno + numeroDos));
        proceso.setOperadores(to_string(numeroUno), to_string(numeroDos),
                              " + ");
        break;
      }
      case 4: {
        proceso.setResultado(to_string(numeroUno) + "-" + to_string(numeroDos) +
                             "=" + to_string(numeroUno - numeroDos));
        proceso.setOperadores(to_string(numeroUno), to_string(numeroDos),
                              " - ");
        break;
      }
      case 5: {
        // Verificación de la división entre 0.
        verificarDivision(numeroDos);
        proceso.setResultado(to_string(numeroUno) + "%" + to_string(numeroDos) +
                             "=" + to_string(numeroUno % numeroDos));
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

    if (contadorProceso == 4) {
      numeroLote++;               // Aumenta el número del lote
      listaLote.push_back(lote);  // Ingresa el lote
      lote.mostrarLote(lote);     // Muestra el lote completo antes de limpiarlo
      lote.vaciarLote();          // Vacia el lote para usar otro nuevo
    }
  }

  listaLote.push_back(lote);  // Ingresa el lote
  lote.mostrarLote(lote);     // Muestra el lote completo antes de limpiarlo
  lote.vaciarLote();          // Vacia el lote para usar otro nuevo

  // Limpia la terminal para pasar a procesar.
  system("cls");

  auto contador = listaLote.begin();  // Se inicializa el iterador apuntando al
                                      // primer elemento de listaLote

  int tiempo = 1;
  int tiempoTotal = 0;

  while (contador != listaLote.end()) {
    while (kbhit()) {
      getch();  // Leer y descartar el carácter del búfer de entrada (para que
                // no te salgan letras a lo pendejo
    }
    // Procesar los lotes mostrados
    int posicion = 0;

    Lote& lote = *contador;  // Obtenemos el primer lote
    // Obtenemos el primer proceso del lote
    Datos proceso = lote.obtenerElemento(posicion);

    // Calcula el tiempo de llegada y establece el tiempo de llegada del proceso
    proceso.setTiempoLlegada(tiempoTotal);
    // Calcula el tiempo de respuesta como la diferencia entre el tiempo actual
    // y el tiempo de llegada
    //proceso.setTiempoRespuesta(tiempoTotal,proceso.getTiempoLlegada());

    lote.eliminarElemento(proceso);  // Eliminar el objeto del lote

    // Mostramos el lote
    cout << "Procesos Faltantes: " << listaProcesos.size() << endl;
    lote.mostrarLote(lote);

    cout << "\n----------------------------------" << endl;
    cout << "         Bloqueados         " << endl;
    // lote.mostrarBloqueados(lote);
    lote.mostrarBloqueados(lote);

    cout << "\n----------------------------------" << endl;

    // Imprimir y procesar el proceso actual

    // Obtenemos el tiempo total estimado
    int totalTime = proceso.GetTiempo();
    // Obtenemos el tiempo restante
    int tiempobloq = 8;
    int tiempoRestante = proceso.GetTiempo();
    int tiempoSumado = 0;
    int tiempoTranscurrido = proceso.GetTiempoTranscurrido();
    cout << "         Ejecucion        " << endl;
    cout << "ID: " << proceso.GetID() << endl;
    cout << "Operadores: " << proceso.getOperadores() << endl;

    bool pausado = false;

    /* // Agregar tiempo de llegada **
    proceso.setTiempoLlegada(tiempoTotal); */

    // Bucle para la interrumpción y la terminación de procesos
    while (tiempoRestante > 0) {
      if (kbhit()) {
        char tecla = getch();  // Obtener la tecla presionada

        // Tecla para pausar el proceso actual
        if (tecla == 'p') {
          pausado = true;
          cout << "Proceso pausado. Presiona 'c' para reanudar." << endl;
        } else if (tecla == 'c') {  // Tecla para reanudar el proceso actual
          pausado = false;
          cout << "\033[2A\033[K";
          cout << "Proceso reanudado." << endl;
        }
        if (tecla == 'e') {
          Datos objetoAux;  // Crear un nuevo objeto auxiliar para guardar los
                            // datos
          objetoAux = proceso;  // se guardan los datos de este proceso en un
                                // nuevo proceso
          objetoAux.SetId(proceso.GetID());
          lote.eliminarElemento(proceso);
          objetoAux.SetTiempo(totalTime - tiempoSumado);
          objetoAux.SetTiempoTranscurrido(
              tiempoTranscurrido);  // Actualizar su tiempo
          objetoAux.setTiempoBloq(0);
          // Agregar el objeto auxiliar al loteo
          // Agregar el objeto auxiliar al lote

          listaBloq.push_back(objetoAux);
          lote.agregarElementoBloq(objetoAux);
          // Mover al siguiente proceso
          system("cls");

          // Mostrar el lote actualizado
          cout << "memoria actual" << endl;
          // lote.mostrarLote(lote);
          cout << "Bloqueados" << endl;
          lote.mostrarBloqueados(lote);

          // Hacer un segundo de retraso antes de continuar con el siguiente
          // proceso
          this_thread::sleep_for(chrono::seconds(1));

          break;
        }
        // Tecla para interrupir el proceso actual y generar un error
        if (tecla == 'w') {
          // El resultado resulta ERROR
          proceso.setResultado("ERROR");
          // Pasamos el proceso a la lista de terminados y pasamos al otro
          // siguiente
          listaLoteTerminados.push_back(proceso);

          this_thread::sleep_for(chrono::seconds(1));

          break;
        }
      }

      // Si no esta pausado, sigue el proceso como si nada
      if (!pausado) {
        // recorrer el proceso de los bloqueados
        recorrerListaBloq(listaBloq, lote);
        // Imprimir información del proceso
        cout << "Tiempo restante: " << tiempoRestante << " segundos" << endl;
        cout << "Tiempo ejecutado: " << tiempoTranscurrido << " segundos"
             << endl;
        proceso.SetTiempoTranscurrido(tiempoTranscurrido);
        cout << "Tiempo total: " << tiempoTotal << " segundos" << endl;
        // Pausa de un segundo para simular el tiempo
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\033[3A\033[K";  // Retrocede dos líneas y las limpia
        tiempoRestante--;
        tiempoSumado++;
        tiempoTotal++;
        tiempoTranscurrido++;
        tiempobloq--;

        if (tiempoSumado == totalTime) {
          // Agregamos tiempo de finalización **
          proceso.setTiempoFinalizacion(tiempoTotal);
          proceso.calcularTiempos();
          // Aumentamos el contador para apuntar al siguiente lote
          contador++;
          Lote& loteSiguiente = *contador;
          if (!loteSiguiente.estaVacia()) {
            // Obtenemos el primer proceso del siguiente lote
            proceso = loteSiguiente.obtenerElemento(0);
            // Eliminamos el proceso del siguiente lote
            loteSiguiente.eliminarElemento(proceso);
            // Agregamos el elemento al lote actual.
            lote.agregarElemento(proceso);
          }

          listaLoteTerminados.push_back(proceso);
          contador--;
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

    // Si el lote esta vacío, salimos del bucle while
    if (lote.estaVacia()) {
      break;
    }
  }

  // Imprimir la tabla de tiempos **

  for (size_t i = 0; i < listaLoteTerminados.size(); i++) {
    imprimirTiempos(listaLoteTerminados[i]);
  }

  system("pause");
  return 0;
}
