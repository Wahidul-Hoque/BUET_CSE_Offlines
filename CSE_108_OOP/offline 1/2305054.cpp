#include <iostream>

using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

class Fraction
{
private:
    int numerator;
    int denominator;

public:
    Fraction()
    {
        numerator = 0;
        denominator = 1;
    }
    Fraction(int a)
    {
        numerator = a;
        denominator = 1;
    }
    Fraction(int a, int b)
    {
        numerator = a;
        denominator = b;
    }
    Fraction(const Fraction &f)
    {
        numerator = f.numerator;
        denominator = f.denominator;
    }
    Fraction &operator=(const Fraction &f)
    {
        if (this != &f)
        {
            numerator = f.numerator;
            denominator = f.denominator;
        }
        return *this;
    }
    ~Fraction()
    {
    }

    Fraction add(Fraction &f)
    {
        Fraction result;
        int a = (numerator * f.denominator) + (denominator * f.numerator);
        int d = denominator * f.denominator;
        int g = gcd(a, d);
        result.numerator = a / g;
        result.denominator = d / g;
        return result;
    }
    Fraction add(int n)
    {
        Fraction result;
        int a = denominator * n + numerator;
        int g = gcd(a, denominator);
        result.numerator = a / g;
        result.denominator = denominator / g;
        return result;
    }

    Fraction sub(Fraction &f)
    {
        Fraction result;
        int a = (numerator * f.denominator) - (denominator * f.numerator);
        int d = denominator * f.denominator;
        int g = gcd(a, d);
        result.numerator = a / g;
        result.denominator = d / g;
        return result;
    }
    Fraction sub(int n)
    {
        Fraction result;
        int a = numerator - (denominator * n);
        int g = gcd(a, denominator);
        result.numerator = a / g;
        result.denominator = denominator / g;
        return result;
    }
    Fraction mul(Fraction &f)
    {
        Fraction result;
        int a = numerator * f.numerator;
        int d = denominator * f.denominator;
        int g = gcd(a, d);
        result.numerator = a / g;
        result.denominator = d / g;
        return result;
    }
    Fraction mul(int n)
    {
        Fraction result;
        int a = numerator * n;
        int g = gcd(a, denominator);
        result.numerator = a / g;
        result.denominator = denominator / g;
        return result;
    }
    Fraction div(Fraction &f)
    {
        Fraction result;
        int a = numerator * f.denominator;
        int d = denominator * f.numerator;
        int g = gcd(a, d);
        result.numerator = a / g;
        result.denominator = d / g;
        return result;
    }
    Fraction div(int n)
    {
        Fraction result;
        if (n != 0)
        {
            int a = numerator;
            int d = denominator * n;
            int g = gcd(a, d);
            result.numerator = a / g;
            result.denominator = d / g;
            return result;
        }
        else
        {
            cout << "Can not divide by 0" << endl;
            return *this;
        }
    }
    int get_n()
    {
        return numerator;
    }
    int get_d()
    {
        return denominator;
    }
    void print()
    {
        if (denominator)
        {
            cout << numerator << "/" << denominator << endl;
        }
        else
        {
            cout << "Invalid fraction" << endl;
        }
    }
    int operator==(const Fraction &f)
    {
        return numerator * f.denominator == denominator * f.numerator;
    }
};

class FractionCollection
{
private:
    Fraction *fractions;
    int maxlength;
    int length;

public:
    FractionCollection()
    {
        maxlength = 10;
        length = 0;
        fractions = new Fraction[maxlength];
    }
    FractionCollection(int m)
    {
        maxlength = m;
        length = 0;
        fractions = new Fraction[maxlength];
    }
    ~FractionCollection()
    {
        delete[] fractions;
    }
    void insert(Fraction f)
    {
        fractions[length] = f;
        length++;
    }
    void insert(int pos, Fraction f)
    {
        for (int i = length; i > pos; i--)
        {
            fractions[i] = fractions[i - 1];
        }
        fractions[pos] = f;
        length++;
    }
    void remove()
    {
        length--;
    }
    void remove(Fraction f)
    {
        int ind;
        for (int i = 0; i < length;)
        {
            if (fractions[i] == f)
            {
                ind = i;
                break;
            }
        }
        remove(ind);
    }
    void remove(int pos)
    {
        for (int i = pos; i < length - 1; ++i)
        {
            fractions[i] = fractions[i + 1];
        }
        length--;
    }
    Fraction getmax()
    {
        Fraction max = fractions[0];
        for (int i = 1; i < length; i++)
        {
            if ((fractions[i].get_n() * max.get_d()) > (fractions[i].get_d() * max.get_n()))
            {
                max = fractions[i];
            }
        }
        return max;
    }
    Fraction getmin()
    {
        Fraction min = fractions[0];
        for (int i = 1; i < length; i++)
        {
            if ((fractions[i].get_n() * min.get_d()) < (fractions[i].get_d() * min.get_n()))
            {
                min = fractions[i];
            }
        }
        return min;
    }
    Fraction add(int start, int end)
    {
        Fraction result = fractions[start];
        for (int i = start + 1; i <= end; i++)
        {
            result = result.add(fractions[i]);
        }
        return result;
    }
    Fraction mul(int start, int end)
    {
        Fraction result = fractions[start];
        for (int i = start + 1; i <= end; i++)
        {
            result = result.mul(fractions[i]);
        }
        return result;
    }
    Fraction sub(int pos1, int pos2)
    {
        Fraction result = fractions[pos1].sub(fractions[pos2]);
        return result;
    }
    Fraction div(int pos1, int pos2)
    {
        Fraction result = fractions[pos1].div(fractions[pos2]);
        return result;
    }
    void print()
    {
        cout << endl;
        cout << "Fractions" << endl;
        cout << "-------------------------------" << endl;
        for (int i = 0; i < length; i++)
        {
            cout << "Fraction " << i << ": ";
            fractions[i].print();
        }

        cout << "Max: ";
        getmax().print();
        cout << "Min: ";
        getmin().print();
        cout << "Summation: ";
        add(0, length - 1).print();
        cout << "Multiplication: ";
        mul(0, length - 1).print();
    }
};
int main()
{
    Fraction a(5, 2), b(7, 2), c(9, 2), d(28, 5);
    cout << "Fraction" << endl;
    cout << "-------------------------------" << endl;
    cout << "A: ";
    a.print();
    cout << "B: ";
    b.print();
    cout << endl;
    cout << "Add(a,b): ";
    a.add(b).print();
    cout << "Add(a,2): ";
    a.add(2).print();
    cout << "Sub(a,b) ";
    a.sub(b).print();
    cout << "Sub(a,2) ";
    a.sub(2).print();
    cout << "Mul(a,b): ";
    a.mul(b).print();
    cout << "Mul(a,2): ";
    a.mul(2).print();
    cout << "Div(a,b): ";
    a.div(b).print();
    cout << "Div(a,2): ";
    a.div(2).print();
    cout << "Div(a,0): ";
    a.div(0).print();
    Fraction e, f(5), g(10);

    FractionCollection fc(10);
    fc.insert(a);
    fc.insert(b);
    fc.insert(c);
    fc.print();
    cout << "Sub(Pos0, Pos1): ";
    fc.sub(0, 1).print();
    cout << "Div(Pos0, Pos1): ";
    fc.div(0, 1).print();
    fc.remove(1);
    fc.print();
    fc.remove(a);
    fc.print();
    fc.insert(d);
    fc.insert(0, e);
    fc.insert(f);
    fc.insert(g);
    fc.print();
    fc.remove();
    fc.print();
    return 0;
}