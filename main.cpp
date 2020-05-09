#include "graphics.hpp"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "widget.h"
#include "numeric_widget.h"
#include "select_widget.h"
#include "background_widget.h"
#include "button_widget.h"
#include "textholder_widget.h"
#include "preview_widget.h"
using namespace genv;
using namespace std;

const int X = 1440;
const int Y = 800;
const double pi = 3.1415;

struct Game_Master
{
    vector<Widget*>Wid;
    Game_Master()
    {
        Background_Widget* ba1 = new Background_Widget(0,0,X,Y,false,3,168, 208,237);
        Background_Widget* ba2 = new Background_Widget(0+3,Y-100,X-3,Y-3,false,0,102, 255, 51);
        Wid.push_back(ba1);
        Wid.push_back(ba2);
        Button_Widget* bu1 = new Button_Widget(620,200,830,250,true,"Start",0,255,0);
        Button_Widget* bu2 = new Button_Widget(620,300,830,350,true,"Exit",255,0,0);
        Wid.push_back(bu1);
        Wid.push_back(bu2);
        vector<string>tankmenu;
        tankmenu.push_back("tank1");
        tankmenu.push_back("tank2");
        tankmenu.push_back("tank3");
        Select_Widget* s1 = new Select_Widget(300,450,500,500,true,tankmenu,2);
        Select_Widget* s2 = new Select_Widget(940,450,1140,500,true,tankmenu,2);
        Wid.push_back(s1);
        Wid.push_back(s2);
        TextHolder_Widget* te1 = new TextHolder_Widget(250,75,550,135,false,"Player 1",255,255,255,3);
        TextHolder_Widget* te2 = new TextHolder_Widget(900,75,1200,135,false,"Player 2",255,255,255,3);
        Wid.push_back(te1);
        Wid.push_back(te2);
        Preview_Widget* pr1 = new Preview_Widget(275,150,525,400,false,"tank1.kep",168, 208,237,false);
        Preview_Widget* pr2 = new Preview_Widget(915,150,1165,400,false,"tank1.kep",168, 208,237,true);
        Wid.push_back(pr1);
        Wid.push_back(pr2);

    }
    void draw_menu(event ev)
    {
        for(size_t i =0; i<Wid.size(); ++i)
        {
            Wid[i]->event_handler(ev);
        }
        gout<<refresh;
    }
    void check_event_menu(event ev)
    {
        if(ev.type==ev_mouse && ev.button == btn_left)
        {
            for(size_t i =0; i<Wid.size(); ++i)
            {
                if(Wid[i]->get_type()=="Select" && ((Select_Widget*)Wid[i])->was_action())
                {
                    ((Select_Widget*)Wid[i])->new_selected(false);
                    for(size_t j =0; j<Wid.size(); ++j)
                    {
                        if(Wid[j]->get_type()=="Preview" && i%2==j%2)
                        {
                            ((Preview_Widget*)Wid[j])->inputkepsetter(Wid[i]->get_value()+".kep");
                        }
                    }
                }
            }
        }

    }
    bool menu = true;


};





int main()
{
    gout.open(X,Y);
    event ev;
    gin.timer(20);
    Game_Master *game = new Game_Master();

    while(gin >> ev && ev.keycode != key_escape)
    {
        if (ev.type != ev_timer)
        {
            game->draw_menu(ev);
        }
        game->check_event_menu(ev);
    }
    return 0;
}
