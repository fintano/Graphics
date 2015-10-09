// 
// CSE3170 Introduction to Computer Graphics HW2 Sample Code V0.5
// Dept. of Computer Sci. & Eng.
// Sogang University
// (C) 2014 Sogang Univeristy CSE3170
//
// These codes are provided just for your convenience, and need lots of improvements!!!
//

#include "1403CSE3170HW2.h"

// Tiger를 움직이는데 필요한 값들
unsigned int prevTickCount = 0, prevTigerTick = 0;
int   g_TigerAniCount = 0;
int   g_Tiger = -1;
float TigerXPos = 0.0;
float TigerYPos = 0.0;
float TigerRotate = 0.0;
float TigerXSpeed = 2.0;
float TigerYSpeed = 0.0;
float TigerXEnd = 0.0;
float TigerYEnd = 0.0;
float TigerEyeAngle = 0.0;
float TigerEye[3] = { 0.0, -88.0, 62.0 };
float TigerEyeAngleSpeed = 1.0;

float besideCameraDis = 170.0;

// 호랑이 움직임 값
void moveTiger(AnimObjects *anim_tiger) {
	g_TigerAniCount++;
	
	if (g_TigerAniCount >= anim_tiger->nobject )
		g_TigerAniCount = 0;

	TigerXPos += TigerXSpeed;
	TigerYPos += TigerYSpeed;
		
	if ( TigerXPos >= TigerXEnd - 5 && TigerXPos <= TigerXEnd + 5 && 
		 TigerYPos >= TigerYEnd - 5 && TigerYPos <= TigerYEnd + 5 )
	{
		g_Tiger++;
		if ( g_Tiger >=4 ) g_Tiger = 0;
	}

	switch( g_Tiger ) {
		case 0:
			TigerRotate = 0.0;
			TigerXSpeed = 1.0;
			TigerYSpeed = 0.0;
			TigerYPos = 0.0;
			TigerXEnd = 120.0;
			TigerYEnd = 0.0;
			break;
		case 1:
			TigerRotate = 180.0;
			TigerXSpeed = -1.0;
			TigerYSpeed = 0.0;
			TigerXEnd = -14.0;
			TigerYEnd = 0.0;
			break;
		case 2:
			TigerRotate = -90.0;
			TigerXSpeed = 0.0;
			TigerYSpeed = -1.0;
			TigerXEnd = -14.0;
			TigerYEnd = -75.0;
			break;
		case 3:
			TigerRotate = 90.0;
			TigerXSpeed = 0.0;
			TigerYSpeed = 1.0;
			TigerXEnd = -14.0;
			TigerYEnd = 0.0;
			break;
	}
	anim_tiger->TigerX = TigerXPos;
	anim_tiger->TigerY = TigerYPos;
	anim_tiger->Rotate = TigerRotate;
	anim_tiger->count = g_TigerAniCount;
}

void drawTiger(AnimObjects *anim_tiger) {
	int num = 0, i = 0, j = 0;

	Object *pObj = &anim_tiger->objects[g_TigerAniCount];

//	if ( bCameraView && ( num = getTextNum( pObj->filename ) ) >= 0 )	{
//		glEnable( GL_TEXTURE_2D );
//		glBindTexture( GL_TEXTURE_2D, texNum[num] );
//		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
//	}
	
	glMatrixMode(GL_MODELVIEW);
	
	glColor3fv( pObj->material[0].diffuse );

	glPushMatrix();
	glTranslatef( TigerXPos, TigerYPos, 0.0 );
	glMultMatrixf( (const float*) &( pObj->xform[0].matrix ) );
	glRotatef( TigerRotate, 0.0, 0.0, 1.0 );

	drawAxes(15.0);

	glPushMatrix();
	glTranslatef(0.0, -88.0, 62.0);
	drawAxes(15.0);
	glPopMatrix();

	//glEnable(GL_TEXTURE_2D);
	//glFrontFace(GL_CW);
	for ( int k = 0; k < pObj->ncopy; ++k ) {
		glMaterialfv( GL_FRONT, GL_AMBIENT, pObj->material[k].ambient );
		glMaterialfv( GL_FRONT, GL_DIFFUSE, pObj->material[k].diffuse );
		glMaterialfv( GL_FRONT, GL_SPECULAR, pObj->material[k].specular );
		glMaterialfv( GL_FRONT, GL_EMISSION, pObj->material[k].emission );
		glMaterialf( GL_FRONT, GL_SHININESS, pObj->material[k].exponent );

		glColor3fv(pObj->material[k].diffuse);

		

		if (pObj->type == TYPE_V) {
			for (i = 0; i < pObj->nface; i++) {
				glBegin(GL_POLYGON);
				for (j = 0; j < pObj->polyhedron[i].nvertex; j++) {
					glVertex3fv(&(pObj->polyhedron[i].face[j][0]));
				}
				glEnd();
			}
		}
		else if (pObj->type == TYPE_VN) {
			for (i = 0; i < pObj->nface; i++) {
				glBegin(GL_POLYGON);
				for (j = 0; j < pObj->polyhedron[i].nvertex; j++) {
					glNormal3fv(&(pObj->polyhedron[i].face[j][3]));
					glVertex3fv(&(pObj->polyhedron[i].face[j][0]));
				}
				glEnd();
			}
		}
		else if (pObj->type == TYPE_VNT) { // for the time being
			for (i = 0; i < pObj->nface; i++) {
				glBegin(GL_POLYGON);
				for (j = 0; j < pObj->polyhedron[i].nvertex; j++) {
					glTexCoord2fv(&(pObj->polyhedron[i].face[j][6]));
					glNormal3fv(&(pObj->polyhedron[i].face[j][3]));
					glVertex3fv(&(pObj->polyhedron[i].face[j][0]));
				}
				glEnd();
			}
		}
	}
	//glFrontFace(GL_CCW);
	//glDisable( GL_TEXTURE_2D );
	glPopMatrix();
}

