#include <iostream>
#include <cmath>
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
    int numerator;
    int denominator;
    void reduce()
    {
        int g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;
        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Fraction(int num = 0, int denom = 1)
    {
        if (denom == 0)
        {
            cout << "Denominator cannot be zero" << endl;
            return;
        }
        numerator = num;
        denominator = denom;
        reduce();
    }
    int getNum() const
    {
        return numerator;
    }
    int getDenom() const
    {
        return denominator;
    }
    Fraction(float f)
    {
        numerator = f * 1000000;
        denominator = 1000000;
        reduce();
    }
    Fraction operator+(const Fraction &f) const
    {
        return Fraction((this->numerator) * (f.denominator) + (this->denominator) * (f.numerator), (this->denominator) * (f.denominator));
    }
    Fraction operator+(float f) const
    {
        Fraction temp = Fraction(f);
        return (*this + temp);
    }
    friend Fraction operator+(float f, const Fraction &frac);

    Fraction operator-(const Fraction &f) const
    {
        return Fraction((this->numerator) * (f.denominator) - (this->denominator) * (f.numerator), (this->denominator) * (f.denominator));
    }
    Fraction operator-(float f) const
    {
        Fraction temp = Fraction(f);
        return (*this - temp);
    }
    friend Fraction operator-(float f, const Fraction &frac);

    Fraction operator*(const Fraction &f) const
    {
        return Fraction((this->numerator) * (f.numerator), (this->denominator) * (f.denominator));
    }
    Fraction operator*(float f) const
    {
        Fraction temp = Fraction(f);
        return ((*this) * temp);
    }
    friend Fraction operator*(float f, const Fraction &frac);

    Fraction operator/(const Fraction &f) const
    {
        if (f.numerator == 0)
        {
            throw invalid_argument("Can't divide by zero.");
        }
        return Fraction((this->numerator) * (f.denominator), (this->denominator) * (f.numerator));
    }
    Fraction operator/(float f) const
    {
        Fraction temp = Fraction(f);
        return (*this / temp);
    }
    friend Fraction operator/(float f, const Fraction &frac);

    Fraction &operator+=(const Fraction &f)
    {
        *this = *this + f;
        return *this;
    }
    Fraction &operator+=(float f)
    {
        *this = *this + f;
        return *this;
    }
    Fraction &operator-=(const Fraction &f)
    {
        *this = *this - f;
        return *this;
    }
    Fraction &operator-=(float f)
    {
        *this = *this - f;
        return *this;
    }
    Fraction &operator*=(const Fraction &f)
    {
        *this = *this * f;
        return *this;
    }
    Fraction &operator*=(float f)
    {
        *this = *this * f;
        return *this;
    }
    Fraction &operator/=(const Fraction &f)
    {
        *this = *this / f;
        return *this;
    }
    Fraction &operator/=(float f)
    {
        *this = *this / f;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Fraction &f);
};
Fraction operator+(float f, const Fraction &frac)
{
    return Fraction(f) + frac;
}
Fraction operator-(float f, const Fraction &frac)
{
    return Fraction(f) - frac;
}
Fraction operator*(float f, const Fraction &frac)
{
    return Fraction(f) * frac;
}
Fraction operator/(float f, const Fraction &frac)
{
    return Fraction(f) / frac;
}
ostream &operator<<(ostream &out, const Fraction &f)
{
    out << f.numerator << "/" << f.denominator;
    return out;
}

