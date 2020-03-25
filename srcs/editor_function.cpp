#include "aha.h"

void save_map(Data param)
{
	c_editor_mode* render = param.acces<c_editor_mode*>(0);
	c_board* board = render->board();
	fstream file = open_file("ressources/maps/saved_map.map", ios_base::out);

	write_on_file(file, render->camera()->pos().str());
	for (size_t i = 0; i < board->edited_voxel().size(); i++)
		write_on_file(file, board->edited_voxel(i).pos.str() + " " + to_string(board->edited_voxel(i).type));
}