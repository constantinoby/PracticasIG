#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

const int W_WIDTH = 600; // Tama�o incial de la ventana
const int W_HEIGHT = 600;
int ancho = W_WIDTH;
int alto = W_HEIGHT;
GLfloat fAngulo; // Variable que indica el �ngulo de rotaci�n de los ejes. 
int figura = 0;
bool ejes=true;
bool solid = false;
bool planes = false;
bool ortho = true;

void drawAxes() {
	glPushMatrix();
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

void drawPlanes() {
	float size = 10.0f;
	glPushMatrix();
	//glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
	// Plano X - Y
	glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
	glBegin(GL_QUADS);
	glVertex3f(-size, size, 0.0f);
	glVertex3f(-size, -size, 0.0f);
	glVertex3f(size, -size, 0.0f);
	glVertex3f(size, size, 0.0f);
	glEnd();

	// Plano X - Z
	glColor3f(0.0f, 1.0f, 0.0f); // Color verde
	glBegin(GL_QUADS);
	glVertex3f(-size, 0.0f, size);
	glVertex3f(-size, 0.0f, -size);
	glVertex3f(size, 0.0f, -size);
	glVertex3f(size, 0.0f, size);
	glEnd();

	// Plano Y - Z
	glColor3f(0.0f, 0.0f, 1.0f); // Color azul
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -size, size);
	glVertex3f(0.0f, -size, -size);
	glVertex3f(0.0f, size, -size);
	glVertex3f(0.0f, size, size);
	glEnd();
	glPopMatrix();
}

void display(void) {
	// Borramos la escena
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (ejes) {
		drawAxes();
	}

	if (planes) {
		drawPlanes();
	}

	switch (figura) {
	case 1:
		glPushMatrix();
		glRotatef(fAngulo, 0.0f, 1.0f, 0.0f);
		glColor3f(0.5, 0.5, 0.5);
		if (solid) {
			glutSolidTeapot(5); // Dibuja un teapot sólido con un radio de 0.5 unidades
		} else {
			glutWireTeapot(5); // Dibuja un teapot delineado con un radio de 0.5 unidades
		}
		glPopMatrix();
		break;
	case 2:
		glPushMatrix();
		glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
		glColor3f(0.5, 0.5, 0.5);
		if (solid) {
			glutSolidCone(5, 5, 5, 5); // Dibuja un cono sólido con un radio de 0.5 unidades
		} else {
			glutWireCone(5, 5, 5, 5); // Dibuja un cono delineado con un radio de 0.5 unidades
		}
		glPopMatrix();
		break;
	case 3:
		glPushMatrix();
		glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.5f, 0.0f);
		glScalef(5.0f, 5.0f, 5.0f);
		if (solid) {
			glutSolidTetrahedron();
		} else {
			glutWireTetrahedron();
		}
		glPopMatrix();
		break;
	case 4:
		glPushMatrix();
		glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
		glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
		if (solid) {
			glutSolidCube(5);// Dibuja un cubo sólido con un tamaño de 0.5
		} else {
			glutWireCube(5);// Dibuja un cubo delineado con un tamaño de 5
		}
		glPopMatrix();
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
	ancho = width;
	alto = height;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ratio = (float)width / (float)height;

	if (ortho) {
		glOrtho(-10.f * ratio, 10.0f * ratio, -10.0f, 10.0f, -1.0f, 100.0f);
	} else {
		glFrustum(-1.0 * ratio, 1.0f * ratio, -1.0, 1.0f, 1.0f, 500.0f);
	}
	printf("L plus ratio = %f \n", ratio);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void userInput(unsigned char key, int x, int y) {
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
		case '4':
			figura = 4;
			break;
		case 'e':
			ejes = !ejes;
			break;
		case 'p':
			planes = !planes;
			break;
		case 's':
			solid = !solid;
			break;
		case 'o':
			ortho = !ortho;
			reshape(ancho, alto);
			break;
		default:
			figura = 0;
			break;
	}
}

// Funci�n que se ejecuta cuando el sistema no esta ocupado
void idle(void) {
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
int main(int argc, char** argv) {
	// Inicializamos la librer�a GLUT
	glutInit(&argc, argv);
	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Etapa 3");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(userInput);

	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}