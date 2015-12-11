/* EC327 Programming Assignment 3. Class definition for Model                  
   Luis Barroso Luque                                              November 2014   */

#ifndef MODEL_H
#define MODEL_H

#include <list>
#include <fstream>
#include "GameObject.h"
#include "Cave.h"
#include "CoralReef.h"
#include "Fish.h"
#include "View.h"
#include "Tuna.h"
#include "Shark.h"
#include "Sharknado.h"

class Sharknado;

//using std::list;
using namespace std;

 class Fish;
 class Tuna;
 class Shark;

class Model
{
public:
	Model(); //Constructor
	~Model(); //Destructor

	//Some member variables here
	Fish* get_Fish_ptr(int id_num);
	CoralReef* get_CoralReef_ptr(int id_num);
	Cave* get_Cave_ptr(int id_num);
	bool update();
	void display(View& view);
	void show_status();
	int get_time();
	Fish* whos_in_cave(Fish* me); //Get fish id of fish in cave if only one other fish is in cave
	void add_new_tuna(Tuna* Parent); //Baby tuna come here pleaseee
	int find_next_fish_id();
	void add_pointer(GameObject* newObject);
	void insert_cave(Cave* cave);
	void insert_reef(CoralReef* reef);
	void insert_fish(Fish* fish);
	void whos_not_hidden(Sharknado* sharknado,list<Fish*>& fishes_not_hidden); //gives all fishes not in cave
	//void remove_fish(Sharknado* sharknado, );//Only the sharknado can remove fish;
	void save(ofstream& file);
	void restore(ifstream& file);

private:
	int time; //How long the fun has lasted
	
	list<GameObject*> object_ptrs; //Pointers to all this stuff
	list<GameObject*>::iterator it_o;

	list<GameObject*> active_ptrs; //Active objects to be displayed
	list<GameObject*>::iterator it_a;

	list<Fish*> fish_ptrs; //keep tabs of all the fishies
	list<Fish*>::iterator it_f;

	list<Cave*> cave_ptrs; //Real estate tabulation 
	list<Cave*>::iterator it_c;

	list<CoralReef*> reef_ptrs; //Gotta know where the food is at
	list<CoralReef*>::iterator it_r;

	Sharknado* sharknado;

	//Model(const Model&); //Copy constructor

};

#endif
