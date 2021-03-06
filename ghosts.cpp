#include "ghosts.h"

enum { RED,PINK,BLUE,ORANGE };
enum { LOOK_RGT,LOOK_DWN,LOOK_LFT,LOOK_UP,EATABLE,BLINK,EYES };
enum { WONDER,HUNT,RUN_AWAY,GO_HOME,AT_HOME,SCATTER,FAKE,GO_TUNNEL,START_UP };
enum{ GO_LFT,GO_RGHT,GO_UP,GO_DWN,RND1,RND2,RND3,RND4,RND5,RND6,RND7,RND8,RND9,RND10,RND11,RND12,RND13,RND14,RND15,RND16,RND17,RND18 };
enum { objects,nonobjects };
float eatable_length = 8000.f; /* 8 seconds for the first level */

int gtimer=20000;

ghost* red;
ghost* pink;
ghost* blue;
ghost* orange;

#include "gameini.h"


ghost::ghost() : character::character(7)
{
	gohome = new pathfinder;
	GotoCorner = new pathfinder;
	followpm = new pathfinder;
	rnawy = new pathfinder;

	ratmrlen = 3000.f;
	animetmr = 600.f;
	x = 114;
	y = 95;
	change_sprite(LOOK_RGT);
	c.r=4;
	is_eatable = false;
	is_dead = false;
	aistate =AT_HOME;
	has_been_eaten = false;
	iscorner = false;
	doanime = true;
	tunngoth = false;
	pathtowhat = -1;
	tbmode = 0;
	remrbck = false;
	is_out_of_box = false;
	movout = 1;
	
}

int go_ghost()
{
	//0 = left
	//1= down
	//2 = right
	//3 = up

	//GhostSwitchMode timer starts here
	// sw_corner, sw_attack

	if (pacman->super == true)
	{
		GhostSwitchMode.pause();
	}

	if (pacman->super == false)
	{
		GhostSwitchMode.unpause();
	}
	if (GhostSwitchMode.is_started() == false)
	{
		GhostSwitchMode.start();
	}

	if (GhostSwitchMode.get_ticks() > gtimer )
	{
		

		if (whichswitchmode == sw_corner)
		{
		
			if (orange->aistate !=  AT_HOME && orange->is_sprite(EYES) == false)
			{
				clroclst(*orange);
				orange->followpm->openlist->settarget(pacman->x,pacman->y);
				orange->followpm->closelist->settarget(pacman->x,pacman->y);
				orange->followpm->openlist->add2lst(orange->x,orange->y,10);
				orange->pathtowhat = objects;
				orange->aistate = HUNT;
			}
			if (red->aistate != AT_HOME && red->is_sprite(EYES) == false)
			{
				clroclst(*red);
				red->followpm->openlist->settarget(pacman->x,pacman->y);
				red->followpm->closelist->settarget(pacman->x,pacman->y);
				red->followpm->openlist->add2lst(red->x,red->y,10);
				red->pathtowhat = objects;
				red->aistate = HUNT;
			}
			
			if (pink->aistate != AT_HOME && pink->is_sprite(EYES) == false)
			{
				clroclst(*pink);
				pink->followpm->openlist->settarget(pacman->x,pacman->y);
				pink->followpm->closelist->settarget(pacman->x,pacman->y);
				pink->followpm->openlist->add2lst(pink->x,pink->y,10);
				pink->pathtowhat = objects;
				pink->aistate = HUNT;
			}

			if (blue->aistate != AT_HOME && blue->is_sprite(EYES) == false)
			{
				clroclst(*blue);
				blue->followpm->openlist->settarget(pacman->x,pacman->y);
				blue->followpm->closelist->settarget(pacman->x,pacman->y);
				blue->followpm->openlist->add2lst(blue->x,blue->y,10);
				blue->pathtowhat = objects;
				blue->aistate = HUNT;
			}
		
			gtimer = 20000;			
			whichswitchmode = sw_attack;
			
			
			
		} else {
			if (red->aistate != AT_HOME && red->is_sprite(EYES) == false)
			{
				clroclst(*red);
				red->GotoCorner->openlist->settarget(214,15);//14,15);//214,15);
				red->GotoCorner->closelist->settarget(214,15);//214,15);
				red->GotoCorner->openlist->add2lst(red->x,red->y,10);
				red->pathtowhat = nonobjects;
				red->aistate= SCATTER;			
				red->remrbck = true;
			}

			if (pink->aistate != AT_HOME && pink->is_sprite(EYES) == false)
			{
				clroclst(*pink);
				pink->GotoCorner->openlist->settarget(14,15);//14,15);//214,15);
				pink->GotoCorner->closelist->settarget(14,15);//214,15);
				pink->GotoCorner->openlist->add2lst(pink->x,pink->y,10);
				pink->pathtowhat = nonobjects;
				pink->aistate= SCATTER;			
				pink->remrbck = true;
			}

			if (blue->aistate != AT_HOME && blue->is_sprite(EYES) == false)
			{
				clroclst(*blue);
				blue->GotoCorner->openlist->settarget(14,15);//14,15);//214,15);
				blue->GotoCorner->closelist->settarget(14,15);//214,15);
				blue->GotoCorner->openlist->add2lst(blue->x,blue->y,10);
				blue->pathtowhat = nonobjects;
				blue->aistate= SCATTER;			
				blue->remrbck = true;
			}
			if (orange->aistate != AT_HOME && orange->is_sprite(EYES) == false)
			{
				clroclst(*orange);
				orange->GotoCorner->openlist->settarget(14,15);//14,15);//214,15);
				orange->GotoCorner->closelist->settarget(14,15);//214,15);
				orange->GotoCorner->openlist->add2lst(orange->x,orange->y,10);
				orange->pathtowhat = nonobjects;
				orange->aistate= SCATTER;			
				orange->remrbck = true;
			}
			whichswitchmode = sw_corner;			
			gtimer = 15000;
			

		}
		GhostSwitchMode.stop();
		GhostSwitchMode.pause();
	}

	red->ai();
	pink->ai();	
	blue->ai();
	orange->ai();

	pink->show_frame(image,pink->sprt2use,pink->frame);
	red->show_frame(image,red->sprt2use,red->frame);
	blue->show_frame(image,blue->sprt2use,blue->frame);
	orange->show_frame(image,orange->sprt2use,orange->frame);

	if (pacman->super == true)
	{	

		

		if (red->is_sprite(BLINK) == false && red->is_sprite(EYES) == false && red->has_been_eaten == false)
		{
			red->change_sprite(EATABLE);
			
			
		}
		if (pink->is_sprite(BLINK) == false && pink->is_sprite(EYES) == false && pink->has_been_eaten == false) 
		{
			pink->change_sprite(EATABLE);
			
		}

		if (blue->is_sprite(BLINK) == false && blue->is_sprite(EYES) == false && blue->has_been_eaten == false) 
		{
			blue->change_sprite(EATABLE);
			
		}

		if (orange->is_sprite(BLINK) == false && orange->is_sprite(EYES) == false && orange->has_been_eaten == false)
		{
			orange->change_sprite(EATABLE);
			
		}		
	}



	if (blue->atimer.is_started() == false)
	{
		blue->atimer.start();
	}

	if (pink->atimer.is_started() == false)
	{
		pink->atimer.start();
	}

	if (red->atimer.is_started() == false)
	{
		red->atimer.start();
	}

	if (orange->atimer.is_started() == false)
	{
		orange->atimer.start();
	}

	if (red->atimer.get_ticks() > red->animetmr )

	{
		if (red->doanime == true)
		{
			red->anime(red->sprt2use);
			red->atimer.start();	
		}
	}

	if (pink->atimer.get_ticks() > pink->animetmr)
	{
		if (pink->doanime == true)
		{
			pink->anime(pink->sprt2use);
			pink->atimer.start();	
		}
	}

	if (blue->atimer.get_ticks() > blue->animetmr)
	{
		if (blue->doanime == true)
		{
			blue->anime(blue->sprt2use);
			blue->atimer.start();	
		}
	}

	if (orange->atimer.get_ticks() > orange->animetmr)
	{
		if (orange->doanime == true)
		{
			orange->anime(orange->sprt2use);
			orange->atimer.start();	
		}
	}
	

	pacman->c.x = pacman->x;
	pacman->c.y = pacman->y;

	red->c.x = red->x;
	red->c.y = red->y;

	pink->c.x = pink->x;
	pink->c.y = pink->y;

	blue->c.x = blue->x;
	blue->c.y = blue->y;

	orange->c.x = orange->x;
	orange->c.y = orange->y;

	

	if (pacman->check_collision(pacman->c,red->c))
	{
		if (red->sprt2use != 6 )
		{
			if (pacman->super == true)
			{
				if (red->aistate != RUN_AWAY)
				{
					
					pacman->died = true;
					clroclst(*red);					
				} else {
					red->change_sprite(EATABLE);
					red->is_eaten = true;
					red->animetmr = 600.f;
					return 0;
				}
			} else
			if (pacman->super == false)
			{
				pacman->died = true;
				clroclst(*red);
				
			} 
	
		}

	} 
	if (pacman->check_collision(pacman->c,pink->c))
	{
		if (pink->sprt2use != 6 )
		{
			if (pacman->super == true)
			{
				if (pink->aistate != RUN_AWAY)
				{
					
					pacman->died = true;
					clroclst(*pink);					
				} else {
					pink->change_sprite(EATABLE);
					pink->is_eaten = true;
					
					return 0;
				}
			} else
			if (pacman->super == false)
			{
				pacman->died = true;
				clroclst(*pink);
				
			} 
	
		}

	} 

	if (pacman->check_collision(pacman->c,blue->c))
	{
		if (blue->sprt2use != 6 )
		{
			if (pacman->super == true)
			{
				if (blue->aistate != RUN_AWAY)
				{
					
					pacman->died = true;
					clroclst(*blue);					
				} else {
					blue->change_sprite(EATABLE);
					blue->is_eaten = true;
					
					return 0;
				}
			} else
			if (pacman->super == false)
			{
				pacman->died = true;
				clroclst(*blue);
				
			} 
	
		}

	} 


	if (pacman->check_collision(pacman->c,orange->c))
	{
		if (orange->sprt2use != 6 )
		{
			if (pacman->super == true)
			{
				if (orange->aistate != RUN_AWAY)
				{
					
					pacman->died = true;
					clroclst(*orange);					
				} else {
					orange->change_sprite(EATABLE);
					orange->is_eaten = true;
					
					return 0;
				}
			} else
			if (pacman->super == false)
			{
				pacman->died = true;
				clroclst(*orange);
				
			} 
	
		}

	}
	return 0;
}

