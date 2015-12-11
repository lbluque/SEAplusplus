/* EC 327 PA3. Definition of class CartPoint used for the Sea++ game. The class
   represents a 2D cartesian coordinate given as its abscissa first and its ordinate
   second.
   Luis Barroso Luque                                               October 2014 */

#ifndef CARTPOINT_H
#define CARTPOINT_H

#include <iostream>
#include <math.h>
#include "CartVector.h"

using namespace std;

//Class definition
class CartPoint
{
 public:

  double x; //abscissa of location
  double y; //ordinate of location

  CartPoint();
  CartPoint(double in_x, double in_y);
};

//Nonmember functions
double cart_distance(const CartPoint& p1, const CartPoint& p2);

//Overloaded Operators
ostream& operator<<(ostream& out, const CartPoint& point);

istream& operator>>(istream& in, CartPoint& point);

CartPoint operator+(const CartPoint& point, const CartVector& vector);

CartVector operator-(const CartPoint& p1, const CartPoint& p2);

#endif
