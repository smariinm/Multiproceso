#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

const int MAX_NOMBRES = 100; 
string nombres[MAX_NOMBRES];  
int contador = 0;             


void agregarNombre(int id) {
    string nombre;

    cout << "Proceso " << id + 1 << ": Introduce un nombre: ";
    cin >> nombre;

    
    nombres[contador] = nombre;
    contador++;

    
    int indiceAleatorio = rand() % contador;
    cout << "Proceso " << id + 1 << ": El nombre seleccionado es: " << nombres[indiceAleatorio] << endl;
}

int main() {
    int N;

    
    cout << "¿Cuántos procesos quieres crear? ";
    cin >> N;

    
    srand(time(0));

  
    for (int i = 0; i < N; ++i) {
        pid_t pid = fork(); 

        if (pid < 0) {
            cerr << "Error al crear el proceso" << endl;
            return 1; 
        }
        else if (pid == 0) {
            
            agregarNombre(i); 
            return 0; 
        }
    }


    for (int i = 0; i < N; ++i) {
        wait(nullptr); 
    }

    cout << "Todos los procesos han terminado." << endl;
    cout << "Nombres introducidos: ";
    for (int i = 0; i < contador; ++i) {
        cout << nombres[i] << (i < contador - 1 ? ", " : "\n");
    }

    return 0;
}
