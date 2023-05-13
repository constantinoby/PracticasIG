#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

const int W_WIDTH = 600; // Tama�o incial de la ventana
const int W_HEIGHT = 600;
const float pi = 3.14159f;
GLfloat fAngulo; // Variable que indica el �ngulo de rotaci�n de los ejes. 
float horizontalCameraAngle = 0;
float verticalCameraAngle = 0;
int figura = 0;
bool ejes = true;
bool solid = false;
bool planes = false;

bool lateralMode = false;
bool rotationMode = false;
bool angularMode = true;

float increment = 0.2f;
GLdouble xPosition = 0.0;//5.0;
GLdouble yPosition = 0.0;//5.0;
GLdouble zPosition = 15.0;
GLdouble centerX = 0.0;
GLdouble centerY = 0.0;
GLdouble centerZ = 0.0;
GLdouble upX = 0.0;
GLdouble upY = 1.0;
GLdouble upZ = 0.0;

float gradsToRads(float grads) {
	return (grads * pi) / 180;
}

float radsToGrads(float rads) {
	return (rads * 180) / pi;
}

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

void drawFigure() {
	switch (figura) {
	case 1:
		glPushMatrix();
		glRotatef(fAngulo, 0.0f, 1.0f, 0.0f);
		glColor3f(0.5, 0.5, 0.5);
		if (solid) {
			glutSolidTeapot(5); // Dibuja un teapot sólido con un radio de 0.5 unidades
		}
		else {
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
		}
		else {
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
		}
		else {
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
		}
		else {
			glutWireCube(5);// Dibuja un cubo delineado con un tamaño de 5
		}
		glPopMatrix();
		break;
	default:
		break;
	}
}

void display(void) {
	// Borramos la escena
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(xPosition, yPosition, zPosition, centerX, centerY, centerZ, upX, upY, upZ);

	if (ejes) {
		drawAxes();
	}

	if (planes) {
		drawPlanes();
	}

	drawFigure();

	
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

	int ratio = width / height;

	gluPerspective(90, ratio, 1.0, 100);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(xPosition, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
	case '8':
		lateralMode = true;
		angularMode = false;
		rotationMode = false;
		break;
	case '9':
		lateralMode = false;
		angularMode = true;
		rotationMode = false;
		break;
	case '0':
		lateralMode = false;
		angularMode = false;
		rotationMode = true;
		break;
	default:
		figura = 0;
		break;
	}
}

void anglesNormalization() {
	if (horizontalCameraAngle >= 360) {
		horizontalCameraAngle -= 360;
	} else if (horizontalCameraAngle <= 0) {
		horizontalCameraAngle += 360;
	}
	if (verticalCameraAngle >= 360) {
		verticalCameraAngle -= 360;
	}
	else if (verticalCameraAngle <= 0) {
		verticalCameraAngle += 360;
	}
}

void rotateCameraHorizontally() {
	printf("angulo %f ||", horizontalCameraAngle);
	float radiansHorizontal = gradsToRads(horizontalCameraAngle);
	GLdouble newXDirection = 0;
	GLdouble newZDirection = 0;
	newXDirection = sqrt((xPosition * xPosition) + (zPosition * zPosition)) * cos(radiansHorizontal);
	newZDirection = sqrt((xPosition * xPosition) + (zPosition * zPosition)) * sin(radiansHorizontal);
	centerX = newXDirection;
	centerZ = newZDirection;
	printf("centerX %f || ", centerX);
	printf("centerZ %f \n", centerZ);
}

