#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdbool.h>
#include <sstream>


#define	ME		1
#define	OPP 	0
#define	NEUTRAL -1
struct Tile
{
        int     x;
        int     y;
        int     scrap_amount;
        int     owner;
        int     units;
        bool    recycler;
        bool    can_build;
        bool    can_spawn;
        bool    in_range_of_recycler;
};

void	action_spawn(std::vector<std::string> & actions, Tile tile, int amount)
{
	std::ostringstream action;
	action << "SPAWN" << " " << amount << " " << tile.x << " " << tile.y << ";";
	actions.push_back(action.str());
}

void	action_move(std::vector<std::string> & actions, Tile from, Tile to, int amount)
{
	std::ostringstream action;
	action << "MOVE" << " " << amount << " " 
		<< from.x << " " << from.y << " "
		<< to.x << " " << to.y << ";";
	actions.push_back(action.str());
}

void	action_build(std::vector<std::string> & actions, Tile tile)
{
	std::ostringstream action;
	action << "SPAWN" << " " << tile.x << " " << tile.y << ";";
	actions.push_back(action.str());
}

void	execute_order_66(std::vector<std::string> & actions)
{
	if (actions.empty() == true)
		std::cout << "WAIT;";
	else
	{
		for (std::vector<std::string>::iterator it = actions.begin(); it != actions.end(); it++)
			std::cout << *it;
		
	}
	std::cout << std::endl;
}

int main()
{
    int width; //x map
    int height; //y map
    std::cin >> width >> height; std::cin.ignore();

/*------------------------------------------------------------------------------------------------------------------------------------------*/

    while (42) 
    {
        int my_matter; //ressource alliée
        int opp_matter; //ressource adverse
        std::cin >> my_matter >> opp_matter; std::cin.ignore();

		std::vector<Tile>			tiles;
		std::vector<Tile>			my_tiles;
		std::vector<Tile>			opp_tiles;
		std::vector<Tile>			neutral_tiles;
		std::vector<Tile>			my_units;
		std::vector<Tile>			opp_units;
		std::vector<Tile>			my_recyclers;
		std::vector<Tile>			opp_recycler;
		// tiles.reserve(width * height);
		std::vector<std::string>	actions;

/*------------------------------------------------------------------------------------------------------------------------------------------*/

        //init tiles
        for (int i = 0; i < height; i++) 
		{
            for (int j = 0; j < width; j++) 
			{
                int scrap_amount;   //if 0 = grass
                int owner;          // 1 = me, 0 = foe, -1 = neutral
                int units;          //nb units by owner
                int recycler;       // 1 if recycleur. owned by owner / else 0
                int can_build;      // 1 if allow to build / else 0
                int can_spawn;      //1 if allow to spawn / else 0
                int in_range_of_recycler; //1 if in range / else 0
                std::cin >> scrap_amount >> owner >> units >> recycler >> can_build >> can_spawn >> in_range_of_recycler; std::cin.ignore();

				Tile tile = {i, j, scrap_amount, owner, units, recycler == true, can_build == true, can_spawn == true, in_range_of_recycler == true};
				
				tiles.push_back(tile);

				if (tile.owner == ME)
				{
					my_tiles.push_back(tile);
					if (tile.units > 0)
						my_units.push_back(tile);
					else if (tile.recycler == true)
						my_recyclers.push_back(tile);
				}
				else if (tile.owner == OPP)
					opp_tiles.push_back(tile);
					if (tile.units > 0)
						opp_units.push_back(tile);
					else if (tile.recycler == true)
						opp_recycler.push_back(tile);
				else if (tile.owner == NEUTRAL)
					neutral_tiles.push_back(tile);
            }
        }

/*------------------------------------------------------------------------------------------------------------------------------------------*/

		//algo elimination des jedis

		
		
		


/*------------------------------------------------------------------------------------------------------------------------------------------*/

        execute_order_66(actions);
        std::cerr << "HALOA" << std::endl;


    }
}
