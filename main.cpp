#include <SFML/Graphics.hpp>
#include <windows.h>
#include <winuser.h>
#include <shellapi.h>
#include <cmath>
#include <string>
#include <vector> 
#include <iostream>
#include "clearscreen.h"
#include "usersettings.h"
#include "colormode.h"


using namespace sf;

using std::string;
using std::vector;

bool war=false;




sf::Vector2f MPosition;
















class Textures
{
public:
    Texture blupi;
    Texture element;
    
    void clearcolor(string dir, Color start, Color replace, Texture &texture)
    {
        Image image;
        image.loadFromFile(dir);

        for (int x = 0; x < image.getSize().x; x++)
        {
            for (int y = 0; y < image.getSize().y; y++)
            {
                if (image.getPixel(x, y) == start)
                {
                    image.setPixel(x, y, replace);
                }
            }
        }
        texture.loadFromImage(image);
    }



	void updateImageType(sf::Texture &texture)
	{
		sf::Image image;
		image = texture.copyToImage();
		
		for(int x=0;x<image.getSize().x;x++)
		{
			for(int y=0;y<image.getSize().y;y++)
			{
				image.setPixel(x,y,	COLORMODE::GET(image.getPixel(x,y)));
			}
		}
		
		texture.update(image);
		
		
	}


	



	
	void updateImages()
	{
		updateImageType(blupi);
		updateImageType(element);
	}


    Textures()
    {
        clearcolor("blupi000.bmp", Color::Blue, Color::Transparent, blupi);
        clearcolor("element.bmp", Color::Blue, Color::Transparent, element);


    }
} textures;












float DPI = 1;



float GetDPI()
{
    HDC hdc = GetDC(NULL);
    if (!hdc) return 1.0f;
    
    // Get system DPI setting
    int d = GetDeviceCaps(hdc, LOGPIXELSX);
    ReleaseDC(NULL, hdc);
    
    // Calculate scaling factor (96 DPI = 100% scaling)
    return static_cast<float>(d) / 96.0f;
}






sf::IntRect workarea;
void getWorkArea()
{
	RECT area;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &area, 0); 
	workarea = {area.left,area.top,area.right - area.left,area.bottom - area.top};
}












class Blupi
{
public:
    float gravity = .5;
    Vector2f velocity;
    Sprite sprite;
    bool horizontal;
    enum Status
    {
        wave,
        fly,
        jeep,
        hover,
        tank,
        glueball,
        glued
    } status;

    Clock deletetime;

    Blupi()
    {
    	
    	scale = UserSettings::BlupiScale;
    	
    	sprite.setScale(scale,scale);
        sprite.setTexture(textures.blupi);
        sprite.setTextureRect(IntRect(33, 285, 35, 49));
        int type = rand() % 4;

        if (type == 0)
            status = wave;
        if (type == 1)
            status = jeep;
        if (type == 2)
            status = tank;
        if (type == 3)
            status = fly;

        int side = rand() % 2;

        if (side == 0)
            leftside = false;
        else
            leftside = true;
    }

