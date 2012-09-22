#include <LedCube.h>

#define SIZE 3
#define COLS (SIZE*SIZE)

byte levelPins[SIZE] = {10,11,12};
byte colPins[COLS] = {0,1,2,3,4,5,6,7,8};

LedCube cube(3, levelPins, colPins);

void setup ()
{
//    Serial.begin(9600);
}

void loop ()
{
    delay(100);
    cube.enableBuffer(false);
    
    // light one level at a time, increasing speed each time
    for(byte d=25; d>2; d-=2) {
        for(byte r=0; r<cube.getLevels(); r++) {
            cube.lightLevel(r,d);
        }
    }
    
    // single random light at a time
    cube.randomLight(random(25,100),100);
    
    // random column drop
    for(byte x=0; x<=15; x++) {
        cube.lightDrop(random(0,cube.getCols()), random(50,150));
    }
    
    // circle around cube at a random level
    for(byte x=0; x<=5; x++) {
        cube.lightPerimeter(random(0,cube.getLevels()), random(1,5), random(25,100));
    }
    
    // random columns
    cube.randomColumn(25);
    
    // turn off a single column randomly
    cube.enableBuffer();
    for(byte c=0; c<25; c++)
    {
        cube.fillBuffer();
        cube.invertBuffer();
        cube.randomColumn();
        cube.drawBuffer(10);
    }
    cube.enableBuffer(false);
    
    // cols in and out
    for(byte c=1, d=0; c<=36; c++)
    {
        if(c%2 == 0){
            for(d=0; d<20; d++) {
                cube.lightColumn(2,1);
                cube.lightColumn(4,1);
                cube.lightColumn(6,1);
                cube.lightColumn(8,1);
            }
        } else if(c%4 == 1) {
            for(d=0; d<30; d++) {
                cube.lightColumn(1,1);
                cube.lightColumn(3,1);
                cube.lightColumn(7,1);
                cube.lightColumn(9,1);
            }
        } else {
            for(d=0; d<70; d++) {
                cube.lightColumn(5,1);
            }
        }
    }
    
    // diamond and box
    byte diamond[] = {0,4, 1,1, 1,3, 1,4, 1,5, 1,7, 2,4};
    byte box[] = {0,0, 0,1, 0,2, 0,3, 0,5, 0,6, 0,7, 0,8, 1,1,  1,0, 1,2, 1,6, 1,8,  2,0, 2,1, 2,2, 2,3, 2,5, 2,6, 2,7, 2,8};
    cube.lightSequence(box, sizeof(box), 200);
    cube.lightSequence(diamond, sizeof(diamond), 400);
    
    // helicopter effect
    cube.enableBuffer();
    byte topSeq[8] = {0,3,6,7,8,5,2,1};
    byte botSeq[8] = {8,5,2,1,0,3,6,7};
    for(byte r = 0; r<7; r++){
        for(byte s= 0; s<8; s++){
            cube.clearBuffer();
            cube.lightOn(0,botSeq[s]);
            cube.lightOn(1,4);
            cube.lightOn(2,topSeq[s]);
            cube.drawBuffer(20); 
        }
    }
    
    // turn off one light at a time
    cube.fillBuffer();
    cube.drawBuffer(25);
    for(byte w=0, l, c; w<27; ){
        l = random(0,cube.getLevels());
        c = random(0,cube.getCols());
        if(cube.getBufferAt(l,c)){
            cube.lightOff(l,c);
            cube.drawBuffer(15+w*2);
            w++;
        }
    }
}

