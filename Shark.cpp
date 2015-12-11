/* EC327 Programming Assignment 3. Class implementation for Shark               
   Luis Barroso Luque                                         November 2014   */

#include "Shark.h"

using namespace std;

Shark::Shark():Fish('S',20)
{
	target = NULL;
	range = 1;
	attack_strength = 2;
	//cout << "Shark default constructed" << endl;
}

Shark::Shark(int in_id):Fish('S', 10)
{
  id_num = in_id;
}

Shark::Shark(int in_id, Model* world):Fish('S', 20, in_id, CartPoint(0,0), world)//
{
	srand(world->get_time());
	location.y = rand()%20;
	location.x = rand()%20;
	target = NULL;
	range = 1;
	attack_strength = 2;
	//cout << "Shark Constructed" << endl;	
}

double Shark::get_speed()
{
	return (1/size)*energy*8;
}

void Shark::start_attack(Fish* target)
{
	if (cart_distance(location,target->get_location()) <= range)
	{
		cout << get_display_code() << id_num << ": Chomp!" << endl;
		this->target = target;
		state = 'a';
		target->get_bitten(attack_strength);
	}
	else 
		cout << get_display_code() << id_num << ": Fish are friends, not food" << endl;
}

bool Shark::update()
{
	Fish::update();
	switch (state)
	{
		case 'x':
		  return false;

		case 's':
		  return false;

		case 'e':
		  //WAIT WHAT SAME AS FISH??? SERIOUSLY???

		case 'a':
			if (cart_distance(location,target->get_location()) > range)
			{
			  cout << 'S' << id_num << ": Darn! it escaped" << endl;
				state = 's';
				target = NULL;
				return true;
			}
			else if (target->get_state() == 'x')
			{
			  cout << 'S' << id_num << ": I triumph!" << endl;
				state = 's';
				target = NULL;
				energy += 5;
				return true;
			}
			else
			{
			  cout << 'S' << id_num << ": Chomp!" << endl;
				target->get_bitten(attack_strength);
				return false;
			}
	}
	return false;
}

void Shark::show_status()
{
	cout << "Shark status: ";
	Fish::show_status();

	switch (state)
	{
		case 'a':
			cout  << " is attacking Fish " << target->get_id() << endl;
			break;
	}
}

void Shark::start_hiding(Cave* destCave)
{
	cout << get_display_code() << id_num << ": I'm a shark. I'll never fit in caves" << endl;
	state = 'f';
}

void Shark::start_eating(CoralReef* destReef)
{
	cout << get_display_code() << id_num << ": I'm a shark. I only eat fish" << endl;
	state = 'f';
}


void Shark::save(ofstream& file)
{
  file << display_code << " " << get_id() << " " << state << " " << energy << " " 
       << size << " " << prefeast_size << " " << location << " " << destination << " "
  	   << delta << " " << attack_strength << " " << range << " ";
  //Fish target
  if (target != NULL)
    file << target->get_id() << " ";
  else
    file << -1 << endl;
  return;
}

void Shark::restore(ifstream& file, Model* world)
{

  int target_id;
  this->world = world;

  file >> display_code >> id_num >> state >> energy >> size >> prefeast_size
  	   >> location >> destination >> delta >> attack_strength >> range;

  file >> target_id;
  if (target_id == -1)
  	target = NULL;
  else
  	target = world->get_Fish_ptr(target_id);

  return;
}
