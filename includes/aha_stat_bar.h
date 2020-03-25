#ifndef AHA_STAT_BAR_H
#define AHA_STAT_BAR_H

#include "jgl.h"

class c_stat_bar : public c_widget
{
private:
	Stat* _stat;

	Color _bar_color;
	w_box_component _box;
	w_text_component _label;
public:
	c_stat_bar(Stat* p_stat, Color p_bar_color, c_widget *p_parent = nullptr) : c_widget(p_parent)
	{
		_stat = p_stat;
		_bar_color = p_bar_color;
		_box = w_box_component(this);
		_label = w_text_component(this, "Text");
		_label.set_align(alignment::centred);
	}
	void render()
	{
		if (is_active() == false)
			return;
		_box.render(_viewport);
		Vector2 pos = _box.anchor() + _box.border();
		float tmp = static_cast<float>(_stat->actual) / static_cast<float>(_stat->max);
		Vector2 size = Vector2((_box.area().x - _box.border() * 2) * tmp, _box.area().y - _box.border() * 2);
		fill_rectangle(pos, size, _bar_color, _viewport);
		_label.set_text(to_string(_stat->actual) + " / " + to_string(_stat->max));
		_label.render(_viewport);
	}
	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		_box.set_area(p_area);
		_box.set_anchor(p_anchor);
		_label.set_area(p_area - _box.border() * 2);
		_label.set_anchor(p_anchor + _box.border());
		_label.calc_text_size(_label.area());
	}
};

#endif