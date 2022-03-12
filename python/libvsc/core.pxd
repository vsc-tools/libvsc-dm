
from libvsc cimport decl
from libc.stdint cimport intptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
cimport cpython.ref as cpy_ref

cdef class Vsc(object):
    cdef decl.IVsc              *_hndl
    
    cdef decl.IContext *mkContext(self)
   
cdef class Context(object):
    cdef decl.IContext               *_hndl
    
    cpdef mkDataTypeInt(self, bool is_signed, int width)
    cpdef mkModelFieldRoot(self, DataType type, name)
    
cdef class DataType(object):
    cdef decl.IDataType         *_hndl
    
    @staticmethod
    cdef mk(decl.IDataType *, owned=*)

cdef class DataTypeInt(DataType):

    @staticmethod
    cdef mk(decl.IDataTypeInt *, owned=*)
    
    cdef decl.IDataTypeInt *asTypeInt(self)
    

cdef class ModelExpr(object):
    cdef decl.IModelExpr         *_hndl
    cdef bool                    _owned
    
    cpdef accept(self, VisitorBase v)
    
    @staticmethod
    cdef mkWrapper(decl.IModelExpr *e)

cdef class ModelExprBin(ModelExpr):

    @staticmethod
    cdef mkWrapper(decl.IModelExprBin *e)
    cdef decl.IModelExprBin *asExprBin(self)
    
cdef class ModelField(object):
    cdef decl.IModelField       *_hndl
    
    cpdef name(self)
    cpdef getDataType(self)
    cpdef getParent(self)
    cpdef setParent(self, ModelField)
    cpdef fields(self)
    cpdef addField(self, ModelField)
    cpdef val(self)

    @staticmethod
    cdef mk(decl.IModelField *, owned=*)

cdef class ModelVal(object):
    cdef decl.IModelVal         *_hndl
    cdef bool                   _owned

    cpdef bits(self)
    cpdef val_u(self)
    cpdef val_i(self)
    cpdef set_val_i(self, int64_t v, int32_t bits=*)
    cpdef set_val_u(self, uint64_t, int32_t bits=*)
    
    @staticmethod 
    cdef mk(decl.IModelVal *, owned=*)
    
cdef class VisitorBase(object):
    cdef decl.VisitorProxy      *_proxy
    
    cpdef visitModelExprBin(self, ModelExprBin e)