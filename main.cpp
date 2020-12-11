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
        int clean_board();
        Game(){};

};
int Game::clean_board()
{
    printf("clear the board");
    for (int i=0;i<ROW;i++)
    {
        for (int j=0;j<CUL;j++)
        {
            this->board[i][j] =0;
        }
    }
}
Game::Game(void){ 
    clean_board();
    }
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
        Player(int p, list <int> dead_trops , bool is_won=false){};
        Player(Player *P){};
};
Player:: Player(int p, list <int> dead_trops , bool is_won=false)
{
    
    this->pid = p;
    this->is_won =false;
    this->dead_trops = dead_trops;
}
Player::Player(Player *p)/*copy constarctor*/
{
    this->pid = p->pid;
    this->is_won = p->is_won;
    this->dead_trops = p->dead_trops;
}
class Soldier : public Player
{
private:
    /* data */
public:
    int tol_id;
    bool is_alive;
    int place_x;
    int place_y;
    int move(int x, int y);
    Soldier(int place_x, int place_y, Player *P);
    ~Soldier();
    virtual int move(int x, int y);
    virtual int can_go_there(int x, int y);
    virtual int move_soldier(int x, int y);
};


Soldier::Soldier(int place_x, int place_y, Player *p):Player(p)
{
    this->is_alive = 1;
    this->place_x = place_x;
    this->place_y = place_y;
}
int Soldier::move_soldier(int x, int y)
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
class Pawn : public Soldier
{
    public:
    int move(int x, int y);
    int can_go_there(int x, int y);
    int move_soldier(int x, int y);
    Pawn Pawn(int place_x, int place_y, Player *p){};
};
Pawn::Pawn(int place_x, int place_y, Player *p): Soldier(place_x, place_y, p){
    printf("created pawn in (%d, %d)", place_x, place_y);
}
int Pawn::can_go_there(int x, int y)
{
    if (y == place_y+1 && x == place_x)
        return 1;
    return 0;
}

int Pawn::move(int x, int y)
{
    if (can_go_there(x, y))
    {
        printf("move Pawn to (%d, %d)", x, y);
        return Soldier::move_soldier(x, y);
    }
}
class Knight : public Soldier
{
    public:
        int move(int x, int y);
        int can_go_there(int x, int y);
        Knight Knight(int place_x, int place_y, Player *P){};
};
Knight::Knight(int place_x, int place_y, Player *P):Soldier(place_x, place_y, p){
    printf("create Knight in (%d, %d)", place_x, place_y);

}
int Knight::move(int x, int y)
{
    if(can_go_there(x, y))
    {
        printf("move Knight to (%d, %d)", x, y);
        return Soldier::move_soldier(x, y);
    }
    return 0;
}
int Knight::can_go_there(int x, int y)
{
   
    if ( x == place_x+2 && place_y+1 == y || place_x-2 == x && place_y-1 == y)
        return 1;
    else if ( x == place_x+2 && place_y-1 == y || place_x-2 == x && place_y+1 == y)
        return 1;

    else if ( x == place_x && place_y+1 == y || place_x == x && place_y-1 == y)
        return 1;
    return 0;
    
}
class Bishop : public Soldier //runner
{
    public:
        int move(int x, int y);
        int can_go_there(int x, int y);
        Bishop Bishop(int place_x, int place_y, Player *p){};

};
Bishop ::Bishop(int place_x, int place_y, Player *p): Soldier(place_x, place_y, p)
{
    printf("created bishop in (%d, %d)", place_x, place_y );
}
int Bishop::move(int x, int y)
{
    if(can_go_there(x, y))
        {
            printf("move Bishop to (%d, %d)", x, y);
            return Soldier::move_soldier(x, y);
        }
    return 0; 
}
int Bishop::can_go_there(int x,int y)
{
    for(int i=0;i<8-place_y;i++)
    {
        if (place_x+i == x && place_y+i == y)
            return 1;
    } 
    for(int i=place_x;i<0; i++)
    {
        if (place_x-i ==x && place_y-i ==y)
            return 1;
    }
}
class Torre : public Soldier
{
    public :
    int move(int x,int y);
    int can_go_there(int x ,int y);
    Torre Torre(int place_x, int place_y, Player *p){};


};
Torre::Torre(int place_x, int place_y, Player *p):Soldier(place_x, place_y, p)
{
    // just for triaing- the Soldier constarctor dose
    //the extra job
    /*
    this::Soldier.place_x = place_x;
    this::Soldier.place_y = place_y;
    this::Player-> p;
    */
   printf("create Torre in (%d, %d)", place_x, place_y);
}
int Torre:: can_go_there(int x, int y)
{
    
    if (place_x =x && y != place_y)
    {
        return 1;
    }
    else if (place_y = y && x != place_x)
    {
        return 1;
    }
    return 0;
}
int Torre::move(int x, int y)
{
    if (can_go_there(x, y))
    {
        printf("move Torre to (%d, %d)", x, y);
        return Soldier::move_soldier(x,y);
    }
    return -1;
}
class Queen: public Soldier :public Torre : public Bishop
{
    public:
    int move(int x, int y);
    int can_go_there(int x, int y);
    Queen Queen(int place_x, int place_y, Player *p){};
};
Queen::Queen(int place_x, int place_y, Player *p):Soldier(place_x, place_y, p)
{
    printf("create Queen in (%d, %d)", place_x, place_y);
}
int Queen::move(int x, int y)
{
    if (can_go_there(int x, int y))
    {
        printf("move Queen to (%d, %d)", x, y);
        return Soldier::move_soldier(x, y);
    }
    return -1;
}
int Queen::can_go_there(int x, int y)
{
    return Bishop::can_go_there(x,y) && Torre::can_go_there(x,y);
}
class King : public Soldier
{
    public:
        int move(int x, int y);
        int can_go_there(int x, int y);
        King King(int place_x, int place_y, Player *p);
}
King::King(int place_x, int place_y, Player *p):Soldier(place_x, place_y, p)
{
    printf("created king in (%d, %d)", place_x, place_y);
}
int King::move(int x, int y)
{
    if(can_go_there(x, y)
    {
        printf("move King to (%d, %d)", x, y);
        return Soldier::move_soldier();
    }
    return -1;
}
int King::can_go_there(int x, int y)
{
    for (int i=-1;i<2;i++)
    {
        if ((place_x+i == x && place_y+i == y )&& !(place_x == x && place_y == y))
                return 1;
    }
    return -1;
}
void main()
{
    
}