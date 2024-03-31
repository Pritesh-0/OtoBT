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
class TubeFound : public BT::SyncActionNode
{
        public:
                explicit TubeFound(const std::string &name) : BT::SyncActionNode(name, {})
                        {}
                BT::NodeStatus tick() override
                {
                        std::cout<<"Checking if the Tube is in sight: "<<this->name() <<std::endl;
			int status;std::cin>>status;
                        if(status){
                                std::cout<<"Tube is in Sight"<<std::endl;
                                return BT::NodeStatus::SUCCESS;
                        }
                        else{
                                return BT::NodeStatus::FAILURE;
                        }

                        return BT::NodeStatus::SUCCESS;
                }
};

//SearchTube
class SearchTube : public BT::SyncActionNode
{
        public:
                explicit SearchTube(const std::string &name) : BT::SyncActionNode(name, {})
                        {}
                BT::NodeStatus tick() override
                {
                        std::cout<<"Searching for Tube\nTube Found: "<<this->name() <<std::endl;
                        return BT::NodeStatus::SUCCESS;
                }
};

//GotoTube
class GotoTube : public BT::SyncActionNode
{
        public:
                explicit GotoTube(const std::string &name) : BT::SyncActionNode(name, {})
                        {}
                BT::NodeStatus tick() override
                {
                        std::cout<<"Going towards Tube: "<<this->name() <<std::endl;
                        return BT::NodeStatus::SUCCESS;
                }
};

//OpenGripper

//CloseGripper

int main()
{
	BT::BehaviorTreeFactory factory;
	factory.registerNodeType<AtWP>("AtWP");
	factory.registerNodeType<GotoWP>("GotoWP");
	factory.registerNodeType<TubeFound>("TubeFound");
	factory.registerNodeType<SearchTube>("SearchTube");
	factory.registerNodeType<GotoTube>("GotoTube");

	auto tree = factory.createTreeFromFile("./../bt_tree.xml");

	tree.tickWhileRunning();
	return 0;
}
