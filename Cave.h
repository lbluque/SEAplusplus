/* EC327 Programming Assignment 3. Class definition for Cave                  
   Luis Barroso Luque                                              November 2014   */

#ifndef CAVE_H
#define CAVE_H

#include <fstream>
#include "GameObject.h"
#include "CartPoint.h"
#include "Fish.h"

class Fish;
class Model;

class Cave: public GameObject
{
 public:
  //Constructors
  Cave();
  Cave(int in_id, const CartPoint& in_loc);
  ~Cave();

  //Member functions
  bool hide_fish(Fish* fish_to_hide); //Attempts to hide fish if there's space
                                      //and updates the available space in cave
  bool release_fish(Fish* fish_to_release); //Releases a fish if hidded and
                                      //and updates space in cave
  bool update(); //Updates the caves state based on the space it has
  void show_status(); //Shows whats going on in the cave
  double get_space() const; //How much room is there for activities?
  void save(ofstream& file);
  void restore(ifstream& file, Model* model);
 
 private:

  //Class data
  double space; //Space available for the fishies and what not

};

#endif
