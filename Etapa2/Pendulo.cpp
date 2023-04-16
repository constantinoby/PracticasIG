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

const float g = 9.8f;
const float pi = 3.1415f;

GLfloat alpha = 28.64f;
GLfloat beta = 57.29f;
float massAlpha = 1.0f;
float massBeta = 2.0f;
float lenghtAlpha = 1.0f;
float lenghtBeta = 1.0f;
float alphaIncrement = 0.03f;
float betaIncrement = 0.03f;

float gradsToRads(float grads) {
	return (grads * pi) / 180;
}

float radsToGrads(float rads) {
	return (rads * 180) / pi;
}

float predictAlpha() {
	float alphaRad = gradsToRads(alpha);
	float betaRad = gradsToRads(beta);
	float aux = (- g) * (2 * massAlpha + massBeta) * sin(alphaRad) - massBeta * g * sin(alphaRad + (- 2) * betaRad);
	float aux2 = (- 2) * sin(alphaRad - betaRad) * massBeta * ((betaRad * betaRad) * lenghtBeta + (alphaRad * alphaRad) * lenghtAlpha * cos(alphaRad - betaRad));
	float aux3 = lenghtAlpha * (2 * massAlpha + massBeta - massBeta * cos(2 * alphaRad - 2 * betaRad));
	float result = (aux + aux2) / (aux3);
	return radsToGrads(result);
}

float predictBeta() {
	float alphaRad = gradsToRads(alpha);
	float betaRad = gradsToRads(beta);
	float aux = 2 * sin(alphaRad - betaRad) * ((alphaRad * alphaRad) * lenghtAlpha * (massAlpha + massBeta)
		+ g * (massAlpha + massBeta) * cos(alphaRad) +(betaRad * betaRad)*lenghtBeta*massBeta*cos(alphaRad - betaRad));
	float aux2 = lenghtBeta * (2 * massAlpha + massBeta - massBeta * cos(2 * alphaRad - 2 * betaRad));
	float result = aux / aux2;
	return radsToGrads(result);
}

void drawDoblePendulum() {
	//pendulo principal
	glPushMatrix();
	glRotatef(alpha, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, -1.0f);
	glEnd();
	glPushMatrix();
	glTranslatef(0.0f, -1.0f, 0.0f);
	glScalef(0.1f, 0.1f, 0.1f);
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 1.0f, 1.0f);
	for (int i = 0; i < 360; i++) {
		float x = cos(i * 3.14159f / 180.0f);
		float y = sin(i * 3.14159f / 180.0f);
		glVertex2f(x, y);
	}
	glEnd();
	//reescalamos al tamaño original
	glScalef(10.0f, 10.0f, 10.0f);
	//péndulo secundario
	glPushMatrix();
	glRotatef(beta - alpha, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, -1.0f);
	glEnd();
	glPushMatrix();
	glTranslatef(0.0f, -1.0f, 0.0f);
	glScalef(0.1f, 0.1f, 0.1f);
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
	printf("Esto vale alpha %f    ------------    ", alpha);
	float nextAlpha = predictAlpha();
	float nextBeta = predictBeta();
	while (nextAlpha >= 360) {
		nextAlpha -= 360;
	}
	while (nextAlpha < 0) {
		nextAlpha += 360;
	}
	while (nextBeta >= 360) {
		nextBeta -= 360;
	}
	while (nextBeta < 0) {
		nextBeta += 360;
	}
	//nextAlpha = (nextAlpha - alpha) / 10;
	//nextBeta = (nextBeta - beta) / 10;
	alpha = nextAlpha;
	beta = nextBeta;
	printf("Ahora vale %f   ||||||||", alpha);
	glutPostRedisplay();
}

void timer(int iUnused) {
	idle();
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
	//timer(0);
	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}