    bool animatebool = false;
    float totaltime = 0;
    float delay = 0;
    int currentframe = 0;
    void animate(float delay, IntRect rect1, IntRect rect2, IntRect rect3 = IntRect(-1, 0, 0, 0), IntRect rect4 = IntRect(-1, 0, 0, 0), IntRect rect5 = IntRect(-1, 0, 0, 0), IntRect rect6 = IntRect(-1, 0, 0, 0), IntRect rect7 = IntRect(-1, 0, 0, 0), IntRect rect8 = IntRect(-1, 0, 0, 0))
    {
        if (animatebool)
        {
            this->delay = delay;
            totaltime += seconds(1.f/60.f).asSeconds();

            if (totaltime > delay)
            {
                if (currentframe == 0)
                {
                    sprite.setTextureRect(rect1);
                }
                if (currentframe == 1)
                {
                    sprite.setTextureRect(rect2);

                    if (rect3 == IntRect(-1, 0, 0, 0))
                    {
                        animatebool = false;
                        totaltime = 0;
                        currentframe = 0;
                        return;
                    }
                }
                if (currentframe == 2)
                {
                    sprite.setTextureRect(rect3);

                    if (rect4 == IntRect(-1, 0, 0, 0))
                    {
                        animatebool = false;
                        totaltime = 0;
                        currentframe = 0;
                        return;
                    }
                }
                if (currentframe == 3)
                {
                    sprite.setTextureRect(rect4);

                    if (rect5 == IntRect(-1, 0, 0, 0))
                    {
                        animatebool = false;
                        totaltime = 0;
                        currentframe = 0;
                        return;
                    }
                }
                if (currentframe == 4)
                {
                    sprite.setTextureRect(rect5);

                    if (rect6 == IntRect(-1, 0, 0, 0))
                    {
                        animatebool = false;
                        totaltime = 0;
                        currentframe = 0;
                        return;
                    }
                }

                if (currentframe == 5)
                {
                    sprite.setTextureRect(rect6);

                    if (rect7 == IntRect(-1, 0, 0, 0))
                    {
                        animatebool = false;
                        totaltime = 0;
                        currentframe = 0;
                        return;
                    }
                }

                if (currentframe == 6)
                {
                    sprite.setTextureRect(rect7);

                    if (rect8 == IntRect(-1, 0, 0, 0))
                    {
                        animatebool = false;
                        totaltime = 0;
                        currentframe = 0;
                        return;
                    }
                }

                if (currentframe == 7)
                {
                    sprite.setTextureRect(rect8);
                    animatebool = false;
                    totaltime = 0;
                    currentframe = 0;
                    return;
                }

                currentframe++;
                totaltime = 0;
            }
        }
        else
        {
            totaltime = 0;
            currentframe = 0;
        }
    }

    bool introduce = true;
    bool appear = true;
    bool waveway = false;
    bool released2 = true;
    bool leftside = false;
    bool shootglue = false;
    bool dropglue = false;
    Clock timer;
    int setangle;
    float angle = 0;
    int source=0;
    bool enemy = false;
    float scale = 1.3;

