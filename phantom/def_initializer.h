/* TODO LICENCE HERE */

#ifndef o_def_initializer_h__
#define o_def_initializer_h__

o_namespace_begin(phantom)

/* initialization */
namespace detail
{
    enum default_initializer_id
    {
        default_initializer_member_function_and_instanciation_notification,
        default_initializer_none,
    };

    template<typename t_Ty>
    struct default_initializer_helper<t_Ty, default_initializer_none>
    {
        o_forceinline static void initialize(reflection::Type*, t_Ty* a_pInstance) {  }
        o_forceinline static void terminate(reflection::Type*, t_Ty* a_pInstance) {  }
        o_forceinline static void initialize(reflection::Type*, t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) {  }
        o_forceinline static void terminate(reflection::Type*, t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) {  }
        o_forceinline static restore_state restore(reflection::Type*, t_Ty* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass) { return restore_complete; }
        o_forceinline static restore_state restore(reflection::Type*, t_Ty* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize) { return restore_complete; }
    };


    // INITIALIZER METHODS (RECURSIVE) CALLERS

    template<typename t_Ty>
    struct initialize_member_function_caller;
    template<typename t_Ty>
    struct terminate_member_function_caller;
    template<typename t_Ty>
    struct restore_member_function_caller;
    template<typename t_Ty>
    struct destroyed_signal_emitter;


    // INITIALIZE CALLER

