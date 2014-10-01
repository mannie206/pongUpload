#include "AIE.h"
#include <iostream>
using namespace std;


//const int......



const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

struct Colisions
{
	float Xmin;
	float Xmax;
	float Ymin;
	float Ymax;
};

struct Ball
{
	float deltatime = GetDeltaTime();
	float width;
	float height;
	Colisions box;
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
			speedY *= -1.f;
		}
		if (postionY > SCREEN_HEIGHT - 60)
		{
			speedY *= -1.f;
		}

		// RIGHT SIDE
		if (postionX > SCREEN_WIDTH - (width*.5f))
		{
			postionY = SCREEN_HEIGHT / 2;
			postionX = SCREEN_WIDTH / 2;
			speedX = speedX * -1;
		}
		// leftside 

		if (postionX < 0)
		{
			postionY = SCREEN_HEIGHT / 2;
			postionX = SCREEN_WIDTH / 2;
			speedX = speedX * -1;
		}

		box.Xmin = postionX - (width*.5f);
		box.Xmax = postionX + (width*.5f);
		box.Ymin = postionY - (height*.5f);
		box.Ymax = postionY + (height*.5f);
	}

	void Draw()
	{
		DrawSprite(spriteID);
	}
};

struct Padle
{
	Colisions box;
	float postionX;
	float postionY;
	float speedY = 500.f;
	float width = 30;
	float height = 100;
	unsigned int spriteID;
	unsigned int iMoveUpKey;
	unsigned int iMoveDownKey;

	void SetPostion(float a_x, float a_y)
	{
		postionX = a_x;
		postionY = a_y;
	}

	void SetMovementKeys(float a_moveUp, float a_moveDown)
	{
		iMoveUpKey = a_moveUp;
		iMoveDownKey = a_moveDown;
	}

	void Move(float a_fDeltaTime)
	{
		MoveSprite(spriteID, postionX, postionY);

		if (IsKeyDown(iMoveUpKey))
		{
			postionY += speedY * a_fDeltaTime;

			if (postionY > SCREEN_HEIGHT - 60)
			{
				postionY = SCREEN_HEIGHT - 60;
			}

		}


		if (IsKeyDown(iMoveDownKey))

		{
			postionY -= speedY * a_fDeltaTime;
			if (postionY < height*.5f)
			{
				postionY = height*.5f;
			}
		}

		box.Xmin = postionX - (width*.5f);
		box.Xmax = postionX + (width*.5f);
		box.Ymin = postionY - (height*.5f);
		box.Ymax = postionY + (height*.5f);

		MoveSprite(spriteID, postionX, postionY);
	}

	void Draw()
	{
		DrawSprite(spriteID);
	};

};
Padle may, two;

bool colisoncheck(Colisions box1, Colisions box2)
{
	if (box1.Xmin > box2.Xmin && box1.Ymin > box2.Ymin && box1.Xmin < box2.Xmax && box1.Ymin < box2.Ymax)
	{
		return true;
	}
	if (box1.Xmax > box2.Xmin && box1.Ymax > box2.Ymin && box1.Xmax < box2.Xmax && box1.Ymax < box2.Ymax)
	{
		return true;
	}
	if (box1.Xmin > box2.Xmin && box1.Ymax > box2.Ymin && box1.Xmin < box2.Xmax && box1.Ymax < box2.Ymax)
	{
		return true;
	}
	if (box1.Xmax > box2.Xmin && box1.Ymin > box2.Ymin && box1.Xmax < box2.Xmax && box1.Ymin < box2.Ymax)
	{
		return true;
	}
	return false;
}

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

	may.SetMovementKeys('W', 'S');
	two.SetMovementKeys('O', 'L');

	may.SetPostion(30, SCREEN_HEIGHT*.5f);
	two.SetPostion(SCREEN_WIDTH - 30, SCREEN_HEIGHT*.5f);

	joe.spriteID = CreateSprite("./images/ball.png", joe.width, joe.height, true);
	may.spriteID = CreateSprite("./images/padle.png", may.width, may.height, true);
	two.spriteID = CreateSprite("./images/padle2.png", may.width, may.height, true);


	SetBackgroundColour(SColour(14, 0, 24, 8));



	//GameLoop...
	do
	{
		float DeltaTime = GetDeltaTime();

		ClearScreen();

		two.Move(GetDeltaTime()); joe.Move(GetDeltaTime() * 100);
		may.Move(GetDeltaTime());
		

		if (colisoncheck(joe.box, may.box) && joe.speedX < 0)
		{
			joe.speedX *= -1;
			joe.speedY *= -1;
		}
		if (colisoncheck(joe.box, two.box) && joe.speedX > 0)
		{
			joe.speedX *= -1;
			joe.speedY *= -1;
		}

		joe.Draw();
		may.Draw();
		two.Draw();

	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}
