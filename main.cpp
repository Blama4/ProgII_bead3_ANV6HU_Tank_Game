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
#include "active_widget.h"
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
    int tmpx;
    int tmpy;
    string filename;
    int max_deg;
    int min_deg;
    int max_speed;
    int min_speed;
    bool enemy;
    canvas can;
public:
    Tank(int _max_deg,int _min_deg,int _max_speed,int _min_speed,string _filename, bool _enemy)
    {
        srand (time(NULL));
        filename = _filename;
        enemy = _enemy;

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
        end_y = 700;
        beg_y = end_y-tmpy;
        max_deg = _max_deg;
        min_deg = _min_deg;
        max_speed = _max_speed;
        min_speed = _min_speed;
        beg_x = 0;
    }
    int get_rand_beg_x(bool enemy)
    {
        int randbegx;
        if(!enemy)
        {
            randbegx = rand()%(720-tmpx)+10;
        }
        else
        {
            randbegx = rand()%(720-tmpx)+710;
        }
        return randbegx;
    }
    canvas GetTankCanvas()
    {
        return can;
    }
    int get_beg_x()
    {
        return beg_x;
    }
    int get_beg_y()
    {
        return beg_y;
    }
    int get_end_x()
    {
        return end_x;
    }
    int get_end_y()
    {
        return end_y;
    }
    int get_speed_max()
    {
        return max_speed;
    }
    int get_speed_min()
    {
        return min_speed;
    }
    int get_deg_max()
    {
        return max_deg;
    }
    int get_deg_min()
    {
        return min_deg;
    }
    void set_beg_x(int inbegx)
    {
        beg_x=inbegx;
        end_x =inbegx+tmpx;
    }
};

