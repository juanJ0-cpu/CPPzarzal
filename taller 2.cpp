// cout << "=== EJERCICIOS PARA PRACTICAR ===\n";
/*cout << "1. Crea un programa que encuentre la mediana de un array\n";
 cout << "2. Implementa la búsqueda binaria en un array ordenado\n";
 cout << "3. Desarrolla un programa que calcule la transpuesta de una matriz\n";
 cout << "4. Crea un sistema de inventario simple con arrays\n";
 cout << "5. Implementa el algoritmo de ordenamiento por selección\n";
 cout << "6. Desarrolla un programa que encuentre elementos duplicados\n";
 cout << "7. Crea un juego de tres en raya usando arrays bidimensionales\n\n";*/

#include <iostream>
#include <limits>
using namespace std;

void mostrarTablero(char tablero[3][3])
{
    cout << "   Tablero:\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "   ";
        for (int j = 0; j < 3; j++)
        {
            cout << tablero[i][j];
            if (j < 2)
                cout << "|";
        }
        cout << "\n";
        if (i < 2)
            cout << "   -----\n";
    }
}

bool hayGanador(char tablero[3][3], char jugador)
{
    // Filas y columnas
    for (int i = 0; i < 3; i++)
    {
        if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) ||
            (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador))
            return true;
    }
    // Diagonales
    if ((tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) ||
        (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador))
        return true;
    return false;
}

bool tableroLleno(char tablero[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i][j] == ' ')
                return false;
    return true;
}

int main()
{
    // 1. Crea un programa que encuentre la mediana de un array
    int a[5] = {5, 6, 7, 2, 4};
    // Crear una copia para ordenar
    int numerosOrdenados[5];
    for (int i = 0; i < 5; i++)
    {
        numerosOrdenados[i] = a[i];
    }

    // Ordenamiento burbuja (ascendente)
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if (numerosOrdenados[j] > numerosOrdenados[j + 1])
            {
                // Intercambiar elementos
                int temp = numerosOrdenados[j];
                numerosOrdenados[j] = numerosOrdenados[j + 1];
                numerosOrdenados[j + 1] = temp;
            }
        }
    }

    cout << "   Array ordenado (ascendente): ";
    for (int i = 0; i < 5; i++)
    {
        cout << numerosOrdenados[i] << " ";
    }
    cout << "\n\n";
    // La mediana es el valor central en un array ordenado
    cout << "   La mediana es: " << numerosOrdenados[2] << "\n";

    cout << " 2. Implementa la búsqueda binaria en un array ordenado\n";
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 10;
    int left = 0;
    int right = n - 1;
    int mid;
    bool found = false;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (arr[mid] == x)
        {
            found = true;
            break;
        }
        if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    if (found)
        cout << "   Elemento " << x << " encontrado en el array.\n";
    else
        cout << "   Elemento " << x << " no encontrado en el array.\n";

    cout << "3. Desarrolla un programa que calcule la transpuesta de una matriz\n";
    int matriz[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int transpuesta[3][3];

    // Calcular la transpuesta
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            transpuesta[j][i] = matriz[i][j];
        }
    }

    // Mostrar la matriz original
    cout << "   Matriz original:\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << "\n";
    }

    // Mostrar la matriz transpuesta
    cout << "   Matriz transpuesta:\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << transpuesta[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "4. Crea un sistema de inventario simple con arrays\n";
    const int MAX_PRODUCTOS = 10;
    string nombres[MAX_PRODUCTOS];
    int cantidades[MAX_PRODUCTOS];
    float precios[MAX_PRODUCTOS];
    int totalProductos = 0;

    // Agregar productos
    while (true)
    {
        string nombre;
        int cantidad;
        float precio;
        cout << "   Agregar producto (nombre, cantidad, precio) o 'fin' para terminar:\n";
        cout << "nombre: ";
        cin >> nombre;
        if (nombre == "fin")
            break;
        cout << "cantidad: ";
        cin >> cantidad;
        cout << "precio: ";
        cin >> precio;

        // Almacenar en arrays
        nombres[totalProductos] = nombre;
        cantidades[totalProductos] = cantidad;
        precios[totalProductos] = precio;
        totalProductos++;
    }

    // Mostrar inventario solo una vez al final
    cout << "   Inventario:\n";
    for (int i = 0; i < totalProductos; i++)
    {
        cout << "   Producto: " << nombres[i] << ", Cantidad: " << cantidades[i] << ", Precio: " << precios[i] << "\n";
    }

    cout << "5. Implementa el algoritmo de ordenamiento por selección\n";
    int arr2[] = {64, 25, 12, 22, 11};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    for (int i = 0; i < n2 - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n2; j++)
            if (arr2[j] < arr2[min_idx])
                min_idx = j;
        // Intercambiar el elemento mínimo con el primer elemento
        int temp = arr2[min_idx];
        arr2[min_idx] = arr2[i];
        arr2[i] = temp;
    }
    cout << "   Array ordenado (ascendente): ";
    for (int i = 0; i < n2; i++)
        cout << arr2[i] << " ";
    cout << "\n";

    cout << "6. Desarrolla un programa que encuentre elementos duplicados\n";
    int arr3[] = {1, 2, 3, 4, 2, 3, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    bool duplicadosEncontrados = false;
    cout << "   Elementos duplicados: ";
    for (int i = 0; i < n3; i++)
    {
        for (int j = i + 1; j < n3; j++)
        {
            if (arr3[i] == arr3[j])
            {
                cout << arr3[i] << " ";
                duplicadosEncontrados = true;
                break;
            }
        }
    }
    if (!duplicadosEncontrados)
        cout << "   No se encontraron elementos duplicados.\n";
    cout << "\n";

    cout << "7. Crea un juego de tres en raya usando arrays bidimensionales\n";
    char tablero[3][3] = {{' ', ' ', ' '},
                          {' ', ' ', ' '},
                          {' ', ' ', ' '}};
    char jugadorActual = 'X';
    int fila, columna;
    bool juegoTerminado = false;

    while (!juegoTerminado)
    {
        mostrarTablero(tablero);
        // Limpiar el búfer de entrada antes de pedir la jugada

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Pedir movimiento al jugador
        cout << "   Jugador " << jugadorActual << ", ingresa fila: ";
        cin >> fila;
        cout << "   Jugador " << jugadorActual << ", ingresa columna: ";
        cin >> columna;
        // Validar entrada
        if (cin.fail() || fila < 0 || fila > 2 || columna < 0 || columna > 2)
        {
            cout << "   Entrada inválida. Intenta de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (tablero[fila][columna] != ' ')
        {
            cout << "   Casilla ocupada. Intenta de nuevo.\n";
            continue;
        }

        // Realizar movimiento
        tablero[fila][columna] = jugadorActual;

        // Verificar ganador
        if (hayGanador(tablero, jugadorActual))
        {
            mostrarTablero(tablero);
            cout << "   ¡Jugador " << jugadorActual << " gana!\n";
            juegoTerminado = true;
        }
        else if (tableroLleno(tablero))
        {
            mostrarTablero(tablero);
            cout << "   ¡Empate!\n";
            juegoTerminado = true;
        }
        else
        {
            // Cambiar de jugador
            jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
        }
    }
    return 0;
}