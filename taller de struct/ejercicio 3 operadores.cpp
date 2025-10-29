#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

class Producto
{
private:
    std::string nombre;
    double precio;

public:
    Producto(const std::string &n, double p) : nombre(n), precio(p) {}

    // Getters
    std::string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }

    // Operador de igualdad (ignora mayúsculas/minúsculas)
    bool operator==(const Producto &otro) const
    {
        std::string nombre1 = nombre;
        std::string nombre2 = otro.nombre;

        // Convertir ambos nombres a minúsculas
        std::transform(nombre1.begin(), nombre1.end(), nombre1.begin(), ::tolower);
        std::transform(nombre2.begin(), nombre2.end(), nombre2.begin(), ::tolower);

        return nombre1 == nombre2;
    }

    // Operador menor que (por precio, si igual por nombre)
    bool operator<(const Producto &otro) const
    {
        if (precio == otro.precio)
        {
            return nombre < otro.nombre;
        }
        return precio < otro.precio;
    }
};

int main()
{
    std::vector<Producto> productos = {
        Producto("Manzana", 2.5),
        Producto("MANZANA", 3.0),
        Producto("Pera", 2.5),
        Producto("Banana", 1.5)};

    // Ordenar productos
    std::sort(productos.begin(), productos.end());

    // Mostrar productos ordenados
    std::cout << "Productos ordenados por precio (y nombre si precio igual):\n";
    for (const auto &p : productos)
    {
        std::cout << p.getNombre() << " - $" << p.getPrecio() << "\n";
    }

    // Buscar un producto por nombre (ignorando mayúsculas/minúsculas)
    Producto buscar("manzana", 0.0); // El precio no importa para la búsqueda
    auto it = std::find(productos.begin(), productos.end(), buscar);

    if (it != productos.end())
    {
        std::cout << "\nProducto encontrado: " << it->getNombre()
                  << " - $" << it->getPrecio() << "\n";
    }
    else
    {
        std::cout << "\nProducto no encontrado\n";
    }

    return 0;
}