/* EC 327 PA3. Implementation of class CartVector used for the Sea++ game. 
   The class represents a 2D cartesian vector represented by its x-component
   followed by its y-component.
   Luis Barroso Luque                                            October 2014 */

#include <iostream>
#include "CartVector.h"

using namespace std;

//Default constructor
CartVector::CartVector()
{
  this->x = 0.0;
  this->y = 0.0;
}

//Constructors
CartVector::CartVector(double in_x, double in_y)
{
  this->x = in_x;
  this->y = in_y;
}

//Overloaded Operators
ostream& operator<<(ostream& out, const CartVector& v1)
{
  out << "<" << v1.x << ", " << v1.y << ">";
}

istream& operator>>(istream& in, CartVector& vect)
{
  char par1, com, par2;
  in >> par1 >> vect.x >> com >> vect.y >> par2;
}

CartVector operator*(const CartVector& vector, double scalar)
{
  CartVector newVector(vector.x*scalar, vector.y*scalar);
  return newVector;
}

CartVector operator/(const CartVector& vector, double scalar)
{
  CartVector newVector(vector.x/scalar, vector.y/scalar);
  return newVector;
}
