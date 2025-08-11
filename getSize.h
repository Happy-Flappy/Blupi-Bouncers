
#ifndef GETSIZE_H
#define GETSIZE_H

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>

namespace GetSize
{
    namespace Real
    {
        sf::IntRect workarea;
        sf::IntRect taskbar;
        sf::IntRect desktop;
    }
    
    namespace Scaled
    {
        sf::IntRect workarea;
        sf::IntRect taskbar;
        sf::IntRect desktop;
    }

    namespace Percent
    {
        sf::Vector2f workarea;
        sf::Vector2f taskbar; 
    }

	namespace Bounds
	{
		sf::IntRect workarea;
	}





    float DPI = 1.0f;

    bool getWorkArea() 
    {
        RECT workArea;
        if (!SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0))
            return false;
            
        Real::workarea = {
            static_cast<int>(workArea.left),
            static_cast<int>(workArea.top),
            static_cast<int>(workArea.right - workArea.left),
            static_cast<int>(workArea.bottom - workArea.top)
        };
        return (Real::workarea.width > 0 && Real::workarea.height > 0);
    }
    
    bool getTaskbar() 
    {
        HWND taskbar = FindWindowA("Shell_TrayWnd", NULL);
        if (!taskbar) 
            return false;
            
        RECT rect;
        if (!GetWindowRect(taskbar, &rect))
            return false;
            
        Real::taskbar = {
            static_cast<int>(rect.left),
            static_cast<int>(rect.top),
            static_cast<int>(rect.right - rect.left),
            static_cast<int>(rect.bottom - rect.top)
        };
        return (Real::taskbar.width > 0 && Real::taskbar.height > 0);
    }
    
    bool Init() 
    {
        // Get SFML's scaled desktop size (physical pixels)
        const sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
        const int scaledWidth = static_cast<int>(videoMode.width);
        const int scaledHeight = static_cast<int>(videoMode.height);
        
        // Get WinAPI's unscaled desktop size (logical pixels)
        const int unscaledWidth = GetSystemMetrics(SM_CXSCREEN);
        const int unscaledHeight = GetSystemMetrics(SM_CYSCREEN);
        
        // Calculate DPI scaling factor
        if (unscaledWidth > 0 && unscaledHeight > 0) {
            DPI = static_cast<float>(scaledWidth) / unscaledWidth;
            // Handle cases where DPI might be calculated as 0 or negative
            if (DPI <= 0) DPI = 1.0f;
        }
        else {
            DPI = 1.0f;
        }
        
        // Get work area and taskbar in logical pixels
        if (!getWorkArea() || !getTaskbar())
            return false;
        
        // Store desktop metrics
        Real::desktop = {0, 0, unscaledWidth, unscaledHeight};
        Scaled::desktop = {0, 0, scaledWidth, scaledHeight};
        
        // Convert WinAPI logical sizes to physical pixels
        auto scaleRect = [](const sf::IntRect& r, float dpi) -> sf::IntRect 
        {
            return {
                static_cast<int>(r.left * dpi),
                static_cast<int>(r.top * dpi),
                static_cast<int>(r.width * dpi),
                static_cast<int>(r.height * dpi)
            };
        };
        
        Scaled::workarea = scaleRect(Real::workarea, DPI);
        Scaled::taskbar = scaleRect(Real::taskbar, DPI);
        
        // Calculate percentage values
        if (Real::desktop.width > 0 && Real::desktop.height > 0) 
        {
            Percent::workarea = {
                static_cast<float>(Real::workarea.width) / Real::desktop.width,
                static_cast<float>(Real::workarea.height) / Real::desktop.height
            };
            
            Percent::taskbar = {
                static_cast<float>(Real::taskbar.width) / Real::desktop.width,
                static_cast<float>(Real::taskbar.height) / Real::desktop.height
            };
        }
        
        // Debug output
        std::cout << "Detected DPI scaling: " << DPI << "\n";
        std::cout << "Unscaled desktop: " << unscaledWidth << "x" << unscaledHeight << "\n";
        std::cout << "Scaled desktop: " << scaledWidth << "x" << scaledHeight << "\n";
        std::cout << "Taskbar height (logical): " << Real::taskbar.height << "\n";
        std::cout << "Taskbar height (scaled): " << Scaled::taskbar.height << "\n";
        
        return true;
    }
}

#endif



//
//#ifndef GETSIZE_H
//#define GETSIZE_H
//
//#include <SFML/Graphics.hpp>
//#include <windows.h>
//
//
//namespace GetSize
//{
//	namespace Real
//	{
//		sf::IntRect workarea;
//		sf::IntRect taskbar;
//		sf::IntRect desktop;
//	}
//	
//	namespace Scaled
//	{
//		sf::IntRect workarea;
//		sf::IntRect taskbar;
//		sf::IntRect desktop;
//	}
//
//	namespace Percent
//	{
//		sf::Vector2f workarea;
//		sf::Vector2f taskbar; 
//	}
//
//	namespace Bounds
//	{
//		sf::IntRect workarea;
//	}
//
//
//	float DPI = 1;
//
//
//	bool getWorkArea() 
//	{
//	    RECT workArea;
//	    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
//	    Real::workarea = {int(workArea.left),int(workArea.top),int(workArea.right - workArea.left), int(workArea.bottom - workArea.top)};
//		if(Real::workarea.width <= 0 || Real::workarea.height <= 0)
//		{
//			return false;
//		}
//		return true;
//	}
//	
//	
//	bool getTaskbar() 
//	{
//	    HWND taskbar = FindWindow("Shell_TrayWnd", NULL);
//	    if (!taskbar) 
//			return false;
//		RECT rect;
//		if(!GetWindowRect(taskbar,&rect))
//			return false;
//			    
//	    Real::taskbar = {int(rect.left),int(rect.top),int(rect.right - rect.left), int(rect.bottom - rect.top)};
//		if(Real::taskbar.width <= 0 || Real::taskbar.height <= 0)
//		{
//			return false;
//		}
//		
//		return true;
//	}
//	
//	
//	
//	
//	bool Init() {
//	    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();  // full size
//	    int fullsize = desktop.width;
//		int realsize = GetSystemMetrics(SM_CXSCREEN);
//	
//	    DPI = fullsize / realsize;
//	    
//	    if(DPI <= 0)
//	    	return false;
//	    
//	    
//	    if(!getWorkArea() || !getTaskbar())
//	    	return false;
//	    	
//	    std::cout << "DPI:"<<DPI << "\n";
//	    
//	    sf::IntRect r = Real::workarea;
//	    Scaled::workarea = sf::IntRect(r.left,r.top,r.width * DPI,r.height * DPI);
//	    r = Real::taskbar;
//	    Scaled::taskbar = sf::IntRect(r.left,r.top,r.width * DPI,r.height * DPI);
//	    
//	    std::cout << "ScaledTaskbar:"<<Scaled::taskbar.height<<"\n";
//	    
//	    
//	    Real::desktop.width = GetSystemMetrics(SM_CXSCREEN);
//	    Real::desktop.height = GetSystemMetrics(SM_CYSCREEN);
//	    
//	    Percent::workarea = sf::Vector2f({float(Real::workarea.width/Real::desktop.width),float(Real::workarea.height/Real::desktop.height)});
//	    Percent::taskbar = sf::Vector2f({float(Real::taskbar.width/Real::desktop.width),float(Real::taskbar.height/Real::desktop.height)});
//	    
//	    
//	    
//	    return true;
//	}
//}
//
//
//
//
//#endif