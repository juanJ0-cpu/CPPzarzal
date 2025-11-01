#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura del nodo
typedef struct Nodo
{
    int x;
    struct Nodo *sig; // Puntero al siguiente nodo
} Nodo;

// --- Funciones de Gestión de la Lista Enlazada ---

/**
 * @brief Crea un nuevo nodo.
 * @param valor El entero a almacenar.
 * @return Puntero al nuevo nodo o NULL si falla la asignación de memoria.
 */
Nodo *crear_nodo(int valor)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo == NULL)
    {
        perror("Error de asignación de memoria");
        return NULL;
    }
    nuevo->x = valor;
    nuevo->sig = NULL;
    return nuevo;
}

/**
 * @brief Añade un elemento al frente (cabeza) de la lista. (push_front)
 * @param cabeza Puntero al puntero de la cabeza de la lista.
 * @param valor El entero a añadir.
 */
void push_front(Nodo **cabeza, int valor)
{
    Nodo *nuevo = crear_nodo(valor);
    if (nuevo == NULL)
        return;

    // El nuevo nodo apunta a la cabeza actual
    nuevo->sig = *cabeza;
    // La cabeza de la lista se actualiza para apuntar al nuevo nodo
    *cabeza = nuevo;
    printf("Elemento %d añadido al frente.\n", valor);
}

/**
 * @brief Añade un elemento al final de la lista. (push_back)
 * @param cabeza Puntero al puntero de la cabeza de la lista.
 * @param valor El entero a añadir.
 */
void push_back(Nodo **cabeza, int valor)
{
    Nodo *nuevo = crear_nodo(valor);
    if (nuevo == NULL)
        return;

    // Si la lista está vacía, el nuevo nodo es la cabeza
    if (*cabeza == NULL)
    {
        *cabeza = nuevo;
    }
    else
    {
        // Recorrer la lista hasta el último nodo
        Nodo *actual = *cabeza;
        while (actual->sig != NULL)
        {
            actual = actual->sig;
        }
        // El último nodo ahora apunta al nuevo nodo
        actual->sig = nuevo;
    }
    printf("Elemento %d añadido al final.\n", valor);
}

/**
 * @brief Elimina y devuelve el elemento del frente de la lista. (pop_front)
 * @param cabeza Puntero al puntero de la cabeza de la lista.
 * @return El valor del nodo eliminado, o -1 si la lista está vacía (aunque este valor
 * puede ser ambiguo, se usa para simplificar el ejemplo).
 */
int pop_front(Nodo **cabeza)
{
    if (*cabeza == NULL)
    {
        printf("ERROR: pop_front en lista vacía.\n");
        return -1; // Lista vacía
    }

    // Guardar el nodo a eliminar y su valor
    Nodo *temp = *cabeza;
    int valor = temp->x;

    // Mover la cabeza al siguiente nodo
    *cabeza = (*cabeza)->sig;

    // Liberar la memoria del nodo eliminado
    free(temp);

    printf("Elemento %d (frente) eliminado.\n", valor);
    return valor;
}

/**
 * @brief Calcula el número de elementos en la lista. (size)
 * @param cabeza Puntero a la cabeza de la lista.
 * @return El número de nodos.
 */
size_t size(Nodo *cabeza)
{
    size_t contador = 0;
    Nodo *actual = cabeza;
    while (actual != NULL)
    {
        contador++;
        actual = actual->sig;
    }
    return contador;
}

/**
 * @brief Libera toda la memoria de la lista. (clear)
 * @param cabeza Puntero al puntero de la cabeza de la lista.
 */
void clear(Nodo **cabeza)
{
    Nodo *actual = *cabeza;
    Nodo *siguiente;

    while (actual != NULL)
    {
        siguiente = actual->sig; // Guardar el puntero al siguiente nodo
        free(actual);            // Liberar la memoria del nodo actual
        actual = siguiente;      // Avanzar al siguiente nodo
    }
    // Asegurar que la cabeza queda nula después de vaciar la lista
    *cabeza = NULL;
    printf("Lista vaciada y memoria liberada.\n");
}

/**
 * @brief Imprime el contenido de la lista desde la cabeza hasta el final.
 * @param cabeza Puntero a la cabeza de la lista.
 */
void imprimir_lista(Nodo *cabeza)
{
    printf("\n--- Contenido Final de la Lista ---\n");
    Nodo *actual = cabeza;
    if (actual == NULL)
    {
        printf("La lista está vacía.\n");
        return;
    }
    while (actual != NULL)
    {
        printf("%d ", actual->x);
        actual = actual->sig;
    }
    printf("\n------------------------------------\n");
}

// --- Función Principal (Manejo de Comandos) ---

int main()
{
    // La lista enlazada se representa solo por un puntero a su primer nodo (cabeza)
    // No usamos variables globales.
    Nodo *cabeza = NULL;
    char comando[10];
    int valor;

    printf("Inicie la simulación de la lista enlazada.\n");
    printf("Comandos: pf <int>, pb <int>, pop, size, clear, fin.\n");

    while (1)
    {
        printf("> ");
        if (scanf("%9s", comando) != 1)
        {
            // Manejar error de lectura o EOF
            break;
        }

        if (strcmp(comando, "pf") == 0)
        { // push_front
            if (scanf("%d", &valor) == 1)
            {
                push_front(&cabeza, valor);
            }
            else
            {
                printf("Error: pf requiere un entero.\n");
            }
        }
        else if (strcmp(comando, "pb") == 0)
        { // push_back
            if (scanf("%d", &valor) == 1)
            {
                push_back(&cabeza, valor);
            }
            else
            {
                printf("Error: pb requiere un entero.\n");
            }
        }
        else if (strcmp(comando, "pop") == 0)
        { // pop_front
            pop_front(&cabeza);
        }
        else if (strcmp(comando, "size") == 0)
        { // size
            printf("Tamaño actual de la lista: %zu\n", size(cabeza));
        }
        else if (strcmp(comando, "clear") == 0)
        { // clear
            clear(&cabeza);
        }
        else if (strcmp(comando, "fin") == 0)
        { // fin
            break;
        }
        else
        {
            // Consumir el resto de la línea para evitar errores futuros
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            printf("Comando desconocido: %s\n", comando);
        }
    }

    // Impresión final del contenido (como se pide en el enunciado)
    imprimir_lista(cabeza);

    // Liberar la memoria restante antes de salir (si el usuario no ejecutó 'clear')
    if (cabeza != NULL)
    {
        clear(&cabeza);
    }

    return 0;
}