#include <iostream>

using namespace std;

template <typename T>
struct Point2D{
    T x;
    T y;

    Point2D(){

    }

    Point2D(T x, T y): x(x), y(y){

    }
};

template <typename T>
T det(Point2D<T> p, Point2D<T> q, Point2D<T> r){
    return p.x*(q.y-r.y) - q.x*(p.y-r.y) + r.x*(p.y-q.y);
}

template <typename T>
bool include(Point2D<T> p, Point2D<T> q, Point2D<T> r){
    return det(p,q,r) == 0 && min(p.x,q.x) <= r.x && min(p.y,q.y) <= r.y
           && max(p.x,q.x) >= r.x && max(p.y,q.y) >= r.y;
}

template <class T>
bool cross(const Point2D<T> p, const Point2D<T> q, const Point2D<T> r, const Point2D<T> s){
    bool koniec_na_odcinku = include(p,q,r) == 1 || include(p,q,s) == 1 || include(r,s,q) == 1 || include(r,s,p) == 1;
    bool przekraczaja_sie = ((det(p,q,r) > 0 && det(p,q,s) < 0) || (det(p,q,r) < 0 && det(p,q,s) > 0))
                          && ((det(r,s,p) > 0 && det(r,s,q) < 0) || (det(r,s,p) < 0 && det(r,s,q) > 0));
    cout << koniec_na_odcinku << przekraczaja_sie << endl;
    return koniec_na_odcinku || przekraczaja_sie;
}

int main() {

    Point2D<int> p(1,0);
    Point2D<int> q(1,1);
    Point2D<int> r(0,0);
    Point2D<int> s(2,0);
    cout << cross(p,q,r,s) << endl;
    return 0;
}