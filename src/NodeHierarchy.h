#pragma once
#include "ExportableResources.h"

class ExportableNode;

typedef std::map<std::string, std::unique_ptr<ExportableNode>> NodeTable;

// Maps each DAG path to the corresponding node
// Owns and creates each node on the fly.
class NodeHierarchy
{
public:
	explicit NodeHierarchy(ExportableResources& resources);
	~NodeHierarchy();

	ExportableResources& resources() const { return m_resources; }

	const Arguments& arguments() const { return m_resources.arguments(); }

	// Gets or creates the node
	// Returns null if the DAG path has no node
	ExportableNode* getNode(const MDagPath& dagPath);

	// Gets or creates the parent of the node.
	// Returns null if the node has no logical parent.
	ExportableNode* getParent(ExportableNode* node);

	static int distanceToRoot(ExportableNode* node);

	const NodeTable& table() const { return m_table; }

private:
	DISALLOW_COPY_MOVE_ASSIGN(NodeHierarchy);

	friend class ExportableNode;

	ExportableResources& m_resources;
	NodeTable m_table;
};

