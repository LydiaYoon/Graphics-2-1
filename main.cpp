#include <vgl.h>
#include <vec.h>
#include <InitShader.h>
#include "MyColorCylinder.h" 

MyColorCylinder cylinder;
int num = 10;
bool bRotate = false;
float time = 0.0;

void myInit()
{
	cylinder.GenerateNPolygon(num);
	cylinder.init();
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	cylinder.Draw();

	glutSwapBuffers();
}

void myIdle()
{
	if (bRotate == true)
		time += 0.01;
	cylinder.setTime(time);
	
	glutPostRedisplay();
	Sleep(16); // 초당 60번
}

void myKey(unsigned char key, int x, int y)
{
	if (key == VK_SPACE) // 스페이스바
	{
		if (bRotate == false)
			bRotate = true;
		else
			bRotate = false;
	}
	else if (key == '1')
	{
		if (num > 3)
			num--;
			printf("NumPolygon: %d, NumTriangle: %d, NumVertex: %d\n", cylinder.NumPolygon, cylinder.NumTriangle, cylinder.NumVertex);
	}
	else if (key == '2')
	{
		num++;
		printf("NumPolygon: %d, NumTriangle: %d, NumVertex: %d\n", cylinder.NumPolygon, cylinder.NumTriangle, cylinder.NumVertex);
	}
	else if (key == 'q' || key == 'Q')
		exit(0); // 종료
	else return;

	myInit();
	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Homework1");

	glewExperimental = true;
	glewInit();
	myInit();

	printf("A Rotating Color Cylinder\n");
	printf("Programming Assignment #1 for Computer Graphics 2\n");
	printf("Department of Digital Contents, Sejong University\n");
	printf("--------------------------------------------------\n");
	printf("Spacebar: starting/stoping rotation\n");
	printf("'1' key: Decreasing the Numver of Edges\n");
	printf("'2' key: Increasing the Numver of Edges\n");
	printf("'Q' key: Exit the program.\n");
	printf("--------------------------------------------------\n");
	printf("NumPolygon: %d, NumTriangle: %d, NumVertex: %d\n", cylinder.NumPolygon, cylinder.NumTriangle, cylinder.NumVertex);

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKey);
	glutMainLoop();

	return 0;
}