int init_ghosts()
{

	red = new ghost;
	red->screen = screen;
	red->timeinbox = 0;
	red->type = RED;
	/* look right */
	red->create_sprites(2,3,89,16,16,0);
	/* look down */
	red->create_sprites(2,35,89,16,16,0);
	/* look left */
	red->create_sprites(2,67,89,16,16,0);
	/* look up */
	red->create_sprites(2,99,89,16,16,0);
	//scared ghost
	red->create_sprites(2,62,175,16,16,0);
	//white
	red->create_sprites(4,62,175,16,16,0);
	//eyes	
	red->create_sprites(4,70,165,14,10,0);

	pink = new ghost;
	pink->screen = screen;
	pink->timeinbox = 1;
	pink->type=PINK;
	/* look right */
	pink->create_sprites(2,3,108,16,16,0);
	/* look down */
	pink->create_sprites(2,35,108,16,16,0);
	/* look left */
	pink->create_sprites(2,67,108,16,16,0);
	/* look up */
	pink->create_sprites(2,99,108,16,16,0);

	//scared ghost
	pink->create_sprites(2,62,175,16,16,0);
	//white
	pink->create_sprites(4,62,175,16,16,0);
	//eyes	
	pink->create_sprites(4,70,165,14,10,0);

	blue = new ghost;
	blue->screen = screen;
	blue->timeinbox=10000;
	blue->type = BLUE;

	/* look right */
	blue->create_sprites(2,3,127,16,16,0);
	/* look down */
	blue->create_sprites(2,35,127,16,16,0);
	/* look left */
	blue->create_sprites(2,67,127,16,16,0);
	/* look up */
	blue->create_sprites(2,99,127,16,16,0);

	//scared ghost
	blue->create_sprites(2,62,175,16,16,0);
	//white
	blue->create_sprites(4,62,175,16,16,0);
	//eyes	
	blue->create_sprites(4,70,165,14,10,0);


	orange = new ghost;
	orange->screen = screen;
	orange->timeinbox=20000;
	orange->type = ORANGE;

	/* look right */
	orange->create_sprites(2,3,146,16,16,0);
	/* look down */
	orange->create_sprites(2,35,146,16,16,0);
	/* look left */
	orange->create_sprites(2,67,146,16,16,0);
	/* look up */
	orange->create_sprites(2,99,146,16,16,0);


	//scared ghost
	orange->create_sprites(2,62,175,16,16,0);
	//white
	orange->create_sprites(4,62,175,16,16,0);
	//eyes	
	orange->create_sprites(4,70,165,14,10,0);

	red->boxmovement = 1;
	red->followstate = 0;
	red->type = RED;
	red->aistate = START_UP;
	red->random_dir = RND1;

	
	pink->boxmovement = 1;
	pink->followstate = 0;
	pink->type = PINK;
	pink->aistate = AT_HOME;
	pink->random_dir = RND1;
	pink->y = 115;

	blue->boxmovement = 1;
	blue->followstate = 0;
	blue->type = BLUE;
	blue->aistate = AT_HOME;
	blue->random_dir = RND1;
	blue->y = 115;

	orange->boxmovement = 1;
	orange->followstate = 0;
	orange->type = ORANGE;
	orange->aistate = AT_HOME;
	orange->random_dir = RND1;
	orange->y = 115;
	
	
	gtimer = 11500;
	whichswitchmode = sw_corner;


	
	
		
	return 0;
}

int del_ghosts()
{

	delete(red);
	red=NULL;
	delete(pink);
	pink=NULL;

	delete(blue);
	blue=NULL;

	delete(orange);
	orange=NULL;

	return 0;
}

int keyghost(ghost &whchghst)
{

	keystates = SDL_GetKeyState( NULL ); 
	if( keystates[ SDLK_d ] ) 
	{
		if ( whchghst.fcollusion() != true)
		{
			 whchghst.move_forward();
			 if (pacman->super == false && whchghst.sprt2use != 6) whchghst.sprt2use = 0;
			 if (whchghst.x  > 239 && whchghst.y == 119)
			 {
				whchghst.x  = -49;
			 }
		
		}
	}
	if( keystates[ SDLK_a ] ) 
	{
		if (whchghst.bcollusion() != true) 
		{
			whchghst.move_left();
			if (pacman->super == false && whchghst.sprt2use != 6) whchghst.sprt2use = 2;
			if (whchghst.x  < -49 && whchghst.y == 119)
			{
				whchghst.x  = 239;
			} 
		}
	}
	if( keystates[ SDLK_s ] ) 
	{
		if (whchghst.dcollusion()!= true) 
		{
			whchghst.move_down();
			if (pacman->super == false  && whchghst.sprt2use != 6) whchghst.sprt2use=1;
		}
	}
	if( keystates[ SDLK_w ] ) 
	{	
		if (whchghst.ucollusion() != true) 
		{
			whchghst.move_up();
			if (pacman->super == false && whchghst.sprt2use != 6) whchghst.sprt2use=3;
		}
	}
	return 0;
}



