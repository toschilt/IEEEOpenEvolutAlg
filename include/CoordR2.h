#ifndef COORDR2_H
#define COORDR2_H

#include <iostream>

using namespace std;

class CoordR2
{
    private:

    public:
        //Coordenada x
        double x;
        //Coordenada y
        double y;
        //Metódos construtores
        CoordR2();

        CoordR2(int val);

        CoordR2(int x, int y);

        //Sobrecrevendo operações nativas 
        friend ostream& operator<<(ostream& output, const CoordR2& p);

        CoordR2& operator+(const CoordR2 &p);

        CoordR2& operator+(const double c);

        CoordR2& operator-(const CoordR2 &p);

        CoordR2& operator-(const double c);

        CoordR2& operator*(const double c);

        CoordR2& operator/(const double c);

        friend bool operator==(const CoordR2 p1, const CoordR2 p2);
};


#endif