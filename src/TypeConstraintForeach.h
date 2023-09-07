/**
 * TypeConstraintForeach.h
 *
 * Copyright 2023 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author: 
 */
#pragma once
#include <string>
#include "vsc/dm/IContext.h"
#include "vsc/dm/ITypeConstraintForeach.h"


namespace vsc {
namespace dm {



class TypeConstraintForeach : 
    public virtual ITypeConstraintForeach {
public:

    TypeConstraintForeach(
        IContext            *ctxt,
        ITypeExpr           *target,
        bool                target_owned,
        const std::string   &iter_name,
        ITypeConstraint     *body,
        bool                body_owned);

    virtual ~TypeConstraintForeach();

    virtual ITypeExpr *getTarget() const override {
        return m_target.get();
    }

    virtual ITypeConstraint *getBody() const {
        return m_body.get();
    }

    virtual void addVariable(ITypeField *var, bool owned=true) override {
        m_variables.push_back(ITypeFieldUP(var, owned));
    }

    virtual const std::vector<ITypeFieldUP> &getVariables() const override {
        return m_variables;
    }

    virtual void accept(IVisitor *v) override { v->visitTypeConstraintForeach(this); }

private:
    ITypeExprUP                     m_target;
    ITypeConstraintUP               m_body;
    std::vector<ITypeFieldUP>       m_variables;

};

}
}


