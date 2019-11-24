#include <GL/glut.h>
#include <iostream>


static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

int main(int argc, char **argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	
	glutDisplayFunc(on_display);
// 	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);
	
	glClearColor(0.75, 0.75, 0.75, 0);
	
	glClearColor(0, 0, 0, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

	GLfloat light_diffuse[] = { 1, 0.8, 1, 1 };
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	
	glutMainLoop();
	
	return 0;
}

static void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (float) width / height, 1, 100);
}

static void on_display(void)
{
    /* Postavlja se boja svih piksela na zadatu boju pozadine. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat light_position[] = { 0, 0.5, 0, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	glPushMatrix();
	glColor3f(0,1,1);
	glutWireSphere(0.4, 10, 10);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0,0,1);
	glTranslatef(0,-0.01,0);
	glRotatef(15,0,0,1);
	glutWireSphere(0.4, 10, 10);
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1,1,1);
	glVertex3f(5,1,1);
	glEnd();
	glPopMatrix();
	
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;
	case 'w':
	case 'W':
		printf("A");
		break;
	}
}
