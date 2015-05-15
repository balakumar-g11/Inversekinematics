#pragma once

#include <vector>
#include <GL/glui.h>
#include "PinvIKSolver.h"
#include "DlsIKSolver.h"
#include "JacobianTransposeIKSolver.h"
#include "CcdIKSolver.h"
#include "Link.h"

enum class AppState{
	RUNNING,
	EXIT
};

class IKWindow
{
public:
	IKWindow();
	~IKWindow();

	void initOpenGL();

	static void draw();

	static void reshape(int width, int height);

	static void idle();

	static void mouseFunc(int btn, int state, int x, int y);

	void initLinkStructure();

	static void updateLinkedStructure(int time);

	static int pseudoInverse;

	static int dls;

	static int jacobianTranspose;

	static int ccd;

	static int secondaryTask;

private:
	AppState _state;

	static int _screenWidth;

	static int _screenHeight;

	static glm::vec2 _targetPos;

	static PinvIKSolver _linkStructure;

	static CcdIKSolver _linkStructure_ccd;

	static JacobianTransposeIKSolver _linkStructure_jt;

	static DlsIKSolver _linkStructure_dls;

	static PinvIKSolver _linkStructure_secTask;
};
