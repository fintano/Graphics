// 
// CSE3170 Introduction to Computer Graphics HW2 Sample Code V0.5
// Dept. of Computer Sci. & Eng.
// Sogang University
// (C) 2014 Sogang Univeristy CSE3170
//
// These codes are provided just for your convenience, and need lots of improvements!!!
//

#include "1403CSE3170HW2.h"
#define PI 3.141592

 SC sc; // Could extend this program to have multiple system contexts simultaneously.

 GLfloat lig_full_pos[] = {0.0, 0.0, 50.0, 1.0};
//GLfloat lig_lamp_spot_dir;
GLfloat lig_full_amb[] = {0.8, 0.7, 0.6, 1.0};
GLfloat lig_full_diff[] = {0.99, 0.85, 0.8, 1.0};
GLfloat lig_full_spec[] = {0.99, 0.85, 0.8, 1.0};


GLfloat lig_lamp_pos[] = {0.0, 0.0, 80.0, 1.0};
//GLfloat lig_lamp_spot_dir;
GLfloat lig_lamp_amb[] = {0.8, 0.7, 0.6, 1.0};
GLfloat lig_lamp_diff[] = {0.99, 0.85, 0.8, 1.0};
GLfloat lig_lamp_spec[] = {0.99, 0.85, 0.8, 1.0};

GLfloat lig_rotate_cow_pos[] = {0.0, 0.0, 80.0, 1.0};
//GLfloat lig_lamp_spot_dir;
GLfloat lig_rotate_cow_amb[] = {0.8, 0.7, 0.6, 1.0};
GLfloat lig_rotate_cow_diff[] = {0.99, 0.85, 0.8, 1.0};
GLfloat lig_rotate_cow_spec[] = {0.99, 0.85, 0.8, 1.0};


GLfloat lig_head_pos[] = {0.0, 1.0, 0.0, 1.0};
GLfloat lig_head_spot_dir[] = {0.0, 0, -5, 0.0};
GLfloat lig_head_amb[] = {0.0, 0.7, 0.6, 1.0};
GLfloat lig_head_diff[] = {0.0, 0.85, 0.8, 1.0};
GLfloat lig_head_spec[] = {0.0, 0.85, 0.8, 1.0};

GLfloat mat_ruby_amb[] = {0.1745, 0.01175, 0.01175};
GLfloat mat_ruby_diff[] = {0.61424, 0.04136, 0.04136};
GLfloat mat_ruby_spec[] = {0.727811, 0.626959, 0.626959};
GLfloat mat_ruby_exp = 76.8;

GLfloat mat_perl_amb[] = {0.25, 0.20725, 0.20725};
GLfloat mat_perl_diff[] = {1, 0.829, 0.829};
GLfloat mat_perl_spec[] = {0.296648, 0.296648, 0.296648};
GLfloat mat_perl_exp = 11.3;

GLfloat lig_cow_pos[] = {0.4, 0.25, 0.0, 1.0};
GLfloat lig_cow_spot_dir[] = {-1.0, 0.0, 0.0, 0.0};
GLfloat lig_cow_amb[] = {0.7, 0.0, 0.0, 1.0};
GLfloat lig_cow_diff[] = {0.8, 0.0, 0.0, 1.0};
GLfloat lig_cow_spec[] = {0.8, 0.0, 0.0, 1.0};

GLfloat mat_gold_amb[] = {0.24725, 0.1995, 0.0745};
GLfloat mat_gold_diff[] = {0.75164, 0.60648, 0.22648};
GLfloat mat_gold_spec[] = {0.628281, 0.555802, 0.366065};
GLfloat mat_gold_exp = 51.2;

GLfloat mat_silver_amb[] = {0.19225, 0.19225, 0.19225};
GLfloat mat_silver_diff[] = {0.50754, 0.50754, 0.50754};
GLfloat mat_silver_spec[] = {0.508274, 0.508274, 0.508274};
GLfloat mat_silver_exp = 51.2;

GLfloat mat_pewter_amb[] = {0.10588, 0.058824, 0.113725};
GLfloat mat_pewter_diff[] = {0.427451, 0.470588, 0.541176};
GLfloat mat_pewter_spec[] = {0.3333, 0.3333, 0.521569};
GLfloat mat_pewter_exp = 9.8;

GLfloat mat_eme_amb[] = {0.0215, 0.1745, 0.0215};
GLfloat mat_eme_diff[] = {0.07568, 0.61424, 0.07568};
GLfloat mat_eme_spec[] = {0.633, 0.727811, 0.633};
GLfloat mat_eme_exp = 76.8;




void initializeTeapot(void) { // 어떤 역할?
	sc.tp_vel[0] = -15.0; sc.tp_vel[1] = 15.0; sc.tp_vel[2] = 40.0;
	sc.tp_pos[0] = 70.0; sc.tp_pos[1] = -70.0; sc.tp_pos[2] = 5.0;
	sc.angle_Teapot = 0;
}

void initializeDinner(void) { // 어떤 역할?
	sc.dn_vel[0] = -15.0; sc.dn_vel[1] = 15.0; sc.dn_vel[2] = 40.0;
	sc.dn_pos[0] = 0.0; sc.dn_pos[1] = 0.0; sc.dn_pos[2] = 30.0;
}

