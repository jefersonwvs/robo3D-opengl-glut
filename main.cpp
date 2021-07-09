/*
 * Universidade Federal da Grande Dourados - UFGD
 * Faculdade de Ciências Exatas e Tecnologia - FACET
 * Curso de Bacharelado em Sistemas de Informação - BSI
 *
 * Disciplina: LABORATÓRIO DE COMPUTAÇÃO GRÁFICA - LCG
 * Prof.: Adailton José Alves da Cruz
 * Período: 2020.05 - Módulo IV - RAE
 *
 * Atividade 04: desenvolvimento de um robô 3D capaz de fazer movimentos simples,
 *               tais como: translações em linha reta e rotações.
 *
 * Desenvolvido por: Jeferson Willian Vieira Silva.
 * Desenvolvido em: 11-12 de dezembro de 2020.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include "header.h"

/*
 * Função principal: ponto de entrada do programa.
 * Parâmetros:
 *  - argc: número de argumentos
 *  - argv: matriz de caracteres (ou vetor de strings)
 * Retorno:
 *  - 0: sucesso na execução do programa
 *  - demais valores: programa finalizado com erro
 */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1360,470);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    window = glutCreateWindow("LCG - Atividade 04 - Robo 3D | por Jeferson W. V. Silva");
    glutReshapeFunc(window_reshape);
    glutDisplayFunc(window_display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboar);

    world1 = glutCreateSubWindow(window, GAP, GAP, 420, 420);
    glutReshapeFunc(world1_reshape);
    glutDisplayFunc(world1_display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboar);

    world2 = glutCreateSubWindow(window, GAP+420+GAP, GAP, 420, 420);
    glutReshapeFunc(world2_reshape);
    glutDisplayFunc(world2_display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboar);

    world3 = glutCreateSubWindow(window, GAP+420+GAP+420+GAP, GAP, 420, 420);
    glutReshapeFunc(world3_reshape);
    glutDisplayFunc(world3_display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboar);

    init();
    glutMainLoop();

    return 0;
}


/*
 * Procedimento que inicializa recursos necessários.
 */
void init(void)
{
    x_foot = 0.0, y_foot = 0.0, z_foot = 0.0;

    eyex = 0.0, eyey = 60.0, eyez = -150;
    upx = 0.0, upy = 1.0, upz = 0.0;
    centerx = 0.0, centery = 60.0, centerz = -50.0;

    y_arm2 = 60.0, y_arm3 = 36.0;

    anglex_arm1 = 0.0, angley_arm1 = 0.0, anglez_arm1 = 0.0;
    anglex_arm2 = -100.0, angley_arm2 = 0.0, anglez_arm2 = 0.0;
    anglex_arm3 = 45.0, angley_arm3 = 0.0, anglez_arm3 = 0.0;
    angle_obj4 = 0.0;
    angle_obj5a = -75.0, angle_obj5b = 15.0;
    angle_arm6 = -60.0;
    angle_arm7 = 0.0;
}


/*
 * Procedimento que redimensiona a janela principal.
 * Parâmetros:
 *  - width: nova largura
 *  - height: nova altura
 */
void window_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutSetWindow(world1);
    glutPositionWindow(GAP, GAP);
    glutReshapeWindow(420, 420);

    glutSetWindow(world2);
    glutPositionWindow(GAP+420+GAP, GAP);
    glutReshapeWindow(420, 420);

    glutSetWindow(world3);
    glutPositionWindow(GAP+420+GAP+420+GAP, GAP);
    glutReshapeWindow(420, 420);

}


/*
 * Procedimento que redesenha os elementos na janela principal.
 */
