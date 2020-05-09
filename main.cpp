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


struct Tank
{
protected:
    int beg_x;
    int end_x;
    int beg_y;
    int end_y;
    string filename;
    int max_deg;
    int min_deg;
    int max_speed;
    int min_speed;
    bool enemy;
    canvas can;
public:
    Tank(int _beg_x,int _end_x,int _beg_y,int _end_y,int _max_deg,int _min_deg,int _max_speed,int _min_speed,string _filename, bool _enemy)
    {
        beg_x = _beg_x;
        end_x = _end_x;
        beg_y = _beg_y;
        end_y = _end_y;
        max_deg = _max_deg;
        min_deg = _min_deg;
        max_speed = _max_speed;
        min_speed = _min_speed;
        filename = _filename;
        enemy = _enemy;

        int tmpx;
        int tmpy;
        ifstream f;
        f.open(filename.c_str());
        f>>tmpx>>tmpy;
        can.open(tmpx,tmpy);
        for(int i = 0; i<tmpy; ++i)
        {
            int r,g,b;
            for(int y = 0; y<tmpx; ++y)
            {
                if(!enemy)
                {
                    f>>r>>g>>b;

                    can<<move_to(y,i)<<color(r,g,b)<<dot;
                }
                else
                {
                    f>>r>>g>>b;
                    if(r>200)
                    {
                        r=0;
                        b=255;
                    }
                    can<<move_to(((tmpx-1-y)),i)<<color(r,g,b)<<dot;
                }
            }
        }
    }
    canvas GetTankCanvas()
    {
        return can;
    }

};

class Game_Master
{
    bool menu = true;
    vector<Widget*>Wid;
    vector<Widget*>GameWid;
    vector<Tank*>Tanks;

public:
    Game_Master()
    {
        Background_Widget* ba1 = new Background_Widget(0,0,X,Y,false,3,168, 208,237);
        Background_Widget* ba2 = new Background_Widget(0+3,Y-100,X-3,Y-3,false,0,102, 255, 51);
        Wid.push_back(ba1);
        Wid.push_back(ba2);
        GameWid.push_back(ba1);
        GameWid.push_back(ba2);
        Button_Widget* bu1 = new Button_Widget(620,200,830,250,true,"Start",0,255,0,1);
        Button_Widget* bu2 = new Button_Widget(620,300,830,350,true,"Exit",255,0,0,2);
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
        GameWid.push_back(te1);
        GameWid.push_back(te2);

        Preview_Widget* pr1 = new Preview_Widget(275,150,525,400,false,"tank1.kep",168, 208,237,false);
        Preview_Widget* pr2 = new Preview_Widget(915,150,1165,400,false,"tank1.kep",168, 208,237,true);
        Wid.push_back(pr1);
        Wid.push_back(pr2);

        Num_Widget* nu1 = new Num_Widget(50,200,250,250,true,45,85,20);
        Num_Widget* nu2 = new Num_Widget(50,275,250,325,true,100,180,20);
        Num_Widget* nu3 = new Num_Widget(1190,200,1390,250,true,45,85,20);
        Num_Widget* nu4 = new Num_Widget(1190,275,1390,325,true,100,180,20);
        GameWid.push_back(nu1);
        GameWid.push_back(nu2);
        GameWid.push_back(nu3);
        GameWid.push_back(nu4);

        Button_Widget* bu3 = new Button_Widget(620,100,820,150,true,"FIRE",255,55,55,3);
        GameWid.push_back(bu3);

        Tank* ta1 = new Tank(50,200,650,700,80,50,200,100,"tank1.kep",false);
        Tank* ta2 = new Tank(50,200,650,700,70,40,180,80,"tank2.kep",false);
        Tank* ta3 = new Tank(50,200,650,700,70,30,120,60,"tank3.kep",true);
        Tanks.push_back(ta1);
        Tanks.push_back(ta2);
        Tanks.push_back(ta3);

    }
    void check_event(event ev)
    {
        if(menu)
        {
            if (ev.type != ev_timer)
            {
                for(size_t i =0; i<Wid.size(); ++i)
                {
                    Wid[i]->event_handler(ev);
                }
                gout<<refresh;
            }
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
                    if(Wid[i]->get_type()=="Button" && ((Button_Widget*)Wid[i])->getfocused())
                    {

                        if(((Button_Widget*)Wid[i])->getid()==1)
                        {
                            menu = false;
                        }
                        else if(((Button_Widget*)Wid[i])->getid()==2)
                        {
                            exit(0);
                        }

                    }
                }
            }
        }
        if(!menu)
        {
            if (ev.type != ev_timer)
            {
                for(size_t i =0; i<GameWid.size(); ++i)
                {
                    GameWid[i]->event_handler(ev);

                }
                canvas c;
                c = Tanks[2]->GetTankCanvas();
                gout<<stamp(c,200,600);
                gout<<refresh;
            }
        }

    }
};

int main()
{
    gout.open(X,Y);
    event ev;
    gin.timer(20);
    Game_Master *game = new Game_Master();

    while(gin >> ev && ev.keycode != key_escape)
    {
        game->check_event(ev);
    }
    return 0;
}
