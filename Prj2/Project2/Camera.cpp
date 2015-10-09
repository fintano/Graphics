// 
// CSE3170 Introduction to Computer Graphics HW2 Sample Code V0.5
// Dept. of Computer Sci. & Eng.
// Sogang University
// (C) 2014 Sogang Univeristy CSE3170
//
// These codes are provided just for your convenience, and need lots of improvements!!!
//

#include "1403CSE3170HW2.h"

void set_rotate_mat(Camera *cam) {
	#define M(row,col)  cam->mat[col*4+row] // C/C++ way
    M(0,0)=cam->uaxis[X]; M(0,1)=cam->uaxis[Y]; M(0,2)=cam->uaxis[Z]; M(0,3)=0.0;
    M(1,0)=cam->vaxis[X]; M(1,1)=cam->vaxis[Y]; M(1,2)=cam->vaxis[Z]; M(1,3)=0.0;
    M(2,0)=cam->naxis[X]; M(2,1)=cam->naxis[Y]; M(2,2)=cam->naxis[Z]; M(2,3)=0.0;
    M(3,0)=0.0;  M(3,1)=0.0;  M(3,2)=0.0;  M(3,3)=1.0;
}

void initializeCamera(Camera *cam, int mode) {
	GLfloat matrix[16];

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	if(mode == MAIN)
		gluLookAt(150.0, 150.0, 50.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	else if(mode == SUB)
		gluLookAt(150.0 ,150.0, 20.0, 0.0, 0.0, 20.0, 0.0, 0.0, 1.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();

	if(mode == MAIN){
		cam->pos[X] = 150.0; cam->pos[Y]= 150.0;  cam->pos[Z] = 50.0;
	}
	else if(mode == SUB){
		cam->pos[X] = 150.0; cam->pos[Y] = 150.0 ; cam -> pos[Z] = 20.0;
	}

	cam->uaxis[X] = matrix[0]; cam->uaxis[Y] = matrix[4]; cam->uaxis[Z] = matrix[8];
	cam->vaxis[X] = matrix[1]; cam->vaxis[Y] = matrix[5]; cam->vaxis[Z] = matrix[9];
	cam->naxis[X] = matrix[2]; cam->naxis[Y] = matrix[6]; cam->naxis[Z] = matrix[10];
	
	set_rotate_mat(cam);

	cam->move = 0;
	cam->fovy = 45.0, cam->aspect = 1.0; cam->near_c = 1.0; cam->far_c = 1000.0;
}

