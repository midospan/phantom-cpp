#ifndef o_math_multipolygon_h__
#define o_math_multipolygon_h__

#include "polygon2.h"
#include "polygon3.h"

o_declareNT(struct, (phantom, math), (typename), (t_Polygon), multipolygon);

o_namespace_begin(phantom, math)

template<class t_Ty>
struct make_float_polygon;

template<class t_Ty>
struct make_float_polygon<polygon2<t_Ty> >
{
    typedef polygon2<typename make_float<t_Ty>::type> type;
};

template<class t_Ty>
struct make_float_polygon<polygon3<t_Ty> >
{
    typedef polygon3<typename make_float<t_Ty>::type> type;
};

template<typename t_Polygon>
struct multipolygon_contour_precondition
{
    static bool test(const t_Polygon&) { return true; }
};

template<class t_Ty>
struct multipolygon_contour_precondition<polygon2<t_Ty> >
{
    static bool test(const polygon2<t_Ty>& p)
    { 
        return p.isCounterClockWise(p); 
    }
};

template<typename t_Polygon>
struct multipolygon
{
    typedef typename t_Polygon::iterator iterator;
    typedef typename t_Polygon::const_iterator const_iterator;
    typedef typename make_float_polygon<t_Polygon>::type friendType;
    typedef typename multipolygon<t_Polygon> self_type;
    typedef typename t_Polygon::value_type value_type;
    typedef typename t_Polygon::float_type float_type;

public:
    multipolygon() {}

    multipolygon(const t_Polygon& contour)
    {
        addContour(contour);
    }

    void clear()
    {
        contours.clear();
        holes.clear();
    }

    inline multipolygon(const multipolygon<friendType> mp)
    {
        auto it = mp.beginContours();
        for (; it != mp.endContours(); ++it)
        {
            this->contours.push_back(t_Polygon(*it));
        }
        it = mp.beginHoles();
        for (; it != mp.endHoles(); ++it)
        {
            this->holes.push_back(t_Polygon(*it));
        }
    }

    void addContour( const t_Polygon& polygon )
    {
        o_assert(multipolygon_contour_precondition<t_Polygon>::test(polygon));
        contours.push_back(polygon);
    }

    void addHole( const t_Polygon& polygon )
    {
        o_assert(!multipolygon_contour_precondition<t_Polygon>::test(polygon));
        holes.push_back(polygon);
    }

    bool empty() const { return contours.empty(); }

    const_iterator beginContours() const { return contours.begin(); }
    const_iterator endContours() const { return contours.end(); }
    const_iterator beginHoles() const { return holes.begin(); }
    const_iterator endHoles() const { return holes.end(); }

    iterator beginContours() { return contours.begin(); }
    iterator endContours() { return contours.end(); }
    iterator beginHoles() { return holes.begin(); }
    iterator endHoles() { return holes.end(); }

    void reverse()
    {
        for(auto it = contours.begin(); it != contours.end(); ++it)
        {
            std::reverse(it->begin(), it->end());
        }
        for(auto it =holes.begin(); it != holes.end(); ++it)
        {
            std::reverse(it->begin(), it->end());
        }
    }

    bool intersects(const t_Polygon& polygon, std::vector<value_type>* intersectionPoints = nullptr, float_type epsilon = std::numeric_limits<float_type>::epsilon()) const
    {
        for(auto it = contours.begin(); it != contours.end(); ++it)
        {
            if(polygon.intersects(*it, intersectionPoints, epsilon)) return true;
        }
        for(auto it =holes.begin(); it != holes.end(); ++it)
        {
            if(polygon.intersects(*it, intersectionPoints, epsilon)) return true;
        }
        return false;
    }

    bool intersects(const self_type& multiPolygon, std::vector<value_type>* intersectionPoints = nullptr, float_type epsilon = std::numeric_limits<float_type>::epsilon()) const
    {
        for(auto it = multiPolygon.beginContours(); it != multiPolygon.endContours(); ++it)
        {
            if(intersects(*it, intersectionPoints, epsilon)) return true;
        }
        for(auto it =multiPolygon.beginHoles(); it != multiPolygon.endHoles(); ++it)
        {
            if(intersects(*it, intersectionPoints, epsilon)) return true;
        }
        return false;
    }

    void trace()
    {
        for(auto it = beginContours(); it != endContours(); ++it)
        {
            (*it).trace();
        }
        for(auto it = beginHoles(); it != endHoles(); ++it)
        {
            (*it).trace();
        }
    }

protected:
    vector<t_Polygon> contours;
    vector<t_Polygon> holes;
};

typedef multipolygon<polygon2f> multipolygon2f;
typedef multipolygon<polygon2d> multipolygon2d;

typedef multipolygon<polygon3f> multipolygon3f;
typedef multipolygon<polygon3d> multipolygon3d;


o_namespace_end(phantom, math)

#endif // multipolygon2_h__