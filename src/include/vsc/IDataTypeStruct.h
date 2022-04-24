/*
 * IDataTypeStruct.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include <string>
#include <vector>
#include "vsc/IDataType.h"
#include "vsc/IModelStructCreateHook.h"
#include "vsc/ITypeConstraint.h"
#include "vsc/ITypeField.h"

namespace vsc {

class IDataTypeStruct;
using IDataTypeStructUP=std::unique_ptr<IDataTypeStruct>;
class IDataTypeStruct : public IDataType {
public:

	virtual ~IDataTypeStruct() { }

	virtual const std::string &name() const = 0;

	virtual void addField(ITypeField *f) = 0;

	virtual const std::vector<ITypeFieldUP> &getFields() const = 0;

	virtual ITypeField *getField(int32_t idx) = 0;

	virtual void addConstraint(ITypeConstraint *c) = 0;

	virtual const std::vector<ITypeConstraintUP> &getConstraints() const = 0;

	virtual IModelStructCreateHook *getCreateHook() const = 0;

	virtual void setCreateHook(IModelStructCreateHook *hook) = 0;

};

}

