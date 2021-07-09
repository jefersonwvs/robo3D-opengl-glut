#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

/* Procedimento padr�o */
void init(void);


/* Fun��es Callback */
void window_reshape(int, int);
void window_display(void);
void redisplay_all(void);

void world1_reshape(int, int);
void world1_display(void);

void world2_reshape(int, int);
void world2_display(void);

void world3_reshape(int, int);
void world3_display(void);

void keyboard(unsigned char, int, int);
void specialKeyboar(int, int, int);


/* Procedimentos desenhadores */
void drawRobot(void);
void drawWCS(void);
void drawFoot(double, double, double);
void drawArm(double, double);
void drawAxis(double);
void drawLabel(double, double, double, double);
void drawObj(double, double, double, double);


/* Procedimento utilit�rio */
int movementLimitation(double, double, double);


#define GAP 25	/* dist�ncia entre duas sub-janelas de mundos */

int window;		/* id da janela principal */
int world1;		/* id da sub-janela do mundo 1 */
int world2;		/* id da sub-janela do mundo 2 */
int world3;		/* id da sub-janela do mundo 3 */

float eyex, eyey, eyez;					/* vetor eye da c�mera do mundo 2*/
float centerx, centery, centerz;		/* vetor center da c�mera do mundo 2*/
float upx, upy, upz;					/* vetor up da c�mera do mundo 2*/

float x_foot, y_foot, z_foot;			/* posi��o do rob� no espa�o xyz */
float y_arm2, y_arm3;					/* posi��es dos bra�os 2 e 3 */

/* �ngulos dos elementos do rob� */
float anglex_arm1, angley_arm1, anglez_arm1;
float anglex_arm2, angley_arm2, anglez_arm2;
float anglex_arm3, angley_arm3, anglez_arm3;
float angle_obj4, angle_obj5a, angle_obj5b;
float angle_arm6, angle_arm7;

#endif