class FractionVector
{
    Fraction *fractions;
    int size;

public:
    FractionVector(int n = 10)
    {
        if (n <= 0)
        {
            cout << "Size must be positive." << endl;
            return;
        }
        size = n;
        fractions = new Fraction[n];
    }
    FractionVector(const FractionVector &f)
    {
        size = f.size;
        fractions = new Fraction[size];
        for (int i = 0; i < size; i++)
        {
            fractions[i] = f.fractions[i];
        }
    }
    FractionVector &operator=(const FractionVector &f)
    {
        if (this == &f)
            return *this;
        delete[] fractions;
        size = f.size;
        fractions = new Fraction[size];
        for (int i = 0; i < size; i++)
        {
            fractions[i] = f.fractions[i];
        }
        return *this;
    }
    ~FractionVector()
    {
        delete[] fractions;
    }
    int getsize()
    {
        return size;
    }
    Fraction &operator[](int n)
    {
        if (n < 0 || n >= size)
        {
            throw out_of_range("Index out of bounds.");
        }
        return fractions[n];
    }
    const Fraction &operator[](int n) const
    {
        if (n < 0 || n >= size)
        {
            throw out_of_range("Index out of bounds.");
        }
        return fractions[n];
    }
    FractionVector operator+(const FractionVector &f) const
    {
        if (size != f.size)
            throw invalid_argument("Size doesn't match.");
        FractionVector r = FractionVector(size);
        for (int i = 0; i < size; i++)
        {
            r[i] = fractions[i] + f.fractions[i];
        }
        return r;
    }

    FractionVector operator-(const FractionVector &f) const
    {
        if (size != f.size)
            throw invalid_argument("Size doesn't match.");
        FractionVector r = FractionVector(size);
        for (int i = 0; i < size; i++)
        {
            r[i] = fractions[i] - f.fractions[i];
        }
        return r;
    }
    FractionVector operator*(const Fraction &scalar) const
    {
        FractionVector r = FractionVector(size);
        for (int i = 0; i < size; i++)
        {
            r[i] = fractions[i] * scalar;
        }
        return r;
    }
    FractionVector operator/(const Fraction &scalar) const
    {
        if (scalar.getNum() == 0)
            throw invalid_argument("Division by zero.");
        FractionVector r = FractionVector(size);
        for (int i = 0; i < size; i++)
        {
            r[i] = fractions[i] / scalar;
        }
        return r;
    }
    Fraction operator*(const FractionVector &f) const
    {
        if (size != f.size)
            throw invalid_argument("Size doesn't match.");
        Fraction dot = Fraction();
        for (int i = 0; i < size; i++)
        {
            dot += fractions[i] * f.fractions[i];
        }
        return dot;
    }
    friend FractionVector operator*(const Fraction &scalar, const FractionVector &vec);
    friend FractionVector operator/(const Fraction &scalar, const FractionVector &vec);

    Fraction value()
    {
        float sum = 0.0;
        for (int i = 0; i < size; i++)
        {
            double a = ((double)fractions[i].getNum() / (double)fractions[i].getDenom());
            sum += a * a;
        }
        float g= sqrt(sum);
        return Fraction(g);
    }
    friend ostream &operator<<(ostream &out, const FractionVector &f);
};

ostream &operator<<(ostream &out, const FractionVector &f)
{
    out << "[ ";
    for (int i = 0; i < (f.size); i++)
    {
        out << f.fractions[i];
        if (i != f.size - 1)
            out << ", ";
    }
    out << " ]";
    return out;
}

FractionVector operator*(const Fraction &scalar, const FractionVector &vec)
{
    return vec * scalar;
}
FractionVector operator/(const Fraction &scalar, const FractionVector &vec)
{
    FractionVector r = FractionVector(vec.size);
    for (int i = 0; i < vec.size; i++)
    {
        r[i] = scalar / vec.fractions[i];
    }
    return r;
}

