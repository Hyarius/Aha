#include "aha.h"

Item::Item(int p_id, int p_icon)
{
	type = item_type::error;
	id = p_id;
	icon = p_icon;
}

Block_item::Block_item(int p_id, int p_icon, int p_block_id) : Item(p_id, p_icon)
{
	type = item_type::block;
	block_id = p_block_id;
}

void Block_item::use(Data data)
{
	if (data.content.size() == 0)
		return;

	c_game_engine* engine = data.acces<c_game_engine*>(0);
	Vector3* coord = data.acces<Vector3*>(1);

	engine->board()->add_voxel(*coord, block_id);
}