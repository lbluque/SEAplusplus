/* EC327 Programming Assignment 3. Class implementation for Model                  
   Luis Barroso Luque                                              November 2014   */

#include <iostream>
#include "Model.h"
#include "InputHandling.h"

//Constructor
Model::Model() 
{
	time = 0;

	//Initialize all the stuff8
	
	//Caves!!!
	cave_ptrs.push_back(new Cave(1, CartPoint(5,1)));
	object_ptrs.push_back(cave_ptrs.back());
	active_ptrs.push_back(cave_ptrs.back());


	cave_ptrs.push_back(new Cave(2, CartPoint(6,2)));
	object_ptrs.push_back(cave_ptrs.back());	
	active_ptrs.push_back(cave_ptrs.back());


	//Coral Reefs 
	reef_ptrs.push_back(new CoralReef(1, CartPoint(1,20)));
	object_ptrs.push_back(reef_ptrs.back());
	active_ptrs.push_back(reef_ptrs.back());

	reef_ptrs.push_back(new CoralReef(2, CartPoint(20,1)));
	object_ptrs.push_back(reef_ptrs.back());
	active_ptrs.push_back(reef_ptrs.back());

	reef_ptrs.push_back(new CoralReef(3, CartPoint(20,20)));
	object_ptrs.push_back(reef_ptrs.back());
	active_ptrs.push_back(reef_ptrs.back());

	//Point iterators to appropriate lists
	it_o = object_ptrs.begin();
	it_c = cave_ptrs.begin();
	it_r = reef_ptrs.begin();

	//FISH FISH FISH
	fish_ptrs.push_back(new Tuna(1, *it_c, this));
	object_ptrs.push_back(fish_ptrs.back());
	active_ptrs.push_back(fish_ptrs.back());

	it_c++; //at cave 2
	fish_ptrs.push_back(new Tuna(2, *it_c, this));
	object_ptrs.push_back(fish_ptrs.back());
	active_ptrs.push_back(fish_ptrs.back());


	fish_ptrs.push_back(new Tuna(3, *it_c, this));
	object_ptrs.push_back(fish_ptrs.back());
	active_ptrs.push_back(fish_ptrs.back());

	fish_ptrs.push_back(new Shark(4, this));
	object_ptrs.push_back(fish_ptrs.back());
	active_ptrs.push_back(fish_ptrs.back());


	fish_ptrs.push_back(new Shark(5, this));
	object_ptrs.push_back(fish_ptrs.back());
	active_ptrs.push_back(fish_ptrs.back());

	sharknado = Sharknado::get_intance(this);

	cout << "Model default constructed" << endl;

}

Model::~Model()
{
	//Print Sharknado Wrath history
	sharknado->print_history();

	//Release all dynamically allocated memory
	for (it_o = object_ptrs.begin(); it_o != object_ptrs.end(); it_o++)
			delete *it_o;		
	
	//Clear all them lists
	object_ptrs.clear();
	active_ptrs.clear();
	fish_ptrs.clear();
	cave_ptrs.clear();
	reef_ptrs.clear();

	delete sharknado;

	//cout << "Model destructed" << endl;
}

//Some member functions 
Fish* Model::get_Fish_ptr(int id_num)
{
	for (it_f = fish_ptrs.begin(); it_f != fish_ptrs.end(); it_f++)
	{
		if ((*it_f)->get_id() == id_num)
			return *it_f;
	} 

	return NULL;
}

CoralReef* Model::get_CoralReef_ptr(int id_num)
{
	for (it_r = reef_ptrs.begin(); it_r != reef_ptrs.end(); it_r++)
	{
		if ((*it_r)->get_id() == id_num)
			return *it_r;
	} 

	return NULL;
}

Cave* Model::get_Cave_ptr(int id_num)
{
	for (it_c = cave_ptrs.begin(); it_c != cave_ptrs.end(); it_c++)
	{
		if ((*it_c)->get_id() == id_num)
			return *it_c;
	} 

	return NULL;
}

bool Model::update() 
{
  	bool somethingChanged;
	
	for (it_a = active_ptrs.begin(); it_a != active_ptrs.end(); it_a++)
	{
	  if ((*it_a)->is_alive())
	  {
	  	if((*it_a)->update())
	  	{
	    	somethingChanged = true;
	    }
	  }
	else
	  {
	  	it_a = active_ptrs.erase(it_a);
	  	it_a--;
	  	cout << "Model: Dead object removed" << endl;
	  } 
	}

	if (sharknado->update())
	 somethingChanged = true;

	time += 1;

	return somethingChanged;
}

