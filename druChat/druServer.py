from xmlrpc.server import SimpleXMLRPCServer
import queue
#Class to be run on server.
class druChatServer:
    def __init__(self):
        self.messages = [None]*10
        self.size = 0
    def sendMessage(self,message):
        self.messages[self.size] = message
        self.size = (self.size + 1) % 10
    def getMessage(self, i):
        return self.messages[i]
    def numOfMessages(self):
        return self.size
    
        
server = SimpleXMLRPCServer(("localhost", 8000), allow_none=True)
server.register_instance(druChatServer())
server.serve_forever()