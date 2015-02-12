#ifndef INTERSECTION_H_
#define INTERSECTION_H_
#include "nv/nv_math.h"
#include "Material.h"

class Intersection {
public:
	Intersection();
	Intersection(vec3 pos, Material m, double t, vec3 n);
	Intersection(vec3 pos, Material m, double t, vec3 n, int p_id);
	void SetNormal(vec3 n);
	virtual ~Intersection();
	Material GetMaterial(){return m_material;}
	vec3 GetNormal(){return normal;}
	float GetT(){return m_t;}
	vec3 GetPosition(){return position;}
	int GetId(){return m_p_id;}
private:
	Material m_material;
	double m_t;
	vec3 position;
	vec3 normal;
	int m_p_id;
};

#endif /* INTERSECTION_H_ */