void window_display(void)
{
    glClearColor(0.8, 0.8, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

/*
 * Procedimento que sincronizadamente redesenha os elementos nos três "mundos" da janela principal.
 */
void redisplay_all(void)
{
    glutSetWindow(world1);
    world1_reshape(420, 420);
    glutPostRedisplay();

    glutSetWindow(world2);
    world2_reshape(420, 420);
    glutPostRedisplay();

    glutSetWindow(world3);
    world3_reshape(420, 420);
    glutPostRedisplay();
}


/*
 * Procedimento que redimensiona o mundo 1.
 * Parâmetros:
 *  - width: nova largura
 *  - height: nova altura
 */
void world1_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble)width/(GLdouble)height, 1.0, 420.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

/*
 * Procedimento que redesenha os elementos no mundo 1.
 */
void world1_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(x_foot, y_foot+8.0, z_foot-20.0,    x_foot, y_foot+50.0, z_foot-50.0,     0.0, 1.0, 0.0);
    drawRobot();
    glutSwapBuffers();
}


/*
 * Procedimento que redimensiona o mundo 2.
 * Parâmetros:
 *  - width: nova largura
 *  - height: nova altura
 */
void world2_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble)width/(GLdouble)height, 1.0, 420.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}


/*
 * Procedimento que redesenha os elementos no mundo 2.
 */
void world2_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(eyex+x_foot, eyey+y_foot, eyez+z_foot,    centerx+x_foot, centery+y_foot, centerz+z_foot,   upx, upy, upz);
    drawRobot();
    glutSwapBuffers();
}


/*
 * Procedimento que redimensiona o mundo 3.
 * Parâmetros:
 *  - width: nova largura
 *  - height: nova altura
 */
void world3_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble)width/(GLdouble)height, 1.0, 420.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}


/*
 * Procedimento que redesenha os elementos no mundo 3.
 */
void world3_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(0.0,  200.0, 50.0,   0.0, 0.0, 0.0,   0.0, 1.0, -1.0);
    drawRobot();
    glutSwapBuffers();
}


