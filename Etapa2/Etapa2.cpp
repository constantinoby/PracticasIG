// Etapa1.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
const int W_WIDTH = 500; // Tama�o incial de la ventana
const int W_HEIGHT = 500;
GLfloat fAngulo; // Variable que indica el �ngulo de rotaci�n de los ejes. 



void lineas() {
	glPushMatrix();
	// Creamos a las 2 lineas que forman los ejes
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, W_WIDTH);
	glVertex2f(0.0f, -W_WIDTH);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(W_HEIGHT, 0.0f);
	glVertex2f(-W_HEIGHT, 0.0f);
	glEnd();

	glPopMatrix();
}

void figura1() {
	glPushMatrix();

	glTranslatef(-1.5, 1.5, 0.0f);
	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);

	glScalef(0.75, 0.75, 0.75);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.866f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.866f, 0.0f);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-0.5f, 0.866f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.866f, 0.0f);
	glEnd();


	glPopMatrix();
}

void figura2() {

	glPushMatrix();

	glTranslatef(1.5, 1.5, 0.0f);
	glRotatef(2 * fAngulo, 0.0f, 0.0f, 1.0f);

	//dibujamos un pentagono
	glBegin(GL_POLYGON);
	glColor3f(0.0f, -1.0f, 1.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	//amarillo
	glColor3f(1.0f, 1.0f, -1.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);

	glColor3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.3f, -0.4f, 0.0f);

	//rojo
	glColor3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-0.3f, -0.4f, 0.0f);
	//rojo
	glColor3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glEnd();

	glPopMatrix();
}

void figura3() {
		//Figura rara
	glPushMatrix();

	glTranslatef(-1.5, -1.5, 0.0f);
	glRotatef(-fAngulo, 0.0f, 0.0f, 1.0f);


	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f); // verde
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 1.0f); // azul
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(-0.4f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f); // amarillo
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(-0.4f, 0.0f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();

	glPopMatrix();
}

void figura4() {
	glPushMatrix();

	//Cuarto cuadrante
	glTranslatef(1.5, -1.5, 0.0f);
	glRotatef(-(2 * fAngulo), 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.4f, 0.4f); // vértice superior izquierdo
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.4f, 0.4f); // vértice superior derecho
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.2f, -0.4f); // vértice inferior derecho
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-0.2f, -0.4f); // vértice inferior izquierdo
	glEnd();


	glPopMatrix();
}

// Funci�n que visualiza la escena OpenGL
void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	lineas();

	figura1();
	
	figura2();

	figura3();


	figura4();

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
	glutCreateWindow("Mi segunda Ventana");

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