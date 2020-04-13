#ifndef AHA_ITEM_SLOT_H
#define AHA_ITEM_SLOT_H

#include "jgl.h"

#include "aha_inventory.h"

extern c_tileset* icon_tile;

class c_item_slot : public c_widget
{
protected:
	Item** _item;

	w_box_component _box;
public:
	c_item_slot(Item** p_item, c_widget *p_parent = nullptr) : c_widget(p_parent)
	{
		_item = p_item;
		_box = w_box_component(this);
		_box.set_back(Color(90, 90, 90));
		_box.set_front(Color(120, 120, 120));
	}
	Item** item()
	{
		return (_item);
	}
	void render()
	{
		_box.render(_viewport);
		if (_item != nullptr && *_item != nullptr && (*_item)->id != -1)
			icon_tile->draw((*_item)->icon, _box.anchor(), _box.area());
	}
	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		_box.set_anchor(p_anchor);
		_box.set_area(p_area);
	}
	void select()
	{
		_box.set_back(Color(150, 150, 150));
		_box.set_front(Color(190, 190, 190));
	}
	void unselect()
	{
		_box.set_back(Color(90, 90, 90));
		_box.set_front(Color(120, 120, 120));
	}
};

#endif