void initializeSystemContext(void) {
	sc.MainWindowWidth = INIT_WINDOW_WIDTH;
	sc.MainWindowHeight = INIT_WINDOW_HEIGHT;

	sc.SubWindowWidth = sc.MainWindowWidth * (2/5);
	sc.SubWindowHeight = sc.MainWindowHeight * (2/5);

	sc.TigerMoveMode = 0, sc.CowMoveMode = 0, sc.TeapotMoveMode = 0, sc.AfterOneBounce = 0, sc.FillMode = 1;	
	sc.angle_Cow = 0, sc.angle_Teapot = 0,sc.angle_Dinner = 0;
	sc.CameraZoomModeMain = 0, sc.CameraGlobalRotationMode = 0, sc.CameraZoomModeSub = 0;
	sc.leftbuttonpressed = 0, sc.rightbuttonpressed = 0;
	sc.TigerCameraMode = 1; sc.CameraMode = 0;

	read_animobjects("data/Tiger/animtiger.txt", &sc.anim_tiger);
	read_object("data/cow2.txt", &sc.Cow);
	read_object("data/chair0000.txt",&sc.chair);
	read_object("data/new_chair.txt",&sc.chair2);
	read_object("data/clock.txt",&sc.clock);
	read_object("data/Jar.txt",&sc.jar);
	read_object("data/Building1.txt",&sc.building);
	read_object("data/Table.txt",&sc.table);
	read_object("data/Box.txt",&sc.box);
	read_texture_PPM("data/forest1.ppm", &sc.forest1);
	read_texture_PPM("data/forest2.ppm", &sc.forest2);
	read_texture_PPM("data/tiger_tex.P6.ppm",&sc.Tiger_tex);
	initializeTeapot();
}


void displayMain(void) {

	int i;

	glutSetWindow(sc.MainWindowID);
	//glEnable(GL_DEPTH);
	//glEnable(GL_FILL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();

	 // We are in EC here.
	glLightfv(GL_LIGHT5, GL_POSITION, lig_head_pos); // Head light in your head.
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, lig_head_spot_dir);


	glMultMatrixf(sc.camera[MAIN].mat);
	glTranslatef(-sc.camera[MAIN].pos[X], -sc.camera[MAIN].pos[Y], -sc.camera[MAIN].pos[Z]);

	// before viewingT

	set_Light1();
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
  	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 15.0);

	glLightfv(GL_LIGHT3, GL_POSITION,lig_full_pos);
	for(i=0;i<8;i++){
		if(i%2 == 0)
			set_Rotate_Light(i);
	}
	//glLightfv

	drawModel();

	glutSetWindow(sc.MainWindowID);
	glutPostRedisplay();
}

void set_Rotate_Light(int i){

	double temp = (i*45)+((float)sc.angle_Cow);

	sc.lig_rotate_cow_spot_dir[i/2][0] = cosf(temp * PI / 180.0);
	sc.lig_rotate_cow_spot_dir[i/2][1] = sinf(temp * PI /180.0 );

	glLightfv(0x4000+i, GL_POSITION, lig_rotate_cow_pos);
	glLightfv(0x4000+i, GL_SPOT_DIRECTION, sc.lig_rotate_cow_spot_dir[i/2]);
}

void set_Light1(void){

	sc.lig_lamp_spot_dir[0] = sc.anim_tiger.TigerX/80;
	sc.lig_lamp_spot_dir[1] = sc.anim_tiger.TigerY/80;
	
	glLightfv(GL_LIGHT1, GL_POSITION, lig_lamp_pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, sc.lig_lamp_spot_dir);
}

void displaySub(void){

	int i;

	glEnable(GL_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();

	glLightfv(GL_LIGHT5, GL_POSITION, lig_head_pos); // Head light in your head.
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, lig_head_spot_dir);

	glMultMatrixf(sc.camera[SUB].mat);
	glTranslatef(-sc.camera[SUB].pos[X], -sc.camera[SUB].pos[Y], -sc.camera[SUB].pos[Z]);
	
	set_Light1();
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
  	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 15.0);

	glLightfv(GL_LIGHT3, GL_POSITION,lig_full_pos);
	for(i=0;i<8;i++){
		if(i%2 == 0)
			set_Rotate_Light(i);
	}

	drawModel();
	
	glutSetWindow(sc.SubWindowID);
	glutPostRedisplay();
}

void displayTiger(void){

	glFrontFace(GL_CCW); /* which direction for front face? */
 	glCullFace(GL_BACK); /* which one to cull? */
 	glEnable(GL_CULL_FACE); /* Cull faces */
	glEnable(GL_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); 
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT3);

	glLoadIdentity();
	glRotatef(180.0,0.0,0.0,1.0);
	glRotatef(90.0,1.0,0.0,0.0);
	glTranslatef(0.0,88.0,-62.0);
	glRotatef(-sc.anim_tiger.Rotate,0.0,0.0,1.0);
	glMultMatrixf( (const float*) &(sc.anim_tiger.objects[sc.anim_tiger.count].xform[0].matrix_inv));
	glTranslatef(-sc.anim_tiger.TigerX,-sc.anim_tiger.TigerY,0.0);

	drawModel();

	glutSetWindow(sc.TigerWindowID);
	glutPostRedisplay();
}

