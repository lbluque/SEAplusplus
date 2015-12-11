/* EC327 Programming Assignment 3. Class definition for Cave   
   Luis Barroso Luque                                       November 2014   */

#include <iostream>
#include "Cave.h"

//Constructors
Cave::Cave():GameObject('c',0)
{
  this->state = 'e';
  this->space = 100;
  cout << "Cave default constructed" << endl;
  }

Cave::Cave(int in_id, const CartPoint& in_loc):GameObject('c', in_id, in_loc)
{
  this->state = 'e';
  this->space = 100;  
  cout << "Cave constructed" << endl;
  }

Cave::~Cave()
{
  cout << "Cave destructed" << endl;
}

//Member functions                              
                              
bool Cave::hide_fish(Fish* fish_to_hide)
{
  if (space >= fish_to_hide->get_size() && !(fish_to_hide->is_hidden()))
  {
      space -= fish_to_hide->get_size();
      return true;
  }
  else
      return false;
}

bool Cave::release_fish(Fish* fish_to_release)
{
    if (fish_to_release->is_hidden() || !(fish_to_release->is_alive()))
    {
        space += fish_to_release->get_size();
        return true;
    }
    else
        return false;
} 

bool Cave::update()
{
  if (space == 0 && state != 'p')
    {
      state = 'p';
      display_code = 'C';

      cout << "Cave " << this->get_id() << " is packed like sardines" << endl;

      return true;
    }
  else if (state == 'p' && space != 0)
    {
      state = 'e';
      display_code = 'c';
      
      return true; 
    }
  else
    return false;
}
 
void Cave::show_status()
{
  cout << "Cave Status: " << this->display_code << " with ID " << get_id()
       << " at location " << this->location << " has a space of " << this->space
       << endl;
} 

double Cave::get_space() const
{
  return space;
}

void Cave::save(ofstream& file)
{
  file << display_code << " " << get_id() << " " << state << " " << space << " "
       << location << endl;
  return;
}

void Cave::restore(ifstream& file, Model* model)
{
  file >> display_code >> id_num >> state >> space >> location;
  return;
}