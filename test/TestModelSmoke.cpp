/*
 * TestModelSmoke.cpp
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include "TestModelSmoke.h"
#include "Context.h"
#include "ModelFieldRoot.h"
#include "SolverBoolector.h"

namespace vsc {

TestModelSmoke::TestModelSmoke() {
	// TODO Auto-generated constructor stub

}

TestModelSmoke::~TestModelSmoke() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestModelSmoke, smoke) {
	Context ctx;

	DataTypeInt *vsc_uint32_t = ctx.findIntType(false, 32);
	ModelFieldRoot *a = new ModelFieldRoot(vsc_uint32_t, "a");
	SolverBoolector *solver = new SolverBoolector();

	solver->initField(a);
	solver->isSAT();
	solver->setFieldValue(a);
}

} /* namespace vsc */