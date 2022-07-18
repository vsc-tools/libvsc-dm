
from libvsc cimport decl
from libc.stdint cimport intptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
from libcpp.vector cimport vector as cpp_vector
from enum import IntFlag, IntEnum
cimport cpython.ref as cpy_ref

cdef class Vsc(object):
    cdef decl.IVsc              *_hndl
    
    cpdef Context mkContext(self)
   
cdef class Context(object):
    cdef decl.IContext               *_hndl
    cdef bool                        _owned

    cpdef ModelField buildModelField(self, DataTypeStruct, name=*)
    cpdef mkCompoundSolver(self)
    cpdef DataTypeEnum findDataTypeEnum(self, name)
    cpdef DataTypeEnum mkDataTypeEnum(self,
        name,
        bool is_signed)
    cpdef addDataTypeEnum(self, DataTypeEnum)
    cpdef mkModelConstraintBlock(self, name)
    cpdef mkModelConstraintExpr(self, ModelExpr)
    cpdef mkModelConstraintIfElse(self, 
        ModelExpr           cond,
        ModelConstraint     true_c,
        ModelConstraint     false_c)
    cpdef mkModelConstraintImplies(self, 
        ModelExpr           cond,
        ModelConstraint     body)
    cpdef mkModelConstraintScope(self)
    cpdef bool addDataTypeInt(self, DataTypeInt)
    cpdef DataTypeInt findDataTypeInt(self, bool is_signed, int width)
    cpdef DataTypeInt mkDataTypeInt(self, bool is_signed, int width)
    cpdef bool addDataTypeStruct(self, DataTypeStruct)
    cpdef DataTypeStruct findDataTypeStruct(self, name)
    cpdef DataTypeStruct mkDataTypeStruct(self, name)
    cpdef mkModelExprBin(self, ModelExpr, op, ModelExpr)
    cpdef mkModelExprIn(self, ModelExpr, ModelExprRangelist)
    cpdef mkModelExprFieldRef(self, ModelField field)
    cpdef mkModelExprPartSelect(self, ModelExpr lhs, int32_t lower, int32_t upper)
    cpdef mkModelExprRange(self, bool, ModelExpr, ModelExpr)
    cpdef mkModelExprRangelist(self)
    cpdef mkModelExprVal(self, ModelVal)
    cpdef mkModelFieldRoot(self, DataType type, name)
    cpdef mkModelFieldVecRoot(self, DataType type, name)
    cpdef mkModelVal(self)
    cpdef mkRandState(self, uint32_t seed)
    cpdef mkRandomizer(self, SolverFactory, RandState)
    cpdef TypeConstraintBlock mkTypeConstraintBlock(self, name)
    cpdef TypeConstraintExpr mkTypeConstraintExpr(self, TypeExpr)
    cpdef TypeConstraintIfElse mkTypeConstraintIfElse(self, 
        TypeExpr        cond,
        TypeConstraint  true_c,
        TypeConstraint  false_c)
    cpdef TypeConstraintScope mkTypeConstraintScope(self)
    cpdef TypeExprBin mkTypeExprBin(self, TypeExpr, op, TypeExpr)
    cpdef TypeExprFieldRef mkTypeExprFieldRef(self)
    cpdef TypeExprRange mkTypeExprRange(self, bool, TypeExpr, TypeExpr)
    cpdef TypeExprRangelist mkTypeExprRangelist(self)
    cpdef TypeExprVal mkTypeExprVal(self, ModelVal)
    cpdef TypeFieldPhy mkTypeFieldPhy(self, name, DataType, bool, attr, ModelVal)
    cpdef TypeFieldRef mkTypeFieldRef(self, name, DataType, attr)

    @staticmethod    
    cdef mk(decl.IContext *hndl, bool owned=*)

    
cdef class CompoundSolver(object):
    cdef decl.ICompoundSolver   *_hndl
    
    cpdef solve(self, RandState, fields, constraints, flags)
    
    @staticmethod
    cdef mk(decl.ICompoundSolver *)
    
