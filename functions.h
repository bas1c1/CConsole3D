vec2 sphere(vec3 ro, vec3 rd, vec3 pos, float r) {
	ro = v3subv(ro, pos);
	float b = dot(ro, rd);
	float c = dot(ro, ro) - r * r;
	float h = b * b - c;
	if (h < 0.0) return (vec2) {-1.0f, -1.0f};
	h = sqrt(h);
	return (vec2) {-b -h, -b + h};
}

vec2 box(vec3 ro, vec3 rd, vec3 boxSize, vec3 pos, vec3 *outNormal) {
	ro = v3subv(ro, pos);
	vec3 m = v3diviv((vec3){1.0f, 1.0f, 1.0f}, rd);
	vec3 n = v3mulv(m, ro);
	vec3 k = v3mulv(v3abs(m), boxSize);
	vec3 t1 = v3subv(v3usub(n), k);
	vec3 t2 = v3addv(v3usub(n), k);
	float tN = fmax(fmax(t1.x, t1.y), t1.z);
	float tF = fmin(fmin(t2.x, t2.y), t2.z);
	if (tN > tF || tF < 0.0) return (vec2){-1.0f, -1.0f};
	vec3 yzx = (vec3) {t1.y, t1.z, t1.x};
	vec3 zxy = (vec3) {t1.z, t1.x, t1.y};
	*outNormal = v3mulv(v3mulv(v3usub(v3sign(rd)), v3step(yzx, t1)), v3step(zxy, t1));
	return (vec2){tN, tF}; 
}

float plane(vec3 ro, vec3 rd, vec3 p, float w) {
	return -(dot(ro, p) + w) / dot(rd, p);
}