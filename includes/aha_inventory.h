#ifndef AHA_INVENTORY_H
#define AHA_INVENTORY_H

struct Item
{
	int id;

	Item(int p_id = -1)
	{
		id = p_id;
	}
};

class c_inventory
{
protected:
	Item **_content;
	Item *_shortcut;
public:
	c_inventory()
	{
		_content = new Item *[9];
		for (size_t i = 0; i < 9; i++)
		{
			_content[i] = new Item[4];
			for (size_t j = 0; j < 4; j++)
				_content[i][j] = Item();
		}
		_shortcut = new Item[9];
		for (size_t i = 0; i < 9; i++)
			_shortcut[i] = Item();
	}
	Item **content() { return (_content); }
	Item* content(size_t index) { size_t second = index / 4; size_t first = (index - second * 4); return (&(_content[first][second])); }
	Item* short_cut() { return (_shortcut); }
	Item* short_cut(size_t index) { return (&(_shortcut[index])); }
};

#endif