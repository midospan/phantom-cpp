
template<class t_Ty>
inline line2<t_Ty>::line2() : point(0, 0), direction(1, 0) {};

template<class t_Ty>
inline t_Ty line2<t_Ty>::getParameter(vector2_type v, t_Ty epsilon) const
{
    vector2_type n2 = point - v;
    float det = fabs(direction.x*n2.y - direction.y*n2.x);
    o_assert(det < epsilon);
    return (v - point).dot(direction)/(direction.lengthSquared());
}

// Debugging output.
template<class t_Ty>
std::ostream& operator<< (std::ostream& outFile, const line2<t_Ty>& line )
{
    outFile << "point: " << line.point << " | direction: " << line.direction;
    return outFile;
}