void drawModel(void){
	// Now, we want to perform modeling transformations.
	
	int i;

	float text_x, text_y;
	
	glPushMatrix();
	glScalef(12,12,12);
	draw_planes_WC(sc.tex_name[0]);
	glPopMatrix();
	
	/*
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ruby_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_ruby_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_ruby_spec);
	glMaterialf (GL_FRONT, GL_SHININESS, mat_ruby_exp);
	
	glBindTexture(GL_TEXTURE_2D, sc.tex_name[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);

	glScalef(15,15,15);

	glNormal3f(0.0,1.0,0.0);
	glBegin(GL_TRIANGLES);
		glVertex3f(-5,-5,1); glTexCoord2f(0.0,0.0); 
		glVertex3f(-5,-5,7); glTexCoord2f(1.0,0.0);
		glVertex3f(5,-5,1);	 glTexCoord2f(0.0,1.0);
		glVertex3f(-5,-5,7); glTexCoord2f(1.0,0.0);
		glVertex3f( 5,-5,1); glTexCoord2f(0.0,1.0);
		glVertex3f(5,-5,7);	 glTexCoord2f(1.0,1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	*/

	glPushMatrix();
	//glTranslatef(-2.5, 0.0, 0.0);
	glScalef(80,80,80);

	glBindTexture(GL_TEXTURE_2D, sc.tex_name[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);

	glTranslatef(-1.2,0.0,1.0);

	glBegin(GL_TRIANGLES);
	  glNormal3f(1.0, 0.0, 0.0);
	  glTexCoord2f(0.0, 1.0);
	  glVertex3f(0.0, 1.0, -1.0);
	  glTexCoord2f(0.0, 0.0);
	  glVertex3f(0.0, 1.0, 1.0);
	  glTexCoord2f(1.0, 0.0);
	  glVertex3f(0.0, -1.0, 1.0);

	  glTexCoord2f(0.0, 1.0);
	  glVertex3f(0.0, 1.0, -1.0);
	  glTexCoord2f(1.0, 0.0);
	  glVertex3f(0.0, -1.0, 1.0);
	  glTexCoord2f(1.0, 1.0);
	  glVertex3f(0.0, -1.0, -1.0);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(-2.5, 0.0, 0.0);
	glScalef(80,80,80);

	glBindTexture(GL_TEXTURE_2D, sc.tex_name[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);

	glTranslatef(0.0,-1.2,1.0);
	glRotatef(90,0.0,0.0,1.0);

	glBegin(GL_TRIANGLES);
	  glNormal3f(0.0, 1.0, 0.0);
	  glTexCoord2f(0.0, 1.0);
	  glVertex3f(0.0, 1.0, -1.0);
	  glTexCoord2f(0.0, 0.0);
	  glVertex3f(0.0, 1.0, 1.0);
	  glTexCoord2f(1.0, 0.0);
	  glVertex3f(0.0, -1.0, 1.0);

	  glTexCoord2f(0.0, 1.0);
	  glVertex3f(0.0, 1.0, -1.0);
	  glTexCoord2f(1.0, 0.0);
	  glVertex3f(0.0, -1.0, 1.0);
	  glTexCoord2f(1.0, 1.0);
	  glVertex3f(0.0, -1.0, -1.0);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	/*
	glPushMatrix();
	glTranslatef(-125.0, -125.0, 0.0);
	glColor3ub(52,128, 23);
	if (!sc.FillMode) 
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawSquare(250.0, 10);
	if (!sc.FillMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3ub(37, 65, 23);
	if (sc.FillMode) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawSquare(250.0, 10);
	glPopMatrix();
	*/

	drawAxes(30.0); // Draw WC axes.

	

	for(i = 0 ; i< 8 ; i++){
		glPushMatrix();
		//glRotatef((float) sc.angle_Cow, 0.0, 0.0, 1.0);
		glRotatef(i * 45.0 + (float) sc.angle_Cow, 0.0, 0.0, 1.0);
		glTranslatef(0.0, -80.0, 15.0);	
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glScalef(50.0, 50.0, 50.0);
		glColor3ub(195, 188, 223);		
		
		if(!i){ 
		text_x = 80 * cos(i*45+(float)sc.angle_Cow); text_y = 80 * sin(i*45 + (float)sc.angle_Cow); 
		}

		armor_cow();
		glPopMatrix();
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sc.tex_name[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  	drawTiger(&sc.anim_tiger); // Draw moving Tiger
	glDisable(GL_TEXTURE_2D);
	
	glPushMatrix();
	glTranslatef(sc.tp_pos[0], sc.tp_pos[1], sc.tp_pos[2]);
	glRotatef((float) sc.angle_Teapot, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	drawAxes(12.0);
	glColor3ub(195, 253, 184);
	glutSolidTeapot(7.5); // Draw a teapot using a GLUT function.
	//drawObject
	glPopMatrix();

	glPushMatrix();
	glRotatef((float)sc.angle_Dinner,0.0,0.0,1.0);
	glTranslatef(0.0,0.0,sc.dn_pos[2]);
	glScalef(2.0,2.0,2.0);
	draw_table_setting(); // Draw Dinner of Cow 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,0.0,50.0);
	glPopMatrix();

	glutSwapBuffers(); 
}

void armor_cow(void){

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_gold_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_gold_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_gold_spec);
	glMaterialf (GL_FRONT, GL_SHININESS, mat_gold_exp);

	glLightfv(GL_LIGHT7, GL_POSITION, lig_cow_pos); // Laserlight from the big cow's forehead.
	glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, lig_cow_spot_dir);

	drawObject(&sc.Cow); // Draw a rotating cow.
	
	int i;

	for(i=0;i<8;i++){
		glPushMatrix();
		glRotatef((float) sc.angle_Cow, 1.0, 0.0, 0.0);
		glRotatef((float)i*45.0,1,0,0);
		glTranslated(0.0,0.0,0.3);
		glScalef(0.05,0.05,0.05);
		glColor3f(0.3,0.64,0.72);
		
		glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ruby_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_ruby_diff);
		glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_ruby_spec);
		glMaterialf (GL_FRONT, GL_SHININESS, mat_ruby_exp);

		drawObject(&sc.jar);
		glPopMatrix();
	}

	for(i=0;i<8;i++){
		glPushMatrix();
		glRotatef((float) sc.angle_Cow, 1.0, 0.0, 0.0);
		glRotatef((float)i*45.0,1,0,0);
		glTranslated(0.15,0.0,0.3);
		glScalef(0.05,0.05,0.05);
		glColor3f(0.7,0.34,0.32);
			
		glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_perl_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_perl_diff);
		glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_perl_spec);
		glMaterialf (GL_FRONT, GL_SHININESS, mat_perl_exp);
		
		drawObject(&sc.jar);
		glPopMatrix();
	}
	
	for(i=0;i<8;i++){
		glPushMatrix();
		glRotatef((float) sc.angle_Cow, 1.0, 0.0, 0.0);
		glRotatef((float)i*45.0,1,0,0);
		glTranslated(-0.15,0.0,0.3);
		glScalef(0.05,0.05,0.05);
		glColor3f(0.7,0.34,0.72);
		
		glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_eme_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_eme_diff);
		glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_eme_spec);
		glMaterialf (GL_FRONT, GL_SHININESS, mat_eme_exp);
		
		drawObject(&sc.jar);
		glPopMatrix();
	}
	
}

