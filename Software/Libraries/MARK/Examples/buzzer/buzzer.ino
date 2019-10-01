#include <MARK.h>

MARK myrobot;
// Avaible notes : c,d,e,f,g,a,b,C => do re mi fa sol la si do^1
char notes[] = "cegCgec ";
int beats[] = {1,1,1,1,1,1,1,1};

void setup()
{
  myrobot.begin();
}

void loop()
{
    for(int i = 0; i <8; i++) {
        myrobot.playNote(notes[i],beats[i]);
    }

}
