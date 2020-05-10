

#include "textholder_widget.h"
TextHolder_Widget::TextHolder_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable,int _id, std::string _textin, int _r, int _g, int _b, int _margin):Widget(_beg_x, _beg_y, _end_x, _end_y,_focusable, _id)
{
    type = "TextHolder";
        r = _r;
        g = _g;
        b = _b;
        textin = _textin;
        margin = _margin;
}
void TextHolder_Widget::textsetter(std::string newtext)
{
    textin = newtext;
}
std::string TextHolder_Widget::get_value()
{
    return "TEXTHOLDER VAGYOK";
}


void TextHolder_Widget::event_handler(genv::event &e)
{
        draw();
}

void TextHolder_Widget::draw()
{
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


