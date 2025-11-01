#include <iostream>
#include <cstddef>

int **mat_crear(size_t m, size_t n)
{
    if (m == 0 || n == 0)
        return nullptr;
    int **A = new int *[m];
    for (size_t i = 0; i < m; ++i)
        A[i] = new int[n];
    return A;
}

void mat_destruir(int **A, size_t m)
{
    if (!A)
        return;
    for (size_t i = 0; i < m; ++i)
        delete[] A[i];
    delete[] A;
}

void mat_sumas(int **A, size_t m, size_t n, int *sumF, int *sumC)
{
    if (!A || m == 0 || n == 0)
        return;
    // inicializar sumas
    for (size_t i = 0; i < m; ++i)
        sumF[i] = 0;
    for (size_t j = 0; j < n; ++j)
        sumC[j] = 0;

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            int v = A[i][j];
            sumF[i] += v;
            sumC[j] += v;
        }
    }
}

void imprimir_arr(const int *a, size_t len)
{
    std::cout << "[";
    for (size_t i = 0; i < len; ++i)
    {
        std::cout << a[i];
        if (i + 1 < len)
            std::cout << ",";
    }
    std::cout << "]";
}

void imprimir_matriz(int **A, size_t m, size_t n)
{
    std::cout << "Matriz " << m << "x" << n << ":\n";
    for (size_t i = 0; i < m; ++i)
    {
        std::cout << "[";
        for (size_t j = 0; j < n; ++j)
        {
            std::cout << A[i][j];
            if (j + 1 < n)
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
}

int main()
{
    size_t m, n;
    std::cout << "Ingrese la cantidad de filas: ";
    if (!(std::cin >> m))
        return 1;

    std::cout << "Ingrese la cantidad de columnas: ";
    if (!(std::cin >> n))
        return 1;

    int **A = mat_crear(m, n);
    if (!A && (m != 0 && n != 0))
        return 1;

    std::cout << "Ingrese los " << (m * n) << " enteros (fila por fila):\n";
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            std::cout << "A[" << i << "][" << j << "] = ";
            std::cin >> A[i][j];
        }
    }

    // Mostrar la matriz ingresada
    std::cout << "\nDatos ingresados:\n";
    imprimir_matriz(A, m, n);
    std::cout << "\n";

    int *sumF = new int[m];
    int *sumC = new int[n];

    mat_sumas(A, m, n, sumF, sumC);

    std::cout << "sumF: ";
    imprimir_arr(sumF, m);
    std::cout << "\n";

    std::cout << "sumC: ";
    imprimir_arr(sumC, n);
    std::cout << "\n";

    delete[] sumF;
    delete[] sumC;
    mat_destruir(A, m);
    return 0;
}