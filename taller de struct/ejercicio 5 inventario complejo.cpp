#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

// ejercicio 5
// Enumeración para las categorías de productos
enum class Categoria
{
    ELECTRONICA,
    ALIMENTOS,
    ROPA,
    HOGAR
};

// Estructura para representar un producto
struct Producto
{
    string codigo;
    string nombre;
    double precio;
    int cantidad;
    Categoria categoria;
    string proveedor;
    string fecha_vencimiento; // Para alimentos

    // Constructor
    Producto(string cod, string nom, double pre, int cant,
             Categoria cat, string prov, string fecha = "")
        : codigo(cod), nombre(nom), precio(pre), cantidad(cant),
          categoria(cat), proveedor(prov), fecha_vencimiento(fecha) {}
};

// Clase principal del sistema de inventario
class SistemaInventario
{
private:
    vector<Producto> productos;

public:
    // Agregar un nuevo producto
    void agregarProducto(const Producto &producto)
    {
        auto it = find_if(productos.begin(), productos.end(),
                          [&](const Producto &p)
                          { return p.codigo == producto.codigo; });

        if (it != productos.end())
        {
            cout << "Error: El código de producto ya existe\n";
            return;
        }
        productos.push_back(producto);
    }

    // Buscar producto por código
    Producto *buscarProducto(const string &codigo)
    {
        auto it = find_if(productos.begin(), productos.end(),
                          [&](const Producto &p)
                          { return p.codigo == codigo; });

        return it != productos.end() ? &(*it) : nullptr;
    }

    // Actualizar stock (suma)
    bool actualizarStock(const string &codigo, int cantidad)
    {
        if (Producto *p = buscarProducto(codigo))
        {
            p->cantidad += cantidad;
            return true;
        }
        return false;
    }

    // Nuevo: fijar stock a un valor absoluto
    bool setStock(const string &codigo, int nuevaCantidad)
    {
        if (Producto *p = buscarProducto(codigo))
        {
            p->cantidad = nuevaCantidad;
            return true;
        }
        return false;
    }

    // Mostrar inventario
    void mostrarInventario() const
    {
        cout << setw(10) << "Código"
             << setw(20) << "Nombre"
             << setw(10) << "Precio"
             << setw(10) << "Stock"
             << setw(15) << "Proveedor" << "\n";
        cout << string(65, '-') << "\n";

        for (const auto &p : productos)
        {
            cout << setw(10) << p.codigo
                 << setw(20) << p.nombre
                 << setw(10) << p.precio
                 << setw(10) << p.cantidad
                 << setw(15) << p.proveedor << "\n";
        }
    }

    // Calcular valor total del inventario
    double calcularValorTotal() const
    {
        double total = 0;
        for (const auto &p : productos)
        {
            total += p.precio * p.cantidad;
        }
        return total;
    }

    // Alertar productos con bajo stock (menos de 5 unidades)
    void alertaBajoStock() const
    {
        bool any = false;
        for (const auto &p : productos)
        {
            if (p.cantidad < 5) // Cambia a <=5 si quieres incluir exactamente 5
            {
                if (!any)
                {
                    cout << "\nProductos con bajo stock:\n";
                    any = true;
                }
                cout << p.nombre << " - Stock actual: " << p.cantidad << "\n";
            }
        }
        if (!any)
        {
            cout << "\nNo hay más productos con bajo stock menores a 5.\n";
        }
    }
};

int main()
{
    SistemaInventario sistema;

    // Agregar algunos productos de ejemplo
    sistema.agregarProducto(Producto("E001", "Smartphone", 599.99, 10,
                                     Categoria::ELECTRONICA, "TechCorp"));
    sistema.agregarProducto(Producto("A001", "Arroz", 2.99, 100,
                                     Categoria::ALIMENTOS, "FoodSupply", "2024-12-31"));
    sistema.agregarProducto(Producto("R001", "Camiseta", 19.99, 3,
                                     Categoria::ROPA, "FashionInc"));

    // Mostrar inventario inicial y alertas antes de reabastecer
    cout << "Inventario Actual:\n";
    sistema.mostrarInventario();
    sistema.alertaBajoStock(); // alerta antes de aumentar stock

    // Fijar stock a 5 (en vez de sumar)
    if (sistema.setStock("R001", 5))
    {
        cout << "\nStock actualizado correctamente para R001.\n";
    }
    else
    {
        cout << "\nNo se encontró el producto R001. Stock no actualizado.\n";
    }

    // Mostrar valor total y alertas después
    cout << "\nValor total del inventario: $"
         << fixed << setprecision(2)
         << sistema.calcularValorTotal() << "\n";

    sistema.alertaBajoStock();
    return 0;
}
