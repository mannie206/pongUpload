#include "AIE.h"
#include <iostream>
using namespace std;


//const int......



const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

struct Ball
{
	float width;
	float height;
	float postionX;
	float postionY;
	float speedX;
	float speedY;
	unsigned int spriteID;// = CreateSprite("./images/ball.png", 30, 30, true);

	void Move(float a_fDeltaTime)
	{
		postionX += speedX * a_fDeltaTime;
		postionY += speedY * a_fDeltaTime;
		MoveSprite(spriteID, postionX, postionY);

		// BOTOOM

		if (postionY < (0))
		{
			postionY = SCREEN_HEIGHT / 2;
			postionX = SCREEN_WIDTH / 2;

		}

		// RIGHT SIDE
		if (postionX > SCREEN_WIDTH) 
		{
			speedX = speedX * -1;
		}
		// leftside 

		if (postionX < 0)
		{
			speedX = speedX * -1;
		}
		// TOP 
		if (postionX  < (0)) 
		{
			postionX = SCREEN_WIDTH / 1;
			postionY = SCREEN_HEIGHT / 1;
		}



	}

	void Draw()
	{
		DrawSprite(spriteID);
	}
};



struct Padle
{
	float width;
	float height;
	float postionX;
	float postionY;
	float speedX;
	float speedY;
	unsigned int spriteID;// = CreateSprite("./images/padle.png", 40, 40, true);

	void Move(float a_fDeltaTime)
	{
		MoveSprite(spriteID, postionX, postionY);

		if (IsKeyDown('A'))
		{
			postionX -= 3.f;
			
			if (postionX < (width*.5f))
			{
				postionX = width*.5f;
			}
		
		}


		if (IsKeyDown('D'))

		{
			postionX += 3.f;
			if (postionX > (SCREEN_WIDTH - (width*3.f) ))
			{
				postionX = SCREEN_WIDTH - (width*3.f);
			}
		}
	}

	void Draw()
	{
		DrawSprite(spriteID);
	};

};

int main(int argc, char* argv[])
{
	Initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false, "pong");

	Ball joe;
	joe.postionX = (float)(SCREEN_WIDTH / 2);
	joe.postionY = (float)(SCREEN_HEIGHT / 2);
	joe.speedX = 5.0f;
	joe.speedY = -1.0f;
	joe.width = 30;
	joe.height = 30;
	
	joe.spriteID = CreateSprite("./images/ball.png", joe.width,joe.height, true);

	Padle may;
	may.postionX = 20.0f;
	may.postionY = 300.0f;
	may.speedX = 2.0f;
	may.speedY = 2.0f;
	may.width = 20;
	may.height = 30;
	may.spriteID = CreateSprite("./images/padle.png", may.width, may.height, true);


	SetBackgroundColour(SColour(14, 0, 24, 8));



	//GameLoop...
	do
	{
		float DeltaTime = GetDeltaTime();
		may.Move(DeltaTime);

		ClearScreen();
		joe.Move(GetDeltaTime() * 100);
		joe.Draw();
		may.Move(GetDeltaTime() * 100);
		may.Draw();


	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}