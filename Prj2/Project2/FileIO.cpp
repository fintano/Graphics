// 
// CSE3170 Introduction to Computer Graphics HW2 Sample Code V0.5
// Dept. of Computer Sci. & Eng.
// Sogang University
// (C) 2014 Sogang Univeristy CSE3170
//
// These codes are provided just for your convenience, and need lots of improvements!!!
//

#include "1403CSE3170HW2.h"
void read_PPM_P3(FILE *fp, Texture *tex) {
	// This input routine may not be perfect.
	// More things to do: The scale factor must be applied properly. 
	char buf[512];
	int scale, tmp, npixels;
	int counter = 0;
	int r, g, b;
	unsigned char *curptr;

	fgets(buf, 511, fp);
	printf("*** %s\n", buf);
	if (buf[0] != '#') goto next;
	fgets(buf, 511, fp);
next:
	sscanf(buf, "%d %d", &tex->ns, &tex->nt);
	npixels = tex->ns*tex->nt;
	fgets(buf, 511, fp);
	sscanf(buf, "%d", &scale);
	curptr = tex->tmap = (GLubyte *) malloc(npixels*3);

	while (fscanf(fp, "%d %d %d", &r, &g, &b) == 3) {
	    *(curptr++) = (unsigned char) r;
	    *(curptr++) = (unsigned char) g;
	    *(curptr++) = (unsigned char) b;
		counter++;
	}
	printf(" $$$ %d %d\n", counter, npixels);
	if (counter  != npixels) {
		printf("Error: can not read image body properly (%d != %d)...\n", counter, npixels);
		exit(-1);
	}
	fclose(fp);
	printf("Done\n\n");
} 

void read_PPM_P6(FILE *fp, Texture *tex) {
	// This input routine may not be perfect.
	char buf[512];
	int scale, tmp, npixels;

	fgets(buf, 511, fp);
	if (buf[0] != '#') goto next;
	fgets(buf, 511, fp);
next:
	sscanf(buf, "%d %d", &tex->ns, &tex->nt);
	npixels = tex->ns*tex->nt;
	fgets(buf, 511, fp);
	sscanf(buf, "%d", &scale);
	printf("Reading P6 type of size %dx%d with scale %d...\n", tex->ns, tex->nt, scale); 
	tex->tmap = (GLubyte *) malloc(npixels*3);
	if ((tmp = fread(tex->tmap, 3, npixels, fp)) != npixels) {
		printf("Error: can not read image body properly...\n", tmp);
		exit(-1);
	}
	fclose(fp);
	printf("Done\n\n");
}

void read_texture_PPM(char *fname, Texture *tex) {
	// More things to do: The scale factor must be applied properly. 
	FILE *fp;
	char buf[512];

	if ((fp = fopen(fname, "rb")) == NULL) {
		printf("Error: can not open the file %s...\n", fname);
		exit(-1);
	}
	fgets(buf, 511, fp);
	if ((buf[0] == 'P') && (buf[1] == '6'))  
		read_PPM_P6(fp, tex);
	else if ((buf[0] == 'P') && (buf[1] == '3'))
		read_PPM_P3(fp, tex);
	else {
		printf("Error: an unknown ppm format (%c%c)\n", buf[0], buf[1]);
		exit(-1);
	}
}