cdef class Accept(object):
    cdef decl.IAccept *hndl(self)
    
cdef class DataType(object):
    cdef decl.IDataType         *_hndl
    cdef bool                   _owned
    
#    cdef decl.IAccept *hndl(self)
    
    @staticmethod
    cdef mk(decl.IDataType *, bool owned=*)
    
cdef class DataTypeEnum(DataType):

    cpdef name(self)
    
    cpdef isSigned(self)
    
    cpdef addEnumerator(self, name, ModelVal val)
    
    cpdef getDomain(self)
    
    cdef decl.IDataTypeEnum *asEnum(self)
    
    @staticmethod
    cdef mk(decl.IDataTypeEnum *, bool owned=*)

cdef class DataTypeInt(DataType):

    @staticmethod
    cdef mk(decl.IDataTypeInt *, bool owned=*)
    
    cdef decl.IDataTypeInt *asTypeInt(self)
    
cdef class DataTypeStruct(DataType):

    cpdef name(self)
    cpdef addField(self, TypeField f)
    cpdef getFields(self)
    cpdef TypeField getField(self, int32_t idx)
    cpdef addConstraint(self, TypeConstraint c)
    cpdef getConstraints(self)
    cpdef setCreateHook(self, hook_f)

    @staticmethod
    cdef mk(decl.IDataTypeStruct *, bool owned=*)

    cdef decl.IDataTypeStruct *asTypeStruct(self)
    
cdef class ModelConstraint(object):
    cdef decl.IModelConstraint   *_hndl
    cdef bool                    _owned

    cdef decl.IModelConstraint *asConstraint(self)
    
    @staticmethod
    cdef mk(decl.IModelConstraint *hndl, bool owned=*)
    
cdef class ModelConstraintScope(ModelConstraint):
    cpdef constraints(self)
    cpdef addConstraint(self, ModelConstraint)
    
    cdef decl.IModelConstraintScope *asScope(self)

    @staticmethod
    cdef mk(decl.IModelConstraintScope *hndl, bool owned=*)
    
cdef class ModelConstraintBlock(ModelConstraintScope):
    cpdef name(self)
    
    cdef decl.IModelConstraintBlock *asModelConstraintBlock(self)
    
    @staticmethod
    cdef mk(decl.IModelConstraintBlock *hndl, bool owned=*)
    
   
cdef class ModelConstraintExpr(ModelConstraint):

    cpdef expr(self)

    cdef decl.IModelConstraintExpr *asModelConstraintExpr(self)
    @staticmethod
    cdef mk(decl.IModelConstraintExpr *, bool owned=*)

cdef class ModelConstraintIfElse(ModelConstraint):
    cpdef getCond(self)
    cpdef getTrue(self)
    cpdef getFalse(self)
    cpdef setFalse(self, ModelConstraint c)

    cdef decl.IModelConstraintIfElse *asIfElse(self)
    @staticmethod
    cdef mk(decl.IModelConstraintIfElse *, bool owned=*)

cdef class ModelConstraintImplies(ModelConstraint):
    cpdef getCond(self)
    cpdef getBody(self)

    cdef decl.IModelConstraintImplies *asImplies(self)

    @staticmethod
    cdef mk(decl.IModelConstraintImplies *hndl, bool owned=*)
    
cdef class ModelExpr(object):
    cdef decl.IModelExpr         *_hndl
    cdef bool                    _owned
    
    cpdef accept(self, VisitorBase v)
    
    cdef decl.IModelExpr *asExpr(self)
    
    @staticmethod
    cdef mk(decl.IModelExpr *e, bool owned=*)
    


cdef class ModelExprBin(ModelExpr):

    @staticmethod
    cdef mkWrapper(decl.IModelExprBin *e)
    cdef decl.IModelExprBin *asExprBin(self)
    
