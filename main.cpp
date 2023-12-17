#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "xkwindow.hpp"

int main(){
   XKWindow windowHandle("Jan",100,100,750,450);
   windowHandle.open();

   while(windowHandle.isOpen){
      std::cout << "FFGG" << std::endl;
   }

   return 0;
}