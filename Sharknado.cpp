/* EC327 Programming Assignment 4. Class implementation for Sharknado   
   Luis Barroso Luque                                       December 2014   */

#include "Sharknado.h"

bool Sharknado::instanceFlag = false;
Sharknado* Sharknado::sharknado = NULL;

Sharknado* Sharknado::get_intance(Model* world)
{
	if (!instanceFlag) //Only instantiate if it has never been instantiated
	{					//SINGLETON SINGLETON SINGLETON SINGLETON
		sharknado = new Sharknado(world);
		instanceFlag = true;
		return sharknado;
	}
	else
		return sharknado;
}

Sharknado::Sharknado(Model* world):GameObject() //Constructor
{
	this->world = world;
	sweepPeriod = 15;
	alertTime = 5;
	sweepCounter = 0;
}

Sharknado::~Sharknado()//Destructor
{
	instanceFlag = false; //return instance flag to false meaning no Sharknado exists
	swept_fish_ptrs.clear();
	cout << "Sharknado destructed" << endl;
}

bool Sharknado::update()
{

	sweepCounter += 1;

	if (sweepCounter == sweepPeriod)
	{
		sweep();
		sweepCounter = 0;
		return true;
	}
	else if (sweepCounter + 5 == sweepPeriod)
	{
		cout << "The Sharknado is coming!" << endl;
		return true;
	}

	return false;
}

void Sharknado::sweep()
{
	int fish_num = 1;
	cout << "The Sharknado is upon us!" << endl;
	cout << "----------The Sharknado Claimed----------" << endl;
	world->whos_not_hidden(this,current_carnage);

	for (it_s = current_carnage.begin(); it_s != current_carnage.end(); it_s++)
	{
		cout << "(" << fish_num << ") - " << (*it_s)->get_display_code() 
			 << (*it_s)->get_id() << endl;
		fish_num++;
	}

	cout << "-----------------------------------------" << endl;

	swept_fish_ptrs.splice(swept_fish_ptrs.end(),current_carnage);

	return;
}

void Sharknado::save(ofstream& file)
{
	file << swept_fish_ptrs.size();//Print the size of the fishptrs sharknado has taken

	for (it_s = swept_fish_ptrs.begin(); it_s != swept_fish_ptrs.end(); it_s++)
		file << " " << (*it_s)->get_display_code() << " " << (*it_s)->get_id();
	return;
}
void Sharknado::restore(ifstream& file, Model* model)
{
	if (swept_fish_ptrs.size() != 0) //Remove anything in sharkandos list
		swept_fish_ptrs.clear(); //This is done only for the case when a game is saved and restored w/out 
								 //exiting the program
	int id, kill_num; 
	char type;
	file >> kill_num; //How many fish sharknado has previously killed
	
	//creates some fish objects with the ID of fishes swept away in previous game 
	for (int i = 0; i < kill_num; i++) //these are not used for anything except printing the history
	{									//Only sharknado knows about them, sneaky sharknado
		file >> type >> id;
		if (type == 'T')
		{
			swept_fish_ptrs.push_back(new Tuna(id));
		}
		if (type == 'S'){
			swept_fish_ptrs.push_back(new Shark(id));
		}
	}
	return;
}

void Sharknado::print_history()
{
	int fish_num = 1;

	cout << "----------The History of Sharknado's Wrath----------" << endl;
	for (it_s = swept_fish_ptrs.begin(); it_s != swept_fish_ptrs.end(); it_s++)
	{
		cout << "(" << fish_num << ") - " << (*it_s)->get_display_code()
		     << (*it_s)->get_id() << endl;
		fish_num++;
	}
	cout << "----------------------------------------------------" << endl;

}

void Sharknado::set_sweepCounter(int time_in)
{
	sweepCounter = time_in%sweepPeriod;
}
