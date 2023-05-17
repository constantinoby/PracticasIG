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
float horizontalSceneAngle = 0;
float verticalSceneAngle = 0;
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


float light_position[] = { -3.0, 3.0, 10.0, 0.0 };


GLenum  shading_mode = GL_SMOOTH;


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

	case 5:
		glPushMatrix();
		glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
		glScaled(2, 2, 2);
		glBegin(GL_QUADS);

		// Cara frontal
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);

		// Cara trasera
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0, 1.0, -1.0);
		glVertex3f(1.0, 1.0, -1.0);

		// Cara izquierda
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, -1.0);

		// Cara derecha
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, -1.0);
		glVertex3f(1.0, 1.0, -1.0);
		glVertex3f(1.0, 1.0, 1.0);

		// Cara superior
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, -1.0);
		glVertex3f(-1.0, 1.0, -1.0);

		// Cara inferior
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(1.0, -1.0, -1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(-1.0, -1.0, 1.0);

		glEnd();
		glPopMatrix();

		break;

	default:
		break;
	}
}

void drawLight() {
	glPopMatrix();
	glTranslatef(light_position[0], light_position[1], light_position[2]);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();
}


void display(void) {
	// Borramos la escena
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glLoadIdentity();
	gluLookAt(xPosition, yPosition, zPosition, centerX, centerY, centerZ, upX, upY, upZ);

	glShadeModel(shading_mode);
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	if (ejes) {
		drawAxes();
	}

	if (planes) {
		drawPlanes();
	}

	drawFigure();

	drawLight();

	


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

void recalculateHorizontalCameraAngle() {
	double xDistance = xPosition - centerX;
	double zDistance = zPosition - centerZ;
	double distance = sqrt((xDistance * xDistance) + (zDistance * zDistance));
	float rads = asin(zPosition / distance);
	printf("Horizontal Scene angle in rads: %f || ", rads);
	float aux = rads * 180; //por algun motivo se cambia el signo cuando el angulo se acerca a 270 o al equivalente en negativo
	aux = aux / pi;
	printf("CC: %f Distancia: %f ", zPosition, distance);
	horizontalCameraAngle = -aux; //radsToGrads(asin( zPosition / distance ));
	printf("Angle %f \n", horizontalCameraAngle);
}

void recalculateSceneAngle() {
	double distance = sqrt((xPosition * xPosition) + (zPosition * zPosition));
	float rads = acos(zPosition / distance);
	printf("Horizontal Scene angle in rads: %f || ", rads);
	float aux = rads * 180; //por algun motivo se cambia el signo cuando el angulo se acerca a 270 o al equivalente en negativo
	aux = aux / pi;
	printf("Variable aux in grads: %f || ", aux);
	horizontalSceneAngle = aux; //radsToGrads(acos(zPosition / distance));
	printf("Angle %f \n", horizontalSceneAngle);
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
	case '5':
		figura = 5;
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
		centerX = 0.0;
		centerY = 0.0;
		centerZ = 0.0;
		recalculateSceneAngle();
		break;
	case '0':
		lateralMode = false;
		angularMode = false;
		rotationMode = true;
		recalculateHorizontalCameraAngle();
		break;
	case 'A': //Posicion 1 de la luz, mueve luz izquierda
		light_position[0] -= 1.0;
		break;
	case 'Z': //Posicion 2 de la luz, mueve luz derecha
		light_position[0] += 1.0;
		break;
	case 'S': //Posicion 3 de la luz, mueve luz abajo
		light_position[1] -= 1.0;
		break;
	case 'X': //Posicion 4 de la luz, mueve luz arriba
		light_position[1] += 1.0;
		break;
	case 'D': //Posicion 5 de la luz, meuve luz atras
		light_position[2] -= 1.0;
		break;
	case 'C': //Posicion 6 de la luz, mueve luz delante
		light_position[2] += 1.0;
		break;
	case ' ' :
		if (shading_mode == GL_FLAT) {
			shading_mode = GL_SMOOTH;
		}else {
			shading_mode = GL_FLAT;
		}
		break;
	case 'm':
		printf("ligt[0]: %f    ligt[1]: %f	  ligt[2]: %f \n", light_position[0], light_position[1], light_position[2]);
		break;
	default:
		figura = 0;
		break;
	}
}