class FractionMatrix
{
    int row, col;
    FractionVector *row_elem;
    FractionVector *col_elem;

public:
    FractionMatrix(int r, int c)
    {
        row = r;
        col = c;
        row_elem = new FractionVector[row];
        col_elem = new FractionVector[col];
        for (int i = 0; i < row; i++)
        {
            row_elem[i] = FractionVector(col);
        }
        for (int i = 0; i < col; i++)
        {
            col_elem[i] = FractionVector(row);
        }
    }
    ~FractionMatrix()
    {
        delete[] row_elem;
        delete[] col_elem;
    }
    FractionMatrix(const FractionMatrix &f)
    {
        row = f.row;
        col = f.col;
        row_elem = new FractionVector[row];
        col_elem = new FractionVector[col];
        for (int i = 0; i < row; i++)
        {
            row_elem[i] = f.row_elem[i];
        }
        for (int i = 0; i < col; i++)
        {
            col_elem[i] = f.col_elem[i];
        }
    }
    FractionMatrix &operator=(const FractionMatrix &f)
    {
        if (this == &f)
            return *this;
        delete[] row_elem;
        delete[] col_elem;
        row = f.row;
        col = f.col;
        row_elem = new FractionVector[row];
        col_elem = new FractionVector[col];
        for (int i = 0; i < row; i++)
        {
            row_elem[i] = f.row_elem[i];
        }
        for (int i = 0; i < col; i++)
        {
            col_elem[i] = f.col_elem[i];
        }
    }
    FractionVector &operator[](int i)
    {
        if (i < 0 || i >= row)
        {
            throw out_of_range("Row index out of bounds");
        }
        return row_elem[i];
    }
    const FractionVector &operator[](int i) const
    {
        if (i < 0 || i >= row)
        {
            throw out_of_range("Row index out of bounds");
        }
        return row_elem[i];
    }
    void set_col_elem()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                col_elem[j][i] = row_elem[i][j];
            }
        }
    }
    FractionVector getColumn(int ind) const
    {
        if (ind < 0 || ind >= col)
        {
            throw out_of_range("Column index out of bounds");
        }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                col_elem[j][i] = row_elem[i][j];
            }
        }
        return col_elem[ind];
    }
    FractionMatrix operator+(const FractionMatrix &f) const
    {
        if (row != f.row || col != f.col)
            throw invalid_argument("Matrix dimensions don't match for addition.");
        FractionMatrix res(row, col);
        for (int i = 0; i < row; i++)
        {
            res.row_elem[i] = row_elem[i] + f.row_elem[i];
        }
        res.set_col_elem();
        return res;
    }
    FractionMatrix operator-(const FractionMatrix &f) const
    {
        if (row != f.row || col != f.col)
            throw invalid_argument("Matrix dimensions don't match subtraction.");
        FractionMatrix res(row, col);
        for (int i = 0; i < row; i++)
        {
            res.row_elem[i] = row_elem[i] - f.row_elem[i];
        }
        res.set_col_elem();
        return res;
    }
    FractionMatrix operator*(const Fraction &f) const
    {
        FractionMatrix res(row, col);
        for (int i = 0; i < row; i++)
        {
            res.row_elem[i] = row_elem[i] * f;
        }
        res.set_col_elem();
        return res;
    }
    friend FractionMatrix operator*(const Fraction &sc, const FractionMatrix &f);

    FractionMatrix operator/(const Fraction &f) const
    {
        if (f.getNum() == 0)
            throw invalid_argument("Division by zero.");
        FractionMatrix res(row, col);
        for (int i = 0; i < row; i++)
        {
            res.row_elem[i] = row_elem[i] / f;
        }
        res.set_col_elem();
        return res;
    }

    FractionMatrix operator*(const FractionMatrix &f) const
    {
        if (col != f.row)
            throw invalid_argument("Invalid matrix dimensions for multiplication");
        FractionMatrix res(row, f.col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < f.col; j++)
            {
                Fraction sum;
                for (int k = 0; k < col; k++)
                {
                    sum += (row_elem[i][k] * f.row_elem[k][j]);
                }
                res[i][j] = sum;
            }
        }
        res.set_col_elem();
        return res;
    }
    FractionMatrix operator%(const FractionMatrix &f) const
    {
        if (row != f.row || col != f.col)
            throw invalid_argument("Matrix dimensions don't match for hadamard.");
        FractionMatrix res(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                res[i][j] = row_elem[i][j] * f.row_elem[i][j];
            }
        }
        res.set_col_elem();
        return res;
    }
    FractionMatrix transpose() const
    {
        FractionMatrix res(col, row);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                res[j][i] = row_elem[i][j];
            }
        }
        res.set_col_elem();
        return res;
    }
    friend ostream &operator<<(ostream &out, const FractionMatrix &f);
};