    template<typename t_Ty, int t_base_class_count_of, bool t_declared>
    struct initialize_member_function_caller_base_
    {
        typedef typename base_class_of<t_Ty,t_base_class_count_of-1>::type base_class;
        static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance)
        {
            // Call base first
            initialize_member_function_caller<base_class>::apply(a_pClass->getBaseClass(t_base_class_count_of-1), a_pInstance);

            // Then the current class
            initialize_member_function_caller_base_<t_Ty, t_base_class_count_of-1, t_declared>::apply(a_pClass, a_pInstance);
        }
    };

    template<typename t_Ty>
    struct initialize_member_function_caller_base_<t_Ty, 0, false>
    {
        inline static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance)
        {
            a_pClass->initializeDataMembers(a_pInstance);
        }
    };

    template<typename t_Ty>
    struct initialize_member_function_caller_friend_breaker;

    template<typename t_Ty>
    struct initialize_member_function_caller_base_<t_Ty, 0, true>
    {
        inline static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance)
        {
            a_pClass->initializeDataMembers(a_pInstance);
            static_cast<initialize_member_function_caller_friend_breaker<t_Ty>*>(a_pInstance)->PHANTOM_CODEGEN_initialize();
        }
    };

    template<typename t_Ty>
    struct initialize_member_function_caller_friend_breaker : public t_Ty
    {
        template<typename t_Ty2, int t_base_class_count_of, bool t_has_initialize_member_function, bool t_declared>
        friend struct initialize_member_function_caller_helper_;
    };

    template<typename t_Ty, int t_base_class_count_of, bool t_has_initialize_member_function, bool t_declared>
    struct initialize_member_function_caller_helper_
        : public initialize_member_function_caller_base_<t_Ty, t_base_class_count_of, t_declared>
    {

    };

    template<typename t_Ty, int t_base_class_count_of, bool t_declared>
    struct initialize_member_function_caller_helper_<t_Ty, t_base_class_count_of, false, t_declared>
    {
        inline static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance)
        {
            a_pClass->initializeDataMembers(a_pInstance);
        }
    };

    template<typename t_Ty>
    struct initialize_member_function_caller
        : public initialize_member_function_caller_helper_<t_Ty
        , base_class_count_of<t_Ty>::value
        , has_initializer_member_function_initialize<t_Ty>::value
        , has_initializer_member_function_initialize_declared<t_Ty>::value>
    {
    };

    // RESTORE CALLER

    template<typename t_Ty, int t_base_class_count_of, bool t_declared>
    struct restore_member_function_caller_base_
    {
        typedef typename base_class_of<t_Ty,t_base_class_count_of-1>::type base_class;

        static restore_state apply(reflection::Class* a_pClass, t_Ty* a_pInstance, uint filter, restore_pass pass)
        {
            // Call base first
            restore_state result = restore_member_function_caller<base_class>::apply(a_pClass->getBaseClass(t_base_class_count_of-1), a_pInstance, filter, pass);
            // Then the current class
            return combine_restore_states(result, restore_member_function_caller_base_<t_Ty, t_base_class_count_of-1, t_declared>::apply(a_pClass, a_pInstance, filter, pass));
        }
    };

    template<typename t_Ty>
    struct restore_member_function_caller_friend_breaker;

    template<typename t_Ty>
    struct restore_member_function_caller_base_<t_Ty, 0, true>
    {
        inline static restore_state apply(reflection::Class* a_pClass, t_Ty* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass)
        {
            restore_state result = a_pClass->restoreDataMembers(a_pInstance, a_uiSerializationFlag, a_uiPass);
            return combine_restore_states(result, static_cast<restore_member_function_caller_friend_breaker<t_Ty>*>(a_pInstance)->PHANTOM_CODEGEN_restore(a_uiSerializationFlag, a_uiPass));
        }
    };

    template<typename t_Ty>
    struct restore_member_function_caller_base_<t_Ty, 0, false>
    {
        inline static restore_state apply(reflection::Class* a_pClass, t_Ty* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass)
        {
            return a_pClass->restoreDataMembers(a_pInstance, a_uiSerializationFlag, a_uiPass);
        }
    };

    template<typename t_Ty>
    struct restore_member_function_caller_friend_breaker : public t_Ty
    {
        template<typename t_Ty2, int t_base_class_count_of, bool t_has_restore_member_function, bool t_declared>
        friend struct restore_member_function_caller_helper_;
    };

    template<typename t_Ty, int t_base_class_count_of, bool t_has_restore_member_function, bool t_declared>
    struct restore_member_function_caller_helper_ : public restore_member_function_caller_base_<t_Ty, t_base_class_count_of, t_declared>
    {

    };

    template<typename t_Ty, int t_base_class_count_of, bool t_declared>
    struct restore_member_function_caller_helper_<t_Ty, t_base_class_count_of, false, t_declared>
    {
        inline static restore_state apply(reflection::Class* a_pClass, t_Ty* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass)
        {
            return a_pClass->restoreDataMembers(a_pInstance, a_uiSerializationFlag, a_uiPass);
        }
    };

    template<typename t_Ty>
    struct restore_member_function_caller
        : public restore_member_function_caller_helper_<t_Ty
        , base_class_count_of<t_Ty>::value
        , has_initializer_member_function_restore<t_Ty>::value
        , has_initializer_member_function_restore_declared<t_Ty>::value>
    {

    };

    // TERMINATE CALLER

    template<typename t_Ty, int t_base_class_count_of, bool t_declared>
    struct terminate_member_function_caller_base_
    {
        typedef typename base_class_of<t_Ty,t_base_class_count_of-1>::type base_class;
        static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance)
        {
            // Current class first
            terminate_member_function_caller_base_<t_Ty, t_base_class_count_of-1, t_declared>::apply(a_pClass, a_pInstance);
            // Then base classes
            terminate_member_function_caller<base_class>::apply(a_pClass->getBaseClass(t_base_class_count_of-1), a_pInstance);
        }
    };

    template<typename t_Ty>
    struct terminate_member_function_caller_friend_breaker;

    template<typename t_Ty>
    struct terminate_member_function_caller_base_<t_Ty, 0, true>
    {
        inline static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance)
        {
            static_cast<terminate_member_function_caller_friend_breaker<t_Ty>*>(a_pInstance)->PHANTOM_CODEGEN_terminate();
            a_pClass->terminateDataMembers(a_pInstance);
        }
    };

    template<typename t_Ty>
    struct terminate_member_function_caller_base_<t_Ty, 0, false>
    {
        inline static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance)
        {
            a_pClass->terminateDataMembers(a_pInstance);
        }
    };

    template<typename t_Ty>
    struct terminate_member_function_caller_friend_breaker : public t_Ty
    {
        template<typename t_Ty2, int t_base_class_count_of, bool t_has_terminate_member_function, bool t_declared>
        friend struct terminate_member_function_caller_helper_;
    };

    template<typename t_Ty, int t_base_class_count_of, bool t_has_terminate_member_function, bool t_declared>
    struct terminate_member_function_caller_helper_ : public terminate_member_function_caller_base_<t_Ty, t_base_class_count_of, t_declared>
    {

    };

    template<typename t_Ty, int t_base_class_count_of, bool t_declared>
    struct terminate_member_function_caller_helper_<t_Ty, t_base_class_count_of, false, t_declared>
    {
        inline static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance)
        {
            a_pClass->terminateDataMembers(a_pInstance);
        }
    };

    template<typename t_Ty>
    struct terminate_member_function_caller
        : public terminate_member_function_caller_helper_<t_Ty
        , base_class_count_of<t_Ty>::value
        , has_initializer_member_function_terminate<t_Ty>::value
        , has_initializer_member_function_terminate_declared<t_Ty>::value>
    {
    };

    // INITIALIZE CALLER
    template<typename t_Ty>
    struct destroyed_signal_emitter_friend_breaker;

    template<typename t_Ty, int t_base_class_count_of, bool t_declared>
    struct destroyed_signal_emitter_base_
    {
        static void apply(t_Ty* a_pInstance)
        {
            // Call base first
            destroyed_signal_emitter<typename base_class_of<t_Ty,t_base_class_count_of-1>::type>::apply(a_pInstance);

            // Then the current class
            destroyed_signal_emitter_base_<t_Ty, t_base_class_count_of-1, t_declared>::apply(a_pInstance);
        }
    };

    template<typename t_Ty>
    struct destroyed_signal_emitter_base_<t_Ty, 0, true>
    {
        inline static void apply(t_Ty* a_pInstance)
        {
            static_cast<destroyed_signal_emitter_friend_breaker<t_Ty>*>(a_pInstance)->PHANTOM_CODEGEN_destroyed();
        }
    };

    template<typename t_Ty>
    struct destroyed_signal_emitter_base_<t_Ty, 0, false>
    {
        inline static void apply(t_Ty* a_pInstance) {}
    };

    template<typename t_Ty>
    struct destroyed_signal_emitter_friend_breaker : public t_Ty
    {
        template<typename t_Ty2, int t_base_class_count_of, bool t_has_initialize_member_function, bool t_declared>
        friend struct destroyed_signal_emitter_helper_;
    };

    template<typename t_Ty, int t_base_class_count_of, bool t_has_initialize_member_function, bool t_declared>
    struct destroyed_signal_emitter_helper_
        : public destroyed_signal_emitter_base_<t_Ty, t_base_class_count_of, t_declared> {};

    template<typename t_Ty, int t_base_class_count_of, bool t_declared>
    struct destroyed_signal_emitter_helper_<t_Ty, t_base_class_count_of, false, t_declared>
    {
        inline static void apply(t_Ty* a_pInstance) {}
    };

    template<typename t_Ty>
    struct destroyed_signal_emitter
        : public destroyed_signal_emitter_helper_<t_Ty
        , base_class_count_of<t_Ty>::value
        , has_destroyed_signal<t_Ty>::value
        , has_destroyed_signal_declared<t_Ty>::value>
    {
    };



    template<typename t_Ty>
    struct default_initializer_helper<t_Ty, default_initializer_member_function_and_instanciation_notification>
    {
        inline static void          initialize( reflection::Class* a_pClass, t_Ty* a_pInstance )
        {
            initialize_member_function_caller<t_Ty>::apply(a_pClass, a_pInstance);
            state_machine_initializer<t_Ty>::initialize(a_pInstance);
#if o__bool__use_kind_creation_signal
            a_pClass->fireKindCreated(a_pInstance);
#endif
        }
        inline static restore_state restore( reflection::Class* a_pClass, t_Ty* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass )
        {
            restore_state result = restore_member_function_caller<t_Ty>::apply(a_pClass, a_pInstance, a_uiSerializationFlag, a_uiPass);
#if o__bool__use_kind_creation_signal
            if(result == restore_complete)
            {
                state_machine_initializer<t_Ty>::initialize(a_pInstance);
                a_pClass->fireKindCreated(a_pInstance);
            }
#endif
            return result;
        }
        inline static void          terminate( reflection::Class* a_pClass, t_Ty* a_pInstance )
        {
#if o__bool__use_kind_destruction_signal
            a_pClass->fireKindDestroyed(static_cast<t_Ty*>(a_pInstance));
#endif
#if o__bool__use_destroyed_signal
            destroyed_signal_emitter<t_Ty>::apply(a_pInstance);
#endif
            state_machine_initializer<t_Ty>::terminate(a_pInstance);
            terminate_member_function_caller<t_Ty>::apply(a_pClass, a_pInstance);
        }
        inline static void          initialize( reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize )
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
            {
                initialize_member_function_caller<t_Ty>::apply(a_pClass, reinterpret_cast<t_Ty*>(pChunk));
                state_machine_initializer<t_Ty>::initialize(reinterpret_cast<t_Ty*>(pChunk));
#if o__bool__use_kind_creation_signal
                a_pClass->fireKindCreated(reinterpret_cast<t_Ty*>(pChunk));
#endif
            }
        }
        inline static void          terminate( reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize )
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
            {
#if o__bool__use_kind_destruction_signal
                a_pClass->fireKindDestroyed(reinterpret_cast<t_Ty*>(pChunk));
#endif
#if o__bool__use_destroyed_signal
                destroyed_signal_emitter<t_Ty>::apply(reinterpret_cast<t_Ty*>(pChunk));
#endif
                state_machine_initializer<t_Ty>::terminate(reinterpret_cast<t_Ty*>(pChunk));
                terminate_member_function_caller<t_Ty>::apply(a_pClass, reinterpret_cast<t_Ty*>(pChunk));
            }
        }
        inline static restore_state restore( reflection::Class* a_pClass, t_Ty* a_pChunk, uint a_uiSerializationFlag, restore_pass a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize  )
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            restore_state result = restore_complete;
            for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
            {
                restore_state this_restore_state;
                result = combine_restore_states(result, this_restore_state = restore_member_function_caller<t_Ty>::apply(a_pClass, reinterpret_cast<t_Ty*>(pChunk), a_uiSerializationFlag, a_uiPass));
#if o__bool__use_kind_creation_signal
                if(this_restore_state == restore_complete)
                {
                    state_machine_initializer<t_Ty>::initialize(reinterpret_cast<t_Ty*>(pChunk));
                    a_pClass->fireKindCreated(reinterpret_cast<t_Ty*>(pChunk));
                }
#endif
            }
            return result;
        }
    };
}


template<typename t_Ty>
struct default_initializer : public detail::default_initializer_helper<t_Ty,
    (is_signal_t<t_Ty>::value
    OR boost::is_void<t_Ty>::value
    OR (boost::is_pod<t_Ty>::value AND NOT(boost::is_class<t_Ty>::value))
    OR is_structure<t_Ty>::value
    OR NOT(has_reflection_cascade<t_Ty>::value))
    ? detail::default_initializer_none
    : boost::is_class<t_Ty>::value
    ? detail::default_initializer_member_function_and_instanciation_notification
    : detail::default_initializer_none
>
{
    o_rebind(default_initializer)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct initializer
///
/// \brief  Initializer. (see instance creation process)
/// 		Initialization is applied just after installation if deserialization doesn't occur
/// 		termination is the first step applied in the instance deletion process.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct initializer : public default_initializer<t_Ty>
{
};

o_forceinline restore_state   combine_restore_states(restore_state s0, restore_state s1)
{
    return s0 > s1 ? s0 : s1;
}

o_namespace_end(phantom)

#endif // o_def_initializer_h__
