
#pragma once
#include <vector>
#include "vsc/IModelConstraint.h"
#include "vsc/IModelField.h"

namespace vsc {

/**
 * @brief Equates two quantities -- an expression on one side and
 *        a select of expressions from the other side
 * 
 */
class IModelConstraintSelect : public IModelConstraint {
public:

    virtual IModelField *getLhs() const = 0;

    virtual const std::vector<IModelField *> &getRhs() const = 0;

    virtual void addRhs(IModelField *rhs) = 0;

    virtual IModelField *getSelector() = 0;

};

}