#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

GLfloat distance = 0;
GLfloat azimuth = 0;
GLfloat incidence = 0;
GLfloat twist = 0;

void polarView()
{
    glTranslatef(0.0, 0.0, -distance);
    glRotatef(-twist, 0.0, 0.0, 1.0);
    glRotatef(-incidence, 1.0, 0.0, 0.0);
    glRotatef(-azimuth, 0.0, 0.0, 1.0);
}

void display()
{
    const double a = glutGet(GLUT_ELAPSED_TIME) / 10.0;
    const double distancia_planetas = 15;
    const double rotacao_planetas = 0.5;
    GLfloat mat_dark[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_yellowEmission[] = {0.6, 0.6, 0.0, 1.0};
    GLfloat mat_shininess = 100.0;
    GLfloat lightPosition[] = {0, 0, 0};

    /* Limpar todos os pixels  */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    polarView();

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_dark);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_yellowEmission);

    // Sol
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(10, 20, 20);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_dark);


    /* Desenhando o Sistema Solar */
    // Mercúrio
    glPushMatrix();
    glColor3f(0.8, 0.7, 0.0);
    glRotated(a, 0, 1, 0);
    glTranslatef(distancia_planetas,0,0);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();

    // Vênus
    glPushMatrix();
    glColor3f(0.9, 0.8, 0.4);
    glRotated(a/2, 0, 1, 0);
    glTranslatef(distancia_planetas+5,0,0);
    glutSolidSphere(2, 20, 20);
    glPopMatrix();

    // Terra
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.5);
    glRotated(a/3, 0, 1, 0);
    glTranslatef(distancia_planetas+10,0,0);
    glutSolidSphere(1.6, 20, 20);
    // Lua
    glColor3f(1.0, 1.0, 1.0);
    glRotated(a/3, 0, 1, 0);
    glTranslatef(3,0,0);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    // Marte
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.2);
    glRotated(a/4, 0, 1, 0);
    glTranslatef(distancia_planetas+15,0,0);
    glutSolidSphere(1.4, 20, 20);
    glPopMatrix();

    // Júpiter
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.6);
    glRotated(a/5, 0, 1, 0);
    glTranslatef(distancia_planetas+25,0,0);
    glutSolidSphere(5, 20, 20);
    glPopMatrix();

    // Saturno
    glPushMatrix();
    glColor3f(0.9, 0.9, 0.5);
    glRotated(a/6, 0, 1, 0);
    glTranslatef(distancia_planetas+37,0,0);
    glutSolidSphere(2.2, 20, 20);
    // Anéis
    glColor3f(1.0, 1.0, 1.0);
    glScaled(1,0.3,1);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(2, 5, 15, 15);
    glPopMatrix();

    // Urano
    glPushMatrix();
    glColor3f(0.6, 0.9, 0.9);
    glRotated(a/7, 0, 1, 0);
    glTranslatef(distancia_planetas+45,0,0);
    glutSolidSphere(2.1, 20, 20);
    glPopMatrix();

    // Netuno
    glPushMatrix();
    glColor3f(0.2, 0.4, 0.9);
    glRotated(a/8, 0, 1, 0);
    glTranslatef(distancia_planetas+50,0,0);
    glutSolidSphere(1.9, 20, 20);
    glPopMatrix();


    glPopMatrix();

    /* Trocar buffers - double-buffering */
    glutSwapBuffers();
}

void myKeyboard(unsigned char c, int x, int y)
{
    switch(c)
    {
    case 'a':
        azimuth += 5;
        break;
    case 'd':
        azimuth -= 5;
        break;
    case 'w':
        incidence += 5;
        break;
    case 's':
        incidence -= 5;
        break;
    case 'z':
        distance -= 1;
        break;
    case 'x':
        distance += 1;
        break;
    case 'q':
        twist += 5;
        break;
    case 'e':
        twist -= 5;
        break;
    }
    glutPostRedisplay();
}

void init()
{
    /* Selecionar cor de fundo (preto) */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* Inicializar sistema de visualizacao */
    glMatrixMode(GL_PROJECTION);
    gluPerspective(30, 1, 1, 500);
    gluLookAt(0, 0, 250,    0, 0, 0,    0, 1, 0);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void idle()
{
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    /* Incializacao */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    init();

    /* Callbacks */
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboard);

    /* Main loop */
    glutMainLoop();

    return 0;
}
