#include <stdio.h>
#include <stdlib.h>

// --- Funciones de Operación ---

/**
 * @brief Duplica el valor de un entero.
 * @param x El entero de entrada.
 * @return El doble de x.
 */
int doble(int x)
{
    return x * 2;
}

/**
 * @brief Calcula el cuadrado de un entero.
 * @param x El entero de entrada.
 * @return El cuadrado de x.
 */
int cuadrado(int x)
{
    return x * x;
}

// --- Función de Alto Nivel (Aplicador) ---

/**
 * @brief Aplica una función de operación dada a cada elemento de un array.
 * * @param a Puntero al inicio del array de enteros.
 * @param n Tamaño del array.
 * @param op Puntero a la función de operación que toma un 'int' y devuelve un 'int'.
 */
void aplicar(int *a, size_t n, int (*op)(int))
{
    printf("Aplicando la operación a cada elemento...\n");
    for (size_t i = 0; i < n; i++)
    {
        // Llama a la función apuntada por 'op'
        a[i] = op(a[i]);
    }
    printf("Operación completada.\n");
}

// --- Funciones Auxiliares ---

/**
 * @brief Imprime los elementos de un array.
 */
void imprimir_array(const int *a, size_t n)
{
    printf("[");
    for (size_t i = 0; i < n; i++)
    {
        printf("%d", a[i]);
        if (i < n - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * @brief Restablece el array a su estado original (solo para el ejemplo).
 */
void reset_array(int *a, size_t n, const int *original)
{
    for (size_t i = 0; i < n; i++)
    {
        a[i] = original[i];
    }
    printf("Array restablecido al estado original.\n");
}

// --- Función Principal y Menú de Uso ---

int main()
{
    const size_t N = 5;
    // Array original inmutable para poder resetear
    const int original[5] = {1, 2, 3, 4, 5};
    // Array mutable al que se aplicarán las operaciones
    int a[5];

    // Inicializar el array de trabajo
    reset_array(a, N, original);

    int opcion;
    do
    {
        printf("\n--- Menú de Operaciones ---\n");
        printf("Array actual: ");
        imprimir_array(a, N);
        printf("1. Aplicar DOBLE\n");
        printf("2. Aplicar CUADRADO\n");
        printf("3. Restablecer array\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");

        if (scanf("%d", &opcion) != 1)
        {
            // Manejar entrada no numérica
            opcion = -1;
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ; // Limpiar buffer
        }

        switch (opcion)
        {
        case 1:
            // Se pasa el puntero a la función 'doble'
            aplicar(a, N, doble);
            break;
        case 2:
            // Se pasa el puntero a la función 'cuadrado'
            aplicar(a, N, cuadrado);
            break;
        case 3:
            reset_array(a, N, original);
            break;
        case 0:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opción inválida. Intente de nuevo.\n");
            break;
        }

    } while (opcion != 0);

    return 0;
}