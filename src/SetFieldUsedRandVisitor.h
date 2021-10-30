/*
 * SetFieldUsedRandVisitor.h
 *
 *  Created on: Oct 24, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "VisitorBase.h"

namespace vsc {

class SetFieldUsedRandVisitor : public VisitorBase {
public:
	SetFieldUsedRandVisitor();

	virtual ~SetFieldUsedRandVisitor();

	void set(ModelField *f);

	virtual void visitModelField(ModelField *f) override;

private:
	std::vector<bool>		m_decl_rand_s;

};

} /* namespace vsc */
