#include <iostream>
#include <list>
#include <iterator>

using namespace std;
#define ROW 8
#define CUL 8


int board[ROW][CUL];
class Game
{
    public:
        int board[ROW][CUL];
        int clean(int x, int y);
        void setboard_xy(int x,int y, int p, int tol_id);
        void kill_in_xy(int x, int y, list <int> deth_table);
        void add_deth(int tol_id, list <int>deth_table);

};
void Game::add_deth(int tol_id, list <int> deth_table)
{
    list <int> :: iterator it;
    for (it = deth_table.begin(); it !=deth_table.end(); it++)
    {
        if (*it == 0)
            *it = tol_id;//fix to list
    }
}
void Game::kill_in_xy(int x, int y, list <int> deth_table)
{
    int tol_id = ((int(board[x][y]/100))*100)-board[x][y];//get the tool id
    add_deth(tol_id, deth_table);


    
}
int Game::clean(int x, int y){
    if (board[x][y] == 0)
        return 1;
    return 0;
}
void Game::setboard_xy(int x, int y, int pid, int tol_id)
{
    board[x][y] == pid+tol_id;
}
class Player : public Game
{
    public:
        int pid;
        bool is_won;
        list <int> dead_trops;
};
class soldier : public Player
{
private:
    /* data */
public:
    int tol_id;
    bool is_alive;
    int place_x;
    int place_y;
    int move(int x, int y);
    soldier(int place_x, int place_y);
    ~soldier();
    virtual int move(int x, int y);
    virtual int can_go_there(int x, int y);
    virtual int move_soldier(int x, int y);
};


soldier::soldier(int place_x, int place_y)
{
    this->is_alive = 1;
    this->place_x = place_x;
    this->place_y = place_y;
}
int soldier::move_soldier(int x, int y)
{
    if (clean(x, y))
    {
        setboard_xy(x, y, pid, tol_id);
        return 1;
    }
    kill_in_xy(x, y, dead_trops);
    setboard_xy(x, y, pid, tol_id);
    return 1;
}
class pawn : public soldier
{
    public:
    int move(int x, int y);
    int can_go_there(int x, int y);
    int move_soldier(int x, int y);
};

int pawn::can_go_there(int x, int y)
{
    if (y == place_y+1 && x == place_x)
        return 1;
    return 0;
}

int pawn::move(int x, int y)
{
    if (can_go_there(x, y))
        return move_soldier(x, y);
}
class knight : public soldier
{
    public:
        int move(int x, int y);
        int can_go_there(int x, int y);
};
int knight::move(int x, int y)
{
    if(can_go_there(x, y))
    {
        return move_soldier(x, y);
    }
    return 0;
}
int knight::can_go_there(int x, int y)
{
   
    if ( x == place_x+2 && place_y+1 == y || place_x-2 == x && place_y-1 == y)
        return 1;
    else if ( x == place_x+2 && place_y-1 == y || place_x-2 == x && place_y+1 == y)
        return 1;

    else if ( x == place_x && place_y+1 == y || place_x == x && place_y-1 == y)
        return 1;
    return 0;
    
}
class bishop : public soldier //runner
{
    public:
        int move(int x, int y);
        int can_go_there(int x, int y);

};
int bishop::move(int x, int y)
{
    if(can_go_there(x, y))
        {
            return move_soldier(x, y);
        }
    return 0; 
}
int bishop::can_go_there(int x,int y)
{
    for(int i=0;i<8-place_y;i++)
    {
        if (place_x+i == x && place_y+i == y)
            return 1;
        else if ()
    }
}