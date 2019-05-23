import re

class Vld_custom_lamda():
    def __init__(self, _lambda, _desc):
        self._lambda = _lambda
        self._desc = _desc
        self.name = "Lambda Validator"
    def __call__(self, value):
        success = self._lambda(value)
        msg = "%s : %s" % (self.name, "valid" if success else "invalid")
        msg += "\n%s" % self._desc
        return msg, success

regex_email_address = "^[a-zA-Z0-9.!#$%&’*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*$"

def vld_always_valid(value):
    name = "Blank validator"
    success = True
    msg = "%s : Always valid" % name
    return msg, success

def vld_always_invalid(value):
    name = "Blank validator"
    success = False
    msg = "%s : Always invalid" % name
    return msg, success

def vld_email_address(value):
    name = "Email address validator"
    success = re.fullmatch(regex_email_address, value) != None
    msg = "%s : %s" % (name, "valid" if success else "invalid")
    return msg, success

def vld_ipv4_address(value):
    name = "IPv4 validator"
    try:
        v = value.split(".")
        success = all([int(x) >= 0 and int(x) <= 255 and len(v) == 4 < 256 for x in v])
    except ValueError:
        success = False
    msg = "%s : %s" % (name, "valid" if success else "invalid")
    return msg, success

def vld_port(value):
    name = "Port validator"
    try:
        success = int(value) >= 0 and int(value) <= (2**16)-1
    except ValueError:
        success = False
    msg = "%s : %s" % (name, "valid" if success else "invalid")
    return msg, success

def vld_ipv4_with_port(value):
    name = "IPv4 with port validator"
    if len(value.split(":")) == 2:
        _, success_ipv4 = vld_ipv4_address(value.split(":")[0])
        _, success_port = vld_port(value.split(":")[1])
        success = success_ipv4 and success_port
    else:
        success = False
    msg = "%s : %s" % (name, "valid" if success else "invalid")
    return msg, success
