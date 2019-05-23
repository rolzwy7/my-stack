from framework.modules.module_map import ModuleMap
import utils.print_utils as print_utils

g_modules = ModuleMap()


def framework_intro():
    ret = print_utils.get_banner()
    ret += "\n - Total modules: %d" % len(g_modules._arr)
    ret += "\n\n"
    return ret


class FrameworkConsole():
    # Clears console screen
    def do_clear(self, line):
        """clear
        Clear screen"""
        print_utils.clear_screen()
        print(print_utils.get_banner())

    # Clears console screen
    def do_cls(self, line):
        """cls
        Clear screen"""
        self.do_clear("")

    # Override emptyline method to do nothing
    def emptyline(self):
        pass

    # Prints banner
    def do_banner(self, line):
        """banner
        Prints banner"""
        framework_intro()

    # Exit framework cmd routine
    def do_exit(self, line):
        """exit
        Exit cmd routine"""
        return True

    # Stop using current module
    def do_reset(self, line):
        """reset
        Stop using current module"""
        self.prompt = self.default_prompt
        self.current_frame = None
