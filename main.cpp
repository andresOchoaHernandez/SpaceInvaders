#define BORDER_WIN_H 30
#define BORDER_WIN_W 105
#define BORDER_WIN_X 0
#define BORDER_WIN_Y 0

#define GAME_WIN_H (BORDER_WIN_H - 2)
#define GAME_WIN_W (BORDER_WIN_W - 2)
#define GAME_WIN_X (BORDER_WIN_X + 1)
#define GAME_WIN_Y (BORDER_WIN_Y + 1)

#define NO_DIR 0
#define RIGTH_DIR 1 
#define LEFT_DIR 2
#define DOWN_DIR 3

#define INITIAL_X_INVADERS 0
#define INITIAL_Y_INVADERS 0
#define ALIENS_PER_LINE 15

#define BULLET_FREQ 237
#define ALIEN_FREQ 1500

#include <curses.h>
#include <unistd.h>
#include <vector>
#include <time.h>

using namespace std;

/* DATA STRUCTURES */

struct spaceship
{
    int y;
    int x;

}
typedef SPACESHIP;

struct shot
{
    int y;
    int x;
}
typedef SHOT;

struct invaderpart
{
    int y;
    int x;
}
typedef INVADERPART;

struct invader
{
    INVADERPART invader[3];
}
typedef INVADER;

