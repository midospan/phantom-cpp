#include <phantom/phantom.h>

o_registerNT((phantom, reflection, native), (typename), (t_MetaType), TConstType)
o_registerNT((phantom, reflection, native), (typename), (t_Ty), TType_)
o_registerNT((phantom, reflection, native), (typename), (t_Ty), TType)
o_registerNT((phantom, reflection, native), (typename), (t_Ty), TSequentialContainerClass)
o_registerNT((phantom, reflection, native), (typename), (t_Ty), TMapContainerClass)
o_registerNT((phantom, reflection, native), (typename), (t_Ty), TSetContainerClass)
o_registerNT((phantom, reflection, native), (typename, typename),(t_Ty, t_ValueType), TMapValueIteratorConstant);
o_registerNT((phantom, reflection, native), (typename, typename,typename),(t_Ty, t_KeyType, t_ValueType), TMapValueIteratorVariable);
o_registerNT((phantom, reflection, native), (typename, typename),(t_Ty, t_ValueType), TSequentialIteratorConstant);
o_registerNT((phantom, reflection, native), (typename, typename),(t_Ty, t_ValueType), TSequentialIteratorVariable);
o_registerNT((phantom, reflection, native), (typename, typename),(t_Ty, t_ValueType), TSetIteratorConstant);
o_registerNT((phantom, reflection, native), (typename, typename),(t_Ty, t_ValueType), TSetIteratorVariable);