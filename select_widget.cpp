#include "select_widget.h"

Select_Widget::Select_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable,int _id, std::vector<std::string>_menu, int _viewable):Widget(_beg_x, _beg_y, _end_x, _end_y,_focusable,_id)
{
    type = "Select";
    viewable = _viewable;
    menu = _menu;
    selected = menu[0];
    menu.erase(menu.begin());
}

std::string Select_Widget::get_value()
{
    return selected;
}

void Select_Widget::opener(int posx, int posy)
{
    if(posx>=end_x-((end_x-beg_x)*rate)+margin && posx<=end_x-margin && posy>=beg_y+margin && posy<=end_y-margin)
    {
        if(open_counter%2==0)
        {
            opened = true;
        }
        else
        {
            opened = false;
        }

        ++open_counter;
    }
}
void Select_Widget::event_handler(genv::event &e)
{

    if(e.type == genv::ev_mouse && e.button == genv::btn_left)
    {
        if(infocus(e.pos_x,e.pos_y))
        {
            setfocused(true);
        }
        else
        {

            setfocused(false);
        }
        on_click(e.pos_x,e.pos_y);

    }
    if(e.type == genv::ev_mouse && e.button == genv::btn_wheelup)
    {
        if(getfocused()||getopened())
        {
            bowl_up();
        }
    }

    if(e.type == genv::ev_mouse && e.button ==genv::btn_wheeldown)
    {
        if(getfocused()||getopened())
        {
            bowl_do();
        }
    }
    draw();
}

bool Select_Widget::was_action()
{
    return newselected;
    new_selected(false);
}
void Select_Widget::new_selected(bool tmp)
{
    newselected = tmp;
}

void Select_Widget::draw()
{
    if(focused)
        margin = 5;
    else
        margin = 3;
    int up_c = 210;
    genv::gout<<genv::move_to(beg_x,beg_y)
              <<genv::color(0,0,0)        //NAGY DOBOZ
              <<genv::box_to(end_x,end_y)
              <<genv::move_to(beg_x+margin,beg_y+margin)
              <<genv::color(210,210,210)
              <<genv::box_to(end_x-margin,end_y-margin);

    genv::gout<<genv::move_to(end_x-(end_x-beg_x)*rate,beg_y)
              <<genv::color(0,0,0)              //ELVÁLASZTÓ
              <<genv::box_to(end_x,end_y);

    genv::gout<<genv::move_to(end_x-((end_x-beg_x)*rate)+margin,beg_y+margin) //LENYÍTÓ
              <<genv::color(20,200,20)
              <<genv::box_to(end_x-margin,end_y-margin);


        int tmpcharsize = (end_y-beg_y)/2;
        genv::gout.load_font("LiberationSans-Regular.ttf", tmpcharsize);  //ÉRTÉK
        int tmpvaluesize = genv::gout.twidth(selected);
        genv::gout<<genv::color(0,0,0)
            <<genv::move_to(((end_x-(end_x-beg_x)*rate-beg_x)-tmpvaluesize)/2+beg_x,((end_y-beg_y)-tmpcharsize)/2+beg_y)
            <<genv::text(selected);



    menu_draw();

}
void Select_Widget::menu_draw()
{
    if(opened)
    {
        int boxh = end_y-beg_y;
        int boxw = end_x-beg_x;
        int tmpcharsize = (end_y-beg_y)/2;
        int tmpvaluesize = selected.size();
        int rate = 0.2;
        for(int i = 1; i <= viewable; ++i)
        {
            genv::gout<<genv::color(210,210,210);
            genv::gout<<genv::move_to(beg_x,beg_y+i*boxh+i*m_margin);
            genv::gout<<genv::box(boxw,boxh);
            genv::gout<<genv::color(0,0,0);
            tmpvaluesize = genv::gout.twidth(menu[i-1]);
            genv::gout<<genv::move_to(((end_x-(end_x-beg_x)*rate-beg_x)-tmpvaluesize)/2+beg_x,((end_y-beg_y)-tmpcharsize)/2+beg_y+i*boxh+i*m_margin)
            <<genv::text(menu[i-1]);
        }
    }
}
void Select_Widget::on_click(int pos_x, int pos_y)
{
    opener(pos_x, pos_y);
    if(opened)
        selector(pos_x, pos_y);
}
void Select_Widget::setmenu(bool tmp)
{
    opened = tmp;
}


void Select_Widget::bowl_up()
{
    int tmp = menu.size()-1;
    std::string stmp = menu[tmp];
    menu.pop_back();
    menu.insert(menu.begin(),stmp);

}
void Select_Widget::bowl_do()
{
    std::string stmp = menu[0];
    menu.erase(menu.begin());
    menu.push_back(stmp);
}
void Select_Widget::select(int tmp)
{
    std::string stmp = selected;
    selected = menu[tmp];
    menu.erase(menu.begin()+tmp);
    menu.insert(menu.begin()+tmp,stmp);
}
void Select_Widget::selector(int posx, int posy)
{
    int tmp;
    if(posx<=end_x && posx>= beg_x && posy> end_y && posy<=viewable*(end_y-beg_y)+viewable*m_margin+end_y)
    {
        int tmp2 = posy-end_y;
        int tmp3 = end_y-beg_y;
        tmp = tmp2/tmp3;
        select(tmp);
        opened = false;
        ++open_counter;
        newselected = true;
    }
}
bool Select_Widget::getfocused()
{
    return focused;
}
bool Select_Widget::getopened()
{
    return opened;
}


