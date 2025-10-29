#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
// ejercicio 4
struct Polinomio
{
    // Vector de coeficientes donde el índice representa el exponente
    vector<double> coeficientes;

    // Constructor por defecto (polinomio nulo)
    Polinomio() {}

    // Constructor con vector de coeficientes
    Polinomio(const vector<double> &coefs) : coeficientes(coefs)
    {
        // Eliminar ceros al final
        while (!coeficientes.empty() && coeficientes.back() == 0)
        {
            coeficientes.pop_back();
        }
    }

    // Evaluar el polinomio en un punto x
    double evaluar(double x) const
    {
        double resultado = 0;
        for (size_t i = 0; i < coeficientes.size(); ++i)
        {
            resultado += coeficientes[i] * pow(x, i);
        }
        return resultado;
    }

    // Obtener el grado del polinomio
    int grado() const
    {
        return coeficientes.empty() ? 0 : coeficientes.size() - 1;
    }

    // Suma de polinomios
    Polinomio operator+(const Polinomio &otro) const
    {
        vector<double> resultado(max(coeficientes.size(), otro.coeficientes.size()), 0);

        // Copiar los coeficientes del primer polinomio
        for (size_t i = 0; i < coeficientes.size(); ++i)
        {
            resultado[i] = coeficientes[i];
        }

        // Sumar los coeficientes del segundo polinomio
        for (size_t i = 0; i < otro.coeficientes.size(); ++i)
        {
            resultado[i] += otro.coeficientes[i];
        }

        return Polinomio(resultado);
    }

    // Mostrar el polinomio
    void mostrar() const
    {
        if (coeficientes.empty())
        {
            cout << "0";
            return;
        }

        bool primero = true;
        for (int i = coeficientes.size() - 1; i >= 0; --i)
        {
            if (coeficientes[i] != 0)
            {
                if (!primero && coeficientes[i] > 0)
                {
                    cout << "+";
                }
                if (coeficientes[i] != 1 || i == 0)
                {
                    cout << coeficientes[i];
                }
                if (i > 0)
                {
                    cout << "x";
                    if (i > 1)
                    {
                        cout << "^" << i;
                    }
                }
                primero = false;
            }
        }
    }
};

int main()
{
    // Ejemplo de uso: p(x) = 3x² + 2x + 1
    Polinomio p1({1, 2, 3}); // Los coeficientes van de menor a mayor grado

    // q(x) = x² - 1
    Polinomio p2({-1, 0, 1});

    cout << "Polinomio 1: ";
    p1.mostrar();
    cout << "\nPolinomio 2: ";
    p2.mostrar();

    // Suma de polinomios
    Polinomio suma = p1 + p2;
    cout << "\nSuma: ";
    suma.mostrar();

    // Evaluación
    double x = 2.0;
    cout << "\n\nEvaluacion de p1 en x = " << x << ": " << p1.evaluar(x);

    return 0;
}