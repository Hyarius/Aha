#include "aha.h"

void save_map(c_game_engine* engine)
{
	c_camera* camera = engine->camera();
	c_player* player = engine->player();
	c_board* board = engine->board();
	fstream file = open_file("ressources/maps/saved_map.map", ios_base::out);

	write_on_file(file, player->name() + " " + player->pos().text());
	write_on_file(file, board->spawn().text());
	for (size_t i = 0; i < board->edited_voxel().size(); i++)
		write_on_file(file, board->edited_voxel(i).pos.text() + " " + to_string(board->edited_voxel(i).type));
}