from stage.scenario import Scenario
from stage.model import Model
from stage.agents.testagent import TestAgent
from stage.agents.randommoveagent import MovingAgent
from stage.agents.circlewalker import CircleWalkerAgent

class ScenarioConcrete(Scenario) :
    def __init__(self) :
        Scenario.__init__(self)

        
        m = Model(name='n0', position=(50,50,0), agents = [], interfaces = {})
        m.get('agents').append(CircleWalkerAgent(Model(job='send')))
        self._nodes.append(m)
        #m = Model(name='n0', position=(0,0,0), agents = [], interfaces = {})
        #m.get('agents').append(MovingAgent(Model(job='send')))
        #n = Model(name='n1', position=(15,15,0), agents = [], interfaces = {})
        #n.get('agents').append(MovingAgent(Model(job='send')))
        #o = Model(name='n2', position=(0,20,0), agents = [], interfaces = {})
        #o.get('agents').append(MovingAgent(Model(job='send')))
        #p = Model(name='n3', position=(30,30,0), agents = [], interfaces = {})
        #p.get('agents').append(MovingAgent(Model(job='send')))
        #q = Model(name='n4', position=(50,10,0), agents = [], interfaces = {})
        #q.get('agents').append(MovingAgent(Model(job='send')))
        #self._nodes.append(m)
        #self._nodes.append(n)
        #self._nodes.append(o)
        #self._nodes.append(p)
        #self._nodes.append(q)

