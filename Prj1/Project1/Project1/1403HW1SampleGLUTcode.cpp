#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>

int MainWindowID, MainWindowWidth, MainWindowHeight;
int SubwindowID, SubwindowWidth, SubwindowHeight;
int width,sub_height,main_height; // ��ü �ʺ�, Console ����, ��ü ����

GLfloat x_rotate, y_rotate, z_rotate;
int leftbuttonpressed = 0; // ���콺 ���� ��ư
int smallsquarepressed = 0; // ���� �Ʒ� �𼭸� ������ ��
char *SubwindowString = ""; // FPS ǥ��
char keyboardString[32]; // Ű���� �Է¿� ���� Consolewindow ���ڿ� ǥ��
int stringCnt=0; // keyboardString�� ���� ���� ��
int frame = 100 , timer_value = 1000/frame; 
char buf1[20],rotation_flag=0; 

void initMainWindowOpenGLRenderingContext(void) {
	glClearColor(0.3, 0.5, 1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	x_rotate = y_rotate = z_rotate = 0.0;
}

void initSubwindowOpenGLRenderingContext(void) {
	glClearColor(1.0, 0.6, 0.2, 1.0);
}
void draw_WC_axis(GLfloat scale) {
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(scale, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, scale, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, scale);
	glEnd();
	glLineWidth(1.0);
}

void displayMain(void) {
	glutSetWindow(MainWindowID);
	glClear(GL_COLOR_BUFFER_BIT);

	draw_WC_axis(1.75);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(x_rotate, 1.0, 0.0, 0.0);
	glRotatef(y_rotate, 0.0, 1.0, 0.0);
	glRotatef(z_rotate, 0.0, 0.0, 1.0);

	glColor3f(0.3, 1.0, 1.0);
	glutWireTeapot(1.0);	
	glPopMatrix();
	glutSwapBuffers(); 
}

void displaySubwindow(void) {

	char *c;
	glClear(GL_COLOR_BUFFER_BIT);

	glRasterPos2i(0, 0);
	for (c = SubwindowString; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glutPostRedisplay();
	glutSwapBuffers();
}

void displayKeyboard(void) { // keyboard�� ���� ���ڸ� Consolewindow�� ����Ѵ�.

	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	glRasterPos2i(0, 0);
	for (i = 0; i<stringCnt; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, keyboardString[i]);
	}
	glutPostRedisplay();
	glutSwapBuffers();
}

void idleMain(int value) { // glutTimerFunc�� ���� �������� idleMain�� �����Ѵ�. 
	if ((x_rotate += 0.1) >= 360.0) 
		x_rotate -= 360.0;
	glutSetWindow(MainWindowID);
	glutPostRedisplay();
	if(rotation_flag == 0) //rotation_flag�� 0�̸� idleMain ������ ����, 1�̸� ���� ȣ������ �ʴ´�.
		glutTimerFunc(1000/frame,idleMain,0);
}

void keyboardMain(unsigned char key, int x, int y) {
	
	char buf[10];
	
	switch (key) {
	case 'm':
		rotation_flag =0; 
		frame = 30;
		glutTimerFunc(1000/frame,idleMain,0);
		
		sprintf(buf,"%d",frame);  // Consolewindow�� ���� FPS ���
		strcpy(buf1,"FPS : ");
		strcat(buf1,buf);
		SubwindowString =buf1;
		glutSetWindow(SubwindowID);
		glutDisplayFunc(displaySubwindow);
		break;
	case 's':
		rotation_flag=1;
		frame = 100;
		SubwindowString="";
		glutSetWindow(MainWindowID);
		initMainWindowOpenGLRenderingContext();
		glutPostRedisplay();
		glutIdleFunc(NULL);
		break;
	case 'x': 
		printf("Pressed X button\n ");
		exit(0);
	}
}

void SpecialKey(int key,int x, int y){

	char buf[10];
	

	switch(key){
	case GLUT_KEY_DOWN : /* FPS�� ������ */
		if((frame) <= 5 )
			break;
		if((frame/=2) < 5)
			frame = 5;

		glutTimerFunc(1000/frame,idleMain,0);

		sprintf(buf,"%d",frame); // FPS ���ڿ� ���
		strcpy(buf1,"FPS : ");
		strcat(buf1,buf);
		SubwindowString =buf1;
		glutSetWindow(SubwindowID);
		glutDisplayFunc(displaySubwindow);
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP : /* FPS�� �ø��� */
		if((frame)>=1000)
			break;
		if((frame*=2)>=1000)
			frame=1000;

		glutTimerFunc(1000/frame ,idleMain,0);

		sprintf(buf,"%d",frame); // FPS ���ڿ� ���
		strcpy(buf1,"FPS : ");
		strcat(buf1,buf);
		SubwindowString =buf1;
		glutSetWindow(SubwindowID);
		glutDisplayFunc(displaySubwindow); 
		glutPostRedisplay();
		break;
	default : 
		break;
	}
}




void keyboardSubwindow(unsigned char key, int x, int y) {
	switch(key) {
	case 'r':
		glutSetWindow(SubwindowID);
		glClearColor(1.0, 0.0, 0.0, 1.0);
		glutPostRedisplay();
		break;
	case 'g':
		glutSetWindow(SubwindowID);
		glClearColor(0.0, 1.0, 0.0, 1.0);
		glutPostRedisplay();
		break;
	case 'b':
		glutSetWindow(SubwindowID);
		glClearColor(0.0, 0.0, 1.0, 1.0);
		glutPostRedisplay();
		break;
	}
}

int prevx, prevy;



void mousepressMain(int button, int state, int x, int y) {

	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		/* Mainwindow���� ���� �Ʒ� 5%�κп� ���� ó��*/
		if(x<(width*1/20) && y>(main_height*19/20)){
			smallsquarepressed = 1;
			glutSetWindow(SubwindowID);
			glutShowWindow();
			glutPostRedisplay();
		}
		leftbuttonpressed = 1;
		prevx = x, prevy = y;
	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
		leftbuttonpressed = 0;
}

void mousepressSub(int button, int state, int x, int y){

	glutSetWindow(SubwindowID);

	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		/* Consolewindow���� ���� �Ʒ� 5%�κп� ���� ó��*/
		if(x<(width*1/20) && y>((main_height-sub_height)*3/4)){
			smallsquarepressed = 1;
			glutSetWindow(SubwindowID);
			glutHideWindow();
			glutPostRedisplay();
		}
	}
}
void menuOption_main(int value){

	if(value == 1){ 
		printf("Menu Selection Exit\n");
		exit(-1);
	}
	else if(value ==2){
		glutSetWindow(SubwindowID);
		glutShowWindow();
		glutPostRedisplay();
	}
	else if(value ==3){
		glutSetWindow(SubwindowID);
		glutHideWindow();
		glutPostRedisplay();
	}
}

