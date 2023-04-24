#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

const int W_WIDTH = 600; // Tama�o incial de la ventana
const int W_HEIGHT = 600;
GLfloat fAngulo; // Variable que indica el �ngulo de rotaci�n de los ejes. 
int figura = 0;

void DrawAxes()
{
	glPushMatrix();
	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
	// Eje X
	glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
	glBegin(GL_LINES);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glEnd();

	// Eje Y
	glColor3f(0.0f, 1.0f, 0.0f); // Color verde
	glBegin(GL_LINES);
	glVertex3f(0.0f, -10.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();

	// Eje Z
	glColor3f(0.0f, 0.0f, 1.0f); // Color azul
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);
	glEnd();

	glPopMatrix();
}




void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawAxes();


	switch (figura) {
	case 1:

		glPushMatrix();
		glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
		glColor3f(0.5, 0.5, 0.5);
		glutWireTeapot(5); // Dibuja un teapot sólido con un radio de 0.5 unidades
		glPopMatrix();
		break;
	case 2:
		glPushMatrix();
		glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
		glColor3f(0.5, 0.5, 0.5);
		glutWireCone(5, 5, 5, 5); // Dibuja un teapot sólido con un radio de 0.5 unidades
		glPopMatrix();
		break;
	case 3:
		//DrawAxes();
		break;
	default:
		break;
	}



	glFlush();
}


// Función que se ejecuta cuando se redimensiona la ventana
void reshape(int width, int height) {
	//un print de width y height para ver que valores se reciben
	//printf(" Etapa 2 = width: %d, height: %d\n", width, height);

	printf(" Etapa 3 = width: %d, height: %d\n", width, height);

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Reemplazamos gluPerspective por glFrustum
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void teclas(unsigned char key, int x, int y) {


	switch (key) {
	case '1':
		figura = 1;
		break;
	case '2':
		figura = 2;
		break;
	case '3':
		figura = 3;
		break;
	default:
		figura = 0;
		break;
	}

	//switch (key) {
	//case 'q': // 
	//	printf("UN");
	//	glPushMatrix();
	//	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
	//	glColor3f(0.5, 0.5, 0.5);
	//	glutWireTeapot(5); // Dibuja un teapot sólido con un radio de 0.5 unidades
	//	glPopMatrix();
	//	break;

	//case '2':
	//	printf("DOS");
		//glPushMatrix();
		//glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
		//glColor3f(0.5, 0.5, 0.5);
		//glutWireCone(5,5,5,5); // Dibuja un teapot sólido con un radio de 0.5 unidades
		//glPopMatrix();
	//}
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

	glutKeyboardFunc(teclas);



	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}