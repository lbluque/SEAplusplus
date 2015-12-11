/* EC327 Programming Assignment 3. Class definition for Fish                  
   Luis Barroso Luque                                              November 2014   */

#ifndef FISH_H
#define FISH_H

#include "GameObject.h"
#include "CartPoint.h"
#include "CoralReef.h"
#include "Cave.h"
#include <math.h>

class Model;
class Cave;

class Fish: public GameObject
{
 public:
  //Constructors
  Fish(char in_code, int in_size);
  Fish(char in_code, int in_size, int in_id, Cave* home, Model* world);
  Fish(char in_code, int in_size, int in_id, CartPoint birthplace, Model* world);
  //Destrooooyyy
  ~Fish();

  //Member functions
  virtual bool update(); //Updates the fish, returns true if state changed, false ifnot
  virtual void show_status(); //Tells us how the fish is doing
  double get_size() const; //How fat is that fish?
  void start_swimming(const CartPoint& dest); //Backstroke backstroke 
  virtual void start_eating(CoralReef* destReef); //Begin the feast here!
  bool is_hidden() const; //Is the fish around?
  virtual void start_hiding(Cave* destCave); //Fish hides in specified cave
  void float_in_place(); //The fish start chillin (stops everythin else)
  virtual double get_speed() = 0; 
  void get_bitten(int attack_strength);
  virtual void start_attack(Fish* fishToGet); //Tries to get someone!
  virtual bool start_mating(Fish* datFishDoe); //Beast with two backs
  Cave* get_home();
  bool is_alive();
  virtual void save(ofstream& file) = 0;
  virtual void restore(ifstream& file, Model* world) = 0;
  bool is_dead_in_cave();
 
 protected:

  //Class data
  double energy; //Health of fish
  double size; //How fat the fish is
  double prefeast_size; //How fat the fish is before getting fatter
  CartPoint destination; //Coordinates where fish is headed
  CartVector delta; //x & y amounts fish will move in each time unit
  CoralReef* reef; //pointer to where fish will eat
  Cave* home; //Home sweet home

  //Private member functions
  bool update_location(); //Updates location of fish when swimming, also 
                          //prints some awesome lines
  void setup_destination(const CartPoint& dest); //Sets up where fish will go
  Model* world; //The world in which the fishy lives
};

#endif