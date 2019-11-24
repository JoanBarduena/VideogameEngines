#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "Globals.h"
#include "MathGeoLib/include/MathGeoLib.h"

class GameObject;
class QuadtreeNode;

class Quadtree
{
public:
	Quadtree(const AABB& container);
	~Quadtree();
	void Draw();
	void AddGameObject(const GameObject* go);
private:
	QuadtreeNode* root;
};

class QuadtreeNode
{
	friend class Quadtree;

public:
	QuadtreeNode(const AABB& container);
	//Index marking which node from parent. 0 stats at top left, and counting clockwise
	QuadtreeNode(Quadtree* tree, QuadtreeNode* parent, uint index);
	~QuadtreeNode();

	bool AddGameobject(const GameObject* go);

private:
	void Split();
	void Redistribute();
	bool SendToChilds(const GameObject* go);

	void Draw();

public:
	AABB container;
	std::vector<QuadtreeNode> childs;

	//Pointer to tree, maybe not necessary
	Quadtree* tree;
	uint maxBucketSize = 3;
	std::vector<const GameObject*> bucket;
};


#endif 