#include <bits/stdc++.h>
using namespace std;
typedef long long int lwi;
lwi p = 1e9 + 7;
lwi max_length_primecheck = 1e6;
void fibonnaci_no(lwi n, vector<lwi> &reqtwovaluesfordoubling)
{
    if (n == 0)
    {
        reqtwovaluesfordoubling[0] = 0;
        reqtwovaluesfordoubling[1] = 1;
        return;
    }
    fibonnaci_no(n / 2, reqtwovaluesfordoubling);
    lwi fn = reqtwovaluesfordoubling[0], fnp1 = reqtwovaluesfordoubling[1];
    lwi f2n = (2 * fnp1 - fn);
    if (f2n < 0)
    {
        f2n += p;
    } // calculating fibonacci by using fast doubling algo which works in logarithmic time
    f2n = ((fn % p) * f2n) % p;
    lwi f2np1 = ((fn * fn) % p + (fnp1 * fnp1) % p) % p;
    if (n % 2)
    {
        reqtwovaluesfordoubling[0] = f2np1;
        reqtwovaluesfordoubling[1] = f2n + f2np1;
    }
    else
    {
        reqtwovaluesfordoubling[0] = f2n;
        reqtwovaluesfordoubling[1] = f2np1;
    }
}
class Sieveoferas
{
public:
    vector<bool> isprime;
    Sieveoferas()
    {
        isprime.resize(max_length_primecheck + 1, true);
    }
    void Arrange_primes()
    {
        for (lwi i = 2; i * i <= max_length_primecheck; i++)
        {
            if (isprime[i])
            {
                for (lwi j = i * i; j <= max_length_primecheck; j += i)
                {
                    isprime[j] = false;
                }
            }
        }
        isprime[0] = false;
        isprime[1] = false;
    }
    friend class PrimeCalculator;
};
class CurrencySorter
{
public:
    void operator()(vector<lwi> &v, lwi L, lwi R)
    {
        // functor for quick sort in which which write another quicksort function
        if (L >= R)
        {
            return;
        }
        lwi len_v = R - L;
        vector<lwi> v_L_R(v.begin() + L, v.begin() + R);
        lwi pivot = momselect(v_L_R, ceil(len_v / 2.0)-1);
        // lwi pivot=v[L];
        vector<lwi> temp(v.begin(), v.end());
        lwi j = L;
        for (lwi i = L; i < R; i++)
        {
            if (temp[i] < pivot)
            {
                v[j] = temp[i];
                j++;
            }
        }
        lwi r = j;
        for (lwi i = L; i < R; i++)
        {
            if (temp[i] == pivot)
            {
                v[j] = temp[i];
                j++;
            }
        }
        for (lwi i = L; i < R; i++)
        {
            if (temp[i] > pivot)
            {
                v[j] = temp[i];
                j++;
            }
        }
        (*this)(v, L, r);
        (*this)(v, r + 1, R);
    }
    lwi momselect(vector<lwi> v, lwi k)
    {
        lwi len_v = v.size();
        if (len_v <= 25)
        {
            sort(v.begin(), v.end());
            return v[k];
        }
        else
        {
            vector<lwi> medianarray;
            lwi m = ceil(len_v / 5.0);
            for (lwi i = 0; i < len_v / 5; i++)
            {
                vector<lwi> median_five;
                for (lwi j = 0; j < 5; j++)
                {
                    median_five.push_back(v[5 * i + j]);
                }
                sort(median_five.begin(), median_five.end());
                medianarray.push_back(median_five[2]);
            }
            // vector<lwi> median_five;
            // for (lwi i = 5 * (len_v / 5); i < len_v; i++)
            // {
            //     median_five.push_back(v[i]);
            // }
            // lwi len_mfive = median_five.size();
            // sort(median_five.begin(), median_five.end());
            // medianarray.push_back(median_five[(len_mfive-1) / 2]);
            lwi mom = momselect(medianarray, ceil(m/2.0));
            vector<lwi> subarr1, subarr2;
            lwi r = 0,no_mom=0;
            for (lwi i = 0; i < len_v; i++)
            {
                if (v[i] < mom)
                {
                    subarr1.push_back(v[i]);
                    r++;
                }
                else if(v[i]>mom)
                {
                    subarr2.push_back(v[i]);
                }else{
                    no_mom++;
                }
            }
            if (k <= r)
            {
                return momselect(subarr1, k);
            }
            else if (k >r+no_mom)
            {
                return momselect(subarr2, k - r-no_mom);
            }
            else
            {
                return mom;
            }
        }
        return 0;
    }
};
class FibonacciGenerator
{
public:
    void operator()(lwi i, vector<lwi> &reqtwovaluesfordoubling)
    {
        fibonnaci_no(i, reqtwovaluesfordoubling); // modifying the array with fibbonaci numbers taking fn and fn+1 in a 2sizearray
        cout << reqtwovaluesfordoubling[0] << endl;
    }
};
class PrimeCalculator
{
public:
    void printPrimes(lwi L, lwi R, vector<bool> &pv)
    {
        // function for printing primes from L to R

        for (lwi i = 0; i <= R - L; i++)
        {
            if (pv[i])
            {
                cout << i + L << " ";
            }
        }
        cout << endl;
    }
    void printPrimeSum(lwi L, lwi R, vector<bool> &pv)
    {
        // function for printing the sum of the primes from L to R

        lwi sum = 0;
        for (lwi i = 0; i <= R - L; i++)
        {
            if (pv[i])
            {
                sum += (i + L);
            }
        }
        cout << sum << endl;
    }
};
class NumberAnalyzer
{
public:
    bool isSquareFree(lwi n)
    {
        // checking a number whether it is squarefree or not
        bool issquarefree = true;
        for (lwi i = 2; i * i <= n; i++)
        {
            if (n % (i * i) == 0)
            {
                issquarefree = false;
            }
        }
        return issquarefree;
    }
    lwi countDivisors(lwi n)
    {
        // function to count no of divisors
        lwi no_of_divisors = 1;
        for (lwi i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                lwi p1 = 0;
                while (n % i == 0)
                {
                    p1++;
                    n = n / i;
                }
                no_of_divisors *= (p1 + 1);
            }
        }
        if (n > 1)
        {
            return no_of_divisors * 2;
        }
        return no_of_divisors;
    }
    lwi sumOfDivisors(lwi n)
    {
        // function for taking sum of all divisors of n
        lwi sum_div = 1 + n;
        lwi i;
        for (i = 2; i * i < n; i++)
        {
            if (n % i == 0)
            {
                sum_div = sum_div + i + (n / i);
            }
        }
        if (i * i == n)
        {
            sum_div += i;
        }
        return sum_div;
    }
};
int main()
{
    lwi operator_no;
    cin >> operator_no;
    if (operator_no == 1)
    {
        lwi t;
        cin >> t;
        while (t--)
        {
            lwi arr_len;
            cin >> arr_len;
            vector<lwi> arr;
            for (lwi i = 0; i < arr_len; i++)
            {
                lwi temp_num;
                cin >> temp_num;
                arr.push_back(temp_num);
            }
            CurrencySorter cur_sorter;
            cur_sorter(arr, 0, arr_len);
            for (auto &i : arr)
            {
                cout << i << " ";
            }
            cout << endl;
        }
    }
    else if (operator_no == 2)
    {
        lwi t;
        cin >> t;
        while (t--)
        {
            lwi i;
            cin >> i;
            vector<lwi> twovalueslist = {0, 0};
            FibonacciGenerator f;
            f(i, twovalueslist);
        }
    }
    else if (operator_no == 3)
    {
        lwi t;
        cin >> t;
        Sieveoferas sea;
        sea.Arrange_primes();
        vector<bool> smallprime_array(sea.isprime.begin(), sea.isprime.end());
        while (t--)
        {
            string s;
            cin >> s;
            lwi L, R;
            cin >> L >> R;
            vector<bool> actual_prime_calculating_array(R - L + 1, true);
            for (lwi i = 2; i * i <= R; i++)
            {
                if (smallprime_array[i])
                {
                    lwi start = max(i * i, L + (i - L % i) % i);
                    for (lwi j = start; j <= R; j += i)
                    {
                        actual_prime_calculating_array[j - L] = false;
                    }
                }
            }
            if (L == 1)
            {
                actual_prime_calculating_array[0] = false;
            }
            if (L == 0)
            {
                actual_prime_calculating_array[0] = false;
                if (L + 1 <= R)
                {
                    actual_prime_calculating_array[1] = false;
                }
            }
            if (s == "printPrimes")
            {
                PrimeCalculator p;
                p.printPrimes(L, R, actual_prime_calculating_array);
            }
            else
            {
                PrimeCalculator p;
                p.printPrimeSum(L, R, actual_prime_calculating_array);
            }
        }
    }
    else
    {
        lwi t;
        cin >> t;
        while (t--)
        {
            string s;
            cin >> s;
            lwi X;
            cin >> X;
            if (s == "isSquareFree")
            {
                NumberAnalyzer na;
                bool check = na.isSquareFree(X);
                if (check)
                {
                    cout << "yes" << endl;
                }
                else
                {
                    cout << "no" << endl;
                }
            }
            else if (s == "countDivisors")
            {
                NumberAnalyzer na;
                cout << na.countDivisors(X) << endl;
            }
            else
            {
                NumberAnalyzer na;
                cout << na.sumOfDivisors(X) << endl;
            }
        }
    }
}
