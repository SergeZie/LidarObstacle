#ifndef KDTREE_H_
#define KDTREE_H_

#include "./render/render.h"


// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}

	~Node()
	{
		delete left;
		delete right;
	}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	~KdTree()
	{
		delete root;
	}
	void insert_aux(Node** curr, int depth, Node* target)
	{
		if(!(*curr))
		{
			*curr = target;
		}
		else
		{
			int dim = depth % target->point.size();
			if ((*curr)->point[dim] < target->point[dim]) //Target is bigger than node, go to the right of node.
			{
				insert_aux(&(*curr)->right, depth+1, target);
			}
			else
			{
				insert_aux(&(*curr)->left, depth+1, target);
			}
		}
			
	}

	void insert(std::vector<float> point, int id)
	{
		Node* node = new Node(point, id);
		insert_aux(&root, 0, node);

	}

	void search_aux(std::vector<float>& target, float distanceTol, Node* node, std::vector<int>& ids, uint depth)
	{
		if(!node)
			return;
		bool inDistance = true;
		uint dim = depth % node->point.size();
		for(size_t i = 0; i < node->point.size(); i++)
		{
			if(node->point[i] > target[i] + distanceTol || node->point[i] < target[i] - distanceTol)
			{
				inDistance = false;
				break;
			}	
		}

		if(inDistance)
		{
			ids.push_back(node->id);
			search_aux(target, distanceTol, node->left, ids, depth+1);
			search_aux(target, distanceTol, node->right, ids, depth+1);
		}
		else
		{
			if (node->point[dim] < target[dim]) //Target is bigger than node, go to the right of node.
			{
				search_aux(target, distanceTol, node->right,ids,  depth+1);
			}
			else
			{
				search_aux(target, distanceTol, node->left, ids, depth+1);
			}
		}

	}
	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
		search_aux(target, distanceTol, root, ids, 0);

		return ids;
	}
	

};



#endif
