from adapt.intent import IntentBuilder
from mycroft.skills.core import MycroftSkill, intent_handler
from mycroft.util.log import LOG
import time
import sys
import subprocess

__author__ = 'camilanovaes'

#LOGGER = getLogger(__name__)

class NfcSkill(MycroftSkill):

    def __init__(self):
        super(NfcSkill, self).__init__(name="NfcSkill")

    @intent_handler(IntentBuilder("").require("Read"))
    def handle_read_nfc_intent(self, message):
        self.speak_dialog("reading.nfc")
        #exec(open("/home/pi/skills-scrips/NFC/Read.py").read()) 
        #s_nfc = subprocess.check_output([sys.executable, "/home/pi/skills-scrips/NFC/Read.py"])
        #if (s_nfc == 'ok'):
        #timeout = time.time() + 5
        #while (time.time() > timeout):
        with open('/home/pi/skills-scrips/NFC/Data2.txt', 'r') as arq:
            data = arq.readlines()
        for men in data:
            self.speak(men)
            time.sleep(2)

    @intent_handler(IntentBuilder("").require("Write"))
    def handle_write_nfc_intent(self, message):
        self.speak_dialog("writing.nfc")

    def stop(self):
        return True

def create_skill():
    return NfcSkill()