int ghost::ai()
{


//55,214
	

	if (aitmr.is_started() == false)
	{
		aitmr.start();
	}
	if (aitmr.get_ticks() > speed)
	{
		//keyghost(*blue);
		
		//type=1;

		switch(aistate)
		{
			
			case START_UP:
			{
				if (is_sprite(EATABLE) == true)
				{
					if (rnawy->openlist != NULL) rnawy->openlist->delall();
	     				if (rnawy->closelist != NULL) rnawy->closelist->delall();
					speed = 160;
					rnawy->openlist->settarget(pacman->x,pacman->y);
					rnawy->closelist->settarget(pacman->x,pacman->y);
					rnawy->openlist->add2lst(x,y,10);
					aigbt = SCATTER;
					aistate = RUN_AWAY;
					return 0;

				}
				switch(type)
				{
					case RED:
					{
						switch(followstate)
						{
							case 0:
							{
								if (x == 78)
								{
									followstate++;
								} else {
									sprt2use = 2;
									move_left();
								}
								break;
							}
							case 1:
							{
								if (y == 119)
								{
									followstate++;
								} else {
									sprt2use=1;
									move_down();
								}
								break;
							}
							case 2:
							{
								if (x == 54)
								{
									followstate++;
								} else {
									sprt2use = 2;
									move_left();
								}
								break;
							}
							case 3:
							{
								if (y == 47)
								{
									followstate++;
								} else {
									sprt2use=3;
									move_up();
								}
								break;
							}
							case 4:
							{
								if (x == 174)
								{
									followstate++;
								} else {
									sprt2use = 0;
									move_forward();
								}
								break;
							}	
							case 5:
							{
								if (y == 15)
								{
									followstate++;
								} else {
									sprt2use=3;
									move_up();
								}
								break;
							}
							case 6:
							{
								if (x == 214)
								{
									followstate++;
								} else {
									sprt2use = 0;
									move_forward();
								}
								break;
							}
							case 7:
							{
								if (dcollusion())
								{
								} else {
									sprt2use=1;
									move_down();		
								}
								break;
							}
							//x=54
							break;
						}
						break;
					}
					break;
				}
				break;
			
			}
			case SCATTER:
			{
				if (is_sprite(EATABLE) == true)
				{
					if (GotoCorner->openlist != NULL)
					{
						GotoCorner->openlist->delall();
					} 
					if (GotoCorner->closelist != NULL)
					{
						GotoCorner->closelist->delall();
					}
					if (followpm->openlist != NULL)
					{
						followpm->openlist->delall();
					} 
					if (followpm->closelist != NULL)
					{
						followpm->closelist->delall();
					}
					speed = 160;
					if (rnawy->openlist != NULL) rnawy->openlist->delall();
					if (rnawy->closelist != NULL) rnawy->closelist->delall();
					rnawy->openlist->settarget(pacman->x,pacman->y);
					rnawy->closelist->settarget(pacman->x,pacman->y);
					rnawy->openlist->add2lst(x,y,10);
					aigbt = SCATTER;
					aistate = RUN_AWAY;
					break;
				}

				if (type == RED || type == PINK || type == BLUE || type == ORANGE)
				{
					if (GoPath(GotoCorner) == 1)
					{
					
						followpm->openlist->settarget(pacman->x,pacman->y);
						followpm->closelist->settarget(pacman->x,pacman->y);
						followpm->openlist->add2lst(x,y,10);
						pathtowhat = objects;
						iscorner = true;
						aistate = HUNT;	
						break;
					}
				}
				break;
			}
			case WONDER:    
			{
				
				/*
					go to random though random paths
					if pacman is seen then go to "hunt" mode
					if pacman eats super pebble then go to
					"run_away"
				*/


				/* go though the tunnel */
				if (x < 42 && y == 119)
				{
					if (followpm->openlist != NULL)
					{
						followpm->openlist->delall();
					} 
					if (followpm->closelist != NULL)
					{
						followpm->closelist->delall();
					}
					tunndir = 0;//LEFT;
					tunngobk = WONDER;
					aistate = GO_TUNNEL;
					break;
				}

				if (x > 190 && y == 119)
				{
					if (followpm->openlist != NULL)
					{
						followpm->openlist->delall();
					} 
					if (followpm->closelist != NULL)
					{
						followpm->closelist->delall();
					}
					tunndir = 1;//RIGHT;
					tunngobk = WONDER;
					aistate = GO_TUNNEL;
					break;
				}		
		
				if (is_sprite(EATABLE) == true)
				{
					if (GotoCorner->openlist != NULL)
					{
						GotoCorner->openlist->delall();
					} 
					if (GotoCorner->closelist != NULL)
					{
						GotoCorner->closelist->delall();
					}
					if (followpm->openlist != NULL)
					{
						followpm->openlist->delall();
					} 
					if (followpm->closelist != NULL)
					{
						followpm->closelist->delall();
					}
					if (rnawy->openlist != NULL) rnawy->openlist->delall();
					if (rnawy->closelist != NULL) rnawy->closelist->delall();
					speed = 160;
					rnawy->openlist->settarget(pacman->x,pacman->y);
					rnawy->closelist->settarget(pacman->x,pacman->y);
					rnawy->openlist->add2lst(x,y,10);
					aigbt = WONDER;
					aistate = RUN_AWAY;
					break;
				}
				switch(random_dir)
				{
					case RND1:
					{
			
	
						
						trandir = rand() % 3;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_LFT;
								break;	
							}
							case 1:
							{
								random_dir = GO_RGHT;
								break;
							}
							case 2:
							{
								random_dir = GO_LFT;
								break;	
							}
							case 3:
							{
								random_dir = GO_RGHT;
								break;
							}
							break;
						}
						break;
					}
					case RND2:
					{
						/* can go up, down, or left */
						trandir = rand() % 2;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_UP;
								break;
							}
							case 1:
							{
								random_dir = GO_DWN;
								break;
							}
							case 2:
							{
								random_dir = GO_LFT;
								break;
							}
							break;
						}
						break;
					}
					case RND3:
					{
						/* can go up of cont. left */
						trandir = rand() % 1;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_UP;
								break;
							}
							case 1:
							{
								random_dir = GO_LFT;
								break;
							}
							break;
						}
						break;
					}
					case RND4:
					{
						/* can go down of cont. left */
						trandir = rand() % 1;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_DWN;
								break;
							}
							case 1:
							{
								random_dir = GO_LFT;
								break;
							}
							break;
						}
						break;
					}
					case RND5:
					{
						/* can go up, down, or right */
						trandir = rand() % 2;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_UP;
								break;
							}
							case 1:
							{
								random_dir = GO_DWN;
								break;
							}
							case 2:
							{
								random_dir = GO_RGHT;
								break;
							}
							break;
						}
						break;
					}
					case RND6:
					{
						/* can go up of cont. right */
						trandir = rand() % 1;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_UP;
								break;
							}
							case 1:
							{
								random_dir = GO_RGHT;
								break;
							}
							break;
						}
						break;
					}
					case RND7:
					{
						/* can go down of cont. right */
						trandir = rand() % 1;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_DWN;
								break;
							}
							case 1:
							{
								random_dir = GO_RGHT;
								break;
							}
							break;
						}
						break;
					}
					case RND8:
					{
						/* can go left, right orpathtowhat = objects; cont. up */
						trandir = rand() % 2;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_LFT;
								break;
							}		
							case 1:
							{
								random_dir = GO_RGHT;
								break;
							}		
							case 2:
							{
								random_dir = GO_UP;
								break;
							}
							break;
						}
						break;
					}

					case RND9:
					{
						/* can go left or cont. up */
						trandir = rand() % 1;
						switch(trandir)
						{pathtowhat = objects;
							case 0:
							{
								random_dir = GO_LFT;
								break;
							}				
							case 1:
							{
								random_dir = GO_UP;
								break;
							}
							break;
						}
						break;
					}
					case RND10:
					{
						/* can go right or cont. up */
						trandir = rand() % 1;
						switch(trandir)
						{pathtowhat = objects;
							case 0:
							{
								random_dir = GO_RGHT;
								break;
							}				
							case 1:
							{
								random_dir = GO_UP;
								break;
							}
							break;
						}
						break;
					}
					case RND11:
					{
						/* can go left, right or cont. down */
						trandir = rand() % 2;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_LFT;
								break;
							}		
							case 1:
							{
								random_dir = GO_RGHT;
								break;
							}		
							case 2:
							{
								random_dir = GO_DWN;
								break;
							}
							break;
						}
						break;
					}

					case RND12:
					{
						/* can go left or cont. down */
						trandir = rand() % 1;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_LFT;
								break;
							}				
							case 1:
							{
								random_dir = GO_DWN;
								break;
							}
							break;
						}
						break;
					}
					case RND13:
					{
						/* can go right or cont. down */
						trandir = rand() % 1;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_RGHT;
								break;
							}				
							case 1:
							{
								random_dir = GO_DWN;
								break;
							}
							break;
						}
						break;
					}
					case RND14:
					{
						/* can go right, up, or down */
						trandir = rand() % 2;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_RGHT;
								break;
							}				
							case 1:
							{
								random_dir = GO_DWN;
								break;
							}
							case 2:
							{
								random_dir = GO_UP;
								break;
							}
							break;
						}
						break;
					}
					case RND15:
					{
						/* can go  up, or down */
						trandir = rand() % 1;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_UP;
								break;
							}				
							case 1:
							{
								random_dir = GO_DWN;
								break;
							}
							break;
						}
						break;
					}
					case RND16:
					{
						/* random left or up */
						trandir = rand() % 2;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_RGHT;
								break;
							}
							case 1:
							{
								random_dir = GO_LFT;
								break;
							}
							case 2:
							{
								random_dir = GO_DWN;
								break;
							}
							break;
						}
						break;
					}
					case RND17:
					{
						/* random right and down */
						trandir = rand() % 1;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_RGHT;
								break;
							}
							case 1:
							{
								random_dir = GO_DWN;
								break;
							}
							break;
						}
						break;
					}
					case RND18:
					{
						/* random right left and up */
						trandir = rand() % 1;
						switch(trandir)
						{
							case 0:
							{
								random_dir = GO_RGHT;
								break;
							}
							case 1:
							{
								random_dir = GO_LFT;
								break;
							}
							case 2:
							{
								random_dir = GO_UP;
								break;
							}
							break;
						}
						break;
					}

					case GO_LFT:
					{
						if (bcollusion() != true) 
						{
							move_left();
							if (is_eatable == false) sprt2use = 2; 

							if (x  == -30 && y == 119)
							{
								x  = 238;
							} 
							if (ucollusion() == false && dcollusion() == false)
							{
								//can go up, down or cont. left
								random_dir = RND2;
							} else
							if (ucollusion() == false && dcollusion() == true)
							{
								//can go up, or cont. left
								random_dir = GO_UP; // RND3;
							} else
							if (ucollusion() == true && dcollusion() == false)
							{
								//can go down or cont. left
								random_dir = GO_DWN; //RND4;
							}
							
						} else {
							
							if (ucollusion() == false && dcollusion() == false && fcollusion() == false)
							{
								/* up, down and forward */
								random_dir = RND14;
							} else
							if (ucollusion() == true && dcollusion() == false && fcollusion() == false)
							{
								/*down,right*/
								random_dir = RND7;
							} else
							if (ucollusion() == false && dcollusion() == false && fcollusion() == true)
							{
								/*up, down */
								random_dir = RND15;
							} else
							if (ucollusion() == true && dcollusion() == true && fcollusion() == false)
							{
								/* go right */
								random_dir = GO_RGHT;
							} else
							if (ucollusion() == true && dcollusion() == false && fcollusion() == true)
							{
								/* go down */
								random_dir = GO_DWN;
							} else
							if (ucollusion() == false && dcollusion() == true && fcollusion() == true)
							{						
								/* go up */
								random_dir = GO_UP;
							}
						}

						break;
					}
					case GO_RGHT:
					{
						if ( fcollusion() != true)
						{
							 move_forward();
							 if (is_eatable == false) sprt2use = 0;  
							 if (x  > 240 && y == 119)
							 {
								x  = -50;
							 }
							 if (ucollusion() == false && dcollusion() == false)
							 {
								//can go up, down or cont. right
								random_dir = RND5;
							 } else
							 if (ucollusion() == false && dcollusion() == true)
							 {
								//can go up, or cont. right
								random_dir = RND6;
							 } else
							 if (ucollusion() == true && dcollusion() == false)
							 {
								//can go down or cont. right 
								random_dir = RND7;
							 }
						} else {
							if (ucollusion() == false && dcollusion() == false && bcollusion() == false)
							{
								/* up, down and left*/
								random_dir = RND14;
							} else
							if (ucollusion() == true && dcollusion() == false && bcollusion() == false)
							{
								/*down,left*/
								random_dir = RND7;
							} else
							if (ucollusion() == false && dcollusion() == false && bcollusion() == true)
							{
								/*up, down */
								random_dir = RND15;
							} else
							if (ucollusion() == true && dcollusion() == true && bcollusion() == false)
							{
								/* go left */
								random_dir = GO_RGHT;
							} else
							if (ucollusion() == true && dcollusion() == false && bcollusion() == true)
							{
								/* go down */
								random_dir = GO_DWN;
							} else
							if (ucollusion() == false && dcollusion() == true && bcollusion() == true)
							{						
								/* go up */
								random_dir = GO_UP;
							}
						}
						break;
					}
					case GO_UP:
					{
						if (ucollusion() != true) 
						{
							move_up();
							if (is_eatable == false) sprt2use=3;
							if (fcollusion() == false && bcollusion() == false)
							{
								/* can go left or right or go cont. up */
								random_dir = RND8;
							} else
							if (fcollusion() == true && bcollusion() == false)
							{
								/* can go left or go cont. up */
								random_dir = RND9;
							} else
							if (fcollusion() == false && bcollusion() == true)
							{
								/* can go right or go cont. up */
								random_dir = RND10;
							}
						} else {
							if (fcollusion() == false && bcollusion() == false && dcollusion() == false)
							{
								/* can go right,left, and down */
								random_dir = RND16;
							} else
							if (fcollusion() == true && bcollusion() == false && dcollusion() == false)
							{
								/* left or down */
								random_dir = RND12;
							} else
							if (fcollusion() == false && bcollusion() == true && dcollusion() == false)
							{
								/* right, down */
								random_dir = RND17;
							} else
							if (fcollusion() == false && bcollusion() == false && dcollusion() == true)
							{
								/* right, left */
								random_dir = RND1;
							} else
							if (fcollusion() == true && bcollusion() == true && dcollusion() == false)
							{
								/* go down */
								random_dir = GO_RGHT;
							} else
							if (fcollusion() == true && bcollusion() == false && dcollusion() == true)
							{
							       /* go left */
							       random_dir = GO_LFT;
							} else
							if (fcollusion() == false && bcollusion() == true && dcollusion() == true)
							{
								/* go right */
							        random_dir = GO_RGHT;
							}
						}
						break;
					}
					case GO_DWN:
					{
						if (dcollusion() != true) 
						{
							move_down();
							if (is_eatable == false) sprt2use=1;
							if (fcollusion() == false && bcollusion() == false)
							{
								/* can go left or right or go cont. down */								random_dir = RND11;
		
							} else
							if (fcollusion() == true && bcollusion() == false)
							{
								/* can go left or go cont. down */
								random_dir = RND12;
							} else
							if (fcollusion() == false && bcollusion() == true)
							{
								/* can go right or go cont. down */
								random_dir = RND13;
							}
						} else {
							if (fcollusion() == false && bcollusion() == false && ucollusion() == false)
							{
								/* can go right,left, and up */
								random_dir = RND18;
							} else
							if (fcollusion() == true && bcollusion() == false && ucollusion() == false)
							{
								/* left or up */
								random_dir = RND16;
							} else
							if (fcollusion() == false && bcollusion() == true && ucollusion() == false)
							{
								/* right, up */
								random_dir = RND10;
							} else
							if (fcollusion() == false && bcollusion() == false && ucollusion() == true)
							{
								/* right, left */
								random_dir = RND1;
							} else
							if (fcollusion() == true && bcollusion() == true && ucollusion() == false)
							{
								/* go up */
								random_dir = GO_UP;
							} else
							if (fcollusion() == true && bcollusion() == false && ucollusion() == true)
							{
							       /* go left */
							       random_dir = GO_LFT;
							} else
							if (fcollusion() == false && bcollusion() == true && ucollusion() == true)
							{
								/* go right */
							        random_dir = GO_RGHT;
							}
						}
						break;
					}
					break;
				}
				break;
			}




			case HUNT:
			{
				/*
					if pacman not in ghost site then go to "WONDER" 
					if pacman eats super pebble then go to "RUN_AWAY"
				*/
				if (x < 42 && y == 119)
				{
					if (followpm->openlist != NULL)
					{
						followpm->openlist->delall();
					} 
					if (followpm->closelist != NULL)
					{
						followpm->closelist->delall();
					}
					tunndir = 0;//LEFT;
					tunngobk = HUNT;
					aistate = GO_TUNNEL;
					break;
				}
				if (x > 190 && y == 119)
				{
					if (followpm->openlist != NULL)
					{
						followpm->openlist->delall();
					} 
					if (followpm->closelist != NULL)
					{
						followpm->closelist->delall();
					}
					tunndir = 1;//RIGHT;
					tunngobk = HUNT;
					aistate = GO_TUNNEL;
					break;
				}

				if (is_sprite(EATABLE) == true)
				{
					//GotoCorner

					if (rnawy->openlist != NULL) rnawy->openlist->delall();
					if (rnawy->closelist != NULL) rnawy->closelist->delall();
					speed = 160;
					rnawy->openlist->settarget(pacman->x,pacman->y);
					rnawy->closelist->settarget(pacman->x,pacman->y);
					rnawy->openlist->add2lst(x,y,10);
					aigbt = HUNT;
					aistate = RUN_AWAY;
					break;
				}
				if (GoPath(followpm) == 1)
				{
					followpm->openlist->settarget(pacman->x,pacman->y);
					followpm->closelist->settarget(pacman->x,pacman->y);
					followpm->openlist->add2lst(x,y,10);
					pathtowhat = objects;
					iscorner = true;
					aistate = HUNT;	
				}
				
				break;
			}  
			case   RUN_AWAY:
			{
				/*
					if ghost change back then go to "WONDER"
					if ghost is eaten then go to "GO_HOME"
				*/
		
				if (is_sprite(EYES) == true)
				{
					/* get current locstion */
					gohome->openlist->settarget(114,115);
					gohome->closelist->settarget(114,115);
					gohome->openlist->add2lst(x,y,10);
					gohome->openlist->current->skip = true;
					pathtowhat = nonobjects;
					speed = 60;
					atimer.stop();
					doanime = false;
					aistate = GO_HOME;
					return 0; 
					
				}
			
				
				if (tatmr.is_started() == false)
				{
					tatmr.start();
				}

				if (tatmr.get_ticks() > ratmrlen )
				{
					if (rnawy->openlist != NULL) rnawy->openlist->delall();
					if (rnawy->closelist != NULL) rnawy->closelist->delall();
					rnawy->openlist->settarget(pacman->x,pacman->y);
					rnawy->closelist->settarget(pacman->x,pacman->y);
					rnawy->openlist->add2lst(x,y,10);
					tatmr.stop();	
				}
				runaway(rnawy);
			
				break;
			}
			case GO_HOME:
			{
				
				if (type == RED || type==PINK || type == BLUE || type == ORANGE)
				{
					if (GoPath(gohome) == 1)
					{
					
						animetmr = 600.f;
						eatable_tmr.stop();
						frame=0;
						change_sprite(LOOK_UP);					
						is_eaten = false;
						is_eatable = false;
						is_dead = false;
						speed = 60;
						sprt2use=0;
						doanime = true;
						has_been_eaten = true;
					
						pathtowhat = nonobjects;
						
						doanime = false;
						 
						
						atimer.start();
						aistate = AT_HOME;
						break;
					}
					
				}

				break;
			}
			case AT_HOME:	
			{

				/*char ghxy[255];
				sprintf(ghxy,"%i %i",x,y);
				print(ghxy,10,10);*/
				
				if (is_out_of_box == true)
				{								
					if (is_eatable == false) sprt2use = 3;

					if (movout != 5)
					{
						move_up();
						movout++;
					}  
					if (movout == 5)
					{
						movout=1;	
						speed = 60;
						doanime = true;
						if (whichswitchmode != sw_corner)
						{
							tbtimer.stop();
							
							if (GotoCorner->openlist != NULL)
							{
								GotoCorner->openlist->delall();	
							}		 
							if (GotoCorner->closelist != NULL)
							{
								GotoCorner->closelist->delall();
							}
							if (followpm->openlist != NULL)
							{
								followpm->openlist->delall();
							} 
							if (followpm->closelist != NULL)
							{
								followpm->closelist->delall();
							}
							followpm->openlist->settarget(pacman->x,pacman->y);
							followpm->closelist->settarget(pacman->x,pacman->y);
							followpm->openlist->add2lst(x,y,10);
							pathtowhat = objects;
							aistate = HUNT;
						} else {
							tbtimer.stop();

							if (GotoCorner->openlist != NULL)
							{
								GotoCorner->openlist->delall();	
							}		 
							if (GotoCorner->closelist != NULL)
							{
								GotoCorner->closelist->delall();
							}
							if (followpm->openlist != NULL)
							{
								followpm->openlist->delall();
							} 
							if (followpm->closelist != NULL)
							{
								followpm->closelist->delall();
							}
								
								
							if (type == RED)
							{
								GotoCorner->openlist->settarget(214,15);//14,15);//214,15);
								GotoCorner->closelist->settarget(214,15);//214,15);
							} else 
							if (type == PINK)
							{
								GotoCorner->openlist->settarget(14,15);//14,15);//214,15);
								GotoCorner->closelist->settarget(14,15);//214,15);
							}else 
							if (type == BLUE)
							{
								GotoCorner->openlist->settarget(14,15);//14,15);//214,15);
								GotoCorner->closelist->settarget(14,15);//214,15);
							}else 
							if (type == ORANGE)
							{
								GotoCorner->openlist->settarget(14,15);//14,15);//214,15);
								GotoCorner->closelist->settarget(14,15);//214,15);
							} 
							GotoCorner->openlist->add2lst(x,y,10);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  								pathtowhat = nonobjects;
							aistate= SCATTER;			
							remrbck = true;	
						}
					}
				} else

				if (tbtimer.is_started())
				{
					if (tbtimer.get_ticks() > timeinbox)
					{
						
						if (x == 114 && y == 95)
						{
							
							is_out_of_box = true;
							speed = 60;
							if (whichswitchmode != sw_corner)
							{
								tbtimer.stop();
								
								if (GotoCorner->openlist != NULL)
								{
									GotoCorner->openlist->delall();	
								}		 
								if (GotoCorner->closelist != NULL)
								{
									GotoCorner->closelist->delall();
								}
								if (followpm->openlist != NULL)
								{
									followpm->openlist->delall();
								} 
								if (followpm->closelist != NULL)
								{
									followpm->closelist->delall();
								}
								followpm->openlist->settarget(pacman->x,pacman->y);
								followpm->closelist->settarget(pacman->x,pacman->y);
								followpm->openlist->add2lst(x,y,10);
								pathtowhat = objects;
								aistate = HUNT;
							} else {
								tbtimer.stop();

								if (GotoCorner->openlist != NULL)
								{
									GotoCorner->openlist->delall();	
								}		 
								if (GotoCorner->closelist != NULL)
								{
									GotoCorner->closelist->delall();
								}
								if (followpm->openlist != NULL)
								{
									followpm->openlist->delall();
								} 
								if (followpm->closelist != NULL)
								{
									followpm->closelist->delall();
								}
								
								
								if (type == RED)
								{
									GotoCorner->openlist->settarget(214,15);//14,15);//214,15);
									GotoCorner->closelist->settarget(214,15);//214,15);
								} else 
								if (type == PINK)
								{
									GotoCorner->openlist->settarget(14,15);//14,15);//214,15);
									GotoCorner->closelist->settarget(14,15);//214,15);
								} else 
								if (type == BLUE)
								{
									GotoCorner->openlist->settarget(14,15);//14,15);//214,15);
									GotoCorner->closelist->settarget(14,15);//214,15);
								} else 
								if (type == ORANGE)
								{
									GotoCorner->openlist->settarget(14,15);//14,15);//214,15);
									GotoCorner->closelist->settarget(14,15);//214,15);
								}
								GotoCorner->openlist->add2lst(x,y,10);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  									pathtowhat = nonobjects;
								aistate= SCATTER;			
								remrbck = true;	
							}
						} else {
							if (type == PINK)
							{
								if (is_eatable == false ) sprt2use=3;
								move_up();
							} else
							if (type == BLUE)
							{

								if (x != 114)
								{
									 if (is_eatable == false) sprt2use=0;
									 move_forward();
									
								} else
								if (x == 114)
								{
									if (is_eatable == false ) sprt2use = 3;
									move_up();
								}
						
							} else
							if (type == ORANGE)
							{

								if (x != 114)
								{
									 if (is_eatable == false ) sprt2use=0;
									 move_left();
									
								} else
								if (x == 114)
								{
									if (is_eatable == false ) sprt2use = 3;
									move_up();
								}
						
							}
						} 
						
					} else {

						if (boxmovement == 0)
						{
							if (is_eatable == false && is_sprite(BLINK) == false) sprt2use=1;
							move_down();
								
							boxmovement = 1;
							break;		
						}
						if (boxmovement == 1)
						{
							if (is_eatable == false && is_sprite(BLINK) == false) sprt2use=1;
							move_down();
							boxmovement = 2;
							break;		
						}
						if (boxmovement == 2)
						{
							if (is_eatable == false && is_sprite(BLINK) == false) sprt2use=3;
							move_up();
							boxmovement=3;
							break;		
						}
						if (boxmovement == 3)
						{
							if (is_eatable == false && is_sprite(BLINK) == false) sprt2use=3;
							move_up();
							boxmovement=0;
							break;		
						}
					}
				
				} else {
					tbtimer.stop();
					tbtimer.start();
				}
				
				break;
			}
			case GO_TUNNEL:
			{
				if (tunndir == 0 && tunngoth == false)
				{
					move_left(); //go left
					if (x <= -22 && y == 119)
					{
						x = 239;
						tunngoth = true;	
					}
				} 
				if (tunndir == 1 && tunngoth == false)
				{
					move_forward();
					if (x >= 239 && y == 119)
					{
						x = -22;
						tunngoth = true;	
					}
					//go right
				}
				if (tunndir == 0 && tunngoth == true)
				{
					move_left();
					if (x <= 174 && y == 119)
					{
						
						if (is_eatable == true)
						{
							aistate = RUN_AWAY;
							break;
						} else
						if (tunngobk == HUNT)
						{
							if (followpm->openlist != NULL)
							{
								followpm->openlist->delall();
							} 
							if (followpm->closelist != NULL)
							{
								followpm->closelist->delall();
							}
							followpm->openlist->settarget(pacman->x,pacman->y);
							followpm->closelist->settarget(pacman->x,pacman->y);
							followpm->openlist->add2lst(x,y,10);
							pathtowhat = objects;
						} 

						aistate = tunngobk;
						tunngoth = false;
						break;
					}
				}
				if (tunndir == 1 && tunngoth == true)
				{
					move_forward();
					if (x >= 54 && y == 119)
					{	
						if (is_eatable == true)
						{
							aistate = RUN_AWAY;
							break;
						} else
						if (tunngobk == HUNT)
						{
							if (followpm->openlist != NULL)
							{
								followpm->openlist->delall();
							} 
							if (followpm->closelist != NULL)
							{
								followpm->closelist->delall();
							}
							followpm->openlist->settarget(pacman->x,pacman->y);
							followpm->closelist->settarget(pacman->x,pacman->y);
							followpm->openlist->add2lst(x,y,10);
							pathtowhat = objects;
						} 

						aistate = tunngobk;
						tunngoth = false;
						break;
					}
					
				}
				break;
			}
			break;
		}
		aitmr.stop();
	}
			
	return 0;
}

