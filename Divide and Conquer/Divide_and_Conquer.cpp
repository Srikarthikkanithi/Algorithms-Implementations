#include <bits/stdc++.h>
using namespace std;
typedef long long int lwi;
// comparator class for sorting every row of the chessboard quantum states which is used as a functor
class Comparator
{
private:
    bool ascending; // declaring a boolean variable to check whether to sort in ascending or descending
public:
    Comparator(bool b1)
    {
        ascending = b1;
    }
    void operator()(vector<lwi> &mat1, lwi L, lwi R)
    {
        if (ascending)
        {
            if (R - L == 2)
            {
                if (mat1[L] > mat1[L + 1])
                {
                    swap(mat1[L], mat1[L + 1]);
                }
                return;
            }
            if (R - L < 2)
            {
                return;
            }
            lwi m = (L + R) / 2;
            (*this)(mat1, L, m);
            (*this)(mat1, m, R);
            vector<lwi> temp(mat1.begin() + L, mat1.begin() + R);
            lwi k = L, i = 0, j = m - L;
            while (i < m - L && j < R - L)
            {
                if (temp[i] > temp[j])
                {
                    mat1[k] = temp[j];
                    j++;
                    k++;
                }
                else
                {
                    mat1[k] = temp[i];
                    i++;
                    k++;
                }
            }

            while (i < m - L)
            {
                mat1[k] = temp[i];
                k++;
                i++;
            }
            while (j < R - L)
            {
                mat1[k] = temp[j];
                k++;
                j++;
            }
        }
        else
        {
            if (R - L == 2)
            {
                if (mat1[L] < mat1[L + 1])
                {
                    swap(mat1[L], mat1[L + 1]);
                }
                return;
            }
            if (R - L < 2)
            {
                return;
            }
            lwi m = (L + R) / 2;
            (*this)(mat1, L, m);
            (*this)(mat1, m, R);
            vector<lwi> temp(mat1.begin() + L, mat1.begin() + R);
            lwi k = L, i = 0, j = m - L;
            while (i < m - L && j < R - L)
            {
                if (temp[i] < temp[j])
                {
                    mat1[k] = temp[j];
                    j++;
                    k++;
                }
                else
                {
                    mat1[k] = temp[i];
                    i++;
                    k++;
                }
            }

            while (i < m - L)
            {
                mat1[k] = temp[i];
                k++;
                i++;
            }
            while (j < R - L)
            {
                mat1[k] = temp[j];
                k++;
                j++;
            }
        }
    }
};
// chessboard class that contains the matrix of quantumstate values and size
class modern_Chessboard
{
private:
    vector<vector<lwi>> matrix;
    lwi size;

public:
    modern_Chessboard() = default;
    modern_Chessboard(vector<vector<lwi>> &mat1)
    {
        matrix = mat1;
        size = mat1.size();
    }
    // counting inversions of a matrix
    lwi countInversions()
    {
        vector<lwi> mat_1d;
        for (auto &i : matrix)
        {
            for (auto &j : i)
            {
                mat_1d.push_back(j);
            }
        }
        lwi p = mat_1d.size();
        return dac_countInversions(mat_1d, 0, p);
    }
    lwi dac_countInversions(vector<lwi> &vec, lwi L, lwi R)
    {
        if (R - L == 2)
        {
            if (vec[L] > vec[L + 1])
            {
                swap(vec[L], vec[L + 1]);
                return 1;
            }
            return 0;
        }
        if (R - L < 2)
        {
            return 0;
        }
        lwi m = (L + R) / 2;
        lwi no_inv1 = dac_countInversions(vec, L, m), no_inv2 = dac_countInversions(vec, m, R), no_inv3 = 0;
        lwi i = 0, j = m - L;
        vector<lwi> temp(vec.begin() + L, vec.begin() + R);
        lwi k = L;
        while (i < m - L && j < R - L)
        {
            if (temp[i] > temp[j])
            {
                no_inv3 += (m - i - L);
                vec[k] = temp[j];
                k++;
                j++;
            }
            else
            {
                vec[k] = temp[i];
                k++;
                i++;
            }
        }
        while (i < m - L)
        {
            vec[k] = temp[i];
            k++;
            i++;
        }
        while (j < R - L)
        {
            vec[k] = temp[j];
            k++;
            j++;
        }
        return no_inv1 + no_inv2 + no_inv3;
    }
    // printing thye matrix
    void display()
    {
        for (auto &i : matrix)
        {
            for (auto &j : i)
            {
                cout << j << " ";
            }
            cout << endl;
        }
    }
    // sortRows func uses the comparator functor and the transform function
    void sortRows(Comparator &comparator)
    {
        for (lwi i = 0; i < size; i++)
        {
            comparator(matrix[i], 0, size); // usage of comparator functor
        }
    }
};
class xsorter;
class ysorter;
class Space_2d; // for the euclidian points distance calculation
// point2d class contains x,y coordinates this is declared to avoid passing a pair of pair of integers or returning the same
class Point_2d
{
private:
    lwi x, y, inp_ind;

public:
    Point_2d() = default;
    Point_2d(lwi x1, lwi y1, lwi ii1)
    {
        x = x1;
        y = y1;
        inp_ind = ii1;
    }
    lwi get_inp_ind()
    {
        return inp_ind;
    }
    lwi get_x()
    {
        return x;
    }
    lwi get_y()
    {
        return y;
    }
    void print()
    {
        cout << x << " " << y;
    }
    friend class Space_2d;
    friend class xsorter;
    friend class ysorter;
};
class xsorter
{
public:
    bool operator()(Point_2d &p1, Point_2d &p2)
    {
        return p1.x < p2.x;
    }
};
class ysorter
{
public:
    bool operator()(Point_2d &p1, Point_2d &p2)
    {
        return p1.y < p2.y;
    }
};
class Space_2d
{
private:
    vector<Point_2d> euclidian_points_set;
    lwi no_of_points;

public:
    vector<Point_2d> xcords;
    vector<Point_2d> ycords;
    Space_2d() = default;
    Space_2d(vector<Point_2d> eps1)
    {
        euclidian_points_set = eps1;
        no_of_points = eps1.size();
    }
    lwi distance(Point_2d p1, Point_2d p2)
    {
        lwi x1 = p1.x, x2 = p2.x, y1 = p1.y, y2 = p2.y;
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }
    void generate_xycoords()
    {
        xcords = euclidian_points_set;
        ycords = euclidian_points_set;
        sort(xcords.begin(), xcords.end(), xsorter());
        sort(ycords.begin(), ycords.end(), ysorter());
    }
    pair<Point_2d, Point_2d> closestpair(vector<Point_2d> px, vector<Point_2d> py)
    {
        // calculating the closest pair and returning the required points
        lwi len = px.size();
        if (len == 3)
        {
            Point_2d p1 = px[0], p2 = px[1];
            if (distance(px[0], px[2]) < distance(p1, p2))
            {
                p1 = px[0];
                p2 = px[2];
            }
            else if (distance(px[0], px[1]) == distance(p1, p2))
            {
                Point_2d p3, p4;
                if (px[0].get_inp_ind() < px[1].get_inp_ind())
                {
                    p3 = px[0];
                }
                else
                {
                    p3 = px[1];
                }
                if (p1.get_inp_ind() < p2.get_inp_ind())
                {
                    p4 = p1;
                }
                else
                {
                    p4 = p2;
                }
                if (p3.x < p4.x)
                {
                    p1 = px[0];
                    p2 = px[1];
                }
                else if (p3.x == p4.x)
                {
                    if (p3.y < p4.y)
                    {
                        p1 = px[0];
                        p2 = px[1];
                    }
                }
            }
            if (distance(px[1], px[2]) < distance(p1, p2))
            {
                p1 = px[1];
                p2 = px[2];
            }
            else if (distance(px[1], px[2]) == distance(p1, p2))
            {
                Point_2d p3, p4;
                if (px[1].get_inp_ind() < px[2].get_inp_ind())
                {
                    p3 = px[1];
                }
                else
                {
                    p3 = px[2];
                }
                if (p1.get_inp_ind() < p2.get_inp_ind())
                {
                    p4 = p1;
                }
                else
                {
                    p4 = p2;
                }
                if (p3.x < p4.x)
                {
                    p1 = px[1];
                    p2 = px[2];
                }
                else if (p3.x == p4.x)
                {
                    if (p3.y < p4.y)
                    {
                        p1 = px[1];
                        p2 = px[2];
                    }
                }
            }
            return {p1, p2};
        }
        else if (len == 2)
        {
            return {px[0], px[1]};
        }
        else
        {
            lwi mid = len / 2;
            vector<Point_2d> qx(px.begin(), px.begin() + mid);
            vector<Point_2d> rx(px.begin() + mid, px.end());
            lwi qx_len = qx.size(), maxqx = qx[qx_len - 1].x;
            vector<Point_2d> qy(qx.begin(), qx.end());
            vector<Point_2d> ry(rx.begin(), rx.end());
            //  for(lwi i=0;i<len;i++){
            //     if(py[i].x<=maxqx){
            //         qy.push_back(py[i]);
            //     }else{
            //         ry.push_back(py[i]);
            //     }
            //  }
            sort(qy.begin(), qy.end(), ysorter());
            sort(ry.begin(), ry.end(), ysorter());
            pair<Point_2d, Point_2d> p1 = closestpair(qx, qy);
            pair<Point_2d, Point_2d> p2 = closestpair(rx, ry);
            lwi d1 = distance(p1.first, p1.second), d2 = distance(p2.first, p2.second);
            lwi d = min(d1, d2);
            vector<Point_2d> sy;
            for (lwi i = 0; i < len; i++)
            {
                if ((py[i].x - maxqx) * (py[i].x - maxqx) < d)
                {
                    sy.push_back(py[i]);
                }
            }
            lwi len_sy = sy.size();
            if (len_sy >= 2)
            {
                Point_2d p3 = sy[0], p4 = sy[1];
                for (lwi i = 0; i < len_sy; i++)
                {
                    for (lwi j = i + 1; j < min(i + 16, len_sy); j++)
                    {
                        if (distance(sy[i], sy[j]) < distance(p3, p4))
                        {
                            p3 = sy[i];
                            p4 = sy[j];
                        }
                    }
                }
                lwi d3 = distance(p3, p4);
                if (d3 < d)
                {
                    return {p3, p4};
                }
                else if (d3 == d)
                {
                    if (d == d1)
                    {
                        Point_2d p5, p6, p7, p8;
                        if (p3.get_inp_ind() < p4.get_inp_ind())
                        {
                            p5 = p3;
                            p7 = p4;
                        }
                        else
                        {
                            p5 = p4;
                            p7 = p3;
                        }
                        if (p1.first.get_inp_ind() < p1.second.get_inp_ind())
                        {
                            p6 = p1.first;
                            p8 = p1.second;
                        }
                        else
                        {
                            p6 = p1.second;
                            p8 = p1.first;
                        }
                        if (p5.x < p6.x)
                        {
                            return {p3, p4};
                        }
                        else if (p5.x == p6.x)
                        {
                            if (p5.y < p6.y)
                            {
                                return {p3, p4};
                            }
                            else if (p5.y > p6.y)
                            {
                                return {p1.first, p1.second};
                            }
                            else
                            {
                                if (p7.x > p8.x)
                                {
                                    return {p1.first, p1.second};
                                }
                                else if (p7.x < p8.x)
                                {
                                    return {p3, p4};
                                }
                                else
                                {
                                    if (p7.y < p8.y)
                                    {
                                        return {p3, p4};
                                    }
                                    else if (p7.y > p8.y)
                                    {
                                        return {p1.first, p1.second};
                                    }
                                    else
                                    {
                                        if (p5.get_inp_ind() < p6.get_inp_ind())
                                        {
                                            return {p3, p4};
                                        }
                                        else
                                        {
                                            return {p1.first, p1.second};
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            return {p1.first, p1.second};
                        }
                    }
                    else
                    {
                        Point_2d p5, p6, p7, p8;
                        if (p3.get_inp_ind() < p4.get_inp_ind())
                        {
                            p5 = p3;
                            p7 = p4;
                        }
                        else
                        {
                            p5 = p4;
                            p7 = p3;
                        }
                        if (p2.first.get_inp_ind() < p2.second.get_inp_ind())
                        {
                            p6 = p2.first;
                            p8 = p1.second;
                        }
                        else
                        {
                            p6 = p2.second;
                            p8 = p2.first;
                        }
                        if (p5.x < p6.x)
                        {
                            return {p3, p4};
                        }
                        else if (p5.x == p6.x)
                        {
                            if (p5.y < p6.y)
                            {
                                return {p3, p4};
                            }
                            else if (p5.y > p6.y)
                            {
                                return {p2.first, p2.second};
                            }
                            else
                            {
                                if (p7.x > p8.x)
                                {
                                    return {p2.first, p2.second};
                                }
                                else if (p7.x < p8.x)
                                {
                                    return {p3, p4};
                                }
                                else
                                {
                                    if (p7.y < p8.y)
                                    {
                                        return {p3, p4};
                                    }
                                    else if (p7.y > p8.y)
                                    {
                                        return {p2.first, p2.second};
                                    }
                                    else
                                    {
                                        if (p5.get_inp_ind() < p6.get_inp_ind())
                                        {
                                            return {p3, p4};
                                        }
                                        else
                                        {
                                            return {p2.first, p2.second};
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            return {p2.first, p2.second};
                        }
                    }
                }
                else if (d1 <= d2)
                {
                    return {p1.first, p1.second};
                }
                else if (d1 > d2)
                {
                    return {p2.first, p2.second};
                }
            }
            if (d1 < d2)
            {
                return {p1.first, p1.second};
            }
            else
            {
                return {p2.first, p2.second};
            }
        }
    }
};
int main()
{
    modern_Chessboard board_n;
    while (true)
    {
        string s;
        cin >> s;
        if (s == "CREATE_2D")
        {
            lwi n;
            cin >> n;
            vector<vector<lwi>> mat1(n);
            for (lwi i = 0; i < n * n; i++)
            { // creating a matrix
                lwi qvi;
                cin >> qvi;
                mat1[i / n].push_back(qvi);
            }
            board_n = modern_Chessboard(mat1);
        }
        else if (s == "SORT_2D")
        {
            bool b1 = false;
            string s1;
            cin >> s1;
            if (s1 == "ascending")
            {
                b1 = true;
                Comparator c1(b1); // sorting using comparator functor
                board_n.sortRows(c1);
            }
            else
            {
                Comparator c1(b1);
                board_n.sortRows(c1);
            }
        }
        else if (s == "INVERSION_2D")
        {
            cout << board_n.countInversions() << endl; // counting the no of inversions
        }
        else if (s == "DISPLAY_2D")
        {
            board_n.display();
        }
        else if (s == "CLOSEST_2D")
        {
            lwi no_of_points;
            cin >> no_of_points;
            vector<Point_2d> euclidian_space_points;
            Space_2d s1;
            for (lwi i = 0; i < no_of_points; i++)
            {
                lwi x, y;
                cin >> x >> y;
                Point_2d pi(x, y, i); // calculating the closest pair of points
                euclidian_space_points.push_back(pi);
            }
            s1 = Space_2d(euclidian_space_points);
            s1.generate_xycoords();
            pair<Point_2d, Point_2d> p1 = s1.closestpair(s1.xcords, s1.ycords);
            if (p1.first.get_inp_ind() < p1.second.get_inp_ind())
            {
                p1.first.print();
                cout << " ";
                p1.second.print();
            }
            else
            {
                p1.second.print();
                cout << " ";
                p1.first.print();
            }
            cout << endl;
        }
        else if (s == "END")
        {
            break;
        }
    }
}
