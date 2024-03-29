/*

============ Source code ============
Link        : https://raw.githubusercontent.com/ramadhinolfski/cpackets/master/conio.h
GitHub      : https://github.com/zoelabbb/conio.h.git
=====================================

*/

/**
* conio4linux (Conio.h for linux)
* Copyright (C) 2013 by Carlos J. Pinto B.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
* @author Carlos J. Pinto B. <pintocar83@gmail.com>
* @date 2013-11-05
* @version 0.3
*/

/*
List funtions
=============
    cprintf
    cscanf
    gotoxy          
    clrscr          
    textcolor       
    textbackground  
    wherex         
    wherey        
    getch          
    getche   
    ungetch
    kbhit          
    putch           
    putchar        
    cputs         
    clreol         
    insline (not implemented)       
    delline (not implemented)       
    cgets   (not implemented)       
    getpass (not implemented)        
    gettext (not implemented)
    _cprintf        
    _cscanf         
    _cputs          
    _getche         
    _kbhit          
    _putch          
    _ungetch
    
Instalation for linux
=====================
    Copy file conio.h to /usr/include/
    Run as root user:
      cp conio.h /usr/include/

Example program
===============
//File name: main.cpp
//Compilation: gcc main.cpp -o program_conio -lstdc++
//Test program: ./program_conio
#include<conio.h>
int main(int argc, char *argv[]){
  textbackground(BLUE);
  clrscr();  
  textcolor(WHITE);
  gotoxy(30,5);
  cprintf("Hello World WHITE");
  textcolor(YELLOW);
  gotoxy(30,6);
  cprintf("Hello World YELLOW");    
  for(int i=0;i<16;i++){
    textcolor(i);
    gotoxy(1,2+i);
    cprintf("Hello World"); 
    }  
  getch();
  return 0;
  }

I need help for
===============
  *Document funtions.
  *Implement funtions not implemented.
  *Add funtions new.
  *Report bugs.
  
  For any case: 
  Send a mail to pintocar83@gmail.com with the modifications and information: Email, Autor and changes.
  Thanks!!!

Contributions
=============




*/


#ifndef __CONIO4LINUX_H
#define __CONIO4LINUX_H

#include <stdio.h>//necesaria
#include <unistd.h>//necesario
#include <fcntl.h>
#include <termios.h>//necesaria


#define BLACK_COLOR        0
#define BLUE_COLOR         1
#define GREEN_COLOR        2
#define CYAN_COLOR         3
#define RED_COLOR          4
#define MAGENTA_COLOR      5
#define BROWN_COLOR        6
#define LIGHTGRAY_COLOR    7
#define DARKGRAY_COLOR     8
#define LIGHTBLUE_COLOR    9
#define LIGHTGREEN_COLOR   10
#define LIGHTCYAN_COLOR    11
#define LIGHTRED_COLOR     12
#define LIGHTMAGENTA_COLOR 13
#define YELLOW_COLOR       14
#define WHITE_COLOR        15
#define BLINK_COLOR        128


class __CONIO_H{
  private:
    int bgc;
  public:
    __CONIO_H(){
      bgc=40;
      }
      
    ~__CONIO_H(){
      printf("\033[m");
      }
      
    void clreol(){
      printf("\033[K");
      }
      
    void insline(){
      printf( "\x1b[1L");
      }
  
    void delline(){
      printf( "\033[1M");
      }

    void gotoxy(int x,int y){
      printf("\033[%d;%df",y,x);
      }
      
    void clrscr(){
      printf( "\033[%dm\033[2J\033[1;1f",bgc);
      }
      
    void textbackground(int color){
      switch(color%16){
	  case BLACK_COLOR:          bgc=40;break;
	  case BLUE_COLOR:           bgc=44;break;
	  case GREEN_COLOR:          bgc=42;break;
	  case CYAN_COLOR:           bgc=46;break;
	  case RED_COLOR:            bgc=41;break;
	  case MAGENTA_COLOR:        bgc=45;break;
	  case BROWN_COLOR:          bgc=43;break;
	  case LIGHTGRAY_COLOR:      bgc=47;break;
	  case DARKGRAY_COLOR:       bgc=40;break;
	  case LIGHTBLUE_COLOR:      bgc=44;break;
	  case LIGHTGREEN_COLOR:     bgc=42;break;
	  case LIGHTCYAN_COLOR:      bgc=46;break;
	  case LIGHTRED_COLOR:       bgc=41;break;
	  case LIGHTMAGENTA_COLOR:   bgc=45;break;
	  case YELLOW_COLOR:         bgc=43;break;
	  case WHITE_COLOR:          bgc=47;break;
	}
      }