void read_object(char *fname, Object *object) {
    FILE *fp;
	char tmpc;
	int nvertex, i, j, k, NUM = 3;
	float tmpf;

	object->xmin = object->ymin = object->zmin = FLT_MAX;
	object->xmax = object->ymax = object->zmax = -FLT_MAX;

	if ((fp = fopen(fname, "r")) == NULL) {
		printf("Error: can not read the file %s ...\n", fname);
		exit(-1);
	}
	fscanf(fp, "%c", &tmpc); 
	switch (tmpc) {
	case 'V' :
		object->type = TYPE_V;  
		NUM = 3;
		break;
	case 'N' :
		object->type = TYPE_VN;  
		NUM = 6;
		break;
	case 'T' :
		object->type = TYPE_VNT;  
		NUM = 8;
		break;
	}
	
	fscanf(fp, "%d", &(object->nface));  
	object->polyhedron = (Polygon *) malloc(sizeof(Polygon)*object->nface);
	for (i = 0; i < object->nface; i++) {
		fscanf(fp, "%d", &nvertex);
		object->polyhedron[i].nvertex = nvertex; 
		for (j = 0; j < nvertex; j++) {
			for (k = 0; k < NUM; k++)
				fscanf(fp, "%f", &(object->polyhedron[i].face[j][k]));

			if ((tmpf=object->polyhedron[i].face[j][0]) < object->xmin) object->xmin = tmpf;
			if ((tmpf=object->polyhedron[i].face[j][0]) > object->xmax) object->xmax = tmpf;
			if ((tmpf=object->polyhedron[i].face[j][1]) < object->ymin) object->ymin = tmpf;
			if ((tmpf=object->polyhedron[i].face[j][1]) > object->ymax) object->ymax = tmpf;
			if ((tmpf=object->polyhedron[i].face[j][2]) < object->zmin) object->zmin = tmpf;
			if ((tmpf=object->polyhedron[i].face[j][2]) > object->zmax) object->zmax = tmpf;
		}
	}
	fclose(fp);
//	printf("       xmin = %f, xmax = %f\n       ymin = %f, ymax = %f\n       zmin = %f, zmax = %f\n", 
//		object->xmin, object->xmax, object->ymin, object->ymax, object->zmin, object->zmax);
}

// Currently unused
void read_light(FILE *fp, Light *light) {

 	fscanf(fp, "%f %f %f %f", &(light->position[0]), &(light->position[1]), 
		&(light->position[2]), &(light->position[3]));
	fscanf(fp, "%f %f %f %f", &(light->ambient[0]), &(light->ambient[1]), 
		&(light->ambient[2]), &(light->ambient[3]));
	fscanf(fp, "%f %f %f %f", &(light->diffuse[0]), &(light->diffuse[1]), 
		&(light->diffuse[2]), &(light->diffuse[3]));
	fscanf(fp, "%f %f %f %f", &(light->specular[0]), &(light->specular[1]), 
		&(light->specular[2]), &(light->specular[3]));

	printf("    --- posi: %f %f %f %f\n", light->position[0], light->position[1], 
		light->position[2], light->position[3]);
	printf("    --- ambi: %f %f %f %f\n", light->ambient[0], light->ambient[1], 
		light->ambient[2], light->ambient[3]);
	printf("    --- diff: %f %f %f %f\n", light->diffuse[0], light->diffuse[1], 
		light->diffuse[2], light->diffuse[3]);
	printf("    --- spec: %f %f %f %f\n", light->specular[0], light->specular[1], 
		light->specular[2], light->specular[3]);
}

// Currently unsed
void read_scene(char *fname, Scene *scene) {
    FILE *fp;
	int i, j, k;
	Object *object;
	Material *material;
	Xform *xform;
 
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("read_scene: can not read the file %s ...\n", fname);
		exit(-1);
	}

	fscanf(fp, "%d", &(scene->nobject));

	for (i = 0; i < scene->nobject; i++) 
		scene->fname[i] = (char *) malloc(256);
	scene->objects = (Object *) malloc(sizeof(Object)*scene->nobject);

	for (i = 0, object = scene->objects; i < scene->nobject; i++, object++) {
 
		fscanf(fp, "%s", scene->fname[i]);

		fscanf(fp, "%d", &(object->ncopy));

		object->material = (Material *) malloc(sizeof(Material)*object->ncopy);
		object->xform = (Xform *) malloc(sizeof(Xform)*object->ncopy);

		for (j = 0, material = object->material, xform = object->xform; j < object->ncopy; j++, material++, xform++) {
//			printf("   --- Reading object(%d)'s (%d)th copy's mat. properties in %s ...\n", i, j, scene->fname[i]);
			fscanf(fp, "%f %f %f %f", &(material->emission[0]), &(material->emission[1]),
				&(material->emission[2]), &(material->emission[3]));
			fscanf(fp, "%f %f %f %f", &(material->ambient[0]), &(material->ambient[1]), 
				&(material->ambient[2]), &(material->ambient[3]));
			fscanf(fp, "%f %f %f %f", &(material->diffuse[0]), &(material->diffuse[1]),
				&(material->diffuse[2]), &(material->diffuse[3]));
			fscanf(fp, "%f %f %f %f", &(material->specular[0]), &(material->specular[1]), 
				&(material->specular[2]), &(material->specular[3]));
			fscanf(fp, "%f", &(material->exponent));

//			printf("   --- Reading object(%d)'s (%d)th copy's trans. information in %s ...\n", i, j, scene->fname[i]);
			for (k = 0; k < 4; k++) fscanf(fp, "%f", xform->matrix + 4*k);
			for (k = 0; k < 4; k++) fscanf(fp, "%f", xform->matrix + 4*k + 1);
			for (k = 0; k < 4; k++) fscanf(fp, "%f", xform->matrix + 4*k + 2);
			for (k = 0; k < 4; k++) fscanf(fp, "%f", xform->matrix + 4*k + 3);
		}

//		printf("   --- Reading object(%d)'s geometry in %s ...\n", i, scene->fname[i]);
		read_object(scene->fname[i], object);
//		printf("   --- Done with object(%d) ...\n\n", i);
	}
	fscanf(fp, "%d", &(scene->nlight));
	scene->lights = (Light *) malloc(sizeof(Light)*scene->nlight);

	printf("[[[ %s contains %d lights ... ]]]\n\n", fname, scene->nlight);
	for (i = 0; i < scene->nlight; i++) {
		printf("   --- Reading light(%d) ...\n", i);
		read_light(fp, &(scene->lights[i]));
		printf("   --- Done ...\n\n");
	}
	fclose(fp);
}