class Game_Master
{
    bool menu = true;
    bool fire = false;
    bool gameover = false;
    int gravity = 10;
    int bg_time = 0;
    int time = 0;
    int player1 = 0;
    int player2 =0;
    double fire_x =0;
    double fire_y =0;
    double angle = 0;
    double Vo = 0;
    int y_offset = 0;
    int x_offset = 0;
    int firecounter = rand()%20;
    int player1point = 0;
    int player2point = 0;
    vector<Widget*>Wid;
    vector<Widget*>GameWid;
    vector<Tank*>Tanks;

public:
    Game_Master()
    {
        Background_Widget* ba1 = new Background_Widget(0,0,X,Y,false,0,3,168, 208,237);
        Background_Widget* ba2 = new Background_Widget(0+3,Y-100,X-3,Y-3,false,1,0,102, 255, 51);
        Wid.push_back(ba1);
        Wid.push_back(ba2);
        GameWid.push_back(ba1);
        GameWid.push_back(ba2);
        Button_Widget* bu1 = new Button_Widget(620,200,830,250,true,2,"Start",0,255,0);
        Button_Widget* bu2 = new Button_Widget(620,300,830,350,true,3,"Exit",255,0,0);
        Wid.push_back(bu1);
        Wid.push_back(bu2);
        vector<string>tankmenu;
        tankmenu.push_back("tank1");
        tankmenu.push_back("tank2");
        tankmenu.push_back("tank3");
        Select_Widget* s1 = new Select_Widget(300,450,500,500,true,4,tankmenu,2);
        Select_Widget* s2 = new Select_Widget(940,450,1140,500,true,5,tankmenu,2);
        Wid.push_back(s1);
        Wid.push_back(s2);
        TextHolder_Widget* te1 = new TextHolder_Widget(250,75,550,135,false,6,"Player 1",255,255,255,3);
        TextHolder_Widget* te2 = new TextHolder_Widget(900,75,1200,135,false,7,"Player 2",255,255,255,3);
        Wid.push_back(te1);
        Wid.push_back(te2);
        GameWid.push_back(te1);
        GameWid.push_back(te2);

        Preview_Widget* pr1 = new Preview_Widget(275,150,525,400,false,8,"tank1.kep",168, 208,237,false);
        Preview_Widget* pr2 = new Preview_Widget(915,150,1165,400,false,9,"tank1.kep",168, 208,237,true);
        Wid.push_back(pr1);
        Wid.push_back(pr2);

        Num_Widget* nu1 = new Num_Widget(50,200,250,250,true,10,0,85,20);
        Num_Widget* nu2 = new Num_Widget(50,275,250,325,true,11,0,180,20);
        Num_Widget* nu3 = new Num_Widget(1190,200,1390,250,true,12,0,85,20);
        Num_Widget* nu4 = new Num_Widget(1190,275,1390,325,true,13,0,180,20);
        GameWid.push_back(nu1);
        GameWid.push_back(nu2);
        GameWid.push_back(nu3);
        GameWid.push_back(nu4);

        Button_Widget* bu3 = new Button_Widget(620,100,820,150,true,14,"FIRE",255,0,0);
        Button_Widget* bu4 = new Button_Widget(20,20,220,70,true,15,"Menu",100,100,100);
        GameWid.push_back(bu3);
        GameWid.push_back(bu4);

        Active_Widget* ac1 = new Active_Widget(520,160,570,210,false,16,firecounter%2,0,255,0);
        Active_Widget* ac2 = new Active_Widget(870,160,920,210,false,17,firecounter%2+1,0,255,0);
        GameWid.push_back(ac1);
        GameWid.push_back(ac2);

        TextHolder_Widget* te3 = new TextHolder_Widget(685,400,765,450,false,18,"0:0",255,255,255,3);
        Wid.push_back(te3);


        Tank* ta1 = new Tank(85,50,200,100,"tank1.kep",false);
        Tank* ta2 = new Tank(70,40,180,80,"tank2.kep",false);
        Tank* ta3 = new Tank(70,30,120,60,"tank3.kep",false);
        Tank* ta4 = new Tank(85,50,200,100,"tank1.kep",true);
        Tank* ta5 = new Tank(70,40,180,80,"tank2.kep",true);
        Tank* ta6 = new Tank(70,30,120,60,"tank3.kep",true);
        Tanks.push_back(ta1);
        Tanks.push_back(ta2);
        Tanks.push_back(ta3);
        Tanks.push_back(ta4);
        Tanks.push_back(ta5);
        Tanks.push_back(ta6);
    }
    bool fire_logic(int angle, int Vo, int time, int x_offset, int y_offset, bool enemy, int tankbegx, int tankendx, int tankbegy, int tankendy)
    {
        double oldy;
        double oldx;
        double x,y;
        int fire_x = time-bg_time;
        double rad = angle*pi/180;
        double tmp1 = fire_x * tan(rad);
        double tmp2 = gravity/(2*pow(Vo,2)*pow(cos(rad),2));
        double tmp3 = pow(fire_x,2);
        fire_y=Y-(tmp1-tmp2*tmp3)-(Y-y_offset);
        double degree = sin((fire_y-oldy)/(sqrt(pow(fire_x-oldx,2)+pow(fire_y-oldy,2))));
        if(enemy)
        {
            x = X-(X-x_offset)-fire_x;
        }
        else
        {
            x = fire_x+x_offset;
        }
        if(fire_y<=700 && fire_y>=0 && x >=0 && x <=X)
        {
            gout<<move_to(x,fire_y)<<color(0,0,0)<<box(15,15);
        }
        oldy = fire_y;
        oldx = fire_x;
        if(x>=tankbegx && x<=tankendx && fire_y<=tankendy && fire_y>=tankbegy)
        {
            return true;
        }
        else
        {
            return false;
        }


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
                                if(i%2==0)
                                {
                                    string tmp1;
                                    tmp1 = Wid[i]->get_value();
                                    tmp1 = tmp1[tmp1.size()-1];
                                    stringstream ss;
                                    ss<<tmp1;
                                    ss>>player1;
                                    player1=player1-1;
                                }
                                else
                                {
                                    string tmp2;
                                    tmp2 = Wid[i]->get_value();
                                    tmp2 = tmp2[tmp2.size()-1];
                                    stringstream ss;
                                    ss<<tmp2;
                                    ss>>player2;
                                    player2 +=2;
                                }
                            }
                        }
                    }
                    if(Wid[i]->get_type()=="Button" && ((Button_Widget*)Wid[i])->getfocused())
                    {
                        if(Wid[i]->get_id()==2)
                        {
                            menu = false;
                        }
                        else if(Wid[i]->get_id()==3)
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

                if(Tanks[player1]->get_beg_x()==0)  //KEZDÕHELYEK ÉS NUM_WIDGET RANGE BEÁLLÍTÁS
                {
                    if(player2==0)
                    {
                        player2 = 3;
                    }
                    Tanks[player1]->set_beg_x(Tanks[player1]->get_rand_beg_x(false));
                    Tanks[player2]->set_beg_x( Tanks[player2]->get_rand_beg_x(true));
                    for(size_t i =0; i<GameWid.size(); ++i)
                    {
                        if(GameWid[i]->get_type()=="Numeric")
                        {
                            int tmpid = GameWid[i]->get_id();
                            if(tmpid==10)
                            {
                                ((Num_Widget*)GameWid[i])->setrangemax(Tanks[player1]->get_deg_max());
                                ((Num_Widget*)GameWid[i])->setrangemin(Tanks[player1]->get_deg_min());
                            }
                            else if(tmpid == 11)
                            {
                                ((Num_Widget*)GameWid[i])->setrangemax(Tanks[player1]->get_speed_max());
                                ((Num_Widget*)GameWid[i])->setrangemin(Tanks[player1]->get_speed_min());
                            }
                            else if(tmpid == 12)
                            {
                                ((Num_Widget*)GameWid[i])->setrangemax(Tanks[player2]->get_deg_max());
                                ((Num_Widget*)GameWid[i])->setrangemin(Tanks[player2]->get_deg_min());
                            }
                            else if(tmpid == 13)
                            {
                                ((Num_Widget*)GameWid[i])->setrangemax(Tanks[player2]->get_speed_max());
                                ((Num_Widget*)GameWid[i])->setrangemin(Tanks[player2]->get_speed_min());
                            }
                            ((Num_Widget*)GameWid[i])->setvaluecenter();
                        }
                    }
                }
                for(size_t i =0; i<GameWid.size(); ++i)
                {
                    if(GameWid[i]->get_type()=="Button" && ((Button_Widget*)GameWid[i])->getfocused())
                    {
                        if(GameWid[i]->get_id()==15)
                        {
                            menu = true;
                        }
                        if(GameWid[i]->get_id()==14)
                        {
                            if(time >= bg_time+1000)
                            {
                                fire = true;
                                bg_time = time;
                                for(size_t i =0; i<GameWid.size(); ++i)
                                {
                                    if(firecounter%2)
                                    {
                                        if(GameWid[i]->get_id()==10)
                                            angle = ((Num_Widget*)GameWid[i])->getintvalue();
                                        if(GameWid[i]->get_id()==11)
                                            Vo = ((Num_Widget*)GameWid[i])->getintvalue();
                                        x_offset = Tanks[player1]->get_end_x();
                                        int tmpyof = (Tanks[player1]->get_end_y()-Tanks[player1]->get_beg_y())/2+Tanks[player1]->get_beg_y();
                                        y_offset = tmpyof;
                                        if(GameWid[i]->get_id()==16)
                                        {
                                            ((Active_Widget*)GameWid[i])->setactive(true);
                                        }
                                        if(GameWid[i]->get_id()==17)
                                        {
                                            ((Active_Widget*)GameWid[i])->setactive(false);
                                        }

                                    }
                                    else
                                    {
                                        if(GameWid[i]->get_id()==12)
                                            angle = ((Num_Widget*)GameWid[i])->getintvalue();
                                        if(GameWid[i]->get_id()==13)
                                            Vo = ((Num_Widget*)GameWid[i])->getintvalue();
                                        x_offset = Tanks[player2]->get_beg_x();
                                        int tmpyof = (Tanks[player2]->get_end_y()-Tanks[player2]->get_beg_y())/2+Tanks[player2]->get_beg_y();
                                        y_offset = tmpyof;
                                    }
                                }
                                ++firecounter;
                            }
                        }
                    }
                }


                //gout<<refresh;
            }
            for(size_t i =0; i<GameWid.size(); ++i)
            {
                GameWid[i]->event_handler(ev);

                if(GameWid[i]->get_id()==16 && time >= bg_time+1000)
                {
                    if(firecounter%2)
                    {
                        ((Active_Widget*)GameWid[i])->setactive(true);
                        ((Active_Widget*)GameWid[i+1])->setactive(false);
                    }
                    else
                    {
                        ((Active_Widget*)GameWid[i])->setactive(false);
                        ((Active_Widget*)GameWid[i+1])->setactive(true);
                    }

                }
            }

            canvas c;
            c = Tanks[player1]->GetTankCanvas();
            gout<<stamp(c,Tanks[player1]->get_beg_x(),Tanks[player1]->get_beg_y());
            canvas e;
            e = Tanks[player2]->GetTankCanvas();
            gout<<stamp(e,Tanks[player2]->get_beg_x(),Tanks[player2]->get_beg_y());

            if (ev.type == ev_timer && ev.type !=ev_key)
            {
                if(fire && time > 2000)
                {
                    if(firecounter%2)
                    {
                        bool tmp = fire_logic(angle,Vo,time,x_offset,y_offset,firecounter%2,Tanks[player1]->get_beg_x(),Tanks[player1]->get_end_x(), Tanks[player1]->get_beg_y(),Tanks[player1]->get_end_y());
                        if(tmp)
                        {
                            gameover = true;
                            player2point++;
                        }
                    }

                    else
                    {
                        bool tmp = fire_logic(angle,Vo,time,x_offset,y_offset,firecounter%2,Tanks[player2]->get_beg_x(),Tanks[player2]->get_end_x(), Tanks[player2]->get_beg_y(),Tanks[player2]->get_end_y());
                        if(tmp)
                        {
                            gameover = true;
                            player1point++;
                        }
                    }

                }
                if(gameover)
                {
                    menu = true;
                    time = 0;
                    bg_time = 0;
                    gameover = false;

                    stringstream szs;
                    stringstream srs;
                    string tmp;
                    string tmp2;
                    szs<<player1point;
                    szs>>tmp;

                    srs<<player2point;
                    srs>>tmp2;
                    ((TextHolder_Widget*)Wid[Wid.size()-1])->textsetter(tmp+" : "+tmp2);

                    Tanks[player1]->set_beg_x(0);
                    firecounter++;

                }

                time=time+8;
            }
            gout<<refresh;
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
