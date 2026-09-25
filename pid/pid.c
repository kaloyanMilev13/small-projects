#include <raylib.h>
#include <math.h>
#include <raymath.h> // for clamp

#define PIXELS_PER_METER 200.0f

#define CART_WIDTH 0.75f

#define STARTING_ANGLE 0.0f
#define MAX_TARGET_ANGLE 0.05f

#define KP 35.0f
#define KD 10.0f
#define KI 0.5f

#define KP_POSITION 0.02f
#define KD_POSITION 0.10f

typedef struct{

	float x;
	float y;

	float velocity;
	float acceleration;
	float mass;

} Cart;


typedef struct{

	float angle;
	float angularVelocity;
	float angularAcceleration;

	float length;
	float mass;

} Pole;


int main(void){

	bool showStats = true;

	float dt;

	float elapsedTime = 0;

	float gravity = 9.81f;

	float totalForce = 0;
	float force = 0;
	float friction = 0.6;

	float trackLeft = 0.5f; //meters
	float trackRight = 4.5f;

	float targetX = (trackLeft + trackRight) / 2.0f;	

	InitWindow(1000, 600, "PID CART - NEW BUILD 123");
	SetTargetFPS(60);

	Cart cart;
	Pole pole;


	cart.x = 2.0f;
	cart.y = 1.5f;

	cart.acceleration = 0;
	cart.velocity = 0;
	cart.mass = 1;


	pole.length = 1.0f;
	pole.angle = STARTING_ANGLE;
	pole.angularVelocity = 0;
	pole.angularAcceleration = 0;
	pole.mass = 1;


	float poleEndX = 0;
	float poleEndY = 0;

	float pivotXMeters = cart.x + CART_WIDTH / 2.0f;
	float pivotYMeters = cart.y;
	float pivotX;
	float pivotY;

	//float damping = 5.0f;


	float poleCOMLength = pole.length / 2.0f;

	float poleCOMX = pivotXMeters + poleCOMLength * sinf(pole.angle);
	float poleCOMY = pivotYMeters - poleCOMLength * cosf(pole.angle);


	//P controller
	float targetAngle = 0.0f;
	float error = pole.angle - targetAngle;
	float Kp = KP;

	float KpPosition = KP_POSITION;
	float maxTargetAngle = MAX_TARGET_ANGLE;

	//D Controller
	float Kd = KD;
	float KdPosition = KD_POSITION;

	//I Controller
	float integral = 0.0f;
	float Ki = KI;


	//cart controller
	float positionError = targetX - (cart.x + CART_WIDTH / 2.0f); // otklonenie



	bool rightArrow = false;
	bool leftArrow = false;


	//camera

	Camera2D camera = {0};

	camera.target = (Vector2){cart.x * PIXELS_PER_METER, cart.y * PIXELS_PER_METER};
	camera.offset = (Vector2){500, 300};

	camera.rotation = 0.0f;
	camera.zoom = 1.0f;



	while(!WindowShouldClose()){

		rightArrow = false;
		leftArrow = false;

		if(IsKeyPressed(KEY_TAB)){

			showStats = !showStats;

		}

		float keyForce = 0;

		if(IsKeyDown(KEY_RIGHT)){

			keyForce = 5;
			rightArrow = true;

		}else if(IsKeyDown(KEY_LEFT)){

			keyForce = -5;
			leftArrow = true;
		}

		dt = 1.0f / 60.0f;

		elapsedTime += dt;

		//PID controller

		positionError = targetX - (cart.x + CART_WIDTH / 2.0f);

		targetAngle = KpPosition * positionError - KdPosition * cart.velocity;

		targetAngle = Clamp(targetAngle, -maxTargetAngle, maxTargetAngle);

		error = pole.angle - targetAngle;

		integral += error * dt;

		force = Kp * error + Kd * pole.angularVelocity + Ki * integral + keyForce;


		float pTerm = Kp * error;
		float dTerm = Kd * pole.angularVelocity;
		float iTerm = Ki * integral;


		//cart position
		totalForce = force - friction * cart.velocity;
		//cart.acceleration = totalForce / cart.mass;

		float temp = (totalForce + pole.mass * (pole.length / 2) * pole.angularVelocity * pole.angularVelocity * sinf(pole.angle)) / (pole.mass + cart.mass);

		pole.angularAcceleration = (gravity * sinf(pole.angle) - cosf(pole.angle) * temp) / ((pole.length / 2) * (4.0f / 3.0f - pole.mass * cosf(pole.angle) * cosf(pole.angle) / (pole.mass + cart.mass)));

		cart.acceleration = temp - (pole.mass * (pole.length / 2) * pole.angularAcceleration * cosf(pole.angle)) / (pole.mass + cart.mass);

		cart.velocity = cart.velocity + cart.acceleration * dt;	
		cart.x = (cart.x + cart.velocity * dt);


		//pole angle
		//pole.angularAcceleration = (gravity / pole.length) * sinf(pole.angle) - damping * pole.angularVelocity;
		pole.angularVelocity += pole.angularAcceleration * dt;
		pole.angle += pole.angularVelocity * dt;



		//pivot position
		pivotXMeters = cart.x + CART_WIDTH / 2.0f;
		pivotYMeters = cart.y;
		pivotX = pivotXMeters * PIXELS_PER_METER;
		pivotY = pivotYMeters * PIXELS_PER_METER;


		//pole position
		poleEndX = pivotX + sinf(pole.angle) * pole.length * PIXELS_PER_METER;
		poleEndY = pivotY - cosf(pole.angle) * pole.length * PIXELS_PER_METER;

		poleCOMX = pivotXMeters + poleCOMLength * sinf(pole.angle);
		poleCOMY = pivotYMeters - poleCOMLength * cosf(pole.angle);




		camera.target.x = cart.x * PIXELS_PER_METER;

		BeginDrawing();

		ClearBackground(BLACK);

		float trackY = (cart.y + 0.5f) * PIXELS_PER_METER;

		float trackLeftPixels = trackLeft * PIXELS_PER_METER;
		float trackRightPixels = trackRight * PIXELS_PER_METER;

		float dashLength = 20.0f;
		float gapLength = 10.0f;


		//dashed track line
		for(float x = trackLeftPixels; x < trackRightPixels; x += dashLength + gapLength){

			float endX = x + dashLength;

			if(endX > trackRightPixels){

				endX = trackRightPixels;

			}

			DrawLine(x, trackY, endX, trackY, GRAY);

		}

		float markerHeight = 25.0f;


		//left end
		DrawLine(trackLeftPixels, trackY - markerHeight, trackLeftPixels, trackY + markerHeight, WHITE);


		//right end
		DrawLine(trackRightPixels, trackY - markerHeight, trackRightPixels, trackY + markerHeight, WHITE);

		float targetXPixels = targetX * PIXELS_PER_METER;

		DrawLine(
				targetXPixels,
				trackY - 15,
				targetXPixels,
				trackY + 15,
				GRAY
			);

		//BeginMode2D(camera);

		DrawRectangleLines(cart.x * PIXELS_PER_METER, cart.y * PIXELS_PER_METER, 150, 100, WHITE);

		DrawLine(pivotX, pivotY, poleEndX, poleEndY, WHITE);

		//center of gravity
		//DrawCircle(poleCOMX * PIXELS_PER_METER, poleCOMY * PIXELS_PER_METER, 5, WHITE);

		DrawCircle(poleEndX, poleEndY, 10, WHITE);


		if(leftArrow){

			DrawRectangle(45, 510, 45, 12, WHITE);
			DrawTriangle((Vector2){55, 495},(Vector2){55, 537},(Vector2){25, 516},WHITE);

		}

		if(rightArrow){

			DrawRectangle(910, 510, 45, 12, WHITE);
			DrawTriangle((Vector2){945, 495},(Vector2){975, 516},(Vector2){945, 537},WHITE);

		}


		//EndMode2D();
		if(showStats){

			//stats

			DrawRectangle(10, 10, 430, 290, Fade(BLACK, 0.75f));
			DrawRectangle(620, 10, 370, 290, Fade(BLACK, 0.75f));


			//pole + cart stats

			DrawText("SYSTEM", 25, 20, 30, WHITE);

			DrawText(TextFormat("Angle: %.4f rad", pole.angle), 25, 65, 24, WHITE);
			DrawText(TextFormat("Angular velocity: %.4f rad/s", pole.angularVelocity), 25, 100, 24, WHITE);
			DrawText(TextFormat("Angular acceleration: %.4f rad/s^2", pole.angularAcceleration), 25, 135, 24, WHITE);

			DrawText(TextFormat("Cart position: %.3f m", cart.x), 25, 185, 24, WHITE);
			DrawText(TextFormat("Cart velocity: %.3f m/s", cart.velocity), 25, 220, 24, WHITE);
			DrawText(TextFormat("Cart acceleration: %.3f m/s^2", cart.acceleration), 25, 255, 24, WHITE);


			//PID stats

			DrawText("PID", 635, 20, 30, WHITE);

			DrawText(TextFormat("Force: %.3f N", force), 635, 65, 24, WHITE);
			DrawText(TextFormat("Error: %.4f", error), 635, 100, 24, WHITE);

			DrawText(TextFormat("P: %.3f N", pTerm), 635, 150, 24, WHITE);
			DrawText(TextFormat("I: %.3f N", iTerm), 635, 185, 24, WHITE);
			DrawText(TextFormat("D: %.3f N", dTerm), 635, 220, 24, WHITE);

			DrawText(TextFormat("Kp: %.2f", Kp), 830, 150, 24, WHITE);
			DrawText(TextFormat("Ki: %.2f", Ki), 830, 185, 24, WHITE);
			DrawText(TextFormat("Kd: %.2f", Kd), 830, 220, 24, WHITE);

			DrawText(TextFormat("Pos error: %.3f", positionError), 25, 320, 20, WHITE);
			DrawText(TextFormat("Target angle: %.3f", targetAngle), 25, 345, 20, WHITE);

		}


		int minutes = (int)elapsedTime / 60;
		float seconds = fmodf(elapsedTime, 60.0f);

		const char *timerText = TextFormat("%02d:%05.2f", minutes, seconds);

		int timerWidth = MeasureText(timerText, 30);

		DrawText(timerText, 500 - timerWidth / 2, 555, 30, WHITE);

		EndDrawing();

	}

	CloseWindow();

}