bool ghost::chkifeaten()
{
	return is_eaten;
}

int ghost::chgetmer()
{
	if (eatable_tmr.is_started())
	{
		if (eatable_tmr.get_ticks() > eatable_length - 2000.f)
		{
			blink_start();
		}
		if (eatable_tmr.get_ticks() > eatable_length)
		{
			turn_back();
			
		}
	}
	return 0;
}

int ghost::turn_back()
{

	
	animetmr = 600.f;
	eatable_tmr.stop();
	sprt2use=0;
	frame=0;
	is_eatable=false;
	pacman->super=false;

	if (is_sprite(EYES) == true) return 0;
	if (aistate == AT_HOME) return 0;

	if (aigbt == HUNT)
	{
		
		if (followpm->openlist != NULL)
		{
			followpm->openlist->delall();
		} 
		if (followpm->closelist != NULL)
		{
			followpm->closelist->delall();
		}
		
		followpm->openlist->settarget(pacman->x,pacman->y);
		followpm->closelist->settarget(pacman->x,pacman->y);
		followpm->openlist->add2lst(x,y,10);
	}
	if (aigbt == SCATTER)
	{
		if (GotoCorner->openlist != NULL)
		{
			GotoCorner->openlist->delall();
		} 
		if (GotoCorner->closelist != NULL)
		{
			GotoCorner->closelist->delall();
		}

		GotoCorner->openlist->settarget(214,15);//14,15);//214,15);
		GotoCorner->closelist->settarget(214,15);//214,15);
		GotoCorner->openlist->add2lst(x,y,10);
		pathtowhat = nonobjects;
	}
	speed = 60;
	aistate = aigbt; 	
	return 0;
}

