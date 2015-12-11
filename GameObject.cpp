/* EC327 Programming Assignment 3. Class implementation for GameObject        
   Luis Barroso Luque                                          November 2014 */

#include <iostream>
#include "GameObject.h"

GameObject::GameObject()
{
  cout << "GameObject default constructed" << endl;
}

GameObject::GameObject(char in_code, int in_id)
{
  display_code = in_code;
  id_num = in_id;
  location.x = 0;
  location.y = 0;

  cout << "GameObject default constructed" << endl;
}

GameObject::GameObject(char in_code, int in_id, const CartPoint& in_loc)
{
  display_code = in_code;
  id_num = in_id;
  location.x = in_loc.x;
  location.y = in_loc.y;

  cout << "GameObject constructed" << endl;
}

GameObject::~GameObject()
{
  cout << "GameObject destructed" << endl;
}

//Member functions
CartPoint GameObject::get_location() const
{
  return location;
}

int GameObject::get_id() const
{
  return id_num;
}

void GameObject::show_status()
{
  cout << "GameObject Status: " << display_code << " with ID " 
       << id_num << " at location " << location << endl;
}

void GameObject::drawself(char* grid)
{
  grid[0] = display_code;
  grid[1] = static_cast<char>(id_num + 48);
}

char GameObject::get_state()
{
  return state;
}

char GameObject::get_display_code()
{
  return display_code;
}

bool GameObject::is_alive()
{
  return true;
}