/*
 * Procedimento que trata os eventos do teclado, para teclas genéricas.
 * Parâmetros:
 *  - key: código ASCII da tecla pressionada
 *  - x: coordenada x no momento do pressionamento da tecla
 *  - y: coordenada y no momento do pressionamento da tecla
 */
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        /* controle de câmera */
        case '1': eyex++; break;
        case '!': eyex--; break;
        case '2': eyey++; break;
        case '@': eyey--; break;
        case '3': eyez++; break;
        case '#': eyez--; break;
        case '4': centerx++; break;
        case '$': centerx--; break;
        case '5': centery++; break;
        case '%': centery--; break;
        case '6': centerz++; break;
        case 168: centerz--; break;
        case '7': upx++; break;
        case '&': upx--; break;
        case '8': upy++; break;
        case '*': upy--; break;
        case '9': upz++; break;
        case '(': upz--; break;

        /* controles de rotação do braço 1 */
        case 'q': anglex_arm1 = (movementLimitation(-15, 15, --anglex_arm1) ? anglex_arm1 : -15); break;
        case 'Q': anglex_arm1 = (movementLimitation(-15, 15, ++anglex_arm1) ? anglex_arm1 : 15); break;
        case 'a': angley_arm1 = (--angley_arm1 > -360.0) ? angley_arm1 : (int)angley_arm1 % 360; break;
        case 'A': angley_arm1 = (++angley_arm1 < 360.0) ? angley_arm1 : (int)angley_arm1 % 360; break;
        case 'z': anglez_arm1 = (movementLimitation(-15, 15, --anglez_arm1) ? anglez_arm1 : -15); break;
        case 'Z': anglez_arm1 = (movementLimitation(-15, 15, ++anglez_arm1) ? anglez_arm1 : 15); break;

        /* controles de rotação do braço 2 */
        case 'w': anglex_arm2 = (movementLimitation(-110, -70, --anglex_arm2) ? anglex_arm2 : -110); break;
        case 'W': anglex_arm2 = (movementLimitation(-110, -70, ++anglex_arm2) ? anglex_arm2 : -70); break;
        case 's': anglez_arm2 = (--anglez_arm2 > -360.0) ? anglez_arm2 : (int)anglez_arm2 % 360; break;
        case 'S': anglez_arm2 = (++anglez_arm2 < 360.0) ? anglez_arm2 : (int)anglez_arm2 % 360; break;
        case 'x': angley_arm2 = (--angley_arm2 > -360.0) ? angley_arm2 : (int)angley_arm2 % 360; break;
        case 'X': angley_arm2 = (++angley_arm2 < 360.0) ? angley_arm2 : (int)angley_arm2 % 360; break;

        /* controles de rotação do braço 3 */
        case 'e': anglex_arm3 = (movementLimitation(-70, 90, --anglex_arm3) ? anglex_arm3 : -70); break;
        case 'E': anglex_arm3 = (movementLimitation(-70, 90, ++anglex_arm3) ? anglex_arm3 : 90); break;
        case 'd': anglez_arm3 = (movementLimitation(-70, 70, --anglez_arm3) ? anglez_arm3 : -70); break;
        case 'D': anglez_arm3 = (movementLimitation(-70, 70, ++anglez_arm3) ? anglez_arm3 : 70); break;
        case 'c': angley_arm3 = (--angley_arm3 > -360.0) ? angley_arm3 : (int)angley_arm3 % 360; break;
        case 'C': angley_arm3 = (++angley_arm3 < 360.0) ? angley_arm3 : (int)angley_arm3 % 360; break;

        /* controles de rotação da mão do robô */
        case 'f': angle_obj4 = (movementLimitation(-70, 70, --angle_obj4) ? angle_obj4 : -70); break;
        case 'F': angle_obj4 = (movementLimitation(-70, 70, ++angle_obj4) ? angle_obj4 : 70); break;
        case 'v': angle_obj5a = (movementLimitation(-80, -60, --angle_obj5a) ? angle_obj5a : -80);
                  angle_obj5b = (movementLimitation(10, 30, ++angle_obj5b) ? angle_obj5b : 30); break;
        case 'V': angle_obj5a = (movementLimitation(-80, -60, ++angle_obj5a) ? angle_obj5a : -60);
                  angle_obj5b = (movementLimitation(10, 30, --angle_obj5b) ? angle_obj5b : 10); break;
        case 'r': angle_arm6 = (movementLimitation(-60, -40, --angle_arm6) ? angle_arm6 : -60); break;
        case 'R': angle_arm6 = (movementLimitation(-60, -40, ++angle_arm6) ? angle_arm6 : -40); break;
        case 't': angle_arm7 = (movementLimitation(-30, -10, --angle_arm7) ? angle_arm7 : -30); break;
        case 'T': angle_arm7 = (movementLimitation(-30, -10, ++angle_arm7) ? angle_arm7 : -10); break;

        /* controles de translação diagonal do robô no plano xz*/
        case 'p': z_foot = -(++x_foot); break;
        case 'P': z_foot = -(--x_foot); break;
    }
    redisplay_all();
}


/*
 * Procedimento que trata os eventos do teclado, para teclas especiais.
 * Parâmetros:
 *  - key: código ASCII da tecla pressionada
 *  - x: coordenada x no momento do pressionamento da tecla
 *  - y: coordenada y no momento do pressionamento da tecla
 */
void specialKeyboar(int key, int x, int y)
{
    switch (key) {
        /* controles de translação dos braços 2 e 3 */
        case GLUT_KEY_F1: y_arm2 = movementLimitation(40.0, 60.0, --y_arm2) ? y_arm2 : 40.0; break;
        case GLUT_KEY_F2: y_arm2 = movementLimitation(40.0, 60.0, ++y_arm2) ? y_arm2 : 60.0; break;
        case GLUT_KEY_F3: y_arm3 = movementLimitation(20.0, 36.0, --y_arm3) ? y_arm3 : 20.0; break;
        case GLUT_KEY_F4: y_arm3 = movementLimitation(20.0, 36.0, ++y_arm3) ? y_arm3 : 36.0; break;
        /* controles de translação horizontal e vertical do robô no plano zx*/
        case GLUT_KEY_UP: z_foot--; break;
        case GLUT_KEY_DOWN: z_foot++; break;
        case GLUT_KEY_RIGHT: x_foot++; break;
        case GLUT_KEY_LEFT: x_foot--; break;
    }
    redisplay_all();
}


