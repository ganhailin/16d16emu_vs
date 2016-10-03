#include <time.h>
#include <math.h>
#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "3D.h"
#include "draw.h"
#include "touch.h"
#include "tetris3d.h"
int fps=0,fpss;
bool done = false;
bool drawdone = false;
pointR3D zero= setpointR(0,0,0);
extern char sharebuff[100];
tetris3d tet;


DWORD WINAPI pth1(LPVOID x)
{

    tet.init();

    char str[30];
    while(!done)
    {
        if(done)
            break;
        clrscreen();
        clrdeepbuff();
        sprintf_s(str,"FPS:%d",fpss);
        sprintf_s(sharebuff,"Number of Finger(s):%d",getfingernum());
        drawstring(0,0,(unsigned char*)str,0xffffff);
        drawstring(0,10,(unsigned char*)sharebuff,0xffffff);
        tet.gamedraw();
        updatescreen();
        fps++;
    }
    drawdone=true;
    return NULL;
}

DWORD WINAPI pth2(LPVOID x)
{
    while(1)
    {

        fps=0;
        for(int i=0; i<10; i++)
			Sleep(100);
        fpss=fps;
    }
    return NULL;
}

DWORD WINAPI pth3(LPVOID x)
{
    while(1)
    {

		Sleep(10);
        uint32_t *key=getkey();
        if(*key&0x01)
            movecam(0,0,1);
        if(*key&0x02)
            movecam(0,0,-1);
        if(*key&0x04)
            movecam(1,0,0);
        if(*key&0x08)
            movecam(-1,0,0);
        if(*key&0x10)
            movecam(0,-1,0);
        if(*key&0x20)
            movecam(0,1,0);
        if(*key&0x0100)
        {
            *key&=~0x0100;
            tet.input(1,0);
        }

        if(*key&0x0200)
        {
            *key&=~0x0200;
            tet.input(2,0);

        }
        if(*key&0x0400)
        {
            *key&=~0x0400;
            tet.input(4,0);

        }
        if(*key&0x0800)
        {
            *key&=~0x0800;
            tet.input(3,0);

        }
        if(*key&0x1000)
        {
            *key&=~0x1000;
            tet.newgame();

        }
        if(*key&0x2000)
        {
            *key&=~0x2000;
            tet.input(0,1);

        }
        if(*key&0x4000)
        {
            *key&=~0x4000;
            tet.input(0,2);

        }
        if(*key&0x8000)
        {
            *key&=~0x8000;
           tet.input(0,3);

        }
        if(*key&0x10000)
        {
            *key&=~0x10000;
            tet.input(0,4);

        }
        if(*key&0x20000)
        {
            *key&=~0x20000;
            tet.input(0,5);

        }
        if(*key&0x40000)
        {
            *key&=~0x40000;
            tet.input(0,6);
        }
    }

    return NULL;
}

DWORD WINAPI pth4(LPVOID x)
{
    while(!done)
    {
		while (!tet.ingame())Sleep(1);
        if(done)
            break;
        for(int i=0; i<40; i++)
			Sleep(100);
        tet.gameloop();
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    HANDLE  thread1,thread2,thread3,thread4;
    setdisplay(1280,720);
    initSDL();
    setcam(setpoint(0,0,-150,0),setpointR(0,0,0));
    seteye(setpoint(0,0,-500,0));
	thread1 = CreateThread(NULL, 0, pth1, NULL, 0, NULL);
	thread2 = CreateThread(NULL, 0, pth2, NULL, 0, NULL);
	thread3 = CreateThread(NULL, 0, pth3, NULL, 0, NULL);
	thread4 = CreateThread(NULL, 0, pth4, NULL, 0, NULL);
    SDLloop(&drawdone,&done);
    exit(0);
}

