

#ifndef CLEARSCREEN_H
#define CLEARSCREEN_H


#include <windows.h>
#include <versionhelpers.h>
#include <SFML/Graphics.hpp>


namespace ClearScreen
{
	HDC hdcMem = NULL;
	HBITMAP hbmp = NULL;
	void* pvBits = NULL;
	int FIXED_WIDTH = 960;
	int FIXED_HEIGHT = 540;
	int SCALE_WIDTH = 1920;
	int SCALE_HEIGHT = 1080;
	sf::RenderTexture renderTexture;
	bool modern = true;
	
	void Init(int width,int height,sf::RenderWindow &window,int scaledX,int scaledY) 
	{
		//Set Sizes
		FIXED_WIDTH = width;
		FIXED_HEIGHT = height;
		SCALE_WIDTH = scaledX;
		SCALE_HEIGHT = scaledY;
		
		
		
		//Get Window Handle
		sf::WindowHandle handle = window.getSystemHandle();
		
		//Set as WS_EX_LAYERED
		SetWindowLongPtrA(handle, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW);
	
		
		if(IsWindows8OrGreater())
			modern = true;
		else
			modern = false;
		
		
		if(modern)
		{
			//Default to use this only since this is all that is necessary on windows 8 and up.
			SetLayeredWindowAttributes(handle, RGB(255, 0, 255), 0,LWA_COLORKEY);
			return;
		}
		//else	
		
	    // Setup Environment for the less efficient but effective method that is supported by windows 2000 and up.
	    hdcMem = CreateCompatibleDC(NULL);
	    BITMAPINFO bmi = { {sizeof(BITMAPINFOHEADER), FIXED_WIDTH, -FIXED_HEIGHT, 1, 32, BI_RGB} };
	    hbmp = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0);
	    SelectObject(hdcMem, hbmp);
	    renderTexture.create(FIXED_WIDTH,FIXED_HEIGHT);
	    
	}
	
	
	void update(HWND hwnd) 
	{
	    
	    if(modern)
	    	return;
	    	
	    sf::Image img = renderTexture.getTexture().copyToImage();
	    
	    int width = img.getSize().x;
	    int height = img.getSize().y;
	    
	    
	    const sf::Uint8* src = img.getPixelsPtr();
	    DWORD* dest = (DWORD*)pvBits;
	    
	    // Process pixels
	    for (int i = 0; i < FIXED_WIDTH * FIXED_HEIGHT; i++) {
	        const sf::Uint8* p = src + i*4;
	        dest[i] = (p[0] == 255 && p[1] == 0 && p[2] == 255)
	            ? 0x00000000 
	            : (0xFF000000 | (p[0]<<16) | (p[1]<<8) | p[2]);
	    }
	    
	    // Update window 
	    SIZE size = {LONG(SCALE_WIDTH), LONG(SCALE_HEIGHT)};
	    POINT ptSrc = {0, 0};
	    BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
	    UpdateLayeredWindow(hwnd, NULL, NULL, &size, hdcMem, &ptSrc, RGB(255,0,255), &blend, ULW_ALPHA|ULW_COLORKEY);
	}
	

	
	void Cleanup()
	{
		
	    DeleteObject(hbmp);
	    DeleteDC(hdcMem);
	    
	}
	
	
	
}


#endif