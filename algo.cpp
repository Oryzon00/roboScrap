#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdbool.h>
#include <sstream>
#include <cstdlib>


#define	ME		1
#define	OPP 	0
#define	NEUTRAL -1

/*------------------------------------------------------------------------------------------------------------------------------------------*/

struct	Data
{
	int							width;
	int							height;
	int							turn;
	int 						my_matter;
	int							opp_matter;
	Tile 						spawn_ally;
	Tile 						spawn_opp;
	std::vector<Tile>			tiles;
	std::vector<Tile>			my_tiles;
	std::vector<Tile>			opp_tiles;
	std::vector<Tile>			neutral_tiles;
	std::vector<Tile>			my_units;
	std::vector<Tile>			opp_units;
	std::vector<Tile>			my_recyclers;
	std::vector<Tile>			opp_recycler;
	std::vector<std::string> 	actions;
};


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
	Tile	*North;
};

//faire un Tile** pour la map ?

//fonction utils:// point de spawn case adverse
			// is_reachable ?

/*------------------------------------------------------------------------------------------------------------------------------------------*/

bool	is_empty(Tile & tile)
{
	if (tile.units == 0 && tile.recycler == false)
		return (true);
	else
		return (false);
}

bool	is_next_to(Tile & tile1, Tile & tile2)
{
	if ( (tile1.x == tile2.x) && (abs(tile1.y - tile2.y) == 1) )
		return (true);
	if ( (abs(tile1.x - tile2.x) == 1) && (tile1.y == tile2.y) )
		return (true);
	return (false);
}

/*------------------------------------------------------------------------------------------------------------------------------------------*/

void	init_spawn_ally(Tile & spawn_ally, std::vector<Tile> & tiles)
{
	for(std::vector<Tile>::iterator it = tiles.begin(); it != tiles.end(); it++)
	{
		if ((*it).owner == ME && is_empty(*it) == true)
			spawn_ally = *it;
	}
}

void	init_spawn_opp(Tile & spawn_opp, std::vector<Tile> & tiles)
{
	for(std::vector<Tile>::iterator it = tiles.begin(); it != tiles.end(); it++)
	{
		if ((*it).owner == OPP && is_empty(*it) == true)
			spawn_opp = *it;
	}
}

void	init_spawn(Data & data)
{
	init_spawn_ally(data.spawn_ally, data.tiles);
	init_spawn_opp(data.spawn_opp, data.tiles);
}

/*------------------------------------------------------------------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------------------------------------------------------------------*/

bool	check_opp_tile_dangerous(Tile & my_tile, std::vector<Tile> & opp_tiles)
{
	for (auto it = opp_tiles.begin(); it != opp_tiles.end(); it++)
	{
		if ((*it).units > 0 && is_next_to(my_tile, *it) == true)
			return (true);
	}
	return (false);
}

void	ligne_maginot(Data & data)
{
	
	for(std::vector<Tile>::iterator it = data.my_tiles.begin(); it != data.my_tiles.end(); it++)
	{
		if (is_empty(*it) == true && check_opp_tile_dangerous(*it, data.opp_tiles) == true)
			action_build(data.actions, *it);
	}
}

/*------------------------------------------------------------------------------------------------------------------------------------------*/

//

//tile_farm
	// tile allié et vide
	// tile North / Sud / West / East --> scrap amount > tile central

bool	check_scrap_NSWE(Tile & tile, std::vector<Tile> & tiles)
{
	
}

void	farming_opti(Data & data)
{
	for (auto it = data.my_tiles.begin(); it != data.my_tiles.end(); it++)
	{
		if (is_empty(*it) == true && check_scrap_NSWE())
	}
}

Data	update_data(Data & data, std::vector<Tile> tiles, std::vector<Tile> my_tiles, std::vector<Tile> opp_tiles, 
					std::vector<Tile> neutral_tiles, std::vector<Tile> my_units, std::vector<Tile> opp_units, 
					std::vector<Tile> my_recyclers, std::vector<Tile> opp_recycler, std::vector<std::string> actions, int turn)
{
	data.tiles = tiles;
	data.my_tiles = my_tiles;
	data.opp_tiles = opp_tiles;
	data.neutral_tiles = neutral_tiles;
	data.my_units = my_units;
	data.opp_units = opp_units;
	data.my_recyclers = my_recyclers;
	data.opp_recycler = opp_recycler;
	data.actions = actions;
	data.turn = turn;
}

void	init_data(Data & data, int width, int height, int turn, Tile spawn_ally, Tile spawn_opp)
{
	data.width = width;
	data.height = height;
	data.turn = turn;
	data.spawn_ally = spawn_ally;
	data.spawn_opp = spawn_opp;
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
    int 	width; //x map
    int 	height; //y map
    std::cin >> width >> height; std::cin.ignore();
	int 	turn = 1;
	Tile	spawn_ally;
	Tile	spawn_opp;
	Data	data; 
	init_data(data, width, height, turn, spawn_ally, spawn_opp);


/*------------------------------------------------------------------------------------------------------------------------------------------*/

    while (42) 
    {
        int my_matter; 
        int opp_matter; 
        std::cin >> my_matter >> opp_matter; std::cin.ignore();

		std::vector<Tile>			tiles;
		std::vector<Tile>			my_tiles;
		std::vector<Tile>			opp_tiles;
		std::vector<Tile>			neutral_tiles;
		std::vector<Tile>			my_units;
		std::vector<Tile>			opp_units;
		std::vector<Tile>			my_recyclers;
		std::vector<Tile>			opp_recycler;
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
		if (turn == 1)
			init_spawn(data);
		update_data(data, tiles, my_tiles, opp_tiles, neutral_tiles, my_units, opp_units, my_recyclers, opp_recycler, actions, turn);

/*------------------------------------------------------------------------------------------------------------------------------------------*/
	
		ligne_maginot(data);
		if (turn <= 7)
			farming_opti(data);
		
		

		
		
/*------------------------------------------------------------------------------------------------------------------------------------------*/
		
// Move --> pathfinding automatique
// Build --> 10 scrap --> sur case controlée libre
// Spawn --> 10 scrap /robot --> sur case controlée
//algo elimination des jedis

	//fonction pour s'etendre nord/sud durant rush initial
// fonction: rush B + spread fumi
	// avance vers case adversaire avec unité > 0

// fonction: splatoon
	//fonction qui detecte si case est attaignable ?
		//pathfinding ?






//spread
	// if je suis le 1er
		// --> if ligne non bloque deplacement + x
		// --> else if ligne bloque deplacement + y


//init x 
	// if spawn x adversaire > spawn x ally 
		// x = 1
	// else
		// x = -1

//init y 
	// if spawn y adv == spawn y ally
		// if  spawn y ally > height / 2
			// y = -1
		//else
			//y = 1
	// else if spawn y adv > spawn y ally
		// y = 1
	// else
		// y = -1


/*------------------------------------------------------------------------------------------------------------------------------------------*/

        execute_order_66(data.actions);
        std::cerr << "HALOA" << std::endl;

		turn++;
    }
}
