#ifndef def_counter_h__
#define def_counter_h__

/// THANKS TO Potatoeswatter on stackoverflow for this code ;) 
/// http://stackoverflow.com/questions/6166337/does-c-support-compile-time-counters

o_namespace_begin(phantom, counter)

#if defined(HAS_CONSTEXPR)

#define o_counter_read_crumb( TAG, RANK, ACC ) phantom::counter::counter_crumb( TAG(), phantom::counter::constant_index< RANK >(), phantom::counter::constant_index< ACC >() )
#define o_counter_read( TAG ) o_counter_read_crumb( TAG, 1, o_counter_read_crumb( TAG, 2, o_counter_read_crumb( TAG, 4, o_counter_read_crumb( TAG, 8, \
    o_counter_read_crumb( TAG, 16, o_counter_read_crumb( TAG, 32, o_counter_read_crumb( TAG, 64, o_counter_read_crumb( TAG, 128, o_counter_read_crumb( TAG, 256, 0 ) ) ) ) ) ) ) ) )

#define o_counter_inc( TAG ) \
    phantom::counter::constant_index< o_counter_read( TAG ) + 1 > \
    constexpr counter_crumb( TAG, phantom::counter::constant_index< ( o_counter_read( TAG ) + 1 ) & ~ o_counter_read( TAG ) >, \
    phantom::counter::constant_index< ( o_counter_read( TAG ) + 1 ) & o_counter_read( TAG ) > ) { return {}; }

#include <utility>

template< std::size_t n >
struct constant_index : std::integral_constant< std::size_t, n > {};

template< typename id, std::size_t rank, std::size_t acc >
constexpr constant_index< acc > counter_crumb( id, constant_index< rank >, constant_index< acc > ) { return {}; } // found by ADL via constant_index

#else

template< size_t n > // This type returns a number through function lookup.
struct cn // The function returns cn<n>.
    { char data[ n + 1 ]; }; // The caller uses (sizeof fn() - 1).

template< typename id, size_t n, size_t acc >
cn< acc > seen( id, cn< n >, cn< acc > ); // Default fallback case.


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

#   define o_read_compilation_counter                   o_counter_read(phantom::counter::compilation_unit_counter)
#   define o_read_compilation_counter_by_type(...)      o_counter_read(phantom::counter::compilation_unit_counter)
#   define o_read_compilation_counter_by_value(...)     o_counter_read(phantom::counter::compilation_unit_counter)

#else 

#   define o_read_compilation_counter                   o_counter_read(phantom::counter::compilation_unit_counter)
#   define o_read_compilation_counter_by_type(...)      o_counter_read_deferred_by_type(phantom::counter::compilation_unit_counter,##__VA_ARGS__)
#   define o_read_compilation_counter_by_value(...)     o_counter_read_deferred_by_value(phantom::counter::compilation_unit_counter,##__VA_ARGS__)

#   define o_counter_read_deferrer_by_type_op 
#   define o_counter_read_deferrer_by_value_op +(t_Zero*t_Value)

#endif

#define o_inc_compilation_counter o_counter_inc(phantom::counter::compilation_unit_counter)
#define o_print_compilation_counter static phantom::counter::printer<o_read_compilation_counter> o_PP_CAT(counter_print, __COUNTER__);


/* Evaluate the counter by finding the last defined overload.
   Each function, when defined, alters the lookup sequence for lower-order
   functions. */
#define o_counter_read( id ) \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 1   + 0 >(),  phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 2   + 0 >(),  phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 4   + 0 >(),  phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 8   + 0 >(),  phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 16  + 0 >(), phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 32  + 0 >(), phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 64  + 0 >(), phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 128 + 0 >(), phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 256 + 0 >(), phantom::counter::cn< 0 \
    >() ) - 1 ) \
    >() ) - 1 ) \
    >() ) - 1 ) \
    >() ) - 1 ) \
    >() ) - 1 ) \
    >() ) - 1 ) \
    >() ) - 1 ) \
    >() ) - 1 ) \
    >() ) - 1 )

#define o_counter_read_deferred_by_type( id, ... ) \
( sizeof phantom::counter::seen( id(), phantom::counter::cn< 1   + boost::is_same<__VA_ARGS__, __VA_ARGS__*>::value >(),  phantom::counter::cn< \
( sizeof phantom::counter::seen( id(), phantom::counter::cn< 2   + boost::is_same<__VA_ARGS__, __VA_ARGS__*>::value >(),  phantom::counter::cn< \
( sizeof phantom::counter::seen( id(), phantom::counter::cn< 4   + boost::is_same<__VA_ARGS__, __VA_ARGS__*>::value >(),  phantom::counter::cn< \
( sizeof phantom::counter::seen( id(), phantom::counter::cn< 8   + boost::is_same<__VA_ARGS__, __VA_ARGS__*>::value >(),  phantom::counter::cn< \
( sizeof phantom::counter::seen( id(), phantom::counter::cn< 16  + boost::is_same<__VA_ARGS__, __VA_ARGS__*>::value >(), phantom::counter::cn< \
( sizeof phantom::counter::seen( id(), phantom::counter::cn< 32  + boost::is_same<__VA_ARGS__, __VA_ARGS__*>::value >(), phantom::counter::cn< \
( sizeof phantom::counter::seen( id(), phantom::counter::cn< 64  + boost::is_same<__VA_ARGS__, __VA_ARGS__*>::value >(), phantom::counter::cn< \
( sizeof phantom::counter::seen( id(), phantom::counter::cn< 128 + boost::is_same<__VA_ARGS__, __VA_ARGS__*>::value >(), phantom::counter::cn< \
( sizeof phantom::counter::seen( id(), phantom::counter::cn< 256 + boost::is_same<__VA_ARGS__, __VA_ARGS__*>::value >(), phantom::counter::cn< 0 \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1) \
>() ) - 1)

#define o_counter_read_deferred_by_value( id, ... ) \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 1   + 0*__VA_ARGS__ >(),  phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 2   + 0*__VA_ARGS__ >(),  phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 4   + 0*__VA_ARGS__ >(),  phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 8   + 0*__VA_ARGS__ >(),  phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 16  + 0*__VA_ARGS__ >(), phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 32  + 0*__VA_ARGS__ >(), phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 64  + 0*__VA_ARGS__ >(), phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 128 + 0*__VA_ARGS__ >(), phantom::counter::cn< \
    ( sizeof phantom::counter::seen( id(), phantom::counter::cn< 256 + 0*__VA_ARGS__ >(), phantom::counter::cn< 0 \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1) \
                        >() ) - 1)


/* Define a single new function with place-value equal to the bit flipped to 1
   by the increment operation.
   This is the lowest-magnitude function yet undefined in the current context
   of defined higher-magnitude functions. */
#define o_counter_inc( id ) \
o_namespace_begin(phantom, counter) \
    cn< o_counter_read( id ) + 1 > \
    seen( id, cn< ( o_counter_read( id ) + 1 ) & ~ o_counter_read( id ) >, \
          cn< ( o_counter_read( id ) + 1 ) & o_counter_read( id ) > ); \
o_namespace_end(phantom, counter)

struct compilation_unit_counter {};

template<int t_counter>
struct printer
{
    o_static_assert(t_counter != t_counter);
};

#endif

o_namespace_end(phantom, counter)

#endif // def_counter_h__
