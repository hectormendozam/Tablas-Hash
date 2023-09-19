#include <iostream>
using namespace std;

// CLASE ESTUDIANTE
class Estudiante {
private:
    int matricula;
    float calif1;
    float calif2;
    float calif3;
public:
    Estudiante();
    Estudiante(int mat, float c1, float c2, float c3);
    int getMatricula(); 
    void modificarCalificaciones(float c1, float c2, float c3);
    void mostrarDatos(); 
};

Estudiante::Estudiante() {
    matricula = 0;
    calif1 = 0.0;
    calif2 = 0.0;
    calif3 = 0.0;
}

Estudiante::Estudiante(int mat, float c1, float c2, float c3) {
    matricula = mat;
    calif1 = c1;
    calif2 = c2;
    calif3 = c3;
}

int Estudiante::getMatricula(){
    return matricula;
}

void Estudiante::modificarCalificaciones(float c1, float c2, float c3) {
    calif1 = c1;
    calif2 = c2;
    calif3 = c3;
}

void Estudiante::mostrarDatos(){
    cout << "Matricula: " << matricula << " | ";
    cout << calif1 << " | ";
    cout << calif2 << " | ";
    cout << calif3 << endl;
}

// FUNCIÓN HASH
void metodoHash(Estudiante* tablaHash, Estudiante estudiante, int numeroElementos) {
    int i = estudiante.getMatricula() % numeroElementos;
    bool noInsertado = true;
    bool claveDuplicada = false;

    while (noInsertado && !claveDuplicada) {
        if (tablaHash[i].getMatricula() == 0) {
            tablaHash[i] = estudiante; // Inserta el elemento en la posición i de la matriz
            noInsertado = false;
        }
        else if (tablaHash[i].getMatricula() == estudiante.getMatricula()) {
            cout << "Error: Esta matricula ya EXISTE!" << endl; // Ocurrió una colisión
            claveDuplicada = true;
        }
        else {
            i = (i + 1) % numeroElementos;  // Avanza al siguiente elemento
            if (i == estudiante.getMatricula() % numeroElementos) {
                cout << "Error: La tabla esta LLENA!" << endl;
                break;
            }
        }
    }
}

// CLASE TABLA HASH
class TablaHash {
private:
    int tamMaximo;
    Estudiante* tabla;
public:
    TablaHash(int tamTabla);
    void insertarEstudiante(const Estudiante& estudiante);
    void eliminarEstudiante(int matricula);
    void buscarEstudiante(int matricula);
    void modificarCalificaciones(int matricula, float calif1, float calif2, float calif3);
    void imprimirTabla();
};

TablaHash::TablaHash(int tamTabla){
    tamMaximo = tamTabla;
    tabla = new Estudiante[tamTabla];
}

void TablaHash::insertarEstudiante(const Estudiante& estudiante) {
    metodoHash(tabla, estudiante, tamMaximo);
}

void TablaHash::eliminarEstudiante(int matricula) {
    int i = matricula % tamMaximo;

    for (int j = 0; j < tamMaximo; j++) {
        if (tabla[i].getMatricula() == matricula) {
            tabla[i] = Estudiante();
            cout << "El estudiante con matricula " << matricula << " ha sido ELIMINADO!" << endl;
            return;
        }
        i = (i + 1) % tamMaximo;
    }

    cout << "El estudiante con matricula " << matricula << " no EXISTE!" << endl;
}

void TablaHash::buscarEstudiante(int matricula) {
    int i = matricula % tamMaximo;

    for (int j = 0; j < tamMaximo; j++) {
        if (tabla[i].getMatricula() == matricula) {
            tabla[i].mostrarDatos();
            return;
        }
        i = (i + 1) % tamMaximo;
    }

    cout << "El estudiante con matricula " << matricula << " NO ha sido encontrado!" << endl;
}

void TablaHash::modificarCalificaciones(int matricula, float calif1, float calif2, float calif3) {
    int i = matricula % tamMaximo;

    for (int j = 0; j < tamMaximo; j++) {
        if (tabla[i].getMatricula() == matricula) {
            tabla[i].modificarCalificaciones(calif1, calif2, calif3);
            cout << "Calificaciones del estudiante con matricula " << matricula << " modificadas!" << endl;
            return;
        }
        i = (i + 1) % tamMaximo;
    }

    cout << "El estudiante con matricula " << matricula << " no EXISTE!" << endl;
}

void TablaHash::imprimirTabla() {
    cout << "Num. de filas max de la tabla: " << tamMaximo << endl;
    cout << "\n---------- TABLA - CALIFICACIONES ----------\n" << endl;
    for (int i = 0; i < tamMaximo; i++) {
        if (tabla[i].getMatricula() != 0) {
            tabla[i].mostrarDatos();
        }
    }
}

int main() {
    int tamTabla;
    cout << "Ingrese el numero de elementos en la tabla: ";
    cin >> tamTabla;

    TablaHash tablaHash(tamTabla);
    bool mantener = true;

    do {
        cout << "\n----------- MENU - TABLA HASH -----------" << endl;
        cout << "1) INSERTAR ESTUDIANTE" << endl;
        cout << "2) MOSTRAR TABLA DE ESTUDIANTES" << endl;
        cout << "3) BUSCAR MATRICULA DE ESTUDIANTE" << endl;
        cout << "4) MODIFICAR CALIFICACIONES DE UN ESTUDIANTE" << endl;
        cout << "5) ELIMINAR UN ESTUDIANTE" << endl;
        cout << "6) SALIR" << endl;
        cout << "Ingrese la opcion deseada: ";

        int menu;
        cin >> menu;

        system("cls");

        switch (menu) {
            case 1: {
                int matricula;
                float calificacion1, calificacion2, calificacion3;

                cout << "Ingrese la matricula del estudiante: ";
                cin >> matricula;
                cout << "Ingrese la calificacion 1 del estudiante: ";
                cin >> calificacion1;
                cout << "Ingrese la calificacion 2 del estudiante: ";
                cin >> calificacion2;
                cout << "Ingrese la calificacion 3 del estudiante: ";
                cin >> calificacion3;

                Estudiante estudiante(matricula, calificacion1, calificacion2, calificacion3);
                tablaHash.insertarEstudiante(estudiante);
                break; }
            case 2: {
                tablaHash.imprimirTabla();
                break; }
            case 3: {
                int matricula;
                cout << "Ingrese la matricula que desea buscar: ";
                cin >> matricula;
                tablaHash.buscarEstudiante(matricula);
                break; }
            case 4: {
                int matricula;
                float nuevaCalificacion1, nuevaCalificacion2, nuevaCalificacion3;
                cout << "Ingrese la matricula del estudiante a modificar: ";
                cin >> matricula;
                cout << "Ingrese la nueva calificacion 1: ";
                cin >> nuevaCalificacion1;
                cout << "Ingrese la nueva calificacion 2: ";
                cin >> nuevaCalificacion2;
                cout << "Ingrese la nueva calificacion 3: ";
                cin >> nuevaCalificacion3;
                tablaHash.modificarCalificaciones(matricula, nuevaCalificacion1, nuevaCalificacion2, nuevaCalificacion3);
                break; }
            case 5: {
                int matricula;
                cout << "Ingrese la matricula del estudiante que desea eliminar: ";
                cin >> matricula;
                tablaHash.eliminarEstudiante(matricula);
                break; }
            case 6: {
                mantener = false;
                break; }
            default: {
                cout << "Error: Ingrese una opcion VALIDA del 1 al 6!" << endl;
                break; }
        }
    } while (mantener);

    return 0;
}