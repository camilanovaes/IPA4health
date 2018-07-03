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
    
    ser = serial.Serial(
           port='/dev/ttyACM0',
           baudrate = 115200,
           parity=serial.PARITY_NONE,
           stopbits=serial.STOPBITS_ONE,
           bytesize=serial.EIGHTBITS,
           timeout=1
    )
    
    @intent_handler(IntentBuilder("").require("Heart"))
    def handle_heart_rate_intent(self, message):
        self.speak_dialog("init.sensor")	
        ser.write("i")
        read = ser.readline() 
        if read == 'o':
            self.speak_dialog("started.sensor")
            ser.write("s")
        else:
            self.speak_dialog("error.sensor")

    def stop(self):
        return False

def create_skill():
    return HeartRateSkill()
