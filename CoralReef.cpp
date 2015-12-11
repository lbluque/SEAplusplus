/* EC327 Programming Assignment 3. Class definition for CoralReef   
   Luis Barroso Luque                                       November 2014   */

#include <iostream>
#include "CoralReef.h"

//Constructors
CoralReef::CoralReef():GameObject('R',0)
{
  this->amount = 100;
  this->state = 'f';

  cout << "CoralReef default constructed" << endl;
  }

CoralReef::CoralReef(int in_id, const CartPoint& in_loc):GameObject('R', in_id, in_loc)
{
  this->amount = 100;
  this->state = 'f';  
  cout << "CoralReef constructed" << endl;
}

CoralReef::~CoralReef()
{
  cout << "CoralReef destructed" << endl;
}

//Public member functions
bool CoralReef::is_empty() const
{
  if (this->amount == 0)
    return true;
  else 
    return false;
}

double CoralReef::provide_food(double amount_to_provide)
{

  if (this->amount >= amount_to_provide)
    {
      this->amount -= amount_to_provide;
      return amount_to_provide;
    }
  else 
    {
      double leftOvers = this->amount;
      this->amount = 0;
      return leftOvers;
    }
}

bool CoralReef::update()
{
  if (CoralReef::is_empty() && this->state != 'e')
    {
      this->state = 'e';
      this->display_code = 'r';
      cout << "CoralReef " << get_id() << " has been depleted of food"
	   << endl;
      return true;
    }
  else
    return false;
}

void CoralReef::show_status()
{
  cout << "CoralReef Status: " << this->display_code << " with ID "
       << get_id() <<" at location "<< this->location<< " containing food "
       << this->amount << endl;
}

void CoralReef::save(ofstream& file)
{
  file << display_code << " " << get_id() << " " << state << " " << amount << " "
       << location << endl;
  return;
}

void CoralReef::restore(ifstream& file, Model* model)
{
  file >> display_code >> id_num >> state >> amount >> location;
  return;
}