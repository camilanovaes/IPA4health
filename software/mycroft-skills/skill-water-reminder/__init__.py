from adapt.intent import IntentBuilder
from mycroft.skills.core import MycroftSkill, intent_handler
from mycroft.util.log import LOG

#__author__ = 'camilanovaes'

#LOGGER = getLogger(__name__)

class WaterReminderSkill(MycroftSkill):

    def __init__(self):
        super(WaterReminderSkill, self).__init__(name="WaterReminderSkill")
        self.count = 0
        self.cups = 0

    @intent_handler(IntentBuilder("").require("Water"))
    def handle_hello_world_intent(self, message):
        self.speak_dialog("gender")
        self.speak("", expect_response=True)

    @intent_handler(IntentBuilder("").require("Sex"))
    def handle_count_intent(self, message):
        if message.data["Sex"] == "girl" or message.data["Sex"] == "woman":
            self.cups = 9
        else:  
            self.cups = 13
        self.speak_dialog("cups.water", data={"cups": self.cups})

   #  def stop(self):
   #     return False

def create_skill():
    return WaterReminderSkill()
