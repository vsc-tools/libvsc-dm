/*
 * ModelExprFieldRef.cpp
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#include "ModelExprFieldRef.h"

namespace vsc {

ModelExprFieldRef::ModelExprFieldRef(ModelField *field) : m_field(field) {
	// TODO: Compute based on field data type
	m_width = 32;
	// TODO Auto-generated constructor stub

}

ModelExprFieldRef::~ModelExprFieldRef() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */