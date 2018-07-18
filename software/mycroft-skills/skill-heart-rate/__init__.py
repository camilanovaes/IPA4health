from adapt.intent import IntentBuilder
from mycroft.skills.core import MycroftSkill, intent_handler
from mycroft.util.log import LOG
import time
import serial

__author__ = 'camilanovaes'

#LOGGER = getLogger(__name__)

class HeartRateSkill(MycroftSkill):

    # The constructor of the skill, which calls MycroftSkill's constructor
    def __init__(self):
        super(HeartRateSkill, self).__init__(name="HeartRateSkill")
        self.ser = serial.Serial(
            port='/dev/ttyACM0',
            baudrate = 115200,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=1
        )
        self.aux = []
        self.total = 0
        self.med = 0
        self.c = 0
        self.read = ''
        self.r = ''

    @intent_handler(IntentBuilder("").require("Heart"))
    def handle_heart_rate_intent(self, message):
        self.speak_dialog("init.sensor")	
        #self.ser.write(str.encode("i"))
        #self.read = self.ser.readline().decode('utf-8')[:-2]
        #self.read = self.ser.readline()
        #self.r = self.read.rstrip()
        #timeout = time.time() + 10
        #while (time.time() < timeout):
         #   self.r = self.read.rstrip()
          #  if (self.r == 'o'):
           #     self.c = 1
            #    self.speak_dialog("started.sensor")
             #   self.ser.write(str.encode("s"))
                #for x in range(0,5):
                 #   if self.read:
                  #      for x in range(0, 5):
                   #         self.aux.append(float(read))
                    #        self.total += float(read)

                     #   dem = len(self.aux)
                      #  self.med = int(self.total/dem)
                #    self.speak_dialog("heart.rate.med", data={"med": self.med})
              #  timeout2 = time.time() + 100
               # while (time.time() < timeout2):
                #   pass 
                
  #              self.ser.write(str.encode("f"))

#        if (time.time() > timeout):
 #           if (self.c == 0):
  #              self.speak_dialog("error.sensor")
   #             self.ser.write(str.encode("f"))

    def stop(self):
        self.ser.write(str.encode("f"))
        return False

def create_skill():
    return HeartRateSkill()
