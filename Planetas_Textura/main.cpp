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

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

GLfloat distance = 0;
GLfloat azimuth = 0;
GLfloat incidence = 0;
GLfloat twist = 0;

// Variável Global para ID de Textura
GLuint id[10];
/*
0 - sol
1 - merc
2 - venus
3 - terra
4 - marte
5 - jupiter
6 - saturno
7 - urano
8 - netuno
9 - lua terra
*/
void createTexture(int i, char* path)
{
    // Carrega uma imagem
    SDL_Surface* image = IMG_Load(path);
    if (!image)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        return;
    }

    //Criamos 1 objeto de textura e obtemos seu id
    glGenTextures(1, (id+i));

    //Dizemos a OpenGL que iremos trabalhar com o objeto.
    glBindTexture(GL_TEXTURE_2D, *(id+i));

    //Filtro
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //Descobrimos o formato a partir da imagem
    GLint format =image->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA;

    //Carregamos a imagem do disco
    glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

    //Como a OpenGL copiou a imagem, apagamos a SDL_Image.
    SDL_FreeSurface(image);
}

void drawSphere(GLfloat radius , GLfloat slices, GLfloat stacks)
{
	GLUquadric *quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluQuadricTexture(quadObj, true); // Habilita aplica��o de textura
	gluSphere(quadObj, radius, stacks, slices);
}

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
    glColor3f(1.0, 1.0, 1.0);

    // Sol
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *(id+0));
    glPushMatrix();
    drawSphere(10,20,20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_dark);

    /* Desenhando o Sistema Solar */
    // Mercúrio
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *(id+1));
    glPushMatrix();
    glRotated(a, 0, 1, 0);
    glTranslatef(distancia_planetas,0,0);
    drawSphere(1, 20, 20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Vênus
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *(id+2));
    glPushMatrix();
    glRotated(a/2, 0, 1, 0);
    glTranslatef(distancia_planetas+5,0,0);
    drawSphere(2, 20, 20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Terra
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *(id+3));
    glPushMatrix();
    glRotated(a/3, 0, 1, 0);
    glTranslatef(distancia_planetas+10,0,0);
    drawSphere(1.6, 20, 20);
    glDisable(GL_TEXTURE_2D);
    // Lua
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *(id+9));
    glRotated(a/3, 0, 1, 0);
    glTranslatef(3,0,0);
    drawSphere(0.5, 20, 20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Marte
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *(id+4));
    glRotated(a/4, 0, 1, 0);
    glTranslatef(distancia_planetas+15,0,0);
    drawSphere(1.4, 20, 20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Júpiter
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *(id+5));
    glRotated(a/5, 0, 1, 0);
    glTranslatef(distancia_planetas+25,0,0);
    drawSphere(5, 20, 20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Saturno
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *(id+6));
    glRotated(a/6, 0, 1, 0);
    glTranslatef(distancia_planetas+37,0,0);
    drawSphere(2.2, 20, 20);
    glDisable(GL_TEXTURE_2D);
    // Anéis
    glColor3f(1.0, 1.0, 1.0);
    glScaled(1,0.3,1);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(2, 5, 15, 15);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    // Urano
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *(id+7));
    glRotated(a/7, 0, 1, 0);
    glTranslatef(distancia_planetas+45,0,0);
    drawSphere(2.1, 20, 20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Netuno
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *(id+8));
    glRotated(a/8, 0, 1, 0);
    glTranslatef(distancia_planetas+50,0,0);
    drawSphere(1.9, 20, 20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

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

    glEnable(GL_TEXTURE_2D);
    createTexture(0, "C:\\Users\\ander\\Desktop\\Workspace Codeblocks\\Planetas_Textura\\sunmap.jpg");
    createTexture(1, "C:\\Users\\ander\\Desktop\\Workspace Codeblocks\\Planetas_Textura\\mercurymap.jpg");
    createTexture(2, "C:\\Users\\ander\\Desktop\\Workspace Codeblocks\\Planetas_Textura\\venusmap.jpg");
    createTexture(3, "C:\\Users\\ander\\Desktop\\Workspace Codeblocks\\Planetas_Textura\\earthmap1k.jpg");
    createTexture(4, "C:\\Users\\ander\\Desktop\\Workspace Codeblocks\\Planetas_Textura\\mars_1k_color.jpg");
    createTexture(5, "C:\\Users\\ander\\Desktop\\Workspace Codeblocks\\Planetas_Textura\\jupitermap.jpg");
    createTexture(6, "C:\\Users\\ander\\Desktop\\Workspace Codeblocks\\Planetas_Textura\\saturnmap.jpg");
    createTexture(7, "C:\\Users\\ander\\Desktop\\Workspace Codeblocks\\Planetas_Textura\\uranusmap.jpg");
    createTexture(8, "C:\\Users\\ander\\Desktop\\Workspace Codeblocks\\Planetas_Textura\\neptunemap.jpg");
    createTexture(9, "C:\\Users\\ander\\Desktop\\Workspace Codeblocks\\Planetas_Textura\\moonmap1k.jpg");

    /* Main loop */
    glutMainLoop();

    return 0;
}
