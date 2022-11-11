
#pragma once
#include "vsc/IModelFieldRef.h"

namespace vsc {

class IModelFieldTypeRef : public virtual IModelFieldRef {
public:

    virtual ~IModelFieldTypeRef() { }

	virtual ITypeField *getTypeField() const = 0;

	template <class T> T *getTypeFieldT() const {
		return dynamic_cast<T *>(getTypeField());
	}

    virtual IDataType *getDataTypeRef() const = 0;

};

}