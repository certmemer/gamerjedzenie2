#include "SDK.h"

void inline math::SinCos(float radians, float *sine, float *cosine)
{
    *sine = sin(radians);
    *cosine = cos(radians);
}

void math::VectorAngles(const vector& forward, QAngle &angles)
{
    if (forward[1] == 0.f && forward[0] == 0.f)
    {
        angles[0] = (forward[2] > 0.f) ? 270.f : 90.f; // Pitch (up/down)
        angles[1] = 0.f;  //yaw left/right
    }
    else
    {
        angles[0] = atan2(-forward[2], forward.Length2D()) * -180.f / M_PI;
        angles[1] = atan2(forward[1], forward[0]) * 180.f / M_PI;

        if (angles[1] > 90.f) angles[1] -= 180.f;
        else if (angles[1] < 90.f) angles[1] += 180.f;
        else if (angles[1] == 90.f) angles[1] = 0.f;
    }

    angles[2] = 0.f;
}

vector CrossProducxDt(const vector &a, const vector &b)
{
    return vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

void math::VectorAngles(const vector& forward, vector& up, QAngle& angles)
{
    vector left = CrossProducxDt(up, forward);
    left.NormalizeInPlace();

    float forwardDist = forward.Length2D();
    constexpr auto pif = 180.f / M_PI;

    if (forwardDist > 0.001f)
    {
        angles[0] = atan2f(-forward.z, forwardDist) * pif;// 180 / M_PI_F;
        angles[1] = atan2f(forward.y, forward.x) * pif;// 180 / M_PI_F;

        float upZ = (left.y * forward.x) - (left.x * forward.y);
        angles[2] = atan2f(left.z, upZ) * pif;// 180 / M_PI_F;
    }
    else
    {
        angles[0] = atan2f(-forward.z, forwardDist) * pif;// 180 / M_PI_F;
        angles[1] = atan2f(-left.x, left.y) * pif;// 180 / M_PI_F;
        angles[2] = 0;
    }
}

void math::angle_vectors(const QAngle &angles, vector *forward)
{
    float sp, sy, cp, cy;

    SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
    SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);

    forward->x = cp * cy;
    forward->y = cp * sy;
    forward->z = -sp;
}

void math::angle_vectors(const QAngle &angles, vector *forward, vector *right, vector *up)
{
    float sr, sp, sy, cr, cp, cy;

    SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
    SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);
    SinCos(DEG2RAD(angles[ROLL]), &sr, &cr);

    if (forward)
    {
        forward->x = cp * cy;
        forward->y = cp * sy;
        forward->z = -sp;
    }

    if (right)
    {
        right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
        right->y = (-1 * sr*sp*sy + -1 * cr*cy);
        right->z = -1 * sr*cp;
    }

    if (up)
    {
        up->x = (cr*sp*cy + -sr * -sy);
        up->y = (cr*sp*sy + -sr * cy);
        up->z = cr * cp;
    }
}

float math::get_fov(const QAngle& viewAngle, const QAngle& aimAngle)
{
    vector ang, aim;

    angle_vectors(viewAngle, &aim);
    angle_vectors(aimAngle, &ang);

    return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
}
QAngle math::calc_angle(const vector& src, const vector& dst)
{
    QAngle angles;
    //vector delta = src - dst;
    VectorAngles(src - dst, angles);
    //delta.Normalize();
    return angles;
}

float math::vector_distance(vector v1, vector v2)
{
    return FASTSQRT(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2));
}

void math::VectorTransform(const vector& in1, const matrix3x4a_t& in2, vector &out)
{
    out.x = in1.Dot(in2.m_flMatVal[0]) + in2.m_flMatVal[0][3];
    out.y = in1.Dot(in2.m_flMatVal[1]) + in2.m_flMatVal[1][3];
    out.z = in1.Dot(in2.m_flMatVal[2]) + in2.m_flMatVal[2][3];
}

float math::GetDelta(float hspeed, float maxspeed, float airaccelerate)
{
    auto term = (30.0 - (airaccelerate * maxspeed / 66.0)) / hspeed;

    if (term < 1.0f && term > -1.0f) {
        return acos(term);
    }

    return 0.f;
}

float math::ClampYaw(float x)
{
    while (x < -180.0f)
        x += 360.0f;

    while (x > 180.0f)
        x -= 360.0f;

    return x;
}

inline float math::RandFloat(float M, float N)
{
    return (float)(M + (rand() / (RAND_MAX / (N - M))));
}

inline vector math::ExtrapolateTick(vector p0, vector v0)
{
    return p0 + (v0 * i::globals->interval_per_tick);
}