from framework.validator import validators as V

class Validator():

    def __init__(self, _validators):
        self._validators = _validators
        self._success = False
        self._validators.append(V.vld_always_valid)

    def add_validator(self, validator):
        assert(callable(validator))
        self._validators.append(validator)

    def _validate_non_list(self):
        if self.opt_value == None and self.mandatory == True:
            return [{
                "msg": "Argument '%s' is mandatory" % self.opt_name,
                "success": False}], False
        msg = ""
        results = []
        success = True
        for valid in self._validators:
            temp_msg, temp_success = valid(self.opt_value)
            if not temp_success:
                success = False
            results.append({
                "msg": "%s | value:=%s" % (temp_msg, self.opt_value),
                "success":temp_success
            })
        return results, success

    def _validate_list(self):
        if self.opt_value == [] and self.mandatory == True:
            return [{
                "msg": "Argument '%s' is mandatory" % self.opt_name,
                "success": False}], False
        msg = ""
        results = []
        success = True
        for valid in self._validators:
            for it_val, val in enumerate(self.opt_value):
                temp_msg, temp_success = valid(val)
                if not temp_success:
                    success = False
                results.append({
                    "msg": "%s | it:=%s , value:=%s" % (temp_msg, it_val, self.opt_value[it_val]),
                    "success":temp_success
                })
        return results, success

    def validate(self):
        # Validate non list
        if self.opt_is_list == False:
            results, success = self._validate_non_list()
            self._success = success
            return results, success
        # Validate list
        if self.opt_is_list == True:
            results, success = self._validate_list()
            self._success = success
            return results, success
