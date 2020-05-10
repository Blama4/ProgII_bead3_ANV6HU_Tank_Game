#include "background_widget.h"

Background_Widget::Background_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable,int _id, int _margin, int _r, int _g, int _b):Widget(_beg_x, _beg_y, _end_x, _end_y,_focusable, _id)
{
    type = "Background";
        r = _r;
        g = _g;
        b = _b;
        margin = _margin;
}
void Background_Widget::event_handler(genv::event &e)
{
        draw();
}

void Background_Widget::draw()
{
    if(margin>0)
    {
        genv::gout<<genv::move_to(beg_x,beg_y)
            <<genv::color(0,0,0)
            <<genv::box_to(end_x-1,end_y-1)
            <<genv::move_to(beg_x+margin,beg_y+margin)
            <<genv::color(r,g,b)
            <<genv::box_to(end_x-margin,end_y-margin);
    }
    else
    {
        genv::gout<<genv::move_to(beg_x,beg_y)
            <<genv::color(r,g,b)
            <<genv::box_to(end_x-1,end_y-1);
    }

}
std::string Background_Widget::get_value()
{
    return "HÁTTÉR VAGYOK";
}