cdef class ModelExprIn(ModelExpr):

    @staticmethod
    cdef mk(decl.IModelExprIn *e, bool owned=*)
    
    cdef decl.IModelExprIn *asExprIn(self)

    
cdef class ModelExprFieldRef(ModelExpr):

    cpdef field(self)

    cdef decl.IModelExprFieldRef *asExprFieldRef(self)
    
    @staticmethod
    cdef mk(decl.IModelExprFieldRef *, bool owned=*)
    
cdef class ModelExprPartSelect(ModelExpr):

    cpdef lhs(self)
    
    cpdef int32_t lower(self)
    
    cpdef int32_t upper(self)
    
    cdef decl.IModelExprPartSelect *asPartSelect(self)
    
    @staticmethod
    cdef mk(decl.IModelExprPartSelect *, bool owned=*)
    
cdef class ModelExprRange(ModelExpr):
    cpdef isSingle(self)
    
    cpdef ModelExpr lower(self)
    
    cpdef ModelExpr upper(self)
    
    cdef decl.IModelExprRange *asRange(self)
    
    @staticmethod 
    cdef mk(decl.IModelExprRange *, bool owned=*)
    
cdef class ModelExprRangelist(ModelExpr): 
    
    cpdef ranges(self)
    
    cpdef addRange(self, ModelExprRange)
    
    cdef decl.IModelExprRangelist *asRangelist(self)
    
    @staticmethod 
    cdef mk(decl.IModelExprRangelist *, bool owned=*)
    
cdef class ModelExprUnary(ModelExpr):

    cpdef ModelExpr expr(self)
    cpdef op(self)
    
    cdef decl.IModelExprUnary *asUnary(self)
    
    @staticmethod
    cdef mk(decl.IModelExprUnary *, bool owned=*)
        
    
cdef class ModelExprVal(ModelExpr):

    cpdef width(self)
    cpdef val(self)
    
    cdef decl.IModelExprVal *asModelExprVal(self)
    
    @staticmethod
    cdef mk(decl.IModelExprVal *, bool owned=*)

cdef class ModelField(object):
    cdef decl.IModelField       *_hndl
    cdef bool                   _owned
    
    cpdef name(self)
    cpdef getDataType(self)
    cpdef getParent(self)
    cpdef setParent(self, ModelField)
    cpdef constraints(self)
    cpdef addConstraint(self, ModelConstraint)
    cpdef fields(self)
    cpdef addField(self, ModelField)
    cpdef ModelField getField(self, int32_t idx)
    cpdef val(self)
    
    cpdef clearFlag(self, flags)
    cpdef setFlag(self, flags)
    cpdef isFlagSet(self, flags)
    cpdef setFieldData(self, data)
    cpdef getFieldData(self)

    @staticmethod
    cdef mk(decl.IModelField *, bool owned=*)
    
cdef class ModelFieldRef(ModelField):
    pass
    
cdef class ModelFieldRoot(ModelField):

    cpdef setName(self, name)

    cdef decl.IModelFieldRoot *asRoot(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldRoot *, bool owned=*)
    
cdef class ModelFieldType(ModelField):

    cdef decl.IModelFieldType *asType(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldType *, bool owned=*)
    
cdef class ModelFieldVec(ModelField):

    cpdef getSizeRef(self)
    
    cpdef getSize(self)
    
    cdef decl.IModelFieldVec *asVec(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldVec *, bool owned=*)
    
cdef class ModelFieldVecRoot(ModelFieldVec):

    cpdef void setName(self, name)

    cdef decl.IModelFieldVecRoot *asVecRoot(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldVecRoot *, bool owned=*)
    
cdef class ModelFieldDataClosure(object):
    cdef decl.IModelFieldData       *_hndl
    
    cpdef getData(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldData *)

cdef class ModelVal(object):
    cdef decl.IModelVal         *_hndl
    cdef bool                   _owned

    cpdef bits(self)
    cpdef setBits(self, b)
    cpdef val_u(self)
    cpdef val_i(self)
    cpdef set_val_i(self, int64_t v, int32_t bits=*)
    cpdef set_val_u(self, uint64_t, int32_t bits=*)
    
    @staticmethod 
    cdef mk(decl.IModelVal *, owned=*)
    