int ghost::change_sprite(int sprite_num)
{
	sprt2use = sprite_num;
	return 0;
}

bool ghost::is_sprite(int sprite_num)
{
	if (sprt2use == sprite_num) return true;
	return false;
}


int ghost::blink_start()
{
	if (is_sprite(BLINK) == false)
	{
		animetmr = 100.f;
		change_sprite(BLINK);
		frame=0;
		
		
	}
	
	return 0;
}



int ghost::turn()
{
	if (sprt2use != 6)
	{
		animetmr = 600.f;
		change_sprite(EATABLE);
		frame=0;
		eatable_tmr.start();
		
	}
	return 0;
}

int ghost::reset()
{
	eatable_tmr.stop();
	animetmr = 100.f;
	frame=0;
	is_eaten = false;

}

bool ghost::dcollusion()
{
	Uint32 pixel; 
    	Uint8 r,g,b;
	for (int y2=2;y2<18;y2++)
	{
		for (int x2=1;x2<15;x2++)
		{
			pixel = get_pixel32(screen,x+x2,y+y2);
			SDL_GetRGB(pixel,screen->format,&r,&g,&b);
			if (r == 0 && g == 0 && b==0xff) return 1;
		}
	}
	if (x < 10 && y == 119)
	{
		return true;
	}
	if (x > 218 && y == 119)
	{
		return true;
	}
	if ((x == 114 && y==95) && (is_sprite(EYES) == false) ) return true;
	return false;	
}


