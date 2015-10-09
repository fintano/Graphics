// 
// CSE3170 Introduction to Computer Graphics HW2 Sample Code V0.5
// Dept. of Computer Sci. & Eng.
// Sogang University
// (C) 2014 Sogang Univeristy CSE3170
//
// These codes are provided just for your convenience, and need lots of improvements!!!
//

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <GL/glut.h>

#define MAX_VERTICES 5
#define X 0
#define Y 1
#define Z 2

#define TYPE_V 5000
#define TYPE_VN 5001
#define TYPE_VNT 5002

#define true 1;
#define false 0;

#define MAIN 0
#define SUB 1
#define TIGER 2

#define UP_ARROW 0
#define DOWN_ARROW 1
#define LEFT_ARROW 2
#define RIGHT_ARROW 3

#define NUM_MAX_ATTRIBUTES 8



typedef struct _polygon {
	int nvertex;
	float face[MAX_VERTICES][NUM_MAX_ATTRIBUTES]; // To be modified to dynamically allocate memory according to polygon types
} Polygon;

typedef struct _material {
	float emission[4], ambient[4], diffuse[4], specular[4], exponent;
} Material;

typedef struct _xform {
	float matrix[16];
	float matrix_inv[16];
} Xform;

typedef struct _object {
	int type;
	int nface;
    Polygon *polyhedron;
    float xmin, xmax, ymin, ymax, zmin, zmax; // Can find the center of an obejct
	int ncopy;
	Material *material;
	Xform *xform;
} Object;

typedef struct _light {
	float position[4], ambient[4], diffuse[4], specular[4];
} Light;

typedef struct _scene { // If not used, forget about this.
	int nobject;
	char *fname[256];
	Object *objects;
	int nlight;
	Light *lights;
} Scene;

typedef struct _animobjects {
	int nobject;
	char *fname[256];
	Object *objects;
	float TigerX;
	float TigerY;
	float Rotate;
	int count;
} AnimObjects;

typedef struct _cam {
	float pos[3];
	float uaxis[3], vaxis[3], naxis[3];
	GLfloat mat[16];
	GLfloat mat_inv[16];
	int move, upanddown;
	GLdouble fovy, aspect, near_c, far_c;
} Camera;

typedef struct {
	int ns, nt;
	GLubyte *tmap;
} Texture;

typedef enum {RGB, RGBA} TEXTURETYPE;

 typedef struct _SC { // System Context. Modify this as you wish.
	int keyStates[256];
	int arrowKeys[4];
	int MainWindowID, MainWindowWidth, MainWindowHeight;
	int SubWindowID, SubWindowWidth, SubWindowHeight;
	int TigerWindowID;
	int TigerMoveMode, CowMoveMode, TeapotMoveMode, AfterOneBounce, FillMode, DinnerMoveMode,DinnerBounceMode;
	int CameraMode,TigerCameraMode;
	int CameraZoomModeMain, CameraZoomModeSub, CameraGlobalRotationMode;
	int angle_Cow, angle_Teapot,angle_Dinner,angle_table;
	float tp_pos[3], tp_vel[3],dn_pos[3],dn_vel[3];
	AnimObjects anim_tiger;
	Object Cow;
	Object chair,clock,jar,building,table,chair2,box;
	float pos[3], vel[3];
	int leftbuttonpressed, rightbuttonpressed;
	double fovy, window_aspect_ratio;
	Camera camera[4];

	int lig[8];
	GLfloat lig_lamp_spot_dir[4];
	GLfloat lig_rotate_cow_spot_dir[4][4];
	Texture forest1,forest2,Tiger_tex;
	GLuint tex_name[2];
}  SC;

 

// Clean up this part!

 bool gluInvertMatrix(const float m[16], float invOut[16]);

 void armor_cow(void);
 void draw_table_setting(void);
 void draw_chair_and_cow(void);
 void draw_box(void);
void globalRotate(int delx, int dely);
void drawModel(void);
void renew_cam_ori_y(int angle);
void get_rotation_mat2(float angle, float m[3][3]);

void keyCheck(void);
void specialDown(int key, int x, int y);
void specialUp(int key, int x, int y);
void read_light(FILE *, Light *);
void read_scene(char *, Scene *);
void read_object(char *, Object *);
void read_animobjects(char *fname, AnimObjects *objects);

void init_system(void);

void moveTiger(AnimObjects *tiger);
void drawTiger(AnimObjects *tiger);
void drawObject(Object *);
void drawAxes(GLfloat scale);
void drawSquare(float size, int freq);
void draw_planes_WC(GLuint tmp);

void read_texture_PPM(char *fname, Texture *tex);
void set_Light1(void);
void set_rotate_mat(Camera *cam);
void initializeCamera(Camera *cam, int mode);
void set_texture(void);
void set_light(void);
void set_Rotate_Light(int i);

#define TIGER_ANIM 2000
#define TIGER_SPEED 80 // milliseconds
#define COW_SPEED 30 // milliseconds
#define TEAPOT_SPEED 10 // milliseconds

#define INIT_WINDOW_WIDTH 800
#define INIT_WINDOW_HEIGHT 600

#define SMALL_OFFSET 1.0
#define ZOOM_SENSITIVITY 0.4
#define GLOBALROTATION_SENSITIVITY 0.25
#define MIN_FOVY 10.0
#define MAX_FOVY 90.0
#define EPSILON 0.00001
