/*
 * ContextDelegator.h
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IContext.h"

namespace vsc {

class ContextDelegator : public virtual vsc::IContext {
public:

	ContextDelegator(IContext *ctxt) : m_ctxt(ctxt) { }

	virtual ~ContextDelegator() {
		if (m_ctxt) {
			delete m_ctxt;
		}
	}

	virtual IModelField *buildModelField(
			IDataTypeStruct			*dt,
			const std::string		&name) override {
		return m_ctxt->buildModelField(dt, name);
	}

	virtual ICompoundSolver *mkCompoundSolver() override {
		return m_ctxt->mkCompoundSolver();
	}

	virtual IModelValOp *getModelValOp() override {
		return m_ctxt->getModelValOp();
	}

	virtual IDataTypeEnum *findDataTypeEnum(const std::string &name) override {
		return m_ctxt->findDataTypeEnum(name);
	}

	virtual IDataTypeEnum *mkDataTypeEnum(
			const std::string 	&name,
			bool				is_signed) override {
		return m_ctxt->mkDataTypeEnum(name, is_signed);
	}

	virtual bool addDataTypeEnum(IDataTypeEnum *e) override {
		return m_ctxt->addDataTypeEnum(e);
	}

	virtual IDataTypeInt *findDataTypeInt(
			bool			is_signed,
			int32_t			width) override {
		return m_ctxt->findDataTypeInt(is_signed, width);
	}

	/**
	 * Returns a new datatype. The expectation is that
	 * it will be subsequently added to the context
	 */
	virtual IDataTypeInt *mkDataTypeInt(
			bool			is_signed,
			int32_t			width) override {
		return m_ctxt->mkDataTypeInt(is_signed, width);
	}

	virtual bool addDataTypeInt(IDataTypeInt *t) override {
		return m_ctxt->addDataTypeInt(t);
	}

	virtual IDataTypeStruct *findDataTypeStruct(const std::string &name) override {
		return m_ctxt->findDataTypeStruct(name);
	}

	virtual bool addDataTypeStruct(IDataTypeStruct *t) override {
		return m_ctxt->addDataTypeStruct(t);
	}

	virtual IDataTypeStruct *mkDataTypeStruct(const std::string &name) override {
		return m_ctxt->mkDataTypeStruct(name);
	}

	virtual IDataTypeVec *findDataTypeVec(IDataType *t) override {
		return m_ctxt->findDataTypeVec(t);
	}

	virtual IDataTypeVec *mkDataTypeVec(IDataType *t) override {
		return m_ctxt->mkDataTypeVec(t);
	}

	virtual bool *addDataTypeVec(IDataTypeVec *t) override {
		return m_ctxt->addDataTypeVec(t);
	}

	virtual IModelConstraintBlock *mkModelConstraintBlock(
			const std::string &name) override {
		return m_ctxt->mkModelConstraintBlock(name);
	}

	virtual IModelConstraintExpr *mkModelConstraintExpr(
			IModelExpr		*expr) override {
		return m_ctxt->mkModelConstraintExpr(expr);
	}

	virtual IModelConstraintForeach *mkModelConstraintForeach(
			IModelExpr			*target,
			const std::string	&index_it_name) override {
		return m_ctxt->mkModelConstraintForeach(target, index_it_name);
	}

	virtual IModelConstraintIfElse *mkModelConstraintIfElse(
			IModelExpr			*cond,
			IModelConstraint	*true_c,
			IModelConstraint	*false_c) override {
		return m_ctxt->mkModelConstraintIfElse(cond, true_c, false_c);
	}

	virtual IModelConstraintImplies *mkModelConstraintImplies(
			IModelExpr			*cond,
			IModelConstraint	*body) override {
		return m_ctxt->mkModelConstraintImplies(cond, body);
	}

	virtual IModelConstraintRef *mkModelConstraintRef(
			IModelConstraint	*target) override {
		return m_ctxt->mkModelConstraintRef(target);
	}

	virtual IModelConstraintScope *mkModelConstraintScope() override {
		return m_ctxt->mkModelConstraintScope();
	}

	virtual IModelConstraintSoft *mkModelConstraintSoft(
		IModelConstraintExpr	*c) override {
		return m_ctxt->mkModelConstraintSoft(c);
	}

	virtual IModelConstraintSubst *mkModelConstraintSubst(
		IModelConstraint		*c) override {
		return m_ctxt->mkModelConstraintSubst(c);
	}

	virtual IModelConstraintUnique *mkModelConstraintUnique(
		const std::vector<IModelExpr *>		&exprs) override {
		return m_ctxt->mkModelConstraintUnique(exprs);
	}

	virtual IModelCoverBinCollection *mkModelCoverBinCollection(
		ModelCoverBinType			type) override {
		return m_ctxt->mkModelCoverBinCollection(type);
	}

	virtual IModelCoverBin *mkModelCoverBinSingleRange(
		const std::string			&name,
		ModelCoverBinType			type,
		bool						is_signed,
		IModelVal					*lower,
		IModelVal					*upper) override {
		return m_ctxt->mkModelCoverBinSingleRange(
			name, type, is_signed, lower, upper);
	}

	virtual IModelCoverBin *mkModelCoverBinSingleVal(
		const std::string			&name,
		ModelCoverBinType			type,
		IModelVal					*value) override {
		return m_ctxt->mkModelCoverBinSingleVal(name, type, value);
	}

	virtual IModelCoverCross *mkModelCoverCross(
		const std::string			&name,
		IModelCoverpointIff			*iff) override {
		return m_ctxt->mkModelCoverCross(name, iff);
	}

	virtual IModelCovergroup *mkModelCovergroup(
		const std::string			&name) override {
		return m_ctxt->mkModelCovergroup(name);
	}

	virtual IModelCoverpoint *mkModelCoverpoint(
		const std::string			&name,
		IModelCoverpointTarget		*target,
		IModelCoverpointIff			*iff) override {
		return m_ctxt->mkModelCoverpoint(name, target, iff);
	}

	virtual IModelCoverpointTarget *mkModelCoverpointTargetExpr(
		IModelExpr					*expr,
		int32_t						width) override {
		return m_ctxt->mkModelCoverpointTargetExpr(expr, width);
	}

	virtual IModelExprBin *mkModelExprBin(
			IModelExpr		*lhs,
			BinOp			op,
			IModelExpr		*rhs) override {
		return m_ctxt->mkModelExprBin(lhs, op, rhs);
	}

	virtual IModelExprCond *mkModelExprCond(
			IModelExpr		*cond,
			IModelExpr		*true_e,
			IModelExpr		*false_e) override {
		return m_ctxt->mkModelExprCond(cond, true_e, false_e);
	}

	virtual IModelExprFieldRef *mkModelExprFieldRef(
			IModelField		*field) override {
		return m_ctxt->mkModelExprFieldRef(field);
	}

	virtual IModelExprIn *mkModelExprIn(
			IModelExpr				*lhs,
			IModelExprRangelist		*rhs) override {
		return m_ctxt->mkModelExprIn(lhs, rhs);
	}

	virtual IModelExprIndexedFieldRef *mkModelExprIndexedFieldRef() override {
		return m_ctxt->mkModelExprIndexedFieldRef();
	}

	virtual IModelExprPartSelect *mkModelExprPartSelect(
			IModelExpr				*lhs,
			int32_t					lower,
			int32_t					upper) override {
		return m_ctxt->mkModelExprPartSelect(lhs, lower, upper);
	}

	virtual IModelExprRef *mkModelExprRef(IModelExpr *target) override {
		return m_ctxt->mkModelExprRef(target);
	}

	virtual IModelExprUnary *mkModelExprUnary(
		UnaryOp		op,
		IModelExpr	*e) override {
		return m_ctxt->mkModelExprUnary(op, e);
	}

	virtual IModelExprVal *mkModelExprVal(IModelVal *v) override {
		return m_ctxt->mkModelExprVal(v);
	}

	virtual IModelFieldRef *mkModelFieldRefRoot(
			IDataType			*type,
			const std::string	&name) override {
		return m_ctxt->mkModelFieldRefRoot(type, name);
	}

	virtual IModelFieldRef *mkModelFieldRefType(
			ITypeField			*type) override {
		return m_ctxt->mkModelFieldRefType(type);
	}

	virtual IModelFieldRoot *mkModelFieldRoot(
			IDataType 			*type,
			const std::string	&name) override {
		return m_ctxt->mkModelFieldRoot(type, name);
	}

	virtual IModelFieldType *mkModelFieldType(
			ITypeField			*type) override {
		return m_ctxt->mkModelFieldType(type);
	}

	virtual IModelFieldVec *mkModelFieldVecRoot(
			IDataType			*type,
			const std::string	&name) override {
		return m_ctxt->mkModelFieldVecRoot(type, name);
	}

	virtual IModelVal *mkModelVal() override {
		return m_ctxt->mkModelVal();
	}

	virtual IRandomizer *mkRandomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate) override {
		return m_ctxt->mkRandomizer(solver_factory, randstate);
	}

	virtual IRandState *mkRandState(const std::string &seed) override {
		return m_ctxt->mkRandState(seed);
	}

	virtual ITask *mkTask(TaskE id) override {
		return m_ctxt->mkTask(id);
	}

	virtual ITypeExprBin *mkTypeExprBin(
			ITypeExpr		*lhs,
			BinOp			op,
			ITypeExpr		*rhs) override {
		return m_ctxt->mkTypeExprBin(lhs, op, rhs);
	}

	virtual ITypeConstraintBlock *mkTypeConstraintBlock(const std::string &name) override {
		return m_ctxt->mkTypeConstraintBlock(name);
	}

	virtual ITypeConstraintExpr *mkTypeConstraintExpr(ITypeExpr *e) override {
		return m_ctxt->mkTypeConstraintExpr(e);
	}

	virtual ITypeConstraintIfElse *mkTypeConstraintIfElse(
			ITypeExpr 		*cond,
			ITypeConstraint	*true_c,
			ITypeConstraint	*false_c) override {
		return m_ctxt->mkTypeConstraintIfElse(cond, true_c, false_c);
	}

	virtual ITypeConstraintImplies *mkTypeConstraintImplies(
			ITypeExpr		*cond,
			ITypeConstraint	*body) override {
		return m_ctxt->mkTypeConstraintImplies(cond, body);
	}

	virtual ITypeConstraintScope *mkTypeConstraintScope() override {
		return m_ctxt->mkTypeConstraintScope();
	}

	virtual ITypeConstraintSoft *mkTypeConstraintSoft(
			ITypeConstraintExpr	*c) override {
		return m_ctxt->mkTypeConstraintSoft(c);
	}

	virtual ITypeConstraintUnique *mkTypeConstraintUnique(
			const std::vector<ITypeExpr *>		&exprs) override {
		return m_ctxt->mkTypeConstraintUnique(exprs);
	}

	virtual ITypeExprFieldRef *mkTypeExprFieldRef() override {
		return m_ctxt->mkTypeExprFieldRef();
	}

	virtual ITypeExprRange *mkTypeExprRange(
			bool				is_single,
			ITypeExpr			*lower,
			ITypeExpr			*upper) override {
		return m_ctxt->mkTypeExprRange(is_single, lower, upper);
	}

	virtual ITypeExprRangelist *mkTypeExprRangelist() override {
		return m_ctxt->mkTypeExprRangelist();
	}

	virtual IModelExprRange *mkModelExprRange(
			bool			is_single,
			IModelExpr		*lower,
			IModelExpr		*upper) override {
		return m_ctxt->mkModelExprRange(is_single, lower, upper);
	}

	virtual IModelExprRangelist *mkModelExprRangelist() override {
		return m_ctxt->mkModelExprRangelist();
	}

	virtual ITypeExprVal *mkTypeExprVal(const IModelVal *v) override {
		return m_ctxt->mkTypeExprVal(v);
	}

	virtual ITypeFieldPhy *mkTypeFieldPhy(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
			IModelVal				*init) override {
		return m_ctxt->mkTypeFieldPhy(name, dtype, own_dtype, attr, init);
	}

	virtual ITypeFieldRef *mkTypeFieldRef(
			const std::string		&name,
			IDataType				*dtype,
			TypeFieldAttr			attr) override {
		return m_ctxt->mkTypeFieldRef(name, dtype, attr);
	}

	virtual ITypeFieldVec *mkTypeFieldVec(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
			IModelVal				*init_sz) override {
		return m_ctxt->mkTypeFieldVec(name, dtype,
			own_dtype, attr, init_sz);
	}

protected:
	IContext				*m_ctxt;

};



}