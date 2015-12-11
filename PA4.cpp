/*EC 325 Programming Assignment 4. Main program to implement the Sea++ game. 
  Luis Barroso Luque                                    November 2014 */


#include <iostream>
#include "Model.h"
#include "GameCommand.h"
#include "View.h"
#include "InputHandling.h"

using namespace std;

int main()
{

//Print out these marvelous greetings
cout << "EC327: Introduction to Software Engineering" << endl;
cout << "Fall 2014" << endl;
cout << "Programming Assignment 4" << endl;

//Create all the fun by instantiating a model object
Model M1 = Model();
M1.show_status();
//And lets look at all this fun by creating a View object
View V1 = View();
M1.display(V1); //LETS SEE IT! LETS SEE IT! LETS SEE IT!  

char command;

do
   {
    cout << "Enter command: ";
    cin >> command;
    try {

      switch (command){
          case 's':
            do_swim_command(M1);
            break;

          case 'e':
            do_eat_command(M1);
            break;

          case 'f':
            do_float_command(M1);
            break;

          case 'z':
            do_zoom_command(M1);
            break;

          case 'g':
            do_go_command(M1);
            break;

          case 'r':
            do_run_command(M1);
            break;

          case 'a':
            do_attack_command(M1);
            break;
	    
          case 'n':
	          add_object_command(M1);
	          break;

          case 'S':
            save_game_command(M1);
            break;

          case 'R':
            restore_game_command(M1);
            break;

          case 'q':
            cout << "Terminating Program" << endl;
            return 0;

          default:
	    throw InvalidInput("Not an option");
      }
    }
    catch (InvalidInput& except) {
    // actions to be taken if the input is wrong
    cout << "Invalid Input - " << except.msg_ptr << endl;
    cin.clear();
    cin.ignore ( 80, '\n' );
    }

    M1.display(V1);
    
   }  while (command != 'q');

return 1;

}
