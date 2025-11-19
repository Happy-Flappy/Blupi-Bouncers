

#ifndef CLEARSCREEN_H
#define CLEARSCREEN_H


#include <windows.h>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <thread>

namespace ClearScreen
{
	HDC hdcMem = NULL;
	HBITMAP hbmp = NULL;
	void* pvBits = NULL;
	int WIDTH,HEIGHT;
	sf::RenderTexture renderTexture;
	bool modern = false;
	
	void Init(bool isModern,sf::RenderWindow &window) 
	{
		
		WIDTH = window.getSize().x;
		HEIGHT = window.getSize().y;
		
		modern = isModern;
		
		
		//Get Window Handle
		sf::WindowHandle handle = window.getSystemHandle();
		
		//Set as WS_EX_LAYERED
		SetWindowLongPtrA(handle, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT);
		
		if(modern)
		{
			//Default to use this only since this is all that is necessary on windows 8 and up.
			SetLayeredWindowAttributes(handle, RGB(255, 0, 255), 0,LWA_COLORKEY);
			return;
		}
		//else	
				

	    renderTexture.create(WIDTH,HEIGHT);

        // Create DIB section with exact 32-bit ARGB format
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = WIDTH;
        bmi.bmiHeader.biHeight = -HEIGHT;  // Top-down
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        
        hdcMem = CreateCompatibleDC(NULL);
        hbmp = CreateDIBSection(hdcMem, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0);
        SelectObject(hdcMem, hbmp);
        
        // Initialize bitmap with full transparency
        std::memset(pvBits, 0, WIDTH * HEIGHT * 4);
	    
	}
	
	
	void update(HWND hwnd) 
	{
	    
	    if(modern)
	    	return;


	    // Get image from render texture
	    sf::Image img = renderTexture.getTexture().copyToImage();
	    const sf::Uint8* src = img.getPixelsPtr();


		//COLOR CONVERSION IGNORED TO PROVIDE MASSIVE PERFORMANCE IMPROVEMENT
		//COLOR CONVERSION OF TEXTURES HANDLED ONCE AT STARTUP.
		// Copy pixel data directly to DIB section
        std::memcpy(pvBits, src, WIDTH * HEIGHT * 4);
	        



        
        // Update window position and size
        RECT rect;
        GetWindowRect(hwnd, &rect);
        POINT ptDst = {rect.left, rect.top};
        SIZE size = {WIDTH, HEIGHT};
        POINT ptSrc = {0, 0};
        
        // Set up blend function for per-pixel alpha
        BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
        
        // Update the layered window
        UpdateLayeredWindow(hwnd, NULL, &ptDst, &size, hdcMem, &ptSrc, 0, &blend, ULW_ALPHA);

        
	    
	}
	

	
	void Cleanup()
	{
		
	    DeleteObject(hbmp);
	    DeleteDC(hdcMem);
	    
	}
	
	
	
}


#endif