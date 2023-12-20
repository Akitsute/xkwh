#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <iostream>
#include <string>
#include <typeinfo>

LRESULT CALLBACK WindowProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);

wchar_t* convertString(const std::string& string){
   int length = MultiByteToWideChar(CP_UTF8,0,string.c_str(),-1,NULL,0);

   wchar_t* wideString = new wchar_t[length];
   MultiByteToWideChar(CP_UTF8,0,string.c_str(),-1,wideString,length);

   return wideString;
}

class XKWindow{
public:
   std::string title;
   int insertX;
   int insertY;
   int scaleX;
   int scaleY;

   int isOpen;

   XKWindow(std::string title,int newInsertX,int newInsertY,int newScaleX,int newScaleY){
      this->title = title;

      insertX = newInsertX;
      insertY = newInsertY;
      scaleX = newScaleX;
      scaleY = newScaleY;

      isOpen = 1;
   }

   void open(){
      WNDCLASSW windowClass = {};
      windowClass.lpfnWndProc = WindowProc;
      windowClass.hInstance = GetModuleHandle(NULL);
      windowClass.lpszClassName = L"XKWindowWin32";

      RegisterClassW(&windowClass);

      wchar_t* convertedTitle = convertString(title);

      hwnd = CreateWindowExW(0,L"XKWindowWin32",convertedTitle,WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
         insertX,insertY,scaleX,scaleY,NULL,NULL,GetModuleHandle(NULL),NULL
      );

      delete[] convertedTitle;

      SetPropW(hwnd,L"WindowPointer",reinterpret_cast<HANDLE>(this));
      wglHDC = GetDC(hwnd);

      PIXELFORMATDESCRIPTOR pfd = {
         sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,
         32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,8,0,0,0,0,0
      };

      int pixelFormat = ChoosePixelFormat(wglHDC,&pfd);
      SetPixelFormat(wglHDC,pixelFormat,&pfd);

      cursorHandle = LoadCursor(NULL,IDC_ARROW);
      SetCursor(cursorHandle);

      wglHGLRC = wglCreateContext(wglHDC);
   }

   void makeContext(){
      wglMakeCurrent(wglHDC,wglHGLRC);
   }

   void updateBuffers(){
      SwapBuffers(wglHDC);
   }

   void updateEvents(){
      MSG msg = {};
      while(PeekMessageW(&msg,NULL,0,0,PM_REMOVE)){
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
   }

   HWND hwnd;
   HDC wglHDC;
   HGLRC wglHGLRC;

   HCURSOR cursorHandle;
};

LRESULT CALLBACK WindowProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam){
   XKWindow* windowPointer = reinterpret_cast<XKWindow*>(GetPropW(hwnd,L"WindowPointer"));

   switch(Message){
      case WM_DESTROY:
         windowPointer->isOpen = 0;

         DestroyCursor(windowPointer->cursorHandle);

         PostQuitMessage(0);
         return 0;
      default:
         return DefWindowProcW(hwnd,Message,wParam,lParam);
   }
}