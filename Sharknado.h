/* EC327 Programming Assignment 4. Class definition for Sharknado   
   Luis Barroso Luque                                       December 2014   */

#ifndef SHARKNADO_H
#define SHARKNADO_H

#include "GameObject.h"
#include "Model.h"
#include <fstream>

class Fish;

class Sharknado: public GameObject
{
private:
Sharknado(){}; //Private constructor - 'Singleton pattern'
Sharknado(Model* world);
static bool instanceFlag; //flag for single instance of Sharknado - 'Singleton pattern'
static Sharknado* sharknado; //pointer to itself, used in get instance

Model* world;
list<Fish*> swept_fish_ptrs; //Everything the Sharknado has taken
list<Fish*> current_carnage;
list<Fish*>::iterator it_s;

int sweepPeriod; //How often the Sharknado sweeps the game up
int alertTime; //Time before a sweep period where the sharkando alerts
int sweepCounter;

public:
static Sharknado* get_intance(Model* world);//instantiates or returns the existing instance
bool update();
void save(ofstream& file);
void restore(ifstream& file, Model* model);
void sweep();
void print_history();
void set_sweepCounter(int time_in);

//Destructor
~Sharknado();

};
#endif