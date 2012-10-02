from stage.scenario import Scenario
from stage.model import Model
from stage.agents.testagent import TestAgent
from stage.agents.randommoveagent import MovingAgent
from stage.agents.circlewalker import CircleWalkerAgent

'''
Defines a scenario with 5 nodes each with a local 'Moving' agent
'''
class ScenarioDef(Scenario) :
    def __init__(self) :
        Scenario.__init__(self)

        for node_id in range(0, 5) :
            ''' Make the node model '''
            node = Model(name='n%s' % node_id, position=(0,0,0), agents = [], interfaces = {})
            ''' Instance of a 'MovingAgent' '''
            agent_instance = MovingAgent()
            ''' Place the agent on the node '''
            node.get('agents').append(agent_instance)
            ''' Add the node to the scenario '''
            self._nodes.append(node)