bool ghost::ucollusion()
{
	Uint32 pixel; 
    	Uint8 r,g,b;
	for (int y2=-1;y2<12;y2++)
	{
		for (int x2=1;x2<15;x2++)
		{
			pixel = get_pixel32(screen,x+x2,y+y2);
			SDL_GetRGB(pixel,screen->format,&r,&g,&b);
			if (r == 0 && g == 0 && b==0xff) return 1;
		}
	}
	if (x < 10 && y == 119)
	{
		return true;
	}
	if (x > 218 && y == 119)
	{
		return true;
	}
	if (x == 74 && y == 119)
	{
		return 1;
	} else 
	if (x > 150 && x < 174 && y == 167)
	{
		return 1;
	} else
	if (x > 150 && x < 174 && y == 119)
	{
		return 1;
	} else
	if (x > 54 && x < 78 && y == 167)
	{
		return 1;
	} else
	if (x > 57 && x < 74 && y == 119)
	{
		return 1; 
	} else
	if (x > 77 && x < 100 && y == 95)
	{
		return 1;
	} else 
	if (x > 126 && x < 154 && y == 95)
	{
		return 1;
	} 
	return false;	
}

bool ghost::bcollusion()
{
	Uint32 pixel; 
    	Uint8 r,g,b;
	for (int y2=2;y2<15;y2++)
	{
		for (int x2=-2;x2<14;x2++)
		{
			pixel = get_pixel32(screen,x+x2,y+y2);
			SDL_GetRGB(pixel,screen->format,&r,&g,&b);
			if (r == 0 && g == 0 && b==0xff) return 1;
		}
	}

	if ( x==78 && y == 163)
	{
		return true;
	}
	if ( x== 78 && y == 153)
	{
		return true;
	}
	if (x == 126 && y == 91)
	{
		return 0;
	}
	if (x == 102 && y == 91)
	{
		return 1;
	} else
	if (x == 174 && y == 163)
	{
		return 1;
	} else 
	if (x == 174 && y == 115)
	{
		return 1;
	} else 
	if (x == 78 && y > 160 && y < 163)
	{
		return 1;
	} else
	if (x == 78 && y == 115)
	{
		return 1;
	} 
	return false;
}

bool ghost::fcollusion()
{
	Uint32 pixel; 
    	Uint8 r,g,b;
	for (int y2=1;y2<15;y2++)
	{
		for (int x2=12;x2<18;x2++)
		{
			pixel = get_pixel32(screen,x+x2,y+y2);
			SDL_GetRGB(pixel,screen->format,&r,&g,&b);
			if (r == 0 && g == 0 && b==0xff) return true;
		}
	}
	if (x ==  78 && y == 163)
	{
		return true;
	}

	if (x ==  54 && y == 115)
	{
		return true;
	}
	if (x == 126 && y == 91)
	{
		return true;
	}
	if (x == 150 && y==163)
	{
		return true;
	} else
	if (x == 150 && y==115)
	{
		return true;
	} else 
	if (x == 54 && y > 160 && y < 164)
	{
		return true;
	}  
	return false;
}




