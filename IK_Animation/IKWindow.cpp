#include "IKWindow.h"
#include <iostream>

PinvIKSolver IKWindow::_linkStructure;
PinvIKSolver IKWindow::_linkStructure_secTask(true);
CcdIKSolver IKWindow::_linkStructure_ccd;
DlsIKSolver IKWindow::_linkStructure_dls;
JacobianTransposeIKSolver IKWindow::_linkStructure_jt;
glm::vec2 IKWindow::_targetPos;
int IKWindow::_screenWidth = 1024;
int IKWindow::_screenHeight = 768;

int IKWindow::pseudoInverse = 1;
int IKWindow::dls = 0;
int IKWindow::jacobianTranspose = 0;
int IKWindow::ccd = 0;
int IKWindow::secondaryTask = 0;

IKWindow::IKWindow()
{
}

IKWindow::~IKWindow()
{
}

void IKWindow::initLinkStructure()
{
	float angle = 0;
	IKSolver::_maxLength = 0.0f;
	for (int i = 0; i < 5; i++)
	{
		GLfloat pinvArmColor[] = { 0.772, 0.666, 0.960, 0.6 };
		GLfloat dlsArmColor[] = { 0.623, 0.007, 0.317, 0.6 };
		GLfloat ccdArmColor[] = { 0.925, 0.474, 0.603, 0.6 };
		GLfloat jtArmColor[] = { 0.960, 0.639, 0.321, 0.6 };
		GLfloat secTaskColor[] = { 0.560, 0.491, 0.987, 0.6 };

		Link2D* link = new Link2D(pinvArmColor);
		link->_angle = (piVal / 4);
		link->_length = 75;
		_linkStructure.addLink(link);

		Link2D* link_jt = new Link2D(jtArmColor);
		link_jt->_angle = (piVal / 4);
		link_jt->_length = 75;
		_linkStructure_jt.addLink(link_jt);

		Link2D* link_ccd = new Link2D(ccdArmColor);
		link_ccd->_angle = (piVal / 4);
		link_ccd->_length = 75;
		_linkStructure_ccd.addLink(link_ccd);

		Link2D* link_dls = new Link2D(dlsArmColor);
		link_dls->_angle = (piVal / 4);
		link_dls->_length = 75;
		_linkStructure_dls.addLink(link_dls);

		Link2D* link_secTask = new Link2D(secTaskColor);
		link_secTask->_angle = (piVal / 4);
		link_secTask->_length = 75;
		_linkStructure_secTask.addLink(link_secTask);

		IKSolver::_maxLength += 75;
	}
}

void IKWindow::initOpenGL()
{
	glClearColor(0.258, 0.235, 0.250, 1);
	glEnable(GL_DEPTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void IKWindow::mouseFunc(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		float posx = x - (_screenWidth / 2);
		float posy = (_screenHeight / 2) - y;

		_targetPos.x = posx;
		_targetPos.y = posy;

		IKSolver::setTarget(_targetPos);

		glutPostRedisplay();
	}
}

void IKWindow::idle()
{
	glutPostRedisplay();
}

void IKWindow::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(_screenWidth/2, _screenHeight/2, 0.0f);

	IKSolver::drawMaxArea();

	if (pseudoInverse == 1)
		_linkStructure.draw();

	if (dls == 1)
		_linkStructure_dls.draw();

	if (ccd == 1)
		_linkStructure_ccd.draw();

	if (jacobianTranspose == 1)
		_linkStructure_jt.draw();

	if (secondaryTask == 1)
		_linkStructure_secTask.draw();

	IKSolver::drawTarget();

	glFlush();
	glutSwapBuffers();
}

void IKWindow::reshape(GLsizei width, GLsizei height)
{
	GLUI_Master.auto_set_viewport();

	_screenWidth = width;
	_screenHeight = height;

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
}

void IKWindow::updateLinkedStructure(int time)
{
	_linkStructure.update();
	_linkStructure_dls.update();
	_linkStructure_ccd.update();
	_linkStructure_jt.update();
	_linkStructure_secTask.update();

	glutTimerFunc(5, IKWindow::updateLinkedStructure, time);
	glutPostRedisplay();
}