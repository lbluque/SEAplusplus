/* EC327 Programming Assignment 3. Class implementation for Fish   
   Luis Barroso Luque                                       November 2014   */

#include <iostream>
#include "Fish.h"

using namespace std;

//Constructors
Fish::Fish(char in_code, int in_size):GameObject(in_code, 0)
{
  state = 'f';
  energy = 15;
  size = in_size;
  prefeast_size = size;
  destination = CartPoint(0,0);
  delta = CartVector(0,0);
  reef = NULL;
  home = NULL;
  world = NULL;
  cout << "Fish default constructed" << endl;
  }

Fish::Fish(char in_code, int in_size, int in_id, Cave* home, Model* world):GameObject(in_code, in_id, home->get_location())
{
  energy = 15;
  size = in_size;
  prefeast_size = size;
  destination = CartPoint(0,0);
  delta = CartVector(0,0);
  reef= NULL;
  state = 'f';
  if (home->hide_fish(this))
  {
    this->home = home;
    state = 'h';
  }
  this->world = world;
  cout << "Fish constructed" << endl;
 }

Fish::Fish(char in_code, int in_size, int in_id, CartPoint birthplace, Model* world):GameObject(in_code, in_id, birthplace)
{
  state = 'f';
  energy = 15;
  size = in_size;
  prefeast_size = size;
  destination = CartPoint(0,0);
  delta = CartVector(0,0);
  reef = NULL;
  home = NULL;
  this->world = world;
  cout << "Fish constructed" << endl;
}

//Destroy again baaaam
 Fish::~Fish()
 {
    cout << "Fish destructed" << endl;
 }

//Private member functions
bool Fish::update_location()
{
    cout << display_code << get_id();
    if (fabs(destination.x - location.x) <= fabs(delta.x) && fabs(destination.y - location.y) <= fabs(delta.y))
    {
        location = destination;
        cout << ": I’m there!" << endl;
        return true;
    }
    else
    {
        location = location + delta;
        cout << ": just keep swimming..." << endl;
        return false;
    }
}

void Fish::setup_destination(const CartPoint& dest)
{
  destination = dest;

  double distance = cart_distance(destination,location);
  
  if (distance == 0)
    delta = destination - location;
  else
    delta = (destination - location)*(get_speed()/distance);

  if (is_hidden())
    home->release_fish(this);
}

//Public member functions
bool Fish::update()
{
    switch (state)
    {
        case 'f':
            return false;
            
        case 's':
            if (update_location())
            {
                state = 'f';
                return true;
            }
            else
                return false;
            
        case 'o':
            if (update_location())
            {
                state = 'e';
		            prefeast_size = size;
                cout << display_code << get_id() 
                << ": Starting to dine at a coral reef" << endl;
                return true;
            }
            else
                return false;
   
        case 'e':
        {
            double foodProvided = 0;
            
            if (size < 2*prefeast_size && !(reef->is_empty()))
            {
                foodProvided = reef->provide_food();
                size += foodProvided/2;
                cout << display_code << get_id() << ": Grew to size " << size << endl;
                return false;
              
            }
            else if (reef->is_empty() && size < 2*prefeast_size)
            {
                state = 'f';
                cout << display_code << get_id() << ": This reef has no more food"
                << " for me..." << endl;
                return true;
            }
            else
            {
                cout << display_code << get_id() << ": I'm full. I'm heading home" << endl;
                state = 'z';
                setup_destination(home->get_location());
                return true;
            }
        }    
           
        case 'z':
        {
            if (update_location())
            {
                if (home->hide_fish(this))
                {
                    state = 'h';
                    cout << display_code << get_id() << ": I am hidden and safe" << endl;
                    return true;
                }
                else
                {
                    state = 'p';
                    cout << display_code << get_id() << ": Help! My home cave is full" << endl;
                    return true;
                }
            }
            return false;
        }    
        case 'h':
	         {
	           if (energy < 5)
		          {
		            state = 'x';  
		            return home->release_fish(this);
		          }
	           else
		        {
		          energy = .75*energy;
		          return false;
		        }
	         }

            case 'p':
	      return false;

            case 'x':
              return false;
    }
}

void Fish::show_status()
{
    //General output
    cout << display_code << " with ID " << get_id() << " at location " << location;
    switch (state)
    {
        case 'f':
            cout << " is floating. Has a size of: " << size << " and energy of: "
            << energy << endl;
            break;
            
        case 's':
	  cout << " has a speed of: "  << get_speed() << " and is heading to: "
		 << destination << endl; //SPEED SPEED SPEED
            break;
            
        case 'o':
            cout << " is outbound to Reef: " << reef->get_id() << " with a speed of "
		 << get_speed() <<  endl; //SPEED SPEED SPEED
            break;
            
        case 'e':
            cout << " is eating at Reef " << reef->get_id() << endl;
            break;
            
        case 'z':
            cout << " is swimming to Cave " << home->get_id() << " with a speed of "
		 << get_speed() << endl; //SPEED SPEED SPEED
            break;
            
        case 'h':
            cout << " is hidden in Cave " << home->get_id() << endl;
	    break;
            
        case 'p':
            cout << " is panicked!!!! " << "And has a size of " << size << endl;
            break;

        case 'x':
          cout << " is dead" << endl;
	  //MAYBE SOMETHING GOES IN HERE
	  break;
    }
} 

double Fish::get_size() const
{
    return size;
}

void Fish::start_swimming(const CartPoint& dest)
{
  setup_destination(dest);

  state = 's';
  cout << display_code << get_id() << ": On my way" << endl;
}

void Fish::start_eating(CoralReef* destReef)
{

  reef = destReef;
  setup_destination(destReef->get_location());
  
  state = 'o';
  cout << "Fish " << get_id() << " eating at CoralReef "
       << destReef->get_id() << " and returning back to Cave " 
       << home->get_id() << endl;
  cout << display_code << get_id() << ": Food here I come!" << endl;
}

bool Fish::is_hidden() const
{
    if (state == 'h')
        return true;
    else
        return false;
}

void Fish::start_hiding(Cave* destCave)
{
  setup_destination(destCave->get_location());
  home = destCave;
  state = 'z';
  cout << "Fish " << get_id() << " swimming to Cave " 
       << destCave->get_id() << endl << display_code << get_id() 
       << ": Off to safety" << endl;  
}

void Fish::float_in_place()
{
  if (state == 'h')
    home->release_fish(this);
  state = 'f';
  cout << "Stopping " << get_id() << endl << display_code 
       << get_id() << ": Resting my fins" << endl;
}

void Fish::get_bitten(int attack_strength)
{
  energy -= attack_strength;

  if (energy <= 0)
    {
    state = 'x';
    cout << display_code << get_id() 
         <<": Oh no, I've become chum!" << endl;
    }
  else
    cout << get_display_code() << id_num << ": Ouch!" << endl;
 
}

void Fish::start_attack(Fish* fishToGet)
{
  cout << get_display_code() << get_id() << ": I cannot attack." << endl;
}

bool Fish::start_mating(Fish* datFishDoe)
{
  cout << get_display_code() << get_id() <<": I cannot mate." << endl;
  return false;
}


Cave* Fish::get_home()
{
  return this->home;
}

bool Fish::is_alive()
{
  if (state == 'x')
    return false;

  return true;
}

 bool Fish::is_dead_in_cave()
 {
    if (state == 'x' && location.x == home->get_location().x && location.y == home->get_location().y)
      return true;
    
    return false;
 }