void draw_table_setting(void){

	drawObject(&sc.table);
	glPushMatrix();
		glTranslated(0.0,20.0,18.0);
		glColor3f(0.7,0.3,0.46);
		draw_chair_and_cow();
	glPopMatrix();

	glPushMatrix();
		glTranslated(0.0,-20.0,18.0);
		glRotatef(180.0,0.0,0.0,1.0);
		glColor3f(0.7,0.3,0.46);
		draw_chair_and_cow();
	glPopMatrix();

	glPushMatrix();
		glTranslated(20.0,0.0,18.0);
		glRotatef(-90.0,0.0,0.0,1.0);
		glColor3f(0.7,0.3,0.46);
		draw_chair_and_cow();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-20.0,0.0,18.0);
		glRotatef(90.0,0.0,0.0,1.0);
		glColor3f(0.7,0.3,0.46);
		draw_chair_and_cow();;
	glPopMatrix();
}

void draw_chair_and_cow(void){

	drawObject(&sc.chair);
	glPushMatrix();
		glTranslated(0.0,-6.0,2.0);
		glScalef(20.0,20.0,20.0);
		glRotatef(-90,0.0,1.0,0.0);
		glColor3f(0.35,0.4,0.7);
		draw_box();
	glPopMatrix();
}

void draw_box(void){

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_eme_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_eme_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_eme_spec);
	glMaterialf (GL_FRONT, GL_SHININESS, mat_eme_exp);

	drawObject(&sc.Cow);
	glPushMatrix();
		glRotatef(2*sc.angle_Dinner,0.0,0.0,1.0);
		glTranslatef(0.0,1.0,0.0);
		glScalef(0.01,0.01,0.01);
		drawObject(&sc.clock);
	glPopMatrix();
}

void timerTiger(int value) {
	moveTiger(&sc.anim_tiger);
	glutPostRedisplay();
	if (sc.TigerMoveMode)
		glutTimerFunc(TIGER_SPEED, timerTiger, 0);
}

void timerCow(int value) {
	if (++sc.angle_Cow >= 360) 
		sc.angle_Cow -= 360;

	glutPostRedisplay();

	if (sc.CowMoveMode)
		glutTimerFunc(COW_SPEED, timerCow, 0);
}

void timerDinner(int value){
	if (++sc.angle_Dinner >= 360) 
		sc.angle_Dinner -= 360;

	glutPostRedisplay();

	if (sc.DinnerMoveMode)
		glutTimerFunc(10, timerDinner, 0);
}

void timerTeapot(int value) {
	sc.tp_vel[0] = sc.tp_vel[0]*0.9995;
	sc.tp_vel[1] = sc.tp_vel[1]*0.9995;
	sc.tp_vel[2] = sc.tp_vel[2] - TEAPOT_SPEED/1000.0*9.80665; // 9 = 9.80665 m/s^2

	sc.tp_pos[0] += TEAPOT_SPEED/1000.0*sc.tp_vel[0];
	sc.tp_pos[1] += TEAPOT_SPEED/1000.0*sc.tp_vel[1];
	sc.tp_pos[2] += TEAPOT_SPEED/1000.0*sc.tp_vel[2];

	if (++sc.angle_Teapot >= 360) sc.angle_Teapot -= 360;

	if (sc.tp_pos[2] <= SMALL_OFFSET) 
		if (sc.AfterOneBounce) { 
			sc.TeapotMoveMode = 0, sc.AfterOneBounce = 0;
		}
		else {
			sc.AfterOneBounce = 1; 
			sc.tp_vel[2] *= -0.75;
		}

	glutPostRedisplay();

	if (sc.TeapotMoveMode) 
		glutTimerFunc(TEAPOT_SPEED, timerTeapot, 0);
}

void bounceDinner(int value){

	sc.dn_vel[0] = sc.dn_vel[0]*0.9995;
	sc.dn_vel[1] = sc.dn_vel[1]*0.9995;
	sc.dn_vel[2] = sc.dn_vel[2] - TEAPOT_SPEED/1000.0*9.80665; // 9 = 9.80665 m/s^2

	sc.dn_pos[0] += TEAPOT_SPEED/1000.0*sc.dn_vel[0];
	sc.dn_pos[1] += TEAPOT_SPEED/1000.0*sc.dn_vel[1];
	sc.dn_pos[2] += TEAPOT_SPEED/1000.0*sc.dn_vel[2];

	//if (++sc.angle_Teapot >= 360) sc.angle_Teapot -= 360;

	if (sc.dn_pos[2] <= SMALL_OFFSET) 
		if (sc.AfterOneBounce) { 
			sc.DinnerBounceMode = 0, sc.AfterOneBounce = 0;
		}
		else {
			sc.AfterOneBounce = 1; 
			sc.dn_vel[2] *= -0.75;
		}

	glutPostRedisplay();

	if (sc.DinnerBounceMode) 
		glutTimerFunc(TEAPOT_SPEED, bounceDinner, 0);
}

void keyUp(unsigned char key, int x, int y)
{
     sc.keyStates[key] = false;
}

