from adapt.intent import IntentBuilder
from mycroft.skills.core import MycroftSkill, intent_handler
from mycroft.util.log import LOG

__author__ = 'camilanovaes'

#LOGGER = getLogger(__name__)

class GoodnightSkill(MycroftSkill):

    def __init__(self):
        super(GoodnightSkill, self).__init__(name="GoodnightSkill")
        self.count = 0

    @intent_handler(IntentBuilder("").require("Goodnight"))
    def handle_good_night_intent(self, message):
        self.speak_dialog("good.night")

    @intent_handler(IntentBuilder("").require("Count").require("Dir"))
    def handle_count_intent(self, message):
        if message.data["Dir"] == "up":
            self.count += 1
        else:  # assume "down"
            self.count -= 1
        self.speak_dialog("count.is.now", data={"count": self.count})

    # The "stop" method defines what Mycroft does when told to stop during
    # the skill's execution. In this case, since the skill's functionality
    # is extremely simple, there is no need to override it.  If you DO
    # need to implement stop, you should return True to indicate you handled
    # it.
    #
    # def stop(self):
    #    return False


def create_skill():
    return GoodnightSkill()