void Model::show_status()
{
	cout << "---Fish---" << endl;
	for (it_f = fish_ptrs.begin(); it_f != fish_ptrs.end(); it_f++)
		(*it_f)->show_status();

	cout << "---Cave---" << endl;
	for (it_c = cave_ptrs.begin(); it_c != cave_ptrs.end(); it_c++)
		(*it_c)->show_status();

	cout << "---Reef---" << endl;
	for (it_r = reef_ptrs.begin(); it_r != reef_ptrs.end(); it_r++)
		(*it_r)->show_status();
}


void Model::display(View& view)
{
	cout << "Time: " << time << endl;
	view.clear();

	for (it_a = active_ptrs.begin(); it_a != active_ptrs.end(); it_a++)
	{
		view.plot(*it_a);
	}

	view.draw();
}

int Model::get_time()
{
	return time;
}

Fish* Model::whos_in_cave(Fish* me) //Finds any other fish in the cave member of 'me'
{									//only returns a fish if there is only one other fish
	int fishInCave = 0;
	Fish* fishy;

	for (it_f = fish_ptrs.begin(); it_f != fish_ptrs.end(); it_f++)
	{

		if ((*it_f)->get_home() == me->get_home() && (*it_f)->get_state() == 'h' && *it_f != me)
		{
			fishy = *it_f;
			fishInCave += 1;
		}
			
	}

	if (fishInCave == 1)
		return fishy;
	else
		return NULL; 
}

int Model::find_next_fish_id() //finds lowest available ID, assumes ids in list are in 
{								//ascending order
	int next_id = 1;

	for (it_f = fish_ptrs.begin(); it_f != fish_ptrs.end(); it_f++)
	{
		if ((*it_f)->get_id() == next_id)
		{
			next_id++;
		}
	}
	return next_id;
}

void Model::add_new_tuna(Tuna* Parent) //Adds that baby tuna muna
{
	int next_id = find_next_fish_id();

	if (next_id == 1)
	{
			fish_ptrs.push_front(new Tuna(next_id,Parent->get_home(),this));
			object_ptrs.push_back(fish_ptrs.front());
			active_ptrs.push_back(fish_ptrs.front());

	}
	else if (next_id > fish_ptrs.back()->get_id())
	{
			fish_ptrs.push_back(new Tuna(next_id,Parent->get_home(),this));
			object_ptrs.push_back(fish_ptrs.back());
			active_ptrs.push_back(fish_ptrs.back());
	}
	else
	{
		it_f = fish_ptrs.begin();
		list<Fish*>::iterator it_next = ++it_f;
		//Find the appropriate location to insert the new Tuna
		for (it_f--; it_next != fish_ptrs.end(); it_f++, it_next++)
		{
			if (next_id < (*it_next)->get_id() && next_id > (*it_f)->get_id())
			{
				fish_ptrs.insert(it_next,new Tuna(next_id,Parent->get_home(),this));
				it_f++;
				object_ptrs.push_back(*it_f);
				active_ptrs.push_back(*it_f);	
			}

		}
	}

	cout << "Tuna " << next_id << " was born in cave " << Parent->get_home()->get_id() << endl;
	
}

void Model::add_pointer(GameObject* newObject)
{
  char type = newObject->get_display_code();

  switch (type) //switch through the types and and to the correct list
  {				//Object must be downcasted to the appropriate class
    case 'R':
    {
      insert_reef(dynamic_cast<CoralReef*>(newObject)); 
      break;
    }
    case 'c':
    {
      insert_cave(dynamic_cast<Cave*>(newObject));
      break;
	}
    case 'T':
    {
      insert_fish(dynamic_cast<Tuna*>(newObject));
      break;
    }
    case 'S':
    {      
      insert_fish(dynamic_cast<Shark*>(newObject));
      break;
    }
  }

  object_ptrs.push_back(newObject);
  active_ptrs.push_back(newObject);

  return;
}

void Model::insert_cave(Cave* cave) //Insterts the cave in the correct location in the
{									// cave_ptrs list
	int id = cave->get_id();

	if (id == 1)
			cave_ptrs.push_front(cave);
	else if (id > cave_ptrs.back()->get_id())
			cave_ptrs.push_back(cave);
	else
	{
		it_c = cave_ptrs.begin();
		list<Cave*>::iterator it_next = ++it_c;
		//Find the appropriate location to insert the new cave
		for (it_c--; it_next != cave_ptrs.end(); it_c++, it_next++)
			if (id < (*it_next)->get_id() && id > (*it_c)->get_id())
				cave_ptrs.insert(it_next,cave);
	}
}

