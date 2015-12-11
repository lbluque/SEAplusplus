/* EC327 Programming Assignment 3. Class implementation for Tuna               
   Luis Barroso Luque                                         November 2014   */

#include "Tuna.h"

Tuna::Tuna():Fish('T', 10)
{
  //cout << "Tuna default constructed" << endl;
}

Tuna::Tuna(int in_id):Fish('T', 10)
{
  id_num = in_id;
}

Tuna::Tuna(int in_id, Cave* home, Model* world):Fish('T', 10, in_id, home, world)
{
  //cout << "Tuna constructed" << endl;
  mateTime = 0;
  initiator = false;
}

double Tuna::get_speed()
{
  double speed = (1/size)*energy*4;
  return speed;
}

bool Tuna::start_mating(Tuna* datTuna)
{
  double necessarySpace = size + datTuna->get_size() + 10; //Check all the stuff
  if (size >= 40 && size <= 60 && datTuna->get_size() >= 40 && datTuna->get_size() <= 60) //&& home->get_space() >= necessarySpace
    {
      cout << get_display_code() << id_num << ": I found my mate!" << endl;
      initiator = true;
      state = 'm';
      datTuna->sexy_time();
      return true;
    }
  return false;
}

bool Tuna::update()
{
  Fish::update();
  
  if (state == 'h')
  {
    Tuna* datTuna = NULL; 

    //Check what fishers are in the cave the fish is in
    Fish* fishyFish = world->whos_in_cave(this);
  
    if (fishyFish)
        datTuna = dynamic_cast<Tuna*>(fishyFish); //Cast the fish to a Tuna

    if (datTuna) //Check if Fish in cave is a Tuna, dont want to get kinky with a Shark
    {
      if (!(datTuna->are_you_hitting_on_me())) //make sure the other Tuna is not making any moves
          if (start_mating(datTuna))
          {  
            if (get_id() < datTuna->get_id())
              datTuna->set_mateTime();

            return true;
          }
    }
  }

  if (state == 'm')
  {
    if (mateTime == 2)
      {
    
        state = 'h';
        mateTime = 0;

      //Create a new flippin tuna
        if (initiator)
        {
          world->add_new_tuna(this);
          initiator = false;
        }

        return true;
      }
    else
      mateTime += 1;
  }
  return false;
}

void Tuna::show_status()
{
  cout << "Tuna status: "; 
  Fish::show_status();
  //Specific tuna info that the world must know
  if (state == 'm')
    cout << " is mating in Cave " << home->get_id() << endl;
}

void Tuna::sexy_time()
{
  state = 'm';
}

bool Tuna::are_you_hitting_on_me()
{
  return initiator;
}

 void Tuna::set_mateTime() //This is used to cordinate mating when the initiator has a lower ID
 {                          //than the other fish
  mateTime = -1;
 }

void Tuna::save(ofstream& file)
{

  file << display_code << " " << get_id() << " " << state << " " << energy << " " 
       << size << " " << prefeast_size << " " << location << " " << destination << " "
       << delta << " " << mateTime << " " << initiator << " ";

  //Reef pointer
  if (reef != NULL)
    file << reef->get_id() << " ";
  else
    file << -1 << " ";
  //Home pointer
  if (home != NULL)
    file << home->get_id() << endl;
  else
    file << -1 << endl;

  return;
}

void Tuna::restore(ifstream& file, Model* world)
{
  int reef_id, home_id;

  this->world = world;

  file >> display_code >> id_num >> state >> energy >> size >> prefeast_size
       >> location >> destination >> delta >> mateTime >> initiator;

  file >> reef_id;
  if (reef_id == -1)
    reef = NULL;
  else 
    reef = world->get_CoralReef_ptr(reef_id);

  file >> home_id;
  if (home_id == -1)
    home = NULL;
  else 
    home = world->get_Cave_ptr(home_id);
  return;
}
