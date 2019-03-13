#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <graphics.h>
#include <conio.h>

using namespace std;

struct POINT
{
    float x, y;
};

///distance between 2 points
float distance(POINT a, POINT b)
{
    float dist = (a.x - b.x)*(a.x - b.x)+(a.y-b.y)*(a.y-b.y);

    return sqrt(dist);
}

bool verifySegment(POINT a, POINT b, POINT c) ///collinearity
{
    float distAB = distance(a, b);
    float distAC = distance(a, c);
    float distCB = distance(b, c);

    if ( ( distAC + distCB ) == distAB ) /// A,B,C collinear
        return true;

    return false;
}

int orientation(POINT a, POINT b, POINT c)
{
    float det = a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - b.x*a.y - c.x*b.y;

    if ( det == 0 ) ///all 3 points are on the same line
        return 1;

    if ( det > 0 ) ///c is left of ab(vector)
        return 2;

    return 3; ///c is right of ab(vector)
}

int triangulation(POINT a, POINT b, POINT c, POINT d)
{
    ///verify if POINT d is inside triangle abc
    ///POINT d is inside the triangle if its orientation towards every segment is the same
    int x,y,z;

    x = orientation(a,b,d);
    y = orientation(b,c,d);
    z = orientation(c,a,d);

    if ( x == y && y == z ) ///inside the triangle
        return 1;

    else if ( x == 1 ) ///on AB
        if ( verifySegment(a,b,d) == true ) return 1;

    else if ( y == 1 )
        {
            if ( verifySegment(b,c,d) == true )
                return 2;
        } ///on BC

        if ( verifySegment(b,c,d) == true )
        {
            return 2;
        }

    else if ( z == 1 ) ///on AC

        if ( verifySegment(c,a,d) == true ) return 1;

    return 0;///not inside of the triangle
}

int main()
{
    ifstream fin("date.in");
    int n, i, j;
    fin >> n;
    if ( n < 3 )
        cout << "The inserted points do not form a convex polygon";
    else
    {
        POINT P;
        POINT *v;

        v = new POINT[n+1];

        for ( i = 0; i <= n; i++ )
            fin >> v[i].x >> v[i].y;

        fin >> P.x >> P.y;

        int insideTriangle = 0;
        char point1, point2;

        for( i = 1; i < n-1 && !insideTriangle; i++ )
        {
            j = triangulation(v[0], v[i], v[i+1], P);
            if ( j == 1 )
                insideTriangle = 1;
            else if ( j == 2 )
                insideTriangle = 2;
        }

        if ( insideTriangle )
        {
            point1 = 'A'+i-1;
            point2 = 'A'+i;
        }

        if ( verifySegment(v[0], v[1], P) == true )
        {
            insideTriangle = 2;
            point1 = 'A';
            point2 = 'B';
        }

        if ( verifySegment(v[0],v[n-1], P) == true )
        {
            insideTriangle = 2;
            point1 = 'A';
            point2 = 'A'+(n-1);
        }

        if ( insideTriangle == 0 )
            cout << "The point is NOT inside the polygon!\n";
        else
            if ( insideTriangle == 1 )
                cout << "The point is inside the polygon and inside the triangle formed by A, " << point1 << ", " << point2 << "\n";
        else
            cout << "The point is on the edge of the polygon formed by: " << point1 << ", " << point2 << "\n";

        //---------------Reprezentare grafica ----------------------

        int gd = DETECT, gm;
        initgraph(&gd, &gm, "C:\\TC\\BGI");


    ///Reper XoY
      /*  line (0, getmaxy()/2, getmaxx(), getmaxy()/2);
        line (getmaxx()/2, 0, getmaxx()/2, getmaxy());

        outtextxy (getmaxx()/2 + 5, 0, "y");
        outtextxy (getmaxx() - 15, getmaxy()/2 - 18, "x");*/

        putpixel(P.x, P.y, WHITE);
        putpixel(P.x+1, P.y+1, WHITE);
        putpixel(P.x-1, P.y-1, WHITE);
        putpixel(P.x-1, P.y+1, WHITE);
        putpixel(P.x+1, P.y-1, WHITE);
        putpixel(P.x+1, P.y, WHITE);
        putpixel(P.x, P.y+1, WHITE);
        putpixel(P.x-1, P.y, WHITE);
        putpixel(P.x, P.y-1, WHITE);

        outtextxy(P.x - 10, P.y - 10, "P");

        int vectDim = 0;
        int points[(n+1)*2+1];

        for ( int i = 0; i <= n; i++ )
        {
            points[vectDim++] = v[i].x;
            points[vectDim++] = v[i].y;
        }

        drawpoly(n+1, points);

        setlinestyle(2, 0, 1);

        for ( int i = 2; i < n-1; i++ )
                line(v[0].x, v[0].y, v[i].x, v[i].y);

        for ( int i = 0; i < n; i++ )
        {
            if ( i == 0 )
                outtextxy(v[i].x - 10, v[i].y - 10, "A");

            if ( i == 1 )
                outtextxy(v[i].x - 10, v[i].y - 10, "B");

            if ( i == 2 )
                outtextxy(v[i].x - 10, v[i].y - 10, "C");

            if ( i == 3 )
                outtextxy(v[i].x - 10, v[i].y - 10, "D");

            if ( i == 4 )
                outtextxy(v[i].x - 10, v[i].y - 10, "E");

            if ( i == 5 )
                outtextxy(v[i].x - 10, v[i].y - 10, "F");

            if ( i == 6 )
                outtextxy(v[i].x - 10, v[i].y - 10, "G");

            if ( i == 7 )
                outtextxy(v[i].x - 10, v[i].y - 10, "H");

            if ( i == 8 )
                outtextxy(v[i].x - 10, v[i].y - 10, "I");

            if ( i == 9 )
                outtextxy(v[i].x - 10, v[i].y - 10, "J");

            if ( i == 10 )
                outtextxy(v[i].x - 10, v[i].y - 10, "K");

            if ( i == 11 )
                outtextxy(v[i].x - 10, v[i].y - 10, "L");

            if ( i == 12 )
                outtextxy(v[i].x - 10, v[i].y - 10, "M");

            if ( i == 13 )
                outtextxy(v[i].x - 10, v[i].y - 10, "N");

            if ( i == 14 )
                outtextxy(v[i].x - 10, v[i].y - 10, "O");

            if ( i == 15 )
                outtextxy(v[i].x - 10, v[i].y - 10, "P");

            if ( i == 16 )
                outtextxy(v[i].x - 10, v[i].y - 10, "Q");

            if ( i == 17 )
                outtextxy(v[i].x - 10, v[i].y - 10, "R");

            if  ( i == 18 )
                outtextxy(v[i].x - 10, v[i].y - 10, "S");

            if  ( i == 19 )
                outtextxy(v[i].x - 10, v[i].y - 10, "T");

            if ( i == 20 )
                outtextxy(v[i].x - 10, v[i].y - 10, "U");

            if ( i == 21 )
                outtextxy(v[i].x - 10, v[i].y - 10, "V");

            if ( i == 22 )
                outtextxy(v[i].x - 10, v[i].y - 10, "W");

            if ( i == 23 )
                outtextxy(v[i].x - 10, v[i].y - 10, "X");

            if ( i == 24 )
                outtextxy(v[i].x - 10, v[i].y - 10, "Y");

            if ( i == 25 )
                outtextxy(v[i].x - 10, v[i].y - 10, "Z");
        }

        getch();
        closegraph();
    }


    return 0;
}
