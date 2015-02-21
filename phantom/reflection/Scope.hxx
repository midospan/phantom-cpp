#pragma once

o_classN((phantom, reflection), Scope, o_deferred) 
(
    o_signal(typeAdded, (Type*))
    o_signal(typeRemoved, (Type*))
    o_signal(templateAdded, (Template*))
    o_signal(templateRemoved, (Template*))
    o_signal(templateSpecializationAdded, (TemplateSpecialization*))
    o_signal(templateSpecializationRemoved, (TemplateSpecialization*))
    o_signal(functionAdded, (Function*))
    o_signal(functionRemoved, (Function*))
    o_signal(variableAdded, (Variable*))
    o_signal(variableRemoved, (Variable*))
    o_signal(aliasAdded, (Alias*))
    o_signal(aliasRemoved, (Alias*))
);





