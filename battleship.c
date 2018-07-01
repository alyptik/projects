#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

#include "msmud.h"

int us = 0, them = 0;

#define N_X  26
#define N_Y  5

#define SHIPS  8

struct battleship_board
{
  struct
  {
    int bombs, hit, miss, sunk;
    char last_cmd[4];
  } player[2];
  char board[N_Y][N_X];
  int turn;
};

struct battleship_board *table = 0;

int init_game(CHAR_DATA *ch, CHAR_DATA *victim);
void cleanup_game(void);
void showBattle(CHAR_DATA *ch);

int checkShip(int x, int y, int o, int d, int l)
{
  int xd, yd, i;

  if(!o)
  {
    if(!d)
    {
      yd = -1;
      if((y - l) < 0) return 0;
    }
    else
    {
      yd = 1;
      if((y + l) >= N_X) return 0;
    }
    xd = 0;
  }
  else
  {
    if(!d)
    {
      xd = -1;
      if((x - l) < 0) return 0;
    }
    else
    {
      xd = 1;
      if((x + l) >= N_Y) return 0;
    }
    yd = 0;
  }
  
  for(i = 0; i < l; i++)
    if(table->board[x += (o ? xd : 0)][y += (o ? 0 : yd)] != '~')
      return 0;

  return 1;  
}

void genShip(int player)
{
  int x, y, o, d, i, l, yd=0, xd=0;
  static int horiz = 0;

  while(1)
  {
    x = number(0, N_Y);
    y = number(0, N_X);

    o = (number(1, 10) < 6);
    d = (number(1, 10) < 6);

    l = number(3, 5);

    if(checkShip(x, y, o, d, l))
    {
      if(!o)
      {
        if(horiz < 2) continue;
        if(!d)
          yd = -1;
        else
          yd = 1;
        xd = 0;
      }
      else
      {
        horiz++;
        if(!d)
          xd = -1;
        else
          xd = 1;
        yd = 0;
      }
  
      for(i = 0; i < l; i++)
        table->board[x += (o ? xd : 0)][y += (o ? 0 : yd)] = player ? (o ? 'H' : 'X') : (o ? 'M' : 'N');

      return;
    }
  }
}

void genBattle(void)
{
  int x, y;

  for(y = 0; y < N_Y; y++)
    for(x = 0; x < N_X; x++)
      table->board[y][x] = '~';

  for(x = 0; x < SHIPS; x++)
  {
    genShip(0);
    genShip(1);
  }
  strcpy(table->player[0].last_cmd, "");
  strcpy(table->player[1].last_cmd, "");
}

int countShips(int player)
{
  int x, y, sections = 0;

  for(x = 0; x < N_Y; x++)
    for(y = 0; y < N_X; y++)
      if(!player)
      {
        if(table->board[x][y] == 'H' || table->board[x][y] == 'X')
          sections++;
      }
      else
      {
        if(table->board[x][y] == 'M' || table->board[x][y] == 'N')
          sections++;
      }
  return sections - 1;
}

int checkSunk(int x, int y, int player)
{
  int i;
  char target;

  target = table->board[x][y];

  switch(target)
  {
    case 'M':  
    case 'H':
      for(i = x + 1; i < N_Y; i++)
      {
        if( (table->board[i][y] == 'M' && player) ||  (table->board[i][y] == 'H' && !player) )
          return 0;

        if(table->board[i][y] == '~' || table->board[i][y] == '*' || table->board[i][y] == 'o')
          break;
      }

      for(i = x - 1; i >= 0; i--)
      {
        if( (table->board[i][y] == 'M' && player) ||  (table->board[i][y] == 'H' && !player) )
          return 0;

        if(table->board[i][y] == '~' || table->board[i][y] == '*' || table->board[i][y] == 'o')
          break;
      }
      return 1;
      break;
 
    case 'N':
    case 'X':
      for(i = y + 1; i < N_X; i++)
      {
        if( (table->board[x][i] == 'N' && player) ||  (table->board[x][i] == 'X' && !player) )
          return 0;

        if(table->board[x][i] == '~' || table->board[x][i] == '*' || table->board[x][i] == 'o')
          break;
      }

      for(i = y - 1 ; i >= 0; i--)
      {
        if( (table->board[x][i] == 'N' && player) ||  (table->board[x][i] == 'X' && !player) )
          return 0;

        if(table->board[x][i] == '~' || table->board[x][i] == '*' || table->board[x][i] == 'o')
          break;
      }
      return 1;
      break;
  } 
}

