#ifndef AHA_INVENTORY_H
#define AHA_INVENTORY_H

#include "aha_item.h"

class c_inventory
{
protected:
	Item ***_content;
	Item **_shortcut;
public:
	c_inventory()
	{
		_content = new Item **[9];
		for (size_t i = 0; i < 9; i++)
		{
			_content[i] = new Item*[4];
			for (size_t j = 0; j < 4; j++)
				_content[i][j] = nullptr;
		}
		_shortcut = new Item*[9];
		for (size_t i = 0; i < 9; i++)
			_shortcut[i] = nullptr;
	}
	void set_item(int pos_x, int pos_y, Item* p_item)
	{
		if (pos_x == -1)
			_shortcut[pos_y] = p_item;
		else
			_content[pos_x][pos_y] = p_item;
	}
	Item*** content() { return (_content); }
	Item** content(size_t index) { size_t second = index / 4; size_t first = (index - second * 4); return (&(_content[first][second])); }
	Item** short_cut() { return (_shortcut); }
	Item** short_cut(size_t index) { return (&(_shortcut[index])); }
};

#endif