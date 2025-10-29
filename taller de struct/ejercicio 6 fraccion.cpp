#include <iostream>
#include <numeric>
#include <stdexcept>
#include <sstream>
#include <cstdint>

using namespace std;

// Helper gcd para int64_t (evita dependencia de std::gcd si el compilador no usa C++17)
static int64_t gcd64(int64_t a, int64_t b)
{
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    while (b != 0)
    {
        int64_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

struct Fraccion
{
    int64_t num{0};
    int64_t den{1};

    Fraccion() = default;
    Fraccion(int64_t n) : num(n), den(1) {}
    Fraccion(int64_t n, int64_t d)
    {
        if (d == 0)
            throw invalid_argument("Denominador no puede ser 0");
        num = n;
        den = d;
        normalizar();
    }

    void normalizar()
    {
        if (den < 0)
        {
            num = -num;
            den = -den;
        }
        int64_t g = gcd64(num, den); // ahora usa gcd64
        if (g > 1)
        {
            num /= g;
            den /= g;
        }
        // Convierte 0/x en 0/1
        if (num == 0)
            den = 1;
    }

    double toDouble() const { return static_cast<double>(num) / static_cast<double>(den); }

    // Operadores aritméticos
    Fraccion operator+(const Fraccion &o) const
    {
        __int128 a = (__int128)num * o.den + (__int128)o.num * den;
        __int128 b = (__int128)den * o.den;
        Fraccion r((int64_t)a, (int64_t)b);
        r.normalizar();
        return r;
    }
    Fraccion operator-(const Fraccion &o) const
    {
        __int128 a = (__int128)num * o.den - (__int128)o.num * den;
        __int128 b = (__int128)den * o.den;
        Fraccion r((int64_t)a, (int64_t)b);
        r.normalizar();
        return r;
    }
    Fraccion operator*(const Fraccion &o) const
    {
        Fraccion r(num * o.num, den * o.den);
        r.normalizar();
        return r;
    }
    Fraccion operator/(const Fraccion &o) const
    {
        if (o.num == 0)
            throw invalid_argument("Division por fraccion 0");
        Fraccion r(num * o.den, den * o.num);
        r.normalizar();
        return r;
    }

    Fraccion &operator+=(const Fraccion &o)
    {
        *this = *this + o;
        return *this;
    }
    Fraccion &operator-=(const Fraccion &o)
    {
        *this = *this - o;
        return *this;
    }
    Fraccion &operator*=(const Fraccion &o)
    {
        *this = *this * o;
        return *this;
    }
    Fraccion &operator/=(const Fraccion &o)
    {
        *this = *this / o;
        return *this;
    }

    Fraccion operator-() const { return Fraccion(-num, den); }

    // Comparaciones (usar cross-multiplicación con __int128 para evitar overflow)
    bool operator==(const Fraccion &o) const { return num == o.num && den == o.den; }
    bool operator!=(const Fraccion &o) const { return !(*this == o); }
    bool operator<(const Fraccion &o) const
    {
        __int128 left = (__int128)num * o.den;
        __int128 right = (__int128)o.num * den;
        return left < right;
    }
    bool operator>(const Fraccion &o) const { return o < *this; }
    bool operator<=(const Fraccion &o) const { return !(*this > o); }
    bool operator>=(const Fraccion &o) const { return !(*this < o); }

    string toString() const
    {
        if (den == 1)
        {
            return to_string(num);
        }
        else
        {
            ostringstream ss;
            ss << num << '/' << den;
            return ss.str();
        }
    }

    // Entrada/salida: formato aceptado "a/b" o "a"
    friend ostream &operator<<(ostream &os, const Fraccion &f)
    {
        if (f.den == 1)
            os << f.num;
        else
            os << f.num << '/' << f.den;
        return os;
    }
    friend istream &operator>>(istream &is, Fraccion &f)
    {
        string s;
        if (!(is >> s))
            return is;
        size_t pos = s.find('/');
        try
        {
            if (pos == string::npos)
            {
                f.num = stoll(s);
                f.den = 1;
            }
            else
            {
                f.num = stoll(s.substr(0, pos));
                f.den = stoll(s.substr(pos + 1));
                if (f.den == 0)
                {
                    is.setstate(ios::failbit);
                    return is;
                }
            }
            f.normalizar();
        }
        catch (...)
        {
            is.setstate(ios::failbit);
        }
        return is;
    }
};

// Ejemplos de uso
int main()
{
    try
    {
        Fraccion a(3, 4), b(5, 6);
        cout << "a = " << a << ", b = " << b << '\n';
        cout << "a + b = " << (a + b) << '\n';
        cout << "a - b = " << (a - b) << '\n';
        cout << "a * b = " << (a * b) << '\n';
        cout << "a / b = " << (a / b) << '\n';
        cout << "Comparaciones: a < b ? " << (a < b) << '\n';
        cout << "Leer fraccion (formato a/b o a): ";
        Fraccion c;
        if (cin >> c)
            cout << "Leido: " << c << '\n';
        else
            cout << "Entrada no valida\n";
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}