#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura Estudiante
typedef struct
{
    char nombre[40];
    int edad;
    double promedio;
} Estudiante;

// Función de comparación para qsort.
// Ordena de forma **descendente** por promedio.
int cmp_prom_desc(const void *a, const void *b)
{
    // Los argumentos 'a' y 'b' son punteros a Estudiante.
    const Estudiante *est_a = (const Estudiante *)a;
    const Estudiante *est_b = (const Estudiante *)b;

    // Se compara como double.
    if (est_a->promedio < est_b->promedio)
    {
        return 1; // 'a' debe ir después de 'b' (orden descendente)
    }
    else if (est_a->promedio > est_b->promedio)
    {
        return -1; // 'a' debe ir antes de 'b' (orden descendente)
    }
    else
    {
        return 0; // Son iguales
    }
}

// Función de búsqueda lineal por nombre.
// Retorna el índice del primer estudiante con el nombre buscado, o -1 si no se encuentra.
int buscar_nombre(Estudiante *v, size_t n, const char *clave)
{
    for (size_t i = 0; i < n; i++)
    {
        // La comparación debe ser exacta (strcmp devuelve 0 si las cadenas son iguales).
        if (strcmp(v[i].nombre, clave) == 0)
        {
            return (int)i; // Nombre encontrado
        }
    }
    return -1; // Nombre no encontrado
}

// Función auxiliar para imprimir un estudiante
void imprimir_estudiante(const Estudiante *e, int indice)
{
    printf("%2d. Nombre: %-30s | Edad: %2d | Promedio: %.2f\n",
           indice, e->nombre, e->edad, e->promedio);
}

int main()
{
    int n;

    // 1. Lectura del número de estudiantes
    printf("Ingrese el número de estudiantes (n): ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Número de estudiantes inválido.\n");
        return 1;
    }

    // 2. Asignación de memoria dinámica para el array de estudiantes
    Estudiante *vector_estudiantes = (Estudiante *)malloc(n * sizeof(Estudiante));
    if (vector_estudiantes == NULL)
    {
        perror("Error al asignar memoria");
        return 1;
    }

    // 3. Lectura de los datos de los 'n' estudiantes
    printf("\n--- Lectura de Datos ---\n");
    for (int i = 0; i < n; i++)
    {
        printf("Estudiante %d:\n", i + 1);
        printf("  Nombre: ");
        // Limpiar el buffer de entrada antes de leer la cadena
        while (getchar() != '\n')
            ;
        if (fgets(vector_estudiantes[i].nombre, 40, stdin) == NULL)
        {
            fprintf(stderr, "Error leyendo el nombre.\n");
            free(vector_estudiantes);
            return 1;
        }
        // Eliminar el salto de línea que `fgets` añade al final
        vector_estudiantes[i].nombre[strcspn(vector_estudiantes[i].nombre, "\n")] = 0;

        printf("  Edad: ");
        if (scanf("%d", &vector_estudiantes[i].edad) != 1)
        {
            fprintf(stderr, "Error leyendo la edad.\n");
            free(vector_estudiantes);
            return 1;
        }

        printf("  Promedio: ");
        if (scanf("%lf", &vector_estudiantes[i].promedio) != 1)
        {
            fprintf(stderr, "Error leyendo el promedio.\n");
            free(vector_estudiantes);
            return 1;
        }
    }

    // 4. Ordenamiento de los estudiantes por promedio descendente
    // 'vector_estudiantes' es un **puntero** a la estructura (Estudiante *).
    // qsort usa punteros a los elementos del array (punteros a struct Estudiante).
    qsort(vector_estudiantes, n, sizeof(Estudiante), cmp_prom_desc);

    // 5. Imprimir el Top-3 por promedio (Caso de prueba 2)
    printf("\n--- Top-3 de Estudiantes (Ordenado Descendente por Promedio) ---\n");
    int top = (n < 3) ? n : 3;
    for (int i = 0; i < top; i++)
    {
        imprimir_estudiante(&vector_estudiantes[i], i + 1);
    }

    // 6. Imprimir la lista completa (opcional, para verificación)
    printf("\n--- Lista Completa Ordenada ---\n");
    for (int i = 0; i < n; i++)
    {
        imprimir_estudiante(&vector_estudiantes[i], i + 1);
    }

    // 7. Búsqueda por nombre (Caso de prueba 3)
    char clave_busqueda[40];
    printf("\n--- Búsqueda de Estudiante ---\n");
    printf("Ingrese el nombre exacto a buscar: ");
    while (getchar() != '\n')
        ; // Limpiar el buffer de entrada
    if (fgets(clave_busqueda, 40, stdin) == NULL)
    {
        fprintf(stderr, "Error leyendo el nombre de búsqueda.\n");
        free(vector_estudiantes);
        return 1;
    }
    clave_busqueda[strcspn(clave_busqueda, "\n")] = 0; // Eliminar el salto de línea

    int indice_encontrado = buscar_nombre(vector_estudiantes, n, clave_busqueda);

    if (indice_encontrado != -1)
    {
        printf("\nEstudiante encontrado en el índice (0-base) %d:\n", indice_encontrado);
        // Imprime el estudiante, usando el índice y el puntero base 'vector_estudiantes'
        imprimir_estudiante(&vector_estudiantes[indice_encontrado], indice_encontrado + 1);
    }
    else
    {
        printf("\nEstudiante con nombre '%s' NO encontrado. (Devuelve -1)\n", clave_busqueda);
    }

    // 8. Liberar la memoria asignada
    free(vector_estudiantes);
    printf("\nMemoria liberada. Fin del programa.\n");

    return 0;
}