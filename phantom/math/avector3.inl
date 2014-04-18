/*
-----------------------------------------------------------------------------
This source file is inspirted from Mathias Goldberg ArrayMath code extracted from OGRE
with its agreement
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/
-----------------------------------------------------------------------------
*/

#if defined(X)
#undef X
#endif

#if defined(Y)
#undef Y
#endif

#define X chunk[0]
#define Y chunk[1]
#define Z chunk[2]

#define aX aChunkBase[0]
#define aY aChunkBase[0]
#define aZ aChunkBase[0]

#define bX bChunkBase[0]
#define bY bChunkBase[1]
#define bZ bChunkBase[2]

#define lX lChunkBase[0]
#define lY lChunkBase[1]
#define lZ lChunkBase[2]

#define X0 lhsChunk[0]
#define Y0 lhsChunk[1]
#define Z0 lhsChunk[2]

#define X1 rhsChunk[0]
#define Y1 rhsChunk[1]
#define Z1 rhsChunk[2]

template<typename t_Ty>
	inline const avector3<t_Ty>& avector3<t_Ty>::operator + () const
	{
		return *this;
	};
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline avector3<t_Ty> avector3<t_Ty>::operator - () const
	{
		return avector3<t_Ty>(
			_mm_xor_ps( X, sse2<t_Ty>::SIGN_MASK ),	//-x
			_mm_xor_ps( Y, sse2<t_Ty>::SIGN_MASK ),	//-y
			_mm_xor_ps( Z, sse2<t_Ty>::SIGN_MASK ) );	//-z
	}
	//-----------------------------------------------------------------------------------

    template<typename t_Ty>
    inline avector3<t_Ty> avector3<t_Ty>::operator + ( const avector3<t_Ty> &rhs ) const
    {
        const t_Ty * o_restrict_alias lhsChunk = chunk;
        const t_Ty * o_restrict_alias rhsChunk = rhs.chunk;
        return avector3<t_Ty>(
            _mm_add_ps( X0, X1 ),
            _mm_add_ps( Y0, Y1 ),
            _mm_add_ps( Z0, Z1 ) );
    }

    template<typename t_Ty>
    inline avector3<t_Ty> avector3<t_Ty>::operator - ( const avector3<t_Ty> &rhs ) const
    {
        const t_Ty * o_restrict_alias lhsChunk = chunk;
        const t_Ty * o_restrict_alias rhsChunk = rhs.chunk;
        return avector3<t_Ty>(
            _mm_sub_ps( X0, X1 ),
            _mm_sub_ps( Y0, Y1 ),
            _mm_sub_ps( Z0, Z1 ) );
    }

    template<typename t_Ty>
    inline avector3<t_Ty> avector3<t_Ty>::operator * ( const avector3<t_Ty> &rhs ) const
    {
        const t_Ty * o_restrict_alias lhsChunk = chunk;
        const t_Ty * o_restrict_alias rhsChunk = rhs.chunk;
        return avector3<t_Ty>(
            _mm_mul_ps( X0, X1 ),
            _mm_mul_ps( Y0, Y1 ),
            _mm_mul_ps( Z0, Z1 ) );
    }

    template<typename t_Ty>
    inline avector3<t_Ty> avector3<t_Ty>::operator / ( const avector3<t_Ty> &rhs ) const
    {
        const t_Ty * o_restrict_alias lhsChunk = chunk;
        const t_Ty * o_restrict_alias rhsChunk = rhs.chunk;
        return avector3<t_Ty>(
            _mm_div_ps( X0, X1 ),
            _mm_div_ps( Y0, Y1 ),
            _mm_div_ps( Z0, Z1 ) );
    }

    template<typename t_Ty>
    inline avector3<t_Ty> operator * ( const t_Ty fScalar, const avector3<t_Ty> &rhs )
    {
        t_Ty lhs = _mm_set1_ps( fScalar );
        return avector3<t_Ty>(
            _mm_mul_ps( lhs, rhs.X ),
            _mm_mul_ps( lhs, rhs.Y ),
            _mm_mul_ps( lhs, rhs.Z ) );
    }

    template<typename t_Ty>
    inline avector3<t_Ty> avector3<t_Ty>::operator + ( const t_Ty fScalar ) const
    {
        const t_Ty * o_restrict_alias lhsChunk = chunk;
        t_Ty rhs = _mm_set1_ps( fScalar );
        return avector3<t_Ty>(
            _mm_add_ps( X0, rhs ),
            _mm_add_ps( Y0, rhs ),
            _mm_add_ps( Z0, rhs ) );
    }

    template<typename t_Ty>
    inline avector3<t_Ty> avector3<t_Ty>::operator - ( const t_Ty fScalar ) const
    {
        const t_Ty * o_restrict_alias lhsChunk = chunk;
        t_Ty rhs = _mm_set1_ps( fScalar );
        return avector3<t_Ty>(
            _mm_sub_ps( X0, rhs ),
            _mm_sub_ps( Y0, rhs ),
            _mm_sub_ps( Z0, rhs ) );
    }

    template<typename t_Ty>
    inline avector3<t_Ty> avector3<t_Ty>::operator * ( const t_Ty fScalar ) const
    {
        const t_Ty * o_restrict_alias lhsChunk = chunk;
        t_Ty rhs = _mm_set1_ps( fScalar );
        return avector3<t_Ty>(
            _mm_mul_ps( X0, rhs ),
            _mm_mul_ps( Y0, rhs ),
            _mm_mul_ps( Z0, rhs ) );
    }

    template<typename t_Ty>
    inline avector3<t_Ty> avector3<t_Ty>::operator / ( const t_Ty fScalar )
    {
        o_assert( fScalar != 0.0 );
        t_Ty rhs = _mm_set1_ps( fInv );
        const t_Ty * o_restrict_alias lhsChunk = chunk;
        return avector3<t_Ty>(
            _mm_div_ps( X0, rhs ),
            _mm_div_ps( Y0, rhs ),
            _mm_div_ps( Z0, rhs ) );
    }

    template<typename t_Ty>
    inline avector3<t_Ty>& avector3<t_Ty>::operator += ( const avector3<t_Ty> &a )
    {
        t_Ty * o_restrict_alias lChunkBase = chunk;
        const t_Ty * o_restrict_alias aChunkBase = a.chunk;
        lX = _mm_add_ps( lX, aX );
        lY = _mm_add_ps( lY, aY );
        lZ = _mm_add_ps( lZ, aZ );
        return *this;
    }

    template<typename t_Ty>
    inline avector3<t_Ty>& avector3<t_Ty>::operator -= ( const avector3<t_Ty> &a )
    {
        t_Ty * o_restrict_alias lChunkBase = chunk;
        const t_Ty * o_restrict_alias aChunkBase = a.chunk;
        lX = _mm_sub_ps( lX, aX );
        lY = _mm_sub_ps( lY, aY );
        lZ = _mm_sub_ps( lZ, aZ );
        return *this;
    }

    template<typename t_Ty>
    inline avector3<t_Ty>& avector3<t_Ty>::operator *= ( const avector3<t_Ty> &a )
    {
        t_Ty * o_restrict_alias lChunkBase = chunk;
        const t_Ty * o_restrict_alias aChunkBase = a.chunk;
        lX = _mm_mul_ps( lX, aX );
        lY = _mm_mul_ps( lY, aY );
        lZ = _mm_mul_ps( lZ, aZ );
        return *this;
    }

    template<typename t_Ty>
    inline avector3<t_Ty>& avector3<t_Ty>::operator /= ( const avector3<t_Ty> &a )
    {
        t_Ty * o_restrict_alias lChunkBase = chunk;
        const t_Ty * o_restrict_alias aChunkBase = a.chunk;
        lX = _mm_div_ps( lX, aX );
        lY = _mm_div_ps( lY, aY );
        lZ = _mm_div_ps( lZ, aZ );
        return *this;
    }

    template<typename t_Ty>
	inline avector3<t_Ty> avector3<t_Ty>::Cmov4( const avector3<t_Ty> &arg1, const avector3<t_Ty> &arg2, t_Ty mask )
	{
		return avector3<t_Ty>(
				sse2<t_Ty>::Cmov4( arg1.X, arg2.X, mask ),
				sse2<t_Ty>::Cmov4( arg1.Y, arg2.Y, mask ),
				sse2<t_Ty>::Cmov4( arg1.Z, arg2.Z, mask ) );
	}


	//Functions
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline t_Ty avector3<t_Ty>::length() const
    {
		return
		_mm_sqrt_ps( _mm_add_ps( _mm_add_ps(					//sqrt(
				_mm_mul_ps( X, X ),	//(x * x +
				_mm_mul_ps( Y, Y ) ),	//y * y) +
			_mm_mul_ps( Z, Z ) ) );	//z * z )
    }
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline t_Ty avector3<t_Ty>::squaredLength() const
    {
        return
		_mm_add_ps( _mm_add_ps(
			_mm_mul_ps( X, X ),	//(x * x +
			_mm_mul_ps( Y, Y ) ),	//y * y) +
		_mm_mul_ps( Z, Z ) );		//z * z )
    }
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline t_Ty avector3<t_Ty>::distance( const avector3<t_Ty>& rhs ) const
    {
        return (*this - rhs).length();
    }
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline t_Ty avector3<t_Ty>::distanceSquared( const avector3<t_Ty>& rhs ) const
    {
        return (*this - rhs).lengthSquared();
    }
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline t_Ty avector3<t_Ty>::dot( const avector3<t_Ty>& vec ) const
	{
		return
		_mm_add_ps( _mm_add_ps(
			_mm_mul_ps( X, vec.X ) ,	//( x * vec.x   +
			_mm_mul_ps( Y, vec.Y ) ),	//  y * vec.y ) +
			_mm_mul_ps( Z, vec.Z ) );	//  z * vec.z
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline t_Ty avector3<t_Ty>::absDotProduct( const avector3<t_Ty>& vec ) const
	{
		return
		_mm_add_ps( _mm_add_ps(
			sse2<t_Ty>::Abs4( _mm_mul_ps( X, vec.X ) ),	//( abs( x * vec.x )   +
			sse2<t_Ty>::Abs4( _mm_mul_ps( Y, vec.Y ) ) ),//  abs( y * vec.y ) ) +
			sse2<t_Ty>::Abs4( _mm_mul_ps( Z, vec.Z ) ) );//  abs( z * vec.z )
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline void avector3<t_Ty>::normalise( void )
	{
		t_Ty sqLength = _mm_add_ps( _mm_add_ps(
			_mm_mul_ps( X, X ),	//(x * x +
			_mm_mul_ps( Y, Y ) ),	//y * y) +

		//Convert sqLength's 0s into 1, so that zero vectors remain as zero
		//Denormals are treated as 0 during the check.
		//Note: We could create a mask now and nuke nans after InvSqrt, however
		//generating the nans could impact performance in some architectures
		sqLength = sse2<t_Ty>::Cmov4( sqLength, sse2<t_Ty>::ONE,
										_mm_cmpgt_ps( sqLength, sse2<t_Ty>::FLOAT_MIN ) );
		t_Ty invLength = sse2<t_Ty>::InvSqrtNonZero4( sqLength );
		X = _mm_mul_ps( X, invLength ); //x * invLength
		Y = _mm_mul_ps( Y, invLength ); //y * invLength
	}
	//-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline avector3<t_Ty> avector3<t_Ty>::cross( const avector3<t_Ty>& rkVec ) const
    {
        return avector3<t_Ty>(
			_mm_sub_ps(
				_mm_mul_ps( Y, rkVec.Z ),
				_mm_mul_ps( Z, rkVec.Y ) ),	//y * rkVec.z - z * rkVec.y
			_mm_sub_ps(
				_mm_mul_ps( Z, rkVec.X ),
				_mm_mul_ps( X, rkVec.Z ) ),	//z * rkVec.x - x * rkVec.z
			_mm_sub_ps(
				_mm_mul_ps( X, rkVec.Y ),
				_mm_mul_ps( Y, rkVec.X ) ) );	//x * rkVec.y - y * rkVec.x
    }
	//-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline avector3<t_Ty> avector3<t_Ty>::midPoint( const avector3<t_Ty>& rkVec ) const
    {
		return avector3<t_Ty>(
			_mm_mul_ps( _mm_add_ps( X, rkVec.X ), sse2<t_Ty>::HALF ),
			_mm_mul_ps( _mm_add_ps( Y, rkVec.Y ), sse2<t_Ty>::HALF ),
			_mm_mul_ps( _mm_add_ps( Z, rkVec.Z ), sse2<t_Ty>::HALF ) );
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline void avector3<t_Ty>::makeFloor( const avector3<t_Ty>& cmp )
    {
		t_Ty * o_restrict_alias aChunkBase = chunk;
		const t_Ty * o_restrict_alias bChunkBase = cmp.chunk;
		aX = _mm_min_ps( aX, bX );
		aY = _mm_min_ps( aY, bY );
		aZ = _mm_min_ps( aZ, bZ );
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline void avector3<t_Ty>::makeCeil( const avector3<t_Ty>& cmp )
    {
		t_Ty * o_restrict_alias aChunkBase = chunk;
		const t_Ty * o_restrict_alias bChunkBase = cmp.chunk;
		aX = _mm_max_ps( aX, bX );
		aY = _mm_max_ps( aY, bY );
		aZ = _mm_max_ps( aZ, bZ );
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline t_Ty avector3<t_Ty>::getMinComponent() const
	{
		return _mm_min_ps( X, _mm_min_ps( Y, Z ) );
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline t_Ty avector3<t_Ty>::getMaxComponent() const
	{
		return _mm_max_ps( X, _mm_max_ps( Y, Z ) );
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline void avector3<t_Ty>::setToSign()
	{
		// x = 1.0f | (x & 0x80000000)
		t_Ty signMask = _mm_set1_ps( -0.0f );
		X = _mm_or_ps( sse2<t_Ty>::ONE, _mm_and_ps( signMask, X ) );
		Y = _mm_or_ps( sse2<t_Ty>::ONE, _mm_and_ps( signMask, Y ) );
		Z = _mm_or_ps( sse2<t_Ty>::ONE, _mm_and_ps( signMask, Z ) );
	}/*
	//-----------------------------------------------------------------------------------
	inline avector3<t_Ty> avector3<t_Ty>::perpendicular( void ) const
    {
        avector3<t_Ty> perp = this->crossProduct( avector3<t_Ty>::UNIT_X );

		const t_Ty mask = _mm_cmple_ps( perp.squaredLength(), sse2<t_Ty>::fSqEpsilon );
        // Check length
        if( _mm_movemask_ps( mask ) )
        {
            / * One or more of these vectors are the X axis multiplied by a scalar,
			   so we have to use another axis for those.
            * /
            avector3<t_Ty> perp1 = this->crossProduct( avector3<t_Ty>::UNIT_Y );
			perp.X = sse2<t_Ty>::Cmov4( perp1.X, perp.X, mask );
			perp.Y = sse2<t_Ty>::Cmov4( perp1.Y, perp.Y, mask );
			perp.Z = sse2<t_Ty>::Cmov4( perp1.Z, perp.Z, mask );
        }
		perp.normalise();

        return perp;
	}*/
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline avector3<t_Ty> avector3<t_Ty>::normalized( void ) const
	{
		t_Ty sqLength = _mm_add_ps(
			_mm_mul_ps( X, X ),	//(x * x +
			_mm_mul_ps( Y, Y ) );		//z * z )

		//Convert sqLength's 0s into 1, so that zero vectors remain as zero
		//Denormals are treated as 0 during the check.
		//Note: We could create a mask now and nuke nans after InvSqrt, however
		//generating the nans could impact performance in some architectures
		sqLength = sse2<t_Ty>::Cmov4( sqLength, sse2<t_Ty>::ONE,
										_mm_cmpgt_ps( sqLength, sse2<t_Ty>::FLOAT_MIN ) );
		t_Ty invLength = sse2<t_Ty>::InvSqrtNonZero4( sqLength );

		return avector3<t_Ty>(
			_mm_mul_ps( X, invLength ),	//x * invLength
			_mm_mul_ps( Y, invLength ),	//y * invLength
			_mm_mul_ps( Z, invLength ) );	//z * invLength
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline avector3<t_Ty> avector3<t_Ty>::reflect( const avector3<t_Ty>& normal ) const
	{
        const t_Ty twoPointZero = _mm_set_ps1( 2.0f );
 		return ( *this - ( _mm_mul_ps( twoPointZero, dot( normal ) ) * normal ) );
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline void avector3<t_Ty>::inverseLeaveZeroes( void )
	{
		//Use InvNonZero, we're gonna nuke the NaNs anyway.
		X = sse2<t_Ty>::CmovRobust( X, sse2<t_Ty>::InvNonZero4(X),
												 _mm_cmpeq_ps( X, _mm_setzero_ps() ) );
		Y = sse2<t_Ty>::CmovRobust( Y, sse2<t_Ty>::InvNonZero4(Y),
												 _mm_cmpeq_ps( Y, _mm_setzero_ps() ) );
		Z = sse2<t_Ty>::CmovRobust( Z, sse2<t_Ty>::InvNonZero4(Z),
												 _mm_cmpeq_ps( Z, _mm_setzero_ps() ) );
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline int avector3<t_Ty>::isNaN( void ) const
	{
		t_Ty mask = _mm_and_ps( _mm_and_ps( 
			_mm_cmpeq_ps( X, X ),
			_mm_cmpeq_ps( Y, Y ) ),
			_mm_cmpeq_ps( Z, Z ) );

		return _mm_movemask_ps( mask ) ^ 0x0000000f;
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline avector3<t_Ty> avector3<t_Ty>::primaryAxis( void ) const
	{
		// We could've used some operators, i.e.
		// xVec = sse2<t_Ty>::Cmov( avector3<t_Ty>::UNIT_X, avector3<t_Ty>::NEGATIVE_UNIT_X )
		// and so forth, which would've increased readability considerably. However,
		// MSVC's compiler ability to do constant propagation & remove dead code sucks,
		// which means it would try to cmov the Y & Z component even though we already
		// know it's always zero for both +x & -x. Therefore, we do it the manual
		// way. Doing this the "human readable way" results in massive amounts of wasted
		// instructions and stack memory abuse.
		// See avector3<t_Ty>::primaryAxis() to understand what's actually going on.
		t_Ty absx = sse2<t_Ty>::Abs4( X );
		t_Ty absy = sse2<t_Ty>::Abs4( Y );
		t_Ty absz = sse2<t_Ty>::Abs4( Z );

		//xVec = x > 0 ? avector3<t_Ty>::UNIT_X : avector3<t_Ty>::NEGATIVE_UNIT_X;
		t_Ty sign = sse2<t_Ty>::Cmov4( _mm_set1_ps( 1.0f ), _mm_set1_ps( -1.0f ),
											_mm_cmpgt_ps( X, _mm_setzero_ps() ) );
		avector3<t_Ty> xVec( sign, _mm_setzero_ps(), _mm_setzero_ps() );

		//yVec = y > 0 ? avector3<t_Ty>::UNIT_Y : avector3<t_Ty>::NEGATIVE_UNIT_Y;
		sign = sse2<t_Ty>::Cmov4( _mm_set1_ps( 1.0f ), _mm_set1_ps( -1.0f ),
									_mm_cmpgt_ps( Y, _mm_setzero_ps() ) );
		avector3<t_Ty> yVec( _mm_setzero_ps(), sign, _mm_setzero_ps() );

		//zVec = z > 0 ? avector3<t_Ty>::UNIT_Z : avector3<t_Ty>::NEGATIVE_UNIT_Z;
		sign = sse2<t_Ty>::Cmov4( _mm_set1_ps( 1.0f ), _mm_set1_ps( -1.0f ),
									_mm_cmpgt_ps( Z, _mm_setzero_ps() ) );
		avector3<t_Ty> zVec( _mm_setzero_ps(), _mm_setzero_ps(), sign );

		//xVec = absx > absz ? xVec : zVec
		t_Ty mask = _mm_cmpgt_ps( absx, absz );
		xVec.X = sse2<t_Ty>::Cmov4( xVec.X, zVec.X, mask );
		xVec.Z = sse2<t_Ty>::Cmov4( xVec.Z, zVec.Z, mask );

		//yVec = absy > absz ? yVec : zVec
		mask = _mm_cmpgt_ps( absy, absz );
		yVec.Y = sse2<t_Ty>::Cmov4( yVec.Y, zVec.Y, mask );
		yVec.Z = sse2<t_Ty>::Cmov4( yVec.Z, zVec.Z, mask );

		yVec.Cmov4( _mm_cmpgt_ps( absx, absy ), xVec );
		return yVec;
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline avector3<t_Ty> avector3<t_Ty>::collapseMin( void ) const
	{
		OGRE_ALIGNED_DECL( t_Ty, vals[4], OGRE_SIMD_ALIGNMENT );
		t_Ty aosVec0, aosVec1, aosVec2, aosVec3;

		//Transpose XXXX YYYY ZZZZ to XYZZ XYZZ XYZZ XYZZ
		t_Ty tmp2, tmp0;
		tmp0   = _mm_shuffle_ps( X, Y, 0x44 );
        tmp2   = _mm_shuffle_ps( X, Y, 0xEE );

        aosVec0 = _mm_shuffle_ps( tmp0, Z, 0x08 );
		aosVec1 = _mm_shuffle_ps( tmp0, Z, 0x5D );
		aosVec2 = _mm_shuffle_ps( tmp2, Z, 0xA8 );
		aosVec3 = _mm_shuffle_ps( tmp2, Z, 0xFD );

		//Do the actual operation
		aosVec0 = _mm_min_ps( aosVec0, aosVec1 );
		aosVec2 = _mm_min_ps( aosVec2, aosVec3 );
		aosVec0 = _mm_min_ps( aosVec0, aosVec2 );

		_mm_store_ps( vals, aosVec0 );

		return avector3<t_Ty>( vals[0], vals[1], vals[2] );
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline avector3<t_Ty> avector3<t_Ty>::collapseMax( void ) const
	{
		OGRE_ALIGNED_DECL( t_Ty, vals[4], OGRE_SIMD_ALIGNMENT );
		t_Ty aosVec0, aosVec1, aosVec2, aosVec3;

		//Transpose XXXX YYYY ZZZZ to XYZZ XYZZ XYZZ XYZZ
		t_Ty tmp2, tmp0;
		tmp0   = _mm_shuffle_ps( X, Y, 0x44 );
        tmp2   = _mm_shuffle_ps( X, Y, 0xEE );

        aosVec0 = _mm_shuffle_ps( tmp0, Z, 0x08 );
		aosVec1 = _mm_shuffle_ps( tmp0, Z, 0x5D );
		aosVec2 = _mm_shuffle_ps( tmp2, Z, 0xA8 );
		aosVec3 = _mm_shuffle_ps( tmp2, Z, 0xFD );

		//Do the actual operation
		aosVec0 = _mm_max_ps( aosVec0, aosVec1 );
		aosVec2 = _mm_max_ps( aosVec2, aosVec3 );
		aosVec0 = _mm_max_ps( aosVec0, aosVec2 );

		_mm_store_ps( vals, aosVec0 );

		return avector3<t_Ty>( vals[0], vals[1], vals[2] );
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline void avector3<t_Ty>::Cmov4( t_Ty mask, const avector3<t_Ty> &replacement )
	{
		t_Ty * o_restrict_alias aChunkBase = chunk;
		const t_Ty * o_restrict_alias bChunkBase = replacement.chunk;
		aX = sse2<t_Ty>::Cmov4( bX, aX, mask );
		aY = sse2<t_Ty>::Cmov4( bY, aY, mask );
		aZ = sse2<t_Ty>::Cmov4( bZ, aZ, mask );
	}
    //-----------------------------------------------------------------------------------
    template<typename t_Ty>
	inline void avector3<t_Ty>::CmovRobust( t_Ty mask, const avector3<t_Ty> &replacement )
	{
		t_Ty * o_restrict_alias aChunkBase = chunk;
		const t_Ty * o_restrict_alias bChunkBase = replacement.chunk;
		aX = sse2<t_Ty>::CmovRobust( bX, aX, mask );
		aY = sse2<t_Ty>::CmovRobust( bY, aY, mask );
		aZ = sse2<t_Ty>::CmovRobust( bZ, aZ, mask );
	}
	//-----------------------------------------------------------------------------------

}
