#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
// ejercicio 2

struct Producto
{
    string nombre;
    double precio = 0.0;
    int stock = 0;

    Producto() = default;
    Producto(const string &nombre, double precio = 0.0, int stock = 0)
        : nombre(nombre), precio(precio), stock(stock) {}

    bool disponible() const
    {
        return stock > 0;
    }

    bool esValido() const
    {
        return precio >= 0 && !nombre.empty();
    }
};

int main()
{
    vector<Producto> productos = {
        Producto("Manzana", 1.50, 10),
        Producto("", -2.0, 5),      // inválido: nombre vacío y precio negativo
        Producto("Leche", 2.50, 0), // no disponible: stock 0
        Producto("Pan", 0.80, 30)};

    cout << "Productos antes del filtrado: " << productos.size() << endl;

    // Eliminar productos no válidos
    productos.erase(
        remove_if(productos.begin(), productos.end(),
                  [](const Producto &p)
                  { return !p.esValido(); }),
        productos.end());

    cout << "\nProductos válidos y disponibles:" << endl;
    cout << fixed << setprecision(2);
    for (const auto &p : productos)
    {
        if (p.disponible())
        {
            cout << p.nombre << " - Precio: " << p.precio
                 << " - Stock: " << p.stock << '\n';
        }
    }

    return 0;
}