// PROFEE NO PUDE HACER EL 7 :( PERO LO INTENTÉ

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Contacto
{
    int id;
    string nombre;
    string telefono;
    string email;
    string direccion;
};

const string FILENAME = "contacts.csv";
int siguienteId = 1;
vector<Contacto> contactos;

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    string item;
    stringstream ss(s);
    while (getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}

int safeStoi(const string &s)
{
    try
    {
        size_t pos;
        int v = stoi(s, &pos);
        if (pos != s.size())
            return -1;
        return v;
    }
    catch (...)
    {
        return -1;
    }
}

string leer(const string &prompt)
{
    cout << prompt;
    string linea;
    getline(cin, linea);
    return linea;
}

void cargarContactos()
{
    ifstream in(FILENAME);
    if (!in)
        return;
    string linea;
    int maxId = 0;
    while (getline(in, linea))
    {
        if (linea.empty())
            continue;
        auto f = split(linea, ';');
        if (f.size() < 5)
            continue;
        Contacto c;
        c.id = safeStoi(f[0]);
        c.nombre = f[1];
        c.telefono = f[2];
        c.email = f[3];
        c.direccion = f[4];
        contactos.push_back(c);
        if (c.id > maxId)
            maxId = c.id;
    }
    siguienteId = maxId + 1;
}

void guardarContactos()
{
    ofstream out(FILENAME, ios::trunc);
    for (const auto &c : contactos)
        out << c.id << ';' << c.nombre << ';' << c.telefono << ';' << c.email << ';' << c.direccion << '\n';
}

void mostrarContacto(const Contacto &c)
{
    cout << "ID: " << c.id << " | Nombre: " << c.nombre << " | Tel: " << c.telefono
         << " | Email: " << c.email << " | Dir: " << c.direccion << '\n';
}

void listarContactos()
{
    if (contactos.empty())
    {
        cout << "No hay contactos guardados.\n";
        return;
    }
    cout << "\n-- Contactos guardados --\n";
    for (const auto &c : contactos)
        mostrarContacto(c);
    cout << endl;
}

void agregarContacto()
{
    cout << "\nAgregar contacto (siga las indicaciones, presione Enter para cada dato):\n";
    Contacto c;
    c.id = siguienteId++;
    c.nombre = leer(" Nombre (ej. Ana Pérez): ");
    c.telefono = leer(" Teléfono (ej. +34 600 000 000): ");
    c.email = leer(" Email (ej. correo@ejemplo.com): ");
    c.direccion = leer(" Dirección (calle, ciudad): ");
    contactos.push_back(c);
    guardarContactos();
    cout << "Contacto agregado con ID " << c.id << ".\n";
}

vector<Contacto *> buscarPorTermino(const string &term)
{
    vector<Contacto *> res;
    string t = term;
    transform(t.begin(), t.end(), t.begin(), ::tolower);
    for (auto &c : contactos)
    {
        string a = c.nombre + " " + c.telefono + " " + c.email + " " + c.direccion;
        transform(a.begin(), a.end(), a.begin(), ::tolower);
        if (a.find(t) != string::npos)
            res.push_back(&c);
    }
    return res;
}

void buscarContacto()
{
    cout << "\nBuscar contacto:\n";
    string term = leer(" Escriba nombre, teléfono, email o parte y presione Enter: ");
    if (term.empty())
    {
        cout << " Búsqueda cancelada (vacía).\n";
        return;
    }
    auto r = buscarPorTermino(term);
    if (r.empty())
    {
        cout << " No se encontraron coincidencias.\n";
        return;
    }
    cout << " Resultados:\n";
    for (auto p : r)
        mostrarContacto(*p);
}

Contacto *encontrarPorId(int id)
{
    for (auto &c : contactos)
        if (c.id == id)
            return &c;
    return nullptr;
}