bool ghost::is_pm_super()
{
	if (pacman->super == false && sprt2use != 6) 
	{
		return false;
	}
	return true;
}

int ghost::GoPath(pathfinder* path)
{
	/*

	A* algorithm path finder 
	algoritm path based on the aStarTutorial.htm by Patrick Lester
	Edited to fit pacman	
	*/


	node* temp;
	node* tmp; 
	node* tmp2;
	node* lwstf;

	bool found=false;

	temp=NULL;
	temp = path->openlist->head;
		

	if (path->closelist->head != NULL)
	{
		/* find the lowest f on the open list. */

		while (temp)
		{	
			
			if (temp->parent_id == path->closelist->current->id)
			{
			
				if (path->lowestf != -1)
				{
					if (path->lowestf >= temp->f) 
					{
						path->lowestf = temp->f;
						path->x = temp->x;
						path->y = temp->y;
						path->lowestnodeid = temp->id; 
						path->g = 10;
		 				path->pdirection = temp->direction;
						temp->skip = true;
							
					} 
				} else {
					path->lowestf = temp->f;
					path->x = temp->x;
					path->y = temp->y;
					path->lowestnodeid = temp->id; 
					path->g = 10;
					path->pdirection = temp->direction;
					temp->skip = true;
				}	
			} 
	
			temp = temp->next;
		}

	} else {
		path->lowestf = temp->f;
		path->x = temp->x;
		path->y = temp->y;
		path->lowestnodeid = temp->id; 
		path->g = 10;
		path->pdirection = -2;
		temp->skip = true;	
	}
	
	/* delete the lowest node by ID */
	path->openlist->delnodebyid(path->lowestnodeid);
	

	/* add the lowest f on the list to the close list */
	path->closelist->add2lst(path->x,path->y,10);
	path->closelist->current->id = path->lowestnodeid;
	path->closelist->current->direction =path->pdirection;
	
	/*reset*/
	path->lowestf = -1;


        if (x != -1 && y != -1)
        {
		switch(aistate)
		{
			case SCATTER:
			{	
				frame = 0;	
				switch(path->closelist->current->direction)
				{	
					case right:
					{
						if (is_sprite(BLINK) == false) sprt2use = 0;
						break;
					}
					case left:
					{
						if (is_sprite(BLINK) == false) sprt2use = 2;
						break;
					}
					case up:
					{
						if (is_sprite(BLINK) == false) sprt2use=3;
						break;
					}
					case down:
					{
						if (is_sprite(BLINK) == false) sprt2use=1;
						break;
					}
					break;
				}
				break;
			}
			case HUNT:
			{	
				frame = 0;	
				switch(path->closelist->current->direction)
				{	
					case right:
					{
						if (is_sprite(BLINK) == false) sprt2use = 0;
						break;
					}
					case left:
					{
						if (is_sprite(BLINK) == false) sprt2use = 2;
						break;
					}
					case up:
					{
						if (is_sprite(BLINK) == false) sprt2use=3;
						break;
					}
					case down:
					{
						if (is_sprite(BLINK) == false) sprt2use=1;
						break;
					}
					break;
				}
				break;
			}
			case GO_HOME:
			{
				switch(path->closelist->current->direction)
				{
					case right:
					{
						frame = 0;
						break;
					}
					case left:
					{
						frame = 2;
						break;
					}
			
					case up:
					{
						frame = 3;
						break;
					}
					case down:
					{
						frame = 1;
						break;
					}
			
					break;
				}
				break;
			}
			break;
		}
        }

	/* Move to the spot */	
	x= path->closelist->current->x;
	y= path->closelist->current->y;
	
	found=false;

	/* check for up colusion*/
	if (ucollusion() != true)
	{
		
		tmp = NULL;
		tmp = path->openlist->head;
		
		/* check the open list for dupicates */
		while (tmp != NULL)
		{
			if (tmp->x == path->closelist->current->x && tmp->y == path->closelist->current->y-4)
			{
				found = true;
			}		
					
			tmp = tmp->next;
		}

		/* checks the close list for dupicates*/
		node* tmpcl = path->closelist->head;
		
		while(tmpcl !=NULL)
		{

			if (tmpcl->x == path->closelist->current->x && tmpcl->y == path->closelist->current->y-4)
			{
				found = true;
			}
			tmpcl = tmpcl->next;
		}
		
		
		//If dupicates is not be found add it to the list.
		if (found == false)
		{
			path->openlist->add2lst(path->closelist->current->x,path->closelist->current->y-4,10);
			path->openlist->current->direction = up;
			path->openlist->current->parent_id = path->closelist->current->id;
		}
	}

	found = false;
	
	//check down colusion
	if (dcollusion() != true)
	{
		
		tmp = NULL;
		tmp = path->openlist->head;
			
		while (tmp != NULL)
		{
					
			if (tmp->x == path->closelist->current->x && tmp->y == path->closelist->current->y+4)
			{
				found = true;
							
			}			
			tmp = tmp->next;
		}

		node* tmpcl = path->closelist->head;
		
		while(tmpcl !=NULL)
		{

			if (tmpcl->x == path->closelist->current->x && tmpcl->y == path->closelist->current->y+4)
			{
				found = true;
			}
			tmpcl = tmpcl->next;
		}

		//if its not on the list then add it.
		if (found == false)
		{
			path->openlist->add2lst(path->closelist->current->x,path->closelist->current->y+4,10);
			path->openlist->current->parent_id = path->closelist->current->id;
			path->openlist->current->direction = down;
		}
	}		

	found = false;

	//check left colusion
	if (fcollusion() != true)
	{

		tmp=NULL;
		tmp = path->openlist->head;
		
		while (tmp != NULL)
		{
					
			if (tmp->x == path->closelist->current->x+4 && tmp->y == path->closelist->current->y)
			{
				found = true;
							
			}
					
			tmp = tmp->next;
		}
		

		/* checks the close list*/
		node* tmpcl = path->closelist->head;
		
		while(tmpcl !=NULL)
		{

			if (tmpcl->x == path->closelist->current->x+4 && tmpcl->y == path->closelist->current->y)
			{
				found = true;
			}
			tmpcl = tmpcl->next;
		}

		if (x == 174 && y == 71 && path->openlist->targety == 118 && path->openlist->targetx > 190) found = true;

		if (x == 174 && y == 119 && path->openlist->targety != 118) found = true;

		if (x == 174 && y == 71 && path->openlist->targetx > 174 && path->openlist->targety > 147)
		{
			found = true;
		}

		if (x == 174 && y == 167 && remrbck == true)
		{
			found = true;
			
		}
		//if its not on the open list, add it
		if (found == false)
		{
			path->openlist->add2lst(path->closelist->current->x+4,path->closelist->current->y,10);
			path->openlist->current->direction = right;
			path->openlist->current->parent_id =  path->closelist->current->id;
		}

	}


	//right colusion detection
	found = false;
	if (bcollusion() != true)
	{
					
		tmp = NULL;
		tmp = path->openlist->head;
			
		while (tmp != NULL)
		{
					
			if (tmp->x == path->closelist->current->x-4 && tmp->y == path->closelist->current->y)
			{
				found = true;
			}
			tmp = tmp->next;
		}
		
		/* checks the close list*/
		node* tmpcl = path->closelist->head;
		
		while(tmpcl !=NULL)
		{

			if (tmpcl->x == path->closelist->current->x-4 && tmpcl->y == path->closelist->current->y)
			{
				found = true;
			}
			tmpcl = tmpcl->next;
		}
		
		if (x == 54 && y == 71 && path->openlist->targety == 118 && path->openlist->targetx < 42) found = true;


		if (x == 54 && y == 119 && path->openlist->targety != 118) found = true;

		if (x == 54 && y == 71 && path->openlist->targetx < 54 && path->openlist->targety > 147)
		{
			found = true;
		}
		if (found == false)
		{
			path->openlist->add2lst(path->closelist->current->x-4,path->closelist->current->y,10);
			path->openlist->current->direction = left;
			path->openlist->current->parent_id =  path->closelist->current->id;
			
		}
	}

	if (path->openlist->current->x == path->openlist->targetx && path->openlist->current->y == path->openlist->targety && pathtowhat == nonobjects) 
	{						
		path->closelist->delall();
		path->openlist->delall();
		pathtowhat = -1;
		if (remrbck == true) remrbck = false;
		return 1;
	}  

	if (path->openlist->current->x+1 == path->openlist->targetx && path->openlist->current->y-1 == path->openlist->targety && pathtowhat == objects) 
	{						
		path->closelist->delall();
		path->openlist->delall();
		pathtowhat = -1;
		return 1;
	}  

	return 0;	
}