void bomb(CHAR_DATA *ch, char *location)
{
  int x, y, hit=0, sections, sunk=0;
  int player = ch->battleship_player - 1;
  char buf[1024];
  CHAR_DATA *victim = get_player(ch->battleship_opponent);

  if(!victim)
  {
    send_to_char("Your opponent is no longer in the game.\n\r", ch);
    ch->battleship_player =0;
    free(ch->battleship_opponent);
    cleanup_game();
    return;
  }

  if(player < 0 || player > 1)
  {
    printf("Invalid player!  Player one: 0, player two: 1.\n");
    return;
  }

  x = toupper(location[0]) - 65;
  y = atoi(location + 1);

  if(y <= 0 || y > N_X || x < 0 || x > N_Y)
  {
    send_to_char("Showing battlefield!\n", ch);
    return;
  }
  
  strncpy(table->player[player].last_cmd, location, 3);

  y--;

  if(player == 0)
  {
    if(table->board[x][y] == 'H' || table->board[x][y] == 'X')
      hit = 1;
  }
  else
  {
    if(table->board[x][y] == 'M' || table->board[x][y] == 'N')
      hit = 1;
  }  

  sunk = checkSunk(x, y, player);

  if(hit == 1)
  {
    if(!player)
      table->board[x][y] = '@';
    else
      table->board[x][y] = '&';
    table->player[player].hit++;
  }
  else
  {
    if(table->board[x][y] == '~')
      if(player == 0)
        table->board[x][y] = '*';
      else
        table->board[x][y] = 'o';
    table->player[player].miss++;
  }

  showBattle(ch);
  showBattle(victim);

  if(hit == 1)
  {
    send_to_char("\n\r--- &rHIT!&n ---\n\r", ch);

    if(sunk)
    {
      send_to_char("\n\rYou sunk their ship!!  ", ch);
      table->player[player].sunk++;

      if(!(sections = countShips(player)))
      {
        send_to_char("You have WON!  Congratulations!\n\r", ch);

  sprintf(buf, "&np1 bombs: %d, hits: %d, miss: %d, sunk: %d\n\rP2 bombs: %d, hits: %d, miss: %d, sunk: %d\n\r", table->player[0].bombs, 
          table->player[0].hit, table->player[0].miss, table->player[0].sunk, table->player[1].bombs, table->player[1].hit, table->player[1].miss,
          table->player[1].sunk);
        send_to_char(buf, ch);

        ch->battleship_player = 0;

        if(!victim)
        {
          free(ch->battleship_opponent);
          cleanup_game();
          return;
        }

        send_to_char("You have LOST the game of Battleship!  Sorry, sucker.\n\r", victim);
        send_to_char(buf, victim);
 
        victim->battleship_player = 0;
        free(victim->battleship_opponent);
        free(ch->battleship_opponent);
        cleanup_game();
        return;
      }
      else
      {
        sprintf(buf,"There are %d ship sections left.\n\r", sections);
        send_to_char(buf, ch);
      }
    }
  }
  else
  {
    send_to_char("\n\r--- miss ---\n\r ", ch);
  }
  table->player[player].bombs++;
}

