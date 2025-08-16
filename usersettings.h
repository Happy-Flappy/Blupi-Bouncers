


#ifndef USER_SETTINGS
#define USER_SETTINGS

#include <fstream>
#include <iostream>





namespace UserSettings
{
	float BlupiScale = 1.3;
	bool modern = false;
	
	void Get()
	{
		std::ifstream file;
		file.open("settings.txt");


		bool m = false;
		float scale = 1.3;
		
		
		bool failed = false;
		
		if(file.eof())
			failed = true;
		file >> m;
		if(file.eof())
			failed = true;
		file >> scale;
		
		if(failed)
		{
			m = false;
			scale = 1.3;
		}
			
			  
		BlupiScale = scale;
		modern = m;
		
		
	}
}


#endif