FractionMatrix operator*(const Fraction &sc, const FractionMatrix &f)
{
    return f * sc;
}
ostream &operator<<(ostream &out, const FractionMatrix &f)
{
    for (int i = 0; i < f.row; i++)
    {
        out << f.row_elem[i] << endl;
    }
    return out;
}

int main()
{
    cout << "Fraction Class:\n";
    Fraction a(1, 2), b(3, 8);
    cout << "a= " << a << ", b= " << b << endl;
    cout << endl;
    Fraction sum1 = a + b;
    cout << "a+b = " << sum1 << endl;
    Fraction sum2 = a + 0.25;
    cout << "a+0.25 = " << sum2 << endl;
    Fraction sum3 = 0.5 + b;
    cout << "0.5+b = " << sum3 << endl;
    cout << endl;

    Fraction sub1 = a - b;
    cout << "a-b = " << sub1 << endl;
    Fraction sub2 = a - 0.25;
    cout << "a-0.25 = " << sub2 << endl;
    Fraction sub3 = 0.5 - b;
    cout << "0.5-b = " << sub3 << endl;
    cout << endl;

    Fraction mul1 = a * b;
    cout << "a*b = " << mul1 << endl;
    Fraction mul2 = a * 0.25;
    cout << "a*0.25 = " << mul2 << endl;
    Fraction mul3 = 0.5 * b;
    cout << "0.5*b = " << mul3 << endl;
    cout << endl;

    Fraction div1 = a / b;
    cout << "a/b = " << div1 << endl;
    Fraction div2 = a / 0.25;
    cout << "a/0.25 = " << div2 << endl;
    Fraction div3 = 0.5 / b;
    cout << "0.5/b = " << div3 << endl;
    cout << endl;

    a += b;
    cout << "After doing a+=b, a = " << a << endl;
    a -= b;
    cout << "After doing a-=b, a = " << a << endl;
    a *= b;
    cout << "After doing a*=b, a = " << a << endl;
    a /= b;
    cout << "After doing a/=b, a = " << a << endl;

    a += 0.25;
    cout << "After doing a+=0.25, a = " << a << endl;
    a -= 0.25;
    cout << "After doing a-=0.25, a = " << a << endl;
    a *= 0.25;
    cout << "After doing a*=0.25, a = " << a << endl;
    a /= 0.25;
    cout << "After doing a/=0.25, a = " << a << endl;
    cout << "\nFraction Vector Class:\n";
    FractionVector v1(3), v2(3);
    v1[0] = Fraction(1, 2);
    v1[1] = Fraction(1, 3);
    v1[2] = Fraction(1, 4);

    v2[0] = Fraction(2, 3);
    v2[1] = Fraction(1, 6);
    v2[2] = Fraction(3, 4);
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "\nFractions in v1 are: ";
    for (int i = 0; i < 3; i++)
    {
        cout << v1[i];
        if (i < 2)
            cout << ", ";
    }
    cout << endl;
    cout << "addition: v1+v2 = " << v1 + v2 << endl;
    cout << "subtraction: v1-v2 = " << v1 - v2 << endl;
    Fraction v1f(2, 5);
    cout << "scalar multiplication: v1*0.4 = " << v1 * v1f << endl;
    cout << "scalar multiplication: 0.4*v1 = " << v1f * v1 << endl;
    cout << "scalar division: v1/0.4 = " << v1 / v1f << endl;
    cout << "scalar division: 0.4/v1 = " << v1f / v1 << endl;

    cout << "dot product of v1*v2 = " << v1 * v2 << endl;
    cout << "L2 norm of v1 = " << v1.value() << endl;
    cout << "L2 norm of v2 = " << v2.value() << endl;
    cout << "\nFraction Matrix Class\n";
    FractionMatrix m1(3, 3), m2(3, 3), m3(2, 3);
    int v = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m1[i][j] = Fraction(1, v++);
        }
    }
    cout << "Matrix m1 = \n"
         << m1 << endl;
    v = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m2[i][j] = Fraction(v++);
        }
    }
    cout << "Matrix m2 = \n"
         << m2 << endl;
    v = 1;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m3[i][j] = Fraction(3, v++);
        }
    }
    cout << "Matrix m3 = \n"
         << m3 << endl;
    cout << "column 3 of m1 = \n"
         << m1.getColumn(2);
    cout << "\n";
    cout << "\naddition: m1 + m2 = \n"
         << m1 + m2 << endl;
    cout << "\nsubtraction: m1 - m2 = \n"
         << m1 - m2 << endl;
    cout << "\nscalar multiplication: m1*0.5 = \n"
         << m1 * a << endl;
    cout << "\nscalar multiplication: 0.5*m1 = \n"
         << a * m1 << endl;
    cout << "\nscalar division: m1/0.5 = \n"
         << m1 / a << endl;
    cout << "\nmatrix multiplication: m1*m2 = \n"
         << m1 * m2 << endl;
    cout << "column 3 of multiplication matrix = \n"
         << (m1 * m2).getColumn(2);
    cout << "\n";
    cout << "\nmatrix hadamard multiplication: m1%m2 = \n"
         << m1 % m2 << endl;
    cout << "transpose of Matrix m2 = \n"
         << m2.transpose() << endl;
        cout << "transpose of Matrix m3 = \n"
         << m3.transpose() << endl;
    cout << "\nException:\n";
    Fraction c(4, 0);
    try
    {
        cout << "a/0 = \n"
             << a / 0 << endl;
    }

    catch (const invalid_argument &e)
    {
        cerr << "1.Invalid Argument: " << e.what() << "\n";
    }
    FractionVector test(-3);
    FractionVector t1(1), t2(2);
    t1[0] = 9;
    t2[0] = 2;
    t2[1] = 6;
    try
    {
        cout << t1 + t2 << endl;
    }
    catch (const invalid_argument &e)
    {
        cerr << "2.Invalid Argument: " << e.what() << "\n";
    }
    try
    {
        cout << t1 * t2 << endl;
    }
    catch (const invalid_argument &e)
    {
        cerr << "3.Invalid Argument: " << e.what() << "\n";
    }
    try
    {
        cout << v1[8];
    }
    catch (const out_of_range &e)
    {
        cerr << "4.Out of range: " << e.what() << "\n";
    }
    try
    {
        cout << m1[7][1];
    }
    catch (const out_of_range &e)
    {
        cerr << "5.Out of range: " << e.what() << "\n";
    }
    try
    {
        cout << m1.getColumn(8);
    }
    catch (const out_of_range &e)
    {
        cerr << "6.Out of range: " << e.what() << "\n";
    }
    try
    {
        cout << "m1%m3 = \n"
             << m1 % m3 << endl;
    }
    catch (const invalid_argument &e)
    {
        cerr << "7.Invalid Argument: " << e.what() << "\n";
    }
    try
    {
        cout << "m1*m3 = \n"
             << m1 * m3 << endl;
    }
    catch (const invalid_argument &e)
    {
        cerr << "8.Invalid Argument: " << e.what() << "\n";
    }
    try
    {
        cout << "m1+m3 = \n"
             << m1 + m3 << endl;
    }
    catch (const invalid_argument &e)
    {
        cerr << "9.Invalid Argument: " << e.what() << "\n";
    }
    try
    {
        cout << "m1/0 = \n"
             << m1 / 0 << endl;
    }
    catch (const invalid_argument &e)
    {
        cerr << "10.Invalid Argument: " << e.what() << "\n";
    }
    try
    {
        cout << "column 4 of m1 = \n"
             << m1.getColumn(3);
    }
    catch (const out_of_range &e)
    {
        cerr << "11.Out of range: " << e.what() << "\n";
    }
}