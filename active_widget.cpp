#include "active_widget.h"
Active_Widget::Active_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable, int _id, bool _active, int _r, int _g, int _b):Widget(_beg_x, _beg_y, _end_x, _end_y,_focusable, _id)
{
    type = "Active";
        r = _r;
        g = _g;
        b = _b;
        active = _active;
}

std::string Active_Widget::get_value()
{
    return "ACTIVE VAGYOK";
}


void Active_Widget::event_handler(genv::event &e)
{
        draw();
}
bool Active_Widget::getfocused()
{
    return focused;
}
bool Active_Widget::getactive()
{
    return active;
}
void Active_Widget::setactive(bool inac)
{
    active = inac;
}

void Active_Widget::draw()
{
            margin = 3;

        genv::gout<<genv::move_to(beg_x,beg_y)
            <<genv::color(0,0,0)        //NAGY DOBOZ
            <<genv::box_to(end_x,end_y)
            <<genv::move_to(beg_x+margin,beg_y+margin)
            <<genv::color(220,220,220)
            <<genv::box_to(end_x-margin,end_y-margin);
            if(active)
            {
            genv::gout<<genv::move_to(beg_x+margin*3,beg_y+margin*3)
            <<genv::color(r,g,b)
            <<genv::box_to(end_x-margin*3,end_y-margin*3);
            }
}


