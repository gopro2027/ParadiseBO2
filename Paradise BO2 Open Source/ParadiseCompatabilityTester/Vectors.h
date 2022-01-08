namespace myMath {
	#define PI (3.1415926535897931)
float abs(float a) {
	if (a < 0)
		return a*-1;
	return a;
}
float DegreesToRadians(float Degrees)
{
    return Degrees * PI / 180.0f;
}
 
float RadiansToDegrees(float Radians)
{
    return Radians * 180.0f / PI;
}
 
float pow(float num, int power) {
    float ret = 1;
    for (int i = 0; i < power; i++)
        ret = ret*num;
    return ret;
}
 
float root(float num, int nroot) {
    int iterations = 15 * (nroot-1);
    float x = iterations*100;
    for (int i = 1; i < iterations; i++) {
       x = (float)(((float)1/nroot)*(((nroot-1)*x)+(num/pow(x,nroot-1))));
    }
    return x;
}
 
float sin(float deg) {
    bool neg = false;
    while (deg >= 360) deg = deg - 360;
    while (deg < 0) deg = deg + 360;
    if (deg > 180) {
        deg = deg - 180;
        neg = true;
    }
    float ret = (float)(4*deg*(180-deg))/(40500-(deg*(180-deg)));
    if (neg)return ret*-1;
    return ret;
}
 
float cos(float AnglesDeg)
{
 float AnglesRad = DegreesToRadians(AnglesDeg);
 float Rad = (float)(PI/2.0f)-AnglesRad;
 float ang = RadiansToDegrees(Rad);
    return sin(ang);
}
 
float tan(float AnglesDeg)
{
    float sinus = sin(AnglesDeg);
    float cosinus = cos(AnglesDeg);
    return sinus/cosinus;
}

double atan(double x, int n)
{
	double a = 0.0;// 1st term
	double sum = 0.0;

	// special cases
	if( x == 1.0 ) return PI/4.0;
	if( x == -1.0 ) return -PI/4.0;

	if(n > 0)
	{
	    if( (x < -1.0) || (x > 1.0) )
	    {
	        // constant term
	        if( x > 1.0 )
                sum = PI/2.0;
            else
                sum = -PI/2.0;
            // initial value of a
            a = -1.0/x;
            for(int j=1; j<=n; j++)
            {
                sum += a;
                a *= -1.0*(2.0*j-1)/((2.0*j+1)*x*x);// next term from last
            }
	    }
	    else// -1 < x < 1
	    {
	        // constant term
	        sum = 0.0;
	        // initial value of a
            a = x;
            for(int j=1; j<=n; j++)
            {
                sum += a;
                a *= -1.0*(2.0*j-1)*x*x/(2.0*j+1);// next term from last
            }
	    }
		//r_err = a;// max. error = 1st term not taken for alternating series
	}

	return sum;
}

double atan2(double y, double x)
{
    double u = atan( y/x, 24);
    if( x < 0.0 )// 2nd, 3rd quadrant
    {
        if( u > 0.0 )// will go to 3rd quadrant
            u -= PI;
        else
            u += PI;
    }
    return u;
}


}




typedef struct Vector2
{
	float x, y;

}Vector2, *PVector2;

typedef struct Vector3
{
	float x, y, z;
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	const bool operator== (Vector3 const &Vector)
	{
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z);
	}
	const Vector3& operator+ (Vector3 const &Vector)
	{
		return Vector3(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z);
	}
	const Vector3& operator- (Vector3 const &Vector)
	{
		return Vector3(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z);
	}

	float Distance(Vector3 const &Vector)
	{
		return sqrt(DistanceEx(Vector));
	}
	float DistanceEx(Vector3 const &Vector)
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	float DotProduct(Vector3 const &Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}
	const Vector3 &RoundHalfUp()
	{
		return Vector3(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}\
		const Vector3 &RoundHalfDown()
	{
		return Vector3(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}
} Vector3, *PVector3;


float dx, dy, dz;
float Distance3D(Vector3 c1, Vector3 c2)
{
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;
	float dz = c2.z - c1.z;

	return sqrt((float)((dx * dx) + (dy * dy) + (dz * dz)));
}

typedef struct Vector4
{
	float x, y, z, a;
	Vector4()
	{
		x = y = z = a = 0;
	}
	Vector4(float x, float y, float z, float a)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->a = a;
	}

} Vector4, *PVector4;

Vector3 vectoangles(Vector3 Angles)
{
	float forward;
	float yaw, pitch;
	//float PI = 3.1415926535897931;
	if (Angles.x == 0 && Angles.y == 0)
	{
		yaw = 0;
		if (Angles.z > 0) pitch = 90.00;
		else pitch = 270.00;
	}
	else
	{
		if (Angles.x != -1) yaw = (float)(atan2((double)Angles.y, (double)Angles.x) * 180.00 / PI);
		else if (Angles.y > 0) yaw = 90.00;
		else yaw = 270;
		if (yaw < 0) yaw += 360.00;

		forward = (float)sqrt((double)(Angles.x * Angles.x + Angles.y * Angles.y));
		pitch = (float)(atan2((double)Angles.z, (double)forward) * 180.00 / PI);
		if (pitch < 0) pitch += 360.00;
	}
	Vector3 AnglesVector(-pitch, yaw, 0);
	return AnglesVector;
}

Vector3 Difference(Vector3 Target, Vector3 Entity)
{
	Vector3 Return = Target - Entity;
	return Return;
}

typedef struct vec4_t
{
	float x, y, z, w;
	vec4_t()
	{
		x = y = z = w = 0;
	};
};

void VectorCopy(Vector3 *orig, Vector3 *final) {
	final->x = orig->x;
	final->y = orig->y;
	final->z = orig->z;
}