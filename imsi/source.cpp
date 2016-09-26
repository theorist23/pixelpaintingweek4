#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 1000;
const int height = 600;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	int i, j;
	if (i0 == i1)
	{
		for (j = j0;j <= j1;j++)
			drawPixel(i0, j, red, green, blue);
	}
	else
	{
		if (j0 == j1)
		{
			for (i = i0; i <= i1; i++)
				drawPixel(i, j0, red, green, blue);
		}
		else
		{
			for (i = i0; i <= i1; i++)
			{
				if (j0 < j1)
				{
					for (j = j0;j <= j1;j++)
					{
						if (i == (i1 - i0)*(j - j0) / (j1 - j0) + i0 || j == (j1 - j0)*(i - i0) / (i1 - i0) + j0)
							drawPixel(i, j, red, green, blue);
					}
				}
				else
				{
					for (j = j1;j <= j0;j++)
					{
						if (i == (i1 - i0)*(j - j0) / (j1 - j0) + i0 || j == (j1 - j0)*(i - i0) / (i1 - i0) + j0)
							drawPixel(i, j, red, green, blue);
					}
				}
			}
		}
	}
}

void drawThick(const int& i0, const int& j0, const int& i1, const int& j1, const int t, const float& red, const float& green, const float& blue)
{
	int i, j, k;
	if (i0 == i1)
	{
		for (j = j0;j <= j1;j++)
			for (k = i0 - t;k <= i0 + t;k++)
				drawPixel(k, j, red, green, blue);
	}
	else
	{
		if (j0 == j1)
		{
			for (i = i0; i <= i1; i++)
				for (k = j0 - t;k <= j0 + t;k++)
					drawPixel(i, k, red, green, blue);
		}
		else
		{
			for (i = i0; i <= i1; i++)
			{
				if (j0 < j1)
				{
					for (j = j0;j <= j1;j++)
					{
						if (i == (i1 - i0)*(j - j0) / (j1 - j0) + i0 || j == (j1 - j0)*(i - i0) / (i1 - i0) + j0)
						{
							for (k = -t;k <= t;k++)
							{
								drawPixel(i + k, j, red, green, blue);
								drawPixel(i, j + k, red, green, blue);
							}
						}
					}
				}
				else
				{
					for (j = j1;j <= j0;j++)
					{
						if (i == (i1 - i0)*(j - j0) / (j1 - j0) + i0 || j == (j1 - j0)*(i - i0) / (i1 - i0) + j0)
						{
							for (k = -t;k <= t;k++)
							{
								drawPixel(i + k, j, red, green, blue);
								drawPixel(i, j + k, red, green, blue);
							}
						}
					}
				}
			}
		}
	}
}
 
void drawRect(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	int i, j;
	for (i = i0;i <= i1;i++)
		drawPixel(i, j0, red, green, blue);
	for (i = i0;i <= i1;i++)
		drawPixel(i, j1, red, green, blue);
	for (j = j0;j <= j1;j++)
		drawPixel(i0, j, red, green, blue);
	for (j = j0;j <= j1;j++)
		drawPixel(i1, j, red, green, blue);
}

void drawRectF(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	int i, j;
	for (i = i0;i <= i1;i++)
	{
		for (j = j0;j <= j1;j++)
		{
			drawPixel(i, j, red, green, blue);
		}
	}
}

void drawCirc(const int& i0, const int& j0, const int& r, const int& t, const float& red, const float& green, const float& blue)
{
	int i, j;
	int a, b, c;

	for (i = i0 - r;i <= i0 + r;i++)
	{
		for (j = j0 - r;j <= j0 + r;j++)
		{
			a = ((i - i0)*(i - i0)) + ((j - j0)*(j - j0));
			b = r*r;
			c = (r - t)*(r - t);
			if (a < b&&a >= c)
			{
				drawPixel(i, j, red, green, blue);
			}
		}
	}
}

void drawIcon(const int& i0, const int& j0, const int& r, const int& t, const float& r1, const float& g1, const float& b1, const float& r2, const float& g2, const float& b2, GLFWwindow* window)
{
	int i, j;
	int a, b, c;
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	for (i = i0 - r;i <= i0 + r;i++)
	{
		for (j = j0 - r;j <= j0 + r;j++)
		{
			a = ((i - i0)*(i - i0)) + ((j - j0)*(j - j0));
			b = r*r;
			c = (r - t)*(r - t);
			if (a < b&&a >= c)
			{
				if (((xpos - i0)*(xpos - i0)) + (((height - 1 - ypos) - j0)*((height - 1 - ypos) - j0)) < b)
					drawPixel(i, j, r2, g2, b2);
				else
					drawPixel(i, j, r1, g1, b1);
			}
		}
	}
}

void drawOnPixelBuffer(GLFWwindow* window)
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

	//const int i = rand() % width, j = rand() % height;
	//drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	//for (int i = 0; i < width*height; i++)
	//{
	//	pixels[i * 3 + 0] = 1.0f; // red 
	//	pixels[i * 3 + 1] = 1.0f; // green
	//	pixels[i * 3 + 2] = 1.0f; // blue
	//}
	drawIcon(100, 150, 70, 3, 1, 0, 0, 0, 0, 1, window);
	drawLine(70, 150, 130, 150, 0, 0, 0);
	drawLine(110, 130, 130, 150, 0, 0, 0);
	drawLine(110, 170, 130, 150, 0, 0, 0);
	drawIcon(300, 150, 70, 3, 1, 0, 0, 0, 0, 1, window);
	drawLine(270, 120, 300, 180, 0, 0, 0);
	drawLine(300, 180, 330, 120, 0, 0, 0);
	drawLine(285, 150, 315, 150, 0, 0, 0);
	drawIcon(500, 150, 70, 3, 1, 0, 0, 0, 0, 1, window);
	drawLine(500, 120, 500, 180, 0, 0, 0);
	drawIcon(700, 150, 70, 3, 1, 0, 0, 0, 0, 1, window);
	drawLine(670, 150, 730, 150, 0, 0, 0);
	drawLine(670, 150, 690, 130, 0, 0, 0);
	drawLine(670, 150, 690, 170, 0, 0, 0);
	drawIcon(900, 150, 70, 3, 1, 0, 0, 0, 0, 1, window);
	drawLine(900, 120, 900, 180, 0, 0, 0);
	drawLine(880, 160, 900, 180, 0, 0, 0);
	drawLine(900, 180, 920, 160, 0, 0, 0);
	drawIcon(100, 450, 70, 3, 1, 0, 0, 0, 0, 1, window);
	drawThick(75, 400, 125, 500, 2, 0, 0, 0);
	drawIcon(300, 450, 70, 3, 1, 0, 0, 0, 0, 1, window);
	drawCirc(300, 450, 35, 6, 0, 0, 0);
	drawIcon(500, 450, 70, 3, 1, 0, 0, 0, 0, 1, window);
	drawRect(470, 420, 530, 480, 0, 0, 0);
	drawIcon(700, 450, 70, 3, 1, 0, 0, 0, 0, 1, window);
	drawLine(670, 420, 730, 480, 0, 0, 0);
	drawLine(670, 480, 730, 420, 0, 0, 0);
	drawIcon(900, 450, 70, 3, 1, 0, 0, 0, 0, 1, window);
	drawLine(900, 420, 900, 480, 0, 0, 0);
	drawLine(880, 440, 900, 420, 0, 0, 0);
	drawLine(900, 420, 920, 440, 0, 0, 0);

	//TODO: try moving object
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer(window);

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}