    void update(RenderWindow &window)
    {
    	
    	
    	
        sprite.setOrigin(Vector2f(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2));

		
		





        if (status == wave)
        {
            if (!animatebool)
            {
                if (!waveway)
                    waveway = true;
                else
                    waveway = false;
            }
            animatebool = true;

			if (!waveway)
    			animate(0.15, IntRect(541, 495, 33, 56), IntRect(219, 552, 35, 57), IntRect(288, 495, 42, 54), IntRect(435, 388, 51, 51));
			else
    			animate(0.15, IntRect(435, 388, 51, 51), IntRect(288, 495, 42, 54), IntRect(219, 552, 35, 57), IntRect(541, 495, 33, 56));

        }

        if (status == glueball)
        {
            sprite.setTexture(textures.element);
            sprite.setTextureRect(IntRect({
			210, 0},{ 16, 16}));

            if (leftside)
            {
                velocity.x = -10;
            }
            else
                velocity.x = 10;
        }




		if(status == glued)
		{
			sprite.setTexture(textures.element,false);
           
			
			
			
			if (!animatebool)
            {
                if (!waveway)
                    waveway = true;
                else
                    waveway = false;
            }
            animatebool = true;
			
			
			
			if(!waveway)
   				animate(0.15, IntRect(53,418,60,50), IntRect(308,418,60,51), IntRect(833,418,60,53), IntRect(107,471,61,54));
			else
    			animate(0.15, IntRect(107,471,61,54), IntRect(833,418,60,53), IntRect(308,418,60,51), IntRect(53,418,60,50));
			


		}



        if (status == tank)
        {
            sprite.setTextureRect(IntRect({
			567, 668},{ 57, 59}));

            if (leftside)
            {
                sprite.setScale(-scale, scale);
            }

            if (sprite.getTextureRect() != IntRect({
			0, 609},{ 56, 58}))
            {
                if (timer.getElapsedTime().asSeconds() > 2)
                {
                    shootglue = true;
                    timer.restart();
                }
            }
            else
            {
                if (timer.getElapsedTime().asSeconds() > 0.15)
                {
                    sprite.setTextureRect(IntRect({
					567, 668},{ 57, 59}));
                    timer.restart();
                }
            }
        }

        if (status == jeep)
        {
            sprite.setTextureRect(IntRect({
			384, 441}, {54, 54}));

            if (!leftside)
            {
                sprite.setScale(-scale, scale);
            }
        }

        if (status == fly)
        {
            sprite.setTextureRect(IntRect({
			408, 846}, {45, 60}));

            srand(time(NULL));

			static bool retreatingleft=false;


			if (angle < 360)
            {
            	if(!retreatingleft)
                	angle += 1;
            }
            else 
            {
                angle = 0;
            }


            float rad = angle * (3.14 / 180);
			
			
			if(sprite.getPosition().x< workarea.width/8)
			{
				
				angle-=4;
			}
			if(sprite.getPosition().x>workarea.width - workarea.width/8)
			{
				angle++;
			}
			 
			
			
            sprite.move((cos(rad) * (workarea.width/8))/40, (sin(rad) * (workarea.height/8))/40);

            velocity.x = 0;
            velocity.y = 0;

            if (angle <= 90)
            {
                leftside = false;
            }
            if (angle > 90 && angle < 180 + 90)
            {
                leftside = true;
            }
            if (angle > 180 + 90)
                leftside = false;

             if (!leftside)
                sprite.setScale(-scale, scale);
            else
                sprite.setScale(scale, scale);
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
            if(war)   
            {
            	if (timer.getElapsedTime().asSeconds() > 2)
                {
                    
                    dropglue = true;
//                    if(timer.getElapsedTime().asSeconds()<2.15)
//                    {
//                    	sprite.setTextureRect(IntRect(467,609,36,59));
//					}
//					else
//					{
					if(timer.getElapsedTime().asSeconds() > 2.01)
						timer.restart();
//                   	}
                }	
			}   
                
        }

        if (status == wave || status == jeep || status == tank || status == glued)
        {
            if (sprite.getPosition().y + ((sprite.getTextureRect().height / 2) * scale) < workarea.height)
            {
                velocity.y += gravity;
            }
            else
            {
            	velocity.y = 0;
                sprite.setPosition(sprite.getPosition().x,workarea.height-((sprite.getTextureRect().height / 2) * scale));
                if (status == wave || status == glued)
                {
                    if (timer.getElapsedTime().asSeconds() > 3)
                    {
                        velocity.y = -10;
                        timer.restart();
                    }
                    velocity.x = 0;
                }
                
                if (status == jeep || status == tank)
                {
                    if (leftside)
                        velocity.x = -2;
                    else
                        velocity.x = 2;
                }
            }
        }

		
        if (sprite.getGlobalBounds().contains(MPosition))
        {
            if (status == jeep || status == wave || status == tank || status == glued)
            {
                if (horizontal)
                    horizontal = false;
                else
                    horizontal = true;

                if (horizontal)
                    velocity.x = -2;
                else
                    velocity.x = 2;
 
                velocity.y = -10;
            }
        }






        sprite.move(velocity.x, velocity.y);
    	
		if(enemy)
    	{
    		sprite.setColor(Color(255,0,255));
		}
    }
    
    
    
    void draw(sf::RenderTarget &target)
    {
    	target.draw(sprite);
	}
};

vector<Blupi> blupi;
bool released;
