void showBattle(CHAR_DATA *ch)
{
  int x,y, player;
  char buf[1024];

  player = ch->battleship_player - 1;

    if(strlen(table->player[player ? 0 : 1].last_cmd))
      sprintf(buf, "Player %s has attacked %s\n\r\n\r", player ? "one" : "two", table->player[player ? 0 : 1].last_cmd);
    else
      sprintf(buf, "\n\r");
    send_to_char(buf, ch);


  sprintf(buf,             "&n/----------------------------\\\n\r");
  sprintf(buf+strlen(buf), "|           &y1         2      |\n\r");
  sprintf(buf+strlen(buf), "|&n&c  123456789&y0&c123456789&y0&c123456&n|\n\r");

  for(y=0; y < N_Y; y++)
  {
    sprintf(buf+strlen(buf), "|&c%c ", 97+y);
    for(x = 0; x < N_X; x++)
    {
      if(player == 0)
      {
        if(table->board[y][x] == 'H' || table->board[y][x] == 'X')
        {
          sprintf(buf+strlen(buf), "&b~");
          continue;
        } else
        {
          if(table->board[y][x] == '@' || table->board[y][x] == '&')
            sprintf(buf+strlen(buf), "&r");
          else if(table->board[y][x] == 'o' || table->board[y][x] == '*')
            sprintf(buf+strlen(buf), "&m");
          else if(table->board[y][x] == '~')
            sprintf(buf+strlen(buf), "&b");
          else
            sprintf(buf+strlen(buf), "&w");
          if(table->board[y][x] == '&')
            sprintf(buf+strlen(buf), "&&");
          else
            sprintf(buf+strlen(buf), "%c", table->board[y][x]);
        }
      } else
      {
        if(table->board[y][x] == 'M' || table->board[y][x] == 'N')
        {
          sprintf(buf+strlen(buf), "&b~");
          continue;
        } else
        {
          if(table->board[y][x] == '@' || table->board[y][x] == '&')
            sprintf(buf+strlen(buf), "&r");
          else if(table->board[y][x] == 'o' || table->board[y][x] == '*')
            sprintf(buf+strlen(buf), "&m");
          else if(table->board[y][x] == '~')
            sprintf(buf+strlen(buf), "&b");
          else
            sprintf(buf+strlen(buf), "&w");
          if(table->board[y][x] == '&')
            sprintf(buf+strlen(buf), "&&");
          else
            sprintf(buf+strlen(buf), "%c", table->board[y][x]);
        }
      }
    }
    sprintf(buf+strlen(buf), "&n|\n\r");
  }
    sprintf(buf+strlen(buf),             "\\----------------------------/\n\r");
 
  if(player == 0)
    send_to_char(" Player One Legend:  ships: [M/N]  ocean: [&b~~&n]   player one miss: [*]  player two miss: [o]  player one hit: [&r@&n]  p2 hit: [&r&&&n]\n\r\n\r", ch);
  else
    send_to_char(" Player Two Legend:  ships: [H/X]  ocean: [&b~~&n]   player one miss: [*]  player two miss: [o]  player one hit: [&r@&n]  p2 hit: [&r&&&n]\n\r\n\r", ch);

   send_to_char(buf, ch);

  sprintf(buf, "Player One:  bombs fired: %3d, hits: %3d, misses: %3d, ships sunk: %3d, sections left: %d\n\rPlayer Two:  bombs fired: %3d, hits: %3d, misses: %3d, ships sunk: %3d, sections left: %d\n\r",
               table->player[0].bombs, table->player[0].hit, table->player[0].miss, table->player[0].sunk, countShips(1)+1,  table->player[1].bombs, table->player[1].hit, 
table->player[1].miss,table->player[1].sunk, countShips(0)+1);

  send_to_char(buf, ch);

  if((table->turn == 1 && ch->battleship_player == 1) || (table->turn == 2 && ch->battleship_player == 2))
  {
    send_to_char("\n\rIt is your turn.\n\r", ch);
  }
  else
  {
    send_to_char("\n\rIt is not your turn.\n\r",ch);	
  }
}

