#pragma once

o_classN((phantom), Module, o_deferred|o_no_default_constructor) 
(
    o_signal(elementAboutToBeRemoved, (reflection::LanguageElement*));
    o_signal(elementAdded, (reflection::LanguageElement*));
    o_signal(elementsAboutToBeReplaced, (const vector<reflection::LanguageElement*>&));
    o_signal(elementsReplaced, (const vector<reflection::LanguageElement*>&, const vector<reflection::LanguageElement*>&));
);





