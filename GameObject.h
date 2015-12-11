/* EC327 Programming Assignment 3. Class definition for GameObject
   Luis Barroso Luque                                              November 2014   */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "CartPoint.h"

class Model;

class GameObject
{

 public:

  //Constructors
  GameObject();
  GameObject(char in_code, int in_id); //initializes with given display_code, id_num,
                                       // and location to (0,0)
  GameObject(char in_code, int in_id, const CartPoint& in_loc); //initializes with given 
                                       //display_code, id_num and location

  virtual ~GameObject(); //Destroy this thing!
  
  //Member functions
  CartPoint get_location() const; //Returns location for object
  int get_id() const; //returns id_num for object
  virtual void show_status(); //Outputs information display_code, id_num, location
  virtual bool update() = 0; //A class more abstract than any Kandinsky 
  void drawself(char* grid); //Like drawing a picture of yourself. No looking into a mirror though
  char get_state(); //pretty obvious
  char get_display_code();
  virtual bool is_alive();
  virtual void save(ofstream& file) = 0;
  virtual void restore(ifstream& file, Model* model) = 0;

 protected:

  int id_num;
  CartPoint location;
  char display_code;
  char state;

};

#endif
