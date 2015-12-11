/* EC327 Programming Assignment 3. Function prototypes for GameCommands                  
   Luis Barroso Luque                                              November 2014   */

#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H

#include "InputHandling.h"
#include "Model.h"
#include <fstream>

class Cave;
class CoralReef;
class Fish;
class CartPoint;

void do_swim_command(Model& model);	
void do_eat_command(Model& model);
void do_float_command(Model& model);
void do_zoom_command(Model& model);
void do_go_command(Model& model);
void do_run_command(Model& model);
void do_attack_command(Model& model);
void add_object_command(Model& model);
void save_game_command(Model& model);
void restore_game_command(Model& model);

#endif