int main()
{
	
	
	
	if(MessageBox(NULL,"Do you want to use legacy transparency? \n(Legacy transparency is compatible from windows 2000 up to windows 11)\n(Modern transparency is less compatible with older windows but more efficient)","Initial Setup:",MB_YESNO  | MB_ICONQUESTION) == IDYES)
	{
		UserSettings::modern = false;
	}
	else
		UserSettings::modern = true;
	
	
	if(MessageBox(NULL,"Do you want Blupi Bouncers to cover the entire screen?\n (Click NO to force Blupi Bouncers to stay behind other windows.)","Initial Setup:",MB_YESNO  | MB_ICONQUESTION) == IDYES)
	{
		UserSettings::coverAll = true;
	}
	else
		UserSettings::coverAll = false;
	
	
	
	bool gettingBlupiScale = true;
	
	while(gettingBlupiScale)
	{
	
	
		std::string str = "Do you want the individual blupi scale to be larger than " + std::to_string(static_cast<float>(UserSettings::BlupiScale)) + "? \nClick yes to increase. \nClick no to decrease. \nClick cancel to confirm choice.";
		
		int result = MessageBox(
	        NULL, 
	        str.c_str(), 
	        "Initial Setup:", 
	        MB_YESNOCANCEL | MB_ICONQUESTION 
	    );
	
	    switch (result) {
	        case IDYES:
	        	UserSettings::BlupiScale += 0.2;
	            break;
	        case IDNO:
	            UserSettings::BlupiScale -= 0.2;
	            break;
	        case IDCANCEL:
	        	gettingBlupiScale = false;
	            break;
	    }
	    
	    if(UserSettings::BlupiScale < 0)
	    	UserSettings::BlupiScale = 0;
	    
	}
	
	
	
	
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED);
	
	
	
	
	
	
	DPI = GetDPI();
	getWorkArea();
	
	
	
	
	
	
	
	
	
	std::cout << "workarea = "<< workarea.width << "," << workarea.height << "\n";
	
	std::cout << "DPI: "<<DPI << "\n";
	
	
    View view;
    view.reset(sf::FloatRect(0,0,workarea.width,workarea.height));
    view.setViewport(sf::FloatRect(0, 0, 1, 1));
	
	
    RenderWindow mainwindow(VideoMode(workarea.width,workarea.height),"", Style::None);	
    sf::WindowHandle handle = mainwindow.getSystemHandle();
    mainwindow.setPosition(Vector2i(workarea.left, workarea.top));
	
	mainwindow.setView(view);

    
	ClearScreen::Init(UserSettings::modern,mainwindow);
	
	
	
	
    Clock dtclock;
    Time timesincelastupdate=Time::Zero;
    Time timeperframe=seconds(1.f/60.f);
	
	
	
	Clock RESETclock;
    string brush = "random";
    float keyboardtime = 0;
    bool forceEnemy=false;
    
    
	
	
    while (mainwindow.isOpen())
    {


		static sf::IntRect lastworkarea;
		getWorkArea();
		
		if(GetDPI()!=DPI || workarea != lastworkarea)
		{
			
			DPI = GetDPI();
			getWorkArea();
			
	        mainwindow.setSize(Vector2u(workarea.width, workarea.height));
	        mainwindow.setPosition(Vector2i(workarea.left, workarea.top));

	        view.setSize(workarea.width, workarea.height);
	        view.setCenter(workarea.width / 2, workarea.height / 2);
	        mainwindow.setView(view);
			
	
			lastworkarea = workarea;
			
			
			
			//Clearscreen size needs to be re-updated so that it won't be cut off.
			ClearScreen::Init(UserSettings::modern,mainwindow);
				
		}

		if(UserSettings::coverAll)
		{
			if(GetTopWindow(NULL)!=handle)
	    		SetWindowPos(handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		else
		{
			SetWindowPos(handle, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		

		

		MPosition = mainwindow.mapPixelToCoords(sf::Mouse::getPosition(mainwindow));

		
		
		
		
     	if (RESETclock.getElapsedTime().asSeconds() > 50)
        {
            brush = "random";
            war=false;
            forceEnemy=false;
            RESETclock.restart();
        }








        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (released)
            {
                Blupi newblupi;
                if (brush == "fly")
                {
                    newblupi.status = newblupi.fly;
                }
                if (brush == "jeep")
                {
                    newblupi.status = newblupi.jeep;
                }
                if (brush == "tank")
                {
                    newblupi.status = newblupi.tank;
                }
                if (brush == "wave")
                {
                    newblupi.status = newblupi.wave;
                }

				
                newblupi.sprite.setPosition(MPosition);
                int z=0;
				
				if(war&& forceEnemy)
                {
					newblupi.enemy=true;
				}
				
				
					
               	blupi.push_back(newblupi); 
            }
            released = false;
        } 
        else
            released = true;


















        
		timesincelastupdate += dtclock.restart();
        
		while(timesincelastupdate > timeperframe)
		{
			timesincelastupdate -= timeperframe;
		
			
	        Event e;
	        while (mainwindow.pollEvent(e))
	        {
	            if (e.type == Event::Closed)
	                mainwindow.close();
	        }
			
			
			
			//game logic
			
			keyboardtime += timeperframe.asSeconds();



        
	        if (sf::Keyboard::isKeyPressed(Keyboard::Add) || sf::Keyboard::isKeyPressed(Keyboard::Equal))
	        {
	            if (keyboardtime > 0.5)
	            {
	                for (int a = 0; a < 50; a++)
	                {
	                    Blupi newblupi;
	                    int x = rand() % workarea.width;
	                    int y = rand() % workarea.height;
	
	                    if (brush == "fly")
	                    {
	                        newblupi.status = newblupi.fly;
	                    }
	                    if (brush == "jeep")
	                    {
	                        newblupi.status = newblupi.jeep;
	                    }
	                    if (brush == "tank")
	                    {
	                        newblupi.status = newblupi.tank;
	                    }
	                    if (brush == "wave")
	                    {
	                        newblupi.status = newblupi.wave;
	                    }
	
	                    newblupi.sprite.setPosition(x, y);
	                    
	                    
	                    if(forceEnemy)
	                    {
	                    	newblupi.enemy=true;
						}
						else
							newblupi.enemy=false;
	                    
	                    blupi.push_back(newblupi);
	                }
	                keyboardtime = 0;
	            }
	        }
	        else
	            keyboardtime = 6;
	

			
			
			
			
			
			
			
	        if (sf::Keyboard::isKeyPressed(Keyboard::Num0))
	        {
	            brush = "random";
	        }






	
	
	
	
	        if (sf::Keyboard::isKeyPressed(Keyboard::Num1))
	        {
	            brush = "fly";
	            RESETclock.restart();
	        }
	        if (sf::Keyboard::isKeyPressed(Keyboard::Num2))
	        {
	            brush = "jeep";
	            RESETclock.restart();
	        }
	        if (sf::Keyboard::isKeyPressed(Keyboard::Num3))
	        {
	            brush = "tank";
	            RESETclock.restart();
	        }
	        if (sf::Keyboard::isKeyPressed(Keyboard::Num4))
	        {
	            brush = "wave";
	            RESETclock.restart();
	        }
	        
			if (sf::Keyboard::isKeyPressed(Keyboard::Num5))
	        {
	        	forceEnemy=true;
	            RESETclock.restart();
	        }
	        if (sf::Keyboard::isKeyPressed(Keyboard::Num6))
	        {
	        	forceEnemy=false;
	        }
	        
	        
	        static bool warButton = false;
			if (sf::Keyboard::isKeyPressed(Keyboard::Num9))
			{
				if(!warButton)
					war=!war;
				warButton = true;
			}
			else
				warButton = false;
				

	
	        if (sf::Keyboard::isKeyPressed(Keyboard::Space))
	        {
	            blupi.clear();
	        }

















	        if (Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl))
	        {
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    mainwindow.close();
                }
        
	        }


			
			







	      	for (int a = 0; a < blupi.size(); a++)
	        {
	            blupi[a].update(mainwindow);
	
	            if (blupi[a].shootglue)
	            {
	                blupi[a].sprite.setTextureRect(IntRect(0, 609, 56, 58));
	                Blupi newblupi;
	                newblupi.status = blupi[a].glueball;
	                newblupi.sprite.setTexture(textures.element);
	                newblupi.sprite.setTextureRect(IntRect(210, 0, 16, 16));
	                newblupi.source=a;
	                if (blupi[a].leftside)
	                    newblupi.sprite.setPosition(blupi[a].sprite.getPosition().x - 18, blupi[a].sprite.getPosition().y + 15);
	                else
	                    newblupi.sprite.setPosition(blupi[a].sprite.getPosition().x + 18, blupi[a].sprite.getPosition().y + 2);
	
	                newblupi.leftside = blupi[a].leftside;
	                blupi.push_back(newblupi);
	                blupi[a].shootglue = false;
	            }
	            
	            
	            
	            
	            if (blupi[a].dropglue)
	            {
	            	
	                Blupi newblupi;
	                newblupi.status = blupi[a].glueball;
	                newblupi.velocity.y=10;
	                newblupi.sprite.setTexture(textures.element);
	                newblupi.sprite.setTextureRect(IntRect(210, 0, 16, 16));
	                newblupi.source=a;
	                
					newblupi.sprite.setPosition(blupi[a].sprite.getPosition().x, blupi[a].sprite.getPosition().y);
	                
					blupi[a].dropglue = false;
	                blupi.push_back(newblupi);
	                
	            }
	            
	            
	            
	            
	
	
				if(war)
				{
					int z=0;
					for(auto b:blupi)
					{
						
						z++;
						if(b.status == b.glueball && blupi[a].status != b.glueball && b.source != a && blupi[a].status != b.glued)
						{
							if(b.source>-1&&b.source<blupi.size())
							{
							
								if(blupi[b.source].enemy != blupi[a].enemy)
								{
									
									if(blupi[a].sprite.getGlobalBounds().contains(b.sprite.getPosition()))
									{
										blupi[a].status = b.glued;
										blupi[a].sprite.setTexture(textures.element);
										blupi[a].sprite.setTextureRect(IntRect(107,471,61,54));
										blupi.erase(blupi.begin() + z);
										break;
									}
								}
							}
						}
					}
				}
	
	
	
	
	            if (blupi[a].sprite.getPosition().x < -(blupi[a].sprite.getTextureRect().width / 2) || blupi[a].sprite.getPosition().x > workarea.width + (blupi[a].sprite.getTextureRect().width / 2))
	            {
	                blupi.erase(blupi.begin() + a);
	            }
	
	            if (blupi[a].sprite.getTextureRect() == IntRect(0, 0, 0, 0))
	            {
	                blupi.erase(blupi.begin() + a);
	            }
	
	            if (blupi[a].deletetime.getElapsedTime().asSeconds() > 50)
	                blupi.erase(blupi.begin() + a);
	
	            if (blupi[a].status == blupi[a].fly)
	            {
	                if (blupi[a].deletetime.getElapsedTime().asSeconds() > 20)
	                {
	                    blupi.erase(blupi.begin() + a);
	                }
	            } 
	        }










			
		}
		
		
		
		static bool uptodate = false;
		
		sf::Color clearColor = COLORMODE::GET(sf::Color::Transparent);
		if(ClearScreen::modern)
		{
			clearColor = COLORMODE::GET(sf::Color(255,0,255));				
		}
		else
		{
			if(!uptodate)
			{
				COLORMODE::type = "BGRA";
				textures.updateImages();
				uptodate = true;
			}
		}
			
			
		//draw
		mainwindow.setView(view);
    	mainwindow.clear(clearColor);
    
        for (auto& b : blupi) {
            b.draw(mainwindow);
        }
        
		mainwindow.display();

		if(!ClearScreen::modern)
      	{
			//draw again
			ClearScreen::renderTexture.setView(view);
	    	ClearScreen::renderTexture.clear(clearColor);
	    	
	        for (auto& b : blupi) {
	            b.draw(ClearScreen::renderTexture);
	        }       	
	        
	        ClearScreen::renderTexture.display();
	  	
		}
		
		ClearScreen::update(handle);
		
    }
    
    ClearScreen::Cleanup();
    
    return 0;
}