void cameraMovement(int key, int x, int y) {
	anglesNormalization();
	float radiansHorizontal = 0;
	if (lateralMode) { //la camara se mueve lateralmente CODIGO 8
		switch (key) {
			case GLUT_KEY_UP: //Nos acercamos al objeto
				xPosition -= increment;
				//yPosition += increment;
				//xPosition += increment;
				break;
			case GLUT_KEY_DOWN: //Nos alejamos del objeto
				//yPosition += increment;
				break;
			case GLUT_KEY_RIGHT: //Nos movemos lateralmente hacia la derecha
				radiansHorizontal = gradsToRads(horizontalCameraAngle);
				xPosition += increment * cos(radiansHorizontal);
				zPosition += increment * sin(radiansHorizontal);
				centerX += increment * cos(radiansHorizontal);
				centerZ += increment * sin(radiansHorizontal);
				break;
			case GLUT_KEY_LEFT: //Nos movemos lateralmente hacia la izquierda
				radiansHorizontal = gradsToRads(horizontalCameraAngle);
				xPosition -= increment * cos(radiansHorizontal);
				zPosition -= increment * sin(radiansHorizontal);
				centerX -= increment * cos(radiansHorizontal);
				centerZ -= increment * sin(radiansHorizontal);
				break;
		}
	} else if (rotationMode) { //la camara rota sobre si misma CODIGO 0
		GLdouble newXDirection = 0;
		GLdouble newZDirection = 0;
		GLdouble newUpX = 0;
		GLdouble newUpY = 0;
		GLdouble newUpZ = 0;
		GLdouble aux = 0;
		float radiansVertical = 0;
		switch (key) {
			case GLUT_KEY_UP: //sube la mirada
				verticalCameraAngle += increment * 10;
				radiansVertical = gradsToRads(verticalCameraAngle);
				centerY = sqrt(sqrt((xPosition * xPosition) + (zPosition * zPosition)) + (yPosition * yPosition)) * sin(radiansVertical);
				/*aux = sqrt((xPosition * xPosition) + (zPosition * zPosition)) * cos(radiansVertical);
				newXDirection += centerX;
				newZDirection += centerZ;
				newXDirection += aux * cos(radiansHorizontal);
				newZDirection += aux * sin(radiansHorizontal);
				centerX = newXDirection;
				centerZ = newZDirection;*/
				break;
			case GLUT_KEY_DOWN: //baja la mirada
				verticalCameraAngle -= increment * 10;
				radiansVertical = gradsToRads(verticalCameraAngle);
				centerY = sqrt(sqrt((xPosition * xPosition) + (zPosition * zPosition)) + (yPosition * yPosition)) * sin(radiansVertical);
				/*newXDirection -= sqrt((xPosition * xPosition) + (zPosition * zPosition)) * cos(radiansHorizontal);
				newZDirection -= sqrt((xPosition * xPosition) + (zPosition * zPosition)) * sin(radiansHorizontal);
				centerX = newXDirection;
				centerZ = newZDirection;*/
				//centerY = sqrt((xPosition * xPosition) + (zPosition * zPosition)) * sin(verticalCameraAngle);
				//centerY -= increment * sin(verticalCameraAngle);
				break;
			case GLUT_KEY_RIGHT: //rota hacia la derecha
				horizontalCameraAngle += increment*10;
				rotateCameraHorizontally();
				break;
			case GLUT_KEY_LEFT: //rota hacia la izquierda
				horizontalCameraAngle -= increment*10;
				rotateCameraHorizontally();
				//centerX -= increment * cos(horizontalCameraAngle);
				//centerZ -= increment * sin(horizontalCameraAngle);
				break;
		}
	} else if (angularMode) { //CODIGO 9
		GLdouble newX = 0;
		GLdouble newZ = 0;
		switch (key) {
			case GLUT_KEY_UP: //rota alrededor de la escena hacia arriba
				//yPosition += increment;
				//xPosition += cos();
				upX += increment;
				break;
			case GLUT_KEY_DOWN: //rota alrededor de la escena hacia abajo
				upY += increment;
				break;
			case GLUT_KEY_RIGHT: //rota alrededor de la escena hacia la derecha
				horizontalCameraAngle += increment * 10;
				radiansHorizontal = gradsToRads(horizontalCameraAngle);
				newX = sqrt((xPosition * xPosition) + (zPosition * zPosition)) * sin(radiansHorizontal);
				newZ = sqrt((xPosition * xPosition) + (zPosition * zPosition)) * cos(radiansHorizontal);
				xPosition = newX;
				zPosition = newZ;
				printf("xPosition: %f    zPosition: %f \n", xPosition, zPosition);
				break;
			case GLUT_KEY_LEFT: //rota alrededor de la escena hacia la izquierda
				horizontalCameraAngle -= increment * 10;
				radiansHorizontal = gradsToRads(horizontalCameraAngle);
				newX = sqrt((xPosition * xPosition) + (zPosition * zPosition)) * sin(radiansHorizontal);
				newZ = sqrt((xPosition * xPosition) + (zPosition * zPosition)) * cos(radiansHorizontal);
				xPosition = newX;
				zPosition = newZ;
				printf("xPosition: %f    zPosition: %f \n", xPosition, zPosition);
				break;
		}
	}
	glutPostRedisplay();
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
	glutSpecialFunc(cameraMovement);
	glutSpecialUpFunc(cameraMovement);

	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}