void editarContacto()
{
    cout << "\nEditar contacto:\n";
    listarContactos();
    string s = leer(" Escriba el ID del contacto que desea editar y presione Enter: ");
    int id = safeStoi(s);
    if (id < 0)
    {
        cout << " ID inválido.\n";
        return;
    }
    Contacto *c = encontrarPorId(id);
    if (!c)
    {
        cout << " Contacto no encontrado.\n";
        return;
    }
    cout << " Dejar en blanco y presionar Enter para mantener el valor actual.\n";
    cout << " Nombre actual: " << c->nombre << '\n';
    string tmp = leer(" Nuevo nombre: ");
    if (!tmp.empty())
        c->nombre = tmp;
    cout << " Teléfono actual: " << c->telefono << '\n';
    tmp = leer(" Nuevo teléfono: ");
    if (!tmp.empty())
        c->telefono = tmp;
    cout << " Email actual: " << c->email << '\n';
    tmp = leer(" Nuevo email: ");
    if (!tmp.empty())
        c->email = tmp;
    cout << " Dirección actual: " << c->direccion << '\n';
    tmp = leer(" Nueva dirección: ");
    if (!tmp.empty())
        c->direccion = tmp;
    guardarContactos();
    cout << " Contacto actualizado.\n";
}

void eliminarContacto()
{
    cout << "\nEliminar contacto:\n";
    listarContactos();
    string s = leer(" Escriba el ID del contacto a eliminar y presione Enter: ");
    int id = safeStoi(s);
    if (id < 0)
    {
        cout << " ID inválido.\n";
        return;
    }
    Contacto *c = encontrarPorId(id);
    if (!c)
    {
        cout << " Contacto no encontrado.\n";
        return;
    }
    string confirma = leer(" Escriba 'SI' para confirmar la eliminación: ");
    if (confirma != "SI" && confirma != "Si" && confirma != "si")
    {
        cout << " Eliminación cancelada.\n";
        return;
    }
    contactos.erase(remove_if(contactos.begin(), contactos.end(), [id](const Contacto &x)
                              { return x.id == id; }),
                    contactos.end());
    guardarContactos();
    cout << " Contacto eliminado.\n";
}

void imprimirAyuda()
{
    cout << "\nAyuda rápida:\n"
         << " Escriba el número de la opción y presione Enter.\n"
         << " 1 - Listar contactos  (ver todos los contactos y sus IDs)\n"
         << " 2 - Agregar contacto  (se le pedirá Nombre, Teléfono, Email, Dirección)\n"
         << " 3 - Buscar contacto   (escriba parte del nombre, teléfono o email)\n"
         << " 4 - Editar contacto   (necesita el ID; puede dejar campos en blanco)\n"
         << " 5 - Eliminar contacto (necesita el ID; se pedirá confirmación escribiendo SI)\n"
         << " 6 - Ayuda             (muestra esta ayuda)\n"
         << " 7 - Salir             (cierra el programa)\n\n";
}

void mostrarMenu()
{
    cout << "\n=====================================\n";
    cout << " SISTEMA DE GESTIÓN DE CONTACTOS\n";
    cout << " ¿Qué desea hacer? Escriba el número y presione Enter.\n";
    cout << " 1) Listar contactos    -> escribe 1\n";
    cout << " 2) Agregar contacto    -> escribe 2\n";
    cout << " 3) Buscar contacto     -> escribe 3\n";
    cout << " 4) Editar contacto     -> escribe 4\n";
    cout << " 5) Eliminar contacto   -> escribe 5\n";
    cout << " 6) Mostrar ayuda       -> escribe 6\n";
    cout << " 7) Salir               -> escribe 7\n";
    cout << "Ejemplo: para agregar un contacto escriba 2 y presione Enter.\n";
    cout << "=====================================\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Cargar datos y mostrar mensaje inicial
    cargarContactos();
    cout << "Bienvenido al SISTEMA DE GESTIÓN DE CONTACTOS.\n"
         << "El programa muestra las opciones y qué escribir para cada acción.\n";
    cout << flush;

    while (true)
    {
        mostrarMenu();
        cout << flush; // asegurar que el prompt se vea inmediatamente
        string opt = leer(" Opción: ");
        if (opt == "1")
            listarContactos();
        else if (opt == "2")
            agregarContacto();
        else if (opt == "3")
            buscarContacto();
        else if (opt == "4")
            editarContacto();
        else if (opt == "5")
            eliminarContacto();
        else if (opt == "6")
            imprimirAyuda();
        else if (opt == "7")
        {
            cout << "Saliendo...\n";
            break;
        }
        else
        {
            cout << " Opción inválida. Escriba un número entre 1 y 7.\n";
        }
    }

    // Pausa final para que la ventana no se cierre si se ejecuta haciendo doble clic
    cout << "\nPresione Enter para cerrar...";
    cout << flush;
    string espera;
    getline(cin, espera);

    // Alternativa Windows: system("pause");  (si prefieres)
    return 0;
}