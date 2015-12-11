/* EC327 Programming Assignment 3. Class definition for View object                  
   Luis Barroso Luque                                              November 2014   */

#ifndef VIEW_H
#define VIEW_H

#include "CartPoint.h"
#include "GameObject.h"

const int view_maxsize=50;

class View
{

 private:
  //Some exclusive members here
  int size; //current size of grid to be displayed
  double scale; //distance in each cell of grid
  CartPoint origin; //location of lower-lefthand corner of grid
  char grid[view_maxsize][view_maxsize][2];//holds the stuff on the grid
  
  //Some private functionality
  bool get_subscripts(int &ix, int &iy, CartPoint location); //gets some stuff 
  //regarding the subscripts of points on the grid. Some very fancy stuff
  
 public:
  View(); //Let there be light
  void clear(); //Trying to match the sample output here
  void plot(GameObject* ptr); //put stuff on the grid
  void draw(); //draws eeerrything

};

#endif
