#include "IKWindow.h"
#include <GL/glui.h>
#include "IKSolver.h"
#include "DlsIKSolver.h"

GLUI_Scrollbar* dampingScroll;

void setDampingVal(int val)
{
	DlsIKSolver::dampingVal = dampingScroll->get_int_val();
}

int main()
{
	IKWindow window;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);

	int glutWindow = glutCreateWindow("IK Coursework Assignment - Balakumar Marimuthu");
	window.initLinkStructure();
	window.initOpenGL();

	GLUI* gluiWindow = GLUI_Master.create_glui_subwindow(glutWindow, GLUI_SUBWINDOW_RIGHT);
	GLUI_Master.set_glutDisplayFunc(IKWindow::draw);
	GLUI_Master.set_glutReshapeFunc(IKWindow::reshape);
	GLUI_Master.set_glutMouseFunc(IKWindow::mouseFunc);
	GLUI_Master.set_glutIdleFunc(IKWindow::idle);
	GLUI_Master.set_glutTimerFunc(5, IKWindow::updateLinkedStructure, 0);

	GLUI_Panel* ikTypeSelectPanel = gluiWindow->add_panel("Select IK Method");

	GLUI_Rollout* rollOut = gluiWindow->add_rollout_to_panel(ikTypeSelectPanel, "IK Methods", 0, 1);

	GLUI_Checkbox* pseudoInverse = new GLUI_Checkbox(rollOut, "Pseudo Inverse", &IKWindow::pseudoInverse);
	GLUI_Checkbox* dls = new GLUI_Checkbox(rollOut, "Damping Least Square", &IKWindow::dls);
	GLUI_Checkbox* jacobianTranspose = new GLUI_Checkbox(rollOut, "Jacobian Transpose", &IKWindow::jacobianTranspose);
	GLUI_Checkbox* ccd = new GLUI_Checkbox(rollOut, "CCD", &IKWindow::ccd);
	GLUI_Checkbox* secondaryTask = new GLUI_Checkbox(rollOut, "Secondary Task", &IKWindow::secondaryTask);

	gluiWindow->add_separator_to_panel(ikTypeSelectPanel);

	GLUI_StaticText* dampValText = gluiWindow->add_statictext_to_panel(ikTypeSelectPanel, "Damping Val : (1 to 100)");
	dampingScroll = new GLUI_Scrollbar(ikTypeSelectPanel, "Damping Val", GLUI_SCROLL_HORIZONTAL, GLUI_SCROLL_INT, 1, &setDampingVal);
	dampingScroll->set_int_limits(1, 100);
	DlsIKSolver::dampingVal = 100;
	dampingScroll->set_int_val(DlsIKSolver::dampingVal);

	GLUI_EditText* stepValText = gluiWindow->add_edittext_to_panel(ikTypeSelectPanel, "Step Val", GLUI_EDITTEXT_FLOAT, &IKSolver::_step);
	IKSolver::_step = 1.0f;
	stepValText->set_float_val(1.0f);
	stepValText->set_int_limits(0.1, 2.0);

	GLUI_EditText* toleranceValText = gluiWindow->add_edittext_to_panel(ikTypeSelectPanel, "Tolerance", GLUI_EDITTEXT_FLOAT, &IKSolver::_tolerance);
	IKSolver::_tolerance = 1.0f;
	toleranceValText->set_float_val(1.0f);
	toleranceValText->set_int_limits(1.0, 5.0);

	gluiWindow->set_main_gfx_window(glutWindow);

	GLUI_Master.auto_set_viewport();

	window.draw();

	glutMainLoop();

	return 0;
}