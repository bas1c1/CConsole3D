#include <stdio.h>
short linux = 0;
#if defined(linux) || defined(__linux) || defined(UNIX)
	linux = 1;
#else
	#include <windows.h>
	#include <winuser.h>
#endif
#include <math.h>
#include "vector.h"
#include "functions.h"

#define WIDTH 160
#define HEIGHT 50

struct mains
{
	char *screen;
} mains;

#define screen mains.screen

void setMirror(vec3 *ro, vec3 *rd, float minIt) {
	*ro = v3addv(v3mul(*rd, minIt - 0.01), *ro);
}

void main(void) {
	if (linux == 1) {
		printf("%s\n", "Your device is not supported");
		return;
	}
    system("mode con cols=160 lines=50");
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
    float aspect = (float)WIDTH/HEIGHT;
    float pix_aspect = 11.0f/24.0f;
	screen = (char*)malloc(WIDTH+HEIGHT+1);
	screen[WIDTH * HEIGHT] = '\0';
	char gradient[] = " .:!/r(l1Z4H9W8$@";//
	int gradientSize = sizeof(gradient)-2;
	
	for (int t = 0; t < 10000; t++) {
		vec3 light = norm((vec3){-0.5, 0.5, -1.0});
		//light = norm(v3rotateZ(light, t * 0.01));
		vec3 spherePos = (vec3){0, 3, 0};
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				vec2 uv = sub(mul(diviv( (vec2){i, j}, (vec2){WIDTH, HEIGHT} ), 2.0f), 1.0f);
				uv.x *= aspect * pix_aspect;
				vec3 ro = (vec3) {-6, 0, 0};
				vec3 rd = norm((vec3) {2, uv.x, uv.y});
				ro = v3rotateY(ro, 0.25);
				rd = v3rotateY(rd, 0.25);
				ro = v3rotateZ(ro, t * 0.01);
				rd = v3rotateZ(rd, t * 0.01);
				float diff = 1;
				for (int k = 0; k < 200; k++) {
					float minIt = 99999;
					vec2 intersection;// = sphere(v3subv(ro, spherePos), rd, 1);
					vec3 n;// = (vec3){0, 0, 0};
					float albedo = 1;
					/*
					if (intersection.x > 0) {
						vec3 itPoint = v3mul(v3addv(v3subv(ro, spherePos), rd), intersection.x);
						minIt = intersection.x;
						n = norm(itPoint);
						
					}*/
					vec3 boxN = (vec3){0, 0, 0};
					intersection = box(ro, rd, (vec3){2, 1, 1}, boxN, &boxN);
					if (intersection.x > 0 && intersection.x < minIt) {
						minIt = intersection.x;
						n = boxN;
						//setMirror(&ro, &rd, minIt);
					}

					vec3 box2N = (vec3){0, 3, 0};
					intersection = box(ro, rd, (vec3){0.5, 2, 0.5}, box2N, &box2N);
					if (intersection.x > 0 && intersection.x < minIt) {
						minIt = intersection.x;
						n = box2N;
						//setMirror(&ro, &rd, minIt);
					}

					
					float tmp = plane(ro, rd, (vec3){0, 0, -1}, 1);
					intersection = (vec2){tmp, tmp};
					if (intersection.x > 0 && intersection.x < minIt) {
						minIt = intersection.x;
						n = (vec3){0, 0, -1};
						albedo = 0.5;

					}

					if (minIt < 99999) {
						diff *= (dot(n, light) * 0.5 + 0.5) * albedo;
						rd = reflect(rd, n);
					}
					else break;
				}
				int color = (int)(diff * 20);
				color = checki(color, 0, gradientSize);
				char pixel = gradient[color];
				screen[i + j * WIDTH] = pixel;
			}
		}
		WriteConsoleOutputCharacter(hConsole, screen, WIDTH * HEIGHT, (COORD){ 0, 0 }, &dwBytesWritten);
	}
	
	for(;;);
	return;
}