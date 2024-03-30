#include<iostream>
#include<chrono>
#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"

using namespace std::chrono_literals;

//AtWP
class AtWP : public BT::SyncActionNode
{
	public:
		explicit AtWP(const std::string &name) : BT::SyncActionNode(name, {})
			{}
		BT::NodeStatus tick() override
		{
			std::cout<<"Checking if Reached at WayPoint: "<<this->name() <<std::endl;
			int status;std::cin>>status;
			if(status){
				std::cout<<"Rover already at WayPoint"<<std::endl;
				return BT::NodeStatus::SUCCESS;
			}
			else{
				return BT::NodeStatus::FAILURE;
			}
		}
};

//GotoWP
class GotoWP : public BT::SyncActionNode
{
        public:
                explicit GotoWP(const std::string &name) : BT::SyncActionNode(name, {})
                        {}
                BT::NodeStatus tick() override
                {
                        std::cout<<"Searching and Moving to WayPoint: "<<this->name() <<std::endl;
                        return BT::NodeStatus::SUCCESS;
                }
};

//TubeFound


int main()
{
	BT::BehaviorTreeFactory factory;
	factory.registerNodeType<AtWP>("AtWP");
	factory.registerNodeType<GotoWP>("GotoWP");

	auto tree = factory.createTreeFromFile("./../bt_tree.xml");

	tree.tickWhileRunning();
	return 0;
}
