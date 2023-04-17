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
const float pi = 3.14159265358979323846f;

GLfloat alpha = 28.64f;
GLfloat beta = 57.29f;
const float massAlpha = 1.0f;
const float massBeta = 2.0f;
const float lenghtAlpha = 1.0f;
const float lenghtBeta = 1.0f;
float velAlpha = 0.0f;
float velBeta = 0.0f;
const float dt = 0.1f;
const float coefRoz = 0.1f;

float gradsToRads(float grads) {
	return (grads * pi) / 180;
}

float radsToGrads(float rads) {
	return (rads * 180) / pi;
}

float predictAccAlpha() {
	float alphaRad = gradsToRads(alpha);
	float betaRad = gradsToRads(beta);
	float aux = (float)((- g) * (2 * massAlpha + massBeta) * sin(alphaRad) - massBeta * g * sin(alphaRad + (- 2) * betaRad));
	float aux2 = (float)((- 2) * sin(alphaRad - betaRad) * massBeta * ((velBeta * velBeta) * lenghtBeta + (velAlpha * velAlpha) * lenghtAlpha * cos(alphaRad - betaRad)));
	float aux3 = (float)(lenghtAlpha * (2 * massAlpha + massBeta - massBeta * cos(2 * alphaRad - 2 * betaRad)));
	float accAlpha = (float)((aux + aux2) / (aux3));
	return accAlpha;
}

float predictAccBeta() {
	float alphaRad = gradsToRads(alpha);
	float betaRad = gradsToRads(beta);
	float aux = (float)(2 * sin(alphaRad - betaRad) * ((velAlpha * velAlpha) * lenghtAlpha * (massAlpha + massBeta) + g * (massAlpha + massBeta) * cos(alphaRad) + (velBeta * velBeta) * lenghtBeta * massBeta * cos(alphaRad - betaRad)));
	float aux2 = (float)(lenghtBeta * (2 * massAlpha + massBeta - massBeta * cos(2 * alphaRad - 2 * betaRad)));
	float aux3 = (float)((coefRoz / (massAlpha * lenghtAlpha * lenghtAlpha)) * velBeta);
	float accBeta = (aux) / (aux2) - aux3;
	return accBeta;
}

void drawDoblePendulum() {
	//pendulo principal
	glPushMatrix();
	glRotatef(alpha, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, -lenghtAlpha);
	glEnd();
	glPushMatrix();
	glTranslatef(0.0f, -lenghtAlpha, 0.0f);
	glScalef(0.1f, 0.1f, 0.1f);
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 1.0f, 1.0f);
	for (int i = 0; i < 360; i++) {
		float x = (float)cos(i * 3.14159f / 180.0f);
		float y = (float)sin(i * 3.14159f / 180.0f);
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
	glVertex2f(0.0f, -lenghtBeta);
	glEnd();
	glPushMatrix();
	glTranslatef(0.0f, -lenghtBeta, 0.0f);
	glScalef(0.1f, 0.1f, 0.1f);
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 1.0f, 1.0f);
	for (int i = 0; i < 360; i++) {
		float x = (float)cos(i * 3.14159 / 180.0);
		float y = (float)sin(i * 3.14159 / 180.0);
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
	//Calculamos las aceleraciones angulares
	float accAlpha = predictAccAlpha();
	float accBeta = predictAccBeta();
	//Actualizamos las velocidades angulares
	velAlpha = velAlpha + accAlpha * dt;
	velBeta = velBeta + accBeta * dt;
	//Pasamos los grados de los angulos usados a radianes para actualizarlos
	float alphaRad = gradsToRads(alpha);
	float betaRad = gradsToRads(beta);
	//actualizamos los angulos
	alphaRad = alphaRad + velAlpha * dt;
	betaRad = betaRad + velBeta * dt;
	//los volvemos a transformar a grados para que sean representados
	alpha = radsToGrads(alphaRad);
	beta = radsToGrads(betaRad);
	//evitamos cualquier underflow y overflow
	int alphaOverflow = (int)alpha / 360;
	printf("AlphaOverflow vale %i", alphaOverflow);
	alpha = (GLfloat)(alpha - 360 * alphaOverflow);
	int betaOverflow = (int)beta / 360;
	beta = (GLfloat)(beta - 360 * betaOverflow);
	/*while (alpha >= 360) {
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
	}*/
	//nextAlpha = (nextAlpha - alpha) / 10;
	//nextBeta = (nextBeta - beta) / 10;
	/*alpha = nextAlpha;
	beta = nextBeta;*/
	printf("Ahora vale %f   ||||||||", alpha);
	glutPostRedisplay();
}

void timer(int iUnused) {
	idle();
	glutTimerFunc(30, timer, 0);
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
	//glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
	timer(0);
	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}