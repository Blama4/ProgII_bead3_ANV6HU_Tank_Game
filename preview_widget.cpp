#include "preview_widget.h"
Preview_Widget::Preview_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable,int _id, std::string _inputkep,int _r, int _g, int _b, bool _enemy):Widget(_beg_x, _beg_y, _end_x, _end_y,_focusable,_id)
{
    type = "Preview";
    r = _r;
    g = _g;
    b = _b;
    inputkep = _inputkep;
    enemy = _enemy;
    draw();
}
void Preview_Widget::inputkepsetter(std::string newinput)
{
    inputkep = newinput;
}
std::string Preview_Widget::get_value()
{
    return "PREVIEW VAGYOK";
}
void Preview_Widget::event_handler(genv::event &e)
{
    draw();
}
void Preview_Widget::draw()
{
    genv::gout<<genv::move_to(beg_x,beg_y)
              <<genv::color(0,0,0)        //NAGY DOBOZ
              <<genv::box_to(end_x,end_y)
              <<genv::move_to(beg_x+margin,beg_y+margin)
              <<genv::color(r,g,b)
              <<genv::box_to(end_x-margin,end_y-margin);
    int tank1_sx, tank1_sy;
    std::ifstream f;
    f.open(inputkep.c_str());

    if(!f.good())
    {
        genv::gout<<genv::color(0,0,0)<<genv::text("KEPBEOLVASAS SIKERTELEN: "+inputkep);
    }
    else
    {
        f>>tank1_sx>>tank1_sy;
        int offset_x = ((end_x-beg_x)-tank1_sx)/2+beg_x;
        int offset_y = ((end_y-beg_y)-tank1_sy)/2+beg_y;;
        for(int i = 0; i<tank1_sy; ++i)
        {
            int r,g,b;
            for(int y = 0; y<tank1_sx; ++y)
            {
                if(!enemy)
                {
                    f>>r>>g>>b;
                    genv::gout<<genv::move_to(y+offset_x,i+offset_y)<<genv::color(r,g,b)<<genv::dot;
                }
                else
                {
                    f>>r>>g>>b;
                    if(r>200)
                    {
                        r=0;
                        b=255;
                    }
                    genv::gout<<genv::move_to(((tank1_sx-y)+offset_x),i+offset_y)<<genv::color(r,g,b)<<genv::dot;
                }
            }
        }
    }

}


