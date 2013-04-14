#include <GL/glut.h>
#include <math.h>
#define PI 3.14159

/*声明物体*/
GLUquadricObj *quadObj1;
GLUquadricObj *quadObj2;
GLUquadricObj *quadObj3;
GLUquadricObj *quadObj4;
GLUquadricObj *quadObj5;
GLUquadricObj *quadObj6;
GLUquadricObj *quadObj7;
GLUquadricObj *quadObj8;

static float light_ambient[] = {0.1,0.1,0.1,1.0};
static float light_diffuse[] = {0.5,1.0,1.0,1.0};
static float light_position[] = {90.0,90.0,150.0,0.0};
static float front_mat_shininess[] = {60.0};
static float front_mat_specular[] = {0.2,0.2,0.2,1.0};
static float front_mat_diffuse[] = {0.5,0.5,0.28,1.0};
static float back_mat_shininess[] = {60.0};
static float back_mat_specular[] = {0.5,0.5,0.2,1.0};
static float back_mat_diffuse[] = {1.0,0.9,0.2,1.0};
static float Imodel_ambient[] = {1.0,1.0,1.0,1.0};
static float Imodel_twoside[] = {GL_TRUE};
static float Imodel_oneside[] = {GL_FALSE};

//标记当前图形
static int flag = 0;

void DrawCylinder1();
void DrawCylinder2(GLfloat lenth,GLfloat rad,int lon,GLfloat slipe);
void DrawCylinder3(GLfloat lenth,GLfloat rad,int lon,GLfloat slipe);
void DrawBall2();

void myInit(void)
{
/*设置背景色*/
glClearColor(1.0,1.0,1.0,1.0);

glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LEQUAL);

/*设置光照*/
glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
glLightfv(GL_LIGHT0,GL_POSITION,light_position);

/*设置材质*/
glMaterialfv(GL_FRONT,GL_DIFFUSE,front_mat_diffuse);
glMaterialfv(GL_FRONT,GL_SPECULAR,front_mat_specular);
glMaterialfv(GL_FRONT,GL_SHININESS,front_mat_shininess);

glMaterialfv(GL_BACK,GL_DIFFUSE,back_mat_diffuse);
glMaterialfv(GL_BACK,GL_SPECULAR,back_mat_specular);
glMaterialfv(GL_BACK,GL_SHININESS,back_mat_shininess);

/*设置光照模型参数*/
glLightModelfv(GL_LIGHT_MODEL_AMBIENT,Imodel_ambient);
glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE,Imodel_twoside);

/*激活关照*/
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glShadeModel(GL_SMOOTH); 
}

void myDisplay(void)
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

switch(flag)
{
	case 0:
		DrawCylinder1();
		break;
    case 1:
        DrawCylinder2(20,3,30,1);
        break;
    case 2:
        DrawCylinder3(50,20,30,3);
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
         break;
    case 6:
         break;
    case 7:
        DrawBall2();
        break;
}
glFlush();
}

