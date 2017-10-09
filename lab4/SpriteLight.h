// SpriteLight - Heavily simplified sprite engine
// by Ingemar Ragnemalm 2009

// What does a mogwai say when it sees a can of soda?
// Eeek! Sprite light! Sprite light!

#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	#include "MicroGlut.h"
#else
	#include <GL/gl.h>
	#include "MicroGlut.h"
#endif

#include "LoadTGA.h"

typedef struct FPoint
{
	GLfloat h, v; //vertical, horisontal
} FPoint;

typedef struct SpriteRec
{
	FPoint position;
	TextureData *face;
	FPoint speed;
	GLfloat rotation;
	struct SpriteRec *next; //pointer to next sprite
	
	// Add custom sprite data here as needed
	FPoint avoidance;
	FPoint cohesion;
	FPoint alignment;

	int typeID;
	
} SpriteRec, *SpritePtr;

// Globals: The sprite list, background texture and viewport dimensions (virtual or real pixels)
extern SpritePtr gSpriteRoot;
extern SpritePtr dogSpritePtr;
extern GLuint backgroundTexID;
extern long gWidth, gHeight;
extern float kMaxDistance; //distance/radius of when boids affect each other

// Functions
TextureData *GetFace(char *fileName);
struct SpriteRec *NewSprite(int id, TextureData *f, GLfloat h, GLfloat v, GLfloat hs, GLfloat vs);
void HandleSprite(SpritePtr sp);
void DrawSprite(SpritePtr sp);
void DrawBackground();

void InitSpriteLight();
FPoint FPointSub(FPoint a, FPoint b);
FPoint FPointAdd(FPoint a, FPoint b);//a+b
FPoint FPointScalarDiv(FPoint a, float b);
FPoint FPointScalarMult(FPoint a, float b);
FPoint FPointSet(float a, float b);


