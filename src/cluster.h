#ifndef CLUSTER_H_
#define CLUSTER_H_


#include "kdtree.h"

inline void clusterProximity(int pointIndex, std::vector<int>& cluster, std::vector<bool>* proceessedPoints, 
							KdTree* tree, const std::vector<std::vector<float>>& points, float distanceTol)
{
	
	(*proceessedPoints)[pointIndex] = true;
	cluster.push_back(pointIndex);
	std::vector<int> foundCluster;
	foundCluster = tree->search(points[pointIndex], distanceTol);

	for(int id : foundCluster)
	{
		if(!(*proceessedPoints)[id])
			clusterProximity(id, cluster, proceessedPoints, tree, points, distanceTol);
	}


}

inline std::vector<std::vector<int>> euclideanCluster(const std::vector<std::vector<float>>& points, KdTree* tree, float distanceTol)
{



	std::vector<std::vector<int>> clusters;
	std::vector<bool> processed(points.size(),false); //Init the processed vector with false.

	for (size_t i = 0; i < points.size(); i++)
	{
		if(processed[i])
		{
			continue;
		}
		std::vector<int> cluster;

		clusterProximity(i, cluster, &processed, tree, points, distanceTol);

		clusters.push_back(cluster);

	}

	return clusters;

}

#endif /* CLUSTER_H_ */