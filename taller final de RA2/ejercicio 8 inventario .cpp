#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura Venta
typedef struct
{
    char prod[32]; // Nombre del producto
    int unidades;  // Cantidad vendida
    double precio; // Precio unitario
} Venta;

// --- Funciones de Utilidad ---

/**
 * @brief Carga datos de un archivo CSV a un array dinámico de estructuras Venta.
 * @param nombre_archivo Nombre del archivo CSV.
 * @param n_registros Puntero donde se almacenará el número total de registros cargados.
 * @return Puntero al array dinámico de Venta, o NULL si hay error.
 */
Venta *cargar_ventas_csv(const char *nombre_archivo, size_t *n_registros)
{
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        *n_registros = 0;
        return NULL;
    }

    // Usaremos un array dinámico para almacenar las ventas
    Venta *ventas = NULL;
    size_t capacidad = 0;
    size_t count = 0;
    char linea[100];

    // Leer línea por línea
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        // Eliminar el salto de línea si existe
        linea[strcspn(linea, "\n")] = 0;

        // Si la capacidad es insuficiente, redimensionar (realloc)
        if (count >= capacidad)
        {
            capacidad = (capacidad == 0) ? 2 : capacidad * 2;
            Venta *temp = (Venta *)realloc(ventas, capacidad * sizeof(Venta));

            if (temp == NULL)
            {
                perror("Error de realloc al expandir el array");
                free(ventas);
                fclose(archivo);
                *n_registros = 0;
                return NULL;
            }
            ventas = temp;
        }

        // Tokenizar la línea usando ',' como delimitador
        char *token;
        int unidades;
        double precio;

        // 1. Producto
        token = strtok(linea, ",");
        if (token == NULL || strlen(token) >= 32)
            goto error_formato;
        strncpy(ventas[count].prod, token, 31);
        ventas[count].prod[31] = '\0'; // Asegurar terminación nula

        // 2. Unidades
        token = strtok(NULL, ",");
        if (token == NULL || sscanf(token, "%d", &unidades) != 1)
            goto error_formato;
        ventas[count].unidades = unidades;

        // 3. Precio
        token = strtok(NULL, ",");
        if (token == NULL || sscanf(token, "%lf", &precio) != 1)
            goto error_formato;
        ventas[count].precio = precio;

        count++;
    }

    // Si hubo una línea con formato incorrecto
    goto cierre_exitoso;

error_formato:
    fprintf(stderr, "⚠️ Error de formato en línea %zu. Se detiene la carga.\n", count + 1);
    free(ventas);
    ventas = NULL;
    count = 0;

cierre_exitoso:
    fclose(archivo);
    *n_registros = count;
    return ventas;
}

/**
 * @brief Calcula el total vendido, producto más vendido y ticket promedio.
 * @param ventas Puntero al array de estructuras Venta.
 * @param n_registros Número total de registros.
 * @param total_vendido Puntero para almacenar el total vendido.
 * @param producto_mas_vendido Puntero para almacenar el nombre del producto más vendido.
 * @param unidades_mas_vendidas Puntero para almacenar las unidades del producto más vendido.
 * @param ticket_promedio Puntero para almacenar el ticket promedio.
 */
void calcular_estadisticas(Venta *ventas, size_t n_registros,
                           double *total_vendido,
                           char *producto_mas_vendido,
                           int *unidades_mas_vendidas,
                           double *ticket_promedio)
{

    if (n_registros == 0)
    {
        *total_vendido = 0.0;
        *ticket_promedio = 0.0;
        strcpy(producto_mas_vendido, "N/A");
        *unidades_mas_vendidas = 0;
        return;
    }

    *total_vendido = 0.0;
    *unidades_mas_vendidas = 0;

    // El ticket promedio es la suma de los montos de cada venta, dividido por el número de ventas
    for (size_t i = 0; i < n_registros; i++)
    {
        double monto_venta = ventas[i].unidades * ventas[i].precio;
        *total_vendido += monto_venta;

        // Determinar el producto más vendido (por unidades)
        if (ventas[i].unidades > *unidades_mas_vendidas)
        {
            *unidades_mas_vendidas = ventas[i].unidades;
            strcpy(producto_mas_vendido, ventas[i].prod);
        }
    }

    // Cálculo final del ticket promedio
    *ticket_promedio = *total_vendido / n_registros;
}

// --- Función Principal ---

int main()
{
    const char *nombre_archivo = "ventas.csv";
    size_t n_ventas = 0;

    // 1. Creación del archivo de prueba (Caso 10)
    // Producto,Unidades,Precio
    FILE *f_test = fopen(nombre_archivo, "w");
    if (f_test == NULL)
    {
        perror("Error al crear el archivo de prueba");
        return 1;
    }
    // Totales de referencia:
    // Total Vendido: 30 + 100 + 45 + 10 = 185
    // Producto más vendido (unidades): Papel (10)
    // Ticket promedio: 185 / 4 = 46.25
    fprintf(f_test, "Boligrafo,3,10.0\n"); // 30
    fprintf(f_test, "Cuaderno,5,20.0\n");  // 100
    fprintf(f_test, "Lapiz,9,5.0\n");      // 45
    fprintf(f_test, "Papel,10,1.0\n");     // 10
    fclose(f_test);
    printf("Archivo '%s' creado con 4 registros de prueba.\n", nombre_archivo);

    // 2. Cargar los datos a la memoria dinámica
    Venta *datos_ventas = cargar_ventas_csv(nombre_archivo, &n_ventas);

    if (datos_ventas == NULL)
    {
        fprintf(stderr, "No se pudieron cargar los datos. Terminando.\n");
        return 1;
    }

    printf("\n--- Resultados de Carga ---\n");
    printf("Registros cargados exitosamente: %zu\n", n_ventas);

    // 3. Preparar variables para resultados
    double total_vendido;
    double ticket_promedio;
    char prod_mas_vendido[32];
    int unidades_mas_vendidas;

    // 4. Calcular estadísticas
    calcular_estadisticas(datos_ventas, n_ventas,
                          &total_vendido,
                          prod_mas_vendido,
                          &unidades_mas_vendidas,
                          &ticket_promedio);

    // 5. Imprimir resultados (Caso 10)
    printf("\n--- Análisis de Ventas ---\n");
    printf("Total Vendido: $%.2f\n", total_vendido);
    printf("Producto Más Vendido (por unidades): %s (%d unidades)\n", prod_mas_vendido, unidades_mas_vendidas);
    printf("Ticket Promedio por Transacción: $%.2f\n", ticket_promedio);

    // 6. Liberar la memoria asignada dinámicamente
    free(datos_ventas);
    printf("\nMemoria dinámica liberada. Fin del programa.\n");

    return 0;
}