void drawObject(Object *object) {
	int i, j;

	if (object->type == TYPE_V) {
		for (i = 0; i < object->nface; i++) {
			glBegin(GL_POLYGON);
			for (j = 0; j < object->polyhedron[i].nvertex; j++) {
				glVertex3fv(&(object->polyhedron[i].face[j][0]));
			}
			glEnd();
		}
	}
	else if (object->type == TYPE_VN) {
		for (i = 0; i < object->nface; i++) {
			glBegin(GL_POLYGON);
			for (j = 0; j < object->polyhedron[i].nvertex; j++) {
				glNormal3fv(&(object->polyhedron[i].face[j][3]));
				glVertex3fv(&(object->polyhedron[i].face[j][0]));
			}
			glEnd();
		}
	}
	else if (object->type == TYPE_VNT) {  
		for (i = 0; i < object->nface; i++) {
			glBegin(GL_POLYGON);
			for (j = 0; j < object->polyhedron[i].nvertex; j++) {
				glTexCoord2fv(&(object->polyhedron[i].face[j][6]));
				glNormal3fv(&(object->polyhedron[i].face[j][3]));
				glVertex3fv(&(object->polyhedron[i].face[j][0]));
			}
			glEnd();
		}
	}
}

void drawAxes(GLfloat scale) {
	glLineWidth(3.0);
	glDisable(GL_LIGHTING);
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
	glEnable(GL_LIGHTING);
	glLineWidth(1.0);
}

void drawSquare(float size, int freq) {
	float h, v, delta;
	//glFrontFace(GL_CW);
	delta = size/freq;
	glNormal3f(0.0, 0.0, 1.0);
	for (h = 0.0; h < size; h += delta)  {
		//glDisable(GL_LIGHTING);
		glBegin(GL_QUAD_STRIP);
		for (v = 0.0; v < size + delta; v += delta) {
			glVertex3f(v, h + delta, 0.0);
			glVertex3f(v, h, 0.0);
		}
		glEnd();
		//glEnable(GL_LIGHTING);
	}
}

GLfloat mat_bronze_amb[] = {0.2125, 0.1275, 0.054};
GLfloat mat_bronze_diff[] = {0.714, 0.4284, 0.18144};
GLfloat mat_bronze_spec[] = {0.393548, 0.271906, 0.166721};
GLfloat mat_bronze_exp = 25.6;


GLfloat mat_brass_amb[] = {0.329412, 0.223529, 0.027451};
GLfloat mat_brass_diff[] = {0.780392, 0.568627, 0.113725};
GLfloat mat_brass_spec[] = {0.992157, 0.941176, 0.807843};
GLfloat mat_brass_exp = 27.9;
void draw_planes_WC(GLuint tmp) {	
	
	float i, j;

	//glBindTexture(GL_TEXTURE_2D, tmp);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glEnable(GL_TEXTURE_2D);


	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_bronze_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_bronze_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_bronze_spec);
	glMaterialf (GL_FRONT, GL_SHININESS, mat_bronze_exp);

	glNormal3f(0.0, 1.0, 0.0);
	for (i = -2.0; i < 10.0; i += 0.25) {	
		glBegin(GL_QUAD_STRIP);
		//glTexCoord2f(0.0, 0.0); glTexCoord2f(1.0, 0.0);
		for (j = -10.0; j <= 10.0; j += 0.25) {
			glVertex3f(j, -10.0, i); glVertex3f(j, -10.0, i+0.25);
		}
		//glTexCoord2f(0.0, 1.0);glTexCoord2f(1.0, 1.0);
		glEnd();
	}

	glNormal3f(0.0, 0.0, 1.0);
	for (i = -10.0; i < 10.0; i += 0.25) {	
		glBegin(GL_QUAD_STRIP);
		for (j = -10.0; j <= 10.0; j += 0.25) {
			glVertex3f(i, j, 0.0); glVertex3f(i+0.25, j, 0.0);
		}
		glEnd();
	}
	 
  	glNormal3f(1.0, 0.0, 0.0);
	for (i = -2.0; i < 10.0; i += 0.25) {	
		glBegin(GL_QUAD_STRIP);
		for (j = -10.0; j <= 10.0; j += 0.25) {
			glVertex3f(-10.0, j, i+0.25); glVertex3f(-10.0, j, i);
		}
		glEnd();
	}
	//glDisable(GL_TEXTURE_2D);
}