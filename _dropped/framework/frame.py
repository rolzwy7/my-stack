from framework.option import OptionsContainer


# Create framework frame
def bind_frame(module):
    class Frame(module, OptionsContainer):
        def init(self):
            self._reset_frame()

        def _reset_frame(self):
            self._options = []
    return Frame
