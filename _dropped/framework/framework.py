from framework.modules.module_map import ModuleMap
from framework.option import Option
from framework.frame import bind_frame
import utils.print_utils as print_utils
import config as config

# Extends for framework routine
from . import FrameworkConsole

from pprint import pprint as pp
import cmd

g_modules = ModuleMap()


class Framework(cmd.Cmd, FrameworkConsole):
    modules = g_modules
    current_frame = None
    format_prompt = "noname/%s> "
    default_prompt = format_prompt % ""
    # Cmd module fields
    prompt = default_prompt
    ruler = "="

    # info
    def do_info(self, line):
        """info
        Prints module info"""
        if self.current_frame:
            pp(self.current_frame.__info__, indent=4)
        else:
            print_utils.time_print("Select module first")

    # Select module for use
    def do_use(self, line):
        """use {module_name/module_id}
        Use module"""
        line = line.split(" ")[0]
        # By id or by name
        try:
            module_id = int(line)
            loc_module = self.modules.by_id(module_id)
            if loc_module:
                module_name = loc_module["use_name"]
            else:
                module_name = None
        except ValueError:
            module_name = line
            loc_module = self.modules.by_name(module_name)
            module_id = loc_module["id"] if loc_module is not None else None
        # Create frame
        if loc_module is not None:
            self.current_frame = bind_frame(loc_module["handle"])()
            self.current_frame.print_options()
            self.prompt = self.format_prompt % module_name
        else:
            print_utils.time_print("No such module like: %s" % module_name)
        return False

    # Search for modules
    def do_search(self, line):
        """search [term]
        Search for modules"""
        def usage():
            print_utils.time_print(
                "Invalid number of arguments for 'search' command")
            print_utils.time_print("set command usage: search <term>")
        if line == "":
            usage()
            return False
        print(
            print_utils.get_modules_search_table(line, self.modules._arr)
            )

    # Shows listing
    def do_show(self, line):
        """search {options/modules}
        Shows details"""
        if line == "options":
            if self.current_frame is None:
                print_utils.time_print("Select module first")
            else:
                print("")
                self.current_frame.print_options()
        if line == "modules" or line == "":
            print("")
            print(print_utils.get_modules_search_table("", self.modules._arr))
        if line == "info":
            print("")
            self.current_frame.print_info()

    # Starts currently selected module
    def do_run(self, line):
        """run
        Run current module"""
        if self.current_frame is not None:
            self.current_frame.run()
            print("\n\n", end="")
        else:
            print_utils.time_print("Select module first")

    # Sets currently selected module's option
    def do_set(self, line):
        """set [option_name] [value]
        Run current module"""
        def usage():
            print_utils.time_print(
                "Invalid number of arguments for 'set' command")
            print_utils.time_print("set command usage: set <option> <value>")
        if not self.current_frame:
            print_utils.time_print("Select module first")
            return False
        line = line.split(" ")
        if len(line) < 2:
            usage()
            return False
        if len(line) != 2:
            if not line[1].startswith(config.LST_IND):
                usage()
                return False
            # for list indicator
            if line[1].startswith(config.LST_IND):
                line = [line[0], "".join(line[1:])]
        opt_name, opt_set_value = line

        options = []
        for item in self.current_frame._options:
            if item.opt_name == opt_name:
                options.append(item)

        for option in options:
            try:
                option.set_option_value(opt_set_value)
                print_utils.clear_screen()
            except Exception as e:
                print_utils.clear_screen()
                print("[-]", e, "\n")
            self.current_frame.print_options()
            return False
        print_utils.time_print("There's no option called '%s'" % opt_name)
