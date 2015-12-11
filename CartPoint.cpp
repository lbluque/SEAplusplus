/* EC 327 PA3. Implementation of class CartPoint used for the Sea++ game.
   The class represents a 2D cartesian coordinate given as its abscissa first
   and its ordinate second. Member functions are defined in Cartpoint.cpp 
   Luis Barroso Luque                                           October 2014 */

#include "CartPoint.h"

//Default constructor
CartPoint::CartPoint()
{
  x = 0.0;
  y = 0.0;
}

//Constructors
CartPoint::CartPoint(double in_x, double in_y)
{
  x = in_x;
  y = in_y;
}

//Nonmember functions
double cart_distance(const CartPoint& p1, const CartPoint& p2)
{
  double distance;
  distance = (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
  distance = sqrt(distance);
  return distance;
}

//Overloaded Operators
ostream& operator<<(ostream& out, const CartPoint& point)
{
  out << "(" << point.x << ", " << point.y << ")";
}

istream& operator>>(istream& in, CartPoint& point)
{
  char par1, com, par2;
  in >> par1 >> point.x >> com >> point.y >> par2;
}

CartPoint operator+(const CartPoint& point, const CartVector& vector)
{
  CartPoint newPoint(point.x + vector.x, point.y + vector.y);
  return newPoint;
}

CartVector operator-(const CartPoint& p1, const CartPoint& p2)
{
  CartVector newVector(p1.x - p2.x, p1.y - p2.y);
   return newVector;
}
