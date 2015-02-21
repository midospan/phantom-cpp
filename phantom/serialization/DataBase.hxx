#pragma once

o_classN((phantom, serialization), DataBase, o_deferred|o_abstract) 
(
o_protected:
    o_signal(dataAdded, (const phantom::data&, Node*));
    o_signal(dataAboutToBeRemoved, (const phantom::data&, Node*));
    o_signal(dataAboutToBeAborted, (const phantom::data&, Node*));
    o_signal(dataMoved, (const phantom::data&, Node*, Node*));
    o_signal(dataAttributeValueChanged, (const phantom::data&, size_t, const string&));
    o_signal(dataModifiersChanged, (const phantom::data&, modifiers_t));
    o_signal(dataAboutToBeReplaced, (const phantom::data&, Node*));
    o_signal(dataReplaced, (const phantom::data&, Node*));
    o_signal(dataAboutToBeUnloaded, (const phantom::data&, Node*));
    o_signal(dataReloaded, (const phantom::data&, Node*));
    o_signal(dataErased, (uint));
    o_signal(dataRestored, (uint));
    o_signal(dataAggregationChanged, (const phantom::data&, const string&, const string&));
    o_signal(dataCompositionChanged, (const phantom::data&, const string&, const string&));
    o_signal(dataPropertyValueChanged, (const phantom::data&, reflection::Property*, const variant&, const variant&));
    o_signal(componentOwnershipLost, (const phantom::data&));

    o_signal(nodeAdded, (Node*, Node*));
    o_signal(nodeAboutToBeRemoved, (Node*, Node*));
    o_signal(nodeLoaded, (Node*));
    o_signal(nodeAboutToBeUnloaded, (Node*));
    o_signal(nodeMoved, (Node*, Node*, Node*));
    o_signal(nodeAttributeValueChanged, (Node*, size_t, const string&));
    o_signal(componentReferenceExpressionChanged, (const phantom::data&, const string&, const string&));

    o_slot(void, moduleElementAboutToBeRemoved, (reflection::LanguageElement*));
    o_slot(void, moduleElementAdded, (reflection::LanguageElement*));
    o_slot(void, moduleElementsAboutToBeReplaced, (const vector<reflection::LanguageElement*>&));
    o_slot(void, moduleElementsReplaced, (const vector<reflection::LanguageElement*>&, const vector<reflection::LanguageElement*>&));
    o_slot(void, moduleLoaded, (reflection::Module*, size_t, size_t));

    o_slot(void, componentChanged, (void*, void*));
    o_slot(void, componentInserted, (size_t, void*));
    o_slot(void, componentAboutToBeRemoved, (size_t, void*));
    o_slot(void, componentReplaced, (size_t, void*, void*));
    o_slot(void, componentMoved, (size_t, size_t, void*));
    o_slot(void, componentSwapped, (size_t, size_t, void*, void*));

    o_slot(void, aggregateInserted, (size_t, void*));
    o_slot(void, aggregateAboutToBeRemoved, (size_t, void*));
    o_slot(void, aggregateReplaced, (size_t, void*, void*));
    o_slot(void, aggregateMoved, (size_t, size_t, void*));
    o_slot(void, aggregateSwapped, (size_t, size_t, void*, void*));
    o_slot(void, slotNodeLoaded, ());
    o_slot(void, slotNodeAboutToBeUnloaded, ());

    o_slot(void, propertyChanged, ());

o_public:
    o_member_function(uint, getGuid, ( const phantom::data&), o_public_access);
    o_member_function(const phantom::data&, getData, (uint), o_public_access);
);