void myReshape(int w,int h)
{
glViewport(0,0,(GLsizei)w,(GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45.0,(GLfloat)w/(GLfloat)h,1.0,50.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0.0,0.0,-25.0);
}

void myKeyboard(unsigned char key,GLint x,GLint y)
{
    switch(key)
    {
        case ' ': 
            flag = (flag+1) % 8;
            break;
    }
    glutPostRedisplay(); 
}

void DrawCylinder1()
{

/*绘制填充圆柱体*/
quadObj1 = gluNewQuadric();
glPushMatrix();
gluQuadricDrawStyle(quadObj1,GLU_FILL);
gluQuadricNormals(quadObj1,GL_FLAT);
gluQuadricOrientation(quadObj1,GLU_INSIDE);
gluQuadricTexture(quadObj1,GL_TRUE);

glColor3f(0.0,0.0,0.0);
glRotatef(30,1.0,0.0,0.0);
glRotatef(40,0.0,1.0,0.0);
gluCylinder(quadObj1,2.0,2.0,9.0,20.0,8.0);
glPopMatrix();

gluDeleteQuadric(quadObj1);

}

//用四边形边框模式绘制圆柱体
void DrawCylinder3(GLfloat lenth,GLfloat rad,int lon,GLfloat slipe)
{
	//lenth表示圆柱体长度,rad指半径，lon指圆周被切的块数，slipe指长度增量
	//glEnable(GL_CULL_FACE);		//打开背面裁剪，这样面片的背面不绘制
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);	//正面和背面都是用线框方式绘制。
	glColor3f(0,0.0,0);			//绘制颜色是用黑色
	glLineWidth(1);
	glBegin(GL_QUADS);

	//GLfloat anT  = atan(lenth/(2*rad));
	GLfloat sv   = 2*PI / lon;

	int i;
	GLfloat Ck,Cn,Ln,j,x,y,z;
	for(i = 0, Ck = 0; i < lon; i++)
	{
		Cn = Ck + sv;
		if(Cn >= 2 * PI)
			Cn = 0;
		for(j = -lenth/2; j <= lenth/2 - slipe; j += slipe )
		{
			Ln = j + slipe;

			//第一个点
			x = rad * cos(Ck);
			y = rad * sin(Ck);
			z = j;
			glVertex3f(x,y,z);

			//第二个点
			x = rad * cos(Cn);
			y = rad * sin(Cn);
			z = j;
			glVertex3f(x,y,z);

			//第三个点
			x = rad * cos(Cn);
			y = rad * sin(Cn);
			z = Ln;
			glVertex3f(x,y,z);

			//第四个点
			x = rad * cos(Ck);
			y = rad * sin(Ck);
			z = Ln;
			glVertex3f(x,y,z);
		}
		Ck += sv;
	}
	glEnd();
}

//用三角形边框模式绘制圆柱体
void DrawCylinder2(GLfloat lenth,GLfloat rad,int lon,GLfloat slipe)
{
	//glEnable(GL_CULL_FACE);		//打开背面裁剪，这样面片的背面不绘制
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);	//正面和背面都是用线框方式绘制。
	glColor3f(0,0,0);			//绘制颜色是用黑色
    //glTranslatef(5, 5, 0);
    glRotatef(30,1.0,0.0,0.0);
    glRotatef(40,0.0,1.0,0.0);
	glLineWidth(1);
	glBegin(GL_TRIANGLES);

	GLfloat sv   = 2*PI / lon;

	int i;
	GLfloat Ck,Cn,Ln,j,x,y,z;
	for(i = 0, Ck = 0; i < lon; i++)
	{
		Cn = Ck + sv;
		if(Cn >= 2 * PI)
			Cn = 0;
		for(j = -lenth/2; j <= lenth/2 - slipe; j += slipe )
		{
			Ln = j + slipe;

			//第一个点
			x = rad * cos(Ck);
			y = rad * sin(Ck);
			z = j;
			glVertex3f(x,y,z);

			//第二个点
			x = rad * cos(Cn);
			y = rad * sin(Cn);
			z = j;
			glVertex3f(x,y,z);

			//第三个点
			x = rad * cos(Cn);
			y = rad * sin(Cn);
			z = Ln;
			glVertex3f(x,y,z);

			//第一个点
			x = rad * cos(Cn);
			y = rad * sin(Cn);
			z = Ln;
			glVertex3f(x,y,z);

			//第二个点
			x = rad * cos(Ck);
			y = rad * sin(Ck);
			z = Ln;
			glVertex3f(x,y,z);

			//第三个点
			x = rad * cos(Ck);
			y = rad * sin(Ck);
			z = j;
			glVertex3f(x,y,z);

		}
		Ck += sv;
	}
	glEnd();
}



void DrawBall2()
{

/*绘制边框球体*/
quadObj8 = gluNewQuadric();
glPushMatrix();
gluQuadricDrawStyle(quadObj2,GLU_SILHOUETTE);
glTranslatef(-5.0,-1.0,0.0);
gluSphere(quadObj2,3.0,20.0,20.0);
glPopMatrix();

gluDeleteQuadric(quadObj2);
}



int main(int argc,char ** argv)
{
/*初始化*/
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(800,600);
glutInitWindowPosition(100,100);

/*创建窗口*/
glutCreateWindow(" DRAW QUADRIC OBJECTS ");
glutKeyboardFunc(myKeyboard);

/*绘制与显示*/
myInit();
glutReshapeFunc(myReshape);
glutDisplayFunc(myDisplay);

glutMainLoop();
return 0;
}
