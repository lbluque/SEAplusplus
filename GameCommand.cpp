/* EC327 Programming Assignment 3. Class implementation for Model                  
   Luis Barroso Luque                                              November 2014   */

#include "GameCommand.h"

void do_swim_command(Model& model)
{
	int fish_id;
	double x_in, y_in;

	if (!(cin >> fish_id)) //Check if input is an integer
		throw InvalidInput("Not an integer");

	if (!(cin >> x_in) || !(cin >> y_in)) //Check if inputs are doubles
		throw InvalidInput("Location should be double");

	Fish* nemo = model.get_Fish_ptr(fish_id);

	if(nemo == (Fish*)NULL) // check if is ID valid?
		throw InvalidInput("Invalid Fish ID");

	if (nemo) //Check if pointer is not NULL
	  {
	  	if (nemo->is_alive())
	  	{
		cout << "Swimming " << fish_id << " to "
		     << CartPoint(x_in, y_in) << endl;
		nemo->start_swimming(CartPoint(x_in,y_in));
		}
		else
			cout << nemo->get_display_code() << nemo->get_id() << ": Dead." << endl;

	  }

	return;
}

void do_eat_command(Model& model)
{
	int fish_id, reef_id;

	if (!(cin >> fish_id) || !(cin >> reef_id)) //Check if input stream is good
		throw InvalidInput("Expecting an integer");
	
	Fish* nemo = model.get_Fish_ptr(fish_id);
	CoralReef* reef = model.get_CoralReef_ptr(reef_id);

	if(nemo == (Fish*)NULL) // check if is ID valid?
		throw InvalidInput("Invalid Fish ID");
	if(reef == (CoralReef*)NULL) // check if is ID valid?
		throw InvalidInput("Invalid Reef ID");

	if (nemo && reef) //Check if pointer is not NULL
	{
		if (nemo->is_alive())
			nemo->start_eating(reef);
		else
			cout << nemo->get_display_code() << nemo->get_id() << ": Dead." << endl;

	}
	return;
}

void do_float_command(Model& model)
{
	int fish_id;

	if (!(cin >> fish_id)) //Check if input stream is good
		throw InvalidInput("Expecting an integer");
	
	Fish* nemo = model.get_Fish_ptr(fish_id);

	if(nemo == (Fish*)NULL) // check if is ID valid?
		throw InvalidInput("Invalid Fish ID");

	if (nemo) //Check if pointer is not NULL
	{
		if (nemo->is_alive())
			nemo->float_in_place();
		else
			cout << nemo->get_display_code() << nemo->get_id() << ": Dead." << endl;

	}
	return;
}

void do_zoom_command(Model& model)
{
    int fish_id, cave_id;

	if (!(cin >> fish_id) || !(cin >> cave_id)) //Check if input stream is good
		throw InvalidInput("Expecting an integer");

	Fish* nemo = model.get_Fish_ptr(fish_id);
	Cave* somewhereInAustralia = model.get_Cave_ptr(cave_id);

	if(nemo == (Fish*)NULL) // check if is ID valid?
		throw InvalidInput("Invalid Fish ID");
	if(somewhereInAustralia == (Cave*)NULL) // check if is ID valid?
		throw InvalidInput("Invalid Cave ID");

	if (nemo->is_alive())
		nemo->start_hiding(somewhereInAustralia);
	else 
		cout << nemo->get_display_code() << nemo->get_id() << ": Dead." << endl;

	return;
}

void do_go_command(Model& model)
{
  cout << "Advancing one tick" << endl;
  model.update();
  model.show_status();
}

void do_run_command(Model& model)
{
  cout << "Advancing to next event" << endl;
  int i = 0;
  while (!model.update() && i < 4) //Made it 4 because when it checks the 
    i++;                           //value in model.update() time advances to   
                                   //the 5th tick 
  model.show_status();
}	

void do_attack_command(Model& model)
{
	int attacker_id, attacked_id;

	if (!(cin >> attacker_id) || !(cin >> attacked_id)) //Check if input stream is good
		throw InvalidInput("Expecting an integer");

	Fish* attacker = model.get_Fish_ptr(attacker_id);
	Fish* attacked = model.get_Fish_ptr(attacked_id);

	if (attacker == (Fish*)NULL) // check if is ID valid?
		throw InvalidInput("Invalid Predator Fish ID");

	if (attacked == (Fish*)NULL)
		throw InvalidInput("Invalid Prey Fish ID");


	if (attacker->is_alive() && attacked->is_alive())
		attacker->start_attack(attacked);
	else
		cout << "Someone is dead" << endl;

	return;
}

void add_object_command(Model& model)
{
  char type;
  int in_id, cave_id;
  double in_x, in_y;
  
  if (!(cin >> type))
    throw InvalidInput("Expecting a char");

  if (!(cin >> in_id))
    throw InvalidInput("Expecting an int");

  GameObject* newObject = NULL;

  try{

	  switch (type) //Switch through types and instantiate accordingly
	  {
	    case 'R':
	  case 'r':
	    {

  		  if (!(cin >> in_x) || !(cin >> in_y))
    		throw InvalidInput("Expecting a double");

    	  if (model.get_CoralReef_ptr(in_id) != (GameObject*)NULL) 
      		throw newObject;

	      newObject = new CoralReef(in_id, CartPoint(in_x,in_y));
	      cout << "Created a new reef with id " << in_id << " at " <<  newObject->get_location() << endl;
	      break;
	    }
	    case 'C':
	  case 'c':
	    {

  		  if (!(cin >> in_x) || !(cin >> in_y))
    		throw InvalidInput("Expecting a double");

    	  if (model.get_Cave_ptr(in_id) != (GameObject*)NULL)
      	    throw newObject;

	      newObject = new Cave(in_id, CartPoint(in_x,in_y));
	      cout << "Created a new cave with id " << in_id << " at " <<  newObject->get_location() << endl;
	      break;
		}
	    case 'T':
	  case 't':
	    {
	      if (!(cin >> cave_id))
	      	throw InvalidInput("Expecting an int");
	      if (model.get_Fish_ptr(in_id) != (GameObject*)NULL) 
      		throw newObject;
      	  if (model.get_Cave_ptr(cave_id) == (GameObject*)NULL)
      	    throw newObject;

	      newObject = new Tuna(in_id, model.get_Cave_ptr(cave_id), &model);
	      cout << "Created a new tuna with id " << in_id << " at " <<  newObject->get_location() << endl;
	      break;
	    }
	    case 'S':
	  case 's':
	    {
      	  if (model.get_Fish_ptr(in_id) != (GameObject*)NULL) 
      		throw newObject;

	      newObject = new Shark(in_id, &model);
	      cout << "Created a new shark with id " << in_id << " at " <<  newObject->get_location() << endl;
	      break;
	    }
	    default:
	    {
	      throw InvalidInput("Invalid GameObject type");
	      break;
	  	}
	  }

	  model.add_pointer(newObject);
  }	
  catch (GameObject* exc) {

  	delete exc; //Delete the object created to avoid memory leaks
  	throw InvalidInput("ID is already taken");

  }
  return;
}

void save_game_command(Model& model)
{
	string fileName;
	if(!(cin >> fileName))
		throw InvalidInput("Expecting a string");

	ofstream file(fileName.c_str());

	model.save(file);

	file.close();
	return;
}

void restore_game_command(Model& model)
{
	string fileName;
	if(!(cin >> fileName))
		throw InvalidInput("Expecting a string");

	ifstream file(fileName.c_str());
	if (file.fail())
		throw InvalidInput("File not found");

	model.restore(file);

	file.close();

	return;
}
