import utils.print_utils as print_utils
from framework.validator.validator import Validator
from framework.option_extended import OptionExt
from texttable import Texttable


class Option(Validator, OptionExt):

    def __init__(self, opt_name, opt_value, opt_validators, opt_type, opt_is_list, mandatory, help):
        super(Option, self).__init__(opt_validators)
        self.opt_name = opt_name
        self.opt_value = opt_value
        self.opt_type = opt_type
        self.opt_is_list = opt_is_list
        self.mandatory = mandatory
        self.help = help

    def get_option_row(self):
        opt_name = "%s (*)" % self.opt_name if self.mandatory else self.opt_name
        opt_value = self.opt_value
        if self.opt_is_list:
            opt_name += "\n>size: %s" % len(opt_value)
            if len(opt_value) >= 10:
                opt_value = opt_value[:4] + ["...", "..."] + opt_value[6:10]
        if self.opt_type == bool:
            opt_value = "true" if opt_value in (True, "true", "True", "1") else opt_value
            opt_value = "false" if opt_value in (False, "false", "False", "0") else opt_value
        return [opt_name, opt_value, self.help]

    def set_option_value(self, value):
        try:
            self.opt_value = self.set_option_value_extended(value)
        except Exception as e:
            raise


class OptionsContainer():

    def __init__(self):
        _options = []

    def add_option(self,
                   opt_name,
                   opt_default_value,
                   opt_validators,
                   opt_type,
                   opt_is_list,
                   mandatory,
                   help
                   ):
        # opt_value
        opt_value = None
        # opt_name
        assert(isinstance(opt_name, str))
        # opt_default_value
        if opt_default_value is not None:
            if opt_is_list is False:
                assert(type(opt_default_value) == opt_type)
                opt_value = opt_default_value
            else:
                assert(type(opt_default_value) == list)
                assert(all([type(_) == opt_type for _ in opt_default_value]) is True)
                opt_value = opt_default_value
        # submit new option
        new_option = Option(opt_name, opt_value, opt_validators, opt_type, opt_is_list, mandatory, help)
        self._options.append(new_option)

    def print_options(self):
        table = Texttable()
        all_rows = []
        all_rows.append(["Option Name", "Option Value", "Help"])
        for option in self._options:
            all_rows.append(option.get_option_row())
        table.add_rows(all_rows)
        print("[*]", self.__info__["name"])
        print("\tType: %s" % self.__info__["type"])
        print(table.draw() + "\n")

    def print_info(self):
        print(self.__info__)

    def get_option(self, opt_name):
        g = (item for item in self._options if item.opt_name == opt_name)
        for e in g:
            return e

    def opt_val(self, opt_name):
        g = (item for item in self._options if item.opt_name == opt_name)
        for e in g:
            return e.opt_value

    def validate(self):
        for opt in self._options:
            results, success = opt.validate()
            if not success:
                print("[-] Option '%s' is invalid" % opt.opt_name)
                for _ in results:
                    if _["success"] != True:
                        print("[-]", _["msg"])
                return False
        return True
