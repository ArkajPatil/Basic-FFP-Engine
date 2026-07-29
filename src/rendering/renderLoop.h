#ifndef RENDERLOOP_H
#define RENDERLOOP_H

// variables declarations
extern bool gbShowGrid;
extern bool gbShowAxis;
extern float gfScreenXRotationAngle ;
extern float gfScreenYRotationAngle ;
extern float gfScreenZRotationAngle ;
extern float gfScreenXTranslation ;
extern float gfScreenYTranslation ;
extern float gfScreenZTranslation ;
extern bool gbDisplaySelectedModel ;
extern bool gbDisplayAllModels ;
extern bool gbDisplayAllVisibleModels ;
extern bool gbHighlightSelectedModel ;

// functions declarations
// this functs called every frame
void display(void);
void update(void);

// local fucntions
void showAxis(void);
void showGrid(void);


#endif