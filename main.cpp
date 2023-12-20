#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "xkwindow.hpp"

int main(){
   XKWindow windowHandle("Jan",100,100,750,450);

   windowHandle.open();
   windowHandle.makeContext();

   while(windowHandle.isOpen){
      glClearColor(0.0f,0.0f,0.0f,1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glColor3f(1.0f,0.0f,0.5f);

      glBegin(GL_QUADS);
        glVertex2f(-0.5f,-0.5f);
        glVertex2f(0.5f,-0.5f);
        glVertex2f(0.5f,0.5f);
        glVertex2f(-0.5f,0.5f);
      glEnd();

      windowHandle.updateBuffers();
      windowHandle.updateEvents();
   }

   return 0;
}