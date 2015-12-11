/* EC327 Programming Assignment 3. Class definition for Shark                 
   Luis Barroso Luque                                         November 2014   */

#ifndef SHARK_H
#define SHARK_H

#include <stdlib.h>
#include "Fish.h"
#include "Model.h"
#include "CartPoint.h"

class Model;
class CoralReef;

class Shark: public Fish
{
 public:
  //Constructors
  Shark();
  Shark(int in_id);
  Shark(int in_id, Model* world);

  //Some awesome methods
  double get_speed(); //speed is (1/size)*energy*8
  void start_attack(Fish* target);
  bool update();
  void show_status();
  void start_hiding(Cave* destCave);
  void start_eating(CoralReef* destReef);
  void save(ofstream& file);
  void restore(ifstream& file, Model* world);

  
  private:

 int attack_strength;
 double range; //Attack range
 Fish* target; //Who to attack

};

#endif