/*
 * Função que avalia limites de movimentação.
 * Parâmetros:
 *  - min: límite mínimo para movimentação
 *  - max: limite máximo para movimentação
 *  - value: valor da movimentação
 * Retorno:
 *  - 1: movimentação é válida
 *  - 0: movimentação é inválida
 */
int movementLimitation(double min, double max, double value)
{
    return (min <= value && value <= max);
}


/*
 * Procedimento que desenha o robô.
 */
void drawRobot(void)
{
    glColor3d(0.0, 0.0, 0.0);

    double p = 6.0;
    double k = 1.5;
    double d = 2.5;
    double b = d;
    double h = 6.0;
    double c = 0.625;

    glTranslated(x_foot, y_foot, z_foot);

    drawWCS();
    drawFoot(d, k, p);
    drawLabel(0.0, 12.51, 0.20*p, 0.25*k);

    glTranslated(0.0, 7.5, 0.0);
    glRotated(anglex_arm1, 1.0, 0.0, 0.0);
    glRotated(angley_arm1, 0.0, 1.0, 0.0);
    glRotated(anglez_arm1, 0.0, 0.0, 1.0);
    drawArm(b, h);
    drawAxis(d);

    glTranslated(0.0, y_arm2, 0.0);
    glRotated(anglex_arm2, 1.0, 0.0, 0.0);
    glRotated(angley_arm2, 0.0, 1.0, 0.0);
    glRotated(anglez_arm2, 0.0, 0.0, 1.0);
    drawArm(0.7*b, 0.6*h);
    drawAxis(0.7*d);
    drawLabel(0.0, 9.0, c, c/3);
    glPushMatrix();
        glRotated(90.0, 1.0, 0.0, 0.0);
        drawLabel(0.0, 9.0, c, c/3);
    glPopMatrix();

    glTranslated(0.0, y_arm3, 0.0);
    glRotated(anglex_arm3, 1.0, 0.0, 0.0);
    glRotated(angley_arm3, 0.0, 1.0, 0.0);
    glRotated(anglez_arm3, 0.0, 0.0, 1.0);
    drawArm(0.5*b, 0.4*h);
    drawAxis(0.5*d);
    drawLabel(0.0, 6.5, 0.7*c, 0.7*(c/3));
    glPushMatrix();
        glRotated(90.0, 1.0, 0.0, 0.0);
        drawLabel(0.0, 6.5, 0.7*c, 0.7*(c/3));
    glPopMatrix();

    glTranslated(0.0, 24.0, 0.0);
    glRotated(angle_obj4, 0.0, 0.0, 1.0);

    glPushMatrix();
        glRotated(angle_obj5a, 1.0, 0.0, 0.0);
        drawObj(7.5, 0.3*k, 0.3*k, 0.2*p);
        glTranslated(0.0, 0.0, 12.0);
        glRotated(-angle_obj5a, 1.0, 0.0, 0.0);
        glRotated(angle_arm6, 1.0, 0.0, 0.0);
        drawArm(0.2*b, 0.2*h);
        drawAxis(0.3*d);
    glPopMatrix();

    glPushMatrix();
        glRotated(angle_obj5b, 1.0, 0.0, 0.0);
        drawObj(-7.5, 0.3*k, 0.3*k, 0.2*p);
        glTranslated(0.0, 0.0, -12.0);
        glRotated(-angle_obj5b, 1.0, 0.0, 0.0);
        glRotated(angle_arm7, 1.0, 0.0, 0.0);
        drawArm(0.2*b, 0.2*h);
        drawAxis(0.3*d);
    glPopMatrix();

    drawAxis(0.35*d);

}


/*
 * Procedimento que desenha a base do SRU, a fim de dar suporte ao entendimento.
 */
