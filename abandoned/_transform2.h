#ifndef o_math_transform2_h__
#define o_math_transform2_h__

o_namespace_begin(phantom, math)

template<typename t_Ty>
struct transform2
{
    typedef transform2<t_Ty>    self_type;
    typedef vector2<t_Ty>       vector2_type;
    typedef rotation2D<t_Ty>    rotation2D_type;
    typedef matrix3x3<t_Ty>     matrix3x3_type;
    typedef matrix2x2<t_Ty>     matrix2x2_type;

    transform2()
        : position(0,0)
        , orientation(0)
        , scale(t_Ty(1),t_Ty(1))
    {

    }

    /// Set this to the identity transform.
    void setIdentity()
    {
        position.setZero();
        orientation.setIdentity();
        scale.x = t_Ty(1);
        scale.y = t_Ty(1);
    }

    /// Set this based on the position and angle.
    void set(const vector2_type& a_position, t_Ty a_angle, const vector2_type& a_scale)
    {
        position = a_position;
        orientation.setAngle(a_angle);
        scale = a_scale;
    }

    void set(const vector2_type& a_position, t_Ty a_angle)
    {
        position = a_position;
        orientation.setAngle(a_angle);
    }

    matrix3x3_type getMatrix3x3() const 
    {
        return matrix3x3_type(orientation.c * scale.x
            , orientation.s
            , 0
            , -orientation.s
            , orientation.c * scale.y
            , 0
            , position.x
            , position.y
            , 1);
    }

    matrix3x3_type getMatrix3x3WithoutScale() const 
    {
        return matrix3x3_type(orientation.c
            , orientation.s
            , 0
            , -orientation.s
            , orientation.c
            , 0
            , position.x
            , position.y
            , 1);
    }

    void getMatrix3x3WithoutScale(matrix3x3_type& in_out) const 
    {
        t_Ty* m = in_out.a;

        // col 0
        *m++ = orientation.c ;
        *m++ = orientation.s;
        *m++ = 0;

        // col 1
        *m++ = -orientation.s;
        *m++ = orientation.c ;
        *m++ = 0;

        // col 2
        *m++ = position.x;
        *m++ = position.y;
        *m++ = 1;
    }

    void getMatrix3x3(matrix3x3_type& in_out) const 
    {
        t_Ty* m = in_out.a;

        // col 0
        *m++ = orientation.c * scale.x;
        *m++ = orientation.s;
        *m++ = 0;

        // col 1
        *m++ = -orientation.s;
        *m++ = orientation.c * scale.y;
        *m++ = 0;

        // col 2
        *m++ = position.x;
        *m++ = position.y;
        *m++ = 1;
    }


    matrix2x2_type getRotationMatrix2x2() const 
    {
        return matrix2x2_type(orientation.c
            , orientation.s
            , -orientation.s
            , orientation.c );

    }
    void getRotationMatrix2x2(matrix2x2_type& in_out) const 
    {
        t_Ty* m = in_out.a;

        // col 0
        *m++ = orientation.c ;
        *m++ = orientation.s;

        // col 1
        *m++ = -orientation.s;
        *m++ = orientation.c ;

    }

    bool    operator==(const self_type& other) const 
    {
        return (other.position == position)
            AND (other.scale == scale) 
            AND (other.orientation == orientation);
    }

    bool    operator!=(const self_type& other) const 
    {
        return (other.position != position)
            OR (other.scale != scale) 
            OR (other.orientation != orientation);
    }

    vector2_type        position;
    rotation2D_type     orientation;
    vector2_type        scale;
};

o_namespace_end(phantom, math)

#endif // phantom_math_transform2_h__
