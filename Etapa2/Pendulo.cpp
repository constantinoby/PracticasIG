// Etapa1.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
const int W_WIDTH = 500; // Tama�o incial de la ventana
const int W_HEIGHT = 500;

const float g = 9.8;

GLfloat alpha = 1;
GLfloat beta = 1;
float massAlpha = 1;
float massBeta = 2;
float lenghtAlpha = 1;
float lenghtBeta = 1;
float alphaIncrement = 0.03f;
float betaIncrement = 0.03f;

float predictAlpha() {
	float aux = -g * (2 * massAlpha + massBeta) * sin(alpha) - massBeta * g * sin(alpha - 2 * beta);
	float aux2 = -2 * sin(alpha - beta) * massBeta * ((beta * beta) * lenghtBeta + (alpha * alpha) * lenghtAlpha * cos(alpha - beta));
	float aux3 = lenghtAlpha * (2 * massAlpha + massBeta - massBeta * cos(2 * alpha - 2 * beta));
	float result = (aux + aux2) / (aux3);
	return result;
}

float predictBeta() {
	float aux = 2 * sin(alpha - beta) * ((alpha * alpha) * lenghtAlpha * (massAlpha + massBeta) 
		+ g * (massAlpha + massBeta) * cos(alpha) +(beta * beta)*lenghtBeta*massBeta*cos(alpha - beta));
	float aux2 = lenghtBeta * (2 * massAlpha + massBeta - massBeta * cos(2 * alpha - 2 * beta));
	float result = aux / aux2;
	return result;
}

void drawDoblePendulum() {
	//pendulo principal
	glPushMatrix();
	glRotatef(alpha, 0.0f, 0.0f, -1.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glEnd();
	glPushMatrix();
	glTranslatef(1.0f, 0.0f, 0.0f);
	glScalef(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 1.0f, 1.0f);
	for (int i = 0; i < 360; i++) {
		float x = cos(i * 3.14159 / 180.0);
		float y = sin(i * 3.14159 / 180.0);
		glVertex2f(x, y);
	}
	glEnd();
	//reescalamos al tamaño original
	glScalef(10.0f, 10.0f, 10.0f);
	//péndulo secundario
	glPushMatrix();
	glRotatef(alpha, 0.0f, 0.0f, -1.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glEnd();
	glPushMatrix();
	glTranslatef(1.0f, 0.0f, 0.0f);
	glScalef(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 1.0f, 1.0f);
	for (int i = 0; i < 360; i++) {
		float x = cos(i * 3.14159 / 180.0);
		float y = sin(i * 3.14159 / 180.0);
		glVertex2f(x, y);
	}
	glEnd();
	//descargamos todas las matrices usadas
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawDoblePendulum();
	glutSwapBuffers();
}

void reshape(int width, int height) {
	//un print de width y height para ver que valores se reciben
	printf(" Pendulo = width: %d, height: %d\n", width, height);

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void idle() {
	//printf("%f", alpha);
	//alpha += alphaIncrement;
	//beta += betaIncrement;
	// Si es mayor que dos pi la decrementamos
	/*if (alpha > 180 || alpha < 0) {
		alphaIncrement = -alphaIncrement;
	}
	if (beta > 180 || beta < 0) {
		betaIncrement = -betaIncrement;
	}*/
	/*printf("Esto vale alpha %f    ------------    ", alpha);
	float nextAlpha = predictAlpha();
	int alphaInt = nextAlpha;
	alphaInt = alphaInt % 360;

	float nextBeta = predictBeta();
	int betaInt = nextAlpha;
	betaInt = betaInt % 360;
	alpha = alphaInt;
	beta = betaInt;
	printf("Ahora vale %f   ||||||||", alpha);*/

	//beta = nextBeta;
	//glutPostRedisplay();
	//glutSwapBuffers();
}

void timer(int iUnused) {
	printf("Esto vale alpha %f    ------------    ", alpha);
	float nextAlpha = predictAlpha();
	float nextBeta = predictBeta();
	alpha = nextAlpha;
	beta = nextBeta;
	while (alpha >= 360) {
		alpha -= 360;
	}
	while (alpha < 0) {
		alpha += 360;
	}
	while (beta >= 360) {
		beta -= 360;
	}
	while (beta < 0) {
		beta += 360;
	}
	printf("Ahora vale %f   ||||||||", alpha);
	glutPostRedisplay();
	glutTimerFunc(300, timer, 0);
}

int main(int argc, char** argv) {
	// Inicializamos la librer�a GLUT
	glutInit(&argc, argv);
	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	// Creamos la nueva ventana
	glutCreateWindow("Pendulo");
	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
	timer(0);
	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}