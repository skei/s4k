#ifndef s4k_main_included
#define s4k_main_included
//----------------------------------------------------------------------

#include "s4k.h"

//----------

#pragma code_seg( ".s4k_main")
#pragma data_seg( ".s4k_main.data")
#pragma bss_seg(  ".s4k_main.bss")
#pragma const_seg(".s4k_main.const")

//----------

//#define MAIN_INSERT_SLEEP

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

//static DEVMODE dmScreenSettings;

static PIXELFORMATDESCRIPTOR pfd;
static PVOID hDC;

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

  ///SUBSYSTEM:WINDOWS
  //void WINAPI WinMainCRTStartup(void)

#ifdef _DEBUG

  NOINLINE
  int main(void)

#else

  NOINLINE
  void mainCRTStartup(void)

#endif

{
  pfd.cColorBits = pfd.cDepthBits = 32;
  pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

#ifdef S4K_FULLSCREEN

  hDC = GetDC(
    CreateWindow(
      "edit", 0,
      WS_MAXIMIZE |
      WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
      0, 0,  // 0,0,
      0, 0, // 0,0,
      0,0,0,0
    )
  );

#else

  hDC = GetDC(
    CreateWindow(
      "edit", 0,
      //WS_MAXIMIZE |
      WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
      16,  16,  // 0,0,
      640, 480, // 0,0,
      0,0,0,0
    )
  );

#endif

  SetPixelFormat(hDC,ChoosePixelFormat(hDC,&pfd),&pfd);
  wglMakeCurrent(hDC,wglCreateContext(hDC));
  ShowCursor(FALSE);
  intro_prepare();

  //---------- main loop ----------

  /*
    Sleep
      17 - almost no cpu
      16 - 1-2%
      15 - one core almost 100%
    my monitor reffresh rate (60hz) = 16.666 ms..
  */

  do
  {
    intro_frame();
    SwapBuffers(hDC);

    #ifdef MAIN_INSERT_SLEEP
    Sleep(17);
    #endif

  } while (!GetAsyncKeyState(VK_ESCAPE));

  //----------

  ExitProcess(0);
}

//----------------------------------------------------------------------
#endif

/*
  screen_w = GetSystemMetrics( SM_CXSCREEN );
  screen_h = GetSystemMetrics( SM_CYSCREEN );
*/

/*
  dmScreenSettings.dmSize = sizeof(dmScreenSettings);
  dmScreenSettings.dmPelsWidth = 800;
  dmScreenSettings.dmPelsHeight = 600;
  dmScreenSettings.dmBitsPerPel = 32;
  dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
  ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN);
*/


/*
// Sets vsync on off
void SwitchVsync(bool sync)
{
  BOOL (APIENTRY *wglSwapIntervalEXT)(int);
  wglSwapIntervalEXT=( BOOL (APIENTRY*)(int) )wglGetProcAddress("wglSwapIntervalEXT");
  if (sync=true)
  {
    wglSwapIntervalEXT(1);
  }
  else
  {
    wglSwapIntervalEXT(0);
  }
}*/
