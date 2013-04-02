#include "GL/glut.h"
#include "GL/glu.h"
#include<math.h>

static double rotatex=0,rotatey=0,rotatez=0; 
static double movex=0,movey=0,movez=0;
static double zoomx=1.0,zoomy=1.0,zoomz=1.0;

char posix[6]={"+0.00"}, posiy[6]={"+0.00"};
char anglex[6]={"000.0"},angley[6]={"000.0"}, anglez[6]={"000.0"};
char zx[4]={"0.0"}, zy[4]={"0.0"}, zz[4]={"0.0"};

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

//计算位置
void posi_trans(char *arr, float n)
{
    int num;
    num = n * 100;
    if(num<0) 
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
    arr[4] = (num%10) + '0';
}

//计算角度
void angle_trans(char *arr, float n)
{
    int num;
    num = n * 10;
    if(num > 3600)
    {
        num = num % 3600;
    }
    arr[0] = num/1000 + '0';
    arr[1] = (num%1000)/100 + '0';
    arr[2] = (num%100)/10 + '0';
    arr[3] = '.';
    arr[4] = num%10 + '0';
}

//计算缩放
void zoom_trans(char *arr, float n)
{
    int num;
    num = n * 10;
    if(num<0) 
    {
        num = abs(num);
    }

    arr[0] = (num/10) + '0';
    arr[2] = (num%10) + '0';

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

void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0*64/48.0,2.0*64/48.0,-2.0,2.0,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.0,2.0,2.0,0.7,0.7,0.0,0.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(0,0,0);
	glPushMatrix();
    
    //世界坐标系
	glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(0,0,3);
        glVertex3d(0,0,0);
        glVertex3d(0,2,0);
        glVertex3d(0,0,0);
        glVertex3d(3,0,0);
    glEnd();

    glRasterPos2f(3.0,0.0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'X');
    glRasterPos2f(0.0,2.0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'Y');
    glRasterPos2f(-2.0,-2.0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'Z');

    glutWireTetrahedron();//正四面体

    posi_trans(posix, movex);
    posi_trans(posiy, movey);
    angle_trans(anglex, rotatex);
    angle_trans(angley, rotatey);
    angle_trans(anglez, rotatez);
    zoom_trans(zx, zoomx);
    zoom_trans(zy, zoomy);
    zoom_trans(zz, zoomz);

    int i = 0;
    glRasterPos2f(1.5,2.8);
    char position[10] = {"Position:"};
    char rotate[8] = {"Rotate:"};
    char z[6] = {"Zoom:"};

    //显示坐标
    for(i = 0; i < 10; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,position[i]);
    }
    for(i=0; i<5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,posix[i]);
    }
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
    for(i=0; i<5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,posiy[i]);
    }
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'+');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'0');


    //显示旋转角度
    glRasterPos2f(1.5,2.5);
    for(i = 0; i < 8; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,rotate[i]);
    }
    for(i=0; i<5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,anglex[i]);
    }

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
    for(i=0; i<5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,angley[i]);
    }

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
    for(i=0; i<5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,anglez[i]);
    }
    
    //放大倍数
    glRasterPos2f(1.5,2.2);
    //显示'Zoom:'
    for(i = 0; i < 6; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,z[i]);
    }
    //显示具体参数
    for(i=0; i<4; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,zx[i]);
    }

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
    for(i=0; i<4; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,zy[i]);
    }

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
    for(i=0; i<4; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,zz[i]);
    }

    glTranslatef (movex,0.0, 0.0);
    glTranslatef (0.0, movey, 0.0);

	glRotatef (rotatez, 0.0, 0.0, 1.0);
    glRotatef (rotatex, 1.0, 0.0, 0.0);
    glRotatef (rotatey, 0.0, 1.0, 0.0);

	glScalef(zoomx,zoomy,zoomz);

    //显示物体坐标系
	glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(0,0,1);
        glVertex3d(0,0,0);
        glVertex3d(0,1,0);
        glVertex3d(0,0,0);
        glVertex3d(1,0,0);
    glEnd();

	glutWireCube(0.5);//正八面体
	
    glRasterPos2f(1.0,0.0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'x');
    glRasterPos2f(0.0,1.0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'y');

    glPopMatrix(); 
	glFlush();


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
    case 'i':
        glPushMatrix();
        zoomx+=0.2;
        zoomy+=0.2;
        zoomz+=0.2;
        glPopMatrix();
        glutPostRedisplay();
        break;
    case 'o':
        glPushMatrix();
        zoomx-=0.2;
        zoomy-=0.2;
        zoomz-=0.2;
        glPopMatrix();
        glutPostRedisplay();
        break;
	}

}
//使用鼠标放大缩小，改为使用键盘
/*
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
*/

int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("exp1");
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	//glutMouseFunc(myMouse);//使用鼠标放大缩小，改为使用键盘
	myInit();
	glViewport(0,0,640,480);
	glutMainLoop();
	return 0;
}
