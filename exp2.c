#include <GL/glut.h>
#include <math.h>
#define PI 3.14159

GLUquadricObj *quadObj1;
GLUquadricObj *quadObj2;

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
void DrawCone1(GLfloat h,GLfloat rad, int lon, GLfloat  slipe);
void DrawCone2(GLfloat h,GLfloat rad, int lon, GLfloat  slipe);
void DrawCone3(GLfloat h,GLfloat rad, int lon, GLfloat  slipe);
void DrawBall1(GLfloat radius,int lon,int lat);
void DrawBall2();

setLight1()
{
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

/*激活光照*/
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glShadeModel(GL_SMOOTH); 

}

void myInit(void)
{
/*设置背景色*/
glClearColor(1.0,1.0,1.0,1.0);

glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LEQUAL);

}

void myDisplay(void)
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

//世界坐标系
glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(0,0,10);
    glVertex3d(0,0,0);
    glVertex3d(0,10,0);
    glVertex3d(0,0,0);
    glVertex3d(10,0,0);
glEnd();

glRasterPos2f(10.0,0.0);
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'X');
glRasterPos2f(0.0,10.0);
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'Y');
glRasterPos2f(-10.0,-10.0);
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'Z');

switch(flag)
{
	case 0:
		DrawCylinder1();
		break;
    case 1:
        DrawCylinder2(15,3,30,1);
        break;
    case 2:
        DrawCylinder3(15,3,30,1);
        break;
    case 3:
        DrawCone1(15,3,30,2);
        break;
    case 4:
        DrawCone2(15,3,30,2);
        break;
    case 5:
        DrawCone3(15,3,30,2);
        break;
    case 6:
        DrawBall1(2,20,20);
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
//绘制填充圆柱体
setLight1();
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


//用三角形边框模式绘制圆柱体
void DrawCylinder2(GLfloat lenth,GLfloat rad,int lon,GLfloat slipe)
{
    setLight1();

    glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(0,0,0);
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

			//point 1
			x = rad * cos(Ck);
			y = rad * sin(Ck);
			z = j;
			glVertex3f(x,y,z);

			//point 2
			x = rad * cos(Cn);
			y = rad * sin(Cn);
			z = j;
			glVertex3f(x,y,z);

			//point 3
			x = rad * cos(Cn);
			y = rad * sin(Cn);
			z = Ln;
			glVertex3f(x,y,z);

			//1
			x = rad * cos(Cn);
			y = rad * sin(Cn);
			z = Ln;
			glVertex3f(x,y,z);

			//2
			x = rad * cos(Ck);
			y = rad * sin(Ck);
			z = Ln;
			glVertex3f(x,y,z);

			//3
			x = rad * cos(Ck);
			y = rad * sin(Ck);
			z = j;
			glVertex3f(x,y,z);

		}
		Ck += sv;
	}
	glEnd();
    glPopMatrix();
}

//用四边形边框模式绘制圆柱体
void DrawCylinder3(GLfloat lenth,GLfloat rad,int lon,GLfloat slipe)
{
    setLight1();
    glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(0,0.0,0);
    glRotatef(30,1.0,0.0,0.0);
    glRotatef(40,0.0,1.0,0.0);
	glLineWidth(1);
	glBegin(GL_QUADS);

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

			//1
			x = rad * cos(Ck);
			y = rad * sin(Ck);
			z = j;
			glVertex3f(x,y,z);

			//2
			x = rad * cos(Cn);
			y = rad * sin(Cn);
			z = j;
			glVertex3f(x,y,z);

			//3
			x = rad * cos(Cn);
			y = rad * sin(Cn);
			z = Ln;
			glVertex3f(x,y,z);

			//4
			x = rad * cos(Ck);
			y = rad * sin(Ck);
			z = Ln;
			glVertex3f(x,y,z);
		}
		Ck += sv;
	}
	glEnd();
    glPopMatrix();
}

