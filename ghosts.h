#ifndef ghosts_H
#define ghosts_H


#include <stdlib.h>
#include <time.h>
#include "sprites.h"
#include "timer.h"
#include "pathfinder.h"

int init_ghosts();
int del_ghosts();
int go_ghost();
int show_ghosts();


class ghost : public character
{
		public:
		bool dcollusion();
		bool ucollusion();
		bool fcollusion();
		bool bcollusion();
		float animetmr;
		Timer eatable_tmr;
		Timer atimer; //animation timer
		bool is_eatable;
		bool is_dead;
		int sprt2use;
		ghost();
		bool is_eaten;
		bool has_been_eaten;
		int reset();
		int turn();
		int blink_start();
		int turn_back();
		int chgetmer();
		bool chkifeaten();
		int change_sprite(int sprite_num);
		bool is_sprite(int sprite_num);
		bool is_pm_super();

		int type;
		int speed;

		int pacx;
		int pacy;

		int ai();
		Timer aitmr;	
		int aistate;
		int aigbt;

		int random_dir;
		
		int trandir;
		int delPath(pathfinder* path);

		pathfinder* gohome;
		pathfinder* GotoCorner;
		pathfinder* followpm;

		pathfinder* rnawy;

		
		Timer* gctmr;

		int GoPath(pathfinder* path);
		int runaway(pathfinder* path);
		
		~ghost();

		bool iscorner;
		bool doanime;

	

		int tunndir;
		int tunngobk;
		bool tunngoth;
		
		int pathtowhat;

		float ratmrlen;
		Timer tatmr;
		bool remrbck;

		//start up
		int startcnr;

		//followstate
		int followstate;
		
		Timer tbtimer;
		int timeinbox;
		int tbmode;

		int boxmovement;
		
		bool is_out_of_box;

		int movout;

		
};

int keyghost(ghost &whchghst);
int clroclst(ghost &theghost);

#include "ghosts.cpp"

#endif