/* FUNCTIONS */

    /*SPACE SHIP*/
    SPACESHIP initSpaceShip()
    {
        SPACESHIP ship;
        ship.x=GAME_WIN_W/2;  
        ship.y=GAME_WIN_H-1;
        return ship;
    }

    void drawSpaceShip(WINDOW *gameWin,SPACESHIP *ship)
    {
        mvwaddch(gameWin,ship->y,ship->x,'|');
        mvwaddch(gameWin,ship->y-1,ship->x,'T');
        mvwaddch(gameWin,ship->y,ship->x+1,'_');
        mvwaddch(gameWin,ship->y,ship->x-1,'_');
        mvwaddch(gameWin,ship->y-1,ship->x+1,'_');
        mvwaddch(gameWin,ship->y-1,ship->x-1,'_');
        mvwaddch(gameWin,ship->y,ship->x+2,'\\');
        mvwaddch(gameWin,ship->y,ship->x-2,'/');
    }

    void updateSpaceShipPos(SPACESHIP *ship,int direction)
    {
        if(direction == RIGTH_DIR && ship->x+2<GAME_WIN_W-1)
            ship->x++;
        else if(direction== LEFT_DIR && ship->x-2>0)
            ship->x--;
        else
            return;
    }

    void clearShip(WINDOW *gameWin,SPACESHIP *ship) 
    {
        mvwaddch(gameWin,ship->y,ship->x,' ');
        mvwaddch(gameWin,ship->y-1,ship->x,' ');
        mvwaddch(gameWin,ship->y,ship->x+1,' ');
        mvwaddch(gameWin,ship->y,ship->x-1,' ');
        mvwaddch(gameWin,ship->y-1,ship->x+1,' ');
        mvwaddch(gameWin,ship->y-1,ship->x-1,' ');
        mvwaddch(gameWin,ship->y,ship->x+2,' ' );
        mvwaddch(gameWin,ship->y,ship->x-2,' ' );
    }

    /* SHOTS */
    void drawShots(WINDOW *gameWin,vector<SHOT> &bullets)
    {
        for(SHOT elem:bullets)
            mvwaddch(gameWin,elem.y,elem.x,'I');
    }

    void clearShots(WINDOW *gameWin,vector<SHOT> &bullets)
    {
        for(SHOT elem:bullets)
            mvwaddch(gameWin,elem.y,elem.x,' ');
    }

    void updateShotsPos(vector<SHOT> &bullets)
    {
        for(unsigned int i=0;i<bullets.size();i++){
            
            if(bullets[i].y - 1 >= 0)
                bullets[i].y--;
            else
                bullets.erase(bullets.begin()+i);
        }
    }

    /* INVADERS */
    vector <INVADER> initInvaders()
    {
        vector <INVADER> aliens;

        int initialX=INITIAL_X_INVADERS;
        int initialY=INITIAL_Y_INVADERS;

        for(int i=0;i<60;i++)
        {
            if(i%ALIENS_PER_LINE==0 && i!=0)
            {
                initialY+=2;
                initialX=INITIAL_X_INVADERS;       
            }

            INVADERPART left;
            INVADERPART middle;
            INVADERPART right;

            left.y=initialY;
            left.x=initialX++;

            middle.y=initialY;
            middle.x=initialX++;

            right.y=initialY;
            right.x=initialX++;

            initialX+=3;

            INVADER alien;

            alien.invader[0]=left;
            alien.invader[1]=middle;
            alien.invader[2]=right;

            aliens.push_back(alien);

        }

        return aliens;
    }

    void drawInvaders(WINDOW *gameWin,vector<INVADER>&aliens)
    {
            
        for(INVADER elem:aliens)
        {
            mvwaddch(gameWin,elem.invader[0].y,elem.invader[0].x,'/');
            mvwaddch(gameWin,elem.invader[1].y,elem.invader[1].x,'*');
            mvwaddch(gameWin,elem.invader[2].y,elem.invader[2].x,'\\');
        }
            
    }

    void clearInvaders(WINDOW *gameWin,vector<INVADER>&aliens)
    {
        for(INVADER elem:aliens)
        {
            mvwaddch(gameWin,elem.invader[0].y,elem.invader[0].x,' ');
            mvwaddch(gameWin,elem.invader[1].y,elem.invader[1].x,' ');
            mvwaddch(gameWin,elem.invader[2].y,elem.invader[2].x,' ');
        }
    }

    void updateInvadersPos(vector<INVADER>&aliens,int direction)
    {
     
        for(unsigned int i=0;i<aliens.size();i++)
        {
            if (direction==RIGTH_DIR)
            {
                aliens[i].invader[0].x++;
                aliens[i].invader[1].x++;
                aliens[i].invader[2].x++;
            }

            else if (direction==LEFT_DIR)
            {
                aliens[i].invader[0].x--;
                aliens[i].invader[1].x--;
                aliens[i].invader[2].x--;
            }

            else
            {
                aliens[i].invader[0].y++;
                aliens[i].invader[1].y++;
                aliens[i].invader[2].y++;    
            }

        }
    }

    int indexOfGreaterX(vector<INVADER>&aliens)
    {
        int value=0;
        unsigned index;

        for(unsigned i=0;i<aliens.size();i++)
        {
            if(value<aliens[i].invader[2].x)
            {
                value=aliens[i].invader[2].x;
                index=i;
            }
        }
        return index;
    }
    
    int indexOfLowerX(vector<INVADER>&aliens)
    {
        int value=GAME_WIN_W;
        unsigned index;

        for(unsigned i=0;i<aliens.size();i++)
        {
            if(value>aliens[i].invader[0].x)
            {
                value=aliens[i].invader[0].x;
                index=i;
            }
        }
        return index;
    }

    int aliensDirection(vector <INVADER> &aliens,int *precDirection)
    {
        if( *precDirection==RIGTH_DIR && aliens[indexOfGreaterX(aliens)].invader[2].x +1 <= GAME_WIN_W -1 )
            return RIGTH_DIR;
        else if(*precDirection==LEFT_DIR && aliens[indexOfLowerX(aliens)].invader[0].x -1 >= 0 )
            return LEFT_DIR;
        else
            return DOWN_DIR;
    }

    /* FRAME */
    void drawFrame(WINDOW *gameWin, SPACESHIP *ship,vector<SHOT> &bullets,vector<INVADER>&aliens)
    {
        drawSpaceShip(gameWin,ship);
        drawShots(gameWin,bullets); 
        drawInvaders(gameWin,aliens);
        wrefresh(gameWin);
    }

    void clearFrame(WINDOW *gameWin,SPACESHIP *ship,vector<SHOT> &bullets,vector<INVADER>&aliens)
    {
        clearShip(gameWin,ship);
        clearShots(gameWin,bullets);
        clearInvaders(gameWin,aliens);
    }

    /*COLLISION DETECTION*/
    void checkCollision(vector<SHOT>&bullets,vector<INVADER>&aliens)
    {
        bool cond;

        for (unsigned i=0;i<bullets.size();i++)
        {
            for(unsigned j=0;j<aliens.size();j++)
            {
                cond=( bullets[i].x==aliens[j].invader[0].x && bullets[i].y==aliens[j].invader[0].y ) || 
                     ( bullets[i].x==aliens[j].invader[1].x && bullets[i].y==aliens[j].invader[1].y ) || 
                     ( bullets[i].x==aliens[j].invader[2].x && bullets[i].y==aliens[j].invader[2].y );

                if(cond)
                {
                    bullets.erase(bullets.begin()+i);
                    aliens.erase(aliens.begin()+j);
                }
            }
        }
    }

    /*  CHECK WIN */
    bool checkWin(vector<INVADER>&aliens)
    {
        return aliens.empty();
    }
    /*  CHECK LOSE */
    bool checkLose(vector<INVADER>&aliens,SPACESHIP *ship)
    {
        bool lose=false;

        for(INVADER elem:aliens)
        {
            lose=
            (elem.invader[0].x==ship->x && elem.invader[0].y==ship->y) ||
            (elem.invader[0].x==ship->x && elem.invader[0].y==ship->y-1) ||
            (elem.invader[0].x==ship->x-1 && elem.invader[0].y==ship->y-1) ||
            (elem.invader[0].x==ship->x+1 && elem.invader[0].y==ship->y-1) ||
            (elem.invader[0].x==ship->x-1 && elem.invader[0].y==ship->y) ||
            (elem.invader[0].x==ship->x-2 && elem.invader[0].y==ship->y) ||
            (elem.invader[0].x==ship->x+1 && elem.invader[0].y==ship->y) ||
            (elem.invader[0].x==ship->x+2 && elem.invader[0].y==ship->y) ||
            
            (elem.invader[1].x==ship->x && elem.invader[1].y==ship->y) ||
            (elem.invader[1].x==ship->x && elem.invader[1].y==ship->y-1) ||
            (elem.invader[1].x==ship->x-1 && elem.invader[1].y==ship->y-1) ||
            (elem.invader[1].x==ship->x+1 && elem.invader[1].y==ship->y-1) ||
            (elem.invader[1].x==ship->x-1 && elem.invader[1].y==ship->y) ||
            (elem.invader[1].x==ship->x-2 && elem.invader[1].y==ship->y) ||
            (elem.invader[1].x==ship->x+1 && elem.invader[1].y==ship->y) ||
            (elem.invader[1].x==ship->x+2 && elem.invader[1].y==ship->y) ||
            
            (elem.invader[2].x==ship->x && elem.invader[2].y==ship->y) ||
            (elem.invader[2].x==ship->x && elem.invader[2].y==ship->y-1) ||
            (elem.invader[2].x==ship->x-1 && elem.invader[2].y==ship->y-1) ||
            (elem.invader[2].x==ship->x+1 && elem.invader[2].y==ship->y-1) ||
            (elem.invader[2].x==ship->x-1 && elem.invader[2].y==ship->y) ||
            (elem.invader[2].x==ship->x-2 && elem.invader[2].y==ship->y) ||
            (elem.invader[2].x==ship->x+1 && elem.invader[2].y==ship->y) ||
            (elem.invader[2].x==ship->x+2 && elem.invader[2].y==ship->y);

            if (lose)
                break;
        }

        return lose;
    }

    /* THICK */
    void thick(WINDOW *gameWin,SPACESHIP *ship,int direction,vector<SHOT> &bullets,int frequency,vector<INVADER>&aliens,int *initialAliensDir)
    {
        /* DRAW */
        drawFrame(gameWin,ship,bullets,aliens);

        /* CLEAR */
        clearFrame(gameWin,ship,bullets,aliens);
        
        /* UPDATE */
        updateSpaceShipPos(ship,direction);

        if (frequency%BULLET_FREQ==0){
            updateShotsPos(bullets);
            checkCollision(bullets,aliens);
        }

        if(frequency%ALIEN_FREQ==0)
        {
            if(aliensDirection(aliens,initialAliensDir)==DOWN_DIR && *initialAliensDir==RIGTH_DIR)
            {
                updateInvadersPos(aliens,DOWN_DIR);
                *initialAliensDir=LEFT_DIR;
            }
            else if(aliensDirection(aliens,initialAliensDir)==DOWN_DIR && *initialAliensDir==LEFT_DIR)
            {
                updateInvadersPos(aliens,DOWN_DIR);
                *initialAliensDir=RIGTH_DIR;
            }
            else
                updateInvadersPos(aliens,*initialAliensDir);

            checkCollision(bullets,aliens);
        }
        /* SLEEP */
        usleep(10);
    }

