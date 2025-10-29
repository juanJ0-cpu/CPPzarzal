#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ejercicio 1
struct Producto
{
    string nombre;
    double precio = 0.0;
    int stock = 0;

    Producto() = default;
    Producto(const string &nombre, double precio = 0.0, int stock = 0)
        : nombre(nombre), precio(precio), stock(stock) {}
};

int main()
{
    Producto p1("Manzana");       // solo nombre
    Producto p2("Leche", 1.25);   // nombre + precio
    Producto p3("Pan", 0.80, 30); // nombre + precio + stock

    cout << fixed << setprecision(2);
    cout << p1.nombre << " - Precio: " << p1.precio << " - Stock: " << p1.stock << '\n';
    cout << p2.nombre << " - Precio: " << p2.precio << " - Stock: " << p2.stock << '\n';
    cout << p3.nombre << " - Precio: " << p3.precio << " - Stock: " << p3.stock << '\n';
    return 0;
}
