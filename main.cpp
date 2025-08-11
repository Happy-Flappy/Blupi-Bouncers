#include <SFML/Graphics.hpp>
#include <windows.h>
#include <winuser.h>
#include <shellapi.h>
#include <cmath>
#include <string>
#include <vector> 
#include <iostream>
#include "getSize.h"
#include "clearscreen.h"



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


    Textures()
    {
        clearcolor("blupi000.bmp", Color::Blue, Color::Transparent, blupi);
        clearcolor("element.bmp", Color::Blue, Color::Transparent, element);


    }
} textures;




























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
			
			
			if(sprite.getPosition().x< GetSize::Bounds::workarea.width/8)
			{
				
				angle-=4;
			}
			if(sprite.getPosition().x>GetSize::Bounds::workarea.width - GetSize::Bounds::workarea.width/8)
			{
				angle++;
			}
			 
			
			
            sprite.move((cos(rad) * (GetSize::Bounds::workarea.width/8))/40, (sin(rad) * (GetSize::Bounds::workarea.height/8))/40);

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
            if (sprite.getPosition().y + (sprite.getTextureRect().height / 2) < GetSize::Bounds::workarea.height)
            {
                velocity.y += gravity;
            }
            else
            {
            	velocity.y = 0;
                sprite.setPosition(sprite.getPosition().x,GetSize::Bounds::workarea.height-(sprite.getTextureRect().height / 2));
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
	
	int FIXED_WIDTH = 1920;
	int FIXED_HEIGHT = 1080;
	
	
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); //Get fullSize
	
    
	
	
	if(!GetSize::Init())
	{
		MessageBox(NULL,"Failed to find DPI! \nQuitting...","Failed",MB_OK);
		return 0;
	}	


    View view;
    view.reset(sf::FloatRect(0,0,FIXED_WIDTH,FIXED_HEIGHT));// (/1.3)

	GetSize::Bounds::workarea = sf::IntRect(0,0,FIXED_WIDTH,FIXED_HEIGHT - (FIXED_HEIGHT * GetSize::Percent::taskbar.y));
	
	
    RenderWindow mainwindow(VideoMode(desktop.width,desktop.height+1),"", Style::None);	
    sf::WindowHandle handle = mainwindow.getSystemHandle();
	mainwindow.setPosition(Vector2i(0, 0));
	
	
	

    
	ClearScreen::Init(FIXED_WIDTH,FIXED_HEIGHT,mainwindow,GetSize::Scaled::workarea.width,GetSize::Scaled::workarea.height);
	
	
	
	
	
    Clock dtclock;
    Time timesincelastupdate=Time::Zero;
    Time timeperframe=seconds(1.f/60.f);
	
	
	
	Clock RESETclock;
    string brush = "random";
    float keyboardtime = 0;
    bool forceEnemy=false;
    
    
	
	
    while (mainwindow.isOpen())
    {





		if(VideoMode::getDesktopMode().height!=desktop.height)
		{
			
			mainwindow.setSize(Vector2u(VideoMode::getDesktopMode().width,VideoMode::getDesktopMode().height+1));
			
			if(!GetSize::Init())
			{
				MessageBox(NULL,"Failed to find DPI! \nQuitting...","Failed",MB_OK);
				return 0;				
			}
	
			GetSize::Bounds::workarea = sf::IntRect(0,0,FIXED_WIDTH,FIXED_HEIGHT - (FIXED_HEIGHT * GetSize::Percent::taskbar.y));
			
			
			
			desktop = VideoMode::getDesktopMode();
			
			//Clearscreen size needs to be re-updated so that it won't be cut off.
			ClearScreen::Init(FIXED_WIDTH,FIXED_HEIGHT,mainwindow,GetSize::Scaled::workarea.width,GetSize::Scaled::workarea.height);
				
		}


		if(GetTopWindow(NULL)!=handle)
    		SetWindowPos(handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

		
		MPosition = mainwindow.mapPixelToCoords(Mouse::getPosition(mainwindow));
		
		
		

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
	                    int x = rand() % GetSize::Bounds::workarea.width;
	                    int y = rand() % GetSize::Bounds::workarea.height;
	
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
	        
	        
	        
			if (sf::Keyboard::isKeyPressed(Keyboard::Num9))
			{
				war=true;
			}
				

	
	        if (sf::Keyboard::isKeyPressed(Keyboard::Space))
	        {
	            blupi.clear();
	        }

















	        if (Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl))
	        {
	            if (Keyboard::isKeyPressed(Keyboard::LAlt) || Keyboard::isKeyPressed(Keyboard::RAlt))
	            {
	                if (Keyboard::isKeyPressed(Keyboard::Escape))
	                {
	                    mainwindow.close();
	                }
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
	
	
	
	
	            if (blupi[a].sprite.getPosition().x < -(blupi[a].sprite.getTextureRect().width / 2) || blupi[a].sprite.getPosition().x > GetSize::Bounds::workarea.width + (blupi[a].sprite.getTextureRect().width / 2))
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
		
		
			
		//draw
		mainwindow.setView(view);
    	mainwindow.clear(sf::Color(255,0,255));
    
        for (auto& b : blupi) {
            b.draw(mainwindow);
        }
        
		mainwindow.display();

		if(!ClearScreen::modern)
      	{
			//draw again
	    	ClearScreen::renderTexture.clear(sf::Color(255,0,255));
	    	
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