void keyboardMain(unsigned char key, int x, int y) {

	sc.keyStates[key] = true;

	switch (key) {
	case 't':
		sc.TigerMoveMode = 1 - sc.TigerMoveMode;
		if (sc.TigerMoveMode)
			glutTimerFunc(TIGER_SPEED, timerTiger, 0);
		break;
	case 'c': 
		sc.CowMoveMode = 1 - sc.CowMoveMode;
		if (sc.CowMoveMode) 
			glutTimerFunc(COW_SPEED, timerCow, 0);	
		break;
	case 'p': 
		initializeTeapot();
		sc.TeapotMoveMode = 1 - sc.TeapotMoveMode;
		if (sc.TeapotMoveMode) 
			glutTimerFunc(TEAPOT_SPEED, timerTeapot, 0);	
		break;
	case 'f':
		sc.FillMode = 1 - sc.FillMode;
		if (sc.FillMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_DEPTH_TEST);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_DEPTH_TEST);
		}
		glutPostRedisplay();
		break;
	case 'v':
		sc.CameraMode = 1- sc.CameraMode;
		glutSetWindow(sc.SubWindowID);
		if(!sc.CameraMode)
			glutHideWindow();
		else
			glutShowWindow();
		glutPostRedisplay();
		break;
	case 'b':
		sc.TigerCameraMode = 1- sc.TigerCameraMode;
		glutSetWindow(sc.TigerWindowID);
		if(sc.TigerCameraMode)
			glutHideWindow();
		else
			glutShowWindow();
		glutPostRedisplay();
		break;
	case 'n':
		sc.DinnerMoveMode = 1 - sc.DinnerMoveMode;
		if(sc.DinnerMoveMode)
			glutTimerFunc(10,timerDinner,0);
		break;
	case 'm':
		initializeDinner();
		sc.DinnerBounceMode =  1 - sc.DinnerBounceMode;
		if (sc.DinnerBounceMode) 
			glutTimerFunc(TEAPOT_SPEED, bounceDinner, 0);	
		break;
	case '1':
		sc.lig[1] = 1 - sc.lig[1];
		if(sc.lig[1]){
			glutSetWindow(sc.SubWindowID);
			glEnable(GL_LIGHT1);
			glutSetWindow(sc.TigerWindowID);
			glEnable(GL_LIGHT1);
			glutSetWindow(sc.MainWindowID);
			glEnable(GL_LIGHT1);
		}
		else{
			glutSetWindow(sc.SubWindowID);
			glDisable(GL_LIGHT1);
			glutSetWindow(sc.TigerWindowID);
			glDisable(GL_LIGHT1);
			glutSetWindow(sc.MainWindowID);
			glDisable(GL_LIGHT1);
		}
		break;
	case '0':
		sc.lig[0] = 1 - sc.lig[0];
		if(sc.lig[0]){
			glutSetWindow(sc.SubWindowID);
			glEnable(GL_LIGHT5);
			glutSetWindow(sc.TigerWindowID);
			glEnable(GL_LIGHT5);
			glutSetWindow(sc.MainWindowID);
			glEnable(GL_LIGHT5);
		}
		else{
			glutSetWindow(sc.SubWindowID);
			glDisable(GL_LIGHT5);
			glutSetWindow(sc.TigerWindowID);
			glDisable(GL_LIGHT5);
			glutSetWindow(sc.MainWindowID);
			glDisable(GL_LIGHT5);
		}
		break;
	case '2':
		sc.lig[2] = 1 - sc.lig[2];
		if(sc.lig[2]){
			glutSetWindow(sc.SubWindowID);
			glEnable(GL_LIGHT7);
			glutSetWindow(sc.TigerWindowID);
			glEnable(GL_LIGHT7);
			glutSetWindow(sc.MainWindowID);
			glEnable(GL_LIGHT7);
		}
		else{
			glutSetWindow(sc.SubWindowID);
			glDisable(GL_LIGHT7);
			glutSetWindow(sc.TigerWindowID);
			glDisable(GL_LIGHT7);
			glutSetWindow(sc.MainWindowID);
			glDisable(GL_LIGHT7);
		}
		break;
	case '3':
		sc.lig[3] = 1 - sc.lig[3];
		if(sc.lig[3]){
			glutSetWindow(sc.SubWindowID);
			glEnable(GL_LIGHT3);
			glutSetWindow(sc.TigerWindowID);
			glEnable(GL_LIGHT3);
			glutSetWindow(sc.MainWindowID);
			glEnable(GL_LIGHT3);
		}
		else{
			glutSetWindow(sc.SubWindowID);
			glDisable(GL_LIGHT3);
			glutSetWindow(sc.TigerWindowID);
			glDisable(GL_LIGHT3);
			glutSetWindow(sc.MainWindowID);
			glDisable(GL_LIGHT3);
		}
		break;
	case '4':
		sc.lig[5] = 1 - sc.lig[5];
		if(sc.lig[5]){
			
			glutSetWindow(sc.SubWindowID);
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT2);
			glEnable(GL_LIGHT4);
			glEnable(GL_LIGHT6);
			glutSetWindow(sc.TigerWindowID);
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT2);
			glEnable(GL_LIGHT4);
			glEnable(GL_LIGHT6);
			glutSetWindow(sc.MainWindowID);
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT2);
			glEnable(GL_LIGHT4);
			glEnable(GL_LIGHT6);

		}
		else{
			glutSetWindow(sc.SubWindowID);
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHT4);
			glDisable(GL_LIGHT6);
			glutSetWindow(sc.TigerWindowID);
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHT4);
			glDisable(GL_LIGHT6);
			glutSetWindow(sc.MainWindowID);
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHT4);
			glDisable(GL_LIGHT6);
		}
		break;
	case 'q':
		exit(0);
	}
}

int prevx, prevy;

void mousepressMain(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			sc.CameraZoomModeMain = 1;
		}
		else if  (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
			sc.CameraGlobalRotationMode = 1;
		}			
		else if(glutGetModifiers() == GLUT_ACTIVE_ALT)
			sc.CameraZoomModeSub = 1;
		sc.leftbuttonpressed = 1;
		prevx = x, prevy = y;
	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
		sc.CameraZoomModeMain = sc.CameraZoomModeSub = sc.CameraGlobalRotationMode  = 0;
		sc.leftbuttonpressed = 0;
	}
}
void MyVecCrossProduct(float *v1, float *v2, float *v) {
	v[0] =   ( (v1[1] * v2[2]) - (v1[2] * v2[1]) );
	v[1] = - ( (v1[0] * v2[2]) - (v1[2] * v2[0]) );
	v[2] =   ( (v1[0] * v2[1]) - (v1[1] * v2[0]) );
}

