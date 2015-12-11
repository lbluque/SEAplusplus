/* EC 327 PA3. Definition of class CartVector used for the Sea++ game. The class
   represents a 2D cartesian vector represented by its x-component followed by its
   y-component.
   Luis Barroso Luque                                               October 2014 */

#ifndef CARTVECTOR_H
#define CARTVECTOR_H

#include <iostream>

using namespace std;

//Class definition
class CartVector
{
 public:
  double x;
  double y;

  CartVector();
  CartVector(double in_x, double in_y);
};

//Overloaded Operators
ostream& operator<<(ostream& out, const CartVector& v1);

istream& operator>>(istream& in, CartVector& vect);

CartVector operator*(const CartVector& vector, double scalar);

CartVector operator/(const CartVector& vector, double scalar);

#endif