//用三角形填充模式绘制圆锥体
void DrawCone1(GLfloat h,GLfloat rad, int lon, GLfloat  slipe)
{
    setLight1();
    glPushMatrix();
	glPolygonMode(GL_FRONT,GL_FILL);
	glColor3f(0,0,0);
    glRotatef(150,1.0,0.0,0.0);
    glRotatef(40,0.0,1.0,0.0);
	glLineWidth(1);
	glBegin(GL_TRIANGLES);

	GLfloat angle = atan(rad/h);
	GLfloat sv   = 2*PI / lon;

	int i;
	GLfloat Ck,Cn,j,Rk,Rn,x,y,z;
	for(i = 0, Ck = 0; i < lon; i++)
	{
		Cn = Ck + sv;
		if(Cn >= 2 * PI)
			Cn = 0;
		for(j = 0; j <= h - slipe; j += slipe )
		{
			Rk = (h-j)*tan(angle);
			Rn =(h- j - slipe)*tan(angle);

			//1
			x = Rk* cos(Ck);
			y = Rk* sin(Ck);
			z = j;
			glVertex3f(x,y,z);

			//2
			x = Rk * cos(Cn);
			y = Rk * sin(Cn);
			z = j;
			glVertex3f(x,y,z);

			//3
			x = Rn * cos(Cn);
			y = Rn * sin(Cn);
			z = j + slipe;
			glVertex3f(x,y,z);

			//1
			x = Rn * cos(Cn);
			y = Rn * sin(Cn);
			z = j + slipe;
			glVertex3f(x,y,z);

			//2
			x = Rn * cos(Ck);
			y = Rn * sin(Ck);
			z = j + slipe;
			glVertex3f(x,y,z);

			//3
			x = Rk* cos(Ck);
			y = Rk* sin(Ck);
			z = j;
			glVertex3f(x,y,z);
		}
		Ck += sv;
	}
	glEnd();
    glPopMatrix();

}
//用三角形边框模式绘制圆锥体
void DrawCone2(GLfloat h,GLfloat rad, int lon, GLfloat  slipe)
{
    setLight1();
    glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(0,0,0);
    glRotatef(150,1.0,0.0,0.0);
    glRotatef(40,0.0,1.0,0.0);
	glLineWidth(1);
	glBegin(GL_TRIANGLES);

	GLfloat angle = atan(rad/h);
	GLfloat sv   = 2*PI / lon;

	int i;
	GLfloat Ck,Cn,j,Rk,Rn,x,y,z;
	for(i = 0, Ck = 0; i < lon; i++)
	{
		Cn = Ck + sv;
		if(Cn >= 2 * PI)
			Cn = 0;
		for(j = 0; j <= h - slipe; j += slipe )
		{
			Rk = (h-j)*tan(angle);
			Rn =(h- j - slipe)*tan(angle);

			//1
			x = Rk* cos(Ck);
			y = Rk* sin(Ck);
			z = j;
			glVertex3f(x,y,z);

			//2
			x = Rk * cos(Cn);
			y = Rk * sin(Cn);
			z = j;
			glVertex3f(x,y,z);

			//3
			x = Rn * cos(Cn);
			y = Rn * sin(Cn);
			z = j + slipe;
			glVertex3f(x,y,z);

			//1
			x = Rn * cos(Cn);
			y = Rn * sin(Cn);
			z = j + slipe;
			glVertex3f(x,y,z);

			//2
			x = Rn * cos(Ck);
			y = Rn * sin(Ck);
			z = j + slipe;
			glVertex3f(x,y,z);

			//3
			x = Rk* cos(Ck);
			y = Rk* sin(Ck);
			z = j;
			glVertex3f(x,y,z);
		}
		Ck += sv;
	}
	glEnd();
    glPopMatrix();

}
//用四边形边框模式绘制圆锥体
void DrawCone3(GLfloat h,GLfloat rad, int lon, GLfloat  slipe)
{
    setLight1();
    glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(0,0.0,0);
    glRotatef(150,1.0,0.0,0.0);
    glRotatef(40,0.0,1.0,0.0);
	glLineWidth(1);
	glBegin(GL_QUADS);

	//首先求出圆锥角
	GLfloat angle = atan(rad/h);
	GLfloat sv   = 2*PI / lon;

	int i;
	GLfloat Ck,Cn,j,Rk,Rn,x,y,z;
	for(i = 0, Ck = 0; i < lon; i++)
	{
		Cn = Ck + sv;
		if(Cn >= 2 * PI)
			Cn = 0;
		for(j = 0; j <= h - slipe; j += slipe )
		{
			Rk = (h-j)*tan(angle);
			Rn =(h- j - slipe)*tan(angle);

			//1
			x = Rk* cos(Ck);
			y = Rk* sin(Ck);
			z = j;
			glVertex3f(x,y,z);

			//2
			x = Rk * cos(Cn);
			y = Rk * sin(Cn);
			z = j;
			glVertex3f(x,y,z);

			//3
			x = Rn * cos(Cn);
			y = Rn * sin(Cn);
			z = j + slipe;
			glVertex3f(x,y,z);

			//4
			x = Rn * cos(Ck);
			y = Rn * sin(Ck);
			z = j + slipe;
			glVertex3f(x,y,z);
		}
		Ck += sv;
	}
	glEnd();
    glPopMatrix();
}

