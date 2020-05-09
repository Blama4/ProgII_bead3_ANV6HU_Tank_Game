#include "numeric_widget.h"

void Num_Widget::valuesetter(bool inc, int ext)
{
        if(inc && value<=max_value-ext)
        {
            value+=ext;
        }
        if(!inc && value>=min_value+ext)
        {
            value-=ext;
        }
}
std::string Num_Widget::get_value()
{
    std::stringstream tmp;
    std::string tmp2;
    tmp<<value;
    tmp>>tmp2;
    return tmp2;
}

bool Num_Widget::inc(int pos_x, int pos_y)
{
    if(pos_x <=end_x-margin &&
                pos_x>=end_x-((end_x-beg_x)*rate)+margin &&
                pos_y<=beg_y+(end_y-beg_y)/2-margin/2 &&
                pos_y>=beg_y+margin)
        {
            return true;
        }
        else
        {
            return false;
        }
}
bool Num_Widget::dec(int pos_x, int pos_y)
{
        if(pos_x<=end_x-margin &&
                pos_x>=end_x-((end_x-beg_x)*rate)+ margin &&
                pos_y>=beg_y+(end_y-beg_y)/2+margin/2 &&
                pos_y<=end_y-margin)


            return true;
        else
            return false;
}
Num_Widget::Num_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable, int _value, int _max_value, int _min_value):Widget(_beg_x, _beg_y, _end_x, _end_y,_focusable)
{
    type = "Numeric";
        max_value = _max_value;
        min_value = _min_value;
        if(_value>_min_value)
        {
            value = _value;
        }
        else
        {
            value = (_min_value+max_value)/2;
        }
}
void Num_Widget::event_handler(genv::event &e)
{
    if(e.type == genv::ev_mouse && e.button == genv::btn_left)
        {

            setfocused(false);
            if(infocus(e.pos_x,e.pos_y))
            {
                setfocused(true);
            }
            on_click(e.pos_x,e.pos_y);
        }
        if(e.type == genv::ev_key && e.keycode ==  genv::key_pgup)
        {

            if(getfocused())
                valuesetter(1,10);
        }
        if(e.type == genv::ev_key && e.keycode ==  genv::key_pgdn)
        {

            if(getfocused())
                valuesetter(0,10);
        }
        if(e.type == genv::ev_key && e.keycode == genv::key_up )
        {

            if(getfocused())
                valuesetter(1,1);
        }
        if(e.type == genv::ev_key && e.keycode == genv::key_down )
        {

            if(getfocused())
                valuesetter(0,1);
        }

        draw();
}
bool Num_Widget::getfocused()
{
    return focused;
}
void Num_Widget::on_click(int pos_x, int pos_y)
{
    if(focused)
        {
            if(inc(pos_x,pos_y)||dec(pos_x,pos_y))
            {
                valuesetter(inc(pos_x,pos_y),1);
            }
        }
}
void Num_Widget::draw()
{
    if(focused)
            margin = 5;
        else
            margin = 3;
        std::string value_s;
        std::stringstream ss;
        ss<<value;
        ss>>value_s;

        genv::gout<<genv::move_to(beg_x,beg_y)
            <<genv::color(0,0,0)        //NAGY DOBOZ
            <<genv::box_to(end_x,end_y)
            <<genv::move_to(beg_x+margin,beg_y+margin)
            <<genv::color(210,210,210)
            <<genv::box_to(end_x-margin,end_y-margin);
        genv::gout<<genv::move_to(end_x-(end_x-beg_x)*rate,beg_y)
            <<genv::color(0,0,0)              //ELVÁLASZTÓ
            <<genv::box_to(end_x,end_y);
        genv::gout<<genv::move_to(end_x-((end_x-beg_x)*rate)+margin,beg_y+margin) //FELSÕLÉPTETÕ
            <<genv::color(up_c,up_c,up_c)
            <<genv::box_to(end_x-margin,beg_y+(end_y-beg_y)/2-margin/2);
        genv::gout<<genv::move_to(end_x-((end_x-beg_x)*rate)+margin,beg_y+(end_y-beg_y)/2+margin/2) //ALSÓLÉPTETÕ
            <<genv::color(do_c,do_c,do_c)
            <<genv::box_to(end_x-margin,end_y-margin);
        genv::gout<<genv::move_to(end_x-((end_x-beg_x)*rate)+2*margin,beg_y+(end_y-beg_y)/2-2*margin) //FELSÕNYÍL
            <<genv::color(0,0,0)
            <<genv::line_to(end_x-((end_x-beg_x)*rate)+(end_x-(end_x-((end_x-beg_x)*rate)))/2,beg_y+2*margin)
            <<genv::line_to(end_x-2*margin,beg_y+(end_y-beg_y)/2-2*margin);
        genv::gout<<genv::move_to(end_x-((end_x-beg_x)*rate)+2*margin,beg_y+(end_y-beg_y)/2+2*margin) //ALSÓNYÍL
            <<genv::color(0,0,0)
            <<genv::line_to(end_x-((end_x-beg_x)*rate)+(end_x-(end_x-((end_x-beg_x)*rate)))/2,end_y-2*margin)
            <<genv::line_to(end_x-2*margin,beg_y+(end_y-beg_y)/2+2*margin);

            /*
        int tmpcharsize = (end_y-beg_y)/2;
        int tmpvaluesize = value_s.size();
        genv::gout.load_font("LiberationSans-Regular.ttf", tmpcharsize);  //ÉRTÉK
        genv::gout<<genv::color(0,0,0)
            <<genv::move_to(((end_x-(end_x-beg_x)*rate)-beg_x)/2+beg_x-tmpvaluesize*(tmpcharsize*0.2),(end_y-beg_y)/2+beg_y-tmpcharsize/2)
            <<genv::text(value_s);
            */

        int tmpcharsize = (end_y-beg_y)/2;
        genv::gout.load_font("LiberationSans-Regular.ttf", tmpcharsize);  //ÉRTÉK
        int tmpvaluesize = genv::gout.twidth(value_s);
        genv::gout<<genv::color(0,0,0)
            <<genv::move_to(((end_x-(end_x-beg_x)*rate-beg_x)-tmpvaluesize)/2+beg_x,((end_y-beg_y)-tmpcharsize)/2+beg_y)
            <<genv::text(value_s);
}


