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

//display.cpp - Sourec file of implementation of TUI buffer/drawing element of library

#include "display.hpp"
//Header

Display::Display(int _width, int _height, bool memory_optimized = false, int _refresh = 0)
{
    if(memory_optimized) //Hardcore RAM saving mode ON - will accquire more processing
    //power and will decrease TUI customazibility/quality 
    {
        width = height = 24;
        //Setting buffer size to 24x24(just for testing these values might change,
        //but will be constant across library for RAM saving purposes) - evereything will
        //be scaled to fit this parameters if memory optimization is ON 
    }
    
    if(_refresh > 0) //Refreshing of display buffer
    {
        refresh = _refresh;
        //Setting refresh rate
    }
    else
    {
        refresh = 0;
        //Setting sleep time calculated by refresh rate
    }

    width = _width;
    height = _height;
    //Setting public width and height of display buffer

    buffer = new char*[width];
    for(int i = 0; i < width; i++)
    {
        buffer[i] = new char[height];
    }
    //Inicializing display buffer

    int* wrapped = DisplayHandler_Wrapper(this); 
    //Wrapping DisplayHandler

    pthread_create(&handler, NULL, wrapped, NULL);
    pthread_detach(handler);
    //Creating thread for handling display
}
//Constructor

Display::~Display()
{
    for(int i = 0; i < width; i++)
    {
        delete[] buffer[i];
    }
    //Deleting buffer
}
//Destructor

void Refresh()
{
    Output();
}
//Refreshes display

int DisplayHandler(void*)
{
    int retval = 0;
    //Return value of this thread - will handle errors and signals

    if(refresh >0)
    {
        int sleepperiod = (1/refresh)*1000000;
        //Calculating period of sleep
    }
    else
    {
        int sleepperiod = (1/refresh+1)*1000000;
        //Calculating period of sleep
    }
    //Calculating refresh rate based on mode

    Output();
    //Output handling
    
    while(true)
    {
        try
        {
            if(refresh > 0)
            {
                Refresh();
                usleep(sleepperiod-(sleepperiod/10000);
                //Right amount of sleep for refresh
            }

            if(display_request > 0) //Checking if refresh demanded
            {
                Refresh();
            }
            //Refreshing on demand

            usleep(sleepperiod/10000);
            //Static sleep even if not refreshing to not push CPU too much
        }
        catch(int error)
        {
            retval = error;
            break;
            //Exiting loop
        }
        catch(...)
        {
            retval = 13816; //Unknown error ;)
            break;
            //Exiting loop
        }
        //Error handling
    }
    //Main, infinite loop

    pthread_exit(retval);
}
//Handles display buffer

void Output()
{
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < height; x++)
        {
            cout << buffer[x][y];
            //Output single char
        }
        //Output single line of image

        cout << '\n';
        //Start new line
    }
    //Buffer outputting loops
}
//Low-level buffer displayment

int* DisplayHandler_Wrapper(*Display handler)
{
    return &(handler->DisplayHandler(NULL));
    //Wrap
}
//Wrapper for DisplayHandler - returns it adress in memory for pthread call