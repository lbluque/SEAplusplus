/* EC327 Programming Assignment 3. Class definition for CoralReef                  
   Luis Barroso Luque                                              November 2014   */

#ifndef CORALREEF_H
#define CORALREEF_H

#include <fstream>
#include "GameObject.h"
#include "CartPoint.h"

class Model;

class CoralReef: public GameObject
{
 public:

  //Member functions
  bool is_empty() const;
  double provide_food(double amount_to_provide = 20);
  bool update();
  void show_status();
  void save(ofstream& file);
  void restore(ifstream& file, Model* model);

  //Constructors
  CoralReef();
  CoralReef(int in_id, const CartPoint& in_loc);
  ~CoralReef();

 private:

  //Class data
  double amount;

};

#endif
