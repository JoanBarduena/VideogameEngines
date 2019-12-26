#include "QuadTree.h"
#include "Application.h"

#include "mmgr/mmgr.h"

Quadtree::Quadtree(const AABB& container)
{
	root = new QuadtreeNode(container); 
	root->tree = this; 
}

Quadtree::~Quadtree()
{
}

void Quadtree::Draw()
{
	root->Draw(); 
}

void Quadtree::AddGameObject(const GameObject* go)
{
	root->AddGameobject(go); 
}

QuadtreeNode::QuadtreeNode(const AABB& container) : container(container)
{
}

QuadtreeNode::QuadtreeNode(Quadtree* tree, QuadtreeNode* parent, uint index) : tree(tree)
{
	float3 minPoint, maxPoint;
	minPoint.y = parent->container.minPoint.y;
	maxPoint.y = parent->container.maxPoint.y;

	minPoint.x = (index / 2) == 1 ? parent->container.minPoint.x : (parent->container.maxPoint.x + parent->container.minPoint.x) / 2;
	maxPoint.x = (index / 2) == 1 ? (parent->container.maxPoint.x + parent->container.minPoint.x) / 2 : parent->container.maxPoint.x;

	minPoint.z = index % 2 == 0 ? parent->container.minPoint.z : (parent->container.maxPoint.z + parent->container.minPoint.z) / 2;
	maxPoint.z = index % 2 == 0 ? (parent->container.maxPoint.z + parent->container.minPoint.z) / 2 : parent->container.maxPoint.z;
	container = AABB(minPoint, maxPoint);
}

QuadtreeNode::~QuadtreeNode()
{
}

bool QuadtreeNode::AddGameobject(const GameObject* go)
{
	/*if (container.Intersects(go->mesh->GetAABB()))
	{
		if (childs.empty())
		{
			bucket.push_back(go);
			if (bucket.size() > maxBucketSize)
			{
				Split();
				Redistribute();
			}
		}
		else
		{
			SendToChilds(go);
		}

	}
	else*/
		return false;

}

void QuadtreeNode::Split()
{
	if (!childs.empty())
	{
		App->Console_Log("[error] Quadtree Node splitting when it already has childs");
	}	
	else
	{
		for (uint i = 0; i < 4; i++)
		{
			childs.push_back(QuadtreeNode(tree, this, i));
		}		
	}
}

void QuadtreeNode::Redistribute()
{
	for (std::vector<const GameObject*>::iterator it = bucket.begin(); it != bucket.end(); it++)
	{
		if (SendToChilds(*it))
		{
			it = bucket.erase(it);
		}
	}
}

bool QuadtreeNode::SendToChilds(const GameObject* go)
{
	uint intersectionCount = 0;
	uint intersectionChild = -1;

	for (uint i = 0; i < childs.size(); i++)
	{
		/*if (childs[i].container.Intersects(go->mesh->GetAABB()))
		{
			intersectionCount++;
			intersectionChild = i;
		}*/
	}
	if (intersectionCount == 1)
	{
		childs[intersectionChild].AddGameobject(go);
		return true;
	}
	else if (intersectionCount == 0)
		LOG("[error] Quadtree parent node intersecting but not child intersection found");
	return false;
}

void QuadtreeNode::Draw()
{
	App->renderer3D->AddAABB(container, Color(0.6, 0.19, 0.8, 1));

	for (uint i = 0; i < childs.size(); i++)
		childs[i].Draw();
}