void Model::insert_reef(CoralReef* reef) //same as other inserts
{
	int id = reef->get_id();

	if (id == 1)
			reef_ptrs.push_front(reef);
	else if (id > reef_ptrs.back()->get_id())
			reef_ptrs.push_back(reef);
	else
	{
		it_r = reef_ptrs.begin();
		list<CoralReef*>::iterator it_next = ++it_r;
		//Find the appropriate location to insert the new reef
		for (it_r--; it_next != reef_ptrs.end(); it_r++, it_next++)
			if (id < (*it_next)->get_id() && id > (*it_r)->get_id())
				reef_ptrs.insert(it_next,reef);
	}
}

void Model::insert_fish(Fish* fish) //same as other inserts
{
	int id = fish->get_id();

	if (id == 1)
			fish_ptrs.push_front(fish);
	else if (id > fish_ptrs.back()->get_id())
			fish_ptrs.push_back(fish);
	else
	{
		it_f = fish_ptrs.begin();
		list<Fish*>::iterator it_next = ++it_f;
		//Find the appropriate location to insert the new fisher
		for (it_f--; it_next != fish_ptrs.end(); it_f++, it_next++)
			if (id < (*it_next)->get_id() && id > (*it_f)->get_id())
				fish_ptrs.insert(it_next,fish);
	}	
}

void Model::save(ofstream& file)
{
	file << time << endl << active_ptrs.size() << endl; //Save time and number of pointers
														// in the first two lines
	//Create the catalog listing each objects display_code and id
	for (it_a = active_ptrs.begin(); it_a != active_ptrs.end(); it_a++)
		file << (*it_a)->get_display_code() << " " << (*it_a)->get_id() << endl;

	file << endl;

	//Call each objects save function 
	for (it_a = active_ptrs.begin(); it_a != active_ptrs.end(); it_a++)
	{
		(*it_a)->save(file);
		file << endl;
	}

	//Now have sharknado save its stuffs
	sharknado->save(file);

	return;
}

void Model::restore(ifstream& file)
{
	int read_int, num_objects;
	double read_double;
	char read_char;

	sharknado->print_history(); //print history so match that sample output

	//Remove and deallocate all objects in current game
	for (it_o = object_ptrs.begin(); it_o != object_ptrs.end(); it_o++)
		delete *it_o;
	
	//Clear all them lists
	object_ptrs.clear();
	active_ptrs.clear();
	fish_ptrs.clear();
	cave_ptrs.clear();
	reef_ptrs.clear();


	//Read in time
	file >> read_int;
	time = read_int;

	sharknado->set_sweepCounter(time); //Synchronize the sharknado

	file >> read_int;
	num_objects = read_int;

	for (int i = 0; i < num_objects; i++)
	{
		file >> read_char >> read_int;

		switch (read_char) //Switch through the read char and instantiate
		{					// the corresponding object
			case 'c':
			case 'C':
			cave_ptrs.push_back(new Cave());
			object_ptrs.push_back(cave_ptrs.back());
			active_ptrs.push_back(cave_ptrs.back());
			break;

			case 'r':
			case 'R':
			reef_ptrs.push_back(new CoralReef());
			object_ptrs.push_back(reef_ptrs.back());
			active_ptrs.push_back(reef_ptrs.back());
			break;

			case 'T':
			fish_ptrs.push_back(new Tuna());
			object_ptrs.push_back(fish_ptrs.back());
			active_ptrs.push_back(fish_ptrs.back());
			break;

			case 'S':
			fish_ptrs.push_back(new Shark());
			object_ptrs.push_back(fish_ptrs.back());
			active_ptrs.push_back(fish_ptrs.back());
			break;

		}
	}

	//Restore the cave data 
	for (it_c = cave_ptrs.begin(); it_c != cave_ptrs.end(); it_c++)
		(*it_c)->restore(file, this);
	//Restore the reef data
	for (it_r = reef_ptrs.begin(); it_r != reef_ptrs.end(); it_r++)
		(*it_r)->restore(file, this);
	//Restore the fish data
	for (it_f = fish_ptrs.begin(); it_f != fish_ptrs.end(); it_f++)
		(*it_f)->restore(file, this);

	//Now sharknado restores its stuff
	sharknado->restore(file,this);

	return;
}
							//Only sharknado can call this function
void Model::whos_not_hidden(Sharknado* sharknado, list<Fish*>& fishes_not_hidden)
{
	for (it_f = --(fish_ptrs.end()); it_f != --(fish_ptrs.begin()); it_f--)
		if (!((*it_f)->is_hidden()) && !((*it_f)->is_dead_in_cave())) //Check if hidden
		{
			fishes_not_hidden.push_front(*it_f); //Put fish in sharknado's list
			fish_ptrs.remove(*it_f); //remove from fish
			active_ptrs.remove(*it_f); //remove from active pointers
		}
}
