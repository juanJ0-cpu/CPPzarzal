#include <iostream>
#include <string>
#include <cctype>
#include <cstddef>

size_t normalizar_espacios(const char *in, char *out, size_t outcap)
{
    if (!in || !out || outcap == 0)
        return 0;

    const char *src = in;
    char *dst = out;
    char *end = out + outcap - 1; // reservar 1 para '\0'

    // saltar espacios iniciales
    while (*src && std::isspace(static_cast<unsigned char>(*src)))
        ++src;

    bool pending_space = false;
    while (*src)
    {
        if (std::isspace(static_cast<unsigned char>(*src)))
        {
            // marcar que debe ir un único espacio cuando aparezca la próxima palabra
            pending_space = true;
            while (*src && std::isspace(static_cast<unsigned char>(*src)))
                ++src;
            continue;
        }

        // insertar espacio único si corresponde
        if (pending_space)
        {
            if (dst < end)
            {
                *dst++ = ' ';
            }
            else
            {
                break; // no hay espacio en out
            }
            pending_space = false;
        }

        // copiar la palabra (caracteres no espacio)
        while (*src && !std::isspace(static_cast<unsigned char>(*src)))
        {
            if (dst < end)
            {
                *dst++ = *src++;
            }
            else
            {
                // no queda espacio para más caracteres; descartar resto de la palabra
                while (*src && !std::isspace(static_cast<unsigned char>(*src)))
                    ++src;
                break;
            }
        }
    }

    *dst = '\0';
    return static_cast<size_t>(dst - out);
}

int main()
{
    std::string linea;
    std::cout << "Ingrese una línea (≤1000 chars):\n";
    if (!std::getline(std::cin, linea))
        return 0;

    if (linea.size() > 1000)
        linea.resize(1000);

    char salida[1001];
    size_t len = normalizar_espacios(linea.c_str(), salida, sizeof(salida));

    std::cout << "Salida: \"" << salida << "\" (longitud " << len << ")\n";
    return 0;
}