cdef class Randomizer(object):
    cdef decl.IRandomizer      *_hndl
    
    cpdef randomize(self, list fields, list, bool)
    
    @staticmethod
    cdef mk(decl.IRandomizer *hndl)
    
cdef class RandState(object):
    cdef decl.IRandState       *_hndl
    
    cpdef randint32(self, int32_t, int32_t)
    cpdef randbits(self, ModelVal)
    
    @staticmethod
    cdef mk(decl.IRandState *)
    
cdef class SolverFactory(object):
    cdef decl.ISolverFactory    *_hndl
    
cdef class Task(object):
    cdef decl.ITask             *_hndl
    
    cpdef apply(self, Accept it)
    
cdef class TypeConstraint(object):
    cdef decl.ITypeConstraint   *_hndl
    cdef bool                   _owned

    cdef decl.ITypeConstraint *asConstraint(self)
    
    @staticmethod
    cdef TypeConstraint mk(decl.ITypeConstraint *, bool owned=*)

cdef class TypeConstraintExpr(TypeConstraint):

    cpdef TypeExpr expr(self)

    cdef decl.ITypeConstraintExpr *asExpr(self)

    @staticmethod
    cdef TypeConstraintExpr mk(decl.ITypeConstraint *, bool owned=*)

cdef class TypeConstraintIfElse(TypeConstraint):
    cpdef getCond(self)
    cpdef getTrue(self)
    cpdef getFalse(self)
    cpdef setFalse(self, TypeConstraint c)

    cdef decl.ITypeConstraintIfElse *asIfElse(self)

    @staticmethod
    cdef TypeConstraintIfElse mk(decl.ITypeConstraintIfElse *hndl, bool owned=*)
   
cdef class TypeConstraintScope(TypeConstraint):
    
    cpdef addConstraint(self, TypeConstraint)
    
    cdef decl.ITypeConstraintScope *asScope(self)
    
    @staticmethod
    cdef TypeConstraintScope mk(decl.ITypeConstraintScope *, bool owned=*)
    
cdef class TypeConstraintBlock(TypeConstraintScope):
    
    cpdef name(self)
    
    cdef decl.ITypeConstraintBlock *asBlock(self)
    
    @staticmethod
    cdef TypeConstraintBlock mk(decl.ITypeConstraintBlock *, bool owned=*)

cdef class TypeExpr(object):
    cdef decl.ITypeExpr         *_hndl
    cdef bool                   _owned

    cdef decl.ITypeExpr *asExpr(self)
    
    @staticmethod
    cdef TypeExpr mk(decl.ITypeExpr *hndl, bool owned=*)
    
cdef class TypeExprRange(TypeExpr):

    cpdef isSingle(self)

    cpdef TypeExpr lower(self)
    
    cpdef TypeExpr upper(self)
  
    cdef decl.ITypeExprRange *asRange(self)
      
    @staticmethod
    cdef TypeExprRange mk(decl.ITypeExprRange *, bool owned=*)

cdef class TypeExprRangelist(TypeExpr):    

    cpdef addRange(self, TypeExprRange r)
    
    cpdef getRanges(self)
    
    cdef decl.ITypeExprRangelist *asRangelist(self)

    @staticmethod
    cdef TypeExprRangelist mk(decl.ITypeExprRangelist *hndl, bool owned=*)
    
cdef class TypeExprFieldRefElem(object):
    cdef const decl.TypeExprFieldRefElem   *_hndl

    cpdef getKind(self)
    cpdef int32_t getIdx(self)

cdef class TypeExprBin(TypeExpr):

    cpdef TypeExpr lhs(self)
    cpdef op(self)
    cpdef TypeExpr rhs(self)

    cdef decl.ITypeExprBin *asBin(self)
        
    @staticmethod
    cdef TypeExprBin mk(decl.ITypeExprBin *hndl, bool owned=*)    

