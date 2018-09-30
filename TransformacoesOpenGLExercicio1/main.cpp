/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;
static double angle = 0.0;
GLfloat distance = 0;
GLfloat azimuth = 0;
GLfloat incidence = 0;
GLfloat twist = 0;

/*
void polarView()
{
    glTranslatef(0.0, 0.0, -distance);
    glRotatef(-twist, 0.0, 0.0, 1.0);
    glRotatef(-incidence, 1.0, 0.0, 0.0);
    glRotatef(-azimuth, 0.0, 0.0, 1.0);
}
*/

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glPushMatrix();
    //polarView();

    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
        glRotatef(angle, 1.0, 0.0, 0.0);
        glBegin(GL_LINES);
            glVertex3d(-5, -5, 0);
            glVertex3d(-5, 5, 0);

            glVertex3d(-3, -5, 0);
            glVertex3d(-3, 5, 0);

            glVertex3d(-1, -5, 0);
            glVertex3d(-1, 5, 0);

            glVertex3d(1, -5, 0);
            glVertex3d(1, 5, 0);

            glVertex3d(3, -5, 0);
            glVertex3d(3, 5, 0);

            glVertex3d(5, -5, 0);
            glVertex3d(5, 5, 0);

            glVertex3d(5, 5, 0);
            glVertex3d(-5, 5, 0);

            glVertex3d(5, 3, 0);
            glVertex3d(-5, 3, 0);

            glVertex3d(5, 1, 0);
            glVertex3d(-5, 1, 0);

            glVertex3d(5, -1, 0);
            glVertex3d(-5, -1, 0);

            glVertex3d(5, -3, 0);
            glVertex3d(-5, -3, 0);

            glVertex3d(5, -5, 0);
            glVertex3d(-5, -5, 0);
        glEnd();
    glPopMatrix();

    glutSwapBuffers();
}


static void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;

    case '+':
        angle+=10;
        break;

    case '-':
        angle-=10;
        break;

    case 'p':
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30, 1, 1, 500);
        //glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 25.0);
        gluLookAt(0, 0, 30,    0, 0, 0,    0, 1, 0);
        glMatrixMode(GL_MODELVIEW);
        break;

    case 'o':
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //gluPerspective(30, 1, 1, 500);
        glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 25.0);
        gluLookAt(0, 0, 20,    0, 0, 0,    0, 1, 0);
        glMatrixMode(GL_MODELVIEW);
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


void init()
{
    /* Selecionar cor de fundo (preto) */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* Inicializar sistema de visualizacao */
    glMatrixMode(GL_PROJECTION);
    //gluPerspective(30, 1, 1, 500);
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 25.0);
    gluLookAt(0, 0, 20,    0, 0, 0,    0, 1, 0);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char *argv[])
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

    return EXIT_SUCCESS;
}
