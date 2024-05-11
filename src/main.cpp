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
#include "marco.hpp"

using namespace std;

// funcion para recorrer el proceso de los bloqueados
void recorrerListaBloq(vector<Datos>& listaBloq, Lote& lote) {
  for (auto it = listaBloq.begin(); it != listaBloq.end(); ++it) {
    Datos& proceso = *it;  // esto para la pocision y despues poder elminar
    int tiempoActualizado =
        proceso.getTiempoBloq();  // se obtiene el proceso de bloqueados que se
                                  // inicializa en 0

    tiempoActualizado++;                       // se suma en cada iteracion
    proceso.setTiempoBloq(tiempoActualizado);  // se actualiza en cada iteracion
                                               // el proceso de bloqueado
    cout << proceso.GetID() << " : " << proceso.getTiempoBloq() << "     ";
    if (proceso.getTiempoBloq() == 8) {
      lote.agregarElemento(proceso);  // se agrega de nuevo
      lote.eliminarElementoBloq(
          proceso);  // aqui tambien se elimina de la lista de los objetos
      it = listaBloq.erase(
          it);  // Eliminar el proceso del vector y actualizar el iterador
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
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distribucion(minimo, maximo);
  return distribucion(gen);
}

int generarEnterosAleatoriosStatic(int minimo, int maximo) {
  static random_device rd;
  static mt19937 gen(rd());
  static uniform_int_distribution<> distribucion(minimo, maximo);
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
  cout << "Proceso No. " << proceso.GetID()
       << " ||Tiempo de Llegada: " << proceso.getTiempoLlegada()
       << " ||Tiempo de Servicio: " << proceso.GetTiempoEstimado()
       << " ||Tiempo de Espera: " << proceso.getTiempoEspera()
       << " ||Tiempo de Retorno: " << proceso.getTiempoRetorno()
       << " ||Tiempo de Finalizacion: " << proceso.getTiempoFinalizacion()
       << " ||Tiempo de Respuesta: " << proceso.getTiempoRespuesta()
       << " ||Resultado: " << proceso.getResultado() << "\n";
}

void imprimirTablaPaginacion(Marco marco, vector<Marco> listaMarcos) {
  for (Marco i : listaMarcos) {
    cout << i.getIdMarco() << "\t" << i.getTamanio() << "\t" << i.getIdProceso()
         << endl;
  }
}

int contarMarcosVacios(vector<Marco>& listaMarco) {
  int cont = 0;
  for (int i = 0; i < listaMarco.size(); i++) {
    if (listaMarco[i].getIdProceso() == "Libre") {
      cont++;
    }
  }
  return cont;
}

bool comprobarCabida(Datos proceso, vector<Datos>& listaProcesos,
                     vector<Datos>& listaListos, vector<Marco>& listaMarcos) {
  if (proceso.getPaginas() <= contarMarcosVacios(listaMarcos)) {
    return true;
  } else {
    return false;
  }
}

void meterProcesos(Datos proceso, vector<Datos>& listaProcesos,
                   vector<Datos>& listaListos, vector<Marco>& listaMarcos,
                   int residuo) {
  int contadorMarcoOcupado = 0;
  int contadorDePaginas = 0;

  for (int i = 0; i < listaMarcos.size(); i++) {
    if (listaMarcos[i].getIdProceso() == "Libre" && contadorMarcoOcupado < proceso.getPaginas()) {

      listaMarcos[i].setIdProceso(to_string(proceso.GetID()));

      // Si el proceso que sigue, es diferente al actual, y el actual tiene
      // residuo, colocar el residuo:
      if (residuo != 0 && contadorDePaginas == proceso.getPaginas() - 1) {
        listaMarcos[i].setTamanio(to_string(residuo) + "/5");
      } else {
        listaMarcos[i].setTamanio("5/5");
        contadorDePaginas++;
      }

      contadorMarcoOcupado++;
    }
  }
}

void eliminarProceso(vector<Marco>& listaMarcos, vector<Datos>& listaListos, vector<Datos>& listaProcesos, Lote& lote, Datos& proceso, int tiempoLlegada) {
  
  for (int i = 0; i < listaMarcos.size(); i++) {
    if (listaMarcos[i].getIdProceso() == to_string(proceso.GetID())) {
      listaMarcos[i].setIdProceso("Libre");
      listaMarcos[i].setTamanio("0/5");
    }
  }

  for (auto it = listaListos.begin(); it != listaListos.end();) {
 
    Datos& i = *it;
    // Verificar si el elemento actual ya está en listaProcesos
    if (find(listaProcesos.begin(), listaProcesos.end(), i) == listaProcesos.end()) {
      // El elemento no está en listaProcesos, agregarlo
      if (comprobarCabida(i, listaProcesos, listaListos, listaMarcos)) {
        i.setTiempoLlegada(tiempoLlegada);
        i.setTiempoLlegadaVerificar(true);
        listaProcesos.push_back(i);
        lote.agregarElemento(i);
        meterProcesos(i, listaProcesos, listaListos, listaMarcos,
                      i.getResiduo());
        listaListos.erase(it);
      } else {
        break;
      }
    }
  }
}

Datos crearProceso(Lote& lote, int& numeroLote, int& i, float quantum) {
  // Declaración de variables
  Datos proceso;
  int tamanio;
  int tiempoEstimado, opcionOperacion, numeroUno, numeroDos, numeroDosDivision;

  // Asigna el número del lote (ID)
  lote.setLoteID(numeroLote);

  // ingresa el id al objeto
  proceso.SetId(i + 1);

  tiempoEstimado = generarEnterosAleatorios(5, 18);

  // ingresa el tiempo estimado al objeto
  proceso.SetTiempo(tiempoEstimado);
  proceso.SetTiempoEstimado(tiempoEstimado);

  opcionOperacion = generarEnterosAleatorios(1, 5);

  numeroUno = generarEnterosAleatorios();
  numeroDos = generarEnterosAleatorios();
  numeroDosDivision = generarEnterosAleatorios(1, 100);
  tamanio = generarEnterosAleatoriosStatic(6, 26);

  switch (opcionOperacion) {  // Asignar operación
    case 1: {
      proceso.setResultado(to_string(numeroUno) + "x" + to_string(numeroDos) +
                           "=" + to_string(numeroUno * numeroDos));

      proceso.setOperadores(to_string(numeroUno) + " x " +
                            to_string(numeroDos));
      break;
    }
    case 2: {
      // Verificación de la division entre 0.
      verificarDivision(numeroDosDivision);
      proceso.setResultado(to_string(numeroUno) + "/" +
                           to_string(numeroDosDivision) + "=" +
                           to_string(numeroUno / numeroDosDivision));
      proceso.setOperadores(to_string(numeroUno) + " / " +
                            to_string(numeroDosDivision));
      break;
    }
    case 3: {
      proceso.setResultado(to_string(numeroUno) + "+" + to_string(numeroDos) +
                           "=" + to_string(numeroUno + numeroDos));
      proceso.setOperadores(to_string(numeroUno) + " + " +
                            to_string(numeroDos));
      break;
    }
    case 4: {
      proceso.setResultado(to_string(numeroUno) + "-" + to_string(numeroDos) +
                           "=" + to_string(numeroUno - numeroDos));
      proceso.setOperadores(to_string(numeroUno) + " - " +
                            to_string(numeroDos));
      break;
    }
    case 5: {
      // Verificación de la división entre 0.
      verificarDivision(numeroDosDivision);
      proceso.setResultado(to_string(numeroUno) + "%" +
                           to_string(numeroDosDivision) + "=" +
                           to_string(numeroUno % numeroDosDivision));
      proceso.setOperadores(to_string(numeroUno) + " % " +
                            to_string(numeroDosDivision));
      break;
    }
  }

  int paginasPorProceso;

  proceso.setTiempoRespuestaVerificar(true);
  proceso.setVerificarBloqueado(false);
  proceso.setLoteID(numeroLote);
  proceso.setTiempoLlegadaVerificar(true);
  proceso.setQuantum(quantum);
  proceso.setTamanio(tamanio);

  // Calculamos el número total de paginas que ocupara el proceso
  int tamanios = proceso.getTamanio();
  paginasPorProceso = tamanios / 5;
  int residuoTamanio = tamanios % 5;
  if (residuoTamanio > 0) {
    paginasPorProceso++;
  }

  proceso.setResiduo(residuoTamanio);
  proceso.setPaginas(paginasPorProceso);

  i++;

  return proceso;
}

Datos crearProceso(Lote& lote, int& numeroLote, int& i, int& tiempoTotal,
                   float quantum) {
  // Declaración de variables
  Datos proceso;
  int tamanio;
  int tiempoEstimado, opcionOperacion, numeroUno, numeroDos, numeroDosDivision;

  // Asigna el número del lote (ID)
  lote.setLoteID(numeroLote);

  // ingresa el id al objeto
  proceso.SetId(i + 1);

  tiempoEstimado = generarEnterosAleatorios(5, 18);

  // ingresa el tiempo estimado al objeto
  proceso.SetTiempo(tiempoEstimado);
  proceso.SetTiempoEstimado(tiempoEstimado);

  opcionOperacion = generarEnterosAleatorios(1, 5);

  numeroUno = generarEnterosAleatorios();
  numeroDos = generarEnterosAleatorios();
  numeroDosDivision = generarEnterosAleatorios(1, 100);
  tamanio = generarEnterosAleatoriosStatic(6, 26);

  switch (opcionOperacion) {  // Asignar operación
    case 1: {
      proceso.setResultado(to_string(numeroUno) + "x" + to_string(numeroDos) +
                           "=" + to_string(numeroUno * numeroDos));

      proceso.setOperadores(to_string(numeroUno) + " x " +
                            to_string(numeroDos));
      break;
    }
    case 2: {
      // Verificación de la division entre 0.
      verificarDivision(numeroDosDivision);
      proceso.setResultado(to_string(numeroUno) + "/" +
                           to_string(numeroDosDivision) + "=" +
                           to_string(numeroUno / numeroDosDivision));
      proceso.setOperadores(to_string(numeroUno) + " / " +
                            to_string(numeroDosDivision));
      break;
    }
    case 3: {
      proceso.setResultado(to_string(numeroUno) + "+" + to_string(numeroDos) +
                           "=" + to_string(numeroUno + numeroDos));
      proceso.setOperadores(to_string(numeroUno) + " + " +
                            to_string(numeroDos));
      break;
    }
    case 4: {
      proceso.setResultado(to_string(numeroUno) + "-" + to_string(numeroDos) +
                           "=" + to_string(numeroUno - numeroDos));
      proceso.setOperadores(to_string(numeroUno) + " - " +
                            to_string(numeroDos));
      break;
    }
    case 5: {
      // Verificación de la división entre 0.
      verificarDivision(numeroDosDivision);
      proceso.setResultado(to_string(numeroUno) + "%" +
                           to_string(numeroDosDivision) + "=" +
                           to_string(numeroUno % numeroDosDivision));
      proceso.setOperadores(to_string(numeroUno) + " % " +
                            to_string(numeroDosDivision));
      break;
    }
  }

  int paginasPorProceso;

  proceso.setTiempoRespuestaVerificar(true);
  proceso.setVerificarBloqueado(false);
  proceso.setLoteID(numeroLote);
  proceso.setTiempoLlegada(tiempoTotal);
  proceso.setTiempoLlegadaVerificar(false);
  proceso.setQuantum(quantum);
  proceso.setTamanio(tamanio);

  // Calculamos el número total de paginas que ocupara el proceso
  int tamanios = proceso.getTamanio();
  paginasPorProceso = tamanios / 5;
  int residuoTamanio = tamanios % 5;
  if (residuoTamanio > 0) {
    paginasPorProceso++;
  }

  proceso.setResiduo(residuoTamanio);
  proceso.setPaginas(paginasPorProceso);

  i++;

  return proceso;
}

int main() {
  int numeroLote = 1;
  Datos proceso;  // Objeto proceso
  Lote lote;      // Objeto proceso
  vector<Datos> listaProcesos;
  vector<Lote> listaLote;  // lista de lotes
  vector<Datos> listaLoteTerminados;
  vector<Datos> listaBloq;
  vector<Marco> listaMarcos(46);
  vector<Datos> listaListos;

  // Agregar marcos a la memoria:
  for (int i = 0; i < 41; i++) {
    listaMarcos[i].setIdMarco(i);
    listaMarcos[i].setIdProceso("Libre");
    listaMarcos[i].setTamanio("0/5");
  }

  // Agregamos las 5 paginas del SO
  for (int i = 41; i < 46; i++) {
    listaMarcos[i].setIdMarco(i);
    listaMarcos[i].setIdProceso("SO");
    listaMarcos[i].setTamanio("5/5");
  }

  cout << "Ingresa el numero de procesos" << endl;
  int numeroProcesoTotal = validarEntero();  // Numero de procesos total

  int i = 0;            // Contador de procesos
  int tiempoEstimado;   // Tiempo estimado del proceso
  int contadorProceso;  // Contador del proceso

  // Añadir proceso
  float quantum;

  cout << "Ingresa el quantum que deseas ingresar" << endl;
  cin >> quantum;

  bool comprobarCabidaBandera = true;

  while (i < numeroProcesoTotal) {
    system("cls");

    cout << "Proceso No.  " << i + 1 << endl << endl;

    proceso = crearProceso(lote, numeroLote, i, quantum);

    if (comprobarCabida(proceso, listaProcesos, listaListos, listaMarcos) &&
        comprobarCabidaBandera) {
      proceso.setTiempoLlegada(0);
      listaProcesos.push_back(proceso);
      lote.agregarElemento(proceso);
      meterProcesos(proceso, listaProcesos, listaListos, listaMarcos,
                    proceso.getResiduo());
    } else {
      proceso.setTiempoLlegadaVerificar(false);
      listaListos.push_back(proceso);
      comprobarCabidaBandera = false;
    }

    contadorProceso++;
  }

  for (Datos i : listaProcesos) {
    cout << "lista proceso " << i.GetID() << endl;
    ;
  }
  for (Datos i : listaListos) {
    cout << "lista listos " << i.GetID() << endl;
    ;
  }

  system("pause");

  listaLote.push_back(lote);  // Ingresa el lote
  lote.mostrarLote(lote);     // Muestra el lote completo antes de limpiarlo
  lote.vaciarLote();

  // Limpia la terminal para pasar a procesar.
  system("cls");

  auto contador = listaLote.begin();  // Se inicializa el iterador apuntando al
                                      // primer elemento de listaLote

  int tiempo = 1;
  int tiempoTotal = 0;
  int contadorLote = 0;  // Contador de lotes procesados
  int tiempoEspera = 1;

  while (contador != listaLote.end()) {
    Marco marco;
    int contVacios = 0;

    while (kbhit()) {
      getch();  // Leer y descartar el carácter del búfer de entrada (para que
                // no te salgan letras a lo pendejo
    }

    int posicion = 0;

    Lote& lote = *contador;  // Obtenemos el primer lote
    // Obtenemos el primer proceso del lote

    int tiempoTranscurrido = proceso.GetTiempoTranscurrido();

    while (lote.estaVaciaLote()) {
      recorrerListaBloq(listaBloq, lote);
      cout << "Tiempo total: " << tiempoTotal << " segundos" << endl;
      this_thread::sleep_for(chrono::seconds(1));
      tiempoTotal++;
      system("cls");
    }

    Datos proceso = lote.obtenerElemento(posicion);

    contadorLote++;

    lote.eliminarElemento(proceso);  // Eliminar el objeto del lote

    cout << "Procesos en cola de nuevos: " << listaListos.size()
         << "\tQuantum: " << quantum;
    if (!listaListos.empty()){
      cout << "\nSiguiente proceso: " << listaListos[0].toString();
    }
    cout << "\n\n\t-- LISTOS --" << endl;

    lote.mostrarLote(lote);

    cout << "\n----------------------------------" << endl;
    cout << "\t-- BLOQUEADOS --" << endl;

    lote.mostrarBloqueados(lote);

    cout << "\n----------------------------------" << endl;

    // Imprimir y procesar el proceso actual

    // Obtenemos el tiempo total estimado
    int totalTime = proceso.GetTiempo();
    // Obtenemos el tiempo restante
    int tiempobloq = 8;
    int tiempoRestante = proceso.GetTiempo();
    int tiempoSumado = 0;
    int tiempoQuantum = 0;

    bool pausado = false;

    // Agregar tiempo de respuesta **
    // Si paso ya, no se mueve el tiempo de respuesta, de lo contrario, entra y
    // lo define
    if (proceso.getTiempoRespuestaVerificar()) {
      proceso.setTiempoRespuesta(tiempoTotal);
      proceso.setTiempoRespuestaVerificar(false);
    }

    cout << "\t-- EJECUCION --" << endl;
    cout << "ID: " << proceso.GetID() << endl;
    cout << "Operadores: " << proceso.getOperadores() << endl;

    // Bucle para la interrumpción y la terminación de procesos
    while (tiempoRestante > 0) {
      if (tiempoQuantum == proceso.getQuantum()) {
        lote.eliminarElemento(proceso);
        proceso.SetTiempo(totalTime - tiempoSumado);
        proceso.SetTiempoTranscurrido(tiempoTranscurrido);
        proceso.setTiempoLlegadaVerificar(true);
        lote.agregarElemento(proceso);
        proceso = lote.obtenerElemento(posicion);
        tiempoQuantum = 0;
        break;
      }

      if (kbhit()) {
        char tecla = getch();  // Obtener la tecla presionada

        // Tecla para pausar el proceso actual
        if (tecla == 'p') {
          pausado = true;
          cout << "Proceso pausado. Presiona 'c' para reanudar." << endl;
        } else if (tecla == 'c') {  // Tecla para reanudar el proceso actual
          pausado = false;
          cout << "\033[3A\033[K";
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
          objetoAux.setVerificarBloqueado(true);

          listaBloq.push_back(objetoAux);
          lote.agregarElementoBloq(objetoAux);
          // Mover al siguiente proceso
          system("cls");

          // Mostrar el lote actualizado
          cout << "memoria actual" << endl;
          cout << "Bloqueados" << endl;
          lote.mostrarBloqueados(lote);

          this_thread::sleep_for(chrono::seconds(1));
          break;
        }
        // Tecla para interrupir el proceso actual y generar un error
        if (tecla == 'w') {
          // El resultado resulta ERROR
          proceso.SetTiempoEstimado(tiempoTranscurrido);
          proceso.setResultado("ERROR");
          proceso.setTiempoFinalizacion(tiempoTotal);
          proceso.setTiempoRetorno(proceso.getTiempoFinalizacion(),
                                   proceso.getTiempoLlegada());
          proceso.setTiempoServicio(tiempoTotal);
          proceso.setTiempoEspera(proceso.getTiempoServicio(),
                                  proceso.GetTiempoTranscurrido());
          // Pasamos el proceso a la lista de terminados y pasamos al otro
          // siguiente
          listaLoteTerminados.push_back(proceso);

          eliminarProceso(listaMarcos, listaListos, listaProcesos, lote,
                          proceso, tiempoTotal);

          this_thread::sleep_for(chrono::seconds(1));

          break;
        }
        if (tecla == 'b') {
          for (size_t i = 0; i < listaLoteTerminados.size(); i++) {
            imprimirTiempos(listaLoteTerminados[i]);
          }
          pausado = true;
          cout << "Proceso pausado. Presiona 'c' para reanudar." << endl;
        }
        if (tecla == 'n') {
          cout << "Proceso No.  " << i + 1 << endl << endl;

          Datos procesoNuevo =
              crearProceso(lote, numeroLote, i, tiempoTotal, quantum);

          if (comprobarCabida(procesoNuevo, listaProcesos, listaListos,
                              listaMarcos)) {
            procesoNuevo.setTiempoLlegada(tiempoTotal);
            procesoNuevo.setTiempoLlegadaVerificar(true);
            listaProcesos.push_back(procesoNuevo);
            // Lista de los procesos
            lote.agregarElemento(procesoNuevo);
            meterProcesos(procesoNuevo, listaProcesos, listaListos, listaMarcos,
                          procesoNuevo.getResiduo());
          } else {
            listaListos.push_back(procesoNuevo);
          }
        }
        if (tecla == 't') {
          Marco marco;
          cout << "\t-- TABLA DE PAGINAS -- \n\n" << endl;
          imprimirTablaPaginacion(marco, listaMarcos);

          pausado = true;
          cout << "Proceso pausado. Presiona 'c' para reanudar." << endl;
        }
      }

      // Si no esta pausado, sigue el proceso como si nada
      if (!pausado) {
        tiempoTranscurrido = proceso.GetTiempoTranscurrido();
        // recorrer el proceso de los bloqueados
        recorrerListaBloq(listaBloq, lote);
        // Imprimir información del proceso
        cout << "Tiempo restante: " << tiempoRestante << " segundos" << endl;
        cout << "Tiempo ejecutado: " << tiempoTranscurrido << " segundos"
             << endl;
        cout << "Tiempo total: " << tiempoTotal << " segundos" << endl;
        // Pausa de un segundo para simular el tiempo
        this_thread::sleep_for(chrono::seconds(1));
        tiempoRestante--;
        tiempoSumado++;
        tiempoTotal++;
        tiempoTranscurrido++;
        proceso.SetTiempoTranscurrido(tiempoTranscurrido);
        tiempobloq--;
        tiempoEspera++;
        tiempoQuantum++;
        // Dentro del bucle principal donde se ejecutan los procesos
        cout << "\033[3A\033[K";
        // Si el proceso ya termino su ejecucion:
        if (tiempoSumado == totalTime) {
          /*
          Función para quitar elemento de la lista marco,
          y agregar otro proceso de la lista procesos si es posible
          */

          eliminarProceso(listaMarcos, listaListos, listaProcesos, lote,
                          proceso, tiempoTotal);

          // Agregamos tiempo de finalización, retorno y servicio **
          proceso.setTiempoFinalizacion(tiempoTotal);
          proceso.setTiempoRetorno(proceso.getTiempoFinalizacion(),
                                   proceso.getTiempoLlegada());
          proceso.setTiempoServicio(tiempoTotal);
          proceso.setTiempoEspera(proceso.getTiempoServicio(),
                                  proceso.GetTiempoTranscurrido());
          listaLoteTerminados.push_back(proceso);
          // Aumentamos el contador para apuntar al siguiente lote
        }
      }
    }

    cout << endl;
    cout << "\t-- TERMINADOS --" << endl;

    // Mostrar los procesos terminados en una posición fija en la consola
    for (const Datos& proceso : listaLoteTerminados) {
      proceso.toStringTerminados(proceso.getLoteID());
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
