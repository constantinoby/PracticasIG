#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

const int W_WIDTH = 600; // Tama�o incial de la ventana
const int W_HEIGHT = 600;
GLfloat fAngulo; // Variable que indica el �ngulo de rotaci�n de los ejes. 

void sol() {
	glPushMatrix();

	glScalef(0.75, 0.75, 0.75);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.5f, 0.0f);
	for (int i = 0; i < 360; i++)
	{
		float x = cos(i * 3.14159 / 180.0);
		float y = sin(i * 3.14159 / 180.0);
		glVertex2f(x, y);
	}
	glEnd();

	glPopMatrix();
}

void planeta1() {
	glPushMatrix();

	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
	glTranslatef(-2.6, 0.0f, 0.0f);
	glScalef(0.3, 0.3, 0.3);
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 1.0f, 1.0f);
	for (int i = 0; i < 360; i++)
	{
		float x = cos(i * 3.14159 / 180.0);
		float y = sin(i * 3.14159 / 180.0);
		glVertex2f(x, y);
	}
	glEnd();

	glPopMatrix();
}

void planeta2() {
	glPushMatrix();

	glRotatef(2*fAngulo, 0.0f, 0.0f, 1.0f);
	glTranslatef(-1.4, 0.0f, 0.0f);
	glScalef(0.25, 0.25, 0.25);
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 0.5f);
	for (int i = 0; i < 360; i++)
	{
		float x = cos(i * 3.14159 / 180.0);
		float y = sin(i * 3.14159 / 180.0);
		glVertex2f(x, y);
	}
	glEnd();

	glPopMatrix();
}

void planeta3() {
	glPushMatrix();

	glRotatef((3*fAngulo), 0.0f, 0.0f, 1.0f);
	glTranslatef(-2, 0.0f, 0.0f);
	glScalef(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < 360; i++)
	{
		float x = cos(i * 3.14159 / 180.0);
		float y = sin(i * 3.14159 / 180.0);
		glVertex2f(x, y);
	}
	glEnd();

	glPopMatrix();
}

void planeta4() {
	glPushMatrix();

	glRotatef(-fAngulo, 0.0f, 0.0f, 1.0f);
	glTranslatef(-1, 0.0f, 0.0f);
	glScalef(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.1f, 0.1f);
	for (int i = 0; i < 360; i++)
	{
		float x = cos(i * 3.14159 / 180.0);
		float y = sin(i * 3.14159 / 180.0);
		glVertex2f(x, y);
	}
	glEnd();

	glPopMatrix();
}

void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);


	sol();

	planeta1();

	planeta2();

	planeta3();


	planeta4();

	glFlush();
}


// Función que se ejecuta cuando se redimensiona la ventana
void reshape(int width, int height) {
	//un print de width y height para ver que valores se reciben
	printf(" Etapa 2 = width: %d, height: %d\n", width, height);

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


// Funci�n que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	// Incrementamos el �ngulo
	fAngulo += 0.03f;
	// Si es mayor que dos pi la decrementamos
	if (fAngulo > 360)
		fAngulo -= 360;
	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
	glutSwapBuffers();

}

// Funci�n principal
int main(int argc, char** argv)
{
	// Inicializamos la librer�a GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);


	// Creamos la nueva ventana
	glutCreateWindow("Mi Sistema Solar");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	glutReshapeFunc(reshape);



	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}
