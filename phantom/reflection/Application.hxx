#pragma once

#include "NamedElement.hxx"

o_classNB((phantom, reflection), Application, (NamedElement))
(
        o_slot(void, moduleInstanciated, (void*));
        o_slot(void, moduleDeleted, (void*));
        o_signal(libraryAboutToBeLoaded, (const string&));
        o_signal(libraryLoaded, (const string&));
        o_signal(libraryAboutToBeUnloaded, (const string&));
        o_signal(libraryUnloaded, (const string&));
        o_signal(libraryLoadFailed, (const string&));
        o_signal(libraryUnloadFailed, (const string&));
        o_signal(moduleCreated, (Module*));
        o_signal(moduleDestroyed, (Module*));
        o_signal(moduleAboutToBeDestroyed, (Module*));
        o_signal(moduleLoaded, (Module*, size_t, size_t));
        o_signal(moduleUnloaded, (Module*, size_t, size_t));
        o_signal(elementAdded, (LanguageElement*));
        o_signal(elementAboutToBeRemoved, (LanguageElement*));
        o_signal(elementsReplaced, (const vector<LanguageElement*>&, const vector<LanguageElement*>&));
        o_signal(elementsAboutToBeReplaced, (const vector<LanguageElement*>&));
);