void drawWCS(void)
{
    glPushMatrix();
        glTranslated(50.0, 0.0, 0.0);
        glPointSize(10.0);
        glBegin(GL_POINTS);
            glVertex3d(0.0, 0.0, 0.0);
        glEnd();
    glPopMatrix();

    glLineWidth(2.0);
    glPushMatrix();
        glTranslated(50.0, 0.0, 0.0);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
            glVertex3d(0.0, 0.0, 0.0);
            glVertex3d(0.0, 0.0, 50.0);
        glEnd();
        glTranslated(0.0, 0.0, 50.0);
        glutSolidCone(2.5, 7.5, 100.0, 100.0);
        glRasterPos3f(2.0, 0.0, 0.0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'z');
    glPopMatrix();

    glPushMatrix();
        glTranslated(50.0, 0.0, 0.0);
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
            glVertex3d(0.0, 0.0, 0.0);
            glVertex3d(0.0, 50.0, 0.0);
        glEnd();
        glTranslated(0.0, 50.0, 0.0);
        glRotated(-90.0, 1.0, 0.0, 0.0);
        glutSolidCone(2.5, 7.5, 100.0, 100.0);
        glRasterPos3f(3.0, 0.0, 0.0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'y');
    glPopMatrix();

    glPushMatrix();
        glTranslated(50.0, 0.0, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINES);
            glVertex3d(0.0, 0.0, 0.0);
            glVertex3d(50.0, 0.0, 0.0);
        glEnd();
        glTranslated(50.0, 0.0, 0.0);
        glRotated(90.0, 0.0, 1.0, 0.0);
        glutSolidCone(2.5, 7.5, 100.0, 100.0);
        glRasterPos3f(3.0, 0.0, 0.0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'x');
    glPopMatrix();
}


/*
 * Procedimento que desenha um cubo escalonado no formato de paralelepípedo para a base do robô.
 * Parâmetros:
 *  - d: fator de escala em x
 *  - k: fator de escala em y
 *  - p: fator de escala em z
 */
void drawFoot(double d, double k, double p)
{
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
        glScaled(d, k, p);
        glutSolidCube(10);
    glPopMatrix();
}


/*
 * Procedimento que desenha um cone escalonado que forma um braço do robô.
 * Parâmetros:
 *  - b: fator de escala em x e z
 *  - h: fator de escala em y
 */
void drawArm(double b, double h)
{
    glColor3f(1.0, 0.5, 1.0);
    glPushMatrix();
        glRotated(-90.0, 1.0, 0.0, 0.0); /* altura do cone passa a ser o eixo y*/
        glScaled(b/2, b/2, h);
        glutSolidCone(10, 10, 100.0, 100.0);
    glPopMatrix();
}


/*
 * Procedimento que desenha uma esfera escalonada que forma um cotôvelo do robô.
 * Parâmetro:
 *  - d: fator de escala em x, y e z
 */
void drawAxis(double d)
{
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
        glScaled(d, d, d);
        glutSolidSphere(5.0, 100.0, 100.0);
    glPopMatrix();
}


/*
 * Procedimento que desenha um retângulo escalonado que forma o rótulo ( – )
 * Parâmetros:
 *  - angle: ângulo do rótulo
 *  - tx: translação em relação a x para posicionar o rótulo corretamente
 *  - p: fator de escala em z
 *  - k: fator de escala em y
 */
void drawLabel(double angle, double tx, double p, double k)
{
    glColor3d(0.0, 0.0, 1.0);
    glPushMatrix();
        glTranslated(tx, 0.0, 0.0);
        glRotated(90, 0.0, 1.0, 0.0);
        glScaled(p, k, 0.0);
        glRectf(-5.0, -5.0, 5.0, 5.0);
    glPopMatrix();
}


/*
 * Procedimento que desenha um cubo escalonado do formato de um paralelepípedo.
 * Parâmetros:
 *  - tz: translação em z para posicionar corretamente o desenho
 *  - d: fator de escala em x
 *  - k: fator de escala em y
 *  - p: fator de escala em z
 */
void drawObj(double tz, double d, double k, double p)
{
    glColor3f(1.0, 0.5, 1.0);
    glPushMatrix();
        glTranslated(0.0, 0.0, tz);
        glScaled(d, k, p);
        glutSolidCube(10);
    glPopMatrix();
}
