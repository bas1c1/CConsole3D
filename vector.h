typedef struct
{
	float x,y;
} vec2;

vec2 addv(vec2 own, vec2 other) {
	return (vec2){own.x + other.x, own.y + other.y};
}

vec2 subv(vec2 own, vec2 other) {
	return (vec2){own.x - other.x, own.y - other.y};
}

vec2 diviv(vec2 own, vec2 other) {
	return (vec2){own.x / other.x, own.y / other.y};
}

vec2 mulv(vec2 own, vec2 other) {
	return (vec2){own.x * other.x, own.y * other.y};
}
/*ANOTHER*/
vec2 add(vec2 own, float other) {
	return (vec2){own.x + other, own.y + other};
}

vec2 sub(vec2 own, float other) {
	return (vec2){own.x - other, own.y - other};
}

vec2 divi(vec2 own, float other) {
	return (vec2){own.x / other, own.y / other};
}

vec2 mul(vec2 own, float other) {
	return (vec2){own.x * other, own.y * other};
}

vec2 usub(vec2 own) {
	return (vec2){-own.x, -own.y};
}

typedef struct
{
	float x,y,z;
} vec3;

vec3 v3addv(vec3 own, vec3 other) {
	return (vec3){own.x + other.x, own.y + other.y, own.z + other.z};
}

vec3 v3subv(vec3 own, vec3 other) {
	return (vec3){own.x - other.x, own.y - other.y, own.z - other.z};
}

vec3 v3diviv(vec3 own, vec3 other) {
	return (vec3){own.x / other.x, own.y / other.y, own.z / other.z};
}

vec3 v3mulv(vec3 own, vec3 other) {
	return (vec3){own.x * other.x, own.y * other.y, own.z * other.z};
}
/*ANOTHER*/
vec3 v3add(vec3 own, float other) {
	return (vec3){own.x + other, own.y + other, own.z + other};
}

vec3 v3sub(vec3 own, float other) {
	return (vec3){own.x - other, own.y - other, own.z - other};
}

vec3 v3divi(vec3 own, float other) {
	return (vec3){own.x / other, own.y / other, own.z / other};
}

vec3 v3mul(vec3 own, float other) {
	return (vec3){own.x * other, own.y * other, own.z * other};
}

vec3 v3usub(vec3 own) {
	return (vec3){-own.x, -own.y, -own.z};
}

double sign(double a) {
	return (0 < a) - (a < 0);
}

double step(double edge, double x) {
	return x > edge;
}

vec3 v3sign(vec3 v) {
	return (vec3){sign(v.x), sign(v.y), sign(v.z)};
}

vec3 v3step(vec3 edge, vec3 v) {
	return (vec3){step(edge.x, v.x), step(edge.y, v.y), step(edge.z, v.z)};
}

vec3 v3abs(vec3 v) {
	return (vec3){fabs(v.x), fabs(v.y), fabs(v.z)};
}

float checki(float val, float min, float max) {
	return fmax(fmin(val, max), min);
}

float len(vec2 v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

float v3len(vec3 v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 norm(vec3 v) {
	return v3divi(v, v3len(v));
}

float dot(vec3 v1, vec3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3 reflect(vec3 rd, vec3 n) {
	return v3subv(rd, v3mul(n, (2 * dot(n, rd))));
}

vec3 v3rotateX(vec3 vec, double angle) {
    vec3 _2vec = vec;
    _2vec.z = vec.z * cos(angle) - vec.y * sin(angle);
    _2vec.y = vec.z * sin(angle) + vec.y * cos(angle);
    return _2vec;
}

vec3 v3rotateY(vec3 vec, double angle)
{
    vec3 _2vec = vec;
    _2vec.x = vec.x * cos(angle) - vec.z * sin(angle);
    _2vec.z = vec.x * sin(angle) + vec.z * cos(angle);
    return _2vec;
}

vec3 v3rotateZ(vec3 vec, double angle) {
    vec3 _2vec = vec;
    _2vec.x = vec.x * cos(angle) - vec.y * sin(angle);
    _2vec.y = vec.x * sin(angle) + vec.y * cos(angle);
    return _2vec;
}