COMMAND(do_challenge)
{
  char buf[1024], arg1[512], arg2[512], arg3[512], arg4[512],buf2[1024];
  CHAR_DATA *victim;

  if(ch->battleship_player == 3)
  {
    send_to_char("Please wait patiently for the challenge to be answered.\n\r", ch);
    return;
  }

  if(ch->battleship_player == 4)
  {
    send_to_char("Please answer the challenge against you.\n\r", ch);
    return;
  }

  if(ch->battleship_player)
  {
    send_to_char("But you're already playing a game!  Use 'concede' to exit this game and receive a loss.\n\r", ch);
    return;
  }

  if(table)
  {
    send_to_char("Unfortunately the only Battleship board available here is currently in use.  Please wait patiently and try again later.\n\r", ch);
    send_to_char("This is only temporarily until we have the funding to purchase more boards for the community.\n\r", ch);
    return;
  }

  half_chop(argument, arg1, buf);
  half_chop(buf, arg2, buf2);  
  half_chop(buf2, arg3, arg4);

  if(!strlen(arg1))
  {
    send_to_char("Usage:  challenge <opponent> [board width] [board height] [number of ships] (defaults: 26 x 5 x 8)\n\r", ch);
    return;
  }

  if(!(victim = get_player(arg1)))
  {
     send_to_char("No-one by that name in the world.\n\r", ch);
     return;
  }  

  if(IS_NPC(victim))
  {
    send_to_char("A creature does not have the wits required for this game.  You must challenge a real player.\n\r", ch);
    return;
  }

  if(victim == ch)
  {
    send_to_char("You may not challenge yourself, sorry.\n\r", ch);
    return;
  }

  if(victim->battleship_player)
  {
    send_to_char("That person is already engaged in a game.  Try again later.\n\r", ch);
    return;
  }

  sprintf(buf, "You've challenged %s to a game of Battleship.  Please wait patiently for the response.  You may use 'concede' to abort the challenge.\n\r",
               GET_NAME(victim));
  send_to_char(buf, ch);

  sprintf(buf, "%s has challenged you to a game of Battleship!  Respond with 'play accept' to accept or 'play decline' to refuse.\n\r", GET_NAME(ch));
  send_to_char(buf, victim);

  ch->battleship_player = 3;
  victim->battleship_player = 4;

  ch->battleship_opponent = strdup(GET_NAME(victim));
  victim->battleship_opponent = strdup(GET_NAME(ch));

  return;
}

COMMAND(do_concede)
{
  char buf[1024];
  CHAR_DATA *victim;

  if(!ch->battleship_player)
  {
    send_to_char("You have not challenged anyone to a game of battleship.  Use: challenge <player> [board width] [board height] [number of ships]  (defaults:  26x5 with 8 ships).\n\r", ch);  
    return;
  }

  if(ch->battleship_player == 4)
  {
    send_to_char("Please answer the challenge with either 'play accept' or 'play decline'.\n\r", ch);
    return;
  }

  if(ch->battleship_player == 3)
  {
    send_to_char("You abort the challenge.\n\r", ch);
    if(victim = get_player(ch->battleship_opponent))
    {
      sprintf(buf, "%s has aborted the challenge.\n\r", GET_NAME(ch));
      send_to_char(buf, victim);
      free(victim->battleship_opponent);
      victim->battleship_player = 0;
    }
    free(ch->battleship_opponent);
    ch->battleship_player = 0;
    return;
  }

  if(!(victim = get_player(ch->battleship_opponent)))
  {
    send_to_char("Hmm, your opponent has left the game already.\n\r", ch);
    free(ch->battleship_opponent);
    ch->battleship_player = 0;
    return;
  }
  
  sprintf(buf, "%s has conceded the game to you.\n\r", GET_NAME(ch));
  send_to_char(buf, victim);
  sprintf(buf, "You concede the game to %s.\n\r", GET_NAME(victim));
  send_to_char(buf, ch);

  free(victim->battleship_opponent);
  free(ch->battleship_opponent);
  ch->battleship_player = 0;
  victim->battleship_player = 0;

  cleanup_game();
}