/* MAIN */
int main(int argc,char *argv[])
{
    initscr();

    cbreak();
    curs_set(0);
    
    /*SETTINGS*/
    WINDOW *borderWin=newwin(BORDER_WIN_H,BORDER_WIN_W,BORDER_WIN_Y,BORDER_WIN_X);
    WINDOW *gameWin=newwin(GAME_WIN_H,GAME_WIN_W,GAME_WIN_Y,GAME_WIN_X);
    WINDOW *inputWin=newwin(1,1,BORDER_WIN_H+2,1);

    refresh();

    box(borderWin,0,0);
    
    wrefresh(borderWin);
    wrefresh(gameWin);

    nodelay(inputWin,true);

    
    /*GAME*/

    /* Initial settings */

    begin:

    SPACESHIP ship=initSpaceShip();
    vector<SHOT> bullets;
    vector<INVADER>aliens=initInvaders();

    int currDir=NO_DIR;
    int initialAliensDir=RIGTH_DIR;

    int frequency=0;

    do
    {
        mvwprintw(gameWin,GAME_WIN_H/2-2,GAME_WIN_W/2-9,"[ SPACE INVADERS ]");
        mvwprintw(gameWin,GAME_WIN_H/2,GAME_WIN_W/2-18,"[ PRESS  <-|SPACE_BAR|->  TO PLAY ]");
        mvwprintw(gameWin,GAME_WIN_H/2+2,GAME_WIN_W/2-16,"[...PRESS ENTER TO CONTINUE...]");
        wrefresh(gameWin);
    }
    while(wgetch(inputWin)!='\n');

    wclear(gameWin);

    while(1)
    {
        switch (wgetch(inputWin))
        {
        case 67:
            currDir=RIGTH_DIR;
            thick(gameWin,&ship,currDir,bullets,frequency++,aliens,&initialAliensDir);
            break;
        case 68:
            currDir=LEFT_DIR;
            thick(gameWin,&ship,currDir,bullets,frequency++,aliens,&initialAliensDir);
            break;
        case 32:
            SHOT shot;
            shot.y=ship.y;
            shot.x=ship.x;
            bullets.push_back(shot);
            thick(gameWin,&ship,currDir,bullets,frequency++,aliens,&initialAliensDir);
            break;
        default:
            currDir=NO_DIR;
            thick(gameWin,&ship,currDir,bullets,frequency++,aliens,&initialAliensDir);
            break;
        }

        if(checkWin(aliens) || checkLose(aliens,&ship))
            goto begin;
    }

    endwin();
    return 0;
}