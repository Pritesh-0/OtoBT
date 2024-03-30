#include<iostream>
#include<chrono>
#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"

using namespace std::chrono_literals;

class AtWP : public BT::SyncActionNode
{
	public:
		explicit AtWP(const std::string &name) : BT::SyncActionNode(name, {})
			{}
		BT::NodeStatus tick() override
		{
			std::cout<<"Checking if Reached at WayPoint: "<<this->name() <<std::endl;
			return BT::NodeStatus::SUCCESS;
		}
};

int main()
{
	BT::BehaviorTreeFactory factory;
	factory.registerNodeType<AtWP>("AtWP");

	auto tree = factory.createTreeFromFile("./../bt_tree.xml");

	tree.tickWhileRunning();
	return 0;
}
