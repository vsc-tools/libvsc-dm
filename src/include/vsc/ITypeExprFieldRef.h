/*
 * ITypeExprFieldRef.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/ITypeExpr.h"

namespace vsc {

enum class TypeExprFieldRefElemKind {
	Root,
	IdxOffset
};

struct TypeExprFieldRefElem {
	TypeExprFieldRefElemKind		kind;
	int32_t							idx;
};

class ITypeExprFieldRef : public ITypeExpr {
public:

	virtual ~ITypeExprFieldRef() { }

	virtual void addIdxRef(int32_t idx) = 0;

	virtual void addRootRef() = 0;

	virtual uint32_t size() const = 0;

	virtual const TypeExprFieldRefElem &at(int32_t idx) const = 0;

	virtual const std::vector<TypeExprFieldRefElem> &getPath() const = 0;

};


}