void read_animobjects(char *fname, AnimObjects *objects) {
    FILE *fp;
	int i, j, k;
	Object *object;
	Material *material;
	Xform *xform;
 
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("read_animobjects: can not read the file %s ...\n", fname);
		exit(-1);
	}

	fscanf(fp, "%d", &(objects->nobject));
	printf("[[[ %s contains %d objects ... ]]]\n\n", fname, objects->nobject);

	for (i = 0; i < objects->nobject; i++) 
		objects->fname[i] = (char *) malloc(256);
	objects->objects = (Object *) malloc(sizeof(Object)*objects->nobject);

	for (i = 0, object = objects->objects; i < objects->nobject; i++, object++) {
 
		fscanf(fp, "%s", objects->fname[i]);

		fscanf(fp, "%d", &(object->ncopy));

		object->material = (Material *) malloc(sizeof(Material)*object->ncopy);
		object->xform = (Xform *) malloc(sizeof(Xform)*object->ncopy);

		for (j = 0, material = object->material, xform = object->xform; j < object->ncopy; j++, material++, xform++) {
			printf("   --- Reading object(%d)'s (%d)th copy's mat. properties in %s ...\n", i, j, objects->fname[i]);
			fscanf(fp, "%f %f %f %f", &(material->emission[0]), &(material->emission[1]),
				&(material->emission[2]), &(material->emission[3]));
			fscanf(fp, "%f %f %f %f", &(material->ambient[0]), &(material->ambient[1]), 
				&(material->ambient[2]), &(material->ambient[3]));
			fscanf(fp, "%f %f %f %f", &(material->diffuse[0]), &(material->diffuse[1]),
				&(material->diffuse[2]), &(material->diffuse[3]));
			fscanf(fp, "%f %f %f %f", &(material->specular[0]), &(material->specular[1]), 
				&(material->specular[2]), &(material->specular[3]));
			fscanf(fp, "%f", &(material->exponent));

			printf("   --- Reading object(%d)'s (%d)th copy's trans. information in %s ...\n", i, j, objects->fname[i]);
			for (k = 0; k < 4; k++) fscanf(fp, "%f", xform->matrix + 4*k);
			for (k = 0; k < 4; k++) fscanf(fp, "%f", xform->matrix + 4*k + 1);
			for (k = 0; k < 4; k++) fscanf(fp, "%f", xform->matrix + 4*k + 2);
			for (k = 0; k < 4; k++) fscanf(fp, "%f", xform->matrix + 4*k + 3);

			gluInvertMatrix(xform->matrix,xform->matrix_inv);

		}

		printf("   --- Reading object(%d)'s geometry in %s ...\n", i, objects->fname[i]);
		read_object(objects->fname[i], object);
		printf("   --- Done with object(%d) ...\n\n", i);
	}

	fclose(fp);
}

