//Jan Miksa 1&Zero
//Mix Line Interface Library(MixLI_Lib) v.0.1 source code

/*
  MixLI_Lib - lightweight, highly customizable C++ TUI library for POSIX systems.
  Copyright (C) 2016  Jan Miksa

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
  Contact author: oneandzero24@gmail.com
  */

//display.hpp - Header file of TUI buffer/drawing element of library

//{
#include <pthread.h>
//POSIX Multithreading

#include <unistd.h>

//}
//Libraries

class Display
{
public:
    Display(int, int, bool, int);   //Constructor
    ~Display();                     //Destructor

    void Refresh();                 //Refreshes display
    void DisplayBuff();             //Handlers display buffer request

    char** buffer;                  //Very important variable! - output buffer of display

    int width;                      // \_ Buffer size ([width][height])
    int height;                     // /
private:     
    int DisplayHandler(void*);      //Handles display buffer
    void Output();                  //Low-level buffer displayment

    int refresh;                    //Refresh rate in Hz and flag handling whether auto refreshing of display is ON or OFF CANNOT BE 1
    int display_request;            //Buffer display request flag and handling

    pthread_t handler;              //Thread running DisplayHandler
};
//Class providing interface and low-level handling of buffer(display)

int* DisplayHandler_Wrapper(*Display); //Wrapper for DisplayHandler - returns it adress in memory for pthread call