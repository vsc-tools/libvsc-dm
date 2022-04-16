/*
 * TaskModelFieldBuilder.cpp
 *
 *  Created on: Apr 9, 2022
 *      Author: mballance
 */

#include "Debug.h"
#include "TaskModelExprBuilder.h"
#include "TaskModelFieldBuilder.h"

#include "include/vsc/IDataTypeStruct.h"
#include "include/vsc/IModelFieldRoot.h"
#include "include/vsc/IModelFieldType.h"

#define EN_DEBUG_TASK_MODEL_FIELD_BUILDER

#ifdef EN_DEBUG_TASK_MODEL_FIELD_BUILDER
DEBUG_SCOPE(TaskModelFieldBuilder);
#define DEBUG_ENTER(fmt, ...) \
	DEBUG_ENTER_BASE(TaskModelFieldBuilder, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) \
	DEBUG_LEAVE_BASE(TaskModelFieldBuilder, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) \
	DEBUG_BASE(TaskModelFieldBuilder, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif


namespace vsc {

TaskModelFieldBuilder::TaskModelFieldBuilder(IContext *ctxt) :
		m_ctxt(ctxt), m_type_field(0) {
}

TaskModelFieldBuilder::~TaskModelFieldBuilder() {
	// TODO Auto-generated destructor stub
}

IModelFieldRoot *TaskModelFieldBuilder::build(
		IDataTypeStruct 		*type,
		const std::string		&name) {
	DEBUG_ENTER("build");
	m_field_s.clear();
	m_constraint_s.clear();
	m_name = name; // TODO:
	m_type_field = 0;
	type->accept(this);
	DEBUG_LEAVE("build");
	return dynamic_cast<IModelFieldRoot *>(m_field_s.at(0));
}

void TaskModelFieldBuilder::visitTypeField(ITypeField *f) {
	DEBUG_ENTER("visitTypeField");
	IModelFieldType *field = m_ctxt->mkModelFieldType(f);
	m_field_s.back()->addField(field);

	m_field_s.push_back(field);
	VisitorBase::visitTypeField(f);
	m_field_s.pop_back();
	DEBUG_LEAVE("visitTypeField");
}

void TaskModelFieldBuilder::visitDataTypeInt(IDataTypeInt *t) {

}

void TaskModelFieldBuilder::visitDataTypeStruct(IDataTypeStruct *t) {
	DEBUG_ENTER("visitDataTypeStruct %d %d",
			t->getFields().size(),
			t->getConstraints().size());
	if (m_field_s.size() == 0) {
		IModelFieldRoot *field = m_ctxt->mkModelFieldRoot(t, m_name);

		m_field_s.push_back(field);
	}

	// Visit the members
	VisitorBase::visitDataTypeStruct(t);
	DEBUG_LEAVE("visitDataTypeStruct");
}

void TaskModelFieldBuilder::visitTypeConstraintBlock(ITypeConstraintBlock *c) {
	DEBUG_ENTER("visitTypeConstraintBlock");
	IModelConstraintBlock *cm = m_ctxt->mkModelConstraintBlock(c->name());

	m_constraint_s.push_back(cm);
	for (auto it=c->constraints().begin(); it!=c->constraints().end(); it++) {
		(*it)->accept(this);
	}

	m_constraint_s.pop_back();

	if (m_constraint_s.size() == 0) {
		m_field_s.back()->addConstraint(cm);
	}
	DEBUG_LEAVE("visitTypeConstraintBlock");
}

void TaskModelFieldBuilder::visitTypeConstraintExpr(ITypeConstraintExpr *c) {
	DEBUG_ENTER("visitTypeConstraintExpr");

	// Convert type expression to a model expression
	IModelExpr *expr = TaskModelExprBuilder(
			m_ctxt, m_field_s.back()).build(c->expr());

	IModelConstraintExpr *cm = m_ctxt->mkModelConstraintExpr(expr);

	m_constraint_s.back()->add_constraint(cm);

	DEBUG_LEAVE("visitTypeConstraintExpr");
}

void TaskModelFieldBuilder::visitTypeConstraintScope(ITypeConstraintScope *c) {
	DEBUG_ENTER("visitTypeConstraintScope");
	VisitorBase::visitTypeConstraintScope(c);
	DEBUG_LEAVE("visitTypeConstraintScope");
}


} /* namespace vsc */
