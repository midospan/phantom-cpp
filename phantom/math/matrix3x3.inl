
o_namespace_begin(phantom, math)
    
//-----------------------------------------------------------------------
template<typename t_Ty>
typename matrix3x3<t_Ty>::vector3_type matrix3x3<t_Ty>::getColumn (size_t iCol) const
{
    assert( 0 <= iCol && iCol < 3 );
    return vector3_type(m[0][iCol],m[1][iCol],
        m[2][iCol]);
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::setColumn(size_t iCol, const typename matrix3x3<t_Ty>::vector3_type& vec)
{
    assert( 0 <= iCol && iCol < 3 );
    m[0][iCol] = vec.x;
    m[1][iCol] = vec.y;
    m[2][iCol] = vec.z;

}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::fromAxes(const typename matrix3x3<t_Ty>::vector3_type& xAxis, const typename matrix3x3<t_Ty>::vector3_type& yAxis, const typename matrix3x3<t_Ty>::vector3_type& zAxis)
{
    SetColumn(0,xAxis);
    SetColumn(1,yAxis);
    SetColumn(2,zAxis);

}

//-----------------------------------------------------------------------
template<typename t_Ty>
bool matrix3x3<t_Ty>::operator== (const matrix3x3<t_Ty>& rkMatrix) const
{
    for (size_t iRow = 0; iRow < 3; iRow++)
    {
        for (size_t iCol = 0; iCol < 3; iCol++)
        {
            if ( m[iRow][iCol] != rkMatrix.m[iRow][iCol] )
                return false;
        }
    }

    return true;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
matrix3x3<t_Ty> matrix3x3<t_Ty>::operator+ (const matrix3x3<t_Ty>& rkMatrix) const
{
    matrix3x3<t_Ty> kSum;
    for (size_t iRow = 0; iRow < 3; iRow++)
    {
        for (size_t iCol = 0; iCol < 3; iCol++)
        {
            kSum.m[iRow][iCol] = m[iRow][iCol] +
                rkMatrix.m[iRow][iCol];
        }
    }
    return kSum;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
matrix3x3<t_Ty> matrix3x3<t_Ty>::operator- (const matrix3x3<t_Ty>& rkMatrix) const
{
    matrix3x3<t_Ty> kDiff;
    for (size_t iRow = 0; iRow < 3; iRow++)
    {
        for (size_t iCol = 0; iCol < 3; iCol++)
        {
            kDiff.m[iRow][iCol] = m[iRow][iCol] -
                rkMatrix.m[iRow][iCol];
        }
    }
    return kDiff;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
matrix3x3<t_Ty> matrix3x3<t_Ty>::operator* (const matrix3x3<t_Ty>& rkMatrix) const
{
    matrix3x3<t_Ty> kProd;
    for (size_t iRow = 0; iRow < 3; iRow++)
    {
        for (size_t iCol = 0; iCol < 3; iCol++)
        {
            kProd.m[iRow][iCol] =
                m[iRow][0]*rkMatrix.m[0][iCol] +
                m[iRow][1]*rkMatrix.m[1][iCol] +
                m[iRow][2]*rkMatrix.m[2][iCol];
        }
    }
    return kProd;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
typename matrix3x3<t_Ty>::vector2_type matrix3x3<t_Ty>::operator* (const typename matrix3x3<t_Ty>::vector2_type& rkPoint) const
{
    vector2_type kProd;
    vector3_type rkPoint3 ( rkPoint.x, rkPoint.y, t_Ty(1) );
    for (size_t iRow = 0; iRow < 2; ++iRow)
    {
        kProd[iRow] =
            m[iRow][0]*rkPoint3[0] +
            m[iRow][1]*rkPoint3[1] +
            m[iRow][2]*rkPoint3[2];
    }
    return kProd;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
typename matrix3x3<t_Ty>::vector3_type matrix3x3<t_Ty>::operator* (const typename matrix3x3<t_Ty>::vector3_type& rkPoint) const
{
    vector3_type kProd;
    for (size_t iRow = 0; iRow < 3; ++iRow)
    {
        kProd[iRow] =
            m[iRow][0]*rkPoint[0] +
            m[iRow][1]*rkPoint[1] +
            m[iRow][2]*rkPoint[2];
    }
    return kProd;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
typename matrix3x3<t_Ty>::vector3_type operator* (const typename matrix3x3<t_Ty>::vector3_type& rkPoint, const matrix3x3<t_Ty>& rkMatrix)
{
    vector3_type kProd;
    for (size_t iRow = 0; iRow < 3; iRow++)
    {
        kProd[iRow] =
            rkPoint[0]*rkMatrix.m[0][iRow] +
            rkPoint[1]*rkMatrix.m[1][iRow] +
            rkPoint[2]*rkMatrix.m[2][iRow];
    }
    return kProd;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
matrix3x3<t_Ty> matrix3x3<t_Ty>::operator- () const
{
    matrix3x3<t_Ty> kNeg;
    for (size_t iRow = 0; iRow < 3; iRow++)
    {
        for (size_t iCol = 0; iCol < 3; iCol++)
            kNeg[iRow][iCol] = -m[iRow][iCol];
    }
    return kNeg;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
matrix3x3<t_Ty> matrix3x3<t_Ty>::operator* (t_Ty fScalar) const
{
    matrix3x3<t_Ty> kProd;
    for (size_t iRow = 0; iRow < 3; iRow++)
    {
        for (size_t iCol = 0; iCol < 3; iCol++)
            kProd[iRow][iCol] = fScalar*m[iRow][iCol];
    }
    return kProd;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
matrix3x3<t_Ty> operator* (t_Ty fScalar, const matrix3x3<t_Ty>& rkMatrix)
{
    matrix3x3<t_Ty> kProd;
    for (size_t iRow = 0; iRow < 3; iRow++)
    {
        for (size_t iCol = 0; iCol < 3; iCol++)
            kProd[iRow][iCol] = fScalar*rkMatrix.m[iRow][iCol];
    }
    return kProd;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
matrix3x3<t_Ty> matrix3x3<t_Ty>::transpose () const
{
    matrix3x3<t_Ty> kTranspose;
    for (size_t iRow = 0; iRow < 3; iRow++)
    {
        for (size_t iCol = 0; iCol < 3; iCol++)
            kTranspose[iRow][iCol] = m[iCol][iRow];
    }
    return kTranspose;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
bool matrix3x3<t_Ty>::inverse (matrix3x3<t_Ty>& rkInverse, t_Ty fTolerance) const
{
    // Invert a 3x3 using cofactors.  This is about 8 times faster than
    // the Numerical Recipes code which uses Gaussian elimination.

    rkInverse[0][0] = m[1][1]*m[2][2] -
        m[1][2]*m[2][1];
    rkInverse[0][1] = m[0][2]*m[2][1] -
        m[0][1]*m[2][2];
    rkInverse[0][2] = m[0][1]*m[1][2] -
        m[0][2]*m[1][1];
    rkInverse[1][0] = m[1][2]*m[2][0] -
        m[1][0]*m[2][2];
    rkInverse[1][1] = m[0][0]*m[2][2] -
        m[0][2]*m[2][0];
    rkInverse[1][2] = m[0][2]*m[1][0] -
        m[0][0]*m[1][2];
    rkInverse[2][0] = m[1][0]*m[2][1] -
        m[1][1]*m[2][0];
    rkInverse[2][1] = m[0][1]*m[2][0] -
        m[0][0]*m[2][1];
    rkInverse[2][2] = m[0][0]*m[1][1] -
        m[0][1]*m[1][0];

    t_Ty fDet =
        m[0][0]*rkInverse[0][0] +
        m[0][1]*rkInverse[1][0]+
        m[0][2]*rkInverse[2][0];

    if ( abs(fDet) <= fTolerance )
        return false;

    t_Ty fInvDet = 1.0f/fDet;
    for (size_t iRow = 0; iRow < 3; iRow++)
    {
        for (size_t iCol = 0; iCol < 3; iCol++)
            rkInverse[iRow][iCol] *= fInvDet;
    }

    return true;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
matrix3x3<t_Ty> matrix3x3<t_Ty>::inverse (t_Ty fTolerance) const
{
    matrix3x3<t_Ty> kInverse = matrix3x3<t_Ty>::Zero();
    inverse(kInverse,fTolerance);
    return kInverse;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
t_Ty matrix3x3<t_Ty>::determinant () const
{
    t_Ty fCofactor00 = m[1][1]*m[2][2] -
        m[1][2]*m[2][1];
    t_Ty fCofactor10 = m[1][2]*m[2][0] -
        m[1][0]*m[2][2];
    t_Ty fCofactor20 = m[1][0]*m[2][1] -
        m[1][1]*m[2][0];

    t_Ty fDet =
        m[0][0]*fCofactor00 +
        m[0][1]*fCofactor10 +
        m[0][2]*fCofactor20;

    return fDet;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::bidiagonalize (matrix3x3<t_Ty>& kA, matrix3x3<t_Ty>& kL,
    matrix3x3<t_Ty>& kR)
{
    t_Ty afV[3], afW[3];
    t_Ty fLength, fSign, fT1, fInvT1, fT2;
    bool bIdentity;

    // map first column to (*,0,0)
    fLength = sqrt(kA[0][0]*kA[0][0] + kA[1][0]*kA[1][0] +
        kA[2][0]*kA[2][0]);
    if ( fLength > 0.0 )
    {
        fSign = (kA[0][0] > 0.0f ? 1.0f : -1.0f);
        fT1 = kA[0][0] + fSign*fLength;
        fInvT1 = 1.0f/fT1;
        afV[1] = kA[1][0]*fInvT1;
        afV[2] = kA[2][0]*fInvT1;

        fT2 = -2.0f/(1.0f+afV[1]*afV[1]+afV[2]*afV[2]);
        afW[0] = fT2*(kA[0][0]+kA[1][0]*afV[1]+kA[2][0]*afV[2]);
        afW[1] = fT2*(kA[0][1]+kA[1][1]*afV[1]+kA[2][1]*afV[2]);
        afW[2] = fT2*(kA[0][2]+kA[1][2]*afV[1]+kA[2][2]*afV[2]);
        kA[0][0] += afW[0];
        kA[0][1] += afW[1];
        kA[0][2] += afW[2];
        kA[1][1] += afV[1]*afW[1];
        kA[1][2] += afV[1]*afW[2];
        kA[2][1] += afV[2]*afW[1];
        kA[2][2] += afV[2]*afW[2];

        kL[0][0] = 1.0f+fT2;
        kL[0][1] = kL[1][0] = fT2*afV[1];
        kL[0][2] = kL[2][0] = fT2*afV[2];
        kL[1][1] = 1.0f+fT2*afV[1]*afV[1];
        kL[1][2] = kL[2][1] = fT2*afV[1]*afV[2];
        kL[2][2] = 1.0f+fT2*afV[2]*afV[2];
        bIdentity = false;
    }
    else
    {
        kL = matrix3x3<t_Ty>::IDENTITY;
        bIdentity = true;
    }

    // map first row to (*,*,0)
    fLength = sqrt(kA[0][1]*kA[0][1]+kA[0][2]*kA[0][2]);
    if ( fLength > 0.0 )
    {
        fSign = (kA[0][1] > 0.0f ? 1.0f : -1.0f);
        fT1 = kA[0][1] + fSign*fLength;
        afV[2] = kA[0][2]/fT1;

        fT2 = -2.0f/(1.0f+afV[2]*afV[2]);
        afW[0] = fT2*(kA[0][1]+kA[0][2]*afV[2]);
        afW[1] = fT2*(kA[1][1]+kA[1][2]*afV[2]);
        afW[2] = fT2*(kA[2][1]+kA[2][2]*afV[2]);
        kA[0][1] += afW[0];
        kA[1][1] += afW[1];
        kA[1][2] += afW[1]*afV[2];
        kA[2][1] += afW[2];
        kA[2][2] += afW[2]*afV[2];

        kR[0][0] = 1.0;
        kR[0][1] = kR[1][0] = 0.0;
        kR[0][2] = kR[2][0] = 0.0;
        kR[1][1] = 1.0f+fT2;
        kR[1][2] = kR[2][1] = fT2*afV[2];
        kR[2][2] = 1.0f+fT2*afV[2]*afV[2];
    }
    else
    {
        kR = matrix3x3<t_Ty>::IDENTITY;
    }

    // map second column to (*,*,0)
    fLength = sqrt(kA[1][1]*kA[1][1]+kA[2][1]*kA[2][1]);
    if ( fLength > 0.0 )
    {
        fSign = (kA[1][1] > 0.0f ? 1.0f : -1.0f);
        fT1 = kA[1][1] + fSign*fLength;
        afV[2] = kA[2][1]/fT1;

        fT2 = -2.0f/(1.0f+afV[2]*afV[2]);
        afW[1] = fT2*(kA[1][1]+kA[2][1]*afV[2]);
        afW[2] = fT2*(kA[1][2]+kA[2][2]*afV[2]);
        kA[1][1] += afW[1];
        kA[1][2] += afW[2];
        kA[2][2] += afV[2]*afW[2];

        t_Ty fA = 1.0f+fT2;
        t_Ty fB = fT2*afV[2];
        t_Ty fC = 1.0f+fB*afV[2];

        if ( bIdentity )
        {
            kL[0][0] = 1.0;
            kL[0][1] = kL[1][0] = 0.0;
            kL[0][2] = kL[2][0] = 0.0;
            kL[1][1] = fA;
            kL[1][2] = kL[2][1] = fB;
            kL[2][2] = fC;
        }
        else
        {
            for (int iRow = 0; iRow < 3; iRow++)
            {
                t_Ty fTmp0 = kL[iRow][1];
                t_Ty fTmp1 = kL[iRow][2];
                kL[iRow][1] = fA*fTmp0+fB*fTmp1;
                kL[iRow][2] = fB*fTmp0+fC*fTmp1;
            }
        }
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::golubKahanStep (matrix3x3<t_Ty>& kA, matrix3x3<t_Ty>& kL,
    matrix3x3<t_Ty>& kR)
{
    t_Ty fT11 = kA[0][1]*kA[0][1]+kA[1][1]*kA[1][1];
    t_Ty fT22 = kA[1][2]*kA[1][2]+kA[2][2]*kA[2][2];
    t_Ty fT12 = kA[1][1]*kA[1][2];
    t_Ty fTrace = fT11+fT22;
    t_Ty fDiff = fT11-fT22;
    t_Ty fDiscr = sqrt(fDiff*fDiff+4.0f*fT12*fT12);
    t_Ty fRoot1 = 0.5f*(fTrace+fDiscr);
    t_Ty fRoot2 = 0.5f*(fTrace-fDiscr);

    // adjust right
    t_Ty fY = kA[0][0] - (abs(fRoot1-fT22) <=
        abs(fRoot2-fT22) ? fRoot1 : fRoot2);
    t_Ty fZ = kA[0][1];
    t_Ty fInvLength = invSqrt(fY*fY+fZ*fZ);
    t_Ty fSin = fZ*fInvLength;
    t_Ty fCos = -fY*fInvLength;

    t_Ty fTmp0 = kA[0][0];
    t_Ty fTmp1 = kA[0][1];
    kA[0][0] = fCos*fTmp0-fSin*fTmp1;
    kA[0][1] = fSin*fTmp0+fCos*fTmp1;
    kA[1][0] = -fSin*kA[1][1];
    kA[1][1] *= fCos;

    size_t iRow;
    for (iRow = 0; iRow < 3; iRow++)
    {
        fTmp0 = kR[0][iRow];
        fTmp1 = kR[1][iRow];
        kR[0][iRow] = fCos*fTmp0-fSin*fTmp1;
        kR[1][iRow] = fSin*fTmp0+fCos*fTmp1;
    }

    // adjust left
    fY = kA[0][0];
    fZ = kA[1][0];
    fInvLength = invSqrt(fY*fY+fZ*fZ);
    fSin = fZ*fInvLength;
    fCos = -fY*fInvLength;

    kA[0][0] = fCos*kA[0][0]-fSin*kA[1][0];
    fTmp0 = kA[0][1];
    fTmp1 = kA[1][1];
    kA[0][1] = fCos*fTmp0-fSin*fTmp1;
    kA[1][1] = fSin*fTmp0+fCos*fTmp1;
    kA[0][2] = -fSin*kA[1][2];
    kA[1][2] *= fCos;

    size_t iCol;
    for (iCol = 0; iCol < 3; iCol++)
    {
        fTmp0 = kL[iCol][0];
        fTmp1 = kL[iCol][1];
        kL[iCol][0] = fCos*fTmp0-fSin*fTmp1;
        kL[iCol][1] = fSin*fTmp0+fCos*fTmp1;
    }

    // adjust right
    fY = kA[0][1];
    fZ = kA[0][2];
    fInvLength = invSqrt(fY*fY+fZ*fZ);
    fSin = fZ*fInvLength;
    fCos = -fY*fInvLength;

    kA[0][1] = fCos*kA[0][1]-fSin*kA[0][2];
    fTmp0 = kA[1][1];
    fTmp1 = kA[1][2];
    kA[1][1] = fCos*fTmp0-fSin*fTmp1;
    kA[1][2] = fSin*fTmp0+fCos*fTmp1;
    kA[2][1] = -fSin*kA[2][2];
    kA[2][2] *= fCos;

    for (iRow = 0; iRow < 3; iRow++)
    {
        fTmp0 = kR[1][iRow];
        fTmp1 = kR[2][iRow];
        kR[1][iRow] = fCos*fTmp0-fSin*fTmp1;
        kR[2][iRow] = fSin*fTmp0+fCos*fTmp1;
    }

    // adjust left
    fY = kA[1][1];
    fZ = kA[2][1];
    fInvLength = invSqrt(fY*fY+fZ*fZ);
    fSin = fZ*fInvLength;
    fCos = -fY*fInvLength;

    kA[1][1] = fCos*kA[1][1]-fSin*kA[2][1];
    fTmp0 = kA[1][2];
    fTmp1 = kA[2][2];
    kA[1][2] = fCos*fTmp0-fSin*fTmp1;
    kA[2][2] = fSin*fTmp0+fCos*fTmp1;

    for (iCol = 0; iCol < 3; iCol++)
    {
        fTmp0 = kL[iCol][1];
        fTmp1 = kL[iCol][2];
        kL[iCol][1] = fCos*fTmp0-fSin*fTmp1;
        kL[iCol][2] = fSin*fTmp0+fCos*fTmp1;
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::singularValueDecomposition (matrix3x3<t_Ty>& kL, vector3_type& kS,
    matrix3x3<t_Ty>& kR) const
{
    // temas: currently unused
    //const int iMax = 16;
    size_t iRow, iCol;

    matrix3x3<t_Ty> kA = *this;
    bidiagonalize(kA,kL,kR);

    for (unsigned int i = 0; i < msSvdMaxIterations; i++)
    {
        t_Ty fTmp, fTmp0, fTmp1;
        t_Ty fSin0, fCos0, fTan0;
        t_Ty fSin1, fCos1, fTan1;

        bool bTest1 = (abs(kA[0][1]) <=
            msSvdEpsilon*(abs(kA[0][0])+abs(kA[1][1])));
        bool bTest2 = (abs(kA[1][2]) <=
            msSvdEpsilon*(abs(kA[1][1])+abs(kA[2][2])));
        if ( bTest1 )
        {
            if ( bTest2 )
            {
                kS[0] = kA[0][0];
                kS[1] = kA[1][1];
                kS[2] = kA[2][2];
                break;
            }
            else
            {
                // 2x2 closed form factorization
                fTmp = (kA[1][1]*kA[1][1] - kA[2][2]*kA[2][2] +
                    kA[1][2]*kA[1][2])/(kA[1][2]*kA[2][2]);
                fTan0 = 0.5f*(fTmp+sqrt(fTmp*fTmp + 4.0f));
                fCos0 = invSqrt(1.0f+fTan0*fTan0);
                fSin0 = fTan0*fCos0;

                for (iCol = 0; iCol < 3; iCol++)
                {
                    fTmp0 = kL[iCol][1];
                    fTmp1 = kL[iCol][2];
                    kL[iCol][1] = fCos0*fTmp0-fSin0*fTmp1;
                    kL[iCol][2] = fSin0*fTmp0+fCos0*fTmp1;
                }

                fTan1 = (kA[1][2]-kA[2][2]*fTan0)/kA[1][1];
                fCos1 = invSqrt(1.0f+fTan1*fTan1);
                fSin1 = -fTan1*fCos1;

                for (iRow = 0; iRow < 3; iRow++)
                {
                    fTmp0 = kR[1][iRow];
                    fTmp1 = kR[2][iRow];
                    kR[1][iRow] = fCos1*fTmp0-fSin1*fTmp1;
                    kR[2][iRow] = fSin1*fTmp0+fCos1*fTmp1;
                }

                kS[0] = kA[0][0];
                kS[1] = fCos0*fCos1*kA[1][1] -
                    fSin1*(fCos0*kA[1][2]-fSin0*kA[2][2]);
                kS[2] = fSin0*fSin1*kA[1][1] +
                    fCos1*(fSin0*kA[1][2]+fCos0*kA[2][2]);
                break;
            }
        }
        else
        {
            if ( bTest2 )
            {
                // 2x2 closed form factorization
                fTmp = (kA[0][0]*kA[0][0] + kA[1][1]*kA[1][1] -
                    kA[0][1]*kA[0][1])/(kA[0][1]*kA[1][1]);
                fTan0 = 0.5f*(-fTmp+sqrt(fTmp*fTmp + 4.0f));
                fCos0 = invSqrt(1.0f+fTan0*fTan0);
                fSin0 = fTan0*fCos0;

                for (iCol = 0; iCol < 3; iCol++)
                {
                    fTmp0 = kL[iCol][0];
                    fTmp1 = kL[iCol][1];
                    kL[iCol][0] = fCos0*fTmp0-fSin0*fTmp1;
                    kL[iCol][1] = fSin0*fTmp0+fCos0*fTmp1;
                }

                fTan1 = (kA[0][1]-kA[1][1]*fTan0)/kA[0][0];
                fCos1 = invSqrt(1.0f+fTan1*fTan1);
                fSin1 = -fTan1*fCos1;

                for (iRow = 0; iRow < 3; iRow++)
                {
                    fTmp0 = kR[0][iRow];
                    fTmp1 = kR[1][iRow];
                    kR[0][iRow] = fCos1*fTmp0-fSin1*fTmp1;
                    kR[1][iRow] = fSin1*fTmp0+fCos1*fTmp1;
                }

                kS[0] = fCos0*fCos1*kA[0][0] -
                    fSin1*(fCos0*kA[0][1]-fSin0*kA[1][1]);
                kS[1] = fSin0*fSin1*kA[0][0] +
                    fCos1*(fSin0*kA[0][1]+fCos0*kA[1][1]);
                kS[2] = kA[2][2];
                break;
            }
            else
            {
                golubKahanStep(kA,kL,kR);
            }
        }
    }

    // positize diagonal
    for (iRow = 0; iRow < 3; iRow++)
    {
        if ( kS[iRow] < 0.0 )
        {
            kS[iRow] = -kS[iRow];
            for (iCol = 0; iCol < 3; iCol++)
                kR[iRow][iCol] = -kR[iRow][iCol];
        }
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::singularValueComposition (const matrix3x3<t_Ty>& kL,
    const typename matrix3x3<t_Ty>::vector3_type& kS, const matrix3x3<t_Ty>& kR)
{
    size_t iRow, iCol;
    matrix3x3<t_Ty> kTmp;

    // product S*R
    for (iRow = 0; iRow < 3; iRow++)
    {
        for (iCol = 0; iCol < 3; iCol++)
            kTmp[iRow][iCol] = kS[iRow]*kR[iRow][iCol];
    }

    // product L*S*R
    for (iRow = 0; iRow < 3; iRow++)
    {
        for (iCol = 0; iCol < 3; iCol++)
        {
            m[iRow][iCol] = 0.0;
            for (int iMid = 0; iMid < 3; iMid++)
                m[iRow][iCol] += kL[iRow][iMid]*kTmp[iMid][iCol];
        }
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::orthonormalize ()
{
    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

    // compute q0
    t_Ty fInvLength = invSqrt(m[0][0]*m[0][0]
    + m[1][0]*m[1][0] +
        m[2][0]*m[2][0]);

    m[0][0] *= fInvLength;
    m[1][0] *= fInvLength;
    m[2][0] *= fInvLength;

    // compute q1
    t_Ty fDot0 =
        m[0][0]*m[0][1] +
        m[1][0]*m[1][1] +
        m[2][0]*m[2][1];

    m[0][1] -= fDot0*m[0][0];
    m[1][1] -= fDot0*m[1][0];
    m[2][1] -= fDot0*m[2][0];

    fInvLength = invSqrt(m[0][1]*m[0][1] +
        m[1][1]*m[1][1] +
        m[2][1]*m[2][1]);

    m[0][1] *= fInvLength;
    m[1][1] *= fInvLength;
    m[2][1] *= fInvLength;

    // compute q2
    t_Ty fDot1 =
        m[0][1]*m[0][2] +
        m[1][1]*m[1][2] +
        m[2][1]*m[2][2];

    fDot0 =
        m[0][0]*m[0][2] +
        m[1][0]*m[1][2] +
        m[2][0]*m[2][2];

    m[0][2] -= fDot0*m[0][0] + fDot1*m[0][1];
    m[1][2] -= fDot0*m[1][0] + fDot1*m[1][1];
    m[2][2] -= fDot0*m[2][0] + fDot1*m[2][1];

    fInvLength = invSqrt(m[0][2]*m[0][2] +
        m[1][2]*m[1][2] +
        m[2][2]*m[2][2]);

    m[0][2] *= fInvLength;
    m[1][2] *= fInvLength;
    m[2][2] *= fInvLength;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::qduDecomposition (matrix3x3<t_Ty>& kQ,
    vector3_type& kD, vector3_type& kU) const
{
    // Factor M = QR = QDU where Q is orthogonal, D is diagonal,
    // and U is upper triangular with ones on its diagonal.  Algorithm uses
    // Gram-Schmidt orthogonalization (the QR algorithm).
    //
    // If M = [ m0 | m1 | m2 ] and Q = [ q0 | q1 | q2 ], then
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.  The matrix R has entries
    //
    //   r00 = q0*m0  r01 = q0*m1  r02 = q0*m2
    //   r10 = 0      r11 = q1*m1  r12 = q1*m2
    //   r20 = 0      r21 = 0      r22 = q2*m2
    //
    // so D = diag(r00,r11,r22) and U has entries u01 = r01/r00,
    // u02 = r02/r00, and u12 = r12/r11.

    // Q = rotation
    // D = scaling
    // U = shear

    // D stores the three diagonal entries r00, r11, r22
    // U stores the entries U[0] = u01, U[1] = u02, U[2] = u12

    // build orthogonal matrix Q
    t_Ty fInvLength = m[0][0]*m[0][0] + m[1][0]*m[1][0] + m[2][0]*m[2][0];
    if (!equalsEpsilon(fInvLength,0)) fInvLength = invSqrt(fInvLength);

    kQ[0][0] = m[0][0]*fInvLength;
    kQ[1][0] = m[1][0]*fInvLength;
    kQ[2][0] = m[2][0]*fInvLength;

    t_Ty fDot = kQ[0][0]*m[0][1] + kQ[1][0]*m[1][1] +
        kQ[2][0]*m[2][1];
    kQ[0][1] = m[0][1]-fDot*kQ[0][0];
    kQ[1][1] = m[1][1]-fDot*kQ[1][0];
    kQ[2][1] = m[2][1]-fDot*kQ[2][0];
    fInvLength = kQ[0][1]*kQ[0][1] + kQ[1][1]*kQ[1][1] + kQ[2][1]*kQ[2][1];
    if (!equalsEpsilon(fInvLength,0)) fInvLength = invSqrt(fInvLength);

    kQ[0][1] *= fInvLength;
    kQ[1][1] *= fInvLength;
    kQ[2][1] *= fInvLength;

    fDot = kQ[0][0]*m[0][2] + kQ[1][0]*m[1][2] +
        kQ[2][0]*m[2][2];
    kQ[0][2] = m[0][2]-fDot*kQ[0][0];
    kQ[1][2] = m[1][2]-fDot*kQ[1][0];
    kQ[2][2] = m[2][2]-fDot*kQ[2][0];
    fDot = kQ[0][1]*m[0][2] + kQ[1][1]*m[1][2] +
        kQ[2][1]*m[2][2];
    kQ[0][2] -= fDot*kQ[0][1];
    kQ[1][2] -= fDot*kQ[1][1];
    kQ[2][2] -= fDot*kQ[2][1];
    fInvLength = kQ[0][2]*kQ[0][2] + kQ[1][2]*kQ[1][2] + kQ[2][2]*kQ[2][2];
    if (!equalsEpsilon(fInvLength,0)) fInvLength = invSqrt(fInvLength);

    kQ[0][2] *= fInvLength;
    kQ[1][2] *= fInvLength;
    kQ[2][2] *= fInvLength;

    // guarantee that orthogonal matrix has determinant 1 (no reflections)
    t_Ty fDet = kQ[0][0]*kQ[1][1]*kQ[2][2] + kQ[0][1]*kQ[1][2]*kQ[2][0] +
        kQ[0][2]*kQ[1][0]*kQ[2][1] - kQ[0][2]*kQ[1][1]*kQ[2][0] -
        kQ[0][1]*kQ[1][0]*kQ[2][2] - kQ[0][0]*kQ[1][2]*kQ[2][1];

    if ( fDet < 0.0 )
    {
        for (size_t iRow = 0; iRow < 3; iRow++)
            for (size_t iCol = 0; iCol < 3; iCol++)
                kQ[iRow][iCol] = -kQ[iRow][iCol];
    }

    // build "right" matrix R
    matrix3x3<t_Ty> kR;
    kR[0][0] = kQ[0][0]*m[0][0] + kQ[1][0]*m[1][0] +
        kQ[2][0]*m[2][0];
    kR[0][1] = kQ[0][0]*m[0][1] + kQ[1][0]*m[1][1] +
        kQ[2][0]*m[2][1];
    kR[1][1] = kQ[0][1]*m[0][1] + kQ[1][1]*m[1][1] +
        kQ[2][1]*m[2][1];
    kR[0][2] = kQ[0][0]*m[0][2] + kQ[1][0]*m[1][2] +
        kQ[2][0]*m[2][2];
    kR[1][2] = kQ[0][1]*m[0][2] + kQ[1][1]*m[1][2] +
        kQ[2][1]*m[2][2];
    kR[2][2] = kQ[0][2]*m[0][2] + kQ[1][2]*m[1][2] +
        kQ[2][2]*m[2][2];

    // the scaling component
    kD[0] = kR[0][0];
    kD[1] = kR[1][1];
    kD[2] = kR[2][2];

    // the shear component
    t_Ty fInvD0 = 1.0f/kD[0];
    kU[0] = kR[0][1]*fInvD0;
    kU[1] = kR[0][2]*fInvD0;
    kU[2] = kR[1][2]/kD[1];
}
//-----------------------------------------------------------------------
template<typename t_Ty>
t_Ty matrix3x3<t_Ty>::maxCubicRoot (t_Ty afCoeff[3])
{
    // Spectral norm is for A^T*A, so characteristic polynomial
    // P(x) = c[0]+c[1]*x+c[2]*x^2+x^3 has three positive real roots.
    // This yields the assertions c[0] < 0 and c[2]*c[2] >= 3*c[1].

    // quick out for uniform scale (triple root)
    const t_Ty fOneThird = 1.0/3.0;
    const t_Ty fEpsilon = 1e-06;
    t_Ty fDiscr = afCoeff[2]*afCoeff[2] - 3.0f*afCoeff[1];
    if ( fDiscr <= fEpsilon )
        return -fOneThird*afCoeff[2];

    // Compute an upper bound on roots of P(x).  This assumes that A^T*A
    // has been scaled by its largest entry.
    t_Ty fX = 1.0;
    t_Ty fPoly = afCoeff[0]+fX*(afCoeff[1]+fX*(afCoeff[2]+fX));
    if ( fPoly < 0.0 )
    {
        // uses a matrix norm to find an upper bound on maximum root
        fX = abs(afCoeff[0]);
        t_Ty fTmp = 1.0f+abs(afCoeff[1]);
        if ( fTmp > fX )
            fX = fTmp;
        fTmp = 1.0f+abs(afCoeff[2]);
        if ( fTmp > fX )
            fX = fTmp;
    }

    // Newton's method to find root
    t_Ty fTwoC2 = 2.0f*afCoeff[2];
    for (int i = 0; i < 16; i++)
    {
        fPoly = afCoeff[0]+fX*(afCoeff[1]+fX*(afCoeff[2]+fX));
        if ( abs(fPoly) <= fEpsilon )
            return fX;

        t_Ty fDeriv = afCoeff[1]+fX*(fTwoC2+3.0f*fX);
        fX -= fPoly/fDeriv;
    }

    return fX;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
t_Ty matrix3x3<t_Ty>::spectralNorm () const
{
    matrix3x3<t_Ty> kP;
    size_t iRow, iCol;
    t_Ty fPmax = 0.0;
    for (iRow = 0; iRow < 3; iRow++)
    {
        for (iCol = 0; iCol < 3; iCol++)
        {
            kP[iRow][iCol] = 0.0;
            for (int iMid = 0; iMid < 3; iMid++)
            {
                kP[iRow][iCol] +=
                    m[iMid][iRow]*m[iMid][iCol];
            }
            if ( kP[iRow][iCol] > fPmax )
                fPmax = kP[iRow][iCol];
        }
    }

    t_Ty fInvPmax = 1.0f/fPmax;
    for (iRow = 0; iRow < 3; iRow++)
    {
        for (iCol = 0; iCol < 3; iCol++)
            kP[iRow][iCol] *= fInvPmax;
    }

    t_Ty afCoeff[3];
    afCoeff[0] = -(kP[0][0]*(kP[1][1]*kP[2][2]-kP[1][2]*kP[2][1]) +
        kP[0][1]*(kP[2][0]*kP[1][2]-kP[1][0]*kP[2][2]) +
        kP[0][2]*(kP[1][0]*kP[2][1]-kP[2][0]*kP[1][1]));
    afCoeff[1] = kP[0][0]*kP[1][1]-kP[0][1]*kP[1][0] +
        kP[0][0]*kP[2][2]-kP[0][2]*kP[2][0] +
        kP[1][1]*kP[2][2]-kP[1][2]*kP[2][1];
    afCoeff[2] = -(kP[0][0]+kP[1][1]+kP[2][2]);

    t_Ty fRoot = MaxCubicRoot(afCoeff);
    t_Ty fNorm = sqrt(fPmax*fRoot);
    return fNorm;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::toAngleAxis (vector3_type& rkAxis, t_Ty& rfRadians) const
{
    // Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
    // The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
    // I is the identity and
    //
    //       +-        -+
    //   P = |  0 -z +y |
    //       | +z  0 -x |
    //       | -y +x  0 |
    //       +-        -+
    //
    // If A > 0, R represents a counterclockwise rotation about the axis in
    // the sense of looking from the tip of the axis vector towards the
    // origin.  Some algebra will show that
    //
    //   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
    //
    // In the event that A = pi, R-R^t = 0 which prevents us from extracting
    // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
    // P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
    // z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
    // it does not matter which sign you choose on the square roots.

    t_Ty fTrace = m[0][0] + m[1][1] + m[2][2];
    t_Ty fCos = 0.5f*(fTrace-1.0f);
    rfRadians = acos(fCos);  // in [0,PI]

    if ( rfRadians > t_Ty(0.0) )
    {
        if ( rfRadians < t_Ty(o_math_Pi) )
        {
            rkAxis.x = m[2][1]-m[1][2];
            rkAxis.y = m[0][2]-m[2][0];
            rkAxis.z = m[1][0]-m[0][1];
            rkAxis.normalise();
        }
        else
        {
            // angle is PI
            float fHalfInverse;
            if ( m[0][0] >= m[1][1] )
            {
                // r00 >= r11
                if ( m[0][0] >= m[2][2] )
                {
                    // r00 is maximum diagonal term
                    rkAxis.x = 0.5f*sqrt(m[0][0] -
                        m[1][1] - m[2][2] + 1.0f);
                    fHalfInverse = 0.5f/rkAxis.x;
                    rkAxis.y = fHalfInverse*m[0][1];
                    rkAxis.z = fHalfInverse*m[0][2];
                }
                else
                {
                    // r22 is maximum diagonal term
                    rkAxis.z = 0.5f*sqrt(m[2][2] -
                        m[0][0] - m[1][1] + 1.0f);
                    fHalfInverse = 0.5f/rkAxis.z;
                    rkAxis.x = fHalfInverse*m[0][2];
                    rkAxis.y = fHalfInverse*m[1][2];
                }
            }
            else
            {
                // r11 > r00
                if ( m[1][1] >= m[2][2] )
                {
                    // r11 is maximum diagonal term
                    rkAxis.y = 0.5f*sqrt(m[1][1] -
                        m[0][0] - m[2][2] + 1.0f);
                    fHalfInverse  = 0.5f/rkAxis.y;
                    rkAxis.x = fHalfInverse*m[0][1];
                    rkAxis.z = fHalfInverse*m[1][2];
                }
                else
                {
                    // r22 is maximum diagonal term
                    rkAxis.z = 0.5f*sqrt(m[2][2] -
                        m[0][0] - m[1][1] + 1.0f);
                    fHalfInverse = 0.5f/rkAxis.z;
                    rkAxis.x = fHalfInverse*m[0][2];
                    rkAxis.y = fHalfInverse*m[1][2];
                }
            }
        }
    }
    else
    {
        // The angle is 0 and the matrix is the identity.  Any axis will
        // work, so just use the x-axis.
        rkAxis.x = 1.0;
        rkAxis.y = 0.0;
        rkAxis.z = 0.0;
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::fromAngleAxis (const typename matrix3x3<t_Ty>::vector3_type& rkAxis, const t_Ty& fRadians)
{
    t_Ty fCos = cos(fRadians);
    t_Ty fSin = sin(fRadians);
    t_Ty fOneMinusCos = 1.0f-fCos;
    t_Ty fX2 = rkAxis.x*rkAxis.x;
    t_Ty fY2 = rkAxis.y*rkAxis.y;
    t_Ty fZ2 = rkAxis.z*rkAxis.z;
    t_Ty fXYM = rkAxis.x*rkAxis.y*fOneMinusCos;
    t_Ty fXZM = rkAxis.x*rkAxis.z*fOneMinusCos;
    t_Ty fYZM = rkAxis.y*rkAxis.z*fOneMinusCos;
    t_Ty fXSin = rkAxis.x*fSin;
    t_Ty fYSin = rkAxis.y*fSin;
    t_Ty fZSin = rkAxis.z*fSin;

    m[0][0] = fX2*fOneMinusCos+fCos;
    m[0][1] = fXYM-fZSin;
    m[0][2] = fXZM+fYSin;
    m[1][0] = fXYM+fZSin;
    m[1][1] = fY2*fOneMinusCos+fCos;
    m[1][2] = fYZM-fXSin;
    m[2][0] = fXZM-fYSin;
    m[2][1] = fYZM+fXSin;
    m[2][2] = fZ2*fOneMinusCos+fCos;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
bool matrix3x3<t_Ty>::toEulerAnglesXYZ (t_Ty& rfYAngle, t_Ty& rfPAngle,
    t_Ty& rfRAngle) const
{
    // rot =  cy*cz          -cy*sz           sy
    //        cz*sx*sy+cx*sz  cx*cz-sx*sy*sz -cy*sx
    //       -cx*cz*sy+sx*sz  cz*sx+cx*sy*sz  cx*cy

    rfPAngle = t_Ty(asin(m[0][2]));
    if ( rfPAngle < t_Ty(o_math_Pi_by_2) )
    {
        if ( rfPAngle > t_Ty(-o_math_Pi_by_2) )
        {
            rfYAngle = atan2(-m[1][2],m[2][2]);
            rfRAngle = atan2(-m[0][1],m[0][0]);
            return true;
        }
        else
        {
            // WARNING.  Not a unique solution.
            t_Ty fRmY = atan2(m[1][0],m[1][1]);
            rfRAngle = t_Ty(0.0);  // any angle works
            rfYAngle = rfRAngle - fRmY;
            return false;
        }
    }
    else
    {
        // WARNING.  Not a unique solution.
        t_Ty fRpY = atan2(m[1][0],m[1][1]);
        rfRAngle = t_Ty(0.0);  // any angle works
        rfYAngle = fRpY - rfRAngle;
        return false;
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
bool matrix3x3<t_Ty>::toEulerAnglesXZY (t_Ty& rfYAngle, t_Ty& rfPAngle,
    t_Ty& rfRAngle) const
{
    // rot =  cy*cz          -sz              cz*sy
    //        sx*sy+cx*cy*sz  cx*cz          -cy*sx+cx*sy*sz
    //       -cx*sy+cy*sx*sz  cz*sx           cx*cy+sx*sy*sz

    rfPAngle = asin(-m[0][1]);
    if ( rfPAngle < t_Ty(o_math_Pi_by_2) )
    {
        if ( rfPAngle > t_Ty(-o_math_Pi_by_2) )
        {
            rfYAngle = atan2(m[2][1],m[1][1]);
            rfRAngle = atan2(m[0][2],m[0][0]);
            return true;
        }
        else
        {
            // WARNING.  Not a unique solution.
            t_Ty fRmY = atan2(-m[2][0],m[2][2]);
            rfRAngle = t_Ty(0.0);  // any angle works
            rfYAngle = rfRAngle - fRmY;
            return false;
        }
    }
    else
    {
        // WARNING.  Not a unique solution.
        t_Ty fRpY = atan2(-m[2][0],m[2][2]);
        rfRAngle = t_Ty(0.0);  // any angle works
        rfYAngle = fRpY - rfRAngle;
        return false;
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
bool matrix3x3<t_Ty>::toEulerAnglesYXZ (t_Ty& rfYAngle, t_Ty& rfPAngle,
    t_Ty& rfRAngle) const
{
    // rot =  cy*cz+sx*sy*sz  cz*sx*sy-cy*sz  cx*sy
    //        cx*sz           cx*cz          -sx
    //       -cz*sy+cy*sx*sz  cy*cz*sx+sy*sz  cx*cy

    rfPAngle = asin(-m[1][2]);
    if ( rfPAngle < t_Ty(o_math_Pi_by_2) )
    {
        if ( rfPAngle > t_Ty(-o_math_Pi_by_2) )
        {
            rfYAngle = atan2(m[0][2],m[2][2]);
            rfRAngle = atan2(m[1][0],m[1][1]);
            return true;
        }
        else
        {
            // WARNING.  Not a unique solution.
            t_Ty fRmY = atan2(-m[0][1],m[0][0]);
            rfRAngle = t_Ty(0.0);  // any angle works
            rfYAngle = rfRAngle - fRmY;
            return false;
        }
    }
    else
    {
        // WARNING.  Not a unique solution.
        t_Ty fRpY = atan2(-m[0][1],m[0][0]);
        rfRAngle = t_Ty(0.0);  // any angle works
        rfYAngle = fRpY - rfRAngle;
        return false;
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
bool matrix3x3<t_Ty>::toEulerAnglesYZX (t_Ty& rfYAngle, t_Ty& rfPAngle,
    t_Ty& rfRAngle) const
{
    // rot =  cy*cz           sx*sy-cx*cy*sz  cx*sy+cy*sx*sz
    //        sz              cx*cz          -cz*sx
    //       -cz*sy           cy*sx+cx*sy*sz  cx*cy-sx*sy*sz

    rfPAngle = asin(m[1][0]);
    if ( rfPAngle < t_Ty(o_math_Pi_by_2) )
    {
        if ( rfPAngle > t_Ty(-o_math_Pi_by_2) )
        {
            rfYAngle = atan2(-m[2][0],m[0][0]);
            rfRAngle = atan2(-m[1][2],m[1][1]);
            return true;
        }
        else
        {
            // WARNING.  Not a unique solution.
            t_Ty fRmY = atan2(m[2][1],m[2][2]);
            rfRAngle = t_Ty(0.0);  // any angle works
            rfYAngle = rfRAngle - fRmY;
            return false;
        }
    }
    else
    {
        // WARNING.  Not a unique solution.
        t_Ty fRpY = atan2(m[2][1],m[2][2]);
        rfRAngle = t_Ty(0.0);  // any angle works
        rfYAngle = fRpY - rfRAngle;
        return false;
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
bool matrix3x3<t_Ty>::toEulerAnglesZXY (t_Ty& rfYAngle, t_Ty& rfPAngle,
    t_Ty& rfRAngle) const
{
    // rot =  cy*cz-sx*sy*sz -cx*sz           cz*sy+cy*sx*sz
    //        cz*sx*sy+cy*sz  cx*cz          -cy*cz*sx+sy*sz
    //       -cx*sy           sx              cx*cy

    rfPAngle = asin(m[2][1]);
    if ( rfPAngle < t_Ty(o_math_Pi_by_2) )
    {
        if ( rfPAngle > t_Ty(-o_math_Pi_by_2) )
        {
            rfYAngle = atan2(-m[0][1],m[1][1]);
            rfRAngle = atan2(-m[2][0],m[2][2]);
            return true;
        }
        else
        {
            // WARNING.  Not a unique solution.
            t_Ty fRmY = atan2(m[0][2],m[0][0]);
            rfRAngle = t_Ty(0.0);  // any angle works
            rfYAngle = rfRAngle - fRmY;
            return false;
        }
    }
    else
    {
        // WARNING.  Not a unique solution.
        t_Ty fRpY = atan2(m[0][2],m[0][0]);
        rfRAngle = t_Ty(0.0);  // any angle works
        rfYAngle = fRpY - rfRAngle;
        return false;
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
bool matrix3x3<t_Ty>::toEulerAnglesZYX (t_Ty& rfYAngle, t_Ty& rfPAngle,
    t_Ty& rfRAngle) const
{
    // rot =  cy*cz           cz*sx*sy-cx*sz  cx*cz*sy+sx*sz
    //        cy*sz           cx*cz+sx*sy*sz -cz*sx+cx*sy*sz
    //       -sy              cy*sx           cx*cy

    rfPAngle = asin(-m[2][0]);
    if ( rfPAngle < t_Ty(o_math_Pi_by_2) )
    {
        if ( rfPAngle > t_Ty(-o_math_Pi_by_2) )
        {
            rfYAngle = atan2(m[1][0],m[0][0]);
            rfRAngle = atan2(m[2][1],m[2][2]);
            return true;
        }
        else
        {
            // WARNING.  Not a unique solution.
            t_Ty fRmY = atan2(-m[0][1],m[0][2]);
            rfRAngle = t_Ty(0.0);  // any angle works
            rfYAngle = rfRAngle - fRmY;
            return false;
        }
    }
    else
    {
        // WARNING.  Not a unique solution.
        t_Ty fRpY = atan2(-m[0][1],m[0][2]);
        rfRAngle = t_Ty(0.0);  // any angle works
        rfYAngle = fRpY - rfRAngle;
        return false;
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::fromEulerAnglesXYZ (const t_Ty& fYAngle, const t_Ty& fPAngle,
    const t_Ty& fRAngle)
{
    t_Ty fCos, fSin;

    fCos = cos(fYAngle);
    fSin = sin(fYAngle);
    matrix3x3<t_Ty> kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

    fCos = cos(fPAngle);
    fSin = sin(fPAngle);
    matrix3x3<t_Ty> kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

    fCos = cos(fRAngle);
    fSin = sin(fRAngle);
    matrix3x3<t_Ty> kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

    *this = kXMat*(kYMat*kZMat);
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::fromEulerAnglesXZY (const t_Ty& fYAngle, const t_Ty& fPAngle,
    const t_Ty& fRAngle)
{
    t_Ty fCos, fSin;

    fCos = cos(fYAngle);
    fSin = sin(fYAngle);
    matrix3x3<t_Ty> kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

    fCos = cos(fPAngle);
    fSin = sin(fPAngle);
    matrix3x3<t_Ty> kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

    fCos = cos(fRAngle);
    fSin = sin(fRAngle);
    matrix3x3<t_Ty> kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

    *this = kXMat*(kZMat*kYMat);
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::fromEulerAnglesYXZ (const t_Ty& fYAngle, const t_Ty& fPAngle,
    const t_Ty& fRAngle)
{
    t_Ty fCos, fSin;

    fCos = cos(fYAngle);
    fSin = sin(fYAngle);
    matrix3x3<t_Ty> kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

    fCos = cos(fPAngle);
    fSin = sin(fPAngle);
    matrix3x3<t_Ty> kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

    fCos = cos(fRAngle);
    fSin = sin(fRAngle);
    matrix3x3<t_Ty> kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

    *this = kYMat*(kXMat*kZMat);
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::fromEulerAnglesYZX (const t_Ty& fYAngle, const t_Ty& fPAngle,
    const t_Ty& fRAngle)
{
    t_Ty fCos, fSin;

    fCos = cos(fYAngle);
    fSin = sin(fYAngle);
    matrix3x3<t_Ty> kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

    fCos = cos(fPAngle);
    fSin = sin(fPAngle);
    matrix3x3<t_Ty> kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

    fCos = cos(fRAngle);
    fSin = sin(fRAngle);
    matrix3x3<t_Ty> kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

    *this = kYMat*(kZMat*kXMat);
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::fromEulerAnglesZXY (const t_Ty& fYAngle, const t_Ty& fPAngle,
    const t_Ty& fRAngle)
{
    t_Ty fCos, fSin;

    fCos = cos(fYAngle);
    fSin = sin(fYAngle);
    matrix3x3<t_Ty> kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

    fCos = cos(fPAngle);
    fSin = sin(fPAngle);
    matrix3x3<t_Ty> kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

    fCos = cos(fRAngle);
    fSin = sin(fRAngle);
    matrix3x3<t_Ty> kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

    *this = kZMat*(kXMat*kYMat);
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::fromEulerAnglesZYX (const t_Ty& fYAngle, const t_Ty& fPAngle,
    const t_Ty& fRAngle)
{
    t_Ty fCos, fSin;

    fCos = cos(fYAngle);
    fSin = sin(fYAngle);
    matrix3x3<t_Ty> kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

    fCos = cos(fPAngle);
    fSin = sin(fPAngle);
    matrix3x3<t_Ty> kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

    fCos = cos(fRAngle);
    fSin = sin(fRAngle);
    matrix3x3<t_Ty> kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

    *this = kZMat*(kYMat*kXMat);
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::tridiagonal (t_Ty afDiag[3], t_Ty afSubDiag[3])
{
    // Householder reduction T = Q^t M Q
    //   Input:
    //     mat, symmetric 3x3 matrix M
    //   Output:
    //     mat, orthogonal matrix Q
    //     diag, diagonal entries of T
    //     subd, subdiagonal entries of T (T is symmetric)

    t_Ty fA = m[0][0];
    t_Ty fB = m[0][1];
    t_Ty fC = m[0][2];
    t_Ty fD = m[1][1];
    t_Ty fE = m[1][2];
    t_Ty fF = m[2][2];

    afDiag[0] = fA;
    afSubDiag[2] = 0.0;
    if ( abs(fC) >= epsilon<t_Ty>() )
    {
        t_Ty fLength = sqrt(fB*fB+fC*fC);
        t_Ty fInvLength = 1.0f/fLength;
        fB *= fInvLength;
        fC *= fInvLength;
        t_Ty fQ = 2.0f*fB*fE+fC*(fF-fD);
        afDiag[1] = fD+fC*fQ;
        afDiag[2] = fF-fC*fQ;
        afSubDiag[0] = fLength;
        afSubDiag[1] = fE-fB*fQ;
        m[0][0] = 1.0;
        m[0][1] = 0.0;
        m[0][2] = 0.0;
        m[1][0] = 0.0;
        m[1][1] = fB;
        m[1][2] = fC;
        m[2][0] = 0.0;
        m[2][1] = fC;
        m[2][2] = -fB;
    }
    else
    {
        afDiag[1] = fD;
        afDiag[2] = fF;
        afSubDiag[0] = fB;
        afSubDiag[1] = fE;
        m[0][0] = 1.0;
        m[0][1] = 0.0;
        m[0][2] = 0.0;
        m[1][0] = 0.0;
        m[1][1] = 1.0;
        m[1][2] = 0.0;
        m[2][0] = 0.0;
        m[2][1] = 0.0;
        m[2][2] = 1.0;
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
bool matrix3x3<t_Ty>::qlAlgorithm (t_Ty afDiag[3], t_Ty afSubDiag[3])
{
    // QL iteration with implicit shifting to reduce matrix from tridiagonal
    // to diagonal

    for (int i0 = 0; i0 < 3; i0++)
    {
        const unsigned int iMaxIter = 32;
        unsigned int iIter;
        for (iIter = 0; iIter < iMaxIter; iIter++)
        {
            int i1;
            for (i1 = i0; i1 <= 1; i1++)
            {
                t_Ty fSum = abs(afDiag[i1]) +
                    abs(afDiag[i1+1]);
                if ( abs(afSubDiag[i1]) + fSum == fSum )
                    break;
            }
            if ( i1 == i0 )
                break;

            t_Ty fTmp0 = (afDiag[i0+1]-afDiag[i0])/(2.0f*afSubDiag[i0]);
            t_Ty fTmp1 = sqrt(fTmp0*fTmp0+1.0f);
            if ( fTmp0 < 0.0 )
                fTmp0 = afDiag[i1]-afDiag[i0]+afSubDiag[i0]/(fTmp0-fTmp1);
            else
                fTmp0 = afDiag[i1]-afDiag[i0]+afSubDiag[i0]/(fTmp0+fTmp1);
            t_Ty fSin = 1.0;
            t_Ty fCos = 1.0;
            t_Ty fTmp2 = 0.0;
            for (int i2 = i1-1; i2 >= i0; i2--)
            {
                t_Ty fTmp3 = fSin*afSubDiag[i2];
                t_Ty fTmp4 = fCos*afSubDiag[i2];
                if ( abs(fTmp3) >= abs(fTmp0) )
                {
                    fCos = fTmp0/fTmp3;
                    fTmp1 = sqrt(fCos*fCos+1.0f);
                    afSubDiag[i2+1] = fTmp3*fTmp1;
                    fSin = 1.0f/fTmp1;
                    fCos *= fSin;
                }
                else
                {
                    fSin = fTmp3/fTmp0;
                    fTmp1 = sqrt(fSin*fSin+1.0f);
                    afSubDiag[i2+1] = fTmp0*fTmp1;
                    fCos = 1.0f/fTmp1;
                    fSin *= fCos;
                }
                fTmp0 = afDiag[i2+1]-fTmp2;
                fTmp1 = (afDiag[i2]-fTmp0)*fSin+2.0f*fTmp4*fCos;
                fTmp2 = fSin*fTmp1;
                afDiag[i2+1] = fTmp0+fTmp2;
                fTmp0 = fCos*fTmp1-fTmp4;

                for (int iRow = 0; iRow < 3; iRow++)
                {
                    fTmp3 = m[iRow][i2+1];
                    m[iRow][i2+1] = fSin*m[iRow][i2] +
                        fCos*fTmp3;
                    m[iRow][i2] = fCos*m[iRow][i2] -
                        fSin*fTmp3;
                }
            }
            afDiag[i0] -= fTmp2;
            afSubDiag[i0] = fTmp0;
            afSubDiag[i1] = 0.0;
        }

        if ( iIter == iMaxIter )
        {
            // should not get here under normal circumstances
            return false;
        }
    }

    return true;
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::eigenSolveSymmetric (t_Ty afEigenvalue[3],
    vector3_type akEigenvector[3]) const
{
    matrix3x3<t_Ty> kMatrix = *this;
    t_Ty afSubDiag[3];
    kMatrix.Tridiagonal(afEigenvalue,afSubDiag);
    kMatrix.QLAlgorithm(afEigenvalue,afSubDiag);

    for (size_t i = 0; i < 3; i++)
    {
        akEigenvector[i][0] = kMatrix[0][i];
        akEigenvector[i][1] = kMatrix[1][i];
        akEigenvector[i][2] = kMatrix[2][i];
    }

    // make eigenvectors form a right--handed system
    vector3_type kCross = akEigenvector[1].crossProduct(akEigenvector[2]);
    t_Ty fDet = akEigenvector[0].dotProduct(kCross);
    if ( fDet < 0.0 )
    {
        akEigenvector[2][0] = - akEigenvector[2][0];
        akEigenvector[2][1] = - akEigenvector[2][1];
        akEigenvector[2][2] = - akEigenvector[2][2];
    }
}
//-----------------------------------------------------------------------
template<typename t_Ty>
void matrix3x3<t_Ty>::tensorProduct (const typename matrix3x3<t_Ty>::vector3_type& rkU, const typename matrix3x3<t_Ty>::vector3_type& rkV,
    matrix3x3<t_Ty>& rkProduct)
{
    for (size_t iRow = 0; iRow < 3; iRow++)
    {
        for (size_t iCol = 0; iCol < 3; iCol++)
            rkProduct[iRow][iCol] = rkU[iRow]*rkV[iCol];
    }
}
//-----------------------------------------------------------------------

o_namespace_end(phantom, math)