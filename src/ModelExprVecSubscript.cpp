/*
 * ModelExprVecSubscript.cpp
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#include "ModelExprVecSubscript.h"

namespace vsc {

ModelExprVecSubscript::ModelExprVecSubscript(
		IModelExpr			*expr,
		IModelExpr			*subscript)
				: m_expr(expr), m_subscript(subscript) {

}

ModelExprVecSubscript::~ModelExprVecSubscript() {
	// TODO Auto-generated destructor stub
}

void ModelExprVecSubscript::eval(IModelVal *dst) {
	fprintf(stdout, "TODO: ModelExprVecSubscript::eval\n");
}

} /* namespace vsc */
