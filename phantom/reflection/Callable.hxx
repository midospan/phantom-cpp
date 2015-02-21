#pragma once

o_classN((phantom, reflection), Callable, o_deferred|o_abstract) 
(
o_public:
    o_member_function(void, call, (void**), o_virtual);
    o_member_function(void, call, (void**, void*), o_virtual);
);