cdef class TypeExprFieldRef(TypeExpr):

    cpdef addIdxRef(self, int32_t idx)
    cpdef addRootRef(self)
    cpdef addActiveScopeRef(self, off)
    cpdef uint32_t size(self)
    cpdef TypeExprFieldRefElem at(self, idx)
    
    cdef decl.ITypeExprFieldRef *asFieldRef(self)
    
    @staticmethod
    cdef TypeExprFieldRef mk(decl.ITypeExprFieldRef *hndl, bool owned=*)
    
cdef class TypeExprVal(TypeExpr):
    cpdef ModelVal val(self)
    
    cdef decl.ITypeExprVal *asVal(self)
    
    @staticmethod
    cdef TypeExprVal mk(decl.ITypeExprVal *hndl, bool owned=*)
    
cdef class TypeField(object):
    cdef decl.ITypeField        *_hndl
    cdef bool                   _owned
    
    cpdef DataTypeStruct getParent(self)
    cpdef setParent(self, DataTypeStruct)
    cpdef getIndex(self)
    cpdef setIndex(self, idx)
    cpdef name(self)
    cpdef DataType getDataType(self)
    cpdef TypeField getField(self, idx)
    cpdef getAttr(self)

    @staticmethod
    cdef mk(decl.ITypeField *, bool owned=*)

cdef class TypeFieldPhy(TypeField):

    cpdef ModelVal getInit(self)
    
    cdef decl.ITypeFieldPhy *asPhy(self)
    
    @staticmethod
    cdef mk(decl.ITypeFieldPhy *, bool owned=*)

cdef class TypeFieldRef(TypeField):

    @staticmethod
    cdef mk(decl.ITypeFieldRef *, bool owned=*)    
    
cdef class VisitorBase(object):
    cdef decl.VisitorProxy      *_proxy
    
    cpdef visit(self, obj)
    
    cpdef visitDataTypeEnum(self, DataTypeEnum t)
    
    cpdef visitDataTypeInt(self, DataTypeInt t)
    
    cpdef visitDataTypeStruct(self, DataTypeStruct t)

    cpdef visitModelConstraintBlock(self, ModelConstraintBlock c)

    cpdef visitModelConstraintExpr(self, ModelConstraintExpr c)

    cpdef visitModelConstraintIfElse(self, ModelConstraintIfElse c)

    cpdef visitModelConstraintImplies(self, ModelConstraintImplies c)
    
    cpdef visitModelExprBin(self, ModelExprBin e)
    
    cpdef void visitModelFieldRef(self, ModelFieldRef f)

    cpdef void visitModelFieldRefRoot(self, ModelFieldRef f)

    cpdef void visitModelFieldRefType(self, ModelFieldRef f)

    cpdef void visitModelFieldRoot(self, ModelFieldRoot f)

    cpdef void visitModelFieldType(self, ModelFieldType f)
    
cdef class WrapperBuilder(VisitorBase):
    cdef DataType _data_type
    cdef ModelField _model_field
    cdef ModelConstraint _model_constraint
    
    cdef DataType mkDataType(self, decl.IDataType *obj, bool owned)
    
    cdef ModelField mkModelField(self, decl.IModelField *obj, bool owned)

    cdef ModelConstraint mkModelConstraint(self, decl.IModelConstraint *obj, bool owned)

    cpdef visitModelConstraintBlock(self, ModelConstraintBlock c)

    cpdef visitModelConstraintExpr(self, ModelConstraintExpr c)

    cpdef visitModelConstraintIfElse(self, ModelConstraintIfElse c)

    cpdef visitModelConstraintImplies(self, ModelConstraintImplies c)
    
    
#********************************************************************    
#* VscTasks
#********************************************************************
cpdef ModelField Task_ModelBuildField(
    Context     ctxt,
    DataType    dt, 
    name)
