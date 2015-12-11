/* EC327 Programming Assignment 3. Class implementation for Veiw object     
Luis Barroso Luque                                              November 2014*/


#include "View.h"

View::View()
{
  size = view_maxsize/2 + 1; //Or 11 if you will. Left it like this because that way by just changing maxsize
  scale = 2;					//You can have so much more room for activities.
  origin.x = 0;
  origin.y = 0;
}

bool View::get_subscripts(int &ix, int &iy, CartPoint location)
{
	ix = (location.x - origin.x)/scale;
	iy = (location.y - origin.y)/scale;
	ix = ix + 1; //shift over one in order to have space for axis
	iy = iy + 1;

	//Check if the indices are within the grid displayed
	if (ix < 1 || ix > size + 1 || iy < 1 || iy > size + 1) //MY DISPLAY GRID INCLUDES THE AXII !!!!!!!!!!!!!!!!!!!!!
	{															//IF I GET POINTS OF FOR THIS I WILL BE QUITE UPSET
		cout << "An object is outside the display" << endl; //Also this is printed out for as many objects that are 
		return false; 										//outside of the display
	}
	else
		return true;
}

void View::clear() //SAME HERE: THE AXII ARE PART OF THE DISPLAY GRID. IF YOU DONT LIKE IT, IT SHOULD HAVE BEEN 
{					//MORE CLEARLY SPECIFIED IN THE ASSIGNMENT.
	int ones, tens;
	for (int i = 0; i < (size + 1); i++) //iterate over size + 1 times 
		for (int j = 0; j < (size + 1); j++)
		{
			if (j == 0) //Some stuff to get the tick marks to output and what not. Only even tick marks
			{
				if (i%2 != 0)
				{
					tens = int(scale)*(i-1)/10;
					ones = (int(scale)*(i-1))%10;
					if (tens == 0)
					{
						tens = ones;
						ones = -16; //48 - 16 = 32 is the ASCII code for a blank space. OK?
					}
					grid[i][j][0] = static_cast<char>(48+tens); //48 is 0 in ASCII 
					grid[i][j][1] = static_cast<char>(48+ones);
				}
				else
				{
					grid[i][j][0] = 32;//just to re-use it, because it took me like 1 to get the ASCII code
					grid[i][j][1] = 32;
				}
			}
			else if (i == 0)
			{
				if (j%2 != 0)
				{
					tens = int(scale)*(j-1)/10;
					ones = int(scale)*(j-1)%10;
					if (tens == 0) //check those single unit numbers
					{
						tens = ones;
						ones = -16; //48 - 16 = 32 is the ASCII code for a blank space. OK?
					}
					grid[i][j][0] = static_cast<char>(48+tens); //48 is 0 in ASCII 
					grid[i][j][1] = static_cast<char>(48+ones);
				}
				else
				{
					grid[i][j][0] = 32;//just to re-use it, because it took me like 1 to get the ASCII code
					grid[i][j][1] = 32;
				}
			}
			else
			{
				grid[i][j][0] = '.';
				grid[i][j][1] = 32; 
			}
		}
}

void View::plot(GameObject* ptr)
{
	int ix, iy;
	if (get_subscripts(ix, iy, ptr->get_location()))
		if (grid[iy][ix][0] == '.')
			ptr->drawself(grid[iy][ix]);
		else
		{
			grid[iy][ix][0] = '*';
			grid[iy][ix][1] = ' '; 
		}
}

void View::draw()
{
	for (int i = size; i >= 0; i--)
	{
		for(int j = 0; j < size + 1; j++)
			cout << grid[i][j][0] << grid[i][j][1];
		cout << endl;
	}
}


