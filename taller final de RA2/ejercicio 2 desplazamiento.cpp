#include <iostream>
#include <cstddef>
#include <vector>
#include <limits>

void reverse(int *a, size_t i, size_t j)
{
    if (!a || i >= j)
        return;
    int *pi = a + i;
    int *pj = a + j;
    while (pi < pj)
    {
        int tmp = *pi;
        *pi = *pj;
        *pj = tmp;
        ++pi;
        --pj;
    }
}

void rotar_derecha(int *a, size_t n, size_t k)
{
    if (!a || n == 0)
        return;
    k %= n;
    if (k == 0)
        return;
    // método: reverse todo, reverse primeros k, reverse resto
    reverse(a, 0, n - 1);
    reverse(a, 0, k - 1);
    reverse(a, k, n - 1);
}

void imprimir(const int *a, size_t n)
{
    std::cout << "[";
    for (size_t i = 0; i < n; ++i)
    {
        std::cout << a[i];
        if (i + 1 < n)
            std::cout << ", ";
    }
    std::cout << "]";
}

int main()
{
    size_t n;
    std::cout << "Ingrese la cantidad de elementos: ";
    if (!(std::cin >> n) || n == 0)
    {
        std::cerr << "Entrada inválida o n == 0.\n";
        return 1;
    }

    std::vector<int> arr(n);
    std::cout << "Ingrese " << n << " enteros (separados por espacio o Enter):\n";
    for (size_t i = 0; i < n; ++i)
    {
        while (!(std::cin >> arr[i]))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Reingrese el elemento " << i << ": ";
        }
    }

    size_t k;
    std::cout << "Ingrese k (desplazamiento a la derecha): ";
    while (!(std::cin >> k))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida. Reingrese k: ";
    }

    std::cout << "Antes: ";
    imprimir(arr.data(), n);
    std::cout << "\n";

    rotar_derecha(arr.data(), n, k);

    std::cout << "Después: ";
    imprimir(arr.data(), n);
    std::cout << "\n";

    return 0;
}