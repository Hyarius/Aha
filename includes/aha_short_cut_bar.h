#ifndef AHA_SHORT_CUT_BAR_H
#define AHA_SHORT_CUT_BAR_H

class c_shortcut_bar : public c_widget
{
protected:
	int _index;
	int _old_index;
	c_player* _player;
	c_item_slot* _shortcut[9];

public:
	Vector2 calc_slot_pos(int nb)
	{
		float size = 70.0f;
		float space = 10.0f;
		float tot_size = (size + space) * 8 + size;
		Vector2 pos = Vector2(g_application->size().x / 2.0f - tot_size / 2 + (size + space) * nb, g_application->size().y - (space + size));
		return (pos);
	}
	c_shortcut_bar(c_player* p_player,  c_widget* p_parent = nullptr) : c_widget(p_parent)
	{
		_index = 0;
		_old_index = 1;
		_player = p_player;
		for (int i = 0; i < 9; i++)
		{
			_shortcut[i] = new c_item_slot(_player->inventory()->short_cut(i), this);
			Vector2 pos = calc_slot_pos(i);
			_shortcut[i]->set_geometry(pos, 70.0f);
			_shortcut[i]->activate();
		}
	}
	Item* get_item() { Item** p_item = _shortcut[_index]->item(); if (p_item == nullptr)return(nullptr);return (*p_item); }
	void edit_selected(int delta)
	{
		_index -= delta;
		while (_index < 0)
			_index += 9;
		while (_index >= 9)
			_index -= 9;
	}
	void update()
	{
		if (_index != _old_index)
		{
			_shortcut[_index]->select();
			_shortcut[_index]->set_geometry(calc_slot_pos(_index) - 5, 80.0f);

			_shortcut[_old_index]->unselect();
			_shortcut[_old_index]->set_geometry(calc_slot_pos(_old_index), 70.0f);
			_old_index = _index;
		}
	}
	void render()
	{

	}
	void set_geometry_imp(Vector2 p_anchor, Vector2 area)
	{

	}
};

#endif