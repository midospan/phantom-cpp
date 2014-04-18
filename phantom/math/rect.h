#ifndef o_math_rect_h__
#define o_math_rect_h__


/* ****************** Includes ******************* */

/* **************** Declarations ***************** */
o_declareNT(class, (phantom, math), (typename), (t_Ty), rect);
/* *********************************************** */

o_namespace_begin(phantom, math)

template<typename t_Ty>
class rect
{
public:
    typedef rect<t_Ty> self_type;

public:
    rect(void) : m_x(0), m_y(0), m_w(0), m_h(0) {}
    rect(t_Ty ax, t_Ty ay, t_Ty aw, t_Ty ah) : m_x(ax), m_y(ay), m_w(aw), m_h(ah) {}
	~rect(void) {}

    o_forceinline t_Ty getX() const { return m_x; }
    o_forceinline t_Ty getY() const { return m_y; }
    o_forceinline t_Ty getWidth() const { return m_w; }
    o_forceinline t_Ty getHeight() const { return m_h; }

    o_forceinline void setX(t_Ty ax) { m_x = ax; }
    o_forceinline void setY(t_Ty ay) { m_y = ay; }
    o_forceinline void setWidth(t_Ty aw) { m_w = aw; }
    o_forceinline void setHeight(t_Ty ah)  { m_h = ah; }

    bool operator==(const self_type& other) const 
    {
        return m_x == other.m_x && m_y == other.m_y && m_w == other.m_w && m_h == other.m_h;
    }

    bool operator!=(const self_type& other) const 
    {
        return !operator==(other);
    }

protected:
    t_Ty m_x;
    t_Ty m_y;
    t_Ty m_w;
    t_Ty m_h;
};

typedef rect<float32>   rectf;
typedef rect<float64>   rectd;
typedef rect<int>       recti;
typedef rect<uint>      rectui;

o_namespace_end(phantom, math)

#endif // o_math_rect_h__
