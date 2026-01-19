#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>

class hittable_list : public hittable
{
public:
	std::vector<std::shared_ptr<hittable>> objects;

	hittable_list() = default;
	hittable_list(std::shared_ptr<hittable> object) { add(object); }

	void clear() { objects.clear(); }
	void add(std::shared_ptr<hittable> object)
	{
		objects.emplace_back(object);
	}

	bool hit()
};


#endif // !HITTABLE_LIST_H
