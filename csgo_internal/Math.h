#pragma once

#define square( x ) ( x * x )

namespace math
{
	extern inline void SinCos(float radians, float *sine, float *cosine);
	extern void VectorAngles(const vector& forward, QAngle &angles);
	extern void VectorAngles(const vector& forward, vector& up, QAngle &angles);
	extern void angle_vectors(const QAngle& angles, vector *forward);
	extern void angle_vectors(const QAngle &angles, vector *forward, vector *right, vector *up);
	extern QAngle calc_angle(const vector& v1, const vector& v2);
	extern float get_fov(const QAngle& viewAngle, const QAngle& aimAngle);
	extern float vector_distance(vector v1, vector v2);
	extern void VectorTransform(const vector& in1, const matrix3x4a_t& in2, vector &out);
	extern float GetDelta(float hspeed, float maxspeed, float airaccelerate);
	extern float ClampYaw(float x);
	extern vector ExtrapolateTick(vector p0, vector v0);

	extern inline float RandFloat(float M, float N);

	// sperg cried about the previous method, 
	//here's not only a faster one but inaccurate as well to trigger more people
	inline float FASTSQRT(float x)
	{
		unsigned int i = *(unsigned int*)&x;

		i += 127 << 23;
		// approximation of square root
		i >>= 1;
		return *(float*)&i;
	}
}
