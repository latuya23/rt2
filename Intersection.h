#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "Material.h"
#include <glm/glm.hpp>

class Intersection {
public:
	Intersection();
	Intersection(glm::dvec3 pos, Material m, double t, glm::dvec3 n);
	Intersection(glm::dvec3 pos, Material m, double t, glm::dvec3 n, int p_id);
	void SetNormal(glm::dvec3 n);
	virtual ~Intersection();
	Material GetMaterial(){return m_material;}
	glm::dvec3 GetNormal(){return normal;}
	float GetT(){return m_t;}
	glm::dvec3 GetPosition(){return position;}
	int GetId(){return m_p_id;}
private:
	Material m_material;
	double m_t;
	glm::dvec3 position;
	glm::dvec3 normal;
	int m_p_id;
};

#endif /* INTERSECTION_H_ */
