/*
 * IDataTypeScalar.h
 *
 *  Created on: Jun 27, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IDataType.h"
#include "vsc/ITypeExprRangelist.h"

namespace vsc {

class IDataTypeScalar : public virtual IDataType {
public:

	virtual ~IDataTypeScalar() { }

	virtual ITypeExprRangelist *getDomain() = 0;

	virtual bool isSigned() const = 0;

	virtual int32_t getWidth() = 0;

};


}