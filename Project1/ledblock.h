#ifndef LEDBLOCK_H
#define LEDBLOCK_H
#include <stdint.h>
#include "3D.h"
#include <memory.h>
#include <stdlib.h>
class ledemu
{
public:
    ledemu(void)
    {

    }
    ledemu(uint8_t xi,uint8_t yi,uint8_t zi)
    {
        x=xi;
        y=yi;
        z=zi;
        buff=(uint8_t*)malloc(x*y*z*sizeof(uint8_t));
        buffbk=(uint8_t*)malloc(x*y*z*sizeof(uint8_t));
        clearled();
        memset(buff,0,x*y*z*sizeof(uint8_t));
        flashled();
    }
    void init(uint8_t xi,uint8_t yi,uint8_t zi)
    {
        x=xi;
        y=yi;
        z=zi;
		zero = setpointR(0, 0, 0);
        buff=(uint8_t*)malloc(x*y*z*sizeof(uint8_t));
        buffbk=(uint8_t*)malloc(x*y*z*sizeof(uint8_t));
        clearled();
        memset(buff,0,x*y*z*sizeof(uint8_t));
        flashled();
    }
    uint8_t * getbuffbk()
    {
        return buff;
    }
    void clearled(void)
    {
        memset(buffbk,0,x*y*z*sizeof(uint8_t));
    }
    void flashled(void)
    {
        memcpy(buff,buffbk,x*y*z*sizeof(uint8_t));
    }
    void displayleds(void)
    {
        drawline3D(setpoint(31,70,31,0xffffff),setpoint(31,-81,31,0xffffff),0xffffff);
        drawline3D(setpoint(-41,70,31,0xffffff),setpoint(-41,-81,31,0xffffff),0xffffff);
        drawline3D(setpoint(31,70,-41,0xffffff),setpoint(31,-81,-41,0xffffff),0xffffff);
        drawline3D(setpoint(-41,70,-41,0xffffff),setpoint(-41,-81,-41,0xffffff),0xffffff);
        drawline3D(setpoint(-41,-81,-41,0xffffff),setpoint(-41,-81,31,0xffffff),0xffffff);
        drawline3D(setpoint(-41,-81,-41,0xffffff),setpoint(31,-81,-41,0xffffff),0xffffff);
        drawline3D(setpoint(31,-81,-41,0xffffff),setpoint(31,-81,31,0xffffff),0xffffff);
        drawline3D(setpoint(31,-81,31,0xffffff),setpoint(-41,-81,31,0xffffff),0xffffff);
        drawline3D(setpoint(-41,71,-41,0xffffff),setpoint(-41,71,31,0xffffff),0xffffff);
        drawline3D(setpoint(-41,71,-41,0xffffff),setpoint(31,71,-41,0xffffff),0xffffff);
        drawline3D(setpoint(31,71,-41,0xffffff),setpoint(31,71,31,0xffffff),0xffffff);
        drawline3D(setpoint(31,71,31,0xffffff),setpoint(-41,71,31,0xffffff),0xffffff);
        for (int x=0; x<8; x++)
            for(int y=0; y<8; y++)
                for(int z=0; z<16; z++)
                    //if(getled(x,y,z,0))
                        Drawbox2((x-this->x/2)*10,(z-this->z/2)*10, (y-this->y/2)*10, 1, zero, zero,getled(x,y,z) );
    }
    uint32_t getled(uint8_t x,uint8_t y,uint8_t z,bool i=1)
    {
        uint32_t color=*(buffbk+z*64+y*8+x);
        if(i)
        color =(color|(0x0f<<16&0xE00000))|(color<<11&0xE000)|(color<<6&0xC0)|(0x1f1f1f);


        return color;
    }
    void setled(uint8_t x,uint8_t y,uint8_t z,uint8_t color)
    {
        *(buffbk+z*64+y*8+x)=color;
    }
    void ledfree()
    {
        free(buff);
        free(buffbk);

    }
private:
    uint8_t * buff;
    uint8_t * buffbk;
    uint8_t x,y,z;
    pointR3D zero;

};

#endif // LEDBLOCK_H
