//The headers
/*
By Near
http://near.serveftp.com
*/
//#define windows

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "timer.h"
#include <string.h>
#include <stdlib.h>
#include "sdls.h"
#include "sprites.h"
#include "screen.h"
#include "pacman.h"
#include "maze.h"
#include "font.h"
#include "ghosts.h"
#include "gameini.h"


int main( int argc, char* args[] )
{     
    
    srand ( time(NULL) ); 

    game_state=TITLE;

    change_game_state(BEGIN);

    if( init() == false ) return 1;            

    if( load_files() == false ) return 1; 

    if (inifont() == 0) return 1;
   
    init_pacman();
    inipebbles();
    init_ghosts();

    while( quit == false )
    {
	fps.start();
	events(event);
	paintbg();
	 
	switch(game_state)
	{
		case TITLE:
		{
			
			plyrtmer.start();
			redytmer.start();
			game_state=GAME;	
			
			//apply_surface(1,1,maze[1],screen,NULL);
			break;
		}
		case GAME:
		{
			if (blink_maze == false) draw_map();
			drawpebbles();
			switch(in_game_state)
			{
				case BEGIN:
				{
					game_ini(); 
					break;
				}
				case PLAY:
				{		
					
					if (totalpebs == 248)
					{
						in_game_state = WINNER;
						break;		
					}
					
					go_pacman();

					go_ghost();
					collusion_chk();
		
					break;
				}
				case DIE_PAUSE:
				{	
					if (pacman->died == true)
					{
						show_ghosts();
					}
					if (red->is_eaten == true)
					{
						print("400", red->x-5,red->y);
					} 
					if (pink->is_eaten == true)
					{
						print("400", pink->x-5,pink->y);
					}
					if (blue->is_eaten == true)
					{
						print("400", blue->x-5,blue->y);
					}	
					if (orange->is_eaten == true)
					{
						print("400", orange->x-5,orange->y);
					}
					

					if (red->is_eaten == false)
					{
						red->show_frame(image,red->sprt2use,red->frame);
					}
					if (pink->is_eaten == false)
					{
						pink->show_frame(image,pink->sprt2use,pink->frame);
					}
					if (blue->is_eaten == false)
					{
						blue->show_frame(image,blue->sprt2use,blue->frame);
					}
					if (orange->is_eaten == false)
					{
						orange->show_frame(image,orange->sprt2use,orange->frame);
					}

					if (pacman->diepause.is_started() == false)
					{
						pacman->diepause.start();
					}
					if (pacman->diepause.get_ticks() > die_pause)
					{
						if (pacman->died == true)
						{
							pacman->y+=3;
							pacman->frame=0;
							change_game_state(DIED);
							pacman->diepause.stop();
						} else {
							if (red->is_eaten == true)
							{
								red->reset();
								red->change_sprite(EYES);
								
							} 
							if (pink->is_eaten == true)
							{
								pink->reset();
								pink->change_sprite(EYES);
							}
							if (blue->is_eaten == true)
							{
								blue->reset();
								blue->change_sprite(EYES);
							}
							if (orange->is_eaten == true)
							{
								orange->reset();
								orange->change_sprite(EYES);
							}
							change_game_state(PLAY);
							pacman->diepause.stop();
						}
					}	
					break;
				}

				case DIED:
				{
					if (pacman->diedtimer.is_started() == false)
					{
						pacman->diedtimer.start();
					}
					if (pacman->diedtimer.get_ticks() > 100.f)
					{
						pacman->diedtimer.stop();
						if (pacman->frame == 5 && d_frame == 7)
						{
							pacman->frame=0;
							d_frame=0;
							redytmer.start();

							/*red ghost*/
							red->change_sprite(LOOK_RGT);
							red->followstate=0;
							red->frame=0;
							red->aistate=START_UP;

							pink->change_sprite(LOOK_RGT);
							pink->frame=0;
							pink->aistate=AT_HOME;

							blue->change_sprite(LOOK_RGT);
							blue->frame=0;
							blue->aistate=AT_HOME;

							orange->change_sprite(LOOK_RGT);
							orange->frame=0;
							orange->aistate=AT_HOME;
							
							red->doanime = true;
							blue->doanime = true;
							pink->doanime = true;
							orange->doanime = true;
							
							whichswitchmode = sw_corner;
							GhostSwitchMode.stop();
							gtimer = 10000;
							plyrtmer.start();
							change_game_state(RESTART);
							break;
							
						} else
						if (pacman->frame == 1 && d_frame == 6)
						{
							pacman->frame=0;
							d_frame++;
							pacman->y-=2;
							pacman->x+=3;
						} else
						if (pacman->frame == 2 && d_frame == 5)
						{
							pacman->frame=0;
							d_frame++;
							pacman->y+=2;
						} else {	
							pacman->frame++;
						}
						pacman->diedtimer.start();
					}					
					pacman->show_frame(image,d_frame,pacman->frame);
					break;
				}
				
				case RESTART:
				{
					game_ini();
					break;
				}
				case GAME_OVER:
				{
					print("GAME OVER!",10,10);
					break;
				}
				case WINNER:
				{
					//print("test",10,10);

					show_ghosts();

					pacman->show_frame(curtimg,sprnum,pacman->frame);
					if (mazeblinktmr.is_started() == false)
					{
						mazeblinktmr.stop();
						mazeblinktmr.start();
					} else {
						if (mazeblinktmr.get_ticks() > blink_time)
						{
							
							if (blink_count == 0) blink_time = 500.f;
							if (is_maze_white == false)
							{
								is_maze_white=true;
							} else {
								is_maze_white=false;
							}
							blink_count++;
							if (blink_count == 7)
							{
								blink_count=0;
								blink_time=2000.f;
								blink_maze = false;
								is_maze_white=false;
								in_game_state = GAME_OVER;
								break;
							}
							mazeblinktmr.stop();
				
						}
						if (is_maze_white == true)
						{
							draw_map(true);
						} else {
							draw_map();
						}
					}
					break;
				}
			} 		
			break;
		}

	}

	framerate();
    }

    clean_up();   
    return 0;    
}
