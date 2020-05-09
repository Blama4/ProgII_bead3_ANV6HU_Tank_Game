
#include "button_widget.h"
Button_Widget::Button_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable, std::string _textin, int _r, int _g, int _b):Widget(_beg_x, _beg_y, _end_x, _end_y,_focusable)
{
    type = "Button";
        r = _r;
        g = _g;
        b = _b;
        textin = _textin;
}
void Button_Widget::textsetter(std::string newtext)
{
    textin = newtext;
}
std::string Button_Widget::get_value()
{
    return "GOMB VAGYOK";
}


void Button_Widget::event_handler(genv::event &e)
{
    if(e.type == genv::ev_mouse && e.button == genv::btn_left)
        {

            setfocused(false);
            if(infocus(e.pos_x,e.pos_y))
            {
                setfocused(true);
            }
        }
        draw();
}
bool Button_Widget::getfocused()
{
    return focused;
}
void Button_Widget::draw()
{
    if(focused)
            margin = 5;
        else
            margin = 3;

        genv::gout<<genv::move_to(beg_x,beg_y)
            <<genv::color(0,0,0)        //NAGY DOBOZ
            <<genv::box_to(end_x,end_y)
            <<genv::move_to(beg_x+margin,beg_y+margin)
            <<genv::color(r,g,b)
            <<genv::box_to(end_x-margin,end_y-margin);

        int tmpcharsize = (end_y-beg_y)/2;
        genv::gout.load_font("LiberationSans-Regular.ttf", tmpcharsize);  //ÉRTÉK
        int tmpvaluesize = genv::gout.twidth(textin);
        genv::gout<<genv::color(0,0,0)
            <<genv::move_to(((end_x-beg_x)-tmpvaluesize)/2+beg_x,((end_y-beg_y)-tmpcharsize)/2+beg_y)
            <<genv::text(textin);
}