    void textcolor(short color){  
      switch(color%16){
	  case BLACK_COLOR:          printf("\033[0;%d;%dm",30,bgc);break;
	  case BLUE_COLOR:           printf("\033[0;%d;%dm",34,bgc);break;
	  case GREEN_COLOR:          printf("\033[0;%d;%dm",32,bgc);break;
	  case CYAN_COLOR:           printf("\033[0;%d;%dm",36,bgc);break;
	  case RED_COLOR:            printf("\033[0;%d;%dm",31,bgc);break;
	  case MAGENTA_COLOR:        printf("\033[0;%d;%dm",35,bgc);break;
	  case BROWN_COLOR:          printf("\033[0;%d;%dm",33,bgc);break;
	  case LIGHTGRAY_COLOR:      printf("\033[0;%d;%dm",37,bgc);break;
	  case DARKGRAY_COLOR:       printf("\033[1;%d;%dm",30,bgc);break;
	  case LIGHTBLUE_COLOR:      printf("\033[1;%d;%dm",34,bgc);break;
	  case LIGHTGREEN_COLOR:     printf("\033[1;%d;%dm",32,bgc);break;
	  case LIGHTCYAN_COLOR:      printf("\033[1;%d;%dm",36,bgc);break;
	  case LIGHTRED_COLOR:       printf("\033[1;%d;%dm",31,bgc);break;
	  case LIGHTMAGENTA_COLOR:   printf("\033[1;%d;%dm",35,bgc);break;
	  case YELLOW_COLOR:         printf("\033[1;%d;%dm",33,bgc);break;
	  case WHITE_COLOR:          printf("\033[1;%d;%dm",37,bgc);break;
	}
      }
    
    int ungetch(int ch){
      return ungetc(ch, stdin);
      }
    
    int getch_echo(bool echo=true){
      struct termios oldt, newt;
      int ch;
      tcgetattr( STDIN_FILENO, &oldt );
      newt = oldt;
      newt.c_lflag &= ~ICANON;
      if(echo)
	      newt.c_lflag &=  ECHO;
      else
	      newt.c_lflag &= ~ECHO;
      tcsetattr( STDIN_FILENO, TCSANOW, &newt );
      ch = getchar();
      tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
      return ch;
      }
      
    int getch(){
      return getch_echo(false);
      }
      
    int getche(){
      return getch_echo(true);
      }
      
    int wherexy(int&x,int&y){
      printf("\033[6n");
      if(getch() != '\x1B') return 0;
      if(getch() != '\x5B') return 0;
      int in;
      int ly = 0;
      while((in = getch()) != ';')
      ly = ly * 10 + in - '0';	
      int lx = 0;
      while((in = getch()) != 'R')
      lx = lx * 10 + in - '0';
      x = lx;
      y = ly;

      return 0;
      }

    int wherex(){
      int x=0,y=0;
      wherexy(x,y);
      return x;
      }
      
    int wherey(){
      int x=0,y=0;
      wherexy(x,y);
      return y;
      } 

    int kbhit(){
      struct termios oldt, newt;
      int ch;
      int oldf;    
      tcgetattr(STDIN_FILENO, &oldt);
      newt = oldt;
      newt.c_lflag &= ~(ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
      fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);    
      ch = getchar();    
      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      fcntl(STDIN_FILENO, F_SETFL, oldf);    
      if(ch != EOF){
        ungetc(ch, stdin);
        return 1;
        }    
      return 0;
      }
    
    int putch(const char c){
      printf("%c",c);
      return (int)c;
      }
      
    int cputs(const char*str){
      printf(str);
      return 0;
      }     
  };

//! \brief conio singleton.
class __CONIO_H_INST{
public:
  __CONIO_H_INST()                                     = delete;
  __CONIO_H_INST( const __CONIO_H_INST& )              = delete;
  __CONIO_H_INST& operator = ( const __CONIO_H_INST& ) = delete;

  static __CONIO_H* getInstance(){
    if ( conio_ == nullptr )
      conio_ = new __CONIO_H;

    return conio_;
  }

  static void deleteInstance(){
    delete conio_;
    conio_ = nullptr;
  }

private:
  static __CONIO_H* conio_;
};


#define cprintf printf
#define cscanf scanf
#define cgets gets
  

  
#define gotoxy          __CONIO_H_INST::getInstance()->gotoxy
#define clrscr          __CONIO_H_INST::getInstance()->clrscr
#define textcolor       __CONIO_H_INST::getInstance()->textcolor
#define textbackground  __CONIO_H_INST::getInstance()->textbackground
#define wherex          __CONIO_H_INST::getInstance()->wherex
#define wherey          __CONIO_H_INST::getInstance()->wherey
#define ungetch         __CONIO_H_INST::getInstance()->ungetch  
#define getch           __CONIO_H_INST::getInstance()->getch

#define getche          __CONIO_H_INST::getInstance()->getche
#define kbhit           __CONIO_H_INST::getInstance()->kbhit
#define putch           __CONIO_H_INST::getInstance()->putch
#define putchar         __CONIO_H_INST::getInstance()->putch
#define cputs           __CONIO_H_INST::getInstance()->cputs
#define clreol          __CONIO_H_INST::getInstance()->clreol
#define insline         __CONIO_H_INST::getInstance()->insline
#define delline         __CONIO_H_INST::getInstance()->delline
//#define getpass         ___CONIO_H.getpass
// #define gettext         ___CONIO_H.gettext


//DEV C++ only have the next funtions (version: 4.9.9.2)
#define _cprintf        cprintf
#define _cscanf         cscanf
#define _cputs          cputs
#define _getche         getche
#define _kbhit          kbhit
#define _putch          putch
#define _ungetch        ungetch
#define _getch          getch

#endif

