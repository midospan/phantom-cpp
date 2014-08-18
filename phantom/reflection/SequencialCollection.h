#ifndef o_reflection_SequencialCollection_h__
#define o_reflection_SequencialCollection_h__


/* ****************** Includes ******************* */
#include <phantom/reflection/reflection.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), SequencialCollection);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class SequencialCollection
{
public:
	SequencialCollection(void) {}
	~SequencialCollection(void) {}

    virtual Signal* getAddedSignal() const = 0;
    virtual Signal* getRemovedSignal() const = 0;
    virtual Signal* getAboutToBeRemovedSignal() const = 0;
    virtual Signal* getSwapedSignal() const = 0;

    virtual void add(void* a_pInstance, void* a_pSrc) const = 0;
    virtual void remove(void* a_pInstance, void* a_pSrc) const = 0;
    virtual void set(void* a_pInstance, size_t a_Index, void* a_pSrc) const = 0;
    virtual void swap(void* a_pInstance, size_t a_Index0, size_t a_Index1) const = 0;
    virtual void iterator(const void* a_pInstance, Iterator** a_ppIterator) const = 0;

protected:

};

o_namespace_end(phantom, reflection)

#endif // o_reflection_SequencialCollection_h__
