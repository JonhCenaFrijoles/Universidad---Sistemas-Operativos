using namespace std;
#include <sstream>
#include "string"

class Datos{
private:
    string nombre;
    int ID;
    int T_Duracion;
    string Operacion;
    string operadores;
    string operador;
    int lote;

public:
    string GetNombre() const;
    void SetNombre(string);

    void SetTiempo(int);
    int GetTiempo() const;

    int GetID()const;
    void SetId(int);

    void setOperadores(string, string, string);
    string getOperadores() const;

    void setOperador(string);
    string getOperador() const;

    string getOperacion() const;
    void setOperacion(string);

    void setLote(int);
    int getLote() const;
    
    int getContador() const;
    void toStringMostarlote() const;

    int toStringProceso(int) const;
    void toStringTerceraColumna() const;

    };
