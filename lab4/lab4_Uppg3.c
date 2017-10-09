// Demo of heavily simplified sprite engine
// by Ingemar Ragnemalm 2009
// used as base for lab 4 in TSBK03.
// OpenGL 3 conversion 2013.

#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	#include "MicroGlut.h"
	// uses framework Cocoa
#else
	#include <GL/gl.h>
	#include "MicroGlut.h"
	
#endif

#include <stdlib.h>
#include <math.h>

#include "LoadTGA.h"
#include "SpriteLight.h"
#include "GL_utilities.h"

// L�gg till egna globaler h�r efter behov.
float alignWeight = 0.005f, cohesionWeight=0.0005f, avoidWeight = 0.05f; //0.004. 0.0005


void SpriteBehavior() // Din kod!
{
// L�gg till din labbkod h�r. Det g�r bra att �ndra var som helst i
// koden i �vrigt, men mycket kan samlas h�r. Du kan utg� fr�n den
// globala listroten, gSpriteRoot, f�r att kontrollera alla sprites
// hastigheter och positioner, eller arbeta fr�n egna globaler.
// Double loop for accumulating contributions from other boids

	//loop through all sprites
	SpritePtr currSp = gSpriteRoot; //current sprite

	FPoint speedDiffSum,posAvg,avoidanceVec; 
	

	while(currSp) //while there are sprites
	{

		int spriteCounter = 0;
		//set all to 0,0
		speedDiffSum = FPointSet(0.0f,0.0f); //summated differnce in speed
		posAvg =  FPointSet(0.0f,0.0f); //average pos
		avoidanceVec =  FPointSet(0.0f,0.0f); //avoidance

		//make another loop, to compare with all other sprites
		SpritePtr compSp = gSpriteRoot; //the sprite currently being compared
		
		while(compSp)
		{	
			
			if(currSp == compSp) {
				compSp = compSp->next;
				continue;				
			}
			
			//get the distance between current sprites
			FPoint posDiff = FPointSub(compSp->position, currSp->position);
			float dist = sqrt(pow(posDiff.v,2)+pow(posDiff.h,2));
			
			if(dist <= kMaxDistance) //if boids are close enough to affect each other
			{ 
				//handle cohesion aka get together				
				posAvg = FPointAdd(posAvg, posDiff);

				//apply alignment aka speed
				speedDiffSum = FPointAdd(speedDiffSum, FPointSub(compSp->speed,currSp->speed));

				spriteCounter++;
				
				//avoidance aka keep distance
				if(dist <= (kMaxDistance/2.0f))
				{
					//use the normalized difference vec
					avoidanceVec = FPointAdd(FPointScalarDiv(FPointSub(currSp->position,compSp->position), dist), avoidanceVec);
					
				}
			}
			compSp = compSp->next;
			
		} 
				
		if(spriteCounter > 0)
		{
			//calculate avg diff in speed and pos
			currSp->cohesion = FPointScalarDiv(posAvg, (float)spriteCounter);
			currSp->alignment = FPointScalarDiv(speedDiffSum, (float)spriteCounter);
			currSp->avoidance = FPointScalarDiv(avoidanceVec, (float)spriteCounter);

		}

		//next sprite
		currSp = currSp->next;
	} 

	//loop again and apply calculations
	currSp = gSpriteRoot;
	while(currSp)
	{
		FPoint alignTot, cohesionTot, avoidanceTot;

		alignTot = FPointScalarMult(currSp->alignment,alignWeight);
		cohesionTot = FPointScalarMult(currSp->cohesion,cohesionWeight);
		avoidanceTot = FPointScalarMult(currSp->avoidance,avoidWeight);
		
		//update speed
		currSp->speed = FPointAdd(avoidanceTot,FPointAdd(cohesionTot,FPointAdd(currSp->speed,alignTot)));
		//stabilize
		currSp->speed = FPointScalarMult(currSp->speed,1.0005);
				
		currSp = currSp->next;
	}

}

// Drawing routine
void Display()
{
	SpritePtr sp;
	
	glClearColor(0, 0, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	DrawBackground();
	
	SpriteBehavior(); // Din kod!
	
// Loop though all sprites. (Several loops in real engine.)
	sp = gSpriteRoot;
	do
	{
		HandleSprite(sp); // Callback in a real engine
		DrawSprite(sp);
		sp = sp->next;
	} while (sp != NULL);
	
	glutSwapBuffers();
}

void Reshape(int h, int v)
{
	glViewport(0, 0, h, v);
	gWidth = h;
	gHeight = v;
}

void Timer(int value)
{
	glutTimerFunc(20, Timer, 0);
	glutPostRedisplay();
}

// Example of user controllable parameter
//someValue = cohesionWeight;

void Key(unsigned char key,
         __attribute__((unused)) int x,
         __attribute__((unused)) int y)
{
  switch (key)
  {
    case '+':
		avoidWeight += 0.005;	
		printf("avoidWeight = %f\n", avoidWeight);		
    	break;
    case '-':
		avoidWeight -= 0.005;
    	printf("avoidWeight = %f\n", avoidWeight);
    	break;
    case 0x1b:
      exit(0);
  }
  
}

void Init()
{
	TextureData *sheepFace, *blackFace, *dogFace, *foodFace;
	
	LoadTGATextureSimple("bilder/leaves.tga", &backgroundTexID); // Bakgrund
	
	sheepFace = GetFace("bilder/sheep.tga"); // Ett f�r
	blackFace = GetFace("bilder/blackie.tga"); // Ett svart f�r
	dogFace = GetFace("bilder/dog.tga"); // En hund
	foodFace = GetFace("bilder/mat.tga"); // Mat
	
	NewSprite(sheepFace, 100, 200, 1, 1);
	NewSprite(sheepFace, 200, 100, 1.5, -1);
	NewSprite(sheepFace, 250, 200, -1, 1.5);
	NewSprite(sheepFace, 200, 200, -1, 1.5);
	NewSprite(sheepFace, 100, 100, -1, 1.5);
	NewSprite(sheepFace, 50, 100, -1, 1.5);
	NewSprite(sheepFace, 50, 50, -1, 1.5);
	NewSprite(sheepFace, 200, 50, -1, 1.5);
	NewSprite(sheepFace, 50, 200, -1, 1.5);
	NewSprite(sheepFace, 50, 250, -1, 1.5);
	NewSprite(sheepFace, 150, 50, -1, 1.5);
	NewSprite(sheepFace, 300, 300, 1, 1);
	
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutInitContextVersion(3, 2);
	glutCreateWindow("SpriteLight demo / Flocking");
	
	glutDisplayFunc(Display);
	glutTimerFunc(20, Timer, 0); // Should match the screen synch
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	
	InitSpriteLight();
	Init();
	
	glutMainLoop();
	return 0;
}
