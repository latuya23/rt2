#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "Material.h"
#include <glm/glm.hpp>

class Intersection {
public:
	Intersection();
	Intersection(glm::vec3 pos, Material m, double t, glm::vec3 n);
	Intersection(glm::vec3 pos, Material m, double t, glm::vec3 n, int p_id);
	void SetNormal(glm::vec3 n);
	virtual ~Intersection();
	Material GetMaterial(){return m_material;}
	glm::vec3 GetNormal(){return normal;}
	float GetT(){return m_t;}
	glm::vec3 GetPosition(){return position;}
	int GetId(){return m_p_id;}
private:
	Material m_material;
	double m_t;
	glm::vec3 position;
	glm::vec3 normal;
	int m_p_id;
};

#endif /* INTERSECTION_H_ */
