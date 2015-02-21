/* TODO LICENCE HERE */

#ifndef o_util_flags_h__
#define o_util_flags_h__

// Inpired from Qt::Flags


namespace phantom 
{

class flag
{
    int i;
public:
    inline flag(int i);
    inline operator int() const { return i; }
};

inline flag::flag(int ai) : i(ai) {}

class incompatible_flag
{
    int i;
public:
    inline explicit incompatible_flag(int i);
    inline operator int() const { return i; }
};

inline incompatible_flag::incompatible_flag(int ai) : i(ai) {}


template<typename Enum>
class flags;

template<typename Enum>
struct flags_bit
{
    flags_bit() : m_Flags(0), m_Where((Enum)0) {}
    flags_bit(flags<Enum>* a_Flags, Enum a_Where)
        : m_Flags(a_Flags), m_Where(a_Where) {}
    
    void setValue(bool a_bValue) { if(a_bValue) (*m_Flags) |= m_Where; else (*m_Flags) &= ~m_Where; }
    bool getValue() const { return ((*m_Flags) & m_Where) == m_Where; }

protected:
    flags<Enum>* m_Flags;
    Enum m_Where;
};

template<typename Enum>
struct const_flags_bit
{
    const_flags_bit() : m_Flags(0), m_Where((Enum)0) {}
    const_flags_bit(const flags<Enum>* a_Flags, Enum a_Where)
        : m_Flags(a_Flags), m_Where(a_Where) {}

    bool getValue() const { return ((*m_Flags) & m_Where) == m_Where; }

protected:
    const flags<Enum>* m_Flags;
    Enum m_Where;
};

template<typename Enum>
class flags
{

    typedef void **Zero;
    int i;

public:
    typedef flags_bit<Enum> bit;
    typedef const_flags_bit<Enum> const_bit;
    typedef Enum enum_type;
    inline flags(const flags &f) : i(f.i) {}
    inline flags(Enum f) : i(f) {}
    inline flags(Zero = 0) : i(0) {}
    inline flags(flag f) : i(f) {}

    inline flags &operator=(const flags &f) { i = f.i; return *this; }
    inline flags &operator&=(int mask) { i &= mask; return *this; }
    inline flags &operator&=(unsigned int mask) { i &= mask; return *this; }
    inline flags &operator|=(flags f) { i |= f.i; return *this; }
    inline flags &operator|=(Enum f) { i |= f; return *this; }
    inline flags &operator^=(flags f) { i ^= f.i; return *this; }
    inline flags &operator^=(Enum f) { i ^= f; return *this; }

    inline operator int() const { return i; }

    inline flags operator|(flags f) const { return flags(Enum(i | f.i)); }
    inline flags operator|(Enum f) const { return flags(Enum(i | f)); }
    inline flags operator^(flags f) const { return flags(Enum(i ^ f.i)); }
    inline flags operator^(Enum f) const { return flags(Enum(i ^ f)); }
    inline flags operator&(int mask) const { return flags(Enum(i & mask)); }
    inline flags operator&(unsigned int mask) const { return flags(Enum(i & mask)); }
    inline flags operator&(Enum f) const { return flags(Enum(i & f)); }
    inline flags operator~() const { return flags(Enum(~i)); }

    inline bool operator!() const { return !i; }

    inline bool testFlag(Enum f) const { return (i & f) == f && (f != 0 || i == int(f) ); }

    bit       operator[](Enum f) { return bit(this, f); }
    const_bit operator[](Enum f) const { return const_bit(this, f);  }

};

}


#define o_declare_flags(FlagsName, Enum)\
    typedef phantom::flags<Enum> FlagsName;

#define o_declare_incompatible_flags(flags) \
    inline incompatible_flag operator|(flags::enum_type f1, int f2) \
{ return incompatible_flag(int(f1) | f2); }

#define o_declare_operators_for_flags(flags) \
    inline flags<flags::enum_type> operator|(flags::enum_type f1, flags::enum_type f2) \
{ return flags<flags::enum_type>(f1) | f2; } \
    inline flags<flags::enum_type> operator|(flags::enum_type f1, flags<flags::enum_type> f2) \
{ return f2 | f1; } o_declare_incompatible_flags(flags)

#endif // Flags_h__