int ghost::runaway(pathfinder* path)
{
	node* temp;
	node* tmp; 
	node* tmp2;
	node* lwstf;

	bool found=false;

	temp=NULL;
	temp = path->openlist->head;
		

	if (path->closelist->head != NULL)
	{
		/* find the lowest f on the open list. */

		while (temp)
		{	
			
			if (temp->parent_id == path->closelist->current->id)
			{
			
				if (path->lowestf != -1)
				{
					if (path->lowestf <= temp->f) 
					{
						path->lowestf = temp->f;
						path->x = temp->x;
						path->y = temp->y;
						path->lowestnodeid = temp->id; 
						path->g = 10;
		 				path->pdirection = temp->direction;
						temp->skip = true;
							
					} 
				} else {
					path->lowestf = temp->f;
					path->x = temp->x;
					path->y = temp->y;
					path->lowestnodeid = temp->id; 
					path->g = 10;
					path->pdirection = temp->direction;
					temp->skip = true;
				}	
			} 
	
			temp = temp->next;
		}

	} else {
		path->lowestf = temp->f;
		path->x = temp->x;
		path->y = temp->y;
		path->lowestnodeid = temp->id; 
		path->g = 10;
		path->pdirection = -2;
		temp->skip = true;	
	}
	
	/* delete the lowest node by ID */
	path->openlist->delnodebyid(path->lowestnodeid);
	

	/* add the lowest f on the list to the close list */
	path->closelist->add2lst(path->x,path->y,10);
	path->closelist->current->id = path->lowestnodeid;
	path->closelist->current->direction =path->pdirection;
	
	/*reset*/
	path->lowestf = -1;


	/* Move to the spot */	
	x= path->closelist->current->x;
	y= path->closelist->current->y;
	
	found=false;

	/* check for up colusion*/
	if (ucollusion() != true)
	{
		
		tmp = NULL;
		tmp = path->openlist->head;
		
		/* check the open list for dupicates */
		while (tmp != NULL)
		{
			if (tmp->x == path->closelist->current->x && tmp->y == path->closelist->current->y-4)
			{
				found = true;
			}		
					
			tmp = tmp->next;
		}

		/* checks the close list for dupicates*/
		node* tmpcl = path->closelist->head;
		
		while(tmpcl !=NULL)
		{

			if (tmpcl->x == path->closelist->current->x && tmpcl->y == path->closelist->current->y-4)
			{
				found = true;
			}
			tmpcl = tmpcl->next;
		}
		
		
		//If dupicates is not be found add it to the list.
		if (found == false)
		{
			path->openlist->add2lst(path->closelist->current->x,path->closelist->current->y-4,10);
			path->openlist->current->direction = up;
			path->openlist->current->parent_id = path->closelist->current->id;
		}
	}

	found = false;
	
	//check down colusion
	if (dcollusion() != true)
	{
		
		tmp = NULL;
		tmp = path->openlist->head;
			
		while (tmp != NULL)
		{
					
			if (tmp->x == path->closelist->current->x && tmp->y == path->closelist->current->y+4)
			{
				found = true;
							
			}			
			tmp = tmp->next;
		}

		node* tmpcl = path->closelist->head;
		
		while(tmpcl !=NULL)
		{

			if (tmpcl->x == path->closelist->current->x && tmpcl->y == path->closelist->current->y+4)
			{
				found = true;
			}
			tmpcl = tmpcl->next;
		}

		//if its not on the list then add it.
		if (found == false)
		{
			path->openlist->add2lst(path->closelist->current->x,path->closelist->current->y+4,10);
			path->openlist->current->parent_id = path->closelist->current->id;
			path->openlist->current->direction = down;
		}
	}		

	found = false;

	//check left colusion
	if (fcollusion() != true)
	{

		tmp=NULL;
		tmp = path->openlist->head;
		
		while (tmp != NULL)
		{
					
			if (tmp->x == path->closelist->current->x+4 && tmp->y == path->closelist->current->y)
			{
				found = true;
							
			}
					
			tmp = tmp->next;
		}
		

		/* checks the close list*/
		node* tmpcl = path->closelist->head;
		
		while(tmpcl !=NULL)
		{

			if (tmpcl->x == path->closelist->current->x+4 && tmpcl->y == path->closelist->current->y)
			{
				found = true;
			}
			tmpcl = tmpcl->next;
		}

		if (x == 174 && y == 71 && path->openlist->targety == 118 && path->openlist->targetx > 190) found = true;

		if (x == 174 && y == 119 && path->openlist->targety != 118) found = true;

		if (x == 174 && y == 71 && path->openlist->targetx > 174 && path->openlist->targety > 147)
		{
			found = true;
		}
		//if its not on the open list, add it
		if (found == false)
		{
			path->openlist->add2lst(path->closelist->current->x+4,path->closelist->current->y,10);
			path->openlist->current->direction = right;
			path->openlist->current->parent_id =  path->closelist->current->id;
		}

	}


	//right colusion detection
	found = false;
	if (bcollusion() != true)
	{
					
		tmp = NULL;
		tmp = path->openlist->head;
			
		while (tmp != NULL)
		{
					
			if (tmp->x == path->closelist->current->x-4 && tmp->y == path->closelist->current->y)
			{
				found = true;
			}
			tmp = tmp->next;
		}
		
		/* checks the close list*/
		node* tmpcl = path->closelist->head;
		
		while(tmpcl !=NULL)
		{

			if (tmpcl->x == path->closelist->current->x-4 && tmpcl->y == path->closelist->current->y)
			{
				found = true;
			}
			tmpcl = tmpcl->next;
		}
		
		if (x == 54 && y == 71 && path->openlist->targety == 118 && path->openlist->targetx < 42) found = true;


		if (x == 54 && y == 119 && path->openlist->targety != 118) found = true;

		if (x == 54 && y == 71 && path->openlist->targetx < 54 && path->openlist->targety > 147)
		{
			found = true;
		}
		if (found == false)
		{
			path->openlist->add2lst(path->closelist->current->x-4,path->closelist->current->y,10);
			path->openlist->current->direction = left;
			path->openlist->current->parent_id =  path->closelist->current->id;
			
		}
	}
	return 0;
}

int ghost::delPath(pathfinder* path)
{
	if (path != NULL)
	{
 
		if (path->closelist == NULL)
		{
			path->closelist->delall();
		}
		if (path->openlist == NULL)
		{
			path->openlist->delall();
		}
		delete path;
		path = NULL;
	}	
	return 1;
}


ghost::~ghost()
{
	delete gohome;
	gohome = NULL;

	delete GotoCorner;
	GotoCorner=NULL;

	delete(followpm);
	followpm=NULL;

	delPath(gohome);
	delPath(GotoCorner);
	delPath(followpm);
	delPath(rnawy);
		
}

int clroclst(ghost &theghost)
{
	if (theghost.GotoCorner->openlist != NULL)
	{
		theghost.GotoCorner->openlist->delall();
	} 
	if (theghost.GotoCorner->closelist != NULL)
	{
		theghost.GotoCorner->closelist->delall();
	}
	if (theghost.followpm->openlist != NULL)
	{
		theghost.followpm->openlist->delall();
	} 
	if (theghost.followpm->closelist != NULL)
	{
		theghost.followpm->closelist->delall();
	}
	if (theghost.gohome->openlist != NULL)
	{
		theghost.gohome->openlist->delall();
	} 
	if (theghost.gohome->closelist != NULL)
	{
		theghost.gohome->closelist->delall();
	}
	return 0;
}

int show_ghosts()
{
	red->show_frame(image,red->sprt2use,red->frame);	
	pink->show_frame(image,pink->sprt2use,pink->frame);
	blue->show_frame(image,blue->sprt2use,blue->frame);
	orange->show_frame(image,orange->sprt2use,orange->frame);
	pacman->show_frame(curtimg,sprnum,pacman->frame);
	return 0;
}
