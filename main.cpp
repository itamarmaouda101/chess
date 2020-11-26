#include <iostream>
#include <list>

using namespace std;
#define ROW 8
#define CUL 8


int board[ROW][CUL];
class Game
{
    public:
        int board[ROW][CUL];
        int clean(int x, int y);
        int setboard_xy(int x,int y, int p, int tol_id);
        void kill_in_xy(int x, int y, int *deth_table);
        void add_deth(int tol_id, int *deth_table[16]);

};
void Game::add_deth(int tol_id, int *deth_table[16])
{
    for (int i=0; i<16;i++)
    {
        if (deth_table[i] == 0)
            deth_table[i] = tol_id;//fix to list
    }
}
void Game::kill_in_xy(int x, int y, int *deth_table)
{
    int tol_id = ((int(board[x][y]/100))*100)-board[x][y];//get the tool id
    add_deth(tol_id, deth_table);


    
}
int Game::clean(int x, int y){
    if (board[x][y] == 0)
        return 1;
    return 0;
}
int Game::setboard_xy(int x, int y, int pid, int tol_id)
{
    board[x][y] == pid+tol_id;
}
class Player : public Game
{
    public:
        int pid;
        bool is_won;
        int dead_trops[16];
};
class soldier : public Player
{
private:
    /* data */
public:
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

class pawn : public soldier
{
    public:
    int tol_id;
    virtual int move(int x, int y);
    virtual int can_go_there(int x, int y);
    virtual int move_soldier(int x, int y);
};
int pawn::move_soldier(int x, int y)
{
    if (clean(x, y))
    {
        setboard_xy(x, y, pid, tol_id);
    }
    kill_in_xy(x, y);
    setboard_xy(x, y, pid, tol_id);
}
int pawn::can_go_there(int x, int y)
{
    if (y = place_y+1 && x == place_x)
        return 1;
    return 0;
}

int pawn::move(int x, int y)
{
    if (can_go_there(x, y))
        return move_soldier(x, y);
}

 