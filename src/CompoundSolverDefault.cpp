/*
 * CompoundSolverDefault.cpp
 *
 *  Created on: Mar 23, 2022
 *      Author: mballance
 */

#include "vsc/impl/TaskUnrollModelIterativeConstraints.h"
#include "vsc/impl/TaskRollbackConstraintSubst.h"
#include "CommitFieldValueVisitor.h"
#include "CompoundSolverDefault.h"
#include "Debug.h"
#include "SolverFactoryDefault.h"
#include "SolveSetSolveModelBuilder.h"
#include "SolveSetSwizzlerPartsel.h"
#include "SolveSpecBuilder.h"
#include "TaskSetUsedRand.h"
#include "TaskResizeConstrainedModelVec.h"
#include "vsc/impl/TaskUnrollModelIterativeConstraints.h"

#define EN_DEBUG_COMPOUND_SOLVER_DEFAULT

#ifdef EN_DEBUG_COMPOUND_SOLVER_DEFAULT
DEBUG_SCOPE(CompoundSolverDefault);
#define DEBUG_ENTER(fmt, ...) DEBUG_ENTER_BASE(CompoundSolverDefault, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) DEBUG_LEAVE_BASE(CompoundSolverDefault, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) DEBUG_BASE(CompoundSolverDefault, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {

CompoundSolverDefault::CompoundSolverDefault(IContext *ctxt) : m_ctxt(ctxt) {
	// TODO Auto-generated constructor stub

}

CompoundSolverDefault::~CompoundSolverDefault() {
	// TODO Auto-generated destructor stub
}

bool CompoundSolverDefault::solve(
			IRandState								*randstate,
			const std::vector<IModelField *>		&fields,
			const std::vector<IModelConstraint *>	&constraints,
			SolveFlags								flags) {
	ISolverFactory *solver_f = SolverFactoryDefault::inst();

	bool ret = true;
	DEBUG_ENTER("randomize n_fields=%d n_constraints=%d",
			fields.size(),
			constraints.size());

	if ((flags & SolveFlags::RandomizeDeclRand) || (flags & SolveFlags::RandomizeTopFields)) {
		TaskSetUsedRand task;
		for (auto f=fields.begin(); f!=fields.end(); f++) {
			task.apply(*f,
					(flags & SolveFlags::RandomizeTopFields) != SolveFlags::NoFlags,
					((flags & SolveFlags::RandomizeDeclRand) != SolveFlags::NoFlags)?-1:0);
		}
	}

	SolveSpecUP spec(SolveSpecBuilder().build(
			fields,
			constraints
			));

	DEBUG("%d solve-sets ; %d unconstrained ; %d unconstrained_sz_vec",
			spec->solvesets().size(),
			spec->unconstrained().size(),
			spec->unconstrained_sz_vec().size());

	// Start by fixing the size of the unconstrained-size vectors
	// to the current size
	for (std::vector<IModelFieldVec *>::const_iterator
		it=spec->unconstrained_sz_vec().begin();
		it!=spec->unconstrained_sz_vec().end(); it++) {
		(*it)->getSizeRef()->val()->set_val_u((*it)->getSize(), 32);
		(*it)->getSizeRef()->setFlag(ModelFieldFlag::Resolved);
	}

	for (auto sset=spec->solvesets().begin();
			sset!=spec->solvesets().end(); sset++) {
		DEBUG("Solve Set: %d fields ; %d constraints",
				(*sset)->all_fields().size(),
				(*sset)->constraints().size());

		// See if we need to re-evaluate due to vector constraints
		// TODO: Apply vector-sizing task
		if (TaskResizeConstrainedModelVec(m_ctxt, solver_f).resize(sset->get())) {
			// TODO: If vector-sizing applied to fields, apply unrolling algorithm
			// TODO: After unrolling, we likely have a different set of solve
			//       sets to work with

		} 

		if ((*sset)->hasFlags(SolveSetFlag::HaveForeach)) {
			// This solve-set has foreach constraints. Need to expand
			// the constraints, etc
			fprintf(stdout, "TODO: expand foreach constraints\n");
		} else {
			// If vector-sizing has no effect on this solve set, then proceed

			ISolverUP solver(solver_f->createSolverInst(sset->get()));
			// Build solve data for this solve set
			SolveSetSolveModelBuilder(solver.get()).build(sset->get());

			// First, ensure all constraints solve
			for (auto c_it=(*sset)->constraints().begin();
					c_it!=(*sset)->constraints().end(); c_it++) {
				solver->addAssume(*c_it);
			}
			for (auto c_it=(*sset)->soft_constraints().begin();
					c_it!=(*sset)->soft_constraints().end(); c_it++) {
				solver->addAssume(*c_it);
			}

			if (solver->isSAT()) {
				DEBUG("PASS: Initial try-solve for solveset");
				for (auto c_it=(*sset)->constraints().begin();
					c_it!=(*sset)->constraints().end(); c_it++) {
					solver->addAssert(*c_it);
				}
			} else {
				DEBUG("FAIL: Initial try-solve for solveset");

				ret = false;

				// TODO: Try backing off soft constraints
			}

			if (ret) {
				if ((flags & SolveFlags::Randomize) != SolveFlags::NoFlags) {
					// Swizzle fields
					SolveSetSwizzlerPartsel(randstate).swizzle(
							solver.get(),
							sset->get());
					// Ensure we're SAT
					if (!solver->isSAT()) {
						fprintf(stdout, "unsat post-swizzle\n");
					}
				}
				/*
				solver->isSAT();
				 */

				for (auto f_it=(*sset)->rand_fields().begin();
						f_it!=(*sset)->rand_fields().end(); f_it++) {
					DEBUG("Commit %s", (*f_it)->name().c_str());
					CommitFieldValueVisitor(solver.get()).commit(*f_it);
				}
			} else {
				break;
			}
		}

	}

	for (auto uc_it=spec->unconstrained().begin();
			uc_it!=spec->unconstrained().end(); uc_it++) {
		DEBUG("Randomize unconstrained field %s", (*uc_it)->name().c_str());
		randstate->randbits((*uc_it)->val());
	}

	DEBUG_LEAVE("randomize n_fields=%d n_constraints=%d ret=%d",
			fields.size(),
			constraints.size(),
			ret);
	return ret;
}

} /* namespace vsc */
