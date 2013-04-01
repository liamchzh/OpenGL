#include "GL/glut.h"
#include "GL/glu.h"
#include<math.h>

static double rotatex=0,rotatey=0,rotatez=0; 
static double movex=0,movey=0,movez=0;
static double zoomx=1.0,zoomy=1.0,zoomz=1.0;

char posix[6]={"+0.00"}, posiy[5]={"+0.00"};
char anglex[6]={"+0.00"},angley[6]={"+0.00"}, anglez[6]={"+0.00"};
//char zoom = "1";

void axis(double length)
{
	glPushMatrix();
	glBegin(GL_LINES);
		glVertex3d(0,0,0);
		glVertex3d(0,0,length);
	glEnd();
	glutWireCone(0.04,0.2,12,9);
	glPopMatrix();
}

void transform(char *arr, float n)
{
    int num;
    num = n * 100;
    if(n<0) 
    {
        arr[0] = '-';
        num = abs(num);
    }
    else
    {
        arr[0] = '+';
    }
    arr[1] = num/100 + '0';
    arr[2] = '.';
    arr[3] = (num%100)/10 + '0';
    arr[4] = (num%10);
    arr[5] = '\0';
}

void myInit(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0f,0.0f,0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,640.0,0.0,480.0);
}

void displayCude(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0*64/48.0,2.0*64/48.0,-2.0,2.0,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.0,2.0,2.0,0.7,0.7,0.0,0.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(0,0,1);
	glPushMatrix();

	glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(0,0,3);
        glVertex3d(0,0,0);
        glVertex3d(0,2,0);
        glVertex3d(0,0,0);
        glVertex3d(3,0,0);
    glEnd();

    transform(posix, movex);
    transform(posiy, movey);
    transform(anglex, rotatex);
    transform(angley, rotatey);
    transform(anglez, rotatez);

    int i = 0;
    glRasterPos2f(2,3);
    for(i=0; i<5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,posix[i]);
    }
    for(i=0; i<5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,posiy[i]);
    }

    glRasterPos2f(2,2.5);
    for(i=0; i<5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,anglex[i]);
    }
    for(i=0; i<5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,angley[i]);
    }
    for(i=0; i<5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,anglez[i]);
    }
    
    glTranslatef (movex,0.0, 0.0);
    glTranslatef (0.0, movey, 0.0);

	glRotatef (rotatez, 0.0, 0.0, 1.0);
    glRotatef (rotatex, 1.0, 0.0, 0.0);
    glRotatef (rotatey, 0.0, 1.0, 0.0);

	glScalef(zoomx,zoomy,zoomz);

    
	glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(0,0,1);
        glVertex3d(0,0,0);
        glVertex3d(0,1,0);
        glVertex3d(0,0,0);
        glVertex3d(1,0,0);
    glEnd();

	glutWireCube(0.5);//正八面体
    glutWireTetrahedron();//正四面体
	
    glPopMatrix(); 
	glFlush();


}

void specialKey(GLint key,GLint x,GLint y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		glPushMatrix(); 
		movey+=0.1;
		glPopMatrix();
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		glPushMatrix(); 
		movey+=-0.1;
		glPopMatrix();
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		glPushMatrix(); 
		movex+=-0.1;
		movey+=-0.03;
		glPopMatrix();	
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		glPushMatrix(); 
		movex+=0.1;
		movey+=0.03;
		glPopMatrix();
		glutPostRedisplay();
		break;
	}

}
void myKeyboard(unsigned char key,GLint x,GLint y)
{
	switch(key)
	{
	case 'w':
	glPushMatrix(); 
	movey+=0.1;
	glPopMatrix();
	glutPostRedisplay();
			break;
	case 'a':
		glPushMatrix(); 
		movex+=-0.1;
		movey+=-0.03;
		glPopMatrix();	
		glutPostRedisplay();
		break;
	case 'd':
		glPushMatrix(); 
		movex+=0.1;
		movey+=0.03;
		glPopMatrix();
		glutPostRedisplay();
		break;
	case 's':
		glPushMatrix(); 
		movey+=-0.1;
		glPopMatrix();
		glutPostRedisplay();
		break;
	case 'x':
		glPushMatrix(); 
		rotatex+=0.5;
		glutPostRedisplay();
		glPopMatrix();
		break;
	case 'y':
		glPushMatrix(); 
		rotatey+=0.5;
		glutPostRedisplay();
		glPopMatrix();
		break;
	case 'z':
		glPushMatrix(); 
		rotatez+=0.5;
		glutPostRedisplay();
		glPopMatrix();
		break;
	
	}

}

void myMouse(int button,int state,int x,int y)
{
	if(state==GLUT_DOWN)
	{
		if(button==GLUT_LEFT_BUTTON)
		{
			glPushMatrix();
			zoomx+=0.2;
			zoomy+=0.2;
			zoomz+=0.2;
			glPopMatrix();
			glutPostRedisplay();
		}
		else if(button==GLUT_RIGHT_BUTTON)
		{
			glPushMatrix();
			zoomx+=-0.2;
			zoomy+=-0.2;
			zoomz+=-0.2;
			glPopMatrix();
			glutPostRedisplay();
		}
	}

}


int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("鼠标左键放大 右键缩小");
	glutDisplayFunc(displayCude);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(specialKey);
	glutMouseFunc(myMouse);
	myInit();
	glViewport(0,0,640,480);
	glutMainLoop();
	return 0;
}
