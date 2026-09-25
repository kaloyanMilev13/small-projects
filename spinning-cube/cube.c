#include <raylib.h>
#include <math.h>

/*
#define PI 3.14159265358979323846f
#define DEG2RAD (PI / 180.0f)
*/

float mult = 170.0f;
float z_offset = 4.0f;
float rad = 0.0f;
float angle = 0.0f;
int timeFrame = 0;

int originalPoints[8][3] = {

	{ -1, -1, 1 }, // 0
	{ 1, -1, 1 }, // 1
	{ 1, 1, 1 }, // 2
	{ -1,1, 1 }, // 3
	{ -1, -1, -1 }, // 4
	{ 1, -1, -1 }, // 5
	{ 1, 1, -1 }, // 6
	{ -1, 1, -1 } // 7

};

int points_2d[8][2];

float rotatedPoints[8][3];


void rotatePoints(int originalPoints[][3], float rotatedPoints[][3], float rad, float z_offset){

	for(int i = 0; i < 8; i++){
		rotatedPoints[i][0] = originalPoints[i][0] * cosf(rad) - originalPoints[i][2] * sinf(rad);
		rotatedPoints[i][1] = originalPoints[i][1];
		rotatedPoints[i][2] = originalPoints[i][0] * sinf(rad) + originalPoints[i][2] * cosf(rad) + z_offset;
	}
}

void convertPoints(int points_2d[][2], float rotatedPoints[][3]){

	for(int i = 0; i < 8; i++){
		
		points_2d[i][0] = roundf(400.0f + rotatedPoints[i][0] / rotatedPoints[i][2] * mult);
		points_2d[i][1] = roundf(300.0f - rotatedPoints[i][1] / rotatedPoints[i][2] * mult);

	}

}


void drawCube(int points_2d[][2]){

	BeginDrawing();

	ClearBackground(BLACK);

	//draw Cube
	DrawLine(points_2d[0][0], points_2d[0][1], points_2d[1][0], points_2d[1][1], RAYWHITE); 
	DrawLine(points_2d[1][0], points_2d[1][1], points_2d[2][0], points_2d[2][1], RAYWHITE);
	DrawLine(points_2d[2][0], points_2d[2][1], points_2d[3][0], points_2d[3][1], RAYWHITE);
	DrawLine(points_2d[3][0], points_2d[3][1], points_2d[0][0], points_2d[0][1], RAYWHITE);

	DrawLine(points_2d[4][0], points_2d[4][1], points_2d[5][0], points_2d[5][1], RAYWHITE); 
	DrawLine(points_2d[5][0], points_2d[5][1], points_2d[6][0], points_2d[6][1], RAYWHITE);
	DrawLine(points_2d[6][0], points_2d[6][1], points_2d[7][0], points_2d[7][1], RAYWHITE);
	DrawLine(points_2d[7][0], points_2d[7][1], points_2d[4][0], points_2d[4][1], RAYWHITE);

	DrawLine(points_2d[0][0], points_2d[0][1], points_2d[4][0], points_2d[4][1], RAYWHITE); 
	DrawLine(points_2d[1][0], points_2d[1][1], points_2d[5][0], points_2d[5][1], RAYWHITE);
	DrawLine(points_2d[2][0], points_2d[2][1], points_2d[6][0], points_2d[6][1], RAYWHITE);
	DrawLine(points_2d[3][0], points_2d[3][1], points_2d[7][0], points_2d[7][1], RAYWHITE);


	EndDrawing();

}

int main(void){


	InitWindow(800, 600, "Cubee"); 
	
	SetTargetFPS(60);

	while(!WindowShouldClose()){

		timeFrame++;
		mult = 170 + sinf(timeFrame * 0.05) * 30;

		if(angle <= 90)
			angle++;
		else
			angle = 0;
	
	
		rad = angle * DEG2RAD;

		
		rotatePoints(originalPoints, rotatedPoints, rad, z_offset);

		convertPoints(points_2d, rotatedPoints);

		drawCube(points_2d);
		

	}
	
       	CloseWindow();


	return 0;
}