void anglesNormalization() {
	if (horizontalCameraAngle >= 360) {
		horizontalCameraAngle -= 360;
	}
	else if (horizontalCameraAngle <= 0) {
		horizontalCameraAngle += 360;
	}
	if (verticalCameraAngle >= 360) {
		verticalCameraAngle -= 360;
	}
	else if (verticalCameraAngle <= 0) {
		verticalCameraAngle += 360;
	}

	if (horizontalSceneAngle >= 360) {
		horizontalSceneAngle -= 360;
	}
	else if (horizontalSceneAngle <= 0) {
		horizontalSceneAngle += 360;
	}
	if (verticalSceneAngle >= 360) {
		verticalSceneAngle -= 360;
	}
	else if (verticalSceneAngle <= 0) {
		verticalSceneAngle += 360;
	}
}

void rotateCameraHorizontally() {
	printf("angulo %f ||", horizontalCameraAngle);
	float radiansHorizontal = gradsToRads(horizontalCameraAngle);
	double xDistance = xPosition - centerX;
	double zDistance = zPosition - centerZ;
	double radius = sqrt((xDistance * xDistance) + (zDistance * zDistance));
	centerX = radius * cos(radiansHorizontal);
	centerZ = radius * sin(radiansHorizontal);
	printf("centerX %f || ", centerX);
	printf("centerZ %f \n", centerZ);
}

void rotateCameraAroundSceneHorizontally() {
	float radiansHorizontal = gradsToRads(horizontalSceneAngle);
	double radius = sqrt((xPosition * xPosition) + (zPosition * zPosition));
	xPosition = radius * sin(radiansHorizontal);
	zPosition = radius * cos(radiansHorizontal);
	printf("xPosition: %f    zPosition: %f	  SceneAngle: %f \n", xPosition, zPosition, horizontalSceneAngle);
}

void cameraMovement(int key, int x, int y) {
	anglesNormalization();
	float radiansHorizontal = 0;
	if (lateralMode) { //la camara se mueve lateralmente CODIGO 8
		switch (key) {
		case GLUT_KEY_UP: //Nos acercamos al objeto
			if (xPosition < centerX) {
				xPosition += increment;
				centerX += increment;
			}
			else if (xPosition > centerX) {
				xPosition -= increment;
				centerX -= increment;
			}
			if (yPosition < centerY) {
				yPosition += increment;
				centerY += increment;
			}
			else if (yPosition > centerY) {
				yPosition -= increment;
				centerY -= increment;
			}
			if (zPosition < centerZ) {
				zPosition += increment;
				centerZ += increment;
			}
			else if (zPosition > centerZ) {
				zPosition -= increment;
				centerZ -= increment;
			}
			//xPosition -= increment;
			//yPosition += increment;
			//xPosition += increment;
			break;
		case GLUT_KEY_DOWN: //Nos alejamos del objeto
			if (xPosition < centerX) {
				xPosition -= increment;
				centerX -= increment;
			}
			else if (xPosition > centerX) {
				xPosition += increment;
				centerX += increment;
			}
			if (yPosition < centerY) {
				yPosition -= increment;
				centerY -= increment;
			}
			else if (yPosition > centerY) {
				yPosition += increment;
				centerY += increment;
			}
			if (zPosition < centerZ) {
				zPosition -= increment;
				centerZ -= increment;
			}
			else if (zPosition > centerZ) {
				zPosition += increment;
				centerZ += increment;
			}
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
	}
	else if (rotationMode) { //la camara rota sobre si misma CODIGO 0
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
			//printf("");
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
			horizontalCameraAngle += increment * 10;
			rotateCameraHorizontally();
			break;
		case GLUT_KEY_LEFT: //rota hacia la izquierda
			horizontalCameraAngle -= increment * 10;
			rotateCameraHorizontally();
			//centerX -= increment * cos(horizontalCameraAngle);
			//centerZ -= increment * sin(horizontalCameraAngle);
			break;
		}
	}
	else if (angularMode) { //CODIGO 9
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
			horizontalSceneAngle += increment * 10;
			rotateCameraAroundSceneHorizontally();
			break;
		case GLUT_KEY_LEFT: //rota alrededor de la escena hacia la izquierda
			horizontalSceneAngle -= increment * 10;
			rotateCameraAroundSceneHorizontally();
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// Creamos la nueva ventana
	glutCreateWindow("Etapa 5");

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