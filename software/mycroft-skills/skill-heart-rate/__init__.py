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
        self.ser = serial.Serial('/dev/ttyACM0', 115200, timeout = 1)
        self.aux = None
        self.total = None
        self.med = None
        self.c = 0
        self.read = None

    @intent_handler(IntentBuilder("").require("Heart"))
    def handle_heart_rate_intent(self, message):
        self.speak_dialog("init.sensor")
        self.ser.write(str("i").encode())  # Serial Test
        self.read = self.ser.readline().decode('ascii')
        timeout = time.time() + 5
        while (time.time() < timeout):
            if (self.read.rstrip() == 'o'):
                self.c = 1
                self.speak_dialog("started.sensor")
                self.ser.write(str("s").encode())
                break

                #while 1:
                #    try:
                #        if self.read.rstrip():
                #            for x in range(0, 10):
                #                self.aux.append(float(read))
                #                self.total += float(read)
                #
                #            dem = len(self.aux)
                #            self.med = int(self.total/dem)
                #        self.speak_dialog("heart.rate.med", data={"med": self.med})
                #
                #    except:
                #        self.speak_dialog("error.sensor")
                #        break

        if (time.time() > timeout):
            if (self.c == 0):
                self.speak_dialog("error.sensor")

    def stop(self):
        self.ser.write(str("f").encode())
        return True

def create_skill():
    return HeartRateSkill()
