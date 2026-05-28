#ifndef RENDERLOOP_H
#define RENDERLOOP_H

// variables declarations
extern bool bShowGrid;
extern float gfScreenXRotationAngle ;
extern float gfScreenYRotationAngle ;
extern float gfScreenZRotationAngle ;
extern float gfScreenXTranslation ;
extern float gfScreenYTranslation ;
extern float gfScreenZTranslation ;

// functions declarations
// this functs called every frame
void display(void);
void update(void);

// local fucntions
void showGrid(void);


#endif