void MyVecNormalize(float *v) {
	double length;

	length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	// Must check if length is very small here.

    for (int i = 0; i < 3; i++)
		v[i] /= length;
}

void mousemoveMain(int x, int y) {
	int delx, dely;
	
 
	if (sc.leftbuttonpressed) {
		delx = x - prevx, dely = prevy - y;
		prevx = x, prevy = y;

		if (sc.CameraZoomModeMain) {
				sc.camera[0].fovy += dely*ZOOM_SENSITIVITY;
				if (sc.camera[0].fovy < MIN_FOVY)
					sc.camera[0].fovy = MIN_FOVY;
				if (sc.camera[0].fovy > MAX_FOVY) 
					sc.camera[0].fovy = MAX_FOVY;
				glutSetWindow(sc.MainWindowID);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(sc.camera[0].fovy, sc.camera[0].aspect, sc.camera[0].near_c, sc.camera[0].far_c);
				glutPostRedisplay();
			
		}
		else if(sc.CameraZoomModeSub){
				sc.camera[1].fovy += dely*ZOOM_SENSITIVITY;
				if (sc.camera[1].fovy < MIN_FOVY)
					sc.camera[1].fovy = MIN_FOVY;
				if (sc.camera[1].fovy > MAX_FOVY) 
					sc.camera[1].fovy = MAX_FOVY;

				glutSetWindow(sc.SubWindowID);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(sc.camera[1].fovy, sc.camera[1].aspect, sc.camera[1].near_c, sc.camera[1].far_c);
				glutPostRedisplay();
		}
		else if (sc.CameraGlobalRotationMode) {
			if(sc.CameraMode == MAIN)
				globalRotate(delx,dely);
		}
	}
}

#define TO_RADIAN 0.01745329
void get_rotation_mat2(float angle, float m[3][3]){
	// In this program, vaxis = (0, 1, 0);
	float rad_angle, sina, cosa;

    rad_angle = TO_RADIAN*angle;
	sina = sin(rad_angle); cosa = cos(rad_angle);

	m[0][0] = cosa; m[0][1] = -sina;m[0][2] = 0.0;
	m[1][0] = sina;	m[1][1] = cosa;	m[1][2] = 0.0;
	m[2][0] = 0.0;	m[2][1] = 0.0;	m[2][2] = 0.0;
}

#define CAM_RSPEED 0.3
void renew_cam_ori_y(int angle){
  float m[3][3], tmpX, tmpY, tmpZ;

  get_rotation_mat2(CAM_RSPEED*angle, m);

  sc.camera[1].uaxis[X] = m[0][0]*(tmpX=sc.camera[1].uaxis[X]) + m[0][1]*(tmpY=sc.camera[1].uaxis[Y])
	  + m[0][2]*(tmpZ=sc.camera[1].uaxis[Z]);
  sc.camera[1].uaxis[Y] = m[1][0]*tmpX + m[1][1]*tmpY + m[1][2]*tmpZ;
  sc.camera[1].uaxis[Z] = m[2][0]*tmpX + m[2][1]*tmpY + m[2][2]*tmpZ;
  sc.camera[1].naxis[X] = m[0][0]*(tmpX=sc.camera[1].naxis[X]) + m[0][1]*(tmpY=sc.camera[1].naxis[Y])
	  + m[0][2]*(tmpZ=sc.camera[1].naxis[Z]);
  sc.camera[1].naxis[Y] = m[1][0]*tmpX + m[1][1]*tmpY + m[1][2]*tmpZ;
  sc.camera[1].naxis[Z] = m[2][0]*tmpX + m[2][1]*tmpY + m[2][2]*tmpZ;

  set_rotate_mat(&sc.camera[1]);
}

void mousePassiveMove(int x,int y){
	
	int delx, dely;

	delx = prevx - x, dely = prevy - y;
	prevx = x, prevy = y;

	if(sc.CameraMode){
		renew_cam_ori_y(delx);
		glutPostRedisplay();
	}
}

void globalRotate(int delx, int dely){

	double length, u_length, v_length;
	float d[3], dir[3];
	float R[16], tmpx, tmpy, tmpz;

	length = sqrt( (double) (delx*delx + dely*dely) );
	if (length < EPSILON) return;
	u_length = (double) delx/length, v_length = (double) dely/length;

	for (int i = 0; i < 3; i++) 
		d[i] = u_length*sc.camera[0].uaxis[i] + v_length*sc.camera[0].vaxis[i];
	MyVecCrossProduct(sc.camera[0].naxis, d, dir);

	// Let's borrow the OpenGL's function to setup the rotation matrix R
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(GLOBALROTATION_SENSITIVITY*length, dir[0], dir[1], dir[2]);
	glGetFloatv(GL_MODELVIEW_MATRIX, R); // 회전 행렬 얻기?
	glPopMatrix();

	// 뒤처리  ( vertors, rotate_mat, pos );

	sc.camera[0].uaxis[0] = R[0]*(tmpx=sc.camera[0].uaxis[0]) + R[4]*(tmpy=sc.camera[0].uaxis[1]) // u 방향으로 회전
		+ R[8]*(tmpz=sc.camera[0].uaxis[2]);
	sc.camera[0].uaxis[1] = R[1]*tmpx + R[5]*tmpy + R[9]*tmpz;
	sc.camera[0].uaxis[2] = R[2]*tmpx + R[6]*tmpy + R[10]*tmpz;
	MyVecNormalize(sc.camera[0].uaxis);

	sc.camera[0].vaxis[0] = R[0]*(tmpx=sc.camera[0].vaxis[0]) + R[4]*(tmpy=sc.camera[0].vaxis[1]) // v 방향으로 회전
		+ R[8]*(tmpz=sc.camera[0].vaxis[2]);
	sc.camera[0].vaxis[1] = R[1]*tmpx + R[5]*tmpy + R[9]*tmpz;
	sc.camera[0].vaxis[2] = R[2]*tmpx + R[6]*tmpy + R[10]*tmpz;
	MyVecNormalize(sc.camera[0].vaxis);

	MyVecCrossProduct(sc.camera[0].uaxis, sc.camera[0].vaxis, sc.camera[0].naxis); // 덩달아 나오는 n 벡터

	set_rotate_mat(&sc.camera[0]); // set sc.camera[0].mat 

	sc.camera[0].pos[0] = R[0]*(tmpx=sc.camera[0].pos[0]) + R[4]*(tmpy=sc.camera[0].pos[1])
		+ R[8]*(tmpz=sc.camera[0].pos[2]);
	sc.camera[0].pos[1] = R[1]*tmpx + R[5]*tmpy + R[9]*tmpz;
	sc.camera[0].pos[2] = R[2]*tmpx + R[6]*tmpy + R[10]*tmpz;

	// Now, update the Viewing Transformation

	glutPostRedisplay();

}


