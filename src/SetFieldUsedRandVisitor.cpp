/*
 * SetFieldUsedRandVisitor.cpp
 *
 *  Created on: Oct 24, 2021
 *      Author: mballance
 */

#include "Debug.h"
#include "SetFieldUsedRandVisitor.h"

#undef EN_DEBUG_SET_FIELD_USED_RAND_VISITOR

#ifdef EN_DEBUG_SET_FIELD_USED_RAND_VISITOR
DEBUG_SCOPE(SetFieldUsedRandVisitor)
#define DEBUG_ENTER(fmt, ...) DEBUG_ENTER_BASE(SetFieldUsedRandVisitor, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) DEBUG_LEAVE_BASE(SetFieldUsedRandVisitor, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) DEBUG_BASE(SetFieldUsedRandVisitor, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {

SetFieldUsedRandVisitor::SetFieldUsedRandVisitor() {
	// TODO Auto-generated constructor stub

}

SetFieldUsedRandVisitor::~SetFieldUsedRandVisitor() {
	// TODO Auto-generated destructor stub
}

void SetFieldUsedRandVisitor::set(ModelField *f) {
	DEBUG_ENTER("set %s", f->name().c_str());
	m_decl_rand_s.clear();
	f->accept(this);
	DEBUG_LEAVE("set %s", f->name().c_str());
}

void SetFieldUsedRandVisitor::visitModelField(ModelField *f) {
	DEBUG_ENTER("visitModelField %s flags=0x%08x",
			f->name().c_str(), f->flags());
	if ((m_decl_rand_s.size() == 0 || m_decl_rand_s.back()) &&
			f->is_flag_set(ModelFieldFlag_DeclRand)) {
		f->set_flag(ModelFieldFlag_UsedRand);
	}

	m_decl_rand_s.push_back(
			(m_decl_rand_s.size() == 0 ||
				f->is_flag_set(ModelFieldFlag_DeclRand)));
	VisitorBase::visitModelField(f);
	m_decl_rand_s.pop_back();

	DEBUG_LEAVE("visitModelField %s flags=0x%08x",
			f->name().c_str(), f->flags());
}

} /* namespace vsc */
