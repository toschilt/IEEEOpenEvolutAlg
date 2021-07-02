#include "CoordR2.h"
#include <iostream>

using namespace std;

//Metódos construtores

CoordR2::CoordR2(){
    this->x = -1;
    this->y = -1;
}

CoordR2::CoordR2(int val){
    this->x = val;
    this->y = val;
}

CoordR2::CoordR2(int x, int y){
    this->x = x;
    this->y = y;
}

ostream& operator<<(ostream& output, const CoordR2& p){
    output << "( " << p.x << ", " << p.y << ")";
    return output;
}

CoordR2& CoordR2:: operator+(const CoordR2 &p){
    CoordR2 *res;
    res->x = this->x + p.x;
    res->y = this->y + p.y;
    return *res;
}


CoordR2& CoordR2:: operator+(const double c){
    CoordR2 *res;
    res->x = this->x + c;
    res->y = this->y + c;
    return *res;
}

CoordR2& CoordR2:: operator-(const CoordR2 &p){
    CoordR2 *res;
    res->x = this->x - p.x;
    res->y = this->y - p.y;
    return *res;
}

CoordR2& CoordR2:: operator-(const double c){
    CoordR2 *res;
    res->x = this->x - c;
    res->y = this->y - c;
    return *res;
}

CoordR2& CoordR2:: operator*(const double c){
    CoordR2 *res;
    res->x = this->x * c;
    res->y = this->y * c;
    return *res;
}

CoordR2& CoordR2:: operator/(const double c){
    CoordR2 *res;
    res->x = this->x / c;
    res->y = this->y / c;
    return *res;
}

bool operator==(const CoordR2 p1, const CoordR2 p2)
{
    return( p1.x == p2.x && p1.y == p2.y);
}