void specialDown(int key, int x, int y)
{
	switch(key)
	{
	case(GLUT_KEY_UP):
		sc.arrowKeys[UP_ARROW] = true;
		break;
	case(GLUT_KEY_DOWN):
		sc.arrowKeys[DOWN_ARROW] = true;
		break;
	case(GLUT_KEY_LEFT):
		sc.arrowKeys[LEFT_ARROW] = true;
		break;
	case(GLUT_KEY_RIGHT):
		sc.arrowKeys[RIGHT_ARROW] = true;
		break;
	}
}

void specialUp(int key, int x, int y)
{
	switch(key)
	{
	case(GLUT_KEY_UP):
		sc.arrowKeys[UP_ARROW] = false;
		break;
	case(GLUT_KEY_DOWN):
		sc.arrowKeys[DOWN_ARROW] = false;
		break;
	case(GLUT_KEY_LEFT):
		sc.arrowKeys[LEFT_ARROW] = false;
		break;
	case(GLUT_KEY_RIGHT):
		sc.arrowKeys[RIGHT_ARROW] = false;
		break;
	}
}


void keyCheck(void){

	int delx = 0, dely = 0, delz = 0;
	if(sc.CameraMode == MAIN){
		if(sc.arrowKeys[UP_ARROW]) 
			dely += 2;
		if(sc.arrowKeys[DOWN_ARROW]) 
			dely -= 2;
		if(sc.arrowKeys[RIGHT_ARROW]) 
			delx += 2;
		if(sc.arrowKeys[LEFT_ARROW]) 
			delx -= 2;

		globalRotate(delx,dely);
	}
	else if(sc.CameraMode == SUB){
		if(sc.keyStates['w']) 
			dely += 2;
		if(sc.keyStates['s']) 
			dely -= 2;
		if(sc.keyStates['d']) 
			delx -= 2;
		if(sc.keyStates['a']) 
			delx += 2;
		if(sc.keyStates['z'])
			delz += 2;
		if(sc.keyStates['x'])
			delz -= 2;

		sc.camera[1].pos[X] += (-delx * sc.camera[1].uaxis[X] + -dely * sc.camera[1].naxis[X] + -delz * sc.camera[1].vaxis[X]);
		sc.camera[1].pos[Y] += (-delx * sc.camera[1].uaxis[Y] + -dely * sc.camera[1].naxis[Y] + -delz * sc.camera[1].vaxis[Y]);
		sc.camera[1].pos[Z] += (-delx * sc.camera[1].uaxis[Z] + -dely * sc.camera[1].naxis[Z] + -delz * sc.camera[1].vaxis[Z]);
		glutSetWindow(sc.SubWindowID);
		glutPostRedisplay();
	}
}

void reshapeMain(int x, int y) {
	sc.MainWindowWidth = x, sc.MainWindowHeight = y;

	glViewport(0, 0, x, y);

	sc.camera[0].aspect = (double) x/ y;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(sc.camera[0].fovy, sc.camera[0].aspect, sc.camera[0].near_c, sc.camera[0].far_c);
}

void reshapeSub(int x, int y) {
	sc.MainWindowWidth = x, sc.MainWindowHeight = y;

	glViewport(0, 0, x, y);

	sc.camera[1].aspect = (double) x/ y;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(sc.camera[1].fovy, sc.camera[1].aspect, sc.camera[1].near_c, sc.camera[1].far_c);
}

void reshapeTiger(int x, int y) {
	sc.MainWindowWidth = x, sc.MainWindowHeight = y;

	glViewport(0, 0, x, y);

	sc.camera[2].aspect = (double) x/ y;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(sc.camera[2].fovy, sc.camera[2].aspect, sc.camera[2].near_c, sc.camera[2].far_c);
}


