/*
 * ModelFieldVec.h
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelField.h"

namespace vsc {

class ModelFieldVec : public ModelField {
public:
	ModelFieldVec(ModelField *size);

	virtual ~ModelFieldVec();

	ModelField *size() const { return m_size.get(); }

	void size(ModelField *f) { m_size = ModelFieldUP(f); }

	void push_back(ModelField *f);

	void pop_back();

protected:
	ModelFieldUP					m_size;

};

} /* namespace vsc */