COMMAND(do_play)
{
  char buf[1024];
  CHAR_DATA *victim;
  int row, col;

  if(!ch->battleship_player)
  {
    send_to_char("You have not challenged anyone to a game of battleship.  Use: challenge <player> [board width] [board height] [number of ships]  (defaults:  26x5 with 8 ships).\n\r", ch);  
    return;
  }

  if(ch->battleship_player == 3)
  {
    send_to_char("Please wait patiently for your challenge to be answered.\n\r", ch);
    return;
  }

  if(ch->battleship_player == 4)
  {
    one_argument(argument, buf);

    if(!strcasecmp(buf, "accept"))
    {
      if(!(victim = get_player(ch->battleship_opponent)))
      {
        send_to_char("The challenger does not appear to be in the game.\n\r", ch);
        ch->battleship_player = 0;
        return;
      }
      send_to_char("Challenge accepted!\n\r", victim);
      send_to_char("You accept the challenge.\n\r", ch);

      victim->battleship_player = 1;
      ch->battleship_player = 2;

      init_game(victim, ch);

      return;
    }
 
    if(!strcasecmp(buf, "decline"))
    {
      if(!(victim = get_player(ch->battleship_opponent)))
      {
        send_to_char("The challenger does not appear to be in the game.\n\r", ch);
        ch->battleship_player = 0;
        return;
      }
      send_to_char("The challenge has been declined.\n\r", victim);
      send_to_char("The challenge has been declined.\n\r", ch);

      victim->battleship_player = 0;
      ch->battleship_player = 0;
      
      if(ch->battleship_opponent)
        free(ch->battleship_opponent);
      if(victim->battleship_opponent)
        free(victim->battleship_opponent);
  
      return;
    }
    send_to_char("Please answer the challenge with either 'play accept' or 'play decline'.\n\r", ch);
    return;
  }

  if(ch->battleship_player != 1 && ch->battleship_player != 2)
  {
    send_to_char("You shouldn't be seeing this message.  Go tell Kid.\n\r", ch);
    logfile("Battleship broke.");
    logmud("Battleship broke.", 10000, 32767);
    return;
  }

  if(ch->battleship_player != table->turn)
  {
    send_to_char("It is not your turn yet, please wait patiently.\n\rYou may see the board at any time by typing 'board'.\n\r", ch);
    return;
  }

  one_argument(argument, buf);

  if(!strlen(buf))
  {
    send_to_char("Usage:  play [location]  - [location] is in the form of (row)(column) - eg, to fire a torpedo at square c-13, type:  play c13\n\r", ch);
    return;
  }
  row = buf[0];
  col = atoi(&buf[1]);

  if(row < 'a' || row > 'e')
  {
    send_to_char("Bad row, please choose 'a' - 'e'.\n\r", ch);
    send_to_char("Usage:  play [location]  - [location] is in the form of (row)(column) - eg, to fire a torpedo at square c-13, type:  play c13\n\r", ch);
    return;
  }

  if(col < 1 || col > 26)
  {
    send_to_char("Bad column, please choose '1' - '26'.\n\r", ch);
    send_to_char("Usage:  play [location]  - [location] is in the form of (row)(column) - eg, to fire a torpedo at square c-13, type:  play c13\n\r", ch);
    return;
  }
    

  if(table->turn == 1)
    table->turn = 2;
  else
    table->turn = 1;

  bomb(ch, buf);
}

int init_game(CHAR_DATA *ch, CHAR_DATA *victim)
{
  if(table)
  {
    send_to_char("Unfortunately the only Battleship board available here is currently in use.  Please wait patiently and try again later.\n\r", ch);
    send_to_char("This is only temporarily until we have the funding to purchase more boards for the community.\n\r", ch);
    send_to_char("Unfortunately the only Battleship board available here is currently in use.  Please wait patiently and try again later.\n\r", victim);
    send_to_char("This is only temporarily until we have the funding to purchase more boards for the community.\n\r", victim);

    ch->battleship_player = 0;
    victim->battleship_player = 0;
    free(ch->battleship_opponent);
    free(victim->battleship_opponent);
    return;
  }

  CREATE(table, struct battleship_board, 1);

  bzero((char *)table, sizeof(struct battleship_board));
  table->turn = 2;
  
  genBattle();  

  send_to_char("\n\rYou may view the board at any time by typing 'board'.\n\rTo make your move, use the 'play' command.\n\rYou may forfeit the game at any time by typing 'concede'.\n\r\n\r", ch);
  send_to_char("\n\rYou may view the board at any time by typing 'board'.\n\rTo make your move, use the 'play' command.\n\rYou may forfeit the game at any time by typing 'concede'.\n\r\n\r", victim);

  showBattle(ch);
  showBattle(victim);  

  return 0;
}

void cleanup_game(void)
{
  if(table)
    free(table);
  table = 0;
}

COMMAND(do_board)
{
  char buf[1024];
  int player;

  if(!table)
  {
    send_to_char("There does not appear to be a game going on right now.  Try the 'challenge' command.\n\r", ch);
    return;
  }

  if(ch->battleship_player == 1 || ch->battleship_player == 2)
    showBattle(ch);
  else
  {
    one_argument(argument, buf);
    player = atoi(buf);

    if(!player)
    {
      send_to_char("You are not in a game, but you may view the on-going game.  Choose between player one or player two's board.  Usage:  board <1 or 2>\n\r", ch);
      return;
    }
    if(player <1 || player >2)
    {
      send_to_char("Invalid board.  Try again, choose player 1 or player 2.\n\r", ch);
      return;
    } 

    ch->battleship_player = player; 
    showBattle(ch);
    ch->battleship_player = 0;
  }
}