void menuOption_sub(int value){

	if(value == 1){ 
		printf("Menu Selection Exit\n");
		exit(-1);
	}
}
void color_menu_main(int value){

	if(value == 1){
		glutSetWindow(MainWindowID);
		glClearColor(1.0,0.0,0.0,1.0);
		glutPostRedisplay();
	}
	else if(value == 2){
		glutSetWindow(MainWindowID);
		glClearColor(0.0,1.0,0.0,1.0);
		glutPostRedisplay();
	}
	else if(value == 3){
		glutSetWindow(MainWindowID);
		glClearColor(0.0,0.0,1.0,1.0);
		glutPostRedisplay();
	}
}

void color_menu_sub(int value){

	if(value == 1){
		glutSetWindow(SubwindowID);
		glClearColor(1.0,0.0,0.0,1.0);
		glutPostRedisplay();
	}
	else if(value == 2){
		glutSetWindow(SubwindowID);
		glClearColor(0.0,1.0,0.0,1.0);
		glutPostRedisplay();
	}
	else if(value == 3){
		glutSetWindow(SubwindowID);
		glClearColor(0.0,0.0,1.0,1.0);
		glutPostRedisplay();
	}
}
void buildMenu(){

	int c_menu_id_main,c_menu_id_sub;
	glutSetWindow(MainWindowID);
	c_menu_id_main = glutCreateMenu(color_menu_main);
	glutAddMenuEntry("Red",1);
	glutAddMenuEntry("Green",2);
	glutAddMenuEntry("Blue",3);

	glutCreateMenu(menuOption_main);
	glutAddMenuEntry("Quit",1);
	glutAddMenuEntry("Show Console Window",2);
	glutAddMenuEntry("Hide Console Window",3);
	glutAddSubMenu("Select Color",c_menu_id_main);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutSetWindow(SubwindowID);
	c_menu_id_sub = glutCreateMenu(color_menu_sub);
	glutAddMenuEntry("Red",1);
	glutAddMenuEntry("Green",2);
	glutAddMenuEntry("Blue",3);

	glutCreateMenu(menuOption_sub);
	glutAddMenuEntry("Quit",1);
	glutAddSubMenu("Select Color",c_menu_id_sub);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mousemoveMain(int x, int y) {
	int dely;

	if (leftbuttonpressed) {
		dely = x - prevx; prevx = x; // prevy ���� ���콺�� ���� y��, ���� y�� pressed ���·� ������ ���� y��.

		if ((y_rotate += (GLfloat) dely) >= 360.0) 
			y_rotate -= 360.0;
		glutSetWindow(MainWindowID);
		glutPostRedisplay();
	}
		
}

void keyboardSub(unsigned char key, int x, int y){ /* mouse�� Consolewindow�� �ְ�, Ű���忡 ���� �Է��� �������� ȣ�� */

	switch(key){

	case 8 :
		stringCnt--;
		break;
	case 10:
		stringCnt = 0;
		break;
	case 13:
		stringCnt = 0;
		break;
	default :
		if(stringCnt == 31){
			stringCnt = 0;
		}
		keyboardString[stringCnt++] = key;
		glutSetWindow(SubwindowID);
		glutDisplayFunc(displayKeyboard);
	}

}

void mousePassiveMove(int x, int y){

	glutSetWindow(SubwindowID);
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	glutKeyboardFunc(keyboardSub);

	glutPostRedisplay();
}


void reshapeMain(int x, int y) {
	glViewport(0, 0, x, y);

	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	gluPerspective(15.0,(GLdouble)x/(GLdouble)y, 0.1, 1000.0);

	glutSetWindow(SubwindowID);
	glutPositionWindow(0,y*4/5);
	glutReshapeWindow(x,y*1/5);
	width = x; sub_height=y*4/5; main_height = y;
	glutPostRedisplay();
}


void reshapeConsole(int x, int y) {
	glViewport(0, 0, x, y);
}

void initSystem(void) {
	MainWindowWidth = 640;
	MainWindowHeight = 480;
	SubwindowWidth = 640;
	SubwindowHeight = 96;
}


//int glutCreateMenu(void (*func)(int value));

int main (int argc, char **argv) {
	glutInit(&argc, argv);
	initSystem();

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);  
	glutInitWindowSize(MainWindowWidth, MainWindowHeight);

	MainWindowID = glutCreateWindow("�������б� CSE4170 ������ǻ�ͱ׷��Ƚ� HW1 - ������");
	glutDisplayFunc(displayMain);
	glutReshapeFunc(reshapeMain);
	glutMouseFunc(mousepressMain);
	glutMotionFunc(mousemoveMain);
	glutKeyboardFunc(keyboardMain);
	glutSpecialFunc(SpecialKey);
	initMainWindowOpenGLRenderingContext();

	SubwindowID = glutCreateSubWindow(MainWindowID, 0, MainWindowHeight*4/5, MainWindowWidth, MainWindowHeight*1/5);
	glutDisplayFunc(displaySubwindow); 
	glutMouseFunc(mousepressSub);
	//glutReshapeFunc(reshapeSubwindow);
	glutKeyboardFunc(keyboardSubwindow);
	initSubwindowOpenGLRenderingContext();
	//glutSetWindow(SubwindowID);
	glutPassiveMotionFunc(mousePassiveMove);

	buildMenu();
	glutMainLoop();
	return 0;
}