void initializeMainWindowOpenGLRenderingContext(void) {
	
	initializeCamera(&sc.camera[MAIN], MAIN);

	glClearColor(0.2, 0.2, 0.2, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glShadeModel(GL_SMOOTH); 

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	set_light();
	set_texture();
	
	glutPostRedisplay();
	glutSwapBuffers();
}

void set_light(void){

	int i;

	glLightfv(GL_LIGHT5, GL_AMBIENT,  lig_head_amb);
	glLightfv(GL_LIGHT5, GL_DIFFUSE,  lig_head_diff);
	glLightfv(GL_LIGHT5, GL_SPECULAR, lig_head_spec);

	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 10.0);
  	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 100.0);

	glLightfv(GL_LIGHT1, GL_AMBIENT,  lig_lamp_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  lig_lamp_diff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lig_lamp_spec);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0);
  	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10.0);
	
	glLightfv(GL_LIGHT7, GL_AMBIENT,  lig_cow_amb);
	glLightfv(GL_LIGHT7, GL_DIFFUSE,  lig_cow_diff);
	glLightfv(GL_LIGHT7, GL_SPECULAR, lig_cow_spec);
	
	glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 10.0);
  	glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 30.0);

	glLightfv(GL_LIGHT3, GL_AMBIENT,  lig_full_amb);
	glLightfv(GL_LIGHT3, GL_DIFFUSE,  lig_full_diff);
	glLightfv(GL_LIGHT3, GL_SPECULAR, lig_full_spec);

	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.01);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.001);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.00025);

	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT7);

	for(i=0;i<4;i++){
		glLightfv(0x4000+i*2, GL_AMBIENT,  lig_lamp_amb);
		glLightfv(0x4000+i*2, GL_DIFFUSE,  lig_lamp_diff);
		glLightfv(0x4000+i*2, GL_SPECULAR, lig_lamp_spec);

		glLightf(0x4000+i*2, GL_SPOT_CUTOFF, 20.0);
		glLightf(0x4000+i*2, GL_SPOT_EXPONENT, 10.0);
	
		glEnable(0x4000+i*2);
	}

	sc.lig[0] = sc.lig[2] = sc.lig[5]= 1;
	sc.lig[3] = sc.lig[1] = 0;

	glEnable(GL_NORMALIZE);

	sc.lig_lamp_spot_dir[2] = -1.0;
	sc.lig_lamp_spot_dir[3] =  0.0;

	for(i=0;i<4;i++){
		sc.lig_rotate_cow_spot_dir[i][2] = -1.0;
		sc.lig_rotate_cow_spot_dir[i][3] = 0.0;
	}
}

void set_texture(void){

	glGenTextures(3, sc.tex_name); // Generate one texture object and get its ID.

	glBindTexture(GL_TEXTURE_2D, sc.tex_name[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sc.forest1.ns, sc.forest1.nt, 
						0, GL_RGB, GL_UNSIGNED_BYTE, sc.forest1.tmap);

	glBindTexture(GL_TEXTURE_2D, sc.tex_name[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sc.Tiger_tex.ns, sc.Tiger_tex.nt, 
						0, GL_RGB, GL_UNSIGNED_BYTE, sc.Tiger_tex.tmap);
	glBindTexture(GL_TEXTURE_2D, sc.tex_name[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sc.forest2.ns, sc.forest2.nt, 
						0, GL_RGB, GL_UNSIGNED_BYTE, sc.forest2.tmap);
}

void initializeSubWindowOpenGLRenderingContext(void){

	initializeCamera(&sc.camera[SUB],SUB);
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	set_light();
	set_texture();

	glutSetWindow(sc.SubWindowID);
	glutHideWindow();
	glutPostRedisplay();
	
}

void initializeTigerWindowOpenGLRenderingContext(void){

	initializeCamera(&sc.camera[TIGER],MAIN);
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	set_light();
	set_texture();

	glutSetWindow(sc.TigerWindowID);
	glutHideWindow();
	glutPostRedisplay();
}

void Set_shadingMode(int select){
	
	if(select == 999){
		sc.FillMode = 1 - sc.FillMode;
		if (sc.FillMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_DEPTH_TEST);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_DEPTH_TEST);
		}
	}
	else{
		glShadeModel(select);
	}
	glutPostRedisplay();
}

void mainMenu(int select){

	glutPostRedisplay();
}

void MainMenu(void){

	int choiceshading;

	glutSetWindow(sc.MainWindowID);

	choiceshading = glutCreateMenu(Set_shadingMode);
	glutAddMenuEntry("SMOOTH",GL_SMOOTH);
	glutAddMenuEntry("FLAT",GL_FLAT);
	glutAddMenuEntry("WIRE_FRAME MODE",999);
	
	glutCreateMenu(mainMenu);
	glutAddSubMenu("Choice Shading Mode",choiceshading);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void setMainWindowCallbacks(void) {
	MainMenu();
	glutDisplayFunc(displayMain);
	glutReshapeFunc(reshapeMain);
    glutMouseFunc(mousepressMain);
	glutMotionFunc(mousemoveMain);
	glutPassiveMotionFunc(mousePassiveMove);
	glutKeyboardFunc(keyboardMain);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);
	glutIdleFunc(keyCheck);

}

void setTigerWindowCallbacks(void){
	glutDisplayFunc(displayTiger);
	glutReshapeFunc(reshapeTiger);
}

void setSubWindowCallbacks(void){
	glutDisplayFunc(displaySub);
	glutReshapeFunc(reshapeSub);
}


void main(int argc, char **argv) {
	glutInit(&argc, argv);
	initializeSystemContext();

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);  
	glutInitWindowSize(sc.MainWindowWidth, sc.MainWindowHeight);

	sc.MainWindowID = glutCreateWindow("Sogang University CSE3170 Homework 2 Demo (2014/04)");
	setMainWindowCallbacks();
	initializeMainWindowOpenGLRenderingContext();
	
	sc.TigerWindowID = glutCreateSubWindow(sc.MainWindowID,0,sc.MainWindowHeight*3/5,sc.MainWindowHeight*2/5,sc.MainWindowHeight*2/5);
	setTigerWindowCallbacks();
	initializeTigerWindowOpenGLRenderingContext();

	sc.SubWindowID = glutCreateSubWindow(sc.MainWindowID,sc.MainWindowWidth-sc.MainWindowHeight*2/5,sc.MainWindowHeight*3/5,sc.MainWindowHeight*2/5,sc.MainWindowHeight*2/5);
	setSubWindowCallbacks();
	initializeSubWindowOpenGLRenderingContext();

	glutMainLoop();
}



bool gluInvertMatrix(const float m[16], float invOut[16])
{
    float inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}