GLfloat seta = 0;
void SetLight2()
{
	GLfloat amb[4]={0.2,0.2,0.2,1};
	GLfloat dif[4]={1,1,1,1};
	GLfloat spe[4]={0.2,0.2,0.2,1};
	GLfloat pos[4]={2,0,0,1};
	glPushMatrix();
	glRotatef(seta,1,1,1);
	glTranslatef(pos[0],pos[1],pos[2]);
	glColor3f(1,0,0);
	glutSolidSphere(0.05,10,10);
	
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);
	glLightfv(GL_LIGHT0,GL_SPECULAR,spe);
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void CalculateNormal(GLfloat v1[],GLfloat v2[],GLfloat v3[],GLfloat normal[])
{
	GLfloat dirv2_v1[3],dirv2_v3[3];
    int i;
	for(i=0;i<3;i++)
	{
		dirv2_v1[i]=v1[i]-v2[i];
		dirv2_v3[i]=v3[i]-v2[i];
	}
	//叉乘计算法线方向
	normal[0]=dirv2_v1[1]*dirv2_v3[2]-dirv2_v1[2]*dirv2_v3[1];
	normal[1]=dirv2_v1[2]*dirv2_v3[0]-dirv2_v1[0]*dirv2_v3[2];
	normal[2]=dirv2_v1[0]*dirv2_v3[1]-dirv2_v1[1]*dirv2_v3[0];
}
void normalize(GLfloat *v)
{
	GLfloat dis = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	if(dis>0)
	{
		v[0]/=dis;
		v[1]/=dis;
		v[2]/=dis;
	}
}

//使用三角形绘制，填充绘制，使用光照，计算面片法线
void DrawBall1(GLfloat radius,int lon,int lat)
{
    SetLight2();		//设置光源	
    glPushMatrix();
	//设置材质属性
	GLfloat amb[4]={0.4,0.4,0.4,1};
	GLfloat dif[4]={1,1,1,1};
	GLfloat spe[4]={0.1,0.1,0.1,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);		//设置环境光材质属性，背面和正面使用相同的设置
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,dif);		//设置散射光材质属性，背面和正面使用相同的设置
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spe);	//设置镜面反射光材质属性，背面和正面使用相同的设置
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);			//正面用填充方式绘制。
	glBegin(GL_TRIANGLES);

	GLfloat lonCur,lonNext,lonStep=2*PI/lon,latCur,latNext,latStep=PI/lat;
	GLfloat v1[3],v2[3],v3[3],v4[3],normal[3];
	int i,j;
	for(lonCur=0,i=0;i<lon;lonCur+=lonStep,i++)	//经度
	{
		lonNext = lonCur+lonStep;
		if(i==lon-1) lonNext=0;	//边界约束，经度要转360°连接
		for(latCur=-PI/2,j=0;j<lat;latCur+=latStep,j++)	//维度
		{
			latNext = latCur+latStep;
			if(j==lat-1) latNext=PI/2;	//边界约束，维度约束到90°
			
			//第一个点
			v1[2]=radius*cos(latCur)*sin(lonCur);
			v1[0]=radius*cos(latCur)*cos(lonCur);
			v1[1]=radius*sin(latCur);

			//第二个点
			v2[2]=radius*cos(latCur)*sin(lonNext);
			v2[0]=radius*cos(latCur)*cos(lonNext);
			v2[1]=radius*sin(latCur);

			//第三个点
			v3[2]=radius*cos(latNext)*sin(lonNext);
			v3[0]=radius*cos(latNext)*cos(lonNext);
			v3[1]=radius*sin(latNext);

			//第四个点
			v4[2]=radius*cos(latNext)*sin(lonCur);
			v4[0]=radius*cos(latNext)*cos(lonCur);
			v4[1]=radius*sin(latNext);
			
			//第一个三角形
			CalculateNormal(v1,v2,v3,normal);
			normalize(normal);
			glNormal3fv(normal);
			glVertex3fv(v1);
			glVertex3fv(v2);
			glVertex3fv(v3);
			//第二个三角形
			CalculateNormal(v3,v4,v1,normal);
			normalize(normal);
			glNormal3fv(normal);
			glVertex3fv(v3);
			glVertex3fv(v4);
			glVertex3fv(v1);
		}
	}
	glEnd();
	glDisable(GL_LIGHTING);
    glPopMatrix();
}

void DrawBall2()
{
/*绘制边框球体*/
setLight1();
quadObj2 = gluNewQuadric();
glPushMatrix();
gluQuadricDrawStyle(quadObj2,GLU_SILHOUETTE);
glTranslatef(0.0,0.0,0.0);
glRotatef(90, 1.0, 0.0, 0.0);
gluSphere(quadObj2,3.0,20.0,20.0);
glPopMatrix();

gluDeleteQuadric(quadObj2);
}



int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);

    glutCreateWindow("exp2");
    glutKeyboardFunc(myKeyboard);

    myInit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);

    glutMainLoop();
    return 0;
}
