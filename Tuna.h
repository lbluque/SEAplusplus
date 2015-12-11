/* EC327 Programming Assignment 3. Class definition for Tuna                 
   Luis Barroso Luque                                         November 2014   */

#ifndef TUNA_H
#define TUNA_H

#include "Fish.h"
#include "Model.h"

class Cave;
class Model;
class CartPoint;

class Tuna: public Fish
{
 public:
  //Constructors
  Tuna();
  Tuna(int in_id);
  Tuna(int in_id, Cave* home, Model* world);

  //Some awesome methods
  double get_speed();
  bool start_mating(Tuna* datTuna);
  bool update();
  void show_status();
  void sexy_time(); //Changes the state to 'm' for mating or better said 'sexy time'
  bool are_you_hitting_on_me();
  void set_mateTime();
  void save(ofstream& file);
  void restore(ifstream& file, Model* world);

  private:

  int mateTime;
  bool initiator;

};

#endif
