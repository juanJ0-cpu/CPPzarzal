#include <bits/stdc++.h>
using namespace std;

// Lee n enteros en el arreglo a (usa aritmética de punteros)
void leer_arreglo(int *a, size_t n)
{
    int *p = a;
    for (size_t i = 0; i < n; ++i, ++p)
    {
        if (!(cin >> *p))
            *p = 0; // valor por defecto si falla la lectura
    }
}

// Calcula mínimo, máximo y promedio (prom) de a[0..n-1]
void min_max_prom(const int *a, size_t n, int *minv, int *maxv, double *prom)
{
    if (n == 0)
    {
        *minv = *maxv = 0;
        *prom = 0.0;
        return;
    }
    const int *p = a;
    const int *end = a + n;
    int mn = *p, mx = *p;
    long long sum = 0;
    for (; p < end; ++p)
    {
        if (*p < mn)
            mn = *p;
        if (*p > mx)
            mx = *p;
        sum += *p;
    }
    *minv = mn;
    *maxv = mx;
    *prom = static_cast<double>(sum) / static_cast<double>(n);
}

int main()
{
    cout << "ejercicio 1: escribe la cantidad de numeros, para sacar minimo, maximo y promedio. y luego escribe los numeros separados por espacio o enter: ";
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    if (!(cin >> n))
        return 0;

    vector<int> a(n);

    leer_arreglo(a.data(), n);

    int mn, mx;
    double prom;
    min_max_prom(a.data(), n, &mn, &mx, &prom);

    cout << "min= " << mn << " max= " << mx << " prom= " << fixed << setprecision(2) << prom << "\n";
    return 0;
}