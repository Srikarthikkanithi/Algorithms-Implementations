#include <bits/stdc++.h>
using namespace std;
typedef long long int lwi;
typedef long double ldi;
class String
{
private:
  string s;

public:
  String()
  {
    s = "";
  }
  String(string s1)
  {
    s = s1;
  }
  void print()
  {
    cout << s;
  }
  String operator*(lwi x)
  {
    String res;
    for (lwi i = 0; i < x; i++)
    {
      res.s += s;
    }
    return res;
  }
  String operator+(String s1)
  {
    String res;
    res.s = s + s1.s;
    return res;
  }
};
// creating a complex class to use it just like built-in data types
class Complex
{
private:
  lwi x, y; // real and img part of complex
public:
  // constructers for complex
  Complex() = default;
  Complex(lwi x1, lwi y1)
  {
    x = x1;
    y = y1;
  }
  // overloading operators for +,-,* for complex class
  Complex operator+(Complex c1)
  {
    lwi x2 = c1.x + x, y2 = c1.y + y;
    return {x2, y2};
  }
  Complex operator-(Complex c1)
  {
    lwi x2 = x - c1.x, y2 = y - c1.y;
    return {x2, y2};
  }
  Complex operator*(Complex c1)
  {
    lwi x1 = c1.x, y1 = c1.y;
    lwi x2 = x1 * x - y1 * y, y2 = x1 * y + y1 * x;
    return {x2, y2};
  }
  void print()
  {
    cout << x << " " << y << " ";
  }
};
// class for multiplying two polynomials
template <typename T>
class PolyMult
{
private:
  vector<T> initial_polynomial;

public:
  // constructors for storing the first polynomial and multiplying it with a second polynomial usiung * operator and storing it in another PolyMult class obj
  PolyMult() = default;
  PolyMult(vector<T> &p1)
  {
    initial_polynomial = p1;
  }
  vector<T> operator*(vector<T> &p2)
  {
    // calculating the length of the coefficient vector of two polyonomials of  size m,n which is m+n-1
    // lwi size1 = p1.size(), size2 = initial_polynomial.size();
    // lwi maxsize = size1 + size2 - 1;

    // function for multiplying two polynomials by divide-conquer implementation
    //  consider the two polynomials to be a(x),b(x)
    //  define a1(x),a2(x),b1(x),b2(x) such that:
    //  a(x)=a1(x)+x^(n/2)a2(x);
    //  a(x)=b1(x)+x^(n/2)b2(x);
    // such that a1(x),b1(x),a2(x),b2(x) are all n/2 deg polynomials
    //  so now calculating the multiplication of three polynomials of size n/2 :
    //  1: a1(x)*b1(x)
    //  2: a2(x)*b2(x)
    //  3: (a1(x)+b1(x))*(a2(x)+b2(x))
    //  recursively calculating until we get a polynomial of size 1
    lwi deg1 = initial_polynomial.size() - 1, product_len = 2 * deg1 + 1;
    vector<T> product(product_len, T{});
    if (deg1 == 0)
    {
      product[0] = product[0] + (initial_polynomial[0] * p2[0]);
      return product;
    }
    lwi nxtlen, halfing_len;
    if (deg1 % 2 == 0)
    {
      nxtlen = deg1 / 2 + 1;
      halfing_len = nxtlen - 1;
    }
    else
    {
      nxtlen = (deg1 + 1) / 2;
      halfing_len = nxtlen;
    }
    vector<T> a1(nxtlen, T{}), a2(nxtlen, T{}), b1(nxtlen, T{}), b2(nxtlen, T{});
    for (lwi i = 0; i < nxtlen; i++)
    {
      a1[i] = initial_polynomial[i];
      b1[i] = p2[i];
    }
    for (lwi i = deg1; i >= nxtlen; i--)
    {
      lwi ind = i - deg1 + nxtlen - 1;
      a2[ind] = initial_polynomial[i];
      b2[ind] = p2[i];
    }
    PolyMult coef1(a1), coef2(a2);
    vector<T> pro1 = coef1 * b1;
    vector<T> pro2 = coef1 * b2;
    vector<T> pro3 = coef2 * b1;
    vector<T> pro4 = coef2 * b2;
    lwi dec_len = pro2.size();
    vector<T> add23(dec_len);
    for (lwi i = 0; i < dec_len; i++)
    {
      add23[i] = pro2[i] + pro3[i];
    }
    for (lwi i = 0; i < dec_len; i++)
    {
      product[i] = product[i] + pro1[i];
    }
    for (lwi i = 0; i < dec_len; i++)
    {
      product[i + halfing_len] = product[i + halfing_len] + add23[i];
    }
    for (lwi i = 0; i < dec_len; i++)
    {
      product[i + 2 * halfing_len] = product[i + 2 * halfing_len] + pro4[i];
    }
    return product;
  }
  void change(lwi len2)
  {
    T t1{};
    lwi initial_len = initial_polynomial.size();
    for (lwi i = initial_len; i < len2; i++)
    {
      initial_polynomial.push_back(t1);
    }
  }
};
// class for evaluating the polynomial at a value x
template <typename T>
class PolyEval
{
private:
  vector<T> polynomial;

public:
  // constructors for creating an object
  PolyEval() = default;
  PolyEval(vector<T> &p1)
  {
    polynomial = p1;
  }
  // polynomial_eval func for evaluating a polynomial at a value x
  void polynomial_eval(T &evaluated_val, lwi x)
  {
    // implementing the evaluation of a function at a value x
    lwi poly_deg = polynomial.size() - 1;
    lwi multiplicand = 1;
    for (lwi i = 0; i < poly_deg; i++)
    {
      multiplicand *= x;
    }
    for (lwi i = poly_deg; i >= 0; i--)
    {
      // cout<<i<<" : "<<multiplicand<<endl;
      evaluated_val = evaluated_val + polynomial[i] * multiplicand;
      multiplicand /= x;
    }
  }
};
// class for differentiating a polynomial
template <typename T>
class PolyDiff
{
private:
  vector<T> initial_polynomial;

public:
  // constructors for cresating a polydiff class obj and diffentiating it and storing in another obj of same class
  PolyDiff() = default;
  PolyDiff(vector<T> &p1)
  {
    initial_polynomial = p1;
  }
  // differentiating the polynomial and storing it in the same object
  void polynomial_diff()
  {
    // implementation of differntiation of polynomial
    lwi poly_size = initial_polynomial.size();
    vector<T> temp_poly(poly_size - 1);
    for (lwi i = 1; i < poly_size; i++)
    {
      temp_poly[i - 1] = initial_polynomial[i] * i;
    }
    initial_polynomial = temp_poly;
  }
  vector<T> get_elements()
  {
    return initial_polynomial;
  }
};
int main()
{
  int q;
  cin >> q;
  while (q--)
  {
    int op;
    cin >> op;
    if (op == 1)
    {
      string datatype;
      cin >> datatype;
      lwi deg1;
      cin >> deg1;
      if (datatype == "integer")
      {
        vector<lwi> poly1_coeff;
        for (lwi i = 0; i < deg1; i++)
        {
          lwi pi;
          cin >> pi;
          poly1_coeff.push_back(pi);
        }
        PolyMult<lwi> p1(poly1_coeff);
        lwi deg2;
        cin >> deg2;
        vector<lwi> poly2_coeff;
        for (lwi i = 0; i < deg2; i++)
        {
          lwi pi;
          cin >> pi;
          poly2_coeff.push_back(pi);
        }
        if (deg2 <= deg1)
        {
          for (lwi i = deg2; i < deg1; i++)
          {
            poly2_coeff.push_back(0);
          }
        }
        else
        {
          p1.change(deg2);
        }
        vector<lwi> ans = p1 * poly2_coeff;
        lwi len_ans = deg1 + deg2 - 1;
        for (lwi i = 0; i < len_ans; i++)
        {
          cout << ans[i] << " ";
        }
        cout << endl;
      }
      else if (datatype == "float")
      {
        vector<ldi> poly1_coeff;
        for (lwi i = 0; i < deg1; i++)
        {
          ldi pi;
          cin >> pi;
          poly1_coeff.push_back(pi);
        }
        PolyMult<ldi> p1(poly1_coeff);
        lwi deg2;
        cin >> deg2;
        vector<ldi> poly2_coeff;
        for (lwi i = 0; i < deg2; i++)
        {
          ldi pi;
          cin >> pi;
          poly2_coeff.push_back(pi);
        }
        if (deg2 <= deg1)
        {
          for (lwi i = deg2; i < deg1; i++)
          {
            poly2_coeff.push_back(0.0);
          }
        }
        else
        {
          p1.change(deg2);
        }
        vector<ldi> ans = p1 * poly2_coeff;
        lwi len_ans = deg1 + deg2 - 1;
        for (lwi i = 0; i < len_ans; i++)
        {
          cout << fixed << setprecision(6) << ans[i] << " ";
        }
        cout << endl;
      }
      else
      {
        vector<Complex> poly1_coeff;
        for (lwi i = 0; i < deg1; i++)
        {
          lwi x1, y1;
          cin >> x1 >> y1;
          Complex c1(x1, y1);
          poly1_coeff.push_back(c1);
        }
        PolyMult<Complex> p1(poly1_coeff);
        lwi deg2;
        cin >> deg2;
        vector<Complex> poly2_coeff;
        for (lwi i = 0; i < deg2; i++)
        {
          lwi x1, y1;
          cin >> x1 >> y1;
          Complex c1(x1, y1);
          poly2_coeff.push_back(c1);
        }
        if (deg2 <= deg1)
        {
          for (lwi i = deg2; i < deg1; i++)
          {
            Complex c1(0, 0);
            poly2_coeff.push_back(c1);
          }
        }
        else
        {
          p1.change(deg2);
        }
        vector<Complex> ans = p1 * poly2_coeff;
        lwi len_ans = deg1 + deg2 - 1;
        for (lwi i = 0; i < len_ans; i++)
        {
          ans[i].print();
        }
        cout << endl;
      }
    }
    else if (op == 2)
    {
      string datatype;
      cin >> datatype;
      lwi n;
      cin >> n;
      if (datatype == "integer")
      {
        vector<lwi> polycoeff;
        for (lwi i = 0; i < n; i++)
        {
          lwi pi;
          cin >> pi;
          polycoeff.push_back(pi);
        }
        lwi x;
        cin >> x;
        PolyEval<lwi> p1(polycoeff);
        lwi value_atx = 0;
        p1.polynomial_eval(value_atx, x);
        cout << value_atx << endl;
      }
      else if (datatype == "float")
      {
        vector<ldi> polycoeff;
        for (lwi i = 0; i < n; i++)
        {
          ldi pi;
          cin >> pi;
          polycoeff.push_back(pi);
        }
        lwi x;
        cin >> x;
        PolyEval<ldi> p1(polycoeff);
        ldi value_atx = 0;
        p1.polynomial_eval(value_atx, x);
        cout << fixed << setprecision(6) << value_atx << endl;
      }
      else
      {
        vector<String> polycoeff;
        for (lwi i = 0; i < n; i++)
        {
          string st;
          cin >> st;
          String pi(st);
          polycoeff.push_back(pi);
        }
        lwi x;
        cin >> x;
        PolyEval<String> p1(polycoeff);
        String value_atx;
        p1.polynomial_eval(value_atx, x);
        value_atx.print();
        cout << endl;
      }
    }
    else
    {
      string datatype;
      cin >> datatype;
      lwi deg;
      cin >> deg;
      if (datatype == "integer")
      {
        vector<lwi> poly_coeff;
        for (lwi i = 0; i < deg; i++)
        {
          lwi pi;
          cin >> pi;
          poly_coeff.push_back(pi);
        }
        PolyDiff<lwi> p1(poly_coeff);
        p1.polynomial_diff();
        vector<lwi> coefficients = p1.get_elements();
        if (deg > 1)
        {
          for (auto &i : coefficients)
          {
            cout << i << " ";
          }
          cout << endl;
        }
        else
        {
          cout << 0 << endl;
        }
      }
      else
      {
        vector<ldi> poly_coeff;
        for (lwi i = 0; i < deg; i++)
        {
          ldi pi;
          cin >> pi;
          poly_coeff.push_back(pi);
        }
        PolyDiff<ldi> p1(poly_coeff);
        p1.polynomial_diff();
        vector<ldi> coefficients = p1.get_elements();
        for (auto &i : coefficients)
        {
          cout << fixed << setprecision(6) << i << " ";
        }
        cout